#include "qtmx6qdemo.h"
#include <QPainter>
#include <QDateTime>
#include <QTimer>
#include <QWidget>
#include <stdio.h>
#include <CDecThread.h>
#include<QRect>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/mxcfb.h>
#include <linux/ipu.h>
#include<yuv2rgb.h>

QtMx6qDemo::QtMx6qDemo(QWidget *parent) :
		QWidget(parent) {
	ui.setupUi(this);
	m_maintimer = new QTimer();
	//m_backgroundpix.load("images/bkd4.jpg");//background.png");
	//m_logo.load("images/logo.png");

	//m_floortoup.load("images/up.png");
	//m_floortodown.load("images/down.png");

	setGeometry(0, 0, 800, 600);
	m_canvasPix = QPixmap(width(), height());
	//sleep(50);
	//m_gstreamer.AutoPlayListRun(false);
	m_maintimer->start(1000);

	//connect(this, SIGNAL(SignalCommNotify(int)), this,
	//				SLOT(CommNotify(int)));
	CDecThread *thread[4];
	for (int i = 0; i < 4; i++) {
		thread[i] = new CDecThread(i, this);
		connect(thread[i],
				SIGNAL(SignalYuvNotify(const unsigned char *, int,int,int,int)), this,
				SLOT(YuvDataNotify(const unsigned char *, int,int,int,int )));
		thread[i]->start();
	}

}

QtMx6qDemo::~QtMx6qDemo() {
}
void QtMx6qDemo::TimeOut() {
	//printf("QtMx6qDemo::TimeOut\n");
}

void QtMx6qDemo::YuvDataNotify(const unsigned char *yuvBuffer, int nPacketSize,int swidth,int sheight,
		int index) {
	printf("YuvDataNotify nPacketSize:%d swidth:%d sheight:%d index:%d\n ", nPacketSize, swidth,sheight,index);
	unsigned char rgbBuffer[swidth * sheight * 4];

	int w = m_canvasPix.width();
	int h = m_canvasPix.height();
	QPainter basep(&m_canvasPix);
	QRectF targetRect;
	switch (index) {
	case 0: {
		QRectF targetRecttmp(0, 0, w / 2, h / 2);
		targetRect = targetRecttmp;
	}
		break;
	case 1: {
		QRectF targetRecttmp(w / 2, 0, w / 2, h / 2);
		targetRect = targetRecttmp;
	}
		break;
	case 2: {
		QRectF targetRecttmp(0, h / 2, w / 2, h / 2);
		targetRect = targetRecttmp;
	}
		break;
	case 3: {
		QRectF targetRecttmp(w / 2, h / 2, w / 2, h / 2);
		targetRect = targetRecttmp;
	}
		break;
	default:
		return;
	}
	int sizes = ipu_yuv420p_to_rgb24(yuvBuffer, rgbBuffer, swidth, sheight, targetRect.width(), targetRect.height());
	int objw = targetRect.toRect().width();
	int objh = targetRect.toRect().height();
	QImage tmpImg((uchar *) rgbBuffer, objw, objh, QImage::Format_RGB888);
	basep.drawImage(targetRect, tmpImg);
	repaint(targetRect.toRect());
}
void QtMx6qDemo::paintEvent(QPaintEvent*) {

	QPainter painter(this);
	painter.drawPixmap(0, 0, m_canvasPix);
}

