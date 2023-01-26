/*
purpose: Heap sort
*/

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
#ifndef heap_h
#define heap_h

/*
 * an in place heap maker, moves around contents of arr to transform it into a min-heap.
 * returns nothing.
 */
void heapify(int* arr, int size) {
    // condions on min heap
    // The root node has the minimum value. The value of each node is equal to or greater than the value of its parent node
    for (int i = 0; i < size; i++) {
        if (arr[i] > arr[(i - 1) / 2]) {
            int j = i;
            // keep swapping until parent is smaller than child

            while (arr[j] > arr[(j - 1) / 2]) {
                swap(arr[j], arr[(j - 1) / 2]);
                j = (j - 1) / 2;
            }
        }
    }
}
/*
 * copies the elements of one array arr1 to the other array:arr;
 * size is same for both arrays
 */
void Deepcopy(int* arr1, int* arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = arr1[i];
    }
}
/*swaps the elements in a given array*/

void swap(int*& arr, int pos1, int pos2) {
    int temp = arr[pos2];
    arr[pos2] = arr[pos1];
    arr[pos1] = temp;
}

/*create a quick array of size 7; with thew following values: [3,1,6,5,2,4,9]*/
int* quickArray() {
    int size = 7;
    int* ar = new int[size];

    ar[0] = 3;
    ar[1] = 1;
    ar[2] = 6;
    ar[3] = 5;
    ar[4] = 2;
    ar[5] = 4;
    ar[6] = 9;

    return ar;
}

/*
 * when cpp returns a bool, it returns cpp returns as 0/1.
 * thats confusing for me. so that it gives me true/false
 * */
string booltostring(bool b) {
    return (b == 0) ? "False" : "True";
}

/*returns the height of tree for printing purpose */
int max_height_of_tree(int size) {
    return ceil(log(size + 1) / log(2));
}

/*Display Arrays in this format [ elem,elem... ]. its easier for me to see with the brakets*/
void display_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << " [ " << array[i] << ",";
        } else if (i == size - 1) {
            cout << array[i] << " ]";
        } else {
            cout << array[i] << ",";
        }
    }
    cout << endl;
}

/* builds a heap from an array of random integers and returns the heap (a new array)*/
int* MakeHeap(int* arr, int size) {
    int* a = new int[size];
    Deepcopy(arr, a, size);
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(a, size);

    return a;
}

/* add a new elemennt  to the heap and returns value. */

int AddNode(int* arr, int& heapSize, int item) {
    ++heapSize;
    arr[heapSize] = item;
    int j = heapSize;
    while (arr[j] > arr[(j - 1) / 2]) {
        swap(arr[j], arr[(j - 1) / 2]);
        j = (j - 1) / 2;
    }
    cout << "New value add on: ";
    return j;
};
/* removes heap[itemIndex] from heap and returns the removed item's value */
int RemoveItem(int* heap, int& heapSize, int itemIndex) {
    int lc = heap[(2 * itemIndex) + 1];  // Returns the left child node.
    int rc = heap[(2 * itemIndex) + 2];  // Returns the right child node.

    int val = heap[itemIndex];
    heap[itemIndex] = heap[heapSize - 1];
    heapSize -= 1;

    return val;
}

/* removes the root from heap and returns it's value */

int RemoveRoot(int* heap, int& heapSize) {
    cout << "remove the root: ";
    return RemoveItem(heap, heapSize, 0);
};

/*check whether array is a heap or not.
 * minheap
 * The root node has the minimum value.
 * The value of each node is equal to or greater than the value of its parent node.
 */
bool IsHeap(int* Arr, int arrSize) {
    for (int i = 0; i < arrSize / 2; i++) {
        int p = Arr[(i - 1) / 2];   // Returns the parent node.
        int lc = Arr[(2 * i) + 1];  // Returns the left child node.
        int rc = Arr[(2 * i) + 2];  // Returns the right child node.

        if (lc < p && ((2 * i) + 1) < arrSize - 1) {
            return false;
        }

        if (rc < p && ((2 * i) + 2) < arrSize - 1) {
            return false;
        }
    }
    return true;
}

/*
 * The function where the actual heap sort is defined.
 * returns a sorted array ascending
 * */
int* heapSort(int* arr, int size) {
    //    build a heap from arr
    int* q = MakeHeap(arr, size);
    // swap elements
    for (int i = size - 1; i > 0; i--) {
        swap(q[0], q[i]);

        heapify(q, i);
    }
    //    return sorted array!!
    return q;
}
/*
 * this function displays the array in heap format.
 *  only up to 3 levels or 7 elements.
 *  going beyond that gives you a message.
 * */
void display_heap(int* arr, int size) {
    int hieght = max_height_of_tree(size);
    int maxWidth = pow(2, floor(log(size) / log(2)));  // total number elements in the last line.
    int maxsize = 7;
    if (size > maxsize) {
        cout << "the maximunm height of display is " << max_height_of_tree(maxsize) << " levels. (" << maxsize << " elements). Your size goes beyond that -> the size " << size << " yeilds: " << max_height_of_tree(size) << " levels.  Do you still want to continue(Y/N) ";
        char a;
        cin >> a;
        if (a == 'N' || a == 'n') {
            return;
        }
    }

    // cout << setw(5) << "lines|" << setw(5) << "count|" << endl;

    for (int lines = 0, l = size, r = 0, arrElement = 0; lines == hieght || arrElement <= size; lines++, l--, r++) {
        int count = pow(2, lines);

        // cout << setw(5) << lines << "|" << setw(5) << count << "|";

        for (int j = 0; j < count; j++, arrElement++) {
            if (arrElement == size) {
                break;
            }

            if (arrElement == 0) {  // rootelement
                cout << setw(l) << arr[arrElement];
            } else if (j == 0) {
                cout << setw(l) << arr[arrElement];
            }

            else if (j % 2 == 0) {
                cout << setw(l * 0.5)
                     << arr[arrElement];
            } else {
                cout << setw(l * (0.75))
                     << arr[arrElement];
            }
        }
        if (lines == hieght - 1) {
            break;
        }
        cout << endl;
        // cout << setw(5) << lines << "|"
        //      << setw(5) << 0 << "|";

        for (int i = 0; i < count * 2; i++) {
            if (i == size) {
                break;
            }
            if (i == 0) {
                cout << setw(l - 1)
                     << "/";
            }

            else if (i % 2 != 0) {  // odd
                cout << setw((l * 0.5))
                     << "\\";
            } else if (i % 2 == 0) {  // even
                cout << setw(l * 0.4)
                     << "/";
            }
        }
        // l *= 4;
        cout
            << endl;
    }
    cout << endl
         << endl;
}

#endif
