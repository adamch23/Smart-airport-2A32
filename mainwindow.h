#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vols.h"

#include <QMainWindow>
#include "vols.h"
#include <QEvent>
#include "QRCodeGenerator.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   // MainWindow(QWidget *parent = nullptr);
     explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

   void on_pushboutton_ajouter1_clicked();

    void on_pushButton_supprimer1_clicked();

    void on_update_clicked();
private:
    void updateQRImage();
    void setScale(int);

private:
    Ui::MainWindow *ui;
    VOLS Etmp;
    CQR_Encode qrEncode;
    bool successfulEncoding;
    int encodeImageSize;
    QPoint lastPos;
private slots:
    void on_pButtonSave_clicked();
    void on_sBoxScale_valueChanged(int arg1);
    void on_pTextEditQRText_textChanged();
    void on_pButtonQuit_clicked();
    void on_QRgenerate_clicked();

    void on_pdf_clicked();

    void on_tri_clicked();

    void on_tri_2_clicked();

    void on_siadam_textChanged(const QString &arg1);

    void on_stat_clicked();
    void on_calendarWidget_selectionChanged();



protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter( QObject * object, QEvent * event );
    VOLS v;
};
#endif // MAINWINDOW_H
