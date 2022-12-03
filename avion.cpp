#include "avion.h"
#include<string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QtWidgets>

AVION::AVION()
{
 cod_av=0;
 H_dep=0;
 H_arr=0;
 type_av="";
 num_av=0;
 fct_av=" ";
 num_hang=0;
}
AVION::AVION(int cod_av,int H_dep,int H_arr,QString type_av,int num_av,QString fct_av,int num_hang)
{
    this->cod_av=cod_av;
    this->H_dep=H_dep;
    this->H_arr=H_arr;
    this->type_av=type_av;
    this->num_av=num_av;
    this->fct_av=fct_av;
    this->num_hang=num_hang;
}
int AVION::getcod_av(){ return cod_av;}
int AVION::getH_dep(){ return H_dep;}
int AVION::getH_arr(){ return H_arr;}
QString AVION::gettype_av(){ return type_av;}
int AVION::getnum_av(){ return num_av;}
QString AVION::getfct_av(){ return fct_av;}
int AVION::getnum_hang(){ return num_hang;}

void AVION::setcod_av(int cod_av){ this->cod_av=cod_av; }
void AVION::setH_dep(int H_dep){ this->H_dep=H_dep; }
void AVION::setH_arr(int H_arr){this->H_arr=H_arr;  }
void AVION::settype_av(QString type_av){  this->type_av=type_av; }
void AVION::setnum_av(int num_av){ this->num_av=num_av; }
void AVION::setfct_av(QString fct_av){  this->fct_av=fct_av; }
void AVION::setnum_hang(int num_hang){ this->num_hang=num_hang; }

/*bool AVION::ajouter()
{

    QString res=QString::number(cod_av);
    QString dep=QString::number(H_dep);
    QString arr=QString::number(H_arr);
    QString num=QString::number(num_av);
    QString ha=QString::number(num_hang);



    QSqlQuery query;

  query.prepare("insert into avion (COD_AV, H_DEP, H_ARR, TYPE_AV , NUM_AV , FCT_AV , NUM_HANG) ""VALUES (:cod_av, : H_dep, :H_arr , :type_av , :num_av , :fct_av, :num_hang )");

           query.bindValue(0, res);
           query.bindValue(1, dep);
           query.bindValue(2,arr );
           query.bindValue(3,type_av);
           query.bindValue(4,num);
           query.bindValue(5,fct_av);
            query.bindValue(6,ha);
          return query.exec();
}*/

bool AVION::ajouteravion()
{  QSqlQuery query;

    QString res=QString::number(cod_av);
    QString dep=QString::number(H_dep);
    QString arr=QString::number(H_arr);
    QString num=QString::number(num_av);
    QString ha=QString::number(num_hang);





  query.prepare("insert into avion (COD_AV, H_DEP, H_ARR, TYPE_AV , NUM_AV , FCT_AV , NUM_HANG) ""VALUES (:cod_av, : H_dep, :H_arr , :type_av , :num_av , :fct_av, :num_hang )");

           query.bindValue(0, res);
           query.bindValue(1, dep);
           query.bindValue(2,arr );
           query.bindValue(3,type_av);
           query.bindValue(4,num);
           query.bindValue(5,fct_av);
            query.bindValue(6,ha);
          return query.exec();
}

bool AVION::supprimeravion(int cod_av)
{
    int codavv;
        QSqlQuery query,query1;
        QString res=QString::number(cod_av);

        query.prepare("select COD_AV from AVION where COD_AV= :cod_av");
        query.bindValue(":cod_av", res);
        query.exec();
        while(query.next())
      {

       codavv=query.value(0).toInt();
       }
        if (codavv!=cod_av) {  QMessageBox::critical(nullptr, QObject::tr("supp impossible"),
       QObject::tr("le code avion taper n'existe pas"), QMessageBox::Cancel); }
        else {
            query1.prepare("DELETE from AVION where COD_AV= :cod_av");
            query1.bindValue(":cod_av", cod_av);
            QMessageBox::information(nullptr, QObject::tr("suppression reussit"),
               QObject::tr("suppression reussit"), QMessageBox::Cancel);


       }
        return  query1.exec();
}


QSqlQueryModel * AVION::afficheravion()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from AVION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("COD_AV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("H_DEP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("H_ARR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE_AV"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_AV"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("FCT_AV"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM_HANG"));

    return model;
}



bool AVION::modifieravion()
{

    QSqlQuery query;

    QString res=QString::number(cod_av);
    QString dep=QString::number(H_dep);
    QString arr=QString::number(H_arr);
    QString num=QString::number(num_av);
    QString ha=QString::number(num_hang);

        query.prepare ("update avion set COD_AV = :cod_av , H_DEP = :H_dep , H_ARR = :H_arr , TYPE_AV = :type_av , NUM_AV = :num_av , FCT_AV = :fct_av , NUM_HANG = :num_hang  where COD_AV= :cod_av ");
        query.bindValue(":cod_av",res );
        query.bindValue(":H_dep",dep);
        query.bindValue(":H_arr",arr);
        query.bindValue(":type_av",type_av);
        query.bindValue(":num_av",num );
        query.bindValue(":fct_av",fct_av);
        query.bindValue(":num_hang",ha);
        return query.exec();
}

/*

        query.prepare ("update avion set COD_AV = :cod_av , H_DEP = :H_dep , H_ARR = :H_arr , TYPE_AV = :type_av , NUM_AV = :num_av , FCT_AV = :fct_av , NUM_HANG = :num_hang  where COD_AV= :cod_av ");
        query.bindValue(":cod_av",res );
        query.bindValue(":H_dep",dep);
        query.bindValue(":H_arr",arr);
        query.bindValue(":type_av",type_av);
        query.bindValue(":num_av",num );
        query.bindValue(":fct_av",fct_av);
        query.bindValue(":num_hang",ha);
        return query.exec();
}*/

QSqlQueryModel * AVION:: tri1avion()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from avion order by COD_AV desc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("COD_AV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("H_DEP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("H_ARR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE_AV"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_AV"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("FCT_AV"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM_HANG"));

    return model;
}

QSqlQueryModel * AVION:: tri2avion()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from avion order by COD_AV asc");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("COD_AV"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("H_DEP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("H_ARR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE_AV"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_AV"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("FCT_AV"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM_HANG"));

    return model;
}
QSqlQueryModel * AVION::rechercheravion(QString type_av)
{

     QSqlQueryModel *model= new QSqlQueryModel();
   model->setQuery("SELECT * FROM avion WHERE TYPE_AV LIKE'%"+type_av+"%'");
             return model;
}
