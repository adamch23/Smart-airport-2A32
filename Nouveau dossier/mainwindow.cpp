#include "mainwindow.h"
#include "vols.h"
#include <QScrollArea>
#include <QImageWriter>
#include <QScrollBar>
#include "avion.h"

#include "billet.h"

#include "smtp.h"
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
#include "arduino.h"
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "vols.h"
#include <QMouseEvent>

//#include "widget.h"
#include "DuMessengerConnectionDialog.h"


#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>


//

const QString getIniPath()
{
    const static QString iniPath( qApp->applicationDirPath() + "/settings.ini" );
    return iniPath;
}
QString saveFormats()
{
    static QString suffix;
    foreach ( const QByteArray & format , QImageWriter::supportedImageFormats() )
        suffix += QString( "%1 ( *.%2 )\n" )
                .arg( QString( format ).toUpper() )
                .arg( QString( format ) );

    return suffix;
}


//
namespace DuarteCorporation
{
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //roubee
    ui->ID -> setValidator (new QIntValidator(0, 999999, this));
    ui->ID_2 -> setValidator (new QIntValidator(0, 999999, this));

   ui->tabvalise->setModel(B.afficher());
   ui->rechid -> setValidator (new QIntValidator(0, 999999, this));
   ui->poids -> setValidator (new QIntValidator(0, 99, this));
   ui->poids_2 -> setValidator (new QIntValidator(0, 99, this));


   ui->nom->setInputMask("aaaaaaaaaaaaaaaaaa");
   ui->nom_2->setInputMask("aaaaaaaaaaaaaaaaaa");


   ui->prenom->setInputMask("aaaaaaaaaaaaaaaaaaaa");
   ui->prenom_2->setInputMask("aaaaaaaaaaaaaaaaaaaa");


   ui->typebagage->setInputMask("aaaaaaaaaaaaaaaaaaaa");
   ui->typebagage_2->setInputMask("aaaaaaaaaaaaaaaaaaaa");



   ui->dimensionsbagage->setValidator (new QIntValidator(0, 999999, this));
   ui->dimensionsbagage_2->setValidator (new QIntValidator(0, 999999, this));

   //rahma

   ui->le_nom->setInputMask("aaaaaaaaaaaaaaaaa");
   ui->le_nom_2->setInputMask("aaaaaaaaaaaaaaaaa");
   ui->le_prenom->setInputMask("aaaaaaaaaaaaaaaa");
   ui->le_prenom_2->setInputMask("aaaaaaaaaaaaaaaaa");
   ui->le_ref->setValidator( new QIntValidator(0, 99999999, this) );
   ui->le_destination->setInputMask("aaaaaaaaaaaaaaaa");
   ui->le_destination_2->setInputMask("aaaaaaaaaaaaaaaa");
   ui->le_ref_5->setValidator( new QIntValidator(0, 99999999, this) );
   ui->ancien_ref->setValidator( new QIntValidator(0, 99999999, this) );
   ui->tabbillet->setModel(tmpbillet.afficherrahma());
   ui->tabbillettrier->setModel(tmpbillet.afficherrahma());


   //for email tab
   connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
   connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));


   mSocket = new QTcpSocket(this);

   connect(mSocket , &QTcpSocket :: readyRead , [&]() {
       QTextStream T(mSocket);
       auto text = T.readAll();
       ui->textEdit->append(text);



   });

   mSocket2 = new QTcpSocket(this);

   connect(mSocket2 , &QTcpSocket :: readyRead , [&]() {
       QTextStream T(mSocket2);
       auto text = T.readAll();
       ui->textEdit_2->append(text);



   });

   mSocket3 = new QTcpSocket(this);

   connect(mSocket3 , &QTcpSocket :: readyRead , [&]() {
       QTextStream T(mSocket3);
       auto text = T.readAll();
       ui->textEdit_3->append(text);



   });

   mSocket4 = new QTcpSocket(this);

   connect(mSocket4 , &QTcpSocket :: readyRead , [&]() {
       QTextStream T(mSocket4);
       auto text = T.readAll();
       ui->textEdit_4->append(text);



   });


   int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
                QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
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



void MainWindow::pdf()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tabbb->model()->rowCount();//lignes
                                    const int columnCount = ui->tabbb->model()->columnCount();//coll

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
                                        if (!ui->tabbb->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tabbb->model()->headerData(column, Qt::Horizontal).toString());//afficher a partir de la base de donnes
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tabbb->isColumnHidden(column)) {
                                                QString data = ui->tabbb->model()->data(ui->tabbb->model()->index(row, column)).toString().simplified();
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


            void MainWindow::update_label()
            {
            data=A.read_from_arduino();


            if(data=="1")
            {
                idA=idA+"1";

            }
            else if(data=="2")
            {
                idA=idA+"2";

            }
            else if(data=="3")
            {
                idA=idA+"3";

            }
            else if(data=="4")
            {
                idA=idA+"4";
            }
            else if(data=="5")
            {
                idA=idA+"5";

            }
            else if(data=="6")
            {
                idA=idA+"6";
            }
            else if(data=="7")
            {
                idA=idA+"7";

            }
            else if(data=="8")
            {
                idA=idA+"8";

            }
            else if(data=="9")
            {
                idA=idA+"9";

            }
            else if(data=="0")
            {
                idA=idA+"0";

            }
            else if(data=="A")
            {
            ui->tabbb->setModel(B.rechercher(idA));
            }
            else if(data=="B")
            {
               pdf();
            }
            else if(data=="C")
            {
                idA=QStringLiteral("");
                QSqlQueryModel *model= new QSqlQueryModel();
                ui->tabbb->setModel(model);
               // ui->label_3->setText(idA);
            }
            else if(data=="D")
            {
            idA.chop(1);
            }
            else if(data=="*")
            {
            ui->line_5->setEchoMode(QLineEdit::Password);
            }
            else if(data=="#")
            {
            ui->line_5->setEchoMode(QLineEdit::Normal);
            }
            else if(data=="##")
            {
            close();
            }
            ui->line_5->setText(idA);
            }

void MainWindow::on_pushboutton_ajouter1adam_clicked()
{
    int CODEDEVOL=ui->lineEdit_3vols->text().toInt();
    QString NOMDUVOL=ui->lineEdit_4vols->text();
    QString DATEDEDECOLAGE=ui->lineEdit_13vols->text();
    QString DATEDARRIVEE=ui->lineEdit_10vols->text();
    QString DUREEDUVOL=ui->lineEdit_7vols->text();
    QString TRANSIT=ui->lineEdit_12vols->text();


    VOLS V( CODEDEVOL, NOMDUVOL, DATEDEDECOLAGE, DATEDARRIVEE, DUREEDUVOL, TRANSIT);

    bool test=V.ajoutervols();
    if(test)
    {
           ui->tableViewvols->setModel(V.affichervols());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer1adam_clicked()
{
    QString CODEDEVOL=ui->lineEdit_25vols->text();
    bool test=Etmp.supprimervols(CODEDEVOL);
    if(test)
    {
         ui->tableViewvols->setModel(Etmp.affichervols());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Suppression effectuée. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Suppression non effectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pdfadam_clicked()
{

    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tableViewvols->model()->rowCount();
                                    const int columnCount = ui->tableViewvols->model()->columnCount();

                                    out <<  "<html>\n"
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>listes des vols </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tableViewvols->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tableViewvols->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableViewvols->isColumnHidden(column)) {
                                                QString data = ui->tableViewvols->model()->data(ui->tableViewvols->model()->index(row, column)).toString().simplified();
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

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);

}

void MainWindow::on_triadam_clicked()
{
     ui->tableViewvols->setModel(VOLS().trievols());
}



void MainWindow::on_tri_2adam_clicked()
{
     ui->tableViewvols->setModel(VOLS().trie2vols());
}


void MainWindow::on_siadamvols_textChanged(const QString &arg1)
{
     ui->tableViewvols->setModel(VOLS().recherchervols(arg1));
}

void MainWindow::on_updateadam_clicked()
{
    int CODEDEVOL=ui->lineEdit_9vols->text().toInt();
        QString NOMDUVOL=ui->lineEdit_11vols->text();
        QString DUREEDUVOL=ui->lineEdit_16vols->text();
        QString DATEDEDECOLAGE=ui->lineEdit_14vols->text();
        QString DATEDARRIVAGE=ui->lineEdit_15vols->text();
        QString TRANSIT=ui->lineEdit_17vols->text();


        VOLS V1 ( CODEDEVOL, NOMDUVOL, DUREEDUVOL, DATEDEDECOLAGE, DATEDARRIVAGE, TRANSIT);


        bool test= V1.modifiervols();

        if(test)
        { ui->tableViewvols->setModel(V1.affichervols()) ;        // ui->tableView->setModel(A.afficher());
         // ui->tableView_2->setModel(V.afficher());

        QMessageBox::information(nullptr, QObject::tr("data base is open"),
                                 QObject::tr("oui.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);


        }

        else
            QMessageBox::critical(nullptr, QObject::tr("data base is not open"),
            QObject::tr("non.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_statadam_clicked()

    {
        Dialog_Stats stats;
        stats.setModal(true);
        stats.exec();
    }




void MainWindow::on_pushButton_gestionvols_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_gestionbagages_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_gestionavions_clicked()
{
ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_gestionvoyageurs_clicked()
{
ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_gestionpistes_clicked()
{
ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_Loginvol_clicked()
{
    QString  username=ui->lineEdit_nu1->text();
    QString mot_passe=ui->lineEdit_mdp1->text();


    if(username=="ADAM" && mot_passe!="ADAM")
    {
       QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
       QMessageBox::warning(this,"Login","Mot de passe incorrecte");
     }
    else
        if(username!="ADAM" && mot_passe=="ADAM")
      {
        QMessageBox::information(this,"Login","Mot de passe correcte");
        QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
    }

        else
            if(username=="ADAM" && mot_passe=="ADAM")
          {
            QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");
            ui->stackedWidget->setCurrentIndex(7);
        }

    else
           {
               QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe  incorrectes");
           }

}


void MainWindow::on_pushButton_prec_menuvol_clicked()
{
   ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushboutton_ajouteravion_clicked()
{
    int cod_av=ui->lineEdit_3avion->text().toInt();
    int H_dep=ui->lineEditavion->text().toInt();
    int H_arr=ui->lineEdit_2avion->text().toInt();
    QString type_av=ui->lineEdit_10avion->text();
    int num_av=ui->lineEdit_7avion->text().toInt();
    QString fct_av=ui->lineEdit_12avion->text();
    int num_hang=ui->lineEdit_9avion->text().toInt();

    AVION A1( cod_av, H_dep, H_arr, type_av, num_av, fct_av, num_hang);

    bool test=A1.ajouteravion();
    if(test )
    {
           ui->tableViewavion->setModel(A1.afficheravion());


        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout avion effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout avion non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimeravion_clicked()
{
    AVION A1;
    int cod_av=ui->lineEdit_25avion->text().toInt();
    bool test=A1.supprimeravion(cod_av);
    if(test)
    {
         ui->tableViewavion->setModel(A1.afficheravion());

        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Suppression effectuée. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Suppression non effectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushbutton_modifier1avion_clicked()
{
    int cod_av=ui->lineEdit_code2avion->text().toInt();
    int H_dep=ui->lineEdit_dep2avion->text().toInt();
    int H_arr=ui->lineEdit_arr2avion->text().toInt();
    QString type_av=ui->lineEdit_typeavion2avion->text();
    int num_av=ui->lineEdit_numavi2avion->text().toInt();
    QString fct_av=ui->lineEdit_fct2avion->text();
    int num_hang=ui->lineEdit_numhangar2avion->text().toInt();

    AVION A1( cod_av, H_dep, H_arr, type_av, num_av, fct_av, num_hang);


    bool test= A1.modifieravion();
    if(test)
    { ui->tableViewavion->setModel(A1.afficheravion()) ;        // ui->tableView->setModel(A.afficher());
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


void MainWindow::on_pushButton_suivant_triavion_clicked()
{
  ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_pushButton_ordre_descavion_clicked()
{
    ui->tableView_3avion->setModel(A1.tri1avion());
}

void MainWindow::on_pushButton_ordre_ascavion_clicked()
{
    ui->tableView_3avion->setModel(A1.tri2avion());
}



void MainWindow::on_pushButton_prec_ajoutavion_clicked()
{
   ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_recherchebuttonavion_textChanged(const QString &arg1)
{
    ui->tableView_4avion->setModel(A1.rechercheravion(arg1));
}

void MainWindow::on_pdfavion_clicked()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tableViewavion->model()->rowCount();//lignes
                                    const int columnCount = ui->tableViewavion->model()->columnCount();//coll

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
                                        if (!ui->tableViewavion->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tableViewavion->model()->headerData(column, Qt::Horizontal).toString());//afficher a partir de la base de donnes
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableViewavion->isColumnHidden(column)) {
                                                QString data = ui->tableViewavion->model()->data(ui->tableViewavion->model()->index(row, column)).toString().simplified();
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

void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("anis.chaibi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("anis.chaibi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("anis.chaibi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}



void MainWindow::on_pushButton_prec_login_avion_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_prec_login_vol_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_prec_login_billet_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_prec_login_piste_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_prec_login_bagage_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow:: on_envoyer_chat_clicked()
{
    QTextStream T(mSocket);
    T << ui->surnom->text() << ": " << ui->message_chat->text();
    mSocket->flush();
    ui->message_chat->clear();
}

void MainWindow::on_connecter_chat_clicked()
{
    DuMessengerConnectionDialog D(this);
    if(D.exec() == QDialog :: Rejected)
       {
        return;
    }
    mSocket->connectToHost(D.nomHost(),D.port());

}

}



void DuarteCorporation::MainWindow::on_pushButton_Loginbagage_clicked()
{
    QString  username=ui->lineEdit_nu2->text();
    QString mot_passe=ui->lineEdit_mdp2->text();


    if(username=="ROUBE" && mot_passe!="ROUBE")
    {
       QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
       QMessageBox::warning(this,"Login","Mot de passe incorrecte");
     }
    else
        if(username!="ROUBE" && mot_passe=="ROUBE")
      {
        QMessageBox::information(this,"Login","Mot de passe correcte");
        QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
    }

        else
            if(username=="ROUBE" && mot_passe=="ROUBE")
          {
            QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");
            ui->stackedWidget->setCurrentIndex(0);
        }

    else
           {
               QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe  incorrectes");
           }

}

void DuarteCorporation::MainWindow::on_pushButton_prec_menubagage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DuarteCorporation::MainWindow::on_pushButton_Loginavion_clicked()
{
    QString  username=ui->lineEdit_nu3->text();
    QString mot_passe=ui->lineEdit_mdp3->text();


    if(username=="ANIS" && mot_passe!="ANIS")
    {
       QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
       QMessageBox::warning(this,"Login","Mot de passe incorrecte");
     }
    else
        if(username!="ANIS" && mot_passe=="ANIS")
      {
        QMessageBox::information(this,"Login","Mot de passe correcte");
        QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
    }

        else
            if(username=="ANIS" && mot_passe=="ANIS")
          {
            QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");
            ui->stackedWidget->setCurrentIndex(8);
        }

    else
           {
               QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe  incorrectes");
           }
}

void DuarteCorporation::MainWindow::on_pushButton_prec_menuavion_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DuarteCorporation::MainWindow::on_pushButton_Loginbillet_clicked()
{
    QString  username=ui->lineEdit_nu4->text();
    QString mot_passe=ui->lineEdit_mdp4->text();


    if(username=="RAHMA" && mot_passe!="RAHMA")
    {
       QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
       QMessageBox::warning(this,"Login","Mot de passe incorrecte");
     }
    else
        if(username!="RAHMA" && mot_passe=="RAHMA")
      {
        QMessageBox::information(this,"Login","Mot de passe correcte");
        QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
    }

        else
            if(username=="RAHMA" && mot_passe=="RAHMA")
          {
            QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");
            ui->stackedWidget->setCurrentIndex(9);
        }

    else
           {
               QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe  incorrectes");
           }
}

void DuarteCorporation::MainWindow::on_pushButton_prec_menubillet_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void DuarteCorporation::MainWindow::on_pushButton_Loginpiste_clicked()
{
    QString  username=ui->lineEdit_nu5->text();
    QString mot_passe=ui->lineEdit_mdp5->text();


    if(username=="ISLEM" && mot_passe!="ISLEM")
    {
       QMessageBox::information(this,"Login","Nom d'utilisateur correcte");
       QMessageBox::warning(this,"Login","Mot de passe incorrecte");
     }
    else
        if(username!="ISLEM" && mot_passe=="ISLEM")
      {
        QMessageBox::information(this,"Login","Mot de passe correcte");
        QMessageBox::warning(this,"Login","Nom d'utilisateur incorrecte");
    }

        else
            if(username=="ISLEM" && mot_passe=="ISLEM")
          {
            QMessageBox::information(this,"Login","Nom d'utilisateur et mot de passe correctes");
            ui->stackedWidget->setCurrentIndex(10);
        }

    else
           {
               QMessageBox::warning(this,"Login","Nom d'utilisateur et mot de passe  incorrectes");
           }
}

void DuarteCorporation::MainWindow::on_pushButton_prec_menupiste_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DuarteCorporation::MainWindow::on_pushButton_quitter_clicked()
{
    this->close();
}

void DuarteCorporation::MainWindow::on_envoyer_chat_2_clicked()
{
    QTextStream T(mSocket2);
    T << ui->surnom_2->text() << ": " << ui->message_chat_2->text();
    mSocket2->flush();
    ui->message_chat_2->clear();
}

void DuarteCorporation::MainWindow::on_connecter_chat_2_clicked()
{
    DuMessengerConnectionDialog D(this);
    if(D.exec() == QDialog :: Rejected)
       {
        return;
    }
    mSocket2->connectToHost(D.nomHost(),D.port());

}

void DuarteCorporation::MainWindow::on_envoyer_chat_3_clicked()
{
    QTextStream T(mSocket3);
    T << ui->surnom_3->text() << ": " << ui->message_chat_3->text();
    mSocket3->flush();
    ui->message_chat_3->clear();
}

void DuarteCorporation::MainWindow::on_connecter_chat_3_clicked()
{
    DuMessengerConnectionDialog D(this);
    if(D.exec() == QDialog :: Rejected)
       {
        return;
    }
    mSocket3->connectToHost(D.nomHost(),D.port());
}

void DuarteCorporation::MainWindow::on_ajouterbillet_clicked()
{

    long ref = ui->le_ref->text().toLong();
    QString destination = ui->le_destination->text();
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString date_depart= ui->le_date_depart->text();

  billet c(ref,destination,nom,prenom,date_depart);
  bool test=c.ajouterrahma();
  if(test)
{ui->tabbillet->setModel(tmpbillet.afficherrahma());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un billet"),
                  QObject::tr("billet ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un billet"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void DuarteCorporation::MainWindow::on_supprimerbillet_clicked()
{
    long ref=ui->le_ref_5->text().toLong();
    bool test=tmpbillet.supprimerrahma(ref);
    if(test)
    {ui->tabbillet->setModel(tmpbillet.afficherrahma());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un billet"),
                    QObject::tr("billet supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un billet"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void DuarteCorporation::MainWindow::on_modifierbillet_clicked()
{
    long ref=ui->ancien_ref->text().toInt();
        QString destination = ui->le_destination_2->text();
        QString nom= ui->le_nom_2->text();
        QString prenom= ui->le_prenom_2->text();
        QString date_depart= ui->le_date_depart->text();
        billet c1;

            if(c1.rechrahma(ref)){
                bool test = c1.modifierrahma(ref,destination,nom,prenom,date_depart);
                if(test){
                    ui->tabbillet->setModel(tmpbillet.afficherrahma());
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

void DuarteCorporation::MainWindow::on_trierbillet_clicked()
{
    bool test=true;
        if(test){
                   if(ui->ref->isChecked())
               { ui->tabbillettrier->setModel(tmpbillet.trier_refrahma());
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

void DuarteCorporation::MainWindow::on_export_excel_clicked()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tabbillet->model()->rowCount();
                                    const int columnCount = ui->tabbillet->model()->columnCount();

                                    out <<  "<html>\n"
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>listes des billets </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tabbillet->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tabbillet->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tabbillet->isColumnHidden(column)) {
                                                QString data = ui->tabbillet->model()->data(ui->tabbillet->model()->index(row, column)).toString().simplified();
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

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);
}

void DuarteCorporation::MainWindow::on_pushButton_3_clicked()
{
    QPieSeries *series = new QPieSeries();


            QStringList list=v.listeDUREEDUVOL("CODEDEVOL");



            for (int i =0; i< list.size();i++)
            {
                series->append(list[i],v.calcul_DUREEDUVOL(list[i],"CODEDEVOL"));

            }
            QPieSlice *slice = series->slices().at(1);
            slice->setLabelVisible();
            slice->setExploded();


            QtCharts::QChart *chart =new QtCharts::QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des CODEDEVOL");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartview=new QChartView(chart);
            QGridLayout *mainLayout=new QGridLayout();
            mainLayout->addWidget(chartview,0,0);
            ui->label_91adam->setLayout(mainLayout);
}

void DuarteCorporation::MainWindow::on_pushButton_3adama_clicked()
{
    QPieSeries *series = new QPieSeries();


            QStringList list=v.listeDUREEDUVOL("CODEDEVOL");



            for (int i =0; i< list.size();i++)
            {
                series->append(list[i],v.calcul_DUREEDUVOL(list[i],"CODEDEVOL"));

            }
            QPieSlice *slice = series->slices().at(1);
            slice->setLabelVisible();
            slice->setExploded();


            QtCharts::QChart *chart =new QtCharts::QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des CODEDEVOL");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartview=new QChartView(chart);
            QGridLayout *mainLayout=new QGridLayout();
            mainLayout->addWidget(chartview,0,0);
            ui->label_91adam->setLayout(mainLayout);
}

//nouveau qrcode


void DuarteCorporation::MainWindow::on_QRgenerate_clicked()
{
    //ui->scrollArea->installEventFilter( this );



    QSettings ini( getIniPath(), QSettings::IniFormat );
    ui->splitter_2->restoreState( ini.value( ui->splitter_2->objectName() ).toByteArray() );
    ui->splitter_3->restoreState( ini.value( ui->splitter_3->objectName() ).toByteArray() );
    ui->sBoxScale_2->setValue( ini.value( ui->sBoxScale_2->objectName(), 4 ).toInt() );
    restoreState( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );

    setScale( ui->sBoxScale_2->value() );
    updateQRImage();
}

//fin qrcode
void DuarteCorporation::MainWindow::updateQRImage()
{
    int sizeText = ui->pTextEditQRText_2vols->toPlainText().size();
    ui->labelSizeText_2->setText( QString::number( sizeText ) );

    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    QString encodeString = ui->pTextEditQRText_2vols->toPlainText();

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->image_label_2vols->clear();
        ui->image_label_2vols->setText( tr("QR Code...") );
        ui->labelSize_2->clear();
        ui->pButtonSave_2->setEnabled( successfulEncoding );
        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;

    // Создаем двумерный образ кода
    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );

    // Создать двумерный образ кода
    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->image_label_2vols->setPixmap( QPixmap::fromImage( encodeImage ) );

    setScale(ui->sBoxScale_2->value());
    ui->pButtonSave_2->setEnabled( successfulEncoding );
}
void DuarteCorporation::MainWindow::setScale(int scale)
{
    if ( successfulEncoding )
    {
        int scale_size = encodeImageSize * scale;

        const QPixmap & scale_image = ui->image_label_2vols->pixmap()->scaled( scale_size, scale_size );
        ui->image_label_2vols->setPixmap( scale_image );

        const QString & size_info = QString( "%1x%2" ).arg( scale_size ).arg( scale_size );
        ui->labelSize_2->setText( size_info );
    }
}

void DuarteCorporation::MainWindow::on_pButtonSave_clicked()
{
    const QString & path = QFileDialog::getSaveFileName( this, QString ::null , "qrcode", saveFormats() );
    if ( path.isNull() )
        return;

    ui->image_label_2vols->pixmap()->save( path );
}
void DuarteCorporation::MainWindow::on_sBoxScale_valueChanged(int arg1)
{
    setScale( arg1 );
}
void DuarteCorporation::MainWindow::on_pTextEditQRText_textChanged()
{
    updateQRImage();
}
void DuarteCorporation::MainWindow::on_pButtonQuit_clicked()
{
    close();
}

/*void DuarteCorporation::MainWindow::closeEvent(QCloseEvent *)
{
    QSettings ini( getIniPath(), QSettings::IniFormat );
    ini.setValue( ui->splitter_3->objectName(), ui->splitter_3->saveState() );
    ini.setValue( ui->splitter_2->objectName(), ui->splitter_2->saveState() );
    ini.setValue( ui->sBoxScale_2->objectName(), ui->sBoxScale_2->value() );
    ini.setValue( "State", saveState() );
    ini.setValue( "Geometry", saveGeometry() );

    qApp->quit();
}*/
/*bool DuarteCorporation::MainWindow::eventFilter( QObject * object, QEvent * event )
{
    QScrollArea * scrollArea = ui->scrollArea;

    if ( object == scrollArea )
    {
        if ( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent * mouseEvent = static_cast < QMouseEvent * > ( event );
            if ( mouseEvent->button() == Qt::LeftButton )
            {
                lastPos = mouseEvent->pos();

                if( scrollArea->horizontalScrollBar()->isVisible()
                        || scrollArea->verticalScrollBar()->isVisible() )
                    scrollArea->setCursor( Qt::ClosedHandCursor );
                else
                    scrollArea->setCursor( Qt::ArrowCursor );
            }

        }else if ( event->type() == QEvent::MouseMove )
        {
            QMouseEvent *mouseEvent = static_cast < QMouseEvent * > ( event );

            if ( mouseEvent->buttons() == Qt::LeftButton )
            {
                lastPos -= mouseEvent->pos();

                int hValue = scrollArea->horizontalScrollBar()->value();
                int vValue = scrollArea->verticalScrollBar()->value();

                scrollArea->horizontalScrollBar()->setValue( lastPos.x() + hValue );
                scrollArea->verticalScrollBar()->setValue( lastPos.y() + vValue );

                lastPos = mouseEvent->pos();
            }

        }else if ( event->type() == QEvent::MouseButtonRelease )
            scrollArea->setCursor( Qt::ArrowCursor );
    }

    return QWidget::eventFilter(object, event);
}


*/

void DuarteCorporation::MainWindow::on_pushButton_4vols_clicked()
{
      A.write_to_arduino("1"); //envoyer 1 à arduino
}

void DuarteCorporation::MainWindow::on_pushButton_7vols_clicked()
{
    A.write_to_arduino("0");  //envoyer 0 à arduino
}

void DuarteCorporation::MainWindow::on_pushButton_8vols_clicked()
{
    QString CODEDEVOL=ui->lineEdit_18->text();
    QSqlQuery query;

    QByteArray message;

    QString ch;



    query.prepare("select TRANSIT from VOLS where CODEDEVOL = "+CODEDEVOL+"");
    if (query.exec())
                        {
                            while(query.next())
                            {
                             ch =query.value(0).toString();

                            }

                            message=ch.toUtf8();
                            A.write_to_arduino("4") ;
                             A.write_to_arduino(message) ;}

                             else {



                               A.write_to_arduino("CODE INVALIDE") ;}

}

void DuarteCorporation::MainWindow::update_label2()
{
    data=A.read_from_arduino();
ui->label_13avion->setText("Mouvement non détecté");
    if(data=="1")

      {

        ui->label_13avion->setText("Mouvement détecté !!"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher Mouvement détecté


    //QMessageBox::warning(this,"Détection du mouvement","Mouvement détecté !!");
    }

    //else if (data=="0")

}


void DuarteCorporation::MainWindow::on_envoyer_chat_4_clicked()
{
    QTextStream T(mSocket4);
    T << ui->surnom_4->text() << ": " << ui->message_chat_4->text();
    mSocket4->flush();
    ui->message_chat_4->clear();
}

void DuarteCorporation::MainWindow::on_connecter_chat_4_clicked()
{
    DuMessengerConnectionDialog D(this);
    if(D.exec() == QDialog :: Rejected)
       {
        return;
    }
    mSocket4->connectToHost(D.nomHost(),D.port());
}
