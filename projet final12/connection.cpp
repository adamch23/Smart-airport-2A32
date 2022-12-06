#include "connection.h"
Connection::Connection()
{

}

bool Connection::createconnection()
{

db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("test");
db.setUserName("Islem");//inserer nom de l'utilisateur
db.setPassword("islem01");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
 return  test;
}
 void Connection::closeconnection(){db.close();}
