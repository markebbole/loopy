#include <string>
#include <iostream>
using namespace std;
int main()
{
    string c;
    while (cin >> c) {
        cout << "if (type == \"" << c << "\") {\n"
            << "    allNodes[k] = new " << c << "();\n"
            << "}\n";
    }
}