#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billet.h"
#include <QMessageBox>
#include<QDate>
#include<QDateEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->le_nom->setInputMask("aaaaaaaaaaaaaaaaa");
    ui->le_nom_2->setInputMask("aaaaaaaaaaaaaaaaa");
    ui->le_prenom->setInputMask("aaaaaaaaaaaaaaaa");
    ui->le_prenom_2->setInputMask("aaaaaaaaaaaaaaaaa");
    ui->le_ref->setValidator( new QIntValidator(0, 99999999, this) );
    ui->le_destination->setInputMask("aaaaaaaaaaaaaaaa");
    ui->le_destination_2->setInputMask("aaaaaaaaaaaaaaaa");
    ui->le_ref_5->setValidator( new QIntValidator(0, 99999999, this) );
    ui->ancien_ref->setValidator( new QIntValidator(0, 99999999, this) );
    ui->tabbillet->setModel(tmpbillet.afficher());
    ui->tabbillettrier->setModel(tmpbillet.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouterbillet_clicked()
{

    long ref = ui->le_ref->text().toLong();
    QString destination = ui->le_destination->text();
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString date_depart= ui->le_date_depart->text();

  billet c(ref,destination,nom,prenom,date_depart);
  bool test=c.ajouter();
  if(test)
{ui->tabbillet->setModel(tmpbillet.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un billet"),
                  QObject::tr("billet ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un billet"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_supprimerbillet_clicked()
{
    long ref=ui->le_ref_5->text().toLong();
    bool test=tmpbillet.supprimer(ref);
    if(test)
    {ui->tabbillet->setModel(tmpbillet.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un billet"),
                    QObject::tr("billet supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un billet"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_modifierbillet_clicked()
{
    long ref=ui->ancien_ref->text().toInt();
        QString destination = ui->le_destination_2->text();
        QString nom= ui->le_nom_2->text();
        QString prenom= ui->le_prenom_2->text();
        QString date_depart= ui->le_date_depart->text();
        billet c1;

            if(c1.rech(ref)){
                bool test = c1.modifier(ref,destination,nom,prenom,date_depart);
                if(test){
                    ui->tabbillet->setModel(tmpbillet.afficher());
                    QMessageBox::information(nullptr, QObject::tr("Modifier un billet"),
                                QObject::tr("billet modifié.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier un billet"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
            }

}


void MainWindow::on_trierbillet_clicked()
{
    bool test=true;
        if(test){
                   if(ui->ref->isChecked())
               { ui->tabbillettrier->setModel(tmpbillet.trier_ref());
                QMessageBox::information(nullptr, QObject::tr("trier billet"),
                            QObject::tr("billet trier.\n"
                                        "Voulez-vous enregistrer les modifications ?"),
                                   QMessageBox::Save
                                   | QMessageBox::Cancel,
                                  QMessageBox::Save);
}

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("trier billet"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

}






