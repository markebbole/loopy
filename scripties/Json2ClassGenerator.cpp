#include <string>
#include <iostream>
using namespace std;
int main()
{
    //int numClasses;
    //cin >> numClasses;
    //for (int i = 0; i < numClasses; ++i) {
    string c;
    while (cin >> c) {
        //cin >> c;
        cout << "if (type == \"" << c << "\") {\n"
            << "    allNodes[k] = new " << c << "();\n"
            << "}\n";
    }
}