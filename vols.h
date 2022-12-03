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

    bool ajoutervols();
    bool supprimervols(QString CODEDEVOL);
    QSqlQueryModel * affichervols();
    bool modifiervols();
    QSqlQueryModel* trievols();
 QSqlQueryModel* trie2vols();
 QSqlQueryModel *recherchervols(QString CODEDEVOL);
 QSqlQueryModel *rechercher_Datevols(QDate DATEDEDECOLAGE );



 QSqlQueryModel *affichercalendriervols();

};

#endif // AVION_H
