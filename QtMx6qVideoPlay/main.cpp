#include "qtmx6qdemo.h"

#include <QtGui>
#include <QApplication>

#include <QtGui>
#include <QApplication>
#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <locale.h>
#include <sys/wait.h>
#include <QApplication>
#include <QWSDisplay>
#include <QWindowsXPStyle>
#include <QTransformedScreen>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


int myargc = 3;
char *myargv[] = { "testqt", "-qws", "-display"};
int main(int , char *) {
	QApplication a(myargc, myargv);

	QtMx6qDemo w;
	w.show();
	return a.exec();
}
