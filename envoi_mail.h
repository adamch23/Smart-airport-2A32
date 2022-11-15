#ifndef ENVOI_MAIL_H
#define ENVOI_MAIL_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>

class envoi_mail
{
public:
    envoi_mail();
    envoi_mail(QString,QString);

    QString getdestinataire();
    QString getmail_envoye();

    void setdestinataire(QString);
    void setmail_envoye(QString);

    bool ajouter_envoi_mail();


private:
    QString destinataire;
    QString mail_envoye;

};

#endif // ENVOI_MAIL_H
