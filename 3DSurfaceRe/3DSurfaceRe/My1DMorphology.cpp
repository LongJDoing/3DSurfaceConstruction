#include "StdAfx.h"
#include "My1DMorphology.h"

CMy1DMorphology::CMy1DMorphology(void)
{
}


CMy1DMorphology::~CMy1DMorphology(void)
{
}
void CMy1DMorphology::OneDDilation(int * bitmap, int length)
{
	int * tempbitmap = new int[2*length];
	for(int j = 0; j < 2; j++)
		for(int i = 0; i < length; i++)
		{
			tempbitmap[i + j*length] = bitmap[i];
		}

	int num = length / 10;
	int * MySE = new int[num];
	for(int i = 0; i < num; i++)
		MySE[i] = 1;
	for(int i = 0; i < length; i++)
		bitmap[i] = 0;
	for(int x = 0; x < length; x++)  // A的长度
		for(int j = 0; j < num; j++)  // B的长度
		{
			if(tempbitmap[x + j] == 1)
			{
				bitmap[x] = 1;
				break;
			}
		}
	//fout << endl;
	//fout << "Dilation之后" << endl;

	//for(int i = 0; i < length; i++)
	//	fout << bitmap[i] << " ";
	//fout<< endl;
	delete tempbitmap, MySE;
}

void CMy1DMorphology::OneDErosion(int * bitmap, int length)
{
	int * tempbitmap = new int[2*length];
	for(int j = 0; j < 2; j++)
		for(int i = 0; i < length; i++)
		{
			tempbitmap[i + j*length] = bitmap[i];
		}
	int num = length / 10;
	int * MySE = new int[num];
	for(int i = 0; i < num; i++)
		MySE[i] = 1;
	for(int i = 0; i < length; i++)
		bitmap[i] = 1;
	for(int i = 0; i < 2*length; i++)
	{
		if(tempbitmap[i] == 1)
			tempbitmap[i] = 0;
		else
			tempbitmap[i] =1;
	}
	for(int x = 0; x < length; x++)  // A的长度
		for(int j = 0; j < num; j++)  // B的长度
		{
			if(tempbitmap[x + j] == 1)
			{
				bitmap[x] = 0;
				break;
			}
		}
	delete tempbitmap, MySE;
	//fout << endl;
	//fout << "Erosion之后" << endl;

	//for(int i = 0; i < length; i++)
	//	fout << bitmap[i] << " ";
	//fout<< endl;
}

void CMy1DMorphology::OneDClosing(int * bitmap, int length)
{
	this->OneDDilation(bitmap, length);
	this->OneDErosion(bitmap, length);
}

void CMy1DMorphology::OneDOpening(int * bitmap, int length)
{
	this->OneDErosion(bitmap, length);
	this->OneDDilation(bitmap, length);
}