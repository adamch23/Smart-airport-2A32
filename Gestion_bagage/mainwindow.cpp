#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bagageee.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include "dialog_stats.h"
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->ID -> setValidator (new QIntValidator(0, 999999, this));
   ui->tabvalise->setModel(B.afficher());
   ui->rechid -> setValidator (new QIntValidator(0, 999999, this));
   ui->poids -> setValidator (new QIntValidator(0, 99, this));


   int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
            //le slot update_label suite à la reception du signal readyRead (reception des données).




}
void MainWindow::update_label()
{
 data="";

while((A.getdata().size()<6))
{
    QString key;
data=A.read_from_arduino();

break;

}
if(data.toInt()!=0)
{int D=data.toInt();
    if(A.chercherid(D)!=-1)
    {
        QMessageBox::information(nullptr, QObject::tr("id exist"),
                    QObject::tr("id exist.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {  QMessageBox::critical(nullptr, QObject::tr("introuvlable"),
                             QObject::tr("introuvlable.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}

 qDebug() << D ;
}





data="";
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    //recuperation des information saisis dans les 6 champs
   int id=ui->ID->text().toInt();
   QString nom=ui->nom->text();
   QString prenom=ui->prenom->text();
   QString typebagage=ui->typebagage->text();
   int dimensionsbagage=ui->dimensionsbagage->text().toInt();
   int poids=ui->poids->text().toInt();
 BAGAGEEE B(id,nom,prenom,typebagage,dimensionsbagage,poids);

 if(poids>50)
     {
      QMessageBox::critical(nullptr, QObject::tr("not ok"),
                  QObject::tr("ce bagage depasse la poids maximal . \n"
                              "Click Cancel to exit."), QMessageBox::Ok);

  }
 //else{*/
 bool test=B.ajouter();
 if(test)
 { QMessageBox::information(nullptr, QObject::tr("ok"),
                         QObject::tr("ajout effectué.\n"
                                     "Click Cancel to exit."), QMessageBox::Ok);
  ui->tabvalise->setModel(B.afficher());//refresh
     }
         else
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                         QObject::tr("ajout non effectuée\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

//}


}

void MainWindow::on_supprimer_clicked()
{
   BAGAGEEE B1; B1.setid(ui->id_supp->text().toInt());
   bool test=B1.supprimer(B1.getid());
   QMessageBox msgBox;
   if(test)
   {msgBox.setText("supprimer avec succes");

       ui->tabvalise->setModel(B.afficher());//refresh supp
   }
               else
       msgBox.setText("echec de supprimer");
   msgBox.exec();
}

void MainWindow::on_update_clicked()
{
    int id=ui->ID_2->text().toInt();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    QString typebagage=ui->typebagage_2->text();
    int dimensionsbagage=ui->dimensionsbagage_2->text().toInt();
    int poids=ui->poids_2->text().toInt();
    BAGAGEEE B(id,nom,prenom,typebagage,dimensionsbagage,poids);
    bool test=B.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tabvalise->setModel(B.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
   ui->tabvalise->setModel(B.affichertriAZ()) ;
}

void MainWindow::on_TRI_clicked()
{
    ui->tabvalise->setModel(B.affichertriZA()) ;

}



void MainWindow::on_lineEdit_2_textChanged(const QString &nom)
{
    ui->tabvalise->setModel(B.recherchernom(nom)) ;

}

void MainWindow::on_rechid_textChanged(const QString &arg1)
{
    ui->tabvalise->setModel(B.rechercher(arg1)) ;

}

void MainWindow::on_pushButton_5_clicked()
{

    c= new calculatrice(this);
    c->show();
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tabvalise->model()->rowCount();//lignes
                                    const int columnCount = ui->tabvalise->model()->columnCount();//coll

                                    out <<  "<html>\n"// pour faire un tableau avec html
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>listes des valises </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)// remplissage de tableau
                                        if (!ui->tabvalise->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tabvalise->model()->headerData(column, Qt::Horizontal).toString());//afficher a partir de la base de donnes
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tabvalise->isColumnHidden(column)) {
                                                QString data = ui->tabvalise->model()->data(ui->tabvalise->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);// qprinter c'est une classe qui a comme attribut eli tahtha
                                printer.setOutputFormat(QPrinter::PdfFormat);// format
                               printer.setPaperSize(QPrinter::A4);// size
                              printer.setOutputFileName(fileName);// win bch naaml enregistremet


                               QTextDocument doc;//html
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}

void MainWindow::on_stats_clicked()
{
    Dialog_Stats stats;
    stats.setModal(true);
    stats.exec();
}
