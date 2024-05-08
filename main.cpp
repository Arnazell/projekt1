#include <cstdlib>
#include <iostream>
#include <chrono>
#include <fstream>
#include "algorytmy.hpp"


// Klasa wykorzystywana do mierzenia czasu
class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    std::string m_function;
    std::string m_testType;
    int m_elements;


public:
    Timer(const  std::string& function, int elements, const std::string& testType)
        : m_function(function), m_elements(elements), m_testType(testType)
    {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();  
    }

    ~Timer()
    {
        Stop();
    }

    void Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;

        // zapisz do pliku csv
        std::ofstream file;
        file.open("results.csv", std::ios_base::app);
        file << m_function << "," << m_elements << "," << ms << ","<< m_testType<<std::endl;
        file.close();

    }
};
// ----------------- ładowanie danych do tabilc ----------------------


// Laduje dane z pliku do tablicy losowo
void random(int *tab, int n)
{
    FILE *plik;
    plik=fopen("dane","r");

    for(int i=0;i<n;i++)
    {
        fscanf(plik,"%d",&tab[i]);
    }
    fclose(plik);
}

// Laduje dane z pliku do tablicy posortowane malejaco
void descending(int *tab, int n)
{
    FILE *plik;
    plik=fopen("dane","r");

    for(int i=0;i<n;i++)
    {
        fscanf(plik,"%d",&tab[i]);
    }
    fclose(plik);

    reverse_shell_sort(tab,n);
}

// Laduje dane z pliku do tablicy posortowane rosnaco
void ascending(int *tab, int n)
{
    FILE *plik;
    plik=fopen("dane","r");

    for(int i=0;i<n;i++)
    {
        fscanf(plik,"%d",&tab[i]);
    }
    fclose(plik);

    quick_sort(tab, 0, n-1);
}



// ----------------- testy ----------------------
#define SAMPLES 30
#define MAX_SAMPLE_SIZE 100000
#define DATA descending    // random, ascending, descending  
#define TESTNAME "descendingdata"
// 
#define insert 0
#define bubble 0
#define selection 0
#define quick 1
#define shell 0
#define heap 0


void Test()
{
    // parametry testu
    int step = MAX_SAMPLE_SIZE / SAMPLES;

    // wykonujemy testy dla kolejnych rozmiarów tablicy 
    for(int n=0; n<=MAX_SAMPLE_SIZE; n+=step)
    {
        // 1. dynamiczna alokacja tablicy
        int *tab = new int[n]; 

        // 2. Sortowanie i mierzenie czasu
        if (insert)
        {
            DATA(tab, n);
            {
                Timer timer("insert_sort", n, TESTNAME);
                insert_sort(tab,n);
            }
        }

        if (bubble)
        {
            DATA(tab, n);
            {
                Timer timer("bubble_sort", n, TESTNAME);
                bubble_sort(tab, n);
            }
        }
       
        if (selection)
        {
            DATA(tab, n);
            {
                Timer timer("selection_sort", n, TESTNAME);
                selection_sort(tab,n);
            }
        }
      
        if (quick)
        {
            DATA(tab, n);
            {
                Timer timer("quick_sort", n, TESTNAME);
                quick_sort(tab, 0, n-1);
            }
        }
    
        if (shell)
        {
            DATA(tab, n);
            {
                Timer timer("shell_sort", n, TESTNAME);
                shell_sort(tab,n);
            }
        }

       if (heap)
       {
            DATA(tab, n);
            {
                Timer timer("heap_sort", n, TESTNAME);
                heap_sort(tab,n);
            }
        }
    }
}
// ----------------- main + intefrejs do recznego testowania ----------------------
int main()
{
    FILE *plik;
    plik=fopen("dane","r");
    int n, wybor;
    bool run = true;

    // 1. pobranie ilości elementów
    std::cout << "Podaj n=";
    std::cin >> n;

    // 2. dynamiczna alokacja tablicy
    int *tab = new int[n]; 


    while(run)
    {
        // Wyswietl menu
        std::cout<<"Wybierz metode sortowania: "<<std::endl;
        std::cout<<"1. Insertion sort"<<std::endl;
        std::cout<<"2. Bubble sort"<<std::endl;
        std::cout<<"3. Selection sort"<<std::endl;
        std::cout<<"4. Quick sort"<<std::endl;
        std::cout<<"5. Shell sort"<<std::endl;
        std::cout<<"6. Heap sort"<<std::endl;
        std::cout<<"7. Koniec"<<std::endl;
        std::cout<<"Wybor: ";
        std::cin >> wybor;
        

        // Sprawdz czy uzytkownik wybral koniec - pomin zbedne operacje i wyjdz z petli
        if(wybor == 7)
        {
            run = false;
            break;
        }

        // 3. wczytanie danych z pliku
        for(int i=0;i<n;i++)
        {
            fscanf(plik,"%d",&tab[i]);
        }

        // 4. Wywolanie funkcji sortujacych

        switch (wybor) {
            case 1: {
                {
                    //Timer timer("insert_sort", n, "manual");
                    insert_sort(tab,n);
                }
                break;
            }
            case 2: {
                {
                    //Timer timer("bubble_sort", n, "manual");
                    bubble_sort(tab,n);
                }
                break;
            }
            case 3: {
                {
                    //Timer timer("selection_sort", n, "manual");
                    selection_sort(tab,n);
                }
                break;
            }
            case 4: {
                {
                    //Timer timer("quick_sort", n, "manual");
                    quick_sort(tab,0, n-1);
                }
                break;
            }
            case 5: {
                {
                    //Timer timer("shell_sort", n, "manual");
                    shell_sort(tab,n);
                }
                break;
            }
            case 6: {
                {
                    //Timer timer("heap_sort", n, "manual");
                    heap_sort(tab,n);
                }
                break;
            }
            default: {
                std::cout<<"Niepoprawny wybor"<<std::endl;
                break;
            }
        }
        //5. wypisanie posortowanej tablicy
        for(int i=0;i<n;i++)
        {
            std::cout<< tab[i]<<" ";
        }
        std::cout<<std::endl;
    }
}


