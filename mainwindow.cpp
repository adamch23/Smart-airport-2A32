#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avion.h"
#include "connection.h"
#include <string>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushboutton_ajouter_clicked()
{
    int cod_av=ui->lineEdit_3->text().toInt();
    int H_dep=ui->lineEdit_4->text().toInt();
    int H_arr=ui->lineEdit_13->text().toInt();
    QString type_av=ui->lineEdit_10->text();
    int num_av=ui->lineEdit_7->text().toInt();
    QString fct_av=ui->lineEdit_12->text();
    int num_hang=ui->lineEdit_9->text().toInt();

    AVION A( cod_av, H_dep, H_arr, type_av, num_av, fct_av, num_hang);

    bool test=A.ajouter();
    if(test)
    {
           ui->tableView->setModel(A.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int cod_av=ui->lineEdit_25->text().toInt();
    bool test=Etmp.supprimer(cod_av);
    if(test)
    {
         ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Suppression effectuée. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Suppression non effectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

