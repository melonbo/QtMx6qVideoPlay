/*
 * CDecThread.h
 *
 *  Created on: 2016年12月28日
 *      Author: hbs
 */

#ifndef CDECTHREAD_H_
#define CDECTHREAD_H_

#include <Qt/qthread.h>
#include <decode_stream.h>
class CDecThread: public QThread {
	Q_OBJECT
public:
	CDecThread(int index,QObject *parent = 0);
	virtual ~CDecThread();
protected:
	virtual void run();
private:
	DecContxt decContxt;
	FILE* fin;
    static void YuvDataCallBack(const unsigned char *pPacketBuffer, int nPacketSize,int width,int height,
    		unsigned long uiPara) ;
    static int  H264ReadDataCallBack( unsigned char *pPacketBuffer, size_t nBufSize,	unsigned long uiPara) ;
signals:
	void SignalYuvNotify(const unsigned char *, int,int,int,int);
};

#endif /* CDECTHREAD_H_ */
