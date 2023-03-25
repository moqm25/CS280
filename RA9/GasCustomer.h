//
//  GasCustomer.h
//  RA9
//
//  Created by Moiez Qamar on 12/5/22.
//
#include <iostream>
#include <string>
using namespace std;
#include <stdio.h>
#include "UtilityCustomer.h"

#ifndef GasCustomer_h
#define GasCustomer_h

class GasCustomer: public UtilityCustomer{
    protected:
        const double gas_price = 3.75;
    public:
        double Usage;

        GasCustomer(){
            //cout<<"gas uages = 0.0"<<endl;
            Usage = 0.0;
        }
        GasCustomer(double usage, int accNum){
            //cout<<"gas uages "<<usage<<endl;
            this->Usage = usage;
            setAccount(accNum);
        }
        double getUsage() const{
            return Usage;
        }
        void setUsage(double usage){
            this->Usage = usage;
        }
        double calculateBill(){
            return Usage * gas_price;
        }
        void Display() const{
            cout<<"Gas Utility Customer"<<endl;
            UtilityCustomer::Display();
            cout << "Gas Used (in cubic meters): " << Usage << endl;
            GasCustomer g(Usage, UtilityCustomer::getAccount());
            cout << "total Charge: " << g.calculateBill() << endl;
        }
};
#endif /* GasCustomer_h */
