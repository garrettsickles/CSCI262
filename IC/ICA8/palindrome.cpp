#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "stack.h"
#include "queue.h"
 
using namespace std;
 
bool is_palindrome(const string& s);
 
int main(){
    string line;
    ifstream in("input.txt");
 
    if (!in) {
        cerr << "Unable to open input file" << endl;
        return EXIT_FAILURE;
    }
    
    while (getline(in, line)){
        if (is_palindrome(line))
            cout << "'" << line << "' is a palindrome" << endl;
        else
            cout << "'" << line << "' is not a palindrome" << endl;
    }
    return EXIT_SUCCESS;
}

bool is_palindrome(const string& s){
    stack wordStack;
    queue wordQueue;
    bool same = true;
    int alphaCount = 0;

    for(int i = 0; i < s.length(); i++) {
        if(isalpha(s[i])) {
            wordStack.push(s[i]);
            wordQueue.enqueue(s[i]);
            ++alphaCount;
        }
    }
    for(int i = 0; i < alphaCount; i++)
        same &= (wordStack.top() == wordQueue.front());
    return(same);
}