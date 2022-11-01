#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vols.h"
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
    int CODEDEVOL=ui->lineEdit_3->text().toInt();
    QString NOMDUVOL=ui->lineEdit_4->text();
    QString DATEDEDECOLAGE=ui->lineEdit_13->text();
    QString DATEDARRIVEE=ui->lineEdit_10->text();
    QString DUREEDUVOL=ui->lineEdit_7->text();
    QString TRANSIT=ui->lineEdit_12->text();


    VOLS V( CODEDEVOL, NOMDUVOL, DATEDEDECOLAGE, DATEDARRIVEE, DUREEDUVOL, TRANSIT);

    bool test=V.ajouter();
    if(test)
    {
           ui->tableView->setModel(V.afficher());
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
    QString CODEDEVOL=ui->lineEdit_25->text();
    bool test=Etmp.supprimer(CODEDEVOL);
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



