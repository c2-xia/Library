#ifndef VECTOR_MAP_H
#define VECTOR_MAP_H
#include "sorted_vector.h"
 
template<class Key, class T, class Compare = std::less<Key>, 
		 class Allocator = std::allocator<std::pair<Key, T> > >
class vector_map
{
	public:
	
	typedef Key												key_type;
	typedef T												mapped_type;
	typedef std::pair<Key,T>							value_type;
	typedef Compare										key_compare;
	typedef Allocator										allocator_type;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference	const_reference;
	typedef typename Allocator::size_type			size_type;
	typedef typename Allocator::difference_type	difference_type;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
		
	class value_compare
		: public std::binary_function<value_type,value_type,bool>
	{
	public:
		bool operator()(const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
		bool operator()(const key_type& x, const value_type& y) const
		{
			return comp(x, y.first);
		}
		bool operator()(const value_type& x, const key_type& y) const
		{
			return comp(x.first, y);
		}
		
		value_compare() {}
		value_compare(Compare c) : comp(c) {}
	protected:
		Compare comp;


		friend class vector_map;
	};
	
	typedef	sorted_vector<value_type, value_compare, Allocator>	container;
	typedef	typename container::container vector_container;
	typedef typename 	container::iterator									iterator;
	typedef typename	container::const_iterator							const_iterator;
	typedef typename	container::reverse_iterator						reverse_iterator;		
	typedef typename	container::const_reverse_iterator				const_reverse_iterator;

	public:

	// ctors	
	vector_map (const Compare& comp = Compare (), const Allocator& a = Allocator ())
		: c (value_compare(comp), a)
	{ }
	
	template <class InputIterator>
	vector_map(InputIterator first, InputIterator last, const Compare& comp = Compare (), const Allocator& a = Allocator ())
		: c (value_compare(comp), a)
	{ insert_one (first, last); }

	// iterators 	
	iterator						begin()							{ return c.begin (); }
	const_iterator				begin() const					{ return c.begin (); }
	iterator						end()								{ return c.end (); }
	const_iterator				end() const						{ return c.end (); }
	reverse_iterator			rbegin()							{ return c.rbegin (); }
	const_reverse_iterator	rbegin() const					{ return c.rbegin (); }
	reverse_iterator			rend()							{ return c.rend (); }
	const_reverse_iterator	rend() const					{ return c.rend (); }

	//  capacity:
	bool      				empty() const						{ return c.empty (); }
	size_type				size() const						{ return c.size ();  }
	size_type     			max_size() const					{ return c.max_size (); }

	//  modifiers:
	std::pair<iterator, bool>	insert(const value_type& x)			{ return c.insert_one (x); }
	
	template <class InputIterator>
	void 		insert(InputIterator first, InputIterator last)	{ c.insert_one(first, last); }

	void		erase(iterator position)						{ c.erase (position); }
	size_type	erase(const key_type& x)					{ return c.erase_one (x); }
	void		erase(iterator first, iterator last)		{ c.erase (first, last); }
	void		swap(vector_map& x)								{ c.swap (x.c); }
	void		clear()												{ c.clear (); }

	//  observers:
	key_compare   key_comp() const							{ return c.value_comp ().comp; }
	value_compare value_comp() const							{ return c.value_comp (); }
	 
	mapped_type& operator[] (const key_type& x)			{ mapped_type* temp; c.find_or_insert (temp, x); return *temp; }
		
	iterator       find(const key_type& x)					{ return c.find (x); }
	const_iterator find(const key_type& x) const			{ return c.find (x); }
	size_type      count(const key_type& x) const		{ return c.count_one (x); }

	iterator       lower_bound(const key_type& x)		{ return c.lower_bound (x); }
	const_iterator lower_bound(const key_type& x) const{ return c.lower_bound (x); }
	iterator       upper_bound(const key_type& x)		{ return c.upper_bound (x); }
	const_iterator upper_bound(const key_type& x) const{ return c.upper_bound (x); }

	std::pair<iterator,iterator> equal_range(const key_type& x)							{ return c.equal_range (x); }
	std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const	{ return c.equal_range (x); }
	 
	void 					reserve (size_type n)				{ c.reserve (n); }
	
	vector_container& get_vector () { return c.c; }

	void push_unsorted (const key_type& x, const mapped_type& value)
	{
		get_vector().push_back(std::make_pair(x, value));
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
	
	private:
	
	container				c;	
};
 

#endif
