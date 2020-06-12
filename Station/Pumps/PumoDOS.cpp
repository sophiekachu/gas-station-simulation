// Assignment 1		
// Name:		Sophia Ha
// Student ID:	41171142
// Demo Date:	Nov 8, 2018


#include "..\..\..\Assignment 1\rt.h"
#include "..\Station\Pump.h"
#include <iostream>
#include <stdio.h>

struct	pump_info {			// structure template for some data that we intend to write to the pipeline
	int		fuel_grade;
	double	cost_litre;
	double 	fuel_tank;
	int		fuel_amount;
	double 	price;
	const char *names;
	int		credit[8];
};
struct pump_info *pump_data_pointer;
CDataPool		 *pump_data_pool;

struct	pump_info2 {			// structure template for some data that we intend to write to the pipeline
	int		fuel_grade;
	double	cost_litre;
	double 	fuel_tank;
	int		fuel_amount;
	double 	price;
	const char *names;
	int		credit[8];
};
struct pump_info2 *pump_data_pointer2;
CDataPool		  *pump_data_pool2;

struct	pump_info3 {			// structure template for some data that we intend to write to the pipeline
	int		fuel_grade;
	double	cost_litre;
	double 	fuel_tank;
	int		fuel_amount;
	double 	price;
	const char *names;
	int		credit[8];
};
struct pump_info3 *pump_data_pointer3;
CDataPool		  *pump_data_pool3;

struct	pump_info4 {			// structure template for some data that we intend to write to the pipeline
	int		fuel_grade;
	double	cost_litre;
	double 	fuel_tank;
	int		fuel_amount;
	double 	price;
	const char *names;
	int		credit[8];
};
struct pump_info4 *pump_data_pointer4;
CDataPool		  *pump_data_pool4;

int main() {

	//printf("Attempting to create/use the datapool 1.....\n");
	pump_data_pool = new CDataPool("__CustomerDataPool__" + 1, sizeof(struct pump_info));
	pump_data_pointer = (struct pump_info*)(pump_data_pool->LinkDataPool());

	//printf("Attempting to create/use the datapool 2.....\n");
	pump_data_pool2 = new CDataPool("__CustomerDataPool__" + 2, sizeof(struct pump_info2));
	pump_data_pointer2 = (struct pump_info2*)(pump_data_pool2->LinkDataPool());

	//printf("Attempting to create/use the datapool 2.....\n");
	pump_data_pool3 = new CDataPool("__CustomerDataPool__" + 3, sizeof(struct pump_info2));
	pump_data_pointer3 = (struct pump_info3*)(pump_data_pool3->LinkDataPool());

	//printf("Attempting to create/use the datapool 2.....\n");
	pump_data_pool4 = new CDataPool("__CustomerDataPool__" + 4, sizeof(struct pump_info2));
	pump_data_pointer4 = (struct pump_info4*)(pump_data_pool4->LinkDataPool());

	while (1) {
		MOVE_CURSOR(0, 0);
		TEXT_COLOUR(0, 15);
		cout << "PUMP 1\n";
		TEXT_COLOUR();
		//printf("Name: %s", (pump_data_pointer->names) );
		//cout << pump_data_pointer->names;
		cout << "Credit Card: ";
		for (int i = 0; i < 7; i++) {
			cout << pump_data_pointer->credit[i];
		}
		cout <<	"\nFuel Grade: " << pump_data_pointer->fuel_grade;
		printf("\nCost Per Litre: $ %.2f / L     ", pump_data_pointer->cost_litre);
		cout << "\nFuel Tank: (L) " << pump_data_pointer->fuel_tank << "   \n";
		printf("Total Cost: $ %.2f     ", pump_data_pointer->price);
		fflush(stdout);

		MOVE_CURSOR(0, 8);
	//	cout << "Pump 2\nName: " << pump_data_pointer2->names;
		TEXT_COLOUR(0, 15);
		cout << "PUMP 2\n";
		TEXT_COLOUR();
		cout << "Credit Card: ";
		for (int j = 0; j < 7; j++) {
			cout << pump_data_pointer2->credit[j];
		}
		cout << "\nFuel Grade: " << pump_data_pointer2->fuel_grade;
		printf("\nCost Per Litre: $ %.2f / L     ", pump_data_pointer2->cost_litre);
		cout << "\nFuel Tank: (L) " << pump_data_pointer2->fuel_tank << "   \n";
		printf("Total Cost: $ %.2f     ", pump_data_pointer2->price);
		fflush(stdout);

		MOVE_CURSOR(0, 16);
	//	cout << "Name: " << pump_data_pointer3->names;
		TEXT_COLOUR(0, 15);
		cout << "PUMP 3\n";
		TEXT_COLOUR();
		cout << "Credit Card: ";
		for (int k = 0; k < 7; k++) {
			cout << pump_data_pointer3->credit[k];
		}
		cout << "\nFuel Grade: " << pump_data_pointer3->fuel_grade;
		printf("\nCost Per Litre: $%.2f / L     ", pump_data_pointer3->cost_litre);
		cout << "\nFuel Tank: (L) " << pump_data_pointer3->fuel_tank << "   \n";
		printf("Total Cost: $ %.2f     ", pump_data_pointer3->price);
		fflush(stdout);

		MOVE_CURSOR(0, 24);
	//	cout << "Pump 4\nName: " << pump_data_pointer4->names;
		TEXT_COLOUR(0, 15);
		cout << "PUMP 4\n";
		TEXT_COLOUR();
		cout << "Credit Card: ";
		for (int l = 0; l < 7; l++) {
			cout << pump_data_pointer4->credit[l];
		}
		cout << "\nFuel Grade: " << pump_data_pointer4->fuel_grade;
		printf("\nCost Per Litre: $ %.2f / L     ", pump_data_pointer4->cost_litre);
		cout << "\nFuel Tank (L): " << pump_data_pointer4->fuel_tank << "   \n";
		printf("Total Cost: $ %.2f     ", pump_data_pointer4->price);
		fflush(stdout);

		Sleep(25);
		//CLEAR_SCREEN();
	}

	return 0;
}