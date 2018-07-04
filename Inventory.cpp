#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Inventory.h"

using namespace std;

int Inventory::corpInventory[20];
int Inventory::corpQtySold[20];

Inventory::Inventory(){
	//initialize all the stock to -1.
	for(int j=0;j<20;j++){
		stock[j]=-1;
	}
    
	int request;
	int storestock;
    
    //numbers of models that the store carries
	model = rand()%16+5;
    int carry = model;
    do{
		storestock = rand()%20;	//rolling a dice to pick a model
		if(stock[storestock]==-1){	//process only if the model was not selected previously
                                    //if it was selected before, then it would have a stock.
			request = rand()%75+1;	//random quantity from 1 to 75.
			//request the quantity to stock the inventory
			stock[storestock] = corpRequest(storestock, request);
			carry--;//modify it laster
		}
	} while(carry>0);	//reroll unless the stock for the model is -1.
	
}

void Inventory::setCorpInventory(){
	for(int i=0;i<20;i++){
		corpInventory[i]=rand()%1401+600;	//600 to 2000 random number
	}
	return;
}

int Inventory::getModelSold(int mdl){
	return sold[mdl];
}

void Inventory::salesSimulation(){
    soldInitialize();   //set all sold quantity to 0 at the beginning of the sales.
	int avail;	//available stock placeholder
	for(int i=0;i<20;i++){
        //if there is a stock, run a random from the stock and update stock, sold, and corp sold.
        if(stock[i]>0){
            avail = stock[i];
            sold[i] = rand()%(avail+1);     //if 10 shirts are avilable, then the possible  
                                            //sales range is from 0 to 10. 
            corpQtySold[i] += sold[i];      //update corpQtySold
            stock[i]-=sold[i];              //update stock
        }
	}
    
	return;
}
//add all the sold numbers for every models and multiply by $5 to get total store profit.
int Inventory::getDailySales(){
	int total = 0;
	for(int i=0;i<20;i++){
		total += sold[i];
	}
	return total * 5;
}
//initialize static corpInventory random numbers from 600 to 3000.
void Inventory::corpInventInit(){
	int num;
	for(int i=0;i<20;i++){
		num=rand()%2401+600;	//600 to 3000 stocks
		corpInventory[i]=num;
	}
	return;
}
//initialize static corpQtySold to all 0s.
void Inventory::corpQtySoldInit(){
	for(int i=0;i<20;i++){
		corpQtySold[i]=0;
	}
	return;
}
//return a pointer to the store stock array.
int* Inventory::getAvail(){
    int* x = &stock[0];
    return x;
}

//given the model number and the requested quantity, 
int Inventory::corpRequest(int model, int request){
	int qty;
	//if the request is larger than the current stock
    //it will return whatever is left.
    if(request>corpInventory[model]){
		qty = corpInventory[model];
	} else{
		qty = request;
	}
    corpInventory[model] -= qty;
    
	return qty;
}

//at the end of day, we count money and restock the inventory.
void Inventory::endOfDay(){
    money = getDailySales();    
    
    int soldQty;
    int reqQty;
    for(int i=0;i<20;i++){
        if(sold[i]>0){  //only the models that made sales.
            soldQty = sold[i];
            reqQty = rand()%6+soldQty;
            //if request 10, we want 10~15 shirts.
            //mod6 will result 0~5
            //(0~5) + 10 = 10~15 shirts.
            stock[i]+=corpRequest(i,reqQty);
        }
    }
    return;
}
//initialize sold quantity for daily use.
void Inventory::soldInitialize(){
    for(int i=0;i<20;i++){
        sold[i]=0;
    }
    return;
}
