#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "avion.h"
#include <QMainWindow>
#include <QtWidgets>
#include "smtp.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "arduino.h"

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

   void on_pushboutton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();


    void on_pushbutton_modifier1_clicked();



    void on_pushButton_login_clicked();

    void on_pushButton_quitter_clicked();

    void on_pushButton_suivant_mail_clicked();

    void on_pushButton_suivant_chat_clicked();

    void on_pushButton_prec_ajout_clicked();

    void on_pushButton_prec_mail_clicked();


    void on_pushButton_ordre_desc_clicked();

    void on_pushButton_ordre_asc_clicked();


    void on_recherchebutton_textChanged(const QString &arg1);

    void on_pushButton_prec_login_3_clicked();

    void on_pdf_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();


    void on_pushButton_GESTION_AVION_clicked();

     void update_label();

private:
    Ui::MainWindow *ui;
    AVION A;
    QStringList files;
    QByteArray data; // variable contenant les données reçues

    Arduino Ar; // objet temporaire
};
#endif // MAINWINDOW_H
