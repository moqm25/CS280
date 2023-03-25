#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string fileName = "";

    cout << "Enter the name of a file to read from:\n";
    cin >> fileName;
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "\nFile cannot be opened " << fileName << endl;
        file.close();
        return 0;
    }

    int Total_lines = 0;
    int Commented_lines = 0;
    int Valid_Command_lines = 0;
    int Invalid_Command_lines = 0;
    int Run_commands = 0;
    int Print_commands = 0;
    int Copy_commands = 0;
    int Delete_commands = 0;

    string line = "";
    while (getline(file, line))
    {

        Total_lines++;

        if (line[0] == '%')
        {
            Commented_lines++;
            continue;
        }
        if (line.length() == 0)
        {
            continue;
        }
        string word = "";
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ' && word.length() >= 1)
            {
                if (word == "run")
                {
                    Valid_Command_lines++;
                    Run_commands++;
                    break;
                }
                else if (word == "print")
                {
                    Valid_Command_lines++;
                    Print_commands++;
                    break;
                }
                else if (word == "copy")
                {
                    Valid_Command_lines++;
                    Copy_commands++;
                    break;
                }
                else if (word == "delete")
                {
                    Valid_Command_lines++;
                    Delete_commands++;
                    break;
                }
                else
                {
                    Invalid_Command_lines++;
                    cout << "\nError: Unrecognizable command in line " << Total_lines << endl;
                    break;
                }
            }
            else
            {
                if (isspace(line[i]))
                {
                    word = "";
                }
                else
                {
                    word += line[i];
                }

                continue;
            }
        }
    }

    cout << "\nTotal lines: " << Total_lines << endl;

    cout << "Commented lines: " << Commented_lines << endl;

    cout << "Valid Command lines: " << Valid_Command_lines << endl;

    cout << "Invalid Command lines: " << Invalid_Command_lines << endl;

    cout << "Run commands: " << Run_commands << endl;

    cout << "Print commands: " << Print_commands << endl;

    cout << "Copy commands: " << Copy_commands << endl;

    cout << "Delete commands: " << Delete_commands << endl;
}
