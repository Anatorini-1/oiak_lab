#include <cstdlib>
#include <iostream>
#include <chrono>
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


void testAddSISD(int size, int *nums);
void testSubbSISD(int size, int *nums);
void testMulSISD(int size, int *nums);
void testDivSISD(int size, int *nums);


void testAddSISD(int size, int *nums);
void testSISDForSize(int x);
void testForSize(int x);

int main(){
    std::srand(std::time(nullptr));
    of.open("test2.txt");
    testForSize(512);
    testForSize(1024);
    testForSize(2048);
    testForSize(4096);
    testForSize(8192);
    testForSize(16384);   

    testSISDForSize(512);
    testSISDForSize(1024);
    testSISDForSize(2048);
    testSISDForSize(4096);
    testSISDForSize(8192);
    testSISDForSize(16384);   
    of.close(); 

}



void testForSize(int x){
    Vector nums[x/ 4];
    of << "SIMD;";
    of << x << ";";
    for (int i=0;i<x/4;i++){
        nums[i].a = rand();
        nums[i].b = rand();
        nums[i].c = rand();
        nums[i].d = rand();

    }
    testAddSIMD(x/4,nums);
    testSubbSIMD(x/4,nums);
    testMulSIMD(x/4,nums);
    testDivSIMD(x/4,nums);

    of << "\n";

}


void testSISDForSize(int x){
    of << "SISD;";
    of << x << ";";
    int* data;
    data = new int[x];
    for (int i=0;i<x;i++){
        data[i] = (rand() % 999) + 1;
       
    }
    
    testAddSISD(x,data);
    testSubbSISD(x,data);
    testMulSISD(x,data);
    testDivSISD(x,data);
     of << "\n";
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
    of << (float)totalTime / (float)iterations << ";";
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
of << (float)totalTime / (float)iterations << ";";}

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
of << (float)totalTime / (float)iterations << ";";}
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
of << (float)totalTime / (float)iterations << ";";}


void testAddSISD(int size, int *nums){
    int res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            asm(
                "movl %[v1], %%eax\n"
                "add %[v2],%%eax\n"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
of << (float)totalTime / (float)iterations << ";";}

void testSubbSISD(int size, int *nums){
    int res;

    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            asm(
                "movl %[v1], %%eax\n"
                "sub %[v2],%%eax\n"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
of << (float)totalTime / (float)iterations << ";";}

void testMulSISD(int size, int *nums){

    int res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            
           asm(
                "movl %[v1], %%eax\n"
                "mul %[v2]\n"
                : [res] "=rm" (res)
                : [v1] "irm" (nums[j]), [v2] "irm" (nums[j+1])
                :);
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
of << (float)totalTime / (float)iterations << ";";
}
void testDivSISD(int size, int *nums){
    int res;
    int iterations = 1000;
    int totalTime =0;
    for (int i = 0;i < iterations; i++){
        int t0 = timestamp();
        for ( int j=0; j < size; j+=2){
            __asm__ __volatile__ (
            "movl %[v1], %%eax\n\t"
            "movl $0, %%edx\n"
            "divl %[v2]\n\t"
            :
            : [v1] "m" (nums[j]), [v2] "m" (nums[j+1])
            : "%eax", "%edx");
        }
        int t1 = timestamp();
        totalTime += (t1-t0);
    }
of << (float)totalTime / (float)iterations << ";";}