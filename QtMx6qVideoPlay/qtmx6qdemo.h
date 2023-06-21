#ifndef QTMX6QDEMO_H
#define QTMX6QDEMO_H

#include <QtGui/QWidget>
#include "ui_qtmx6qdemo.h"

class QtMx6qDemo: public QWidget {
Q_OBJECT

public:
	QtMx6qDemo(QWidget *parent = 0);
	~QtMx6qDemo();
	void paintEvent(QPaintEvent*);

public slots:


	void YuvDataNotify(const unsigned char *yuvBuffer, int nPacketSize,int swidth,int sheight,
			int index);
	void TimeOut();
private:
	Ui::QtMx6qDemoClass ui;
	typedef enum {
		FLOOR_UP, FLOOR_DOWN
	} enmFloorStatus;
	;

	QTimer *m_maintimer;
	QPixmap m_canvasPix;
};

#endif // QTMX6QDEMO_H
