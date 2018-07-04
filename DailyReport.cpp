/*
Author: <Eugene A. Ko, Alina Birica, Johnny Qiu>
Course: {235}
Instructor: <Severin Ngnosse>
Assignment: <Project 0>
Due Date: Febuary 28, 2016

	On our honor,
	
	The following program is a result of team effort. We have not discussed with
	anyone other than our instructor or any appropriate person in charge of the class.
	We have not used, or slightly modified code or portion of code from another
	group, or an unauthorized source.
	If any C++ language code or documentation used in our program was obtained from
	another source, such as a textbook or course notes, that has been clearly noted
	with a proper citation in the comments of my program.
	We have not designed this program in such a way as to defeat or interfere with the
	normal operation of the eniac system or cslab machines at Hunter College .
	<Eugene A. Ko, Alina Birica, Johnny Qiu>



				Introduction

		The purpose of this program is to simulate and have statistic of sales
	by stores, by model, or by corporate wide as whole with the user's input.
	
	
				Initialization
	
		There will be 30 to 50 stores that will be choosed by the user's input.
	Each stores will carry 5 to 20 models of shirts that are randomly selected
	and the initial stocks will be in range from 1 to 75. At the beginning, 
	the stores will request for the stocks from the corporate warehouse,
	which will have randomly generated stocks of 600 to 3000 for each model.
	
	
				Simulation
	
		Each day a store will sell from 0 to the quantity the store carries by random and 
	will not sell more that what the store currently carries. Every sales the stores made
	for each model will be reported to the HQ for statistics.

		
				Restock
				
		Corporate warehouse will make more shirts throughout the day and will restock
	at the end of the day. Each stores can only request up to 5 more from what the store
	sold by model and and request to the corporate warehouse;However, if the warehouse
	does not meet the quantity the stores requested, then it will give out whatever
	the amount the warehouse currently holds.
	
	
				Report
		
		First statistic report:
		With the user's input, the program will provide a day's statistic by models 
	and report the total profit made by the store.
	
		Second statistic report:
		User will be asked to select a model number to have a day's report for said model
	for each store by quantity and the profit made by model.
	
		Thrid statistic report:
		The program will display models and its sales quantity with total profit for 
	the entire stores.
	
	
*/


#include <cstdlib>
#include <iostream>
#include "Inventory.h"

using namespace std;

int* grossDailyUpdate();
int* grossDailyQtySold();
int* grossSales();

void storeSimulate(int, Inventory *store);

void firstStat(int, Inventory *store);
void secondStat(int, int, Inventory *store);
void thirdStat(Inventory *store);
void seven(int, Inventory *store);
void corpRestock();
int askStore(int);
int askModel();
void thridPause();

int main(){
	//initialize corpInventory
    Inventory::corpInventInit();
    Inventory::corpQtySoldInit();
    
	int numStores; //number of stores
	
	do{
		cout<<"Enter numbers of stores: ";
		cin>>numStores;
	} while(numStores<30 || numStores>50);
	
	Inventory* stores = new Inventory[numStores];
	
	
    storeSimulate(numStores, stores);   //a day of simulation
    
    
	cout<<"One day simulation: "<<endl;    
    int userStore = askStore(numStores);
	firstStat(userStore, stores);    //get sales report for store number 0
	int userModel = askModel();
    secondStat(userModel, numStores, stores);   //get sales report for model number 0
    thridPause();
    thirdStat(stores);      //get total sales per model and total profit corporate wide.
    
    seven(numStores, stores);   //7 days simulation
    
    cout<<"7 day simulation: "<<endl;
    userStore = askStore(numStores);
    firstStat(userStore, stores);    //same store and model for comparison
    userModel = askModel();
    secondStat(userModel, numStores, stores);
    thridPause();
    thirdStat(stores);
    
    return 0;
}

//run a simulation for each stores
void storeSimulate(int num, Inventory *store){
    for(int i=0;i<num;i++){
        store[i].salesSimulation();
    }
    //corporate office restock
    corpRestock();
    
    //store refill
    for(int j=0;j<num;j++){
        store[j].endOfDay();
    }
    return;
}

//returns current accumulated corpQtySold array pointer
int* grossDailyQtySold(){
    int* x = new int[20];
    x = &Inventory::corpQtySold[0];
    return x;
}

//returns the number of shirts per model still available at the HQ after request from stores are fullfilled.
int* grossDailyUpdate(){
    int* x;
    x = &Inventory::corpInventory[0];
 
	return x;
}

//returns the total profit for each models
int* grossSales(){
	
    int* total;
    int sum=0;
	for(int i=0;i<20;i++){
        sum+=Inventory::corpQtySold[i];
	}
    sum*=5;
    
    total = &sum;
    
    return total;
}

//Reports the given store's sales by model and total profit for the store for the day.
void firstStat(int storeNum, Inventory *store){
    cout<<"Daily Store Sales Report!"<<endl;
    int* avail = store[storeNum].getAvail();
    cout<<"Statistics for the store number "<<storeNum<<"."<<endl;
    for(int i=0;i<20;i++){
        cout<<"Model "<<i<<": sold "<<store[storeNum].getModelSold(i)<<
        ", available "<<avail[i]<<"."<<endl;
    }
    cout<<"Profit for store number "<<storeNum<<": $"<<store[storeNum].getDailySales()<<"."<<endl;
    return;
}

//Reports the given model number's sales quantity by stores and the profit made by model.
void secondStat(int modelNum, int numStores, Inventory *store){
    int total=0;
    cout<<"Model number "<<modelNum<<" Sales Report!"<<endl;
    for(int i=0;i<numStores;i++){
        cout<<"Store number "<<i<<" sold "<<store[i].getModelSold(modelNum)<<"."<<endl;
        total+=store[i].getModelSold(modelNum);
    }
    cout<<"Total amount of profit for the model "<<modelNum<<" is $"<<total*5<<"."<<endl;
    return;
}

//Reports the sales by quantity by models and total profit for the whole company.
void thirdStat(Inventory *store){
    cout<<"Corporate Daily Sales Report!"<<endl;
    int* modelSold = grossDailyQtySold();
    for(int i=0;i<20;i++){
        cout<<"Model "<<i<<" sold "<<modelSold[i]<<" with profit $"<<modelSold[i]*5<<"."<<endl;
    }
    int* total = grossSales();
    cout<<"Total profit is $"<<*total<<"."<<endl;
    return;
}

//7 day simulation
void seven(int numStores, Inventory* store){
    
    int i = 7;
    while(i>0){
        storeSimulate(numStores, store);
        i--;
    }
    
    return;
}
//restock static corpInventory by adding random number from 600 to 2000 inclusive.
void corpRestock(){
	
	for(int i=0;i<20;i++){
		Inventory::corpInventory[i]+=rand()%1401+600;
	}
	return;
}

//User Input section
int askStore(int num){
	int answer;
	
	do{
		cout<<"Enter the sotre number for the first report(0-"<<num<<"): ";
		cin>>answer;
	}while(answer<0 || answer>num);
	
	return answer;
}
int askModel(){
	int answer;
	
	do{
		cout<<"Enter the model number for the first report(0-19): ";
		cin>>answer;
	}while(answer<0 || answer>19);
	
	return answer;
}

void thridPause(){
	int dummy;
	
	do{
		cout<<"Enter 1 to continue to the thrid statistic report."<<endl;
		cin>>dummy;
	}while(dummy!=1);
	
	return;
}
