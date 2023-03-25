#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

int wordCounter = 0;

int oneVowelCounter = 0;
int twoVowelsCounter = 0;
int threePlusVowelsCounter = 0;
int noVowelsCounter = 0;
map<string, int> noVowels;
map<string, int> vowels1;
map<string, int> vowels2;
map<string, int> vowels3;

string lowerFunction(string word){
    int i = 0;
    while (i < word.length()){
        word[i] = tolower(word[i]);
        i++;
    }
    return word;
}

void isname(string str) {
    bool works = false;
    int count = 0;
    string word = lowerFunction(str);
    for (int i = 0; i < str.length(); i++) {
        if( (word[i]=='a') || 
            (word[i]=='e') || 
            (word[i]=='i') || 
            (word[i]=='o') || 
            (word[i]=='u') ){

            works=true;
            count++;
        }
    }
    if(!works){
        noVowelsCounter++;
        noVowels[str]++;
    }else if(count == 1){
        vowels1[str]++;
        oneVowelCounter++;
    }else if(count == 2){
        vowels2[str]++;
        twoVowelsCounter++;
    }else if(count >= 3){
        vowels3[str]++;
        threePlusVowelsCounter++;
    }
}

void words(string str){
    stringstream s(str);
    string word;
    while (s >> word){
        //cout << "WORD IS :" << word << ":" << endl;
        wordCounter++;
        isname(word);
    }
}


int main(int argCount, const char *args[]){
    string fileName;

    if (argCount == 1){
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 0;
    }
    else{
        fileName = args[1];
        ifstream subs(fileName);
        if (!subs.is_open()){
            cout << "CANNOT OPEN THE FILE " << fileName << endl;
            return -1;
        }
    }
    
    int lineCounter = 0;

    string line = "";
    ifstream file(fileName);
    while (getline(file, line)){
        lineCounter++;
        words(line);
    }

    if (lineCounter == 0){
        cout << "File is empty." << endl;
        return 0;
    }


    cout << "Number of words in the file: " << wordCounter << endl;
    cout << "Number of words with no vowels in the file: " << noVowelsCounter << endl;
    cout << "Number of words with one vowel in the file: " << oneVowelCounter << endl;
    cout << "Number of words with two vowels in the file: " << twoVowelsCounter << endl;
    cout << "Number of words with three or more vowels in the file: " << threePlusVowelsCounter << endl;

    if(noVowelsCounter>0){  
        cout<<endl<<"List of Words with no vowels and their number of occurrences:"<<endl;
        for(auto it = noVowels.begin(); it!= noVowels.end(); it++ ){
            cout << it->first << ": " << it->second << endl;
        }
    }
    if(oneVowelCounter>0){  
        cout<<endl<<"List of Words with one vowel and their number of occurrences:"<<endl;
        for(auto it = vowels1.begin(); it!= vowels1.end(); it++ ){
            cout << it->first << ": " << it->second << endl;
        }
    }
    if(twoVowelsCounter>0){  
        cout<<endl<<"List of Words with two vowels and their number of occurrences:"<<endl;
        for(auto it = vowels2.begin(); it!= vowels2.end(); it++ ){
            cout << it->first << ": " << it->second << endl;
        }
    }
    if(threePlusVowelsCounter>0){  
        cout<<endl<<"List of Words with three or more vowels and their number of occurrences:"<<endl;
        for(auto it = vowels3.begin(); it!= vowels3.end(); it++ ){
            cout << it->first << ": " << it->second << endl;
        }
    }
}