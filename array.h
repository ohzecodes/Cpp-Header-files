#include <iostream>

#include "maths.h"
#ifndef array_h
#define array_h

int* Slice(int* arr, int size, int start, int end, int& newsize) {
    int* b = new int[newsize];
    if (start >= 0 && start < size && end > 0 && end < size) {
        for (int j = 0, i = start; j < newsize || i < end; j++, i++) {
            b[j] = arr[i];
        }
    }
    return b;
}

/*b transfers to a */
void Deepcopy(int* b, int* a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = b[i];
    }
}

int* Deepcopy(int* arr1, int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = arr1[i];
    }
    return arr;
}

/* mergeSort functions answer from homework4Sol */
int** Split(int* arr, int size, int indexToSplitAt) {
    int** splits = new int*[2];  //items to the left of indexToSplitAt, items to the right of indexToSplitAt, neither includes arr[indexToSplitAt]

    if (indexToSplitAt != 0) {
        splits[0] = new int[indexToSplitAt];  //items from arr[0] to arr[indexToSplitAt-1] (inclusive)
        for (int i = 0; i < indexToSplitAt; i++) {
            splits[0][i] = arr[i];
        }
    } else {
        splits[0] = nullptr;
    }

    if (size - indexToSplitAt != 0) {
        splits[1] = new int[size - indexToSplitAt];  // items from arr[indexToSplitAt + 1] to arr[size - 1] (inclusive)
        for (int i = indexToSplitAt; i < size; i++) {
            splits[1][i - indexToSplitAt] = arr[i];
        }
    } else {
        splits[1] = nullptr;
    }

    return splits;
}

int* MergeInOrder(int* left, int lSize, int* right, int rSize) {
    int i, j, k;
    int* merged = new int[lSize + rSize];
    i = j = k = 0;

    while (i < lSize && j < rSize) {
        if (left[i] <= right[j]) {
            merged[k++] = left[i++];
        } else {
            merged[k++] = right[j++];
        }
    }
    //remaining items in left, just put in merge since left is already sorted
    while (i < lSize) {
        merged[k++] = left[i++];
    }
    // similarly do for right, in case right has items remaining to place in the merged array
    while (j < rSize) {
        merged[k++] = right[j++];
    }

    if (left) {
        delete[] left;
        left = nullptr;
    }
    if (right) {
        delete[] right;
        right = nullptr;
    }
    return merged;
}

int* MergeSort(int* arr, int size) {
    if (size == 0) {
        return nullptr;
    } else if (size == 1) {
        int* baseSolution = new int[size];
        baseSolution[0] = arr[0];

        delete[] arr;
        arr = nullptr;
        return baseSolution;
    } else if (size == 2) {
        int* baseSolution = new int[size];

        if (arr[0] < arr[1]) {
            baseSolution[0] = arr[0];
            baseSolution[1] = arr[1];
        } else {
            baseSolution[0] = arr[1];
            baseSolution[1] = arr[0];
        }
        // cout << "w";
        delete[] arr;
        arr = nullptr;
        return baseSolution;
    } else {
        //split arr into 2 (somewhat equal) halves, left and right
        int** slices = Split(arr, size, size / 2);
        // left = slices[0];
        int leftSize = size / 2;
        // right = slices[1];
        int rightSize = size - leftSize;

        slices[0] = MergeSort(slices[0], leftSize);
        slices[1] = MergeSort(slices[1], rightSize);

        int* result = MergeInOrder(slices[0], leftSize, slices[1], rightSize);

        return result;
    }
}

// quick sort functions from homework 4 -- swap, Partition, SplitPivot, QuickMerge,QuickSort
void Swap(int* arr, int pos1, int pos2) {
    int temp = arr[pos2];
    arr[pos2] = arr[pos1];
    arr[pos1] = temp;
}

int Partition(int* arr, int size) {
    int pIndex = 0;
    int low = 1;
    int high = size - 1;

    while (low <= high) {
        while (low < size && arr[low] <= arr[pIndex]) {
            low++;
        }
        while (high >= 0 && arr[high] > arr[pIndex]) {
            high--;
        }
        if (low < high) {
            Swap(arr, low, high);
        }
    }
    Swap(arr, pIndex, high);
    return high;
}

int** SplitPivot(int* arr, int size, int indexToSplitAt) {
    int** splits = new int*[2];  //items to the left of indexToSplitAt, items to the right of indexToSplitAt, neither includes arr[indexToSplitAt]

    if (indexToSplitAt != 0) {
        splits[0] = new int[indexToSplitAt];  //items from arr[0] to arr[indexToSplitAt-1] (inclusive)
        for (int i = 0; i < indexToSplitAt; i++) {
            splits[0][i] = arr[i];
        }
    } else {
        splits[0] = nullptr;
    }

    if (size - indexToSplitAt - 1 != 0) {
        splits[1] = new int[size - indexToSplitAt - 1];  // items from arr[indexToSplitAt + 1] to arr[size - 1] (inclusive)
        for (int i = indexToSplitAt + 1; i < size; i++) {
            splits[1][i - (indexToSplitAt + 1)] = arr[i];
        }
    } else {
        splits[1] = nullptr;
    }

    return splits;
}

int* QuickMerge(int* left, int lSize, int* right, int rSize, int pivotItem) {
    // this merge assumes all items in left are smaller than the FIRST item in right
    int i, j, k;
    int* merged = new int[lSize + rSize + 1];  // extra 1 for to place the pivot item
    i = j = k = 0;

    //items in left, just put in merge since they are smaller than FIRST item in right
    while (i < lSize) {
        merged[k++] = left[i++];
    }

    //place the pivot item in merge
    merged[k++] = pivotItem;

    //items in right, just put in merge after pivot since they are greater than last item in left
    while (j < rSize) {
        merged[k++] = right[j++];
    }

    return merged;
}

int* QuickSort(int* arr, int size) {
    if (size == 0) {
        return nullptr;
    } else if (size == 1) {
        int* baseSolution = new int[size];
        baseSolution[0] = arr[0];

        delete[] arr;
        arr = nullptr;
        return baseSolution;
    } else if (size == 2) {
        int* baseSolution = new int[size];

        if (arr[0] < arr[1]) {
            baseSolution[0] = arr[0];
            baseSolution[1] = arr[1];
        } else {
            baseSolution[0] = arr[1];
            baseSolution[1] = arr[0];
        }

        delete[] arr;
        arr = nullptr;
        return baseSolution;
    } else {
        //Display(arr, size);
        int pivIndex = Partition(arr, size);  //place pivot in place and return its index
        int pivItem = arr[pivIndex];          //backup the pivot item itself
        //cout << pivIndex << "," << pivItem << endl;
        int** slices = SplitPivot(arr, size, pivIndex);
        // left = slices[0];//items to the left of pivot
        int leftSize = pivIndex;  //not including pivot
        // right = slices[1];//items to the right of pivot
        int rightSize = size - leftSize - 1;  //not including pivot hence the extra -1

        slices[0] = QuickSort(slices[0], leftSize);
        slices[1] = QuickSort(slices[1], rightSize);
        int* result = QuickMerge(slices[0], leftSize, slices[1], rightSize, pivItem);

        //housekeeping
        if (arr) {
            delete[] arr;
            arr = nullptr;
        }
        if (slices[0] != nullptr) {
            delete[] slices[0];
            slices[0] = nullptr;
        }
        if (slices[1] != nullptr) {
            delete[] slices[1];
            slices[1] = nullptr;
        }
        if (slices != nullptr) {
            delete[] slices;
            slices = nullptr;
        }

        return result;
    }
}

// heap sort function homework 5

bool IsHeap(int* Arr, int arrSize) {
    for (int i = 0; i < arrSize / 2; i++) {
        int p = Arr[(i - 1) / 2];   //Returns the parent node.
        int lc = Arr[(2 * i) + 1];  //Returns the left child node.
        int rc = Arr[(2 * i) + 2];  //Returns the right child node.

        if (lc < p && ((2 * i) + 1) < arrSize - 1) {
            return false;
        }

        if (rc < p && ((2 * i) + 2) < arrSize - 1) {
            return false;
        }
    }
    return true;
}

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

int* MakeHeap(int* arr, int size) {
    int* a = new int[size];
    Deepcopy(arr, a, size);
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(a, size);

    return a;
}

int* heapSort(int* arr, int size) {
    //    build a heap from arr
    int* q = MakeHeap(arr, size);
    //swap elements
    for (int i = size - 1; i > 0; i--) {
        swap(q[0], q[i]);

        heapify(q, i);
    }
    //    return sorted array!!
    return q;
}

void Unsort(int* arr, int size) {
    int j = 0;
    while (j < 35) {
        for (int i = 0; i < size; i++) {
            int pos_to_swap = GenerateRandomValue(size - 1, 0);
            Swap(arr, pos_to_swap, i);
        }
        j++;
    }
}

bool IsSorted(int* arr, int size) {
    for (int i = 1; i <= size; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

/**/

template <typename T>
void display_array(T* array, int size,bool a=true) {
    cout << " [ ";
    for (int i = 0; i < size; i++) {
        cout << array[i];
          if(i<size-1)
            cout << ",";
    }
    cout << "]";

    if (a==true){
      cout<<'\n';
    }
}
void Reset(int* arr, int size) {
    int* barr = arr;

    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

int* randomArray(int size, int min, int max) {
    srand(time(0));
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = GenerateRandomValue(min, max);
    }
    return arr;
}

int* quickArray() {
    int size = 7;
    int* ar = new int[size];
    Reset(ar, size);
    ar[0] = 3;
    ar[1] = 2;
    ar[2] = 6;
    ar[3] = 7;
    ar[4] = 9;
    ar[5] = 8;
    ar[6] = 5;
    return ar;
}

void Display2d(int** a, int rowlen, int col) {
    // for each row
    cout << "[";
    for (int i = 0; i < rowlen; i++) {
        display_array(a[i], col);
        string l = (i == rowlen - 1) ? " " : ",";
        cout << l;
    }
    cout << "]";
}

int* reverse(int* A, int size) {
    int* temp = Deepcopy(A, size);

    for (int i = 0; i < size; i++) {
        temp[(size - 1) - i] = A[i];
    }
    Deepcopy(temp, A, size);
    delete[] temp;
    return A;
}

bool dublicates(int* arr, int size) {
    bool dublicateitemsExists = false;

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                dublicateitemsExists = true;
                break;
            }
        }
        if (dublicateitemsExists) break;
    }
    return dublicateitemsExists;
}

void Rec_bubbleSort(int* arr, int n) {
    // Base case
    if (n == 1)
        return;

    /* One pass of bubble sort. After
    // this pass, the largest element
    // is moved (or bubbled) to end.*/
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            Swap(arr, arr[i], arr[i + 1]);

    // Largest element is fixed,
    // recur for remaining array
    Rec_bubbleSort(arr, n - 1);
}

void bubbleSort(double* list, int listSize) {
    bool changed = true;
    do {
        changed = false;
        for (int j = 0; j < listSize - 1; j++)
            if (list[j] > list[j + 1]) {
                // swap list[j] with list[j + 1];
                changed = true;
            }
    } while (changed);
}

int sumofArray(int* a, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }

    return sum;
}

int productofArray(int* a, int size) {
    int product = 0;
    for (int i = 0; i < size; i++) {
        product *= a[i];
    }

    return product;
}

int diffofArray(int* a, int size) {
    int diff = 0;
    for (int i = 0; i < size; i++) {
        diff -= a[i];
    }

    return diff;
}

void cpsubarray(int* srcArr, int srcSize, int srcPos, int* desArr, int desSize, int desPos, int itemcount) {
    // int* srcArr                                 int* desArr
    if (srcPos < srcSize && srcPos >= 0 && desPos < desSize && desPos >= 0) {
        // check bounds

        if ((itemcount + srcPos) <= srcSize && (itemcount + desPos) <= desSize) {
            // checking last bound
            for (int i = 0, j = desPos, k = srcPos; i <= itemcount; i++) {
                desArr[j + i] = srcArr[i + k];
            }
        } else {
            cout << "check last position bounds " << endl;
        }
    } else {
        cout << "check Source and destination position bounds " << endl;
    }
}

#endif  // array_h