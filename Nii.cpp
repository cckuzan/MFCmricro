#include "stdafx.h"
#include "Nii.h"


char* niiReader::ReadFile(CString& inputfile)
{
	char Dimension = 0;
	char nii_x[2],nii_y[2],nii_z[2];

	char tempBuffer[100 * 1024];
	ifile.open(inputfile,ios::binary);
	ifile.seekg(40,ios::beg);
	ifile >> Dimension;
	ifile.seekg(1,ios::cur);
	ifile.read(nii_x,2);
	ifile.read(nii_y,2);
	ifile.read(nii_z,2);
	DimX = (unsigned char)nii_x[0];
	DimY = (unsigned char)nii_y[0];
	DimZ = (unsigned char)nii_z[0];

	unsigned int FileSize = DimX * DimY * DimZ * 2;
	ifile.seekg(0x160,ios::beg);

	unsigned int iSize = DimX * DimY * 2;
//	char* tempBuffer = new char(iSize);
	for(int i = 0; i < DimZ; i++)
	{
		ifile.read(tempBuffer,iSize);
		memcpy((char*)pOriginData + (i * iSize),(char*)tempBuffer,iSize);
	}
//	ifile.read(pOriginData,FileSize);


	twochar twch;
	unsigned int itemp = 0;
	unsigned short stemp = 0;
	for(int k = 0;k < FileSize;k += 2)
	{
		twch.c[0] = pOriginData[k];
		twch.c[1] = pOriginData[k + 1];
		stemp = twch.s;
		double dtemp;
		if(stemp < 100)
		{
			stemp = 0;
		}
		else if(stemp > 1000)
		{
			stemp = 255;
		}
		else
		{
			stemp = stemp * 0.25;
		}
		pBitmapData[itemp++] = stemp;
	}
	ifile.close();
//	delete[] tempBuffer;
	return pOriginData;
}