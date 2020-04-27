#ifndef ARRETE_H
#define ARRETE_H


class Arrete
{
    public:
        Arrete();
        Arrete(int indice,int s1,int s2);
        virtual ~Arrete();

    int m_indice;
    int indice_s1;
    int indice_s2;
    int m_poids;

};

#endif // ARRETE_H
