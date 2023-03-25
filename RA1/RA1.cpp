#include <iostream>

using namespace std;

int main()
{
    cout << "Welcome to CS 280 in Fall 2022\n";
    cout << "Please enter your last name followed by your first name.\n";
    string first = "";
    string second = "";
    cin >> first;

    cin >> second;

    cout << "Hello " << second << " " << first << " in CS 280" << endl;
}
