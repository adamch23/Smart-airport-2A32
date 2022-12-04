#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "piste.h"

#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QPrinter>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include <QPlainTextEdit>
#include <QQuickItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

    emit setCenter(25.000, 20.000);
    emit addMarker(25.000, 20.000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()          //ajout
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

void MainWindow::on_pushButton_4_clicked()         //suppression
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


   /* int numero = ui->modif_num->text().toInt();
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
*/
   /*
    int etat=ui->modif_etat->text().toInt();
    int numero=ui->modif_num->text().toInt();
        QString reference=ui->modif_ref->text();
        int larg=ui->modif_larg->text().toFloat();
        int longeur=ui->modif_longeur->text().toFloat();*/

        QString reference=ui->modif_ref->text();
        int numero=ui->modif_num->text().toInt();
        int etat=ui->modif_etat->text().toInt();

        int larg=ui->modif_larg->text().toInt();
        int longeur=ui->modif_longeur->text().toInt();

      Piste  p(reference,numero,etat,larg,longeur);

        bool test=p.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tab_pistes->setModel(p.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_butt_rech_clicked()
{
    QString findText;
          QString text = ui->recherche->text();
      Piste p ;
      QTableView* table=ui->tab_pistes;
          if (text.isEmpty()) {
              QMessageBox::information(this, tr("Empty Field"),
                  tr("Entrez une specialité a rechercher."));
              ui->tab_pistes->setModel(p.afficher());
              return;
          } else {
              findText = text;
              p.recherche(table,findText.toUInt());


  }
}

void MainWindow::on_pushButton_3_clicked()   //tri
{
    ui->tab_pistes->setModel(p.tri());
}

void MainWindow::on_pushButton_6_clicked()        //pdf
{
    QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tab_pistes->model()->rowCount();
                        const int columnCount = ui->tab_pistes->model()->columnCount();

                        out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("strTitle")
                            <<  "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"

                           //     "<align='right'> " << datefich << "</align>"
                            "<center> <H1>Liste des Pistes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                        // headers
                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_pistes->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_pistes->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tab_pistes->isColumnHidden(column)) {
                                    QString data = ui->tab_pistes->model()->data(ui->tab_pistes->model()->index(row, column)).toString().simplified();
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










// /////////////nkqjcmhcwbxdwfzd

void MainWindow::on_Send_clicked()
{
    smtp = new Smtp("gestion.pistes.contact@gmail.com" , "nkqjcmhcwbxdwfzd", "smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

       msg=ui->message_mail->toPlainText();

       smtp->sendMail("contact",ui->a_mail->text(),ui->objet_mail->text(),msg);

       QMessageBox::information(nullptr, QObject::tr("SENT"),
                                QObject::tr("Email Sended Successfully.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_excel_clicked()
{
    QTableView *table;
     table = ui->tab_pistes;

     QString filters("CSV files (*.csv);;All files (*.*)");
     QString defaultFilter("CSV files (*.csv)");
     QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                        filters, &defaultFilter);
     QFile file(fileName);

     QAbstractItemModel *model =  table->model();
     if (file.open(QFile::WriteOnly | QFile::Truncate)) {
         QTextStream data(&file);
         QStringList strList;
         for (int i = 0; i < model->columnCount(); i++) {
             if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                 strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
             else
                 strList.append("");
         }
         data << strList.join(";") << "\n";
         for (int i = 0; i < model->rowCount(); i++) {
             strList.clear();
             for (int j = 0; j < model->columnCount(); j++) {

                 if (model->data(model->index(i, j)).toString().length() > 0)
                     strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") + "\n";
         }
         file.close();
         QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
     }
}
