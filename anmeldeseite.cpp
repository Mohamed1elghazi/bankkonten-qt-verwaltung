#include "anmeldeseite.h"
#include "ui_anmeldeseite.h"

Anmeldeseite::Anmeldeseite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Anmeldeseite)
{
    ui->setupUi(this);

}

Anmeldeseite::~Anmeldeseite()
{
    delete ui;
}

void Anmeldeseite::on_Anmeldeseite_accepted()
{
}


void Anmeldeseite::on_Anmeldeseite_rejected()
{

}


void Anmeldeseite::data_changed()
{

}

void Anmeldeseite::on_Anmeldeseite_destroyed()
{

}

void Anmeldeseite::on_anmelden_released()
{
    QString password = QString("%1").arg(QString(QCryptographicHash::hash(ui->passwort->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    kenn_var=ui->kennnumer->text();
    emit sende_anmelde_daten( kenn_var, password);
}







