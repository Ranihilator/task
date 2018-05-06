/*!	\file
	\brief GUI class with qml engine will load qml script
*/

#include "gui.h"

GUI::GUI(QObject *parent) :
	QObject(parent)
{
	this->engine.rootContext()->setContextProperty("GUI", this);

	QQmlComponent* component = new QQmlComponent(&this->engine, QUrl(QStringLiteral("qrc:/main.qml")));
	QObject* mainview = component->create();

	QObject::connect(mainview, SIGNAL(test_crash(QString)), this, SIGNAL(test_crash(QString)));
}