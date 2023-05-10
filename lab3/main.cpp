#include <cstdlib>
#include <iostream>

struct x{
    int a;
    int b;
    int c;
    int d;
    x(){
        a = 1;
        b = 1;
        c = 1;
        d = 1;
    }
};


extern "C"  int addInts(x* vectors, int len);

int main(){
    int len = 2048;

    x tak[len];
    for (int i=0;i<len;i++)
        tak[i] = x();
    
    std :: cout << addInts(tak,len) << std::endl;



}