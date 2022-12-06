#ifndef BILLET_H
#define BILLET_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class billet
{
    long ref;
        QString nom,prenom,destination,date_depart;

public:
    billet();
    billet(long,QString,QString,QString,QString);
    long getref(){return ref;}
    void setref(long ref){this->ref=ref;}
    void setdestination(QString destination){this->destination=destination;}
    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(long);
    bool rech(long);
        bool modifier(long,QString,QString,QString,QString);
        QSqlQueryModel * afficherbilletchercher(long);
        QSqlQueryModel * afficher_billet_ch(int);
        QSqlQueryModel *rechercher(QString id);
        QStringList listedestination(QString var);
        int calcul_destination(QString adresse,QString val);




        QSqlQueryModel * trier_ref();

    ~billet(){}


};

#endif // billet_H
