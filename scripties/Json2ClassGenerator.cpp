#include <string>
#include <iostream>
using namespace std;
int main()
{
    string c;
    while (cin >> c) {
        if (c.at(c.length() - 1) == '_') {
            c = c.substr(0, c.length()-1);
            cout << "if (type == \"" << c << "\") {\n"
            << "    allNodes[k] = new " << c << "();\n"
            << "    inputNodes.push_back((LoopyInputNode*)allNodes[k]);\n"
            << "}\n";
        } else {
            cout << "if (type == \"" << c << "\") {\n"
                << "    allNodes[k] = new " << c << "();\n"
                << "}\n";
        }
    }
}