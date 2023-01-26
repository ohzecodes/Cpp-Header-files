
#ifndef arraySplit_h
#define arraySplit_h

#include <iostream>
#include <string>
using namespace std;

template <typename T>
string arrtostr(T* array, int size, bool a = false) {
    string s = "";
    if (array == nullptr) {
        return s;
    }

    if (a == true) {
        s += " [ ";
    }
    for (int i = 0; i < size; i++) {
        s += to_string(array[i]);
        if (i < size - 1)
            s += ",";
    }
    if (a == true) {
        s += " ] ";
    }
    return s;
}

template <typename T>
void display_array(T* array, int size, bool a = true) {
    if (array == nullptr) {
        return;
    }
    cout << " [ ";
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i < size - 1)
            cout << ",";
    }
    cout << "]";

    if (a == true) {
        cout << '\n';
    }
}

template <typename T>
void Deepcopy(T* b, T* a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = b[i];
    }
}

template <typename T>
T* Deepcopy(T* arr1, int size) {
    T* arr = new T[size];
    for (int i = 0; i < size; i++) {
        arr[i] = arr1[i];
    }
    return arr;
}

template <typename T>
T* reverse(T* A, int size) {
    T* temp = Deepcopy(A, size);

    for (int i = 0; i < size; i++) {
        temp[(size - 1) - i] = A[i];
    }
    Deepcopy(temp, A, size);
    delete[] temp;
    return A;
}

int countDelimeters(string s, char del) {
    int COUNT = 1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == del) {
            COUNT += 1;
        }
    }
    return COUNT;
}

void recursiveSplit(string* a, string s, char del, int firstfind, int count = 0) {
    // base case

    if (s.length() == firstfind) {
        a[count] = s;
        return;
    } else {
        // small problem solution
        int n = s.find_last_of(del);
        string small = s.substr(n + 1, s.length());
        a[count] = small;
        // big problem solution
        recursiveSplit(a, s.substr(0, n), del, firstfind, count + 1);
    }
}

string* recursiveSplitCaller(string s, char del) {
    if (s.length() < 2) {
        return nullptr;
    }

    int size = countDelimeters(s, del);

    string* arr = new string[size];
    recursiveSplit(arr, s, del, s.find_first_of(','), 0);

    return reverse(arr, size);
}

#endif