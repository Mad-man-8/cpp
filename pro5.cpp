#include <iostream>

using namespace std;

int main(){
    for (int j = 0; j < 5; j++){
        for (int i = 0; i < 5; i++){
            if (i == 2){
                continue;
                cout << "num is"; // this code is never reachable 
            }
            cout << i << endl;
        }
    }

    cout << "______________" << endl;

    for (int i = 0; i < 5; i++){
        if (i == 1){
            continue;
        }
        cout << i << endl;
    }

}