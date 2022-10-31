#ifndef BAGAGE_H
#define BAGAGE_H
#include <QString>


class Bagage
{public:
    Bagage();
    Bagage(int,QString,float,QString,QString,float);
   int  get_id_bagage();
    QString  get_type_bagage();
    float get_dimension_bagage();
    QString get_nom();
    QString get_prenom();
    float get_poids();



    void  set_id_bagage(int);
    void  set_type_bagage(QString);
    void  set_dimension_bagage(float);
    void  set_nom( QString);
    void  set_prenom(QString);
    void  set_poids(float);


    bool ajouter();

private:
    QString type_bagage,nom,prenom;
    int id_bagage;
    float dimension_bagage ,poids;
};
#endif // BAGAGE_H
