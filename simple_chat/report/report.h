#pragma once

#include <QWidget>

namespace Ui
{
	class report;
}

class report : public QWidget
{
	Q_OBJECT

public:
	explicit report(QWidget *parent = 0);
	~report();

	void Set_Damp_Path(const QString path);
	void Set_Call_Stack_Path(const QString path);

private slots:
	void SaveAs(bool);

private:
	Ui::report *ui;
};
