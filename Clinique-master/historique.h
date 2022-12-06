#ifndef HISTORIQUE.h
#define HISTORIQUE.h
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class historique
{
private:
    QString operation;

public:
    historique();
    historique(QString);
    QSqlQueryModel * afficher_historique();
    QSqlQueryModel*affichertriAZ();
};

#endif // HISTORIQUE.h

