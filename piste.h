#ifndef PISTE_H
#define PISTE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>

class Piste
{

    QString reference ;
    int numero ;
    int etat;
    float larg;
    float longeur;

public:
    Piste();
    Piste(QString,int,int,float,float);

    QString getRef();
    int getNum();
    int getEtat();
    float getLarg();
    float getLong();


    void setRef(QString);
     void setNum(int);
     void setEtat(int);
     void setLarg(float);
     void setLong(float);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
     void recherche(QTableView* table,int);
      QSqlQueryModel * tri();

};

#endif // PISTE_H
