#include "crash.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>

Crash::Crash()
{
	this->widget.setupUi(this);

	QObject::connect(this->widget.SaveAs, SIGNAL(clicked(bool)), this, SLOT(SaveAs(bool)));

}

void Crash::Set_Damp_Path(const QString path)
{
	QFileInfo info(path);

	this->widget.DumpFile->insert(info.absoluteFilePath());
}

void Crash::Set_Call_Stack_Path(const QString path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	if (!file.isOpen())
		return;

	QTextStream message(&file);

	while (!message.atEnd())
	{
		this->widget.Call_Stack->append(message.readLine());
	}
}

void Crash::SaveAs(bool)
{
	QFileDialog dialog(this);

	auto new_file = dialog.getSaveFileName(this, "Save dump", "", ".dmp");

	if (new_file.isEmpty())
		return;

	auto old_file = this->widget.DumpFile->text();

	if (old_file.isEmpty())
		return;

	if (new_file == old_file)
		return;

	QFile::copy(old_file, new_file);
	this->widget.DumpFile->clear();
	this->widget.DumpFile->insert(new_file);
}