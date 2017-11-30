#include<opencv2\opencv.hpp>
#include<stdio.h>
#include<math.h>
#include<vector>
#include"Mesh_Morphing.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<fstream>

using namespace std;
using namespace cv;


int main()
{
	Mat img_src=imread("test2.jpg",0);
	Mat img_dst=imread("test1.jpg",0);
	imshow("src",img_src);
	imshow("dst",img_dst);
	cout<<"����չʾ�ķֱ���Դͼ��(src)��Ŀ��ͼ��(dst),�������������һ��ѡ��"<<endl;
	waitKey(0);
	destroyAllWindows();
	string str;

	Mesh_Morphing MM(img_src,img_dst);
	int flag1;
	int flag2 =1;
	int flag3 =1;
	string src,dst;
	while(flag2)
	{
	cout<<"�Ƿ�Ҫ�������ļ�ѡ�������㣿"<<endl<<"1.��"<<endl<<"2.��"<<endl;
	cin>>flag1;
	switch (flag1)
	{
	case 1:
		src="feature_src";
		dst="feature_dst";
		MM.get_feature(src,dst);
		flag2=0;
		break;
	case 2:
		while(flag3)
		{
		cout<<"��ѡ��������"<<endl<<"ע�⣺ѡ��������ʱ��˳�����Ŀһ��Ҫ��Ӧ��"<<endl;
		MM.feature_dst.clear();
		MM.feature_src.clear();
		MM.get_feature();
		if(MM.feature_dst.size()==MM.feature_src.size())
			flag3=0;
		else
		{
			cout<<"�������������ȣ�����"<<endl;
			flag3=1;
		}
		}
		flag2=0;
		break;
	default:
		flag2=1;
		break;
	}
	}

	ofstream feature_src,feature_dst;

	MM.Change_to_Triangle();
	vector<Mat> mid;
	int number;
	cout<<"��Ҫ���ɶ�����ͼƬ��"<<endl;
	cin>>number;
	for(int i=0;i<=number-1;i++)
	{
		mid.push_back(MM.Mesh_Morphing_Procedure((float)i/(number-1)));
		cout<<"�������ɵ�"<<i<<"��ͼƬ"<<endl;
	}
	
		cout<<"����չʾ��"<<mid.size()<<"����Ƭ"<<endl;
	for(int i=0;i<mid.size();i++)
	{
		str = "mid"+to_string(i)+".jpg";
		imshow("mid",mid[i]);
		imwrite(str,mid[i]);
		waitKey(1000);
	}
	destroyAllWindows();
	cout<<"ͼƬչʾ��ϣ�����Ŀ¼�²鿴�����ͼƬ"<<endl;
	flag2=1;
	if(flag1==2)
	{
	while(flag2)
	{
	cout<<"�Ƿ񱣴�ո�ѡ��������㣿"<<endl<<"1.��"<<endl<<"2.��"<<endl;
	cin>>flag3;
	switch (flag3)
	{
	case 1:
		feature_src.open("feature_src.txt");
		for(int i=0;i<MM.feature_src.size();i++)
		{
			feature_src<<MM.feature_src[i].x<<endl;
			feature_src<<MM.feature_src[i].y<<endl;
		}
			feature_src.close();	
		feature_dst.open("feature_dst.txt");
		for(int i=0;i<MM.feature_dst.size();i++)
		{
			feature_dst<<MM.feature_dst[i].x<<endl;
			feature_dst<<MM.feature_dst[i].y<<endl;
		}
		feature_dst.close();
		flag2=0;
		break;
	case 2:
		flag2=0;
		break;
	default:
		flag2=1;
		break;
	}
	}
	}
	waitKey(0);
	return 0;
}

