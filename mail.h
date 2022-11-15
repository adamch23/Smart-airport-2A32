#ifndef MAIL_H
#define MAIL_H

#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
class mail
{
public:
    mail();
    mail(QString,QString);

    QString getadresse_mail();
    QString getmdp();

    void setadresse_mail(QString);
    void setmdp(QString);


    bool ajouter_adr_mail();

    //bool rechercher_adr_mail(QString);


private:
    QString adresse_mail;
    QString mdp;

};

#endif // MAIL_H
