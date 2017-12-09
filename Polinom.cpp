#include"Polinom.h"
#include<iostream>
#include <stdexcept>


using namespace std;

Polinom pretvoriStringuPolinom(string pom);
Polinom obradiStepen( Polinom& polinom,int stepen );
void obradi( vector<string>& polinomi, vector<char>&ope );

bool daLiJeOperator( char i )
{
    if( i=='+' or i=='-' or i=='*' or i=='^' )
        return true;
    return false;
}

bool daLiJeBroj( char i )
{
     if( i>='0' and i<='9' )
        return true;
     return false;
}


Polinom::Polinom()
{
    velicina = 0;
    glava = new Cvor( 0, 0, nullptr ,nullptr );
    glava->sljedeci = rep = new Cvor( 0, 0, glava, nullptr );
}

Polinom::~Polinom()
{
    Clear();
    delete glava;
    delete rep;
}

void Polinom::Clear()
{
    Iterator it = Begin();
    while( it != End() )
        it = IzbrisiCvor( it );
}

Polinom& Polinom::operator=( const Polinom& P )
{
    if (this == &P)
        return (*this);
    else
    {
        this->Clear();
        for ( Iterator i=P.Begin();i != P.End();i++ )
        {
            this->dodajCvor( i.trenutni->koe, i.trenutni->exp );
        }
    }
    return ( *this );
}

const Polinom operator+( const Polinom& P1, const Polinom& P2 )
{
    Polinom P3;
    P3 = P1;

    for( Iterator i = P2.Begin();i != P2.End();i++ )
        P3.dodajCvor( i.trenutni->koe, i.trenutni->exp );

    return P3;
}

const Polinom operator-( const Polinom& P1, const Polinom& P2 )
{
    Polinom P3;
    P3 = P1;

    for( Iterator i = P2.Begin();i != P2.End();i++ )
        if( i.trenutni->koe>0 )
            P3.dodajCvor( -( i.trenutni->koe ), i.trenutni->exp );
        else
            P3.dodajCvor( abs( i.trenutni->koe ), i.trenutni->exp );

    for( Iterator i = P3.Begin();i != P3.End();i++ )
        if( i.trenutni->koe==0 )
            P3.IzbrisiCvor(i.trenutni);

    return P3;
}

const Polinom operator*( const Polinom& P1, const Polinom& P2 )
{
    Polinom P3;

    for(Iterator i = P1.Begin(); i != P1.End();i++ )
        for(Iterator j = P2.Begin(); j != P2.End();j++  )
            P3.dodajCvor( i.trenutni->koe*j.trenutni->koe, i.trenutni->exp+j.trenutni->exp );

    return P3;
}

ostream& operator << ( ostream &cout, const Polinom& P )
{
    if( P.velicina == 0 )
    {
        cout << "0" << endl;
        return cout;
    }
    else
    {
        if( P.Begin().trenutni->exp == 0)
            cout << P.Begin().trenutni->koe;
        else if( P.Begin().trenutni->koe == 0)
            cout << "0";
        else if( P.Begin().trenutni->exp == 1 )
        {
            if( P.Begin().trenutni->koe == 1 )
                cout << "x";
            else if ( P.Begin().trenutni->koe == -1 )
                cout << "-x";
            else
                cout << P.Begin().trenutni->koe << "x";
        }
        else
        {
            if( P.Begin().trenutni->koe == 1 )
                cout << "x^" << P.Begin().trenutni->exp;
            else if( P.Begin().trenutni->koe == -1 )
                cout << "-x^" << P.Begin().trenutni->exp;
            else
                cout << P.Begin().trenutni->koe << "x^" << P.Begin().trenutni->exp;
        }
        for( Iterator i = P.Begin().trenutni->sljedeci; i != P.End(); i++ )
            if( i.trenutni->koe > 0 )
            {
                if( i.trenutni->exp == 0 )
                    cout << "+" <<i.trenutni->koe;
                else if ( i.trenutni->exp == 1 )
                {
                    if( i.trenutni->koe == 1 )
                        cout<< "+x";
                    else
                        cout << "+" <<i.trenutni->koe << "x" ;
                }
                else
                {
                    if( i.trenutni->koe == 1)
                        cout << "+x^" << i.trenutni->exp;
                    else
                        cout << "+" << i.trenutni->koe << "x^" << i.trenutni->exp;
                }
            }
            else
            {
                if( i.trenutni->exp == 0 )
                    cout << i.trenutni->koe;
                else if ( i.trenutni->exp == 1 )
                {
                    if( i.trenutni->koe == -1 )
                        cout << "-x";
                    else
                        cout << i.trenutni->koe << "x";
                }
                else
                {
                    if( i.trenutni->koe == -1 )
                        cout<< "-x^" << i.trenutni->exp;
                    else
                        cout << i.trenutni->koe << "x^" << i.trenutni->exp;
                }
            }
    cout << endl;
    return cout;
    }
}



Polinom pretvoriStringuPolinom( string pom )
{
    string e = "", k = "";
    int exp, koe, i=0;

    Polinom P;
    while( i != pom.size() )
    {
        if( pom[i]=='x' )koe = 1;

        if(( pom[i] == '+' or pom[i] == '-' or pom[i] <= '9' or pom[i]>='0' ) and ( pom[i]!='x' ))
        {
            if(pom[i] == '+' or pom[i] == '-')
            {
                k += pom[i];
                i++;
                if( pom[i] == 'x' )
                {
                    k += "1";
                }
            }
        while(pom[i] != '+' and pom[i] != '-' and pom[i] != '*' and pom[i] != 'x' and i != pom.size())
        {
            k += pom[i];
            i++;
        }
            koe = std::atoi (k.c_str());
        }
        if(pom[i] == '+' or pom[i] == '-' or i == pom.size())
        {
            exp = 0;
        }

        else if( pom[i] == 'x' )
        {
            if( pom[i+1] == '+' or pom[i+1] == '-' or i+1 == pom.size()){exp = 1;i++;}
            else
            {
                i = i+2;
                while(i != pom.size() and pom[i] != '-' and pom[i] != '+')
                {
                    e += pom[i];
                    i++;
                }
                exp = atoi (e.c_str());
            }
        }

        else if(pom[i+2] == '+' or pom[i+2] == '-' or i+2 == pom.size())
        {
            exp = 1;i += 2;
        }
        else
        {
            i = i + 3;
            while(i != pom.size() and pom[i] != '-' and pom[i] != '+')
            {
                e += pom[i];
                i++;
            }
            exp = atoi (e.c_str());
        }
        P.dodajCvor( koe, exp );
        e = "";
        k = "";
    }

    for(Iterator i = P.Begin().trenutni; i != P.End(); i++)
        if(i.trenutni->koe == 0)
            P.IzbrisiCvor(i);

    return P;

}

int Prioritet(char c)
{
    if(c=='^')return 3;
    if(c=='*')return 2;
    if(c=='-' or  c=='+')return 1;
    else return 0;

}

istream &operator>>( istream &cin, Polinom & P)
{
    vector<string> stringPolinoma;
    vector<char> operacije;
    string p;
    cin >> p;
    P.ProvjeriUnos( p );
    P.provjeriZagrade( p );

    int i = 0;
    while( i < p.size() )
    {
        if(p[i]=='(')
        {
            if(p[i-1]==')')
                operacije.push_back('*');
            operacije.push_back('(');i++;
        }
        if(p[i]=='*')
        {
            while(!operacije.empty() and Prioritet( p[i] ) <= Prioritet( operacije.back() ))
                    obradi(stringPolinoma,operacije);
            operacije.push_back(p[i]);
            i++;
        }
        if(p[i]=='^')
        {
            operacije.push_back(p[i]);
            i++;
        }
        if(p[i]=='+')
        {
            operacije.push_back(p[i]);
            i++;
        }
        if(p[i]==')')
            {
                while(operacije.back()!='(')
                    obradi(stringPolinoma,operacije);
                operacije.pop_back();
                i++;
            }

        if(( p[i] <= '9' and p[i] >= '0' and i < p.size() ) or ( p[i] == 'x' or p[i] == '-' ))
        {
            string pom1="";
            while( i < p.size() and daLiJeOperator(p[i])!=1 and p[i]!='(' and p[i]!=')' )
            {
                pom1 += p[i];
                i++;
                if(p[i]=='x')
                {
                    stringPolinoma.push_back(pom1);operacije.push_back('*');
                    pom1="";
                }
            }
            if(p[i]==')')
            {
                stringPolinoma.push_back(pom1);
                while(operacije.back()!='(')
                    obradi(stringPolinoma,operacije);
                operacije.pop_back();
            }
            else if(daLiJeOperator(p[i]) and pom1!="")
            {
                if( !operacije.empty() and operacije.back()!='(' and (Prioritet( p[i] ) <= Prioritet( operacije.back() )) )
                {
                    stringPolinoma.push_back(pom1);
                    while(!operacije.empty() and Prioritet( p[i] ) <= Prioritet( operacije.back() ))
                        obradi(stringPolinoma,operacije);
                    operacije.push_back(p[i]);
                }
                else
                {
                    operacije.push_back(p[i]);
                    stringPolinoma.push_back(pom1);
                }
            }
            else if(pom1!="")
            {
                stringPolinoma.push_back(pom1);
            }
            else{
                   if(p[i]=='-' and stringPolinoma.size()==0)
                        {
                            stringPolinoma.push_back("0");
                        }
                   if(p[i]=='-' and p[i-1]=='(')
                        {
                            stringPolinoma.push_back("0");
                        }
                    if(p[i]=='-' and p[i-1]==')')
                        {
                            stringPolinoma.push_back("0");
                            operacije.push_back('+');
                        }
                   if(p[i]=='-' and stringPolinoma.size()!=0)
                        {
                            stringPolinoma.push_back("0");
                            operacije.push_back('+');
                        }

                operacije.push_back(p[i]);}
            i++;
       }
    }

    while(stringPolinoma.size() != 1)

        obradi(stringPolinoma,operacije);

    Polinom P1;
    P1 = pretvoriStringuPolinom(stringPolinoma.back());
    P = P1;
    return cin;
}






//////////////pretvara stringove u polinome i izvršava operacije te rezultat push-a u vector polinomi
void obradi( vector<string>& polinomi, vector<char>&ope )
{
    if( polinomi.size()==1 ) return;

    Polinom rezultat;

    Polinom P1 = pretvoriStringuPolinom( polinomi.back() );
    polinomi.pop_back();

    Polinom P2 = pretvoriStringuPolinom( polinomi.back() );
    polinomi.pop_back();

    char operacija=ope.back();
    ope.pop_back();

    if( operacija == '+' )
        rezultat = P1 + P2;
    if( operacija =='*' )
        rezultat = P1 * P2;
    if(operacija == '-' )
        rezultat = P2 - P1 ;
    if(operacija == '^' )
        rezultat = obradiStepen(P2,P1.Begin().trenutni->koe);

    string rez = rezultat.pretvoriPolinomuString();
    polinomi.push_back( rez );
}

//////////////////provjerava ispravan unos zagrada, operatora
void Polinom::ProvjeriUnos( string izraz )
{
    char pom,pom1;
    int i=0;
    while(i<izraz.size())
    {
        if( daLiJeOperator( izraz[i] ) == 1 and daLiJeOperator( izraz[i+1])==1 )
            throw invalid_argument("Neispravan unos operatora!");
        if( izraz[i]=='x' and daLiJeBroj( izraz[i+1] ) )
            throw invalid_argument("Neispravan unos ( xc )!");
        if( daLiJeBroj( izraz[i] ) and izraz[i+1] == '(' )
            throw invalid_argument("Neispravan unos ( c(ax+b) )!");
        if( izraz[i] == ')' and daLiJeBroj( izraz[i] ) )
            throw invalid_argument("Neispravan unos ( (ax+b)c)!");
        if(izraz[i] == '^' and izraz[i+1]!='(')
        {
            i++;
            while(i!=izraz.size() and daLiJeOperator( izraz[i])!=1 and izraz[i]!='(' and izraz[i]!=')')
            {
                if(izraz[i]=='x')
                    throw invalid_argument("Polinom na polinom zabranjen!");
                i++;
            }
        }
        if(izraz[i] == '^' and izraz[i+1]=='(')
        {
            while( izraz[i]!=')' and i!=izraz.size())
            {
                if(izraz[i]=='x')
                    throw invalid_argument("Polinom na polinom zabranjen!");
                i++;
            }
        }
        i++;
    }
}

///////////pretvara broj u string////////
string itoa( int a )
{
    string ss = "";
    while( a )
    {
        int x = a % 10;
        a /= 10;
        char i = '0';
        i = i + x ;
        ss = i + ss;
    }
    return ss;
}

//////provjerava broj otvorenih i zatvorenih zagrada
void Polinom::provjeriZagrade( string pom )
{
    int zagrade( 0 );
    for( int i = 0 ; i != pom.size() ; i++ )
    {
        if( pom[i] == '(' )zagrade++;
        if( pom[i] == ')' )zagrade--;
    }
    if( zagrade != 0 )
        throw invalid_argument("Pogresan unos zagrada!");
}


string Polinom::pretvoriPolinomuString()
{
    bool prvi = 1;
    string rezultat = "";

    for( Iterator i = this->Begin(); i != this->End(); i++ )
    {
        if( i.trenutni->koe == 0 )
        {
            continue;
        }
        if( prvi )
        {
            prvi=0;
            if( i.trenutni->koe < 0 )
                rezultat += "-" ;
        }
        else
            if( i.trenutni->koe < 0 )
                rezultat += "-" ;
            else
                rezultat += "+" ;

        rezultat += itoa( abs(i.trenutni->koe) );
        if( i.trenutni->exp != 0 )
        {
            rezultat += "x";
            if( i.trenutni->exp > 1 )
                {
                rezultat += "^" + itoa( i.trenutni->exp );
                }
        }

    }
    return rezultat;
}


////////////////dodaje cvor i tom prilikom ga smjesta u odgovarajuæe mjesto tako da je polinom veæ sortiran
void Polinom::dodajCvor(int koeficijent, int exponent)
{
    if(velicina == 0)
        {
            Cvor *noviCvor = new Cvor( koeficijent, exponent, glava, rep );
            rep->prethodni = glava->sljedeci = noviCvor;
            velicina++;
            return;
        }

    Cvor *tekuci = glava->sljedeci;
    while( tekuci!=rep )
    {
        if( tekuci->exp == exponent )
        {
            tekuci->koe = tekuci->koe + koeficijent;
            return;
        }
        else if( tekuci->exp < exponent )
        {
            Cvor *noviCvor = new Cvor( koeficijent, exponent, tekuci->prethodni, tekuci );
            tekuci->prethodni->sljedeci = noviCvor;
            tekuci->prethodni = noviCvor;
            velicina++;
            return;
        }
            tekuci = tekuci->sljedeci;
    }
    Cvor* noviCvor = new Cvor( koeficijent, exponent, rep->prethodni ,rep );
    rep->prethodni->sljedeci = noviCvor;
    rep->prethodni = noviCvor;
    velicina++;
}


Iterator Polinom::IzbrisiCvor(Iterator it)
{
    if( it.trenutni == nullptr )
        throw invalid_argument("Nemoguce je izbrisati!");

    it.trenutni->prethodni->sljedeci = it.trenutni->sljedeci;
    it.trenutni->sljedeci->prethodni = it.trenutni->prethodni;

    Iterator it2 ( it.trenutni->sljedeci );
    delete it.trenutni;
    velicina--;

    return it2;
}


Polinom obradiStepen( Polinom& polinom,int stepen )
{
    Polinom P4;
    P4 = polinom;

    while( stepen != 1 )
    {
        P4 = P4 * polinom;
        stepen--;
    }

    return P4;
}


