#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "vols.h"
#include <QMainWindow>
#include "vols.h"
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

   void on_pushboutton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_update_clicked();

private:
    Ui::MainWindow *ui;
    VOLS Etmp;
};
#endif // MAINWINDOW_H