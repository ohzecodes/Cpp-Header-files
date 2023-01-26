#if !defined(queue_h)
#define queue_h

#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T>
class Queue {
   private:
    vector<T>* Q;

   public:
    /*default constructor*/

    Queue() {
        Q = new vector<T>;
    }
    void Enqueue(T elem) {
        Q->push_back(elem);
    }

    void Dequeue() {
        Q->erase(Q->begin());
    }
    T Front() {
        if (!this->isempty())
            return Q->at(0);
        else {
            throw "Empty Queue";
        }
    }
    bool isempty() {
        return Q->size() == 0;
    }
    void showQueue() {
        for (int i = 0; i < Q->size(); i++) {
            cout << Q->at(i) << " ";
        }
        cout << endl;
    }
};
#endif  // queue_h