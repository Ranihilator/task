/*!	\file
	\brief Simple chat application

	Simple chat and sample of unhandled exception capture and qml ui
*/

#include <QApplication>

#include <iostream>
#include <fstream>
#include <boost/stacktrace.hpp>

#include "defines.h"
#include "gui.h"
#include "test.h"

/// namespace of unhandled exception
namespace App_Crash
{
	using std::cout;
	using std::endl;
	using std::ofstream;

	using google_breakpad::MinidumpDescriptor;
	using google_breakpad::ExceptionHandler;

	/*!
	\brief callback of unhandled exception 

	\details unhandled exception will save dump, call stack in file and will execute report form from external application

	\param[in] descriptor describing how a crash dump 
	\return result
	*/
	static bool dumpCallback(const MinidumpDescriptor& descriptor, void*, bool)
	{
		ofstream ifs(CALL_STACK_PATH);

		ifs << endl;

		ifs << boost::stacktrace::stacktrace();

		ifs.close();

		cout << "Dump path: " << descriptor.path() << endl;
		cout << "Call Stack path: " << CALL_STACK_PATH << endl;

		return execl(APP_CRASH_REPORT, APP_CRASH_REPORT, descriptor.path(), CALL_STACK_PATH, nullptr);
	}

	MinidumpDescriptor descriptor(DUMP_PATH);
	ExceptionHandler eh(descriptor, NULL, dumpCallback, NULL, true, -1);
}

/*!
\brief Start program

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	GUI gui;
	TEST test;

	QObject::connect(&gui, SIGNAL(test_crash(QString)), &test, SLOT(test_crash(QString)));

	return app.exec();
}