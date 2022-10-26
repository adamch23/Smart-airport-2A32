#include "avion.h"
#include<iostream>
#include<string>
using namespace std;

AVION::AVION()
{
 cod_av=0;
 H_dep=0;
 H_arr=0;
 type_av="";
 num_av=0;
 fct_av=" ";
 num_hang=0;
}
AVION::AVION(int cod_av,int H_dep,int H_arr,QString type_av,int num_av,QString fct_av,int num_hang)
{
    this->cod_av=cod_av;
    this->H_dep=H_dep;
    this->H_arr=H_arr;
    this->type_av=type_av;
    this->num_av=num_av;
    this->fct_av=fct_av;
    this->num_hang=num_hang;
}
int AVION::getcod_av(){ return cod_av;}
int AVION::getH_dep(){ return H_dep;}
int AVION::getH_arr(){ return H_arr;}
QString AVION::gettype_av(){ return type_av;}
int AVION::getnum_av(){ return num_av;}
QString AVION::getfct_av(){ return fct_av;}
int AVION::getnum_hang(){ return num_hang;}

void AVION::setcod_av(int cod_av){ this->cod_av=cod_av; }
void AVION::setH_dep(int H_dep){ this->H_dep=H_dep; }
void AVION::setH_arr(int H_arr){this->H_arr=H_arr;  }
void AVION::settype_av(QString type_av){  this->type_av=type_av; }
void AVION::setnum_av(int num_av){ this->num_av=num_av; }
void AVION::setfct_av(QString fct_av){  this->fct_av=fct_av; }
void AVION::setnum_hang(int num_hang){ this->num_hang=num_hang; }

void AVION::ajouter_Avion()
{
    cout<<"Code de l'avion:"<<endl;
    cin>>cod_av;
    cout<<"Heure de départ:"<<endl;
     cin>>H_dep;
    cout<<"Heure d'arrivée:"endl;
    cin>>H_arr;
    cout<<"Type d'avions:"<<endl;
    cin>>type_av;
    cout<<"Numéro d'avions:"<<endl;
    cin>>num_av;
    cout<<"Fonctionnement de l'avion:"<<endl;
    cin>>fct_av;
    cout<<"Numéro du hangars:"<<endl;
    cin>>num_hang;

}
