#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bagageee.h"
#include <QMainWindow>
#include "calculatrice.h"
#include"arduino.h"
#include <QEvent>
#include "avion.h"
#include "smtp.h"
#include "widget.h"
#include "DuMessengerConnectionDialog.h"
#include "billet.h"

#include "vols.h"
#include <QEvent>
#include "QRCodeGenerator.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QTcpSocket;;

namespace DuarteCorporation
{

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

    void update_label();
    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_rechid_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pdf_clicked();
    void pdf();
    void on_stats_clicked();


    void on_pushboutton_ajouter1adam_clicked();

    void on_pushButton_supprimer1adam_clicked();

    void on_pdfadam_clicked();

    void on_triadam_clicked();

    void on_tri_2adam_clicked();




    void on_siadamvols_textChanged(const QString &arg1);

    void on_updateadam_clicked();

    void on_statadam_clicked();

    void on_pushButton_gestionvols_clicked();

    void on_pushButton_gestionbagages_clicked();

    void on_pushButton_gestionavions_clicked();

    void on_pushButton_gestionvoyageurs_clicked();

    void on_pushButton_gestionpistes_clicked();

    void on_pushButton_Loginvol_clicked();


    void on_pushButton_prec_menuvol_clicked();

    void on_pushboutton_ajouteravion_clicked();

    void on_pushButton_supprimeravion_clicked();

    void on_pushbutton_modifier1avion_clicked();

     void on_pushButton_suivant_triavion_clicked();

    void on_pushButton_ordre_descavion_clicked();

    void on_pushButton_ordre_ascavion_clicked();


    void on_pushButton_prec_ajoutavion_clicked();

    void on_recherchebuttonavion_textChanged(const QString &arg1);

    void on_pdfavion_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();

    void on_pushButton_prec_login_avion_clicked();

    void on_pushButton_prec_login_vol_clicked();

    void on_pushButton_prec_login_billet_clicked();

    void on_pushButton_prec_login_piste_clicked();

    void on_pushButton_prec_login_bagage_clicked();


    void on_envoyer_chat_clicked();

    void on_connecter_chat_clicked();


    void on_pushButton_Loginbagage_clicked();

    void on_pushButton_prec_menubagage_clicked();

    void on_pushButton_Loginavion_clicked();

    void on_pushButton_prec_menuavion_clicked();

    void on_pushButton_Loginbillet_clicked();

    void on_pushButton_prec_menubillet_clicked();

    void on_pushButton_Loginpiste_clicked();

    void on_pushButton_prec_menupiste_clicked();

    void on_pushButton_quitter_clicked();

    void on_envoyer_chat_2_clicked();

    void on_connecter_chat_2_clicked();

    void on_envoyer_chat_3_clicked();

    void on_connecter_chat_3_clicked();

    void on_ajouterbillet_clicked();

    void on_supprimerbillet_clicked();

    void on_modifierbillet_clicked();

    void on_trierbillet_clicked();

    void on_export_excel_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_3adama_clicked();

    void update_label2();
//
private:
    void updateQRImage();
    void setScale(int);




private slots:
    void on_pButtonSave_clicked();
    void on_sBoxScale_valueChanged(int arg1);
    void on_pTextEditQRText_textChanged();
    void on_pButtonQuit_clicked();
    void on_QRgenerate_clicked();
    //

    void on_pushButton_4vols_clicked();

    void on_pushButton_7vols_clicked();

    void on_pushButton_8vols_clicked();

    void on_envoyer_chat_4_clicked();

    void on_connecter_chat_4_clicked();

private:
    Ui::MainWindow *ui;
    AVION A1;
    BAGAGEEE B;
    calculatrice *c;
    QStringList files;
    QTcpSocket *mSocket;
    QTcpSocket *mSocket2;
    QTcpSocket *mSocket3;
     QTcpSocket *mSocket4;

    QByteArray data ;
            QString idA=QStringLiteral("");
             arduino A ;
             VOLS Etmp;
             CQR_Encode qrEncode;
             bool successfulEncoding;
             int encodeImageSize;
             QPoint lastPos;
protected:

   // void closeEvent(QCloseEvent *);
    //bool eventFilter( QObject * object, QEvent * event );

    VOLS v;
    billet tmpbillet;

};
}
#endif // MAINWINDOW_H
