#include <cstdlib>
#include <iostream>
#include <chrono>
#include <xmmintrin.h>
#include <fstream>
struct Vector{
    float a;
    float b;
    float c;
    float d;
};


using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time,float_sec>;


int res =0;
std::ofstream of;


int timestamp(){
    return Time::now().time_since_epoch().count();
}

void testAddSIMD(int size, Vector *nums);
void testSubbSIMD(int size, Vector *nums);
void testMulSIMD(int size, Vector *nums);
void testDivSIMD(int size, Vector *nums);

void testAddSISD(int size, Vector *nums);

void testForSize(int x);

int main(){
    of.open("test.txt");
    testForSize(512);
    testForSize(1024);
    testForSize(2048);
    testForSize(4096);
    testForSize(8192);
    testForSize(16384);
    

    of.close(); 

}



void testForSize(int x){
    Vector nums[x];
    of << "Typ obliczen: SIMD\n";
    of << "Liczba liczb: " << x << "\n";
    of << "Sredni czas[x]: \n";
    for (int i=0;i<x;i++){
        nums[i].a = rand();
        nums[i].b = rand();
        nums[i].c = rand();
        nums[i].d = rand();

    }
    testAddSIMD(x,nums);
    testSubbSIMD(x,nums);
    testMulSIMD(x,nums);
    testDivSIMD(x,nums);

    of << "\n\n\n";
}


void testAddSIMD(int size, Vector *nums){
    Vector res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            asm(
                "movups %[v1], %%xmm0\n"
                "movups %[v2], %%xmm1\n"
                "addps %%xmm0, %%xmm1"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
    of << "+ " << (float)totalTime / (float)iterations << std::endl;
}

void testSubbSIMD(int size, Vector *nums){
    Vector res;

    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            asm(
                "movups %[v1], %%xmm0\n"
                "movups %[v2], %%xmm1\n"
                "subps %%xmm0, %%xmm1"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
    of << "- " << (float)totalTime / (float)iterations << std::endl;
}

void testMulSIMD(int size, Vector *nums){

    Vector res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            
            asm(
                "movups %[v1], %%xmm0\n"
                "movups %[v2], %%xmm1\n"
                "subps %%xmm0, %%xmm1"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
    of << "* " << (float)totalTime / (float)iterations << std::endl;
}
void testDivSIMD(int size, Vector *nums){
    Vector res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            asm(
                "movups %[v1], %%xmm0\n"
                "movups %[v2], %%xmm1\n"
                "divps %%xmm0, %%xmm1"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
    of << "/ " << (float)totalTime / (float)iterations << std::endl;
}


void testAddSISD(int size, Vector *nums){
  //TODO   
}


