/*!	\file
	\brief GUI Header
*/

#pragma once

#include <QObject>
#include <QtQml>

class GUI : public QObject
{
	Q_OBJECT

public:
	GUI(QObject *parent = 0);
private:
	QQmlApplicationEngine engine;
public slots:
signals:

	/*!
	\brief signal sending from qml engine, if user send message to chat

	\param[in] str string from chat input
	\return process code
	*/
	void test_crash(QString);
};
