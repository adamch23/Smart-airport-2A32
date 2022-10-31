#include "bagage.h"


Bagage::Bagage()
{


    type_bagage="";
    nom="";
    prenom="";
    id_bagage=0;
    dimension_bagage=0;
    poids=0;

};
Bagage::Bagage(int id_bagage,QString type_bagage,float dimension_bagage,QString nom,QString prenom,float poids )
{
this->id_bagage=id_bagage;
this->type_bagage=type_bagage;
this->dimension_bagage=dimension_bagage;
this->nom=nom;
this->prenom=prenom;
this->poids=poids;
};



int Bagage::get_id_bagage() {return id_bagage;}
QString Bagage::get_type_bagage(){return type_bagage;}
float Bagage::get_dimension_bagage(){return dimension_bagage;}
QString Bagage:: get_nom(){return  nom;}
QString Bagage::get_prenom(){return prenom;}
float Bagage::get_poids() {return poids;}

void  set_id_bagage(int);
void  set_type_bagage(QString);
void  set_dimension_bagage(float);
void  set_nom( QString);
void  set_prenom(QString);
void  set_poids(float);

void Bagage::set_id_bagage(int id_bagage){this->id_bagage=id_bagage;}
void Bagage::set_type_bagage(QString type_bagage){this->type_bagage=type_bagage;}
void Bagage::set_dimension_bagage(float dimension_bagage){this->dimension_bagage=dimension_bagage;}
void Bagage::set_nom(QString nom){this->nom=nom;}
void Bagage::set_prenom(QString prenom){this->prenom=prenom;}
void Bagage::set_poids(float poids){this->poids=poids;}

bool Bagage::ajouter()
{//bool test=false;



          query.prepare("INSERT INTO BAGAGE (ID_BAGAGE, TYPE_BAGAGE,DIMENSION_BAGAGE, NOM,PRENOM,POIDS) "
                        "VALUES (:ID_BAGAGE, :TYPE_BAGAGE,:DIMENSION_BAGAGE,:NOM,:PRENOM, :POIDS )");
          query.bindValue(":ID_BAGAGE", id_bagage);
          query.bindValue(":TYPE_BAGAGE", type_bagage);
          query.bindValue(":DIMENSION_BAGAGE",dimension_bagage);
          query.bindValue(":NOM", nom);
          query.bindValue(":PRENOM",prenom);
          query.bindValue(":POIDS", poids);
          return query.exec();
};
