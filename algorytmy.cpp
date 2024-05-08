#include "algorytmy.hpp"

// insertion sort  - GOTOWE
void insert_sort(int *tab, int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = tab[j];
        // Wstaw tab[j] w posortowany ciąg tab[0..j-1]
        int i = j - 1;
        while (i >= 0 && tab[i] > key)
        {
            tab[i + 1] = tab[i];
            i = i - 1;
        }
        tab[i + 1] = key;

    }
}

// bubble sort - GOTOWE
void bubble_sort(int *tab, int n) 
{
    int i,j,p;
    
    for(j = n - 1; j > 0; j--)
    {
    p = 1;
    for(i = 0; i < j; i++)
        if(tab[i] > tab[i + 1])
        {
        int temp = tab[i];
        tab[i] = tab[i + 1];
        tab[i + 1] = temp;
        p = 0;
        }
    if(p) break;
    }
}

// selection sort - GOTOWE
void selection_sort(int *tab, int n) 
{
    int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (tab[j] < tab[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
        {
            int temp = tab[min_idx];
            tab[min_idx] = tab[i];
            tab[i] = temp;

        }
    }
}

// quick sort
int partition(int *tab, int p, int r)
{
    int x = tab[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (tab[j] <= x)
        {
            i++;
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    int temp = tab[i + 1];
    tab[i + 1] = tab[r];
    tab[r] = temp;
    return i + 1;
}

void quick_sort(int *tab, int p, int r)
{
    if (p < r)
    {
        int q = partition(tab, p, r);
        quick_sort(tab, p, q - 1);
        quick_sort(tab, q + 1, r);
    }
}


// shell sort
void shell_sort(int *tab, int n)
{
    int h;
    // Wyznaczy wartość początkowego przesunięcia
    for(h = 1; h < n; h = 3 * h + 1);
    h /= 9;
    if(!h) h++;

    // sortujemy tablicę
    for (h; h > 0; h /= 2)
    {

        for (int i = h; i < n; i += 1)
        {
            int temp = tab[i];
 
            int j;            
            for (j = i; j >= h && tab[j - h] > temp; j -= h)
                tab[j] = tab[j - h];
             
            tab[j] = temp;
        }
    }
}

// heap sort
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2

void maxheapify(int *tab, int n, int i)
{
    int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);

    if (l < n && tab[l] > tab[largest])
    {
        largest = l;
    }
    if (r < n && tab[r] > tab[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        int temp = tab[i];
        tab[i] = tab[largest];
        tab[largest] = temp;
        maxheapify(tab, n, largest);
    }
}

void build_maxheap(int *tab, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxheapify(tab, n, i);
    }
}

void heap_sort(int *tab, int n)
{
    build_maxheap(tab, n);
    for (int i = n - 1; i > 0; i--)
    {
        int temp = tab[0];
        tab[0] = tab[i];
        tab[i] = temp;
        maxheapify(tab, i, 0);
    }
}

// reverse quick sort
void reverse_shell_sort(int *tab, int n)
{
    int h;
    // Wyznaczy wartość początkowego przesunięcia
    for(h = 1; h < n; h = 3 * h + 1);
    h /= 9;
    if(!h) h++;

    // sortujemy tablicę
    for (h; h > 0; h /= 2)
    {

        for (int i = h; i < n; i += 1)
        {
            int temp = tab[i];
 
            int j;            
            for (j = i; j >= h && tab[j - h] < temp; j -= h)
                tab[j] = tab[j - h];
            tab[j] = temp;
        }
    }
}