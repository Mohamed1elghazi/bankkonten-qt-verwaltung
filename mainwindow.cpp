#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLatin1String>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    anmeldeseite=new Anmeldeseite();
    anmeldeseite->open ();
    this->connect(anmeldeseite,&Anmeldeseite::sende_anmelde_daten,this,&MainWindow::get_zugangsdaten);

    ui->tabWidget->clear ();
    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("6360");
    db.setPort(3307);
    db.setDatabaseName("bankkonten");
    if (db.open()){
        QSqlQuery q;
        q.exec( " show tables" );
        while(q.next())                // save the name of the  table to shw them on the tree
            list_tables.append (QString(q.value(0).toString()));
        this->connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::closetab); // close sig slot
        this->connect(ui->treeWidget,&QTreeWidget::itemDoubleClicked,this,&MainWindow::tree_tab_DoubleClicked); // open table slot
        this->connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::tab_table_index_changed); // close sig slot
        for (int t = 0; t < list_tables.count(); ++t)    // add tree elements(list of fieldnames )
        {
            QTreeWidgetItem *items = new QTreeWidgetItem(ui->treeWidget);
            items ->setText(0,list_tables.at(t));
        }
        QWidget* widget_1 = new QWidget(ui->stackedWidget);   // WIDGET FÜR columns_edit VORBEREITEN // container for the fieldnames of tables
        QVBoxLayout *layout_1 = new QVBoxLayout();             // layout for the fieldnames
        widget_1->setLayout(layout_1);
        layout_1->setAlignment (Qt::AlignTop);
        ui->stackedWidget->addWidget (widget_1);
        QWidget* widget_2 = new QWidget();
        QVBoxLayout *layout_2 = new QVBoxLayout();
        widget_2->setLayout(layout_2);
        layout_2->setAlignment (Qt::AlignTop);
        ui->stackedWidget->addWidget (widget_2);
        QWidget* widget_3 = new QWidget();
        QVBoxLayout *layout_3 = new QVBoxLayout();
        widget_3->setLayout(layout_3);
        layout_3->setAlignment (Qt::AlignTop);
        ui->stackedWidget->addWidget (widget_3);
        qDebug()<<"connection succeded";
    }
    else
    {
        qDebug()<<"connection failed";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::selection_table_changed(const QItemSelection &selected, const QItemSelection &deselected)
{
//    bool QAbstractItemModel::removeColumn(int selected., const QModelIndex &parent = QModelIndex())
}


void MainWindow::columnBox_stateChanged()    // hide columns of a table
{
    QCheckBox * buttonSender = qobject_cast<QCheckBox *>(sender()); // retrieve the button you have clicked
    QString buttonText = buttonSender->text();            // retrive the text from the button clicked
    auto index=ui->tabWidget->currentIndex ();            //
    auto fieldname_index =models_list.at(index)->fieldIndex(buttonText);
    if(buttonSender->isChecked ())
    {
        Table_views.at(index)->hideColumn (fieldname_index);                                                 // hide the cul with the numb
        models_list.at(index)->select();                                                                      // refresh
    }
    else
    {
        Table_views.at(index)->setColumnHidden(fieldname_index, false);
    }
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index==0)
    {
        ui->stackedWidget->setCurrentIndex (index);            // switch to next
    }
    else if (index==1)
    {
        ui->stackedWidget->setCurrentIndex (index);

    }
    else if (index==2)
    {
        ui->stackedWidget->setCurrentIndex (index);
    }
    else
    {

    }
}

void MainWindow::on_submit_clicked()
{
    models_list.at (ui->tabWidget->currentIndex ())->submitAll ();
    ui->revert->setEnabled (false);
    ui->submit->setEnabled (false);
    models_list.at (ui->tabWidget->currentIndex ())->select ();
}

void MainWindow::on_revert_clicked()
{
    if (ui->tabWidget->currentIndex ())
    {
        models_list.at (ui->tabWidget->currentIndex ())->revertAll ();
    }
    ui->revert->setEnabled (false);
    ui->submit->setEnabled (false);
}

void MainWindow::table_data_changed()
{
    ui->revert->setEnabled (true);
    ui->submit->setEnabled (true);
}

void MainWindow::closetab(int index)
{
    ui->tabWidget->removeTab(index);
    ui->comboBox->setCurrentIndex (0);
    //    ui->stackedWidget->setCurrentIndex (0);
    open_tables.removeAt (index);
    models_list.removeAt (index);                                   // no need to reset the pointer to the model
    Table_views.removeAt (index);                                   // no need to reset the pointer to the model

    list_fieldname_add.clear();
    auto model= models_list.at(ui->tabWidget->currentIndex ());     // the closed one can be any tab mussnt be the opened one
    stack_widgets_erstellen (model);
}



//void MainWindow::search_filter_chancged(QString filter)
//{
//    QSqlRelationalTableModel* model= models_list.at(ui->tabWidget->currentIndex ());
//    if (filter!=""){
//        QLineEdit * buttonSender = qobject_cast<QLineEdit*>(sender());
//        model->setFilter (buttonSender->objectName ()+filter);
//        model->select ();
//    }
//    else                             // if the filter == ""
//    {
//        model->setFilter ("");       // unset filter
//        model->select ();            // refrech
//    }
//}



void MainWindow::get_zugangsdaten(QString  kennnummer, QString passwort)
{

        anmeldeseite->accept();
        anmeldeseite->close();
        this->show();
}

void MainWindow::add_edit_changed()
{

    auto index=ui->tabWidget->currentIndex ();          // tab index to access to model of the table
    QSqlRelationalTableModel*  model = models_list.at (index);
    QSqlRecord record = model->record();                // the record that point to the model items or fields
    auto var_2 = model->record ().count ();           // anzahl an feldnamen
    qDebug()<<"index"<<index;
    qDebug()<<"var_2"<<var_2;
    for (int var = 0; var < var_2; ++var)
    {

        qDebug()<<"_______________"<<var_2;
        qDebug()<<"list_fieldname_add.at (var)->count"<<list_fieldname_add.count();
        qDebug()<<"list_fieldname_add.at (var)->text()  "<<list_fieldname_add.at (var)->text()<<var_2;
        record.setValue (var,list_fieldname_add.at (var)->text());
        // name of field                   // values that should be added into the field
    }
    if(model->insertRecord(-1, record)){
        qDebug()<<"successful insertion";
        model->submitAll();
    }
    else
    {
        qDebug()<<"insertion failed ";

    }
    models_list.at(ui->tabWidget->currentIndex ())->select();                                             // hide the cul with the numb
}











QSqlRelationalTableModel* MainWindow::neu_tab_erstellen(QTreeWidgetItem *item,int column)   // item from the tree to get the name
{
    QWidget *widget= new QWidget(ui->tabWidget->tabBar ());                             // widget to put in the tab
    auto index=ui->tabWidget->addTab(widget,item->text (column));  // add tab and put widget with a layout inside of it
    widget->setObjectName (item->text (column));                // set name of widgets
    QHBoxLayout *layout = new QHBoxLayout(widget);              // layout for the buttons right
    widget->setLayout (layout);
    QTableView *Table_view= new QTableView;                              // table view for tab
    Table_view->setAlternatingRowColors (true);
//    Table_view->setEditTriggers(QAbstractItemView::EditKeyPressed);
    Table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
//    Table_view->selectionMode();

//    this->connect(ui->tabWidget,&Table_view::selectionChanged,this,&MainWindow::selection_table_changed); // close sig slot;


    QSqlRelationalTableModel* model=new QSqlRelationalTableModel(widget,db);    // create tabel_model for data
    models_list.append (model);          /*!!!!!!!!!!!!*/                // save model or data in a list
    Table_views.append (Table_view);                                 //
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model); // create proxy
    Table_view->setSortingEnabled(true);                                 // enable sortingEnabled
    proxyModel->setSourceModel(model);                                    // sort
    Table_view->setObjectName (item->text (column));                 //
    Table_view->setModel(model);                                     // show the model on the view
    layout->addWidget (Table_view);                                  // put the data in the layout and show it
    ui->tabWidget->setCurrentIndex(index);                           // jump to the tab
    ui->tabWidget->setStyleSheet("QTabBar::tab {min-width: 150px;max-width: 400px;}");
    model->setObjectName (item->text (column));
    this->connect(model,&QSqlRelationalTableModel::dataChanged,this,&MainWindow::table_data_changed);
    model->setTable(item->text (column));                                // set the table name
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);             // when submit clicked data submitted
    model->select();
    return model;
}

void MainWindow::stack_widgets_erstellen(QSqlRelationalTableModel* model)
{

    qDeleteAll(ui->stackedWidget->findChildren<QLabel*>());
    qDeleteAll(ui->stackedWidget->findChildren<QLineEdit*>());
    qDeleteAll(ui->stackedWidget->findChildren<QCheckBox *>());
    qDeleteAll(ui->stackedWidget->findChildren<QPushButton *>());
    list_fieldname_add.clear ();
    for (int var = 0; var < model->record ().count (); ++var)        //
    {
        QCheckBox *c =new QCheckBox();                      // create checkbox for every fieldname in the table
        c->setText (model->record ().fieldName (var));            // set name of checkbox to fieldname
        ui->stackedWidget->widget (0)->layout ()->addWidget (c);
        this->connect(c,&QCheckBox::released,this,&MainWindow::columnBox_stateChanged); // un/ check signal fieldnamen
    }

    auto var_2 = model->record ().count ();           // anzahl an feldnamen
    for (int var = 0; var <var_2 ; ++var)
    {
        QLineEdit * search_filter_Ledit =new QLineEdit(ui->stackedWidget);
        search_filter_Ledit->setObjectName (model->record().fieldName(var));
        this->connect(search_filter_Ledit,&QLineEdit::textEdited,this,&MainWindow::search_filter_changed); // close sig slot
        ui->stackedWidget->widget (1)->layout()->addWidget (new QLabel(model->record().fieldName(var)));
        ui->stackedWidget->widget (1)->layout()->addWidget (search_filter_Ledit);
    }

    for (int var = 0; var <var_2 ; ++var)
    {
        QLineEdit * search_filter_Ledit_1 =new QLineEdit();
        search_filter_Ledit_1->setObjectName (model->record().fieldName(var));
        ui->stackedWidget->widget (2)->layout()->addWidget (new QLabel(model->record().fieldName(var)));
        ui->stackedWidget->widget (2)->layout()->addWidget (search_filter_Ledit_1);
        list_fieldname_add.append(search_filter_Ledit_1);

    }
    QPushButton * button = new QPushButton("Daten hinzufügen");
    this->connect(button,&QPushButton::released,this,&MainWindow::add_edit_changed);
    ui->stackedWidget->widget (2)->layout()->addWidget (button);
}


void MainWindow::tree_tab_DoubleClicked(QTreeWidgetItem *item, int column)     // tree item clicked WITHOUTCHANGE
{
    if (!open_tables.contains(item->text (column)))                           // table not opened yet
    {
        open_tables.append (item->text (column));                            // list of open tables
        auto model=this->neu_tab_erstellen (item,column);                      // create neu tab
        this->stack_widgets_erstellen (model);
    }
    else                                                                             // table is opened
    {
        ui->tabWidget->setCurrentIndex (open_tables.indexOf(item->text (column)));  // select the tab clicked
    }
    ui->comboBox->setEnabled (true);
    ui->comboBox->setCurrentIndex (0);
    ui->stackedWidget->setCurrentIndex (0);
}



void MainWindow::tab_table_index_changed(int index)  // by onenning new tab this one get called or change tab by movable
{
    if (models_list_count!=models_list.count()) // new tab is opened
    {
        qDebug()<<"new tab opened ";
    }
    else
    {

        if (not_currenttab_clicked)                      //    not current tab_bar_clicked / clicked draged
        {

            if (not_currenttab_clicked_2)                // not current tab_bar_clicked but not draged
            {
                not_currenttab_clicked_2=false;
            }
            else                                         // not current tab_bar_clicked but not draged
            {
                open_tables.move (clicked_index,index);
                models_list.move (clicked_index,index);
                Table_views.move(clicked_index,index);
                clicked_index=index;
            }

        }
        else                                   // current clicked  and draged
        {
            open_tables.move (clicked_index,index);
            models_list.move (clicked_index,index);
            Table_views.move(clicked_index,index);
            clicked_index=index;
        }
    }
    for (int var = 0; var < open_tables.count (); ++var) {
        qDebug()<<open_tables.at (var);
    }

}



void MainWindow::on_tabWidget_tabBarClicked(int index)        // open normal this one doesnt get called
{
    if (index!=-1 and ui->tabWidget->currentIndex ()!=index)                       // NOT current tab clicked
    {
        ui->comboBox->setCurrentIndex (0);
        ui->stackedWidget->setCurrentIndex (0);
        stack_widgets_erstellen(models_list.at(index));          // new stackedwidget created
        auto anzahl_an_columns =models_list.at(index)->record ().count (); //
        for(int i=0; i<anzahl_an_columns ; i++)
        {
            Table_views.at(index)->setColumnHidden(i, false);
        }
        models_list.at(ui->tabWidget->currentIndex ())->select();
        not_currenttab_clicked=true;
        not_currenttab_clicked_2=true;
    }
    else                                                                            // current tab clicked
    {
        not_currenttab_clicked=false;
    }
    clicked_index=index;
    models_list_count=models_list.count();
    for (int var = 0; var < open_tables.count (); ++var) {
        qDebug()<<open_tables.at (var);
    }
}


























//move current tab              :: need move                     tabbarclicked(currentindex)->index_changed(index_1)->index_changed(index_2)->....

//                                                               clicked one                     new on swap with clicked

//current tabclicked      // dont do enything                    tabbarclicked(currentindex)->

//                                                               clicked on


//open a new tab          // dont do enything                                               ->index_changed(index_1)->

//                                                                                               dont do anything


//move not current              :: need move                     tabbarclicked(currentindex)->index_changed(index_1)->index_changed(index_2)->....

//                                                               clicked on                      new one swap with clicked



//not current tab_bar_clicked   :: dont need move                tabbarclicked(currentindex)->index_changed(index_1)

//                                                               clicked one                     dont do anything


//not current tab_bar_clicked   :: dont need move                tabbarclicked(currentindex)->index_changed(index_1)

//                                                               clicked one                     dont do anything
