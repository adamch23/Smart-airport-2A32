#include "vols.h"
#include<string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QCalendarWidget>
#include <QObject>
#include <iostream>
#include <QMessageBox>


VOLS::VOLS()
{
    CODEDEVOL=0;
    NOMDUVOL="";
    DATEDEDECOLAGE="";
    DATEDARRIVAGE="";
    DUREEDUVOL="";
    TRANSIT="";
}
VOLS::VOLS(int CODEDEVOL,QString NOMDUVOL,QString DATEDEDECOLAGE,QString DATEDARRIVAGE,QString DUREEDUVOL,QString TRANSIT)
{

    this->CODEDEVOL=CODEDEVOL;
     this->NOMDUVOL=NOMDUVOL;
     this->DATEDEDECOLAGE=DATEDEDECOLAGE;
     this->DATEDARRIVAGE=DATEDARRIVAGE;
     this->DUREEDUVOL=DUREEDUVOL;
     this->TRANSIT=TRANSIT;
}
int VOLS::getCODEDEVOL(){ return CODEDEVOL;}
QString VOLS::getNOMDUVOL(){ return NOMDUVOL;}
QString VOLS::getDATEDEDECOLAGE(){ return DATEDEDECOLAGE;}
QString VOLS::getDATEDARRIVAGE(){ return DATEDARRIVAGE;}
QString VOLS::getDUREEDUVOL(){ return DUREEDUVOL;}
QString VOLS::getTRANSIT(){ return TRANSIT;}


void VOLS::setCODEDEVOL(int CODEDEVOL){ this->CODEDEVOL=CODEDEVOL; }
void VOLS::setNOMDUVOL(QString NOMDUVOL){ this->NOMDUVOL=NOMDUVOL; }
void VOLS::setDATEDEDECOLAGE(QString DATEDEDECOLAGE){this->DATEDEDECOLAGE=DATEDEDECOLAGE;  }
void VOLS::setDATEDARRIVAGE(QString DATEDARRIVEE){  this->DATEDARRIVAGE=DATEDARRIVEE; }
void VOLS::setDUREEDUVOL(QString DUREEDUVOL){ this->DUREEDUVOL=DUREEDUVOL; }
void VOLS::setTRANSIT(QString TRANSIT){  this->TRANSIT=TRANSIT; }


bool VOLS::ajoutervols()
{
   QString res=QString::number(CODEDEVOL);
    QSqlQuery query;

  query.prepare("insert into VOLs (CODEDEVOL, NOMDUVOL, DATEDEDECOLAGE, DATEDARRIVAGE , DUREEDUVOL , TRANSIT ) "
                "VALUES (:CODEDEVOL, : NOMDUVOL, :DATEDEDECOLAGE , :DATEDARRIVAGE , :DUREEDUVOL , :TRANSIT )");
          /*query.bindValue(":cod_av", cod_av_string);
          query.bindValue(":H_dep", H_dep_string);
          query.bindValue(":H_arr", H_arr_string);
          query.bindValue(":type_av", type_av);
          query.bindValue(":num_av", num_av_string);
          query.bindValue(":fct_av", fct_av);
           query.bindValue(":num_hang", num_hang_string);*/
           query.bindValue(0, CODEDEVOL);
           query.bindValue(1, NOMDUVOL);
           query.bindValue(2, DATEDEDECOLAGE);
           query.bindValue(3, DATEDARRIVAGE);
           query.bindValue(4, DUREEDUVOL);
           query.bindValue(5, TRANSIT);

          return query.exec();
}
bool VOLS::supprimervols(QString CODEDEVOL)
{
   QSqlQuery query;
   query.prepare("Delete from VOLS where CODEDEVOL= :CODEDEVOL");
   query.bindValue(":CODEDEVOL", CODEDEVOL);
    return query.exec();
}

QSqlQueryModel * VOLS:: affichervols()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from VOLS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEDEVOL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMDUVOL"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEDEDECOLAGE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEDARRIVEE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DUREEDUVOL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TRANSIT"));

    return model;
}


QSqlQueryModel* VOLS::affichercalendriervols()
{QSqlQueryModel* model=new QSqlQueryModel();





    model->setQuery("select * from VOLS where DATE1 like (17/11/22)");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEDEVOL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMDUVOL"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEDEDECOLAGE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEDARRIVEE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DUREEDUVOL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TRANSIT"));

return model;
}


bool VOLS::modifiervols()
{
    QSqlQuery query;
    QString res=QString::number(CODEDEVOL);

  query.prepare("update vols set CODEDEVOL=:CODEDEVOL ,NOMDUVOL=:NOMDUVOL ,DUREEDUVOL=:DUREEDUVOL,DATEDEDECOLAGE=:DATEDEDECOLAGE,DATEDARRIVAGE=:DATEDARRIVAGE,TRANSIT=:TRANSIT  where CODEDEVOL= :CODEDEVOL");
  query.bindValue(":CODEDEVOL", res);
  query.bindValue(":NOMDUVOL", NOMDUVOL);
  query.bindValue(":DUREEDUVOL", DUREEDUVOL);
  query.bindValue(":DATEDEDECOLAGE", DATEDEDECOLAGE);
   query.bindValue(":DATEDARRIVAGE", DATEDARRIVAGE);
  query.bindValue(":TRANSIT", TRANSIT);


    return query.exec();
}
QSqlQueryModel* VOLS::trievols()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select CODEDEVOL,NOMDUVOL,DUREEDUVOL,DATEDEDECOLAGE,DATEDARRIVAGE,TRANSIT  from vols ORDER BY CODEDEVOL asc");


        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEDEVOL"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMDUVOL"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEDEDECOLAGE"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEDARRIVEE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("DUREEDUVOL"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("TRANSIT"));


    return model;
}
QSqlQueryModel* VOLS::trie2vols()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select CODEDEVOL,NOMDUVOL,DUREEDUVOL,DATEDEDECOLAGE,DATEDARRIVAGE,TRANSIT  from vols ORDER BY CODEDEVOL desc");


        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODEDEVOL"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMDUVOL"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEDEDECOLAGE"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEDARRIVEE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("DUREEDUVOL"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("TRANSIT"));


    return model;
}

QSqlQueryModel *VOLS::recherchervols(QString CODEDEVOL)
{

    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VOLS WHERE CODEDEVOL LIKE'%"+CODEDEVOL+"%'");
        return model;
}

QStringList VOLS::listeDUREEDUVOL(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from VOLS");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int VOLS::calcul_DUREEDUVOL(QString CODEDEVOL,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from VOLS  WHERE "+val+"=:CODEDEVOL");
     query.bindValue(":CODEDEVOL", CODEDEVOL );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}


