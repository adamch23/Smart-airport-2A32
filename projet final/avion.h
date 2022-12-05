#ifndef AVION_H
#define AVION_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>



class AVION
{
private:
    int cod_av;
    int H_dep;
    int H_arr;
    QString type_av;
    int num_av;
    QString fct_av;
    int num_hang;

public:
    AVION();
    AVION(int,int,int,QString,int,QString,int);
    int getcod_av();
    int getH_dep();
    int getH_arr();
    QString gettype_av();
    int getnum_av();
    QString getfct_av();
    int getnum_hang();

    void setcod_av(int);
    void setH_dep(int);
    void setH_arr(int);
    void settype_av(QString);
    void setnum_av(int);
    void setfct_av(QString);
    void setnum_hang(int);

    bool ajouteravion();
    /*bool supprimer(int cod_av);*/
    bool supprimeravion(int);
    QSqlQueryModel * afficheravion();
    bool modifieravion();
    QSqlQueryModel * tri1avion();
     QSqlQueryModel * tri2avion();
    QSqlQueryModel * rechercheravion(QString type_av);




};

#endif // AVION_H
