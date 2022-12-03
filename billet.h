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
    bool ajouterrahma();
    QSqlQueryModel * afficherrahma();
    bool supprimerrahma(long);
    bool rechrahma(long);
        bool modifierrahma(long,QString,QString,QString,QString);
        QSqlQueryModel * afficherbilletchercherrahma(long);
        QSqlQueryModel * afficher_billet_chrahma(int);
        QSqlQueryModel *rechercherrahma(QString id);
        QStringList listedestinationrahma(QString var);
        int calcul_destinationrahma(QString adresse,QString val);




        QSqlQueryModel * trier_refrahma();

    ~billet(){}


};

#endif // billet_H
