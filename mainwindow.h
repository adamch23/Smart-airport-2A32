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

   void on_pushboutton_ajouteravion_clicked();

    void on_pushButton_supprimeravion_clicked();


    void on_pushbutton_modifier1avion_clicked();





    void on_pushButton_quitter_clicked();

    void on_pushButton_suivant_mailavion_clicked();

    void on_pushButton_suivant_chat_clicked();

    void on_pushButton_prec_ajoutavion_clicked();

    void on_pushButton_prec_mail_clicked();


    void on_pushButton_ordre_descavion_clicked();

    void on_pushButton_ordre_ascavion_clicked();


    void on_recherchebuttonavion_textChanged(const QString &arg1);

    void on_pushButton_prec_login_3_clicked();

    void on_pdfavion_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();


    void on_pushButton_GESTION_AVION_clicked();

     void update_label();

     void on_sendBtn_clicked();

     void on_browseBtn_clicked();

private:
    Ui::MainWindow *ui;
    AVION A;
    QStringList files;
    QByteArray data; // variable contenant les données reçues

    Arduino Ar; // objet temporaire
};
#endif // MAINWINDOW_H
