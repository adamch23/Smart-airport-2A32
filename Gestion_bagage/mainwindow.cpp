

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>


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




void MainWindow::on_pushButtonAjouter_clicked()
{
    QString id_bagage=ui->id_bagage->text();
    QString type_bagage=ui->type_bagage->text();
    QString dimension_bagage=ui->dimension_bagage->text();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString poids=ui->poids->text();
 Bagage B(id_bagage,type_bagage,dimension_bagage,nom,prenom,poids);
 bool test=B.ajouter();
 if (test)
         { //Actualiser
      ui->tab_bagage->setModel(B.afficher());
         QMessageBox:: information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Ajout effectué\n"
                                                        "click cancel to exit."),QMessageBox::Cancel);
         }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "click Cancel to exit."),QMessageBox::Cancel);
 }




