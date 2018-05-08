#include "report.h"
#include "ui_report.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>

report::report(QWidget *parent):
	QWidget(parent), ui(new Ui::report)
{
	ui->setupUi(this);

	QObject::connect(this->ui->SaveDump, SIGNAL(clicked(bool)), this, SLOT(SaveAs(bool)));
}

void report::Set_Damp_Path(const QString path)
{
	QFileInfo info(path);

	this->ui->PathDump->insert(info.absoluteFilePath());
}

void report::Set_Call_Stack_Path(const QString path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	if (!file.isOpen())
	return;

	QTextStream message(&file);

	while (!message.atEnd())
		this->ui->CallStack->append(message.readLine());
}

void report::SaveAs(bool)
{
	QFileDialog dialog(this);

	auto new_file = dialog.getSaveFileName(this, "Save dump", "", ".dmp");

	if (new_file.isEmpty())
		return;

	auto old_file = this->ui->PathDump->text();

	if (old_file.isEmpty())
		return;

	if (new_file == old_file)
		return;

	QFile::copy(old_file, new_file);
	this->ui->PathDump->clear();
	this->ui->PathDump->insert(new_file);
}

report::~report()
{
	delete ui;
}
