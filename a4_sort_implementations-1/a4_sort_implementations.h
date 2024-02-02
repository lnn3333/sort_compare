// a4_sort_implementations.h
/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <LINH NGUYEN>
// St.# : <301457504>
// Email: <lna33@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////
#pragma once

#include "a4_base.h"
#include<ctime>
using namespace std;
template <typename T>
bool is_sorted(vector<T> &v){
    if(v.size()<=1){
        return true;
    }
    else{
    for (int i=0; i< v.size()-1;i++){
        if(v[i]>v[i+1])
        {
         return false;
        }
    }
    }
    return true;
};

template <typename T>
SortStats bubble_sort(vector<T> &v){
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
     cout << "It took bbl s " << elapsed_cpu_time_sec << " seconds to do stuff.\n";
    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};
template <typename T>
ulong insertion_sorthelp(vector<T> &v, int low, int high){
     ulong num_comps = 0;
    for (int i = low+1; i <= high; i++) {
        T key = v[i]; // Current element to be inserted
        int j = i; 
       
        while ((j >low) && v[j-1] > key) {
            v[j ] = v[j-1]; 
            j--;
            num_comps++; // Increment the comparison counter
        }

        v[j ] = key; // Insert the current element at its correct position
    }
return num_comps;
}
template <typename T>
SortStats insertion_sort(vector<T> &v) {
    ulong num_comps = 0; // Initialize the comparison counter to 0
    clock_t start = clock(); // Get the starting time

    num_comps=insertion_sorthelp(v,0,v.size()-1);
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds

    return SortStats{"Insertion sort", v.size(), num_comps, elapsed_cpu_time_sec};
}
template <typename T>
SortStats selection_sort(vector<T> &v){
    ulong num_comps = 0; // Initialize the comparison counter to 0
    clock_t start = clock(); // Get the starting time
    int i, j, m;
    int n =v.size();
    for( i=0; i<n-1;i++){
        m=i;
        for (j=i+1;j<n;j++){
            if(v[j]<v[m]){
                m=j;
                num_comps++;
            }
        }
        if (m!=i){
            swap(v[m],v[i]);
        }
    }
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
    return SortStats{"Selection sort", v.size(), num_comps, elapsed_cpu_time_sec};
};
template<typename T>
ulong merge(vector<T>&left, vector<T>&right, vector<T>&v, ulong& com){
   
    int l= left.size();
    int r= right.size();
    int i=0;
    int j=0;
    int k=0;
    while (j<l && k<r)
    {
        if(left[j]<=right[k]){
            v[i]=left[j];
            j++;
        }
        else{
            v[i]=right[k];
            k++;
        }
        i++;
        com++;
    }
    while (j<l)
    {
    v[i]=left[j];
    i++;j++;
    }
    while (k<r)
    {
    v[i]=right[k];
    i++;k++;
    }
    
    return com;
}
template <typename T>
SortStats merge_sort(vector<T> &v){
    ulong num_comps = 0; // Initialize the comparison counter to 0
    clock_t start = clock(); // Get the starting time
    if (v.size()<=1){
        clock_t end = clock(); // Get the ending time
        double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
        return SortStats{"Merge sort", v.size(), num_comps, elapsed_cpu_time_sec};
    }
    // chia hai vecotr
    else{
        vector<T> left;
        vector<T> right;
        int m=v.size()/2;
        for( size_t i=0;i<m;i++){
            left.push_back(v[i]);
        }
        for( size_t i=0;i<(v.size()-m);i++){
            right.push_back(v[m+i]);
        }
        merge_sort(left);
        merge_sort(right);
        num_comps=merge(left,right,v, num_comps);

    }
  
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
    return SortStats{"Merge sort", v.size(), num_comps, elapsed_cpu_time_sec};
};

template <typename T>
int partition(vector<T>&v, int low, int high, T pivot, ulong& num_c){
   int i = low;
	int j = low;
	while( i <= high){
		if(v[i] > pivot){
			i++;
            num_c++;
		}
		else{
			swap(v[i],v[j]);
			i++;
			j++;
		}
	}
	return j-1;
};
template <typename T>
ulong quickhelp_sort(vector<T> &v, int low, int high){ 
    ulong num_comps=0;
    if (low<high){
        T pivot=v[high];
        int p= partition(v,low,high,pivot, num_comps );
        num_comps+=quickhelp_sort(v,low,p-1);
        num_comps+=quickhelp_sort(v,p+1,high);
    }
    return num_comps;
     
};
template<typename T>
SortStats quick_sort(vector<T> &v){
    ulong num_comps = 0;
    clock_t start = clock(); // Get the starting time
    num_comps=quickhelp_sort(v,0,v.size()-1);
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
    return SortStats{"Quick sort", v.size(), num_comps, elapsed_cpu_time_sec};
};

template <typename T>
SortStats shell_sort(vector<T> &v){
    ulong num_comps = 0; // Initialize the comparison counter to 0
    clock_t start = clock(); // Get the starting time
    
    for (int gap=v.size()/2;gap>0;gap/=2){
        for(int i = gap; i < v.size(); i ++){
        T tem=v[i];
        int j;
        for (j=i;(j>=gap) && v[j-gap] > tem;j-=gap){
            v[j] = v[j-gap];
            num_comps++;
        }
            v[j]=tem;
        
        }
    }
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
    return SortStats{"Shell sort", v.size(), num_comps, elapsed_cpu_time_sec};
    
};
//cal median of array
template <typename T>
ulong iquicksort_help(vector<T>& v,int low, int high){
    ulong num_comps=0;
    ulong num_p=0;
    if(high-low+1<10){
        num_comps=insertion_sorthelp(v,low,high);
    }
    else {
        T pivot=v[high];
        int p= partition(v,low,high,pivot,num_p );
        num_comps+= iquicksort_help(v,low,p-1);
        num_comps+= iquicksort_help(v,p+1,high);
        num_comps+=num_p;
    }

    return num_comps;
     
}
template <typename T>
SortStats iquick_sort(vector<T> &v){
   ulong num_comps = 0;
    // Initialize the comparison counter to 0
    clock_t start = clock(); // Get the starting time
    num_comps=iquicksort_help(v,0,v.size()-1);
    clock_t end = clock(); // Get the ending time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; // Calculate the elapsed CPU time in seconds
    return SortStats{"Iquicksort sort", v.size(), num_comps, elapsed_cpu_time_sec};
};



