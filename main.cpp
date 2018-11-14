#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(10,10);
    for(int i = 1; i <= 10;i++){
        for(int j = 1; j <= 10; j++){
            a.set(i-1,j-1,i*j);
        }
    }
    a.print();
    return EXIT_SUCCESS;
}
