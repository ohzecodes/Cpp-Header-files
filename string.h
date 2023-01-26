#include <iostream>
#include <string>

#include "./maths.h"
using namespace std;
#ifndef mystring_h
#define mystring_h
/* from geeksforgeeks
char* toCharArr(string s) {
    char* ch = new char[s.length() + 1];
    strcpy(ch, s.c_str());
    return ch;
}*/

// compare char in 2 string then return a unique string
// if nothing found return empty string
string CharCompare(string s1, string s2) {
    string result = "";
    for (int i = 0; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            if ((s1.at(i) == s2.at(j)) && (result.find(s2.at(j)) <= -1)) {
                result += s2.at(j);
            }
        }
    }

    return result;
}

// generate a random string of max lenght.
string GenerateRandomWord(int maxlenght = 3, bool lower = false) {
    string p;
    int* i = new int[2];
    i[0] = (lower) ? (int)'a' : (int)'A';
    i[1] = (lower) ? (int)'z' : (int)'Z';

    for (int ch = 0; ch < maxlenght; ch++) {
        p += (char)GenerateRandomValue(i[0], i[1]);
    }
    delete[] i;
    return p;
}
/*TODO: check 0's case.
as of this moment, 0 is not being stored in n;
*/
int toInt(string p) {
    int n = 0, j = 0;
    for (int i = p.size() - 1; i >= 0; i--, j++) {
        if (p.at(i) - 48 == 0) {
            n += 0;
            j--;
        } else {
            n += ((int)p.at(i) - 48) * pow(10, j);
        }
    }

    return n;
};

// generate a random string of len between max and min
string GenerateRandomWord(int min = 5, int max = 10, bool lower = false) {
    int len = GenerateRandomValue(min, max);
    string p;
    int* i = new int[2];
    i[0] = (lower) ? (int)'a' : (int)'A';
    i[1] = (lower) ? (int)'z' : (int)'Z';

    for (int ch = 0; ch < len; ch++) {
        p += (char)GenerateRandomValue(i[0], i[1]);
    }
    delete[] i;
    return p;
}

/*if you dont give a size it will take the lenght of s by default(0);  if a size is passed it will take that size  */
char* toCharArr(string s, int size = 0) {
    if (size == 0) {
        size = s.size();
    }
    char* p = new char[size];
    for (int i = 0; i < size; i++) {
        p[i] = s[i];
    }
    return p;
}

string char_to_string(char a) {
    string str = "";
    str += a;
    return str;
}

// geeks for geeks
string charArrToString(char* a, int size) {
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

// "true" is stored as 1, "false" as 0.
string booltostring(bool b) {
    return (b == 0) ? "false" : "true";
}

string StringNtimes(string c, int n) {
    string r = "";
    for (int i = 0; i < n; i++) {
        r += c;
    }
    return r;
}
/*recursive reverse function not using substring */
string reverse(string str, int& len) {
    if (len == 1) {
        return char_to_string(str.at(0));
    } else {
        string sm = char_to_string(str.at(len - 1));
        string big = sm + reverse(str, --len);
        return big;
    }
}
/*recursive reverse function using sub */
string reverse_using_sub(string str) {
    int len = str.length();
    if (len == 1) {  // base case
        return char_to_string(str.at(0));
    } else {
        string sm = char_to_string(str.at(len - 1));                  //geting last charecter- small problem solution
        string big = sm + reverse_using_sub(str.substr(0, len - 1));  //big solution
        return big;
    }
}
bool palindrome(string s) {
    int len = s.length();
    if (s == reverse(s, len)) {
        return true;
    } else
        return false;
}
bool isPalindrome(const string& s) {
    if (s.size() <= 1)
        return true;
    else if (s[0] != s[s.size() - 1])
        return false;
    else
        return isPalindrome(s.substr(1, s.size() - 2));
}

/*display to console directly */
void revdisplay(string s) {
    int size = s.length();
    if (s.size() == 1) {
        cout << (char)s.at(0);
    } else {
        int sm = s.at(size - 1);
        string sub = s.substr(0, size - 1);
        cout << (char)sm;
        revdisplay(sub);
    }
}
#endif