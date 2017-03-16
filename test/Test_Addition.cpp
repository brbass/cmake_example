#include <iomanip>
#include <iostream>

#include "Math.h"

using std::cerr;
using std::cout;
using std::endl;
using std::setw;

int test_addition(int number_1,
                  int number_2,
                  int expected)
{
    int checksum = 0;
    int width = 16;

    Math math;
    
    int result = math.add(number_1,
                          number_2);
    
    if (expected != result)
    {
        checksum += 1;
        cout << setw(width) << "expected";
        cout << setw(width) << "calculated";
        cout << endl;
        cout << setw(width) << expected;
        cout << setw(width) << result;
        cout << endl;
    }

    return checksum;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "usage: test_addition [num1 num2 result]" << endl;
        return 1;
    }
    
    int checksum = 0;

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int result = atoi(argv[3]);
    
    checksum += test_addition(num1,
                              num2,
                              result);

    return checksum;
}
