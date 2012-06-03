#include <iostream>
#include <string>
using namespace std;

int main()
{
    char p[] = "Hello, world";
    string str1;
    string str2;
    str1 = p;
    str2 = str1;
    str1[1] = 'Y';
    cout << str1 << endl;
    cout << str2 << endl;
    return 0;
}
