/*
 * CDecThread.cpp
 *
 *  Created on: 2016年12月28日
 *      Author: hbs
 */

#include <CDecThread.h>
#include <stdio.h>
#include<bmp_utils.h>
#include<yuv2rgb.h>
 #include <stdlib.h>

#define DEFAULT_FILL_DATA_UNIT	(16*1024)
#define DEFAULT_DELAY_BUFSIZE		(-1)

CDecThread::CDecThread(int index,QObject *parent ) :
		QThread(parent) {
	memset(&decContxt, 0, sizeof(DecContxt));
	fin =  fopen("/home/stream.h264", "rb");
	decContxt.foutcallback = YuvDataCallBack;
	decContxt.fincallback = H264ReadDataCallBack;
	decContxt.index = index;
	decContxt.uiPara = (unsigned long) this;
	//decContxt.fout= fopen("hbs.yuv", "wb");;;
	decContxt.nMaxNum = 0x7FFFFFFF; //无用
	decContxt.nDisplay = 0; //无用
	decContxt.nFbNo = 0; //无用
	decContxt.nCodec = 8; //h.264
	//decContxt.nInWidth=ioParams.width;
	//decContxt.nInHeight=ioParams.height;
	decContxt.nSkipMode = 0;	//不skip
	decContxt.nDelayBufSize = -1;	//DEFAULT_DELAY_BUFSIZE;
	//decContxt.nRepeatNum=0xfff;
	decContxt.nOffset = 0;
	decContxt.nUnitDataSize = DEFAULT_FILL_DATA_UNIT;
	decContxt.nUintDataNum = 0x7FFFFFFF;
	decContxt.nChromaInterleave = 0;//yuv chroma interleave: 0(default)--no interleave; 1--interleave
	decContxt.nMapType = 0;	//register frame type: 0(default)--linear ; 1--frame tile ; 2--field tile
	decContxt.nTile2LinearEnable = 0;
}

CDecThread::~CDecThread() {
	// TODO Auto-generated destructor stub
}
void CDecThread::run() {

	decode_stream (&decContxt);
	qDebug(
			"Frame Num: %d,  [width x height] = [%d x %d], dec FPS: %d, total FPS: %d \r\n",
			decContxt.nFrameNum, decContxt.nWidth, decContxt.nHeight,
			decContxt.nDecFps, decContxt.nTotalFps);
	if (decContxt.nErr) {
		qDebug("Decode Failure \r\n");
	} else {
		//qDebug("Decode OK: repeat %d times, skip mode: %d \r\n",ioParams.repeatnum,ioParams.skipmode);
	}
}

void CDecThread::YuvDataCallBack(const unsigned char *pPacketBuffer,
		int nPacketSize, int width,int height,unsigned long uiPara) {

	CDecThread *pthread = (CDecThread *)uiPara;
	//
//#error 	“必须封装成库，要不断优化让画面连续，现在画面有点卡”
   //if (  pthread->decContxt.index >= 1 ){
//	   return ;
   //}
	//int sizes = yuv420p_to_rgb24(pPacketBuffer,pthread->m_rgbbuf,720,576);
	//printf("YuvDataCallBack %d\n", nPacketSize);
	emit pthread->SignalYuvNotify(pPacketBuffer, nPacketSize, width,height,pthread->decContxt.index);
	usleep(20*1000);
	//write_bmp_file("a.bmp",pthread->m_rgbbuf,720,576);
   //::exit(0);
}
int  CDecThread::H264ReadDataCallBack( unsigned char *pPacketBuffer, size_t nBufSize,	unsigned long uiPara)
{
	CDecThread *pCDecThread = (CDecThread *)uiPara;
	int readbytes;
	//static int totalReadSize=0;
	////DEC_STREAM_PRINTF("read %d bytes \r\n",length);
	readbytes=fread(pPacketBuffer,1,nBufSize,pCDecThread->fin);
	//totalReadSize+=readbytes;
	//printf("total read size: %d \r\n",totalReadSize);
	return readbytes;
}
