/*!	\file
	\brief Test class will be generated unhandled exception (to crash application)
*/

#include "test.h"

TEST::TEST(QObject *parent):
	QObject(parent)
{}

void TEST::test_crash(QString str)
{
	auto crash = []()
	{
		volatile int* a = (int*) (NULL);
		*a = 1;
	};

	if (str == QString("crash"))
		crash();
}
