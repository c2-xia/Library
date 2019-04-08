using MiniJSON;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LayerTool
{
    class LayerInfo
    {
        public long layer;
        public string name;
        public string dirName;
        public static string LAYER_FOLDER_NAME = "~layer";
        public static string LAYER_DESCRIBE_FILE_NAME = LAYER_FOLDER_NAME+ "\\describe.txt";
    }
    class myEmployeeCompare : System.Collections.IComparer
    {
        public int Compare(object x, object y)
        {
            return (int)(((LayerInfo)x).layer - ((LayerInfo)y).layer);
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            string rootPath = "E:\\xia\\Git\\Library\\Core";

            string[] dir = Directory.GetDirectories(rootPath);
            System.Collections.ArrayList list = new System.Collections.ArrayList();
            for(int i=0;i<dir.Length;i++)
            {
                DirectoryInfo fdir = new DirectoryInfo(dir[i]);

                DirectoryInfo[] dir_sub = fdir.GetDirectories();
                if(Program.contain_layer_describe(dir_sub) )
                {
                    list.Add(dir[i]);
                }                
            }
            System.Collections.ArrayList nodeList = new System.Collections.ArrayList();
            for ( int i = 0 ; i < list.Count ; i++ )
            {
                nodeList.Add(getLayerInfo((string)list[i]));
            }
            nodeList.Sort(new myEmployeeCompare());

            for (int i = 0; i < nodeList.Count; i++)
            {
                LayerInfo info = nodeList[i] as LayerInfo;
                string path_name = rootPath + "\\"+info.dirName;
                DirectoryInfo fi = new DirectoryInfo(path_name);
                
                fi.MoveTo(rootPath + "\\" + info.layer + "_" + info.name);
                 

            }
            int ii = 0;
        }
        
        static LayerInfo getLayerInfo(string path)
        {
            LayerInfo result = new LayerInfo();
            StreamReader srReadFile = new StreamReader(path + "\\" + LayerInfo.LAYER_DESCRIBE_FILE_NAME);
            string str_test = srReadFile.ReadToEnd();
            srReadFile.Close();
            Dictionary<string, object> dict = Json.Deserialize(str_test) as Dictionary<string, object>;
            result.name = dict["name"] as string;
            result.layer = (long)dict["layer"];
            DirectoryInfo fdir = new DirectoryInfo(path);
            result.dirName = fdir.Name;
            
            return result;
        }

        static bool contain_layer_describe(DirectoryInfo[] dir_sub)
        { 
            for( int i=0 ; i < dir_sub.Length ; i++ )
            {
                if(dir_sub[i].Name == LayerInfo.LAYER_FOLDER_NAME )
                {
                    return true;
                }
            }
            return false;
        }

    }
}
