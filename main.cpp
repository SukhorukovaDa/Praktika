#include <iostream>
#include "hehe.h"

using namespace std;



int main() {
    int a, b;
    cout << "Raschet, vvedite dva chisla i poluchite proizvedenie: " << endl;
    cin >> a >> b;
    cout << tru(a, b)<<endl;
    cout<<"This is a second function, calculation of sum: "<<endl;
    addition(a,b);
    return 0;
}
