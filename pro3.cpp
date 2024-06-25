#include <iostream>
#include <string>

using namespace std;

//user defined namespace
namespace aVar{
    int num1 = 8;
}

int main(){
    cout << aVar :: num1;
    return 0;
}

