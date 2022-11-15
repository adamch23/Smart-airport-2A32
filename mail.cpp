#include "mail.h"
#include<string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

mail::mail()
{
 adresse_mail="";
 mdp="";
}

mail::mail(QString adresse_mail,QString mdp)
{
    this->adresse_mail=adresse_mail;
    this->mdp=mdp;
}
QString mail::getadresse_mail(){ return adresse_mail;}

QString mail::getmdp(){ return mdp;}



void mail::setadresse_mail(QString adresse_mail ){  this->adresse_mail=adresse_mail; }

void mail::setmdp(QString mdp){  this->mdp=mdp; }

 bool mail::ajouter_adr_mail()
 {
     QSqlQuery query;

   query.prepare("insert into mail (ADRESSE_MAIL, MDP) ""VALUES (:adresse_amil, : mdp )");

            query.bindValue(0, adresse_mail);
            query.bindValue(1, mdp);
           return query.exec();
 }
/* bool mail::rechercher_adr_mail(QString adresse_mail)
 {
     QSqlQuery query;
     query.prepare("Select *from mail where ADRESSE_MAIL TYPE AS "+adresse_mail+"");
     query.bindValue(":ADRESSE_MAIL", adresse_mail);
      return query.exec();
 }*/
