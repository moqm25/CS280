//
//  balancedDelimiters.cpp
//  RA 7
//
//  Created by Moiez Qamar on 11/12/22.
//

//#include "balancedDelimiters.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <map>

using namespace std;
stack<char> delimiterStack;

map<char,char> symbols = {{')','('},{']','['},{'}','{'}};

bool checker(int i, string & inputString){
    
    auto ending = symbols.find(inputString[i]);
    char begin;
    if( ending != symbols.end() ){
        begin = ending->second;
    }else{
        return true;
    }
    
    if(!delimiterStack.empty()){
        if(delimiterStack.top() == begin){
            delimiterStack.pop();
            return true;
        }else{
            if(i==inputString.length()-1){
                cout<<"Stack is not empty and the scanning of input string is completed."<<endl;
                return false;
            }else{
                cout<<"Stack is not empty and the scanning of input string is not completed."<<endl;
                
                return false;
            }
        }
    }else{
        cout<<"Stack is empty and the scanning of input string is not completed."<<endl;
        return false;
    }
}

bool BalancedDelimiters(string & inputString){
    for(int i = 0; i<inputString.length();i++){
        if(inputString[i]=='[' || inputString[i]=='{' || inputString[i]=='('){
            delimiterStack.push(inputString[i]);
        }
        if(!checker(i,inputString)){
            return false;
        }
        
    }
    if(delimiterStack.empty()){
        cout<<"Stack is empty and the scanning of input string is completed."<<endl;
        return true;
    }
    return true;
}
