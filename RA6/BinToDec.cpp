#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int BinToDec(string binNum){
    int result=0;
    if(binNum.length()>0){
        int z = pow(2,binNum.length()-1);
        int x =binNum[0]-'0';
        int y = BinToDec(binNum.substr(1,binNum.length()));
        result+= (x)* z+y;
                
    }else{
        result = 0;
    }
    return result;
}
