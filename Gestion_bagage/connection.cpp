#include"connection.h"
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Gestion_bagage");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("system");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return test;
}
void Connection::closeConnection(){db.close();}
