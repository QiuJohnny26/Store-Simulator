#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory{
	private:
		static int corpInventory[20];	//corporate warehouse stock
		static int corpQtySold[20];		//accumulative quantity sold by company
		
		int model;					//numbers of models carried by the store.
		int stock[20];				//current stock for each model.
		int sold[20];				//sold history for the day
		int money;					//total profit made by the day.
		
		int corpRequest(int, int);	//request the quantity for restock for the model.
        void soldInitialize();		//initialize sales at the beginning of the day.
		
	public:
		Inventory();
		static void setCorpInventory();//initialize corpInventory with stock from 600 to 2000.
		int getModelSold(int mdl);	//returns the sold quantity for the day for given model.
		void salesSimulation();		//main simulation function - sales for model
		int getDailySales();		//total profit for the store for a day
        int* getAvail();			//check the availability for each model for the store.
        friend void corpRestock();	//restocks corporate warehouse
        void endOfDay();			//calculate profit and restock
		
        static void corpInventInit();	//initialize corpInventory from 600 to 3000 randomly.
        static void corpQtySoldInit();	//initialize the sales to 0.
        
        friend int* grossDailyQtySold();	//number of shirts sold per model by the company.
		friend int* grossDailyUpdate();		//number of shirts available from corporate warehouse.
		friend int* grossSales();			//total profit made by the company.
};

#endif
