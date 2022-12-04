#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "piste.h"
#include <QMainWindow>
#include "smtp.h"
#include <QVariant>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_refrech_clicked();

    void on_update_clicked();

    void on_butt_rech_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_Send_clicked();

    void on_pushButton_excel_clicked();

private:
    Ui::MainWindow *ui;
    Piste p;
    Smtp* smtp;
        QString msg;
        QString mail;
signals:
        void setCenter(QVariant, QVariant);
        void addMarker(QVariant, QVariant);

};
#endif // MAINWINDOW_H
