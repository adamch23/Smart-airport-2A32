#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "piste.h"
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString reference=ui->le_ref->text();
    int numero=ui->le_num->text().toInt();
    int etat=ui->le_etat->text().toInt();

    int larg=ui->l_larg->text().toFloat();
    int longeur=ui->le_long->text().toFloat();



Piste p(reference,numero,etat,larg,longeur);
bool test=p.ajouter();

if (test)
{

     ui->tab_pistes->setModel(p.afficher());


    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("ajout effectué\n"
                                         "click cancel to exit."), QMessageBox::Cancel);

}
else QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("Ajout non effectué.\n"
                                       "Click Cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_pushButton_4_clicked()
{
    int numero= ui->le_refsupp->text().toInt();
    bool test=p.supprimer(numero);
    if (test)
    {


        ui->tab_pistes->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué\n"
                                             "click cancel to exit."), QMessageBox::Cancel);

    }
    else QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("suppression non effectué.\n"
                                           "Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_refrech_clicked()
{
     ui->tab_pistes->setModel(p.afficher());
}

void MainWindow::on_update_clicked()
{


    int numero = ui->modif_num->text().toInt();
    QString reference = ui->modif_ref->text();
     int etat = ui->modif_etat->text().toInt();
     float larg = ui->modif_larg->text().toFloat();
    float longeur = ui->modif_longeur->text().toFloat();


   Piste p(reference,numero,etat,larg,longeur);

   bool test=p.modifier(p);
   if (test)
        {  ui->tab_pistes->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("modifier"),
                          QObject::tr(" piste modifié .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
       }





    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectuée"),  QMessageBox::Cancel);

}
