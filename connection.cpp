#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("Islem");//inserer nom de l'utilisateur
db.setPassword("islem01");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
