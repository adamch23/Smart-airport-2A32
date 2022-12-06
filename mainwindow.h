#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "billet.h"
#include <QMainWindow>
#include "exportexcelobject.h"


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








    void on_pdf_clicked();

    void on_rech_textChanged(const QString &arg1);

    void on_stat_clicked();

    void on_pagination_clicked();

    void on_export_excel_clicked();

private:
    Ui::MainWindow *ui;
    billet tmpbillet;
};
#endif // MAINWINDOW_H
