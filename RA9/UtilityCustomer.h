//
//  UtilityCustomer.hpp
//  RA9
//
//  Created by Moiez Qamar on 12/5/22.
//

#include <iostream>
#include <string>
using namespace std;
#include <stdio.h>

#ifndef UtilityCustomer_h
#define UtilityCustomer_h




class UtilityCustomer{
    public:
        int accNum;

        UtilityCustomer(){
            accNum = -1;
            //cout<<"UtilityCustomer accNum = -1"<<endl;
        }
        UtilityCustomer(int num){
            setAccount(num);
            //cout<<"UtilityCustomer accNum = setAccount(num)"<<endl;

        }
        int getAccount() const{
            return accNum;
        }
        void setAccount(int num){
            //cout<<"UtilityCustomer accNum = num"<<endl;

            accNum = num;
        }
        virtual void Display() const{
            cout << "Utility Customer Account number: " << accNum << endl;
        }
    
        virtual double calculateBill() = 0;
    
        bool operator==(UtilityCustomer * UtilityObj) const{
            return this->accNum == UtilityObj->accNum;
        }
    
};


#endif /* UtilityCustomer_hpp */
