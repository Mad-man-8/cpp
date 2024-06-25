#include <iostream>
#include <string>

using namespace std;

void looping();
 
int main(){
    looping();
    return 0;
}

void looping(){
    for (int i =0; i < 5; i++){
        std :: cout << "looping" << endl;
        
    }
    cout << "end";
}