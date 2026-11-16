#ifndef ANMELDESEITE_H
#define ANMELDESEITE_H

#include <QDialog>
#include <QString>
#include <QCryptographicHash>
#include <QByteArray>

namespace Ui {
class Anmeldeseite;
}

class Anmeldeseite : public QDialog
{
    Q_OBJECT

public:
    explicit Anmeldeseite(QWidget *parent = nullptr);
    ~Anmeldeseite();
signals:
    void show_mainwindow();
    void sende_anmelde_daten(QString kennnummer,QString  pasw_hashed);

private slots:
    void on_Anmeldeseite_accepted();
    void on_Anmeldeseite_rejected();
    void on_Anmeldeseite_destroyed();
    void on_anmelden_released();


public slots:
    void data_changed();
private:
    Ui::Anmeldeseite *ui;
public:
    QString  kenn_var;
    QString passwort_var;
};

#endif // ANMELDESEITE_H
