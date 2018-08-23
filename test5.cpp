 #include <iostream>
#include <fstream>
#include <string>
#include <vector>
 #include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
 using namespace std;
 struct result_
 {
	 string plate;
	 Rect vehicle_pos;
	 Rect plate_pos;
 };



int readDir(char *dirName, vector<string> &filesName)
{
	int n=0;
	if (access(dirName,0)!=0)
	{
		return 0;
	}
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	char szFullPath[MAX_PATH];
	char szFilePath[MAX_PATH];
	sprintf( szFilePath, "%s/\*", dirName);
	if((hListFile = FindFirstFile(szFilePath, &FindFileData)) == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	do 
	{
		if( lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 || lstrcmp(FindFileData.cFileName, TEXT("..")) == 0 )
		{
			continue;
		}
		sprintf(szFullPath, "%s/\%s", dirName, FindFileData.cFileName);
		if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			char *pszFileType = NULL;
			pszFileType = &(FindFileData.cFileName[strlen(FindFileData.cFileName) - 3]);
			//cout<<pszFileType<<endl;
			if(!stricmp(pszFileType, "jpg") || !stricmp(pszFileType, "bmp"))
			{
				string str_szFullPath(szFullPath);
				filesName.push_back(str_szFullPath);
			}
		}
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			n=n+1;
			readDir(szFullPath, filesName);
		}
	}while(FindNextFile(hListFile, &FindFileData));

	FindClose(hListFile);
	ZeroMemory(&FindFileData, sizeof(FindFileData));
	return 0;
}

int test_part(string file,string image,string str_vehicle_pos_x2y2,string partPath,int color)
{
	ifstream f_pos;
	f_pos.open(file, ios::in);
	if (!f_pos.is_open())
	{
		cout << "ÎÄ¼þÊý¾Ý´ò¿ª´íÎó£¡"<< endl;
		system("pause");
		return false;
	}

	fstream f_pos_x2y2;
	f_pos_x2y2.open(str_vehicle_pos_x2y2, ios::trunc | ios::out);
	if (!f_pos_x2y2.is_open())
	{
		cout << "x2y2ÎÄ¼þÊý¾Ý´ò¿ª´íÎó£¡"<< endl;
		system("pause");
		return false;
	}

	char line[256];
	while(f_pos.getline(line,sizeof(line)))
	{
		string line_name; 
		int x,y,width,height;
		stringstream str_s(line);
		str_s >> line_name>>x>>y>>width>>height;
		
		f_pos_x2y2<<line_name.c_str()<<" "<<x<<" "<<y<<" "<<x+width-1<<" "<<y+height-1<<endl;
		line_name =line_name+".jpg";
	   line_name=partPath+line_name;
	   Mat img=imread(line_name.c_str());
	   if(img.data==NULL)
	   {
		   printf("img.data=NULL\n");
		  system("pause");
	   }


	}

	f_pos.close();
	return 0;
}
int test5(int argc, char *argv[])
{
	string str_vehicle_pos="I:/calibration/0_ÎÚÂ³Ä¾Æë800/0_vehicle_rect";
	/*string str_plate_pos="I:/calibration/0_ÎÚÂ³Ä¾Æë800/0_plate_rect";
	string str_plate_name="I:/calibration/0_ÎÚÂ³Ä¾Æë800/0_plate_name";*/
	string str_image="I:/calibration/0_ÎÚÂ³Ä¾Æë800/1";
	ifstream f_vehicle_pos;
	f_vehicle_pos.open(str_vehicle_pos, ios::in);

	string str_vehicle_pos_x2y2="I:/calibration/0_ÎÚÂ³Ä¾Æë800/0_vehicle_rect_x2y2";
	

	/* ifstream f_plate_pos;
	f_plate_pos.open(str_vehicle_pos, ios::in);

	ifstream f_plate_name;
	f_plate_name.open(str_vehicle_pos, ios::in);
	map<string,vector<struct result_>>  result_out;*/


	return 0;
}