#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

long        IWidth;      
long        IHeight;     
long        biBitCount;    
long        INewWidth;   
long        INewHeight;  
long		ILineByte;  
long        INewLineByte;   
int         zoomnumberinput=100;    
float       zoomnumber;
unsigned char *pIBuf;   
unsigned char *pINewBuf;



int LoadBmp(const char* bmpName)
{
	FILE *fp=fopen(bmpName,"rb");
	if(fp==0)
	{ 
		printf("打开文件失败\n");
		return 0;
	}

	fseek(fp,sizeof(BITMAPFILEHEADER),0);
	BITMAPINFOHEADER head;
	fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
	IWidth=head.biWidth;
	IHeight=head.biHeight;
	biBitCount=head.biBitCount;
	ILineByte=(IWidth*biBitCount/8+3)/4*4;
    pIBuf=(unsigned char*)malloc(sizeof(unsigned char)*ILineByte*IHeight);
	fread(pIBuf,1,ILineByte *IHeight,fp);
	return 1;
}

int SaveBmp(const char* bmpName,unsigned char *imgBuf,int width,int height,int biBitCount)
{
	if(!imgBuf){
	    return 0;
	}
	INewLineByte=(width*biBitCount/8+3)/4*4;
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0){ 
		return 0;
	}
	BITMAPFILEHEADER fileHead;
	fileHead.bfType=0x4d42;
	fileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+INewLineByte*height;
	fileHead.bfReserved1=0;
	fileHead.bfReserved2=0;
	fileHead.bfOffBits=54;
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	BITMAPINFOHEADER head;
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=ILineByte *height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	fwrite(&head,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(imgBuf,height*INewLineByte,1,fp);
	fclose(fp);
	return 1;
}

int Zoom(const char* bmpName,const char* address)
{
    LoadBmp(bmpName);
	INewWidth=(int)((IWidth*zoomnumber)+0.5);
	INewHeight=(int)(IHeight*zoomnumber+0.5);
	ILineByte=(IWidth*biBitCount/8+3)/4*4;
	INewLineByte=(INewWidth*biBitCount/8+3)/4*4;
    pINewBuf=(unsigned char*)malloc(sizeof(unsigned char)*INewLineByte*INewHeight);

	long i;     
	long j;
	long k;	     
	long i0;	  
	long j0;
	

	for(i=0;i<INewHeight;i++)
   {
	    for(j=0;j<INewWidth;j++)
	   {
		    for(k=0;k<3;k++)  
		   {  
			i0=(int)i/zoomnumber; 
			j0=(int)j/zoomnumber;
			int i1=(int)i0;
			int i2=i1+1;
			int j1=(int)j0;
			int j2=j1+1;
			double fx1=i0-i1;
			double fx2=1.0-fx1;
			double fy1=j0-j1;
			double fy2=1.0-fy1;
			double s1=fx1*fy1;
			double s2=(1.0-fx1)*fy1;
			double s3=(1.0-fx1)*(1.0-fy1);
			double s4=fx1*(1.0-fy1);

			if((j0>=0)&&(j0<IWidth-1)&&(i0>=0)&&(i0<IHeight-1))
		   {
			*(pINewBuf+i*INewLineByte+j*3+k) =*(pIBuf+i2*ILineByte+j2*3+k)*s1
											 +*(pIBuf+i1*ILineByte+j2*3+k)*s2
											 +*(pIBuf+i1*ILineByte+j1*3+k)*s3
											 +*(pIBuf+i2*ILineByte+j1*3+k)*s4;
		   }else{
				  *(pINewBuf+i*INewLineByte+j*3+k)=255;
		   }
		}
	}
}

    SaveBmp(address,pINewBuf,INewWidth,INewHeight,biBitCount);
	free(pINewBuf);
	return 1;
}

int main(int argc,char** argv){
    zoomnumberinput=atoi(argv[2]);
    zoomnumber=zoomnumberinput*1.0/100.0;
    Zoom(argv[1],argv[3]); 
    return 0; 	
}


