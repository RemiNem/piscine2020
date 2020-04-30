#ifndef ARRETE_H
#define ARRETE_H


class Arrete
{
    private:
        int m_indice;
        int indice_s1;
        int indice_s2;
        float m_poids;

    public:
        ///constructeurs/destructeurs

        Arrete();
        Arrete(int indice,int s1,int s2);
        virtual ~Arrete();

        ///getters
        int get_indice() const;
        int get_indice_s1() const;
        int get_indice_s2() const;
        float get_poids() const;

        ///setters
        void set_indice_s1(int indice);
        void set_indice_s2(int indice);
        void set_indice(int i);
        void set_poids(float p);

};

#endif // ARRETE_H
