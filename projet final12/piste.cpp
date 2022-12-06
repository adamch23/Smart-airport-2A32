#include "piste.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include<QTableView>
#include <QSqlTableModel>

Piste::Piste()
{
    reference=" ";
    numero=0;
    etat=0;
    larg=0;
    longeur=0;


}

Piste::Piste(QString reference,int numero,int etat,float larg,float longeur)
{
    this->reference=reference;
    this->numero=numero;
    this->etat=etat;
    this->larg=larg;
    this->longeur=longeur;

}



QString Piste::getRef(){return reference;}
int Piste::getNum(){return numero;}
int Piste::getEtat(){return etat;}
float Piste::getLarg(){return larg;}
float Piste::getLong(){return longeur;}

void Piste::setRef(QString){this->reference=reference;}
void Piste::setNum(int numero){this->numero=numero;}
void Piste::setEtat(int etat){this->etat=etat;}
void Piste::setLarg(float larg){this->larg=larg;}
void Piste::setLong(float longeur){this->longeur=longeur;}



bool Piste::ajouterislem()
{
    QSqlQuery query;
QString res= QString::number(etat);
QString res1= QString::number(numero);
QString res2= QString::number(larg);
QString res3= QString::number(longeur);
query.prepare("INSERT INTO Piste (reference, numero, etat, larg, longeur) "
                       "VALUES (:reference, :numero, :etat, :larg, :longeur)");
         query.bindValue(":reference", reference);
         query.bindValue(":numero", res1);
         query.bindValue(":etat", res);
         query.bindValue(":larg", res2);
          query.bindValue(":longeur", res3);

        return query.exec();

}
bool Piste::supprimerislem(int numero )
{
    QSqlQuery query;
    query.prepare("Delete from Piste where numero=:numero");
         query.bindValue(0, numero);


        return query.exec();
}

QSqlQueryModel* Piste::afficherislem()
{


    QSqlQueryModel* model= new QSqlQueryModel();
          model->setQuery("SELECT * FROM Piste");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("numero"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("larg"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("longeur"));


    return model;
   }

bool Piste::modifierislem()
{

    QSqlQuery query;
    query.prepare( "UPDATE Piste SET  numero =:numero, etat = :etat, larg= :larg, longeur =:longeur WHERE  reference =:reference");
    query.bindValue(":numero",(int)numero);
    query.bindValue(":etat",(int)etat);
    query.bindValue(":larg",(int)larg);
    query.bindValue(":longeur",(int)longeur);
    query.bindValue(":reference", reference);



 return query.exec();


}
void Piste::rechercheislem(QTableView* table,int res1){

    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery;
    query->prepare("select * from Piste  where NUMERO = :numero");
    query->bindValue(":numero",res1);
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}

QSqlQueryModel *Piste::triislem()
{

    QSqlQuery *q = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  Piste ORDER BY numero ");
    q->exec();
    model->setQuery(*q);
    return model;
}

