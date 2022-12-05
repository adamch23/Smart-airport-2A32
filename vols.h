#ifndef VOLS_H
#define VOLS_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>

class VOLS
{
private:
    int CODEDEVOL;
    QString NOMDUVOL;
    QString DUREEDUVOL;
    QString DATEDEDECOLAGE;
    QString DATEDARRIVAGE;
    QString TRANSIT;

public:
    VOLS();
    VOLS(int,QString,QString,QString,QString,QString);
    int getCODEDEVOL();
    QString getNOMDUVOL();
    QString getDUREEDUVOL();
    QString getDATEDEDECOLAGE();
    QString getDATEDARRIVAGE();
    QString getTRANSIT();


    void setCODEDEVOL(int);
    void setNOMDUVOL(QString);
    void setDUREEDUVOL(QString);
    void setDATEDEDECOLAGE(QString);
    void setDATEDARRIVAGE(QString);
    void setTRANSIT(QString);
    QStringList listeDUREEDUVOL(QString var) ;
    int calcul_DUREEDUVOL(QString adresse,QString val);

    bool ajouter();
    bool supprimer(QString CODEDEVOL);
    QSqlQueryModel * afficher();
    bool modifier();
    QSqlQueryModel* trie();
 QSqlQueryModel* trie2();
 QSqlQueryModel *rechercher(QString CODEDEVOL);
 QSqlQueryModel *rechercher_Date(QDate DATEDEDECOLAGE );



 QSqlQueryModel *affichercalendrier();

};

#endif // AVION_H
