#include<iostream>
#include<cstdlib>
#include <stdexcept>

#include "Polinom.h"

using namespace std;

int main()
{

    Polinom P;
    try
    {
        cout <<"Unesite polinom: ";
        cin >> P;
        cout << P;
    }
    catch ( const exception& e )
    {
        cout<<e.what();
    }
}
