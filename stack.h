#if !defined(Stack_h)
#define Stack_h
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T>
class Stack {
   public:
    Stack() {
        v = new vector<T>();
    };

    bool isempty() {
        return v->size() < 0;
    };

    T peek() {
        return v->at(v->size() - 1);
    };

    void push(T value) {
        v->push_back(value);
    };

    T pop() {
        T c = peek();
        v->pop_back();
        return c;
    };

    int getSize() {
        return v->size();
    }

    void PrintStack() {
        for (int i = v->size() - 1; i >= 0; i--) {
            cout << v->at(i);
            cout << endl;
        }
    }

    int size() {
        return (int)v->size();
    }

   private:
    vector<T>* v;
};

#endif  // Stack_h
