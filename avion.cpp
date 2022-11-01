#include "avion.h"
#include<string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

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

bool AVION::ajouter()
{



    QString cod_av_string=QString::number(cod_av);
    QString H_dep_string=QString::number(H_dep);
    QString H_arr_string=QString::number(H_arr);
    QString num_av_string=QString::number(num_av);
    QString num_hang_string=QString::number(num_hang);
    QSqlQuery query;

  query.prepare("insert into AVION (cod_av, H_dep, H_arr, type_av , num_av , fct_av , num_hang) ""VALUES (:cod_av, : H_dep, :H_arr , :type_av , :num_av , :fct_av, :num_hang )");
          /*query.bindValue(":cod_av", cod_av_string);
          query.bindValue(":H_dep", H_dep_string);
          query.bindValue(":H_arr", H_arr_string);
          query.bindValue(":type_av", type_av);
          query.bindValue(":num_av", num_av_string);
          query.bindValue(":fct_av", fct_av);
           query.bindValue(":num_hang", num_hang_string);*/
           query.bindValue(0, cod_av_string);
           query.bindValue(1, H_dep_string);
           query.bindValue(2, H_arr_string);
           query.bindValue(3, type_av);
           query.bindValue(4, num_av_string);
           query.bindValue(5, fct_av);
            query.bindValue(6, num_hang_string);
          return query.exec();
}
bool AVION::supprimer(int cod_av)
{
   QSqlQuery query;
   query.prepare("Delete from avion where cod_av= :cod_av");
   query.bindValue(":cod_av", cod_av);
    return query.exec();
}

QSqlQueryModel * AVION:: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from avion");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cod_av"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("H_dep"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("H_arr"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("type_av"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num_av"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("fct_av"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("num_hang"));

    return model;
}


