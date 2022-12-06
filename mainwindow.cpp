#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billet.h"
#include <QMessageBox>
#include<QDate>
#include<QDateEdit>
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
#include <QSqlQuery>



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







void MainWindow::on_pdf_clicked()
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

void MainWindow::on_rech_textChanged(const QString &arg1)
{
    ui->tabbillet->setModel(tmpbillet.rechercher(arg1));
}

void MainWindow::on_stat_clicked()
{
    QPieSeries *series = new QPieSeries();


            QStringList list=tmpbillet.listedestination("destination");



            for (int i =0; i< list.size();i++)
            {
                series->append(list[i],tmpbillet.calcul_destination(list[i],"destination"));

            }
            QPieSlice *slice = series->slices().at(1);
            slice->setLabelVisible();
            slice->setExploded();


            QtCharts::QChart *chart =new QtCharts::QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des destination");
            chart->setAnimationOptions(QChart::AllAnimations);
            QChartView *chartview=new QChartView(chart);
            QGridLayout *mainLayout=new QGridLayout();
            mainLayout->addWidget(chartview,0,0);
            ui->stat->setLayout(mainLayout);
}

void MainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tabbillet);

    //colums to export
    obj.addField(0, "reference", "char(20)");
    obj.addField(1, "nom", "char(20)");
    obj.addField(2, "prenom", "char(20)");
    obj.addField(3, "destination", "char(20)");
    obj.addField(4, "date de depart", "char(20)");
    obj.addField(5, "pilote", "char(20)");
    obj.addField(5, "avion", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}


