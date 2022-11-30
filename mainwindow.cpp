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
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
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
#include "smtp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Connection c;
     c.createconnection();
    //QPixmap pix("C:/User/Téléchargementslogin.png");
    //ui->label_login->setPixmap(pix);
    ui->lineEdit_3->setValidator(new QIntValidator (0,9999, this));
    ui->lineEdit_25->setValidator(new QIntValidator (0,9999, this));

    ui->tableView->setModel(A.afficher());

    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    int ret=Ar.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< Ar.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<Ar.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(Ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

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

void MainWindow::on_pdf_clicked()
{
    QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tableView->model()->rowCount();
                                    const int columnCount = ui->tableView->model()->columnCount();

                                    out <<  "<html>\n"
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>listes des avions </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tableView->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableView->isColumnHidden(column)) {
                                                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_GESTION_AVION_clicked()
{
     ui->stackedwidget->setCurrentIndex(4);
}

void MainWindow::update_label()
{
    data=Ar.read_from_arduino();
ui->label_13->setText("Mouvement non détecté");
    if(data=="1")

      {

        ui->label_13->setText("Mouvement détecté !!"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher Mouvement détecté


    //QMessageBox::warning(this,"Détection du mouvement","Mouvement détecté !!");
    }

    //else if (data=="0")

}
