#ifndef POLINOM_H
#define POLINOM_H
#include<iostream>
#include<vector>


using namespace std;

//struktura cvor sadzi vrijednost koeficijenta, eksponenta i pokazivac na sljedeci i prethodni
struct Cvor{
    int koe;
    int exp;

    Cvor *sljedeci;
    Cvor *prethodni;

    Cvor(int k, int e, Cvor* pre, Cvor* slje):koe{k}, exp{e}, prethodni{pre}, sljedeci{slje}{};
};

//interator koji pokazuje na trenutni èvor/
class Iterator {
    public:
    Cvor *trenutni;
     Iterator(Cvor *trenutni = nullptr):trenutni{trenutni}{}
     Iterator operator++(int)
     {
       Iterator stari = *this;
       trenutni = trenutni->sljedeci;
       return stari;
     }
     Iterator &operator++()
     {
       trenutni = trenutni->sljedeci;
       return *this;
     }
     Iterator operator--(int)
     {
       Iterator stari = *this;
       trenutni = trenutni->prethodni;
       return stari;
     }
     Iterator &operator--()
     {
       trenutni = trenutni->prethodni;
       return *this;
     }
     inline bool operator!=(const Iterator it) { return trenutni != it.trenutni; }
     friend class Polinom;
   };

class Polinom
{
    private:
        Cvor* glava;
        Cvor* rep;
        int velicina;

    public:

        Polinom();
        ~Polinom();
        Polinom& operator=( const Polinom& P );


        friend const Polinom operator+( const Polinom& P1, const Polinom& P2 );
        friend const Polinom operator-( const Polinom& P1, const Polinom& P2 );
        friend const Polinom operator*( const Polinom& P1, const Polinom& P2 );
        friend Polinom obradiStepen( Polinom& polinom,int stepen );
        friend ostream& operator<<( ostream &cout, const Polinom& P );
        friend istream& operator>>( istream &cin, Polinom & P );
        friend Polinom pretvoriStringuPolinom( string pom );
        friend void obradi( vector<string>& polinomi, char operacija );

        Iterator Begin() const { return Iterator( glava->sljedeci ); }
        Iterator End() const { return Iterator( rep ); }
        Iterator IzbrisiCvor( Iterator it );

        void Oduzmi( Polinom& P1, Polinom P2 );
        void dodajCvor( int koeficijent, int exponent );
        void ParsirajPolinom( string izraz );
        void ProvjeriUnos( string izraz );
        void IzbrisiSaPocetka() { IzbrisiCvor( Begin() ); }
        void IzbrisiSaKraja() { IzbrisiCvor( --End() ); }
        void provjeriZagrade( string pom );
        void Clear();

        string pretvoriPolinomuString();
};

#include"Polinom.cpp"
#endif // POLINOM_H
