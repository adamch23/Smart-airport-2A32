#include "envoi_mail.h"
#include<string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

envoi_mail::envoi_mail()
{
  destinataire="";
  mail_envoye="";
}
envoi_mail::envoi_mail(QString destinataire,QString mail_envoye)
{
    this->destinataire=destinataire;
    this->mail_envoye=mail_envoye;
}
QString envoi_mail::getdestinataire(){ return destinataire;}

QString envoi_mail::getmail_envoye(){ return mail_envoye;}

void envoi_mail::setdestinataire(QString destinataire ){  this->destinataire=destinataire; }

void envoi_mail::setmail_envoye(QString mail_envoye){  this->mail_envoye=mail_envoye; }

bool envoi_mail::ajouter_envoi_mail()
{
    QSqlQuery query;

  query.prepare("insert into envoi_mail (DESTINATAIRE, MAIL_ENVOYE) ""VALUES (:destinataire, : mail_envoye )");

           query.bindValue(0,destinataire);
           query.bindValue(1, mail_envoye);
          return query.exec();
}
