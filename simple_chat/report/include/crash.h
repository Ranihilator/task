#pragma once

#include "ui_crash.h"

class Crash : public QWidget
{
	Q_OBJECT

public:
	Crash();

	void Set_Damp_Path(const QString path);
	void Set_Call_Stack_Path(const QString path);

private slots:
	void SaveAs(bool);

private:
	Ui::Crash widget;
};