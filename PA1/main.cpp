#include <iostream>
#include <fstream>
#include "lex.h"
#include <list>
//#include "tokens.h"
//#include <list>
using namespace std;

/*
int main(){
    cout << "Enter your name: ";
    string x;
    cin >> x;
    cout <<x<<endl;
    for(int y = 0;y<x.length();y++){
        cout<<x[y]<<endl;
    }
}
*/
int main(int argCount, const char *args[]){
    bool vOption = false;
    bool iconstOption = false;
    bool rconstOption = false;
    bool bconstOption = false;
    bool sconstOption = false;
    bool identOption = false;


    string fileName;
    istream *x = &cin; // istream object to pass to getNextToken

    if(argCount==1){
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        return -1;
    }
    for (int i = 1; i < argCount; i++){
        string argu = args[i];
        if (argu == "-v"){
            vOption = true;
            //cout << "-v was successful" << endl;
            continue;
            
        }else if (argu == "-iconst"){
            iconstOption = true;
            //cout << "-strings was successful" << endl;
            continue;
            
        }else if (argu == "-rconst"){
            rconstOption = true;
            //cout << "-ids was successful" << endl;
            continue;
            
        }else if (argu == "-sconst"){
            sconstOption = true;
            //cout << "-ids was successful" << endl;
            continue;
            
        }else if (argu == "-bconst"){
            bconstOption = true;
            //cout << "-ids was successful" << endl;
            continue;
            
        }else if (argu == "-ident"){
            identOption = true;
            //cout << "-ids was successful" << endl;
            continue;
            
        }else if ((i == 1) && ((argu != "-iconst") || (argu != "-rconst") || (argu != "-sconst") || (argu != "-bconst") || (argu != "-ident")  || (argu != "-v"))) {
            ifstream subs(argu);
            if (!subs.is_open()){
                cout << "CANNOT OPEN THE FILE " << argu << endl;
                return -1;
            }else{
                if (subs.peek() == EOF){
                    cout << "Lines: 0"<<endl;
                    return 0;
                }
                //cout << "filename was successful" << endl;
                fileName = argu;
                continue;
            }
        }else{
            if (argu[0] == '-'){
                cout << "UNRECOGNIZED FLAG " << argu << endl;
                return -1;
            }else{
                //cout<< "-----"<<argu[0]<<endl;
                cout << "ONLY ONE FILE NAME ALLOWED." << endl;
                return -1;
            }
        }
    }

    //============ EVERYTHING ABOVE IS FLAGS RELATED=========
    //COUNTERS:
    int lines = 1;
    int tokens = 0;
    
    ifstream file(fileName);
    if (file.peek() == EOF){
        cout << "Total lines: 0";
        return 0;
    }
    x=&file;
    LexItem t;
    t = getNextToken(*x,lines);//LexItem object
    list<string> strings;
    list<int> integers;
    list<string> reals;
    list<string> identifiers;
    list<string> bools;


    while(t != ERR and t != DONE){
        //cout<<"BEFORE-----------------------"<<endl;
        //if(t.GetToken()==PROGRAM){
       //     cout<<"THIS IS A PROGRAM"<<endl;
        //}
        if(vOption){
            cout<<t<<endl;
            //cout<<" Line number:"<<t.GetLinenum()<<endl;;
        }
        if(iconstOption and t==ICONST){
            integers.push_back(stoi(t.GetLexeme()));
        }
        if(rconstOption and t==RCONST){
            reals.push_back(t.GetLexeme());
        }
        if(sconstOption and t==SCONST){
            strings.push_back(t.GetLexeme());
        }
        if(bconstOption and (t.GetLexeme()=="TRUE" || t.GetLexeme()=="FALSE")){
            bools.push_back(t.GetLexeme());
        }
        if(identOption and t==IDENT){
            identifiers.push_back(t.GetLexeme());
        }

       // cout<<"AFTER-----------------------"<<endl;
        tokens++;
        t = getNextToken(*x,lines);
    }

    if( t == ERR ) {
        cout<<"Error in line "<<t.GetLinenum()<<" ("<<t.GetLexeme()<<")"<<endl;
        return -1;
        //cout<<" Line number:"<<t.GetLinenum()<<"--_"<<t.GetLexeme()<<"_"<<endl;
    }
    
// i r s b i

    if(lines-1==1 and tokens==0){
        cout << "Lines: " << lines-2 << endl;
    }else{
        cout << "Lines: " << lines-1 << endl;
        cout << "Tokens: " << tokens << endl;
    }
    
    if(sconstOption and strings.size()>0){
        cout<<"STRINGS:"<<endl;
        strings.sort();
        strings.unique();
        for (string val : strings){
            cout <<"\""<< val<<"\""<< endl;
        }
    }
    
    if(iconstOption and integers.size()>0){
        cout<<"INTEGERS:"<<endl;
        integers.unique();
        integers.sort();
        for (int val : integers){
            cout << val<<endl;
        }
    }
    if(rconstOption and reals.size()>0){
        cout<<"REALS:"<<endl;
        reals.sort();
        reals.unique();
        for (string val : reals){
            cout << val<<endl;
        }
    }
    
    if(bconstOption and bools.size()>0){
        cout<<"Booleans:"<<endl;
        for(string val: bools){
            cout<<val<<endl;
        }
    }
    if(identOption and identifiers.size()>0){
        cout<<"IDENTIFIERS:"<<endl;
        identifiers.sort();
        identifiers.unique();

        int count = 0;
        for (string val : identifiers){
            cout << val;
            if (count != identifiers.size() - 1){
                cout << ", ";
                count++;
            }
        }
        cout<<endl;
    }
}



