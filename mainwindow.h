#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "avion.h"
#include <QMainWindow>
#include <QtWidgets>
#include "mail.h"
#include"envoi_mail.h"
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

    void on_pushButton_confirmer_mail_clicked();

    void on_pushButton_prec_compte_mail_clicked();

    void on_pushButton_envoyer_mail_clicked();

   // void on_pushButton_rechercher_mail_clicked();

    void on_pushButton_ordre_desc_clicked();

    void on_pushButton_ordre_asc_clicked();


    void on_recherchebutton_textChanged(const QString &arg1);

    void on_pushButton_prec_login_3_clicked();

private:
    Ui::MainWindow *ui;
    AVION A;
    mail M;
    envoi_mail EM;
};
#endif // MAINWINDOW_H
