/********************************************************************************
** Form generated from reading UI file 'Crash.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRASH_H
#define UI_CRASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Crash
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QTextEdit *Call_Stack;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *DumpFile;
    QPushButton *SaveAs;

    void setupUi(QWidget *Crash)
    {
        if (Crash->objectName().isEmpty())
            Crash->setObjectName(QStringLiteral("Crash"));
        Crash->resize(932, 418);
        gridLayout_2 = new QGridLayout(Crash);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Crash);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(Crash);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        Call_Stack = new QTextEdit(Crash);
        Call_Stack->setObjectName(QStringLiteral("Call_Stack"));
        Call_Stack->setReadOnly(true);

        verticalLayout->addWidget(Call_Stack);

        label_3 = new QLabel(Crash);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        DumpFile = new QLineEdit(Crash);
        DumpFile->setObjectName(QStringLiteral("DumpFile"));

        horizontalLayout->addWidget(DumpFile);

        SaveAs = new QPushButton(Crash);
        SaveAs->setObjectName(QStringLiteral("SaveAs"));
        SaveAs->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SaveAs->sizePolicy().hasHeightForWidth());
        SaveAs->setSizePolicy(sizePolicy);
        SaveAs->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(SaveAs);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Crash);

        QMetaObject::connectSlotsByName(Crash);
    } // setupUi

    void retranslateUi(QWidget *Crash)
    {
        Crash->setWindowTitle(QApplication::translate("Crash", "Crash", Q_NULLPTR));
        label->setText(QApplication::translate("Crash", "Simple_Chat Test Crash", Q_NULLPTR));
        label_2->setText(QApplication::translate("Crash", "Call STack:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Crash", "Dump", Q_NULLPTR));
        SaveAs->setText(QApplication::translate("Crash", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Crash: public Ui_Crash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRASH_H
