#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bagageee.h"
#include <QMainWindow>
#include "calculatrice.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_update_clicked();

    void on_pushButton_clicked();

    void on_TRI_clicked();


    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_rechid_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pdf_clicked();

    void on_stats_clicked();

    void on_rechid_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    BAGAGEEE B;
    calculatrice *c;


};

#endif // MAINWINDOW_H
