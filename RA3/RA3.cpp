//created by myself
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int linecounter = 0;
int nonblankcounter = 0;
int wordcounter = 0;
int intcounter = 0;
int namescounter = 0;

bool isname(string str)
{
    /*
    A  word is defined as a name if it starts by a letter or an underscore ‘_’, and followed by
                zero  or  more  letters,  digits,  underscores  ‘_’,  or  ‘@’  characters.
                    For  example,  value, val@l9, num234ten, _num_45 are valid names,
                    but 9val, and &num are not.
    */
    if (!((str[0] == '_' || isalpha(str[0]))))
    {
        return false;
    }
    for (int i = 1; i < str.length(); i++)
    {
        if (!(isalnum(str[i]) || str[i] == '_' || str[i] == '@'))
        {
            return false;
        }
    }
    return true;
}

bool isint(string str)
{
    if ((str[0] == '-' || str[0] == '+') && str.length() == 1)
    {
        return false;
    }

    for (int i = 1; i < str.length(); i++)
    {
        if (!(isdigit(str[i])))
        {
            return false;
        }
    }
    return true;
}

void words(string str)
{
    stringstream s(str);
    string word;
    int count = 0;
    bool line = false;
    while (s >> word)
    {
        wordcounter++;
        // cout << "---------  " << word << endl;
        if (isname(word))
        {
            // cout << "========== is name!" << endl;

            namescounter++;
            if (line == false)
            {
                nonblankcounter++;
            }
            line = true;
        }
        else if (isint(word))
        {
            // cout << "========== is int!" << endl;
            intcounter++;
            if (line == false)
            {
                nonblankcounter++;
            }

            line = true;
        }
    }
}

int main(int argCount, const char *args[])
{
    bool all = false;
    bool ints = false;
    bool names = false;
    bool noFalgs = false;
    string fileName;

    if (argCount == 1)
    {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 0;
    }

    for (int i = 1; i < argCount; i++)
    {
        string argu = args[i];

        if (i == 1)
        {
            if ((argu == "-all") || (argu == "-ints") || (argu == "-names"))
            {
                cout << "NO SPECIFIED INPUT FILE NAME";
                return -1;
            }
            ifstream subs(argu);
            if (!subs.is_open())
            {
                cout << "CANNOT OPEN THE FILE " << argu << endl;
                return -1;
            }
            else
            {
                // cout << "filename was successful" << endl;
                fileName = argu;
            }
            if (argCount == 2)
            {
                noFalgs = true;
            }
        }
        if (argu == "-all")
        {
            all = true;
            // cout << "-all was successful" << endl;
            continue;
        }
        else if (argu == "-ints")
        {
            ints = true;
            // cout << "-ints was successful" << endl;
            continue;
        }
        else if (argu == "-names")
        {
            names = true;
            // cout << "-names was successful" << endl;
            continue;
        }
        else
        {
            if (argu[0] == '-')
            {
                cout << "UNRECOGNIZED FLAG " << argu << endl;
                return -1;
            }
        }
    }

    string line = "";
    ifstream file(fileName);
    while (getline(file, line))
    {
        // cout << line << endl;
        linecounter++;
        words(line);
    }

    if (linecounter == 0)
    {
        cout << "File is empty." << endl;
        return 0;
    }

    cout << "Total Number of Lines: " << linecounter << endl;
    cout << "Number of non-blank lines: " << nonblankcounter << endl;
    cout << "Number of Words: " << wordcounter << endl;

    if (all)
    {
        cout << "Number of Integers: " << intcounter << endl;
        cout << "Number of Names: " << namescounter << endl;
    }
    else
    {
        if (ints)
        {
            cout << "Number of Integers: " << intcounter << endl;
        }
        if (names)
        {
            cout << "Number of Names: " << namescounter << endl;
        }
    }
}