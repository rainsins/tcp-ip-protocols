#include <iostream>
#include <stdio.h>
#include "head/xnet_tiny.hpp"

using namespace std;

int main(){
    _xnet_init();
    cout << "xnet running!"<< endl;
    while (1)
    {
        _xnet_poll();
    }
    
}