#include "billet.h"
#include<QSqlQuery>
#include<QString>
#include<QVariant>

billet::billet()
{
    ref=0;
    destination="";
    nom="";
    prenom="";
    date_depart="";
}

billet::billet(long ref,QString destination,QString nom,QString prenom,QString date_depart)
{
this->ref=ref;
this->destination=destination;
this->nom=nom;
this->prenom=prenom;
this->date_depart=date_depart;

}

bool billet::ajouterrahma()
{
    QSqlQuery query;
    QString res=QString::number(ref);
          query.prepare("INSERT INTO BILLET (ref,destination, nom, prenom, date_depart) "
                        "VALUES (:ref, :destination, :nom, :prenom, :date_depart)");
          query.bindValue(":ref", res);
          query.bindValue(":destination", destination);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":date_depart", date_depart);


          return  query.exec();
}

QSqlQueryModel * billet::afficherrahma()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from billet");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("destination"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_depart"));

    return model;
}

bool billet::supprimerrahma(long ref)
{
QSqlQuery query;
QString res= QString::number(ref);
query.prepare("Delete from billet where ref = :ref ");
query.bindValue(":ref", res);
return    query.exec();
}


bool billet::modifierrahma(long ref,QString destination,QString nom,QString prenom,QString date_depart){
    QSqlQuery query;
    QString res=QString::number(ref);
    query.prepare("update billet set destination=:destination ,nom=:nom ,prenom=:prenom,date_depart=:date_depart  where ref = :ref");
    query.bindValue(":ref", res);
    query.bindValue(":destination", destination);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_depart", date_depart);

    return query.exec();
}

bool billet::rechrahma(long ref){
    QSqlQuery query;
    QString res=QString::number(ref);
    query.prepare("select * from billet where ref = :ref");
    query.bindValue(":ref", res);
    query.bindValue(":destination", destination);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_depart", date_depart);


    return query.exec();
}

QSqlQueryModel * billet::afficherbilletchercherrahma(long ref)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString res=QString::number(ref);
    model->setQuery("select * from billet where ref= :ref");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("destination"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_depart"));

    return model;
}

QSqlQueryModel * billet::trier_refrahma()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from billet ORDER BY ref");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("destination"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_depart"));

        return model;
}


QSqlQueryModel *billet::rechercherrahma(QString id)
{

    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM billet WHERE ref LIKE'%"+id+"%'");
        return model;
}
QStringList billet::listedestinationrahma(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from billet");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int billet::calcul_destinationrahma(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from billet  WHERE "+val+"=:destination");
     query.bindValue(":destination", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
