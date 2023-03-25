//
//  ElectricCustomer.h
//  RA9
//
//  Created by Moiez Qamar on 12/5/22.
//
#include <iostream>
#include <string>
using namespace std;
#include <stdio.h>
#include "UtilityCustomer.h"

#ifndef ElectricCustomer_h
#define ElectricCustomer_h
class ElectricityCustomer: public UtilityCustomer{
    protected:
        const double electricity_price = 0.25;
    public:
        double kWattHourUsed;

        ElectricityCustomer(){
            //cout<<"UtilityCustomer accNum = 0.0"<<endl;

            kWattHourUsed = 0.0;
        }
        ElectricityCustomer(double usage, int accNum){
            //cout<<"UtilityCustomer accNum = setkWattHourUsed(usage)"<<endl;
            setkWattHourUsed(usage);
            setAccount(accNum);

        }
        double getkWattHourUsed() const{
            return kWattHourUsed;
        }
        void setkWattHourUsed(double usage){
            kWattHourUsed  = usage;
        }
        double calculateBill(){
            return kWattHourUsed * electricity_price;
        }
        void Display() const{
            cout<<"Electric Utility Customer"<<endl;
            UtilityCustomer::Display();
            cout << "Electricity Used (in kWattHour): " << kWattHourUsed << endl;
            ElectricityCustomer e(kWattHourUsed, UtilityCustomer::getAccount());
            cout << "total Charge: " << e.calculateBill() << endl;
        }
};
#endif /* ElectricCustomer_h */
