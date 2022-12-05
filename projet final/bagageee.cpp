#include "bagageee.h"
#include <QSqlQuery>
#include<QDebug>
#include<QObject>

BAGAGEEE:: BAGAGEEE(int id,QString nom,QString prenom,QString typebagage,int dimensionsbagage,int poids)
{
   this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->typebagage=typebagage;
    this->dimensionsbagage=dimensionsbagage;
    this->poids=poids;


}
bool BAGAGEEE::ajouter()
{
   QString res=QString ::number(id);
   QString res2=QString ::number(poids);
   QString res3=QString ::number(dimensionsbagage);

    QSqlQuery query;

    query.prepare("INSERT INTO bagagee (id, nom, prenom,typebagage,dimensionsbagage,poids) "
                     "VALUES (:id, :nom, :prenom,:typebagage,:dimensionsbagage,:poids)");
      //creation des variables liees
    query.bindValue(":id", res);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":typebagage", typebagage);
       query.bindValue(":dimensionsbagage",res3);
       query.bindValue(":poids", res2);

       return query.exec(); //exec() envoie la requete pour l'executeur
}

bool BAGAGEEE::supprimer(int id)
{
    QSqlQuery query;


       query.prepare("delete from bagagee where id=:id");
       query.bindValue(0, id);


       query.exec();



}
QSqlQueryModel*BAGAGEEE::afficher()
{

     QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT *  FROM bagagee");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifient"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type bagage"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("dimensionsbagage"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("poids"));



 return model;
}
bool BAGAGEEE::modifier()
{
    QString res=QString ::number(id);
    QString res2=QString ::number(poids);
    QString res3=QString ::number(dimensionsbagage);

QSqlQuery query;
query.prepare("update bagagee set id= :id, nom= :nom, prenom= :prenom,typebagage=:typebagage,dimensionsbagage=:dimensionsbagage,poids=:poids where id = :id ");
query.bindValue(":id", res);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":typebagage", typebagage);
   query.bindValue(":dimensionsbagage",res3);
   query.bindValue(":poids", res2);
return    query.exec();
}


QSqlQueryModel * BAGAGEEE::affichertriAZ()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * from bagagee order by prenom Asc");
return model;
}
QSqlQueryModel * BAGAGEEE::affichertriZA()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * from bagagee  order by prenom DESC");
return model;
}
QSqlQueryModel *BAGAGEEE::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM bagagee WHERE id LIKE'"+rech+"%'");
    return model;


}
QSqlQueryModel *BAGAGEEE::recherchernom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM bagagee WHERE nom LIKE'"+nom+"%'");
    return model;


}
