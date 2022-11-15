#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avion.h"
#include "connection.h"
#include <string>
#include<QMessageBox>
#include <QIntValidator>
#include <QPixmap>
#include "QtWidgets"
#include <QTextEdit>
#include <QtDebug>
#include "mail.h"
#include"envoi_mail.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("C:/User/Téléchargementslogin.png");
    //ui->label_login->setPixmap(pix);
    ui->lineEdit_3->setValidator(new QIntValidator (0,9999, this));
    ui->lineEdit_25->setValidator(new QIntValidator (0,9999, this));

    ui->tableView->setModel(A.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    MainWindow w;

   QString  username=ui->lineEdit_nu->text();
   QString mot_passe=ui->lineEdit_mdp->text();

   if(username=="AZERTY" && mot_passe!="ADMIN")
   {
      QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
      QMessageBox::warning(this,"Login","Mot de passe incorrecte");
    }
   else
       if(username!="AZERTY" && mot_passe=="ADMIN")
     {
       QMessageBox::information(this,"Login","Mot de passe correcte");
       QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
   }
   else
   if(username=="AZERTY" && mot_passe=="ADMIN")
   {
      QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");

      ui->stackedwidget->setCurrentIndex(0);


    }
   else

     {
       QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe incorrectes");
}


}


void MainWindow::on_pushboutton_ajouter_clicked()
{
    int cod_av=ui->lineEdit_3->text().toInt();
    int H_dep=ui->lineEdit->text().toInt();
    int H_arr=ui->lineEdit_2->text().toInt();
    QString type_av=ui->lineEdit_10->text();
    int num_av=ui->lineEdit_7->text().toInt();
    QString fct_av=ui->lineEdit_12->text();
    int num_hang=ui->lineEdit_9->text().toInt();

    AVION A( cod_av, H_dep, H_arr, type_av, num_av, fct_av, num_hang);

    bool test=A.ajouter();
    if(test )
    {
           ui->tableView->setModel(A.afficher());


        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout avion effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout avion non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    AVION A;
    int cod_av=ui->lineEdit_25->text().toInt();
    bool test=A.supprimer(cod_av);
    if(test)
    {
         ui->tableView->setModel(A.afficher());

        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Suppression effectuée. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Suppression non effectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}



    void MainWindow::on_pushbutton_modifier1_clicked()
    {
        int cod_av=ui->lineEdit_code2->text().toInt();
        int H_dep=ui->lineEdit_dep2->text().toInt();
        int H_arr=ui->lineEdit_arr2->text().toInt();
        QString type_av=ui->lineEdit_typeavion2->text();
        int num_av=ui->lineEdit_numavi2->text().toInt();
        QString fct_av=ui->lineEdit_fct2->text();
        int num_hang=ui->lineEdit_numhangar2->text().toInt();

        AVION A( cod_av, H_dep, H_arr, type_av, num_av, fct_av, num_hang);


        bool test= A.modifier();
        if(test)
        { ui->tableView->setModel(A.afficher()) ;        // ui->tableView->setModel(A.afficher());
         // ui->tableView_2->setModel(A.afficher());

        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Modification effectuée.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);


        }

        else
            QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
            QObject::tr("Modification non effectuée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


        }





void MainWindow::on_pushButton_quitter_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_suivant_mail_clicked()
{
    ui->stackedwidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_suivant_chat_clicked()
{
    ui->stackedwidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_prec_ajout_clicked()
{
    ui->stackedwidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_prec_mail_clicked()
{
   ui->stackedwidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_confirmer_mail_clicked()
{
    QString adresse_mail=ui->lineEdit_20->text();
    QString mdp=ui->lineEdit_21->text();

    mail M(adresse_mail,mdp);
    bool test=M.ajouter_adr_mail();

    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Nouveau compte mail effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget->setCurrentIndex(1);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Nouveau compte mail non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_prec_compte_mail_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_envoyer_mail_clicked()
{
    QString destinataire=ui->lineEdit_destinataire->text();
    QString mail_envoye=ui->lineEdit_mail_message->text();

    envoi_mail EM(destinataire,mail_envoye);
    bool test=EM.ajouter_envoi_mail();

    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Envoi mail effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Envoi mail non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_ordre_desc_clicked()
{
    ui->tableView_3->setModel(A.tri1());
}

void MainWindow::on_pushButton_ordre_asc_clicked()
{
    ui->tableView_3->setModel(A.tri2());
}


void MainWindow::on_recherchebutton_textChanged(const QString &arg1)
{
    ui->tableView_4->setModel(A.rechercher(arg1));
}

void MainWindow::on_pushButton_prec_login_3_clicked()
{
    ui->stackedwidget->setCurrentIndex(3);
}
