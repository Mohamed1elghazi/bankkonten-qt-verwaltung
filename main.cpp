#include "mainwindow.h"
#include "multilist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

//    MultiList *multiList = new MultiList();

//    multiList->addItems(QStringList() << "One" << "Two" << "Three" << "Four");
//    multiList->setCheckedItems(QStringList() << "One" << "Two");

//    QHBoxLayout *layout = new QHBoxLayout();

//    layout->addWidget(new QLabel("Select items:"));
//    layout->addWidget(multiList, 1);

//    QWidget widget;
//    widget.setWindowTitle("MultiList example");
//    widget.setLayout(layout);
//    widget.show();


    return a.exec();
}
