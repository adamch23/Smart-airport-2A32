#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vols.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <string>
#include<QMessageBox>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QScrollArea>
#include <QImageWriter>
#include <QScrollBar>
#include <QSettings>
#include <QApplication>

#include <QDebug>
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
   , successfulEncoding(false)

{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
     ui->lineEdit_3->setValidator(new QIntValidator(0, 9999999, this));
 //    ui->lineEdit_25->setValidator(new QIntValidator(0, 9999999, this));
 //    ui->lineEdit_9->setValidator(new QIntValidator(0, 9999999, this));

/*
     ui->scrollArea->installEventFilter( this );

     QSettings ini( getIniPath(), QSettings::IniFormat );
     ui->splitter_2->restoreState( ini.value( ui->splitter_2->objectName() ).toByteArray() );
     ui->splitter_3->restoreState( ini.value( ui->splitter_3->objectName() ).toByteArray() );
     ui->sBoxScale_2->setValue( ini.value( ui->sBoxScale_2->objectName(), 4 ).toInt() );
     restoreState( ini.value( "State" ).toByteArray() );
     restoreGeometry( ini.value( "Geometry" ).toByteArray() );

     setScale( ui->sBoxScale_2->value() );
     updateQRImage();
     */


}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushboutton_ajouter1_clicked()
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

//nouveau qrcode





void MainWindow::on_QRgenerate_clicked()
{
    ui->scrollArea->installEventFilter( this );

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


void MainWindow::on_pushButton_supprimer1_clicked()
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


void MainWindow::on_update_clicked()
{

        int CODEDEVOL=ui->lineEdit_9->text().toInt();
            QString NOMDUVOL=ui->lineEdit_11->text();
            QString DUREEDUVOL=ui->lineEdit_16->text();
            QString DATEDEDECOLAGE=ui->lineEdit_14->text();
            QString DATEDARRIVAGE=ui->lineEdit_15->text();
            QString TRANSIT=ui->lineEdit_17->text();


            VOLS V1 ( CODEDEVOL, NOMDUVOL, DUREEDUVOL, DATEDEDECOLAGE, DATEDARRIVAGE, TRANSIT);


            bool test= V1.modifier();

            if(test)
            { ui->tableView->setModel(V1.afficher()) ;        // ui->tableView->setModel(A.afficher());
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
void MainWindow::updateQRImage()
{
    int sizeText = ui->pTextEditQRText_2->toPlainText().size();
    ui->labelSizeText_2->setText( QString::number( sizeText ) );

    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    QString encodeString = ui->pTextEditQRText_2->toPlainText();

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->image_label_2->clear();
        ui->image_label_2->setText( tr("QR Code...") );
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

    ui->image_label_2->setPixmap( QPixmap::fromImage( encodeImage ) );

    setScale(ui->sBoxScale_2->value());
    ui->pButtonSave_2->setEnabled( successfulEncoding );
}
void MainWindow::setScale(int scale)
{
    if ( successfulEncoding )
    {
        int scale_size = encodeImageSize * scale;

        const QPixmap & scale_image = ui->image_label_2->pixmap()->scaled( scale_size, scale_size );
        ui->image_label_2->setPixmap( scale_image );

        const QString & size_info = QString( "%1x%2" ).arg( scale_size ).arg( scale_size );
        ui->labelSize_2->setText( size_info );
    }
}

void MainWindow::on_pButtonSave_clicked()
{
    const QString & path = QFileDialog::getSaveFileName( this, QString ::null , "qrcode", saveFormats() );
    if ( path.isNull() )
        return;

    ui->image_label_2->pixmap()->save( path );
}
void MainWindow::on_sBoxScale_valueChanged(int arg1)
{
    setScale( arg1 );
}
void MainWindow::on_pTextEditQRText_textChanged()
{
    updateQRImage();
}
void MainWindow::on_pButtonQuit_clicked()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings ini( getIniPath(), QSettings::IniFormat );
    ini.setValue( ui->splitter_3->objectName(), ui->splitter_3->saveState() );
    ini.setValue( ui->splitter_2->objectName(), ui->splitter_2->saveState() );
    ini.setValue( ui->sBoxScale_2->objectName(), ui->sBoxScale_2->value() );
    ini.setValue( "State", saveState() );
    ini.setValue( "Geometry", saveGeometry() );

    qApp->quit();
}
bool MainWindow::eventFilter( QObject * object, QEvent * event )
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
                                        "<center> <H1>listes des vols </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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

void MainWindow::on_tri_clicked()
{
    ui->tableView->setModel(VOLS().trie());
}

void MainWindow::on_tri_2_clicked()
{
    ui->tableView->setModel(VOLS().trie2());
}

void MainWindow::on_siadam_textChanged(const QString &arg1)
{
    ui->tableView->setModel(VOLS().rechercher(arg1));

}

void MainWindow::on_stat_clicked()
{
    QPieSeries *series = new QPieSeries();


        QStringList list=VOLS().listeDUREEDUVOL("DUREEDUVOL");



        for (int i =0; i< list.size();i++)
        {
            series->append(list[i],VOLS().calcul_DUREEDUVOL(list[i],"DUREEDUVOL"));

        }
        QPieSlice *slice = series->slices().at(1);
        slice->setLabelVisible();
        slice->setExploded();


        QtCharts::QChart *chart =new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques");
        chart->setAnimationOptions(QChart::AllAnimations);
        QChartView *chartview=new QChartView(chart);
        QGridLayout *mainLayout=new QGridLayout();
        mainLayout->addWidget(chartview,0,0);
        ui->sta->setLayout(mainLayout);
}
//

void MainWindow::on_calendarWidget_selectionChanged()
{

        QDate selectedDate = ui->calendarWidget->selectedDate();
        ui->textBrowser->setText(selectedDate.toString("dd/MM/yy"));
       ui->tableView_2->setModel(v.affichercalendrier());


}













