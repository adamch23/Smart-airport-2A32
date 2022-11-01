#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "billet.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterbillet_clicked();


    void on_supprimerbillet_clicked();




    void on_modifierbillet_clicked();


    void on_trierbillet_clicked();








private:
    Ui::MainWindow *ui;
    billet tmpbillet;
};
#endif // MAINWINDOW_H
