#ifndef BAGAGEEE_H
#define BAGAGEEE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class BAGAGEEE

{
    QString nom,prenom,typebagage;
    int  id;
    int dimensionsbagage,poids;

public:
   //constructeurs
    BAGAGEEE(){}
    BAGAGEEE(int,QString,QString,QString,int,int);
//gettters
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString gettypebagage(){return typebagage;}
    int getid(){return id;}
    int getdimensionsbagage(){return dimensionsbagage;}
    int getPoids(){return poids;}
   //setters
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void settypebagage(QString t){typebagage=t;}
    void setid(int id){this->id=id;}
     void setpoids(int po){this->poids=po;}
     void setdimensionsbagage(int d){this->dimensionsbagage=d;}
     //fonctionnalites de bases relatives à l'entité Bagageee
     bool ajouter();
     QSqlQueryModel * afficher();
    bool supprimer (int);
    bool modifier();
QSqlQueryModel * affichertriAZ();
QSqlQueryModel * affichertriZA();
QSqlQueryModel *rechercher(QString rech);
QSqlQueryModel *recherchernom(QString nom);




};

#endif // BAGAGEEE_H
