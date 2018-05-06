#include <QApplication>
#include <QWidget>

#include "crash.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if (app.arguments().size() != 3)
		return -1;

	Crash crash;

	crash.Set_Damp_Path(app.arguments().at(1));
	crash.Set_Call_Stack_Path(app.arguments().at(2));
	crash.show();

	return app.exec();
}