#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include "qsqldatabase.h"
#include "qstringlist.h"
#include <QTreeWidget>
#include <QSqlQuery>
#include <QTreeWidgetItem>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <stdlib.h>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QDate>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QScrollArea>
#include <QLineEdit>
#include <anmeldeseite.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlRelationalTableModel *neu_tab_erstellen(QTreeWidgetItem *item, int column);
    void stack_widgets_erstellen(QSqlRelationalTableModel *model);
public slots:
    void tree_tab_DoubleClicked(QTreeWidgetItem *item, int column);
    void search_filter_changed(QString filter);
    void closetab(int index);
    void table_data_changed();
    void columnBox_stateChanged();
    void get_zugangsdaten(QString kennnummer, QString passwort);
    void add_edit_changed();
    void tab_table_index_changed(int index);

    void selection_table_changed(const QItemSelection &selected, const QItemSelection &deselected);


private slots:
    void on_submit_clicked();
    void on_revert_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
public:
    QSqlDatabase  db;
    QList <QString> list_tables;
    QList <QTableView*> Table_views;
    QList <QString> open_tables;
    QList <QSqlRelationalTableModel*> models_list;
    QList <QLineEdit*> list_fieldname_add;
    Anmeldeseite*  anmeldeseite  ;
    int  clicked_index{0}  ;
    int  models_list_count{-1};
    bool  not_currenttab_clicked{false}  ;
    bool  not_currenttab_clicked_2{true}  ;
};
#endif // MAINWINDOW_H
