#include <iostream>

#include "Math.h"

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "usage: add [num1 num2]" << endl;
        return 1;
    }

    Math math;

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    
    cout << math.add(num1, num2) << endl;
    
    return 0;
}
