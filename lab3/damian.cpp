#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

//Alokowanie struktury wektora
struct Wektor {
    int x, y, z, w;
};

// uzupelnienie wektorow losowymi liczbami
void uzupelnienieWektorowSIMD(Wektor *wektory, int iloscLiczb) {
    int zakres = 101;
    std::srand(std::time(nullptr));

    for (int i = 0; i < iloscLiczb / 4; i++)
    {
        wektory[i].x = std::rand() % zakres;
        wektory[i].y = std::rand() % zakres;
        wektory[i].z = std::rand() % zakres;
        wektory[i].w = std::rand() % zakres;
    }
}

void uzupelnienieWektorowSISD(Wektor *wektory, int iloscLiczb) {
    int zakres = 101;
    std::srand(std::time(nullptr));

    for (int i = 0; i < iloscLiczb / 2; i++)
    {
        wektory[i].x = std::rand() % zakres;
        wektory[i].y = std::rand() % zakres;
        wektory[i].z = std::rand() % zakres;
        wektory[i].w = std::rand() % zakres;
    }
}

// dodawanie wektorów w assemblerze SIMD
double dodawanieWektorowSIMD(Wektor *v1, Wektor *v2) {
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__(
        "movdqa (%0), %%xmm0\n"
        "movdqa (%1), %%xmm1\n"
        "paddd %%xmm1, %%xmm0\n"
        :
        : "r"(v1), "r"(v2)
        : "%xmm0", "%xmm1");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// odejmowanie wektorów w assemblerze SIMD
double odejmowanieWektorowSIMD(Wektor *v1, Wektor *v2) {
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__(
        "movdqa (%0), %%xmm0\n"
        "movdqa (%1), %%xmm1\n"
        "psubd %%xmm1, %%xmm0\n"
        :
        : "r"(v1), "r"(v2)
        : "%xmm0", "%xmm1");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// mnożenie wektorów w assemblerze SIMD
double mnozenieWektorowSIMD(Wektor *v1, Wektor *v2) {
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__(
        "movdqa (%0), %%xmm0\n"
        "movdqa (%1), %%xmm1\n"
        "mulps %%xmm1, %%xmm0\n"
        :
        : "r"(v1), "r"(v2)
        : "%xmm0", "%xmm1");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// dzielenie wektorów w assemblerze SIMD
double dzielenieWektorowSIMD(Wektor *v1, Wektor *v2) {
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__(
        "movdqa (%0), %%xmm0\n"
        "movdqa (%1), %%xmm1\n"
        "divps %%xmm1, %%xmm0\n"
        :
        : "r"(v1), "r"(v2)
        : "%xmm0", "%xmm1");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}


double dodawanieWektorowSISD(Wektor *v1, Wektor *v2) {
    
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__ (
        "movl (%0), %%eax\n\t"
        "addl (%1), %%eax\n\t"
        :
        : "r"(v1), "r"(v2)
        : "%eax");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double odejmowanieWektorowSISD(Wektor *v1, Wektor *v2){
    
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__ (
        "movl (%0), %%eax\n\t"
        "subl (%1), %%eax\n\t"
        :
        : "r"(v1), "r"(v2)
        : "%eax");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double mnozenieWektorowSISD(Wektor *v1, Wektor *v2){
    
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__ (
        "movl (%0), %%eax\n\t"
        "mull (%1)\n\t"
        :
        : "r"(v1), "r"(v2)
        : "%eax");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double dzielenieWektorowSISD(Wektor *v1, Wektor *v2){
    
    auto start = std::chrono::high_resolution_clock::now();
    __asm__ __volatile__ (
    "movl %[v1], %%eax\n\t"
    "divl %[v2], %%eax\n\t"
    :
    : [v1] "m" (v1), [v2] "m" (v2)
    : "%eax");

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}


// testujemy wszystkie operacje SIMD na wektorach i zapisujemy czas
void testowanieWektorowSIMD(int iloscLiczb, int liczbaTestow, double *czasSIMD) {
    Wektor *v1 = new Wektor[iloscLiczb / 4];
    Wektor *v2 = new Wektor[iloscLiczb / 4];
    

    uzupelnienieWektorowSIMD(v1, iloscLiczb);
    uzupelnienieWektorowSIMD(v2, iloscLiczb);

    for (int i = 0; i < liczbaTestow; i++)
    {
        for (int j = 0; j < iloscLiczb / 4; j++)
        {
            czasSIMD[0] += dodawanieWektorowSIMD(&v1[j], &v2[j]);
            czasSIMD[1] += odejmowanieWektorowSIMD(&v1[j], &v2[j]);
            czasSIMD[2] += mnozenieWektorowSIMD(&v1[j], &v2[j]);
            czasSIMD[3] += dzielenieWektorowSIMD(&v1[j], &v2[j]);
        }
    }

    delete[] v1;
    delete[] v2;
    
}

// testujemy wszystkie operacje SISD na wektorach i zapisujemy czas
void testowanieWektorowSISD(int iloscLiczb, int liczbaTestow, double *czasSISD) {
    Wektor *v1 = new Wektor[iloscLiczb / 2];
    Wektor *v2 = new Wektor[iloscLiczb / 2];

    uzupelnienieWektorowSISD(v1, iloscLiczb);
    uzupelnienieWektorowSISD(v2, iloscLiczb);

    for (int i = 0; i < liczbaTestow; i++)
    {
        for (int j = 0; j < iloscLiczb / 2; j++)
        {
            czasSISD[0] += dodawanieWektorowSISD(&v1[j], &v2[j]);
            czasSISD[1] += odejmowanieWektorowSISD(&v1[j], &v2[j]);
            czasSISD[2] += mnozenieWektorowSISD(&v1[j], &v2[j]);
            czasSISD[3] += dzielenieWektorowSISD(&v1[j], &v2[j]);
        }
    }

    delete[] v1;
    delete[] v2;
}

// zapis wynikow do pliku
void zapiszWyniki(double *czasSIMD, double *czasSISD, int iloscLiczb, int liczbaTestow) {
    std::ofstream file("output.txt");
    if (!file.is_open())
        std::cout << "Nie mozna otworzyc pliku!"
                  << "\n";

    file << "Typ obliczen: SIMD / SISD \n"
         << "Liczba liczb: " << iloscLiczb << "\n"
         << "Sredni czas [x]: \n"
         << "+ " << czasSIMD[0] / liczbaTestow << " / " << czasSISD[0] / liczbaTestow << "\n"
         << "- " << czasSIMD[1] / liczbaTestow << " / " << czasSISD[1] / liczbaTestow << "\n"
         << "* " << czasSIMD[2] / liczbaTestow << " / " << czasSISD[2] / liczbaTestow << "\n"
         << "/ " << czasSIMD[3] / liczbaTestow << " / " << czasSISD[3] / liczbaTestow << "\n";
}

int main(int argc, char *argv[]) {
    double czasSIMD[4] = {};
    double czasSISD[4] = {};
    int iloscLiczb, liczbaTestow;
    
    iloscLiczb = 2048;
    liczbaTestow = 10;
    
    testowanieWektorowSIMD(iloscLiczb, liczbaTestow, czasSIMD);
    testowanieWektorowSISD(iloscLiczb, liczbaTestow, czasSISD);
    zapiszWyniki(czasSIMD, czasSISD, iloscLiczb, liczbaTestow);

    return 0;
}