#ifndef VECTOR_SET_H
#define VECTOR_SET_H

#include "sorted_vector.h"

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class vector_set
{
	public:
	
	typedef 			sorted_vector<Key, Compare, Allocator>	container;
	typedef typename	container::container					vector_container;
	typedef	typename	container::iterator						iterator;		
	typedef	typename	container::const_iterator				const_iterator;
	typedef	typename	container::reverse_iterator				reverse_iterator;		
	typedef	typename	container::const_reverse_iterator		const_reverse_iterator;
	typedef	typename	container::value_type					value_type;
	typedef	typename	container::value_type					key_type;
	typedef				Compare									key_compare;
	typedef				Compare									value_compare;
	typedef	typename	container::size_type					size_type;
	typedef	typename	container::difference_type				difference_type;
	typedef				Allocator								allocator_type;
	
	
	vector_set (const Compare& comp = Compare (), const Allocator& a = Allocator()) 
		: c (comp, a)	{ }
	
	template <class InputIterator>
	vector_set (InputIterator first, InputIterator last, const Compare& comp = Compare (), const Allocator& a = Allocator())
		: c (comp, a)
	{
		assign(first, last);
	}
	 
	template<class InputIterator>
	void assign_sorted (InputIterator first, InputIterator last){ c.c.assign (first, last); c.verify_duplicates_and_sorted (); }
	 
	template<class InputIterator>
	void assign (InputIterator first, InputIterator last)
	{
		c.c.assign (first, last);
		
		sort();
	}
	 
	template<class InputIterator>
	void assign_clear_duplicates (InputIterator first, InputIterator last)
	{
		c.c.assign (first, last);
		std::stable_sort(c.begin(), c.end(), c.value_comp());
		 
		if (!empty())
		{
			Key* previous = &*c.begin();
			iterator i = c.begin(); i++;
			for (; i != c.end();)
			{
				if (*i < *previous || *previous < *i)
				{
					previous = &*i;
					i++;
				}
				else
				{
					iterator e;
					for (e=i;e!=c.end() && !(*e < *previous || *previous < *e);e++)
						;
					c.erase(i, e);
				}
			}
		}

		c.verify_duplicates_and_sorted ();
	}
	
	bool empty () const														{ return c.empty (); }
	
	iterator						begin()										{ return c.begin (); }
	const_iterator				begin() const								{ return c.begin (); }
	iterator						end()											{ return c.end (); }
	const_iterator				end() const									{ return c.end (); }
	reverse_iterator			rbegin()										{ return c.rbegin (); }
	const_reverse_iterator	rbegin() const								{ return c.rbegin (); }
	reverse_iterator			rend()										{ return c.rend (); }
	const_reverse_iterator	rend() const								{ return c.rend (); }

	size_type					size() const								{ return c.size (); }
	size_type     				max_size() const							{ return c.max_size (); }
	
	std::pair<iterator,bool>insert(const value_type& x) 			{ return c.insert_one (x); }
	
	void      					erase(iterator position)				{ c.erase (position); }
	size_type 					erase(const key_type& x)				{ return c.erase_one (x); }
	void      					erase(iterator first, iterator last){ c.erase (first, last); }
	void 							clear()										{ c.clear (); }
	
	void 							swap(vector_set& x)						{ c.swap (x.c); }
	 
	iterator       			find(const key_type& x)					{ return c.find (x); }
	const_iterator				find(const key_type& x) const			{ return c.find (x); }
	size_type					count(const key_type& x) const		{ return c.count_one (x); }

	iterator      				lower_bound(const key_type& x)		{ return c.lower_bound (x); }
	const_iterator				lower_bound(const key_type& x) const{ return c.lower_bound (x); }

	iterator      				upper_bound(const key_type& x)		{ return c.upper_bound (x); }
	const_iterator				upper_bound(const key_type& x) const{ return c.upper_bound (x); }

	std::pair<iterator,iterator>              equal_range(const key_type& x)			{ return c.equal_range (x); }
	std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const	{ return c.equal_range (x); }
	 
	void 								reserve (size_type n)					{ c.reserve (n); }

	value_type& operator [] (int n) { return c[n]; }
	const value_type& operator [] (int n) const { return c[n]; }
	
	vector_container& get_vector () { return c.c; }

	void push_unsorted (const value_type& x)
	{
		get_vector().push_back(x);
	}
	
	void sort ()
	{
		std::sort(c.c.begin(), c.c.end(), c.value_comp ());
		c.verify_duplicates_and_sorted ();
	}
	
	void verify_duplicates_and_sorted () const
	{
		c.verify_duplicates_and_sorted ();
	}
	
	
	public:
	
	container				c;
};
 
#endif
