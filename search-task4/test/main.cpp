#include "head.h"

//extern string name;

int main(int argc, char **argv)
{
    cout << name << endl;
    name = "main___";
    show(&argc, &argv);
    cout << name << endl;
    return 0;
}
