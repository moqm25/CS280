//
//  ra7prog.cpp
//  RA 7
//
//  Created by Moiez Qamar on 11/12/22.
//

#include <stdio.h>
#include "balancedDelimiters.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

bool BalancedDelimiters(string & inputString);
int main(int argc, char *argv []){
    string sentence;
    int x = 1;
    while (x<argc){
        bool balancedDelimiters;
        ifstream file;
        if( argc >= 2 ) {
            file.open(argv[x]);
            if( !file){
                /* error */
                cerr << "File cannot be opened: " << argv[1] << endl;
                exit (1);
            }
        }else{
            cerr << "No file is found" << endl;
            exit (1);
        }
        getline(file, sentence);
        if(sentence.length() == 0){
            cout << "File is empty." << endl;
            return 0;
        }
        cout<<"FILENAME: "<<argv[x]<<endl;

        balancedDelimiters = BalancedDelimiters(sentence);
        
        if (balancedDelimiters)
            cout << "\"" << sentence << "\"" << " contains balanced delimiters." <<endl;
        else
            cout << "\"" << sentence << "\"" << " does not contain balanced delimiters." << endl;
        x++;
        cout<<endl;
    }
}
