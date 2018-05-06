/*!	\file
	\brief Test class Header (for crash class)
*/

#pragma once

#include <QObject>
#include <QString>

#include "client/linux/handler/exception_handler.h"

class TEST : public QObject
{
	Q_OBJECT

public:
	TEST(QObject *parent = 0);

public slots:

	/*!
	\brief slots that receive signal from qml engine

	\details qml engine sending the signal from chat input.
	Method is checked the message. If message have word `crash` method will throw unhandled exception by call lambda function with crash code

	\param[in] str string from chat input
	\return process code
	*/
	void test_crash(QString str);
};