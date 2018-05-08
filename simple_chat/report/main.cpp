#include "report.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if (app.arguments().size() != 3)
		return -1;

	report w;

	w.Set_Damp_Path(app.arguments().at(1));
	w.Set_Call_Stack_Path(app.arguments().at(2));

	w.show();

	return app.exec();
}
