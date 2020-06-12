// Assignment	1		
// Name:		Sophia Ha
// Student ID:	41171142
// Demo Date:	Nov 8, 2018


#include "..\..\..\Assignment 1\rt.h"
#include <iostream>
#include <list>
#include <stdio.h>

#define PUMP 4
#define LINE 4
#define CUSTOMERS 4
#define LITRES	200
#define RF	50

list<int> Time;
list<int> CreditCard;
list<int> Grade;
list<double> Quantity;

using	namespace std;
char	input  = NULL;
double	g1fuel = LITRES;
double	g2fuel = LITRES;
double	g3fuel = LITRES;
double	g4fuel = LITRES;
double	grade1, grade2, grade3, grade4;					// fuel grade prices if not changed
char	price_change;
bool	Refill = TRUE;
const	char* n[17] = {	"John Snow", "Arya Stark", "Ned Stark", "Sansa Stark", "Rob Stark", "Bran Stark",
						"Robert Baratheon", "Jaime Lannister", "Cersei Lannister", "Margery Tyrell", "Daenerys Targaryen", 
						"Jorah Mormont", "Petyr Baelish", "Samwell Tarly", "Sandor Clegane", "Brienne of Tarth", "Melisandre" };

CRendezvous r1			("Rendezvous", PUMP);			// attempt to create a rendezvous point involving the 4 Pump threads
CSemaphore LineUp		("LineUp",	0, CUSTOMERS);		// number of customers entering gas station and lining up
CSemaphore Swipe		("Swipe",	0, PUMP);			// customers swiping credit card
CSemaphore RemoveHose	("Remove",	0, PUMP);			// customers removing hose from pump
CSemaphore Fill			("Fill",	0, PUMP);			// customers entering the 4 pumps
CSemaphore ReturnHose	("Return",	0, PUMP);			// customers returning hose to pump
CSemaphore Exits		("Exits",	0, PUMP);			// amount of free/empty pumps

// pump class
class Pump : public ActiveClass {
private:
	int		credit_card[8];
	int		fuel_grade;
	int		fuel_amount;
	double	fuel_tank;
	const char *name;
	const char *foo;
//	CMutex	*KeyboardMutex;			// pointer to hidden mutex protecting the keyboard variables
	CPipe	*CustomerPipe;

	struct	pump_info {			// structure template for some data that we intend to write to the pipeline
		int		fuel_grade;
		double	cost_litre;
		double 	fuel_tank;
		int		fuel_amount;
		double 	price;
		const	char *names;
		int		credit[8];
	};
	struct pump_info *pump_data_pointer;
	CDataPool		 *pump_data_pool;

public:
	int pump_num;

	// constructor
	Pump(int i) {
		pump_num = i;
		// Pump to Station Datapool Connection
		printf("Pump %i attempting to create/use the datapool.....\n", pump_num);
		pump_data_pool = new CDataPool("__CustomerDataPool__" + pump_num, sizeof(struct pump_info));
		pump_data_pointer = (struct pump_info*)(pump_data_pool->LinkDataPool());
		//KeyboardMutex = new CMutex("__MonitorMutex__" + i);
		//printf("\nThread %d has arrived at Rendezvous; All pumps connected to memory pool\n", pump_num);		// do something after being released, i.e. print my threadnumber
		//r1.Wait();
	} // end constructor

	// selects fuel grade and verifies credit card
	void SwipeCC() {
		// simulate verification of credit card
		Sleep(100);
		if (pump_data_pointer->credit == NULL)
			printf("\nError: credit card for pump %i could not be verified.\n", pump_num);
		else 
			printf("\nCredit Card for pump %i verified and payment received.\n", pump_num);
	
		Swipe.Wait();
	} // end Swipe

	// adds fuel, then prints out amount of gas and cost
	void Fuel() {

		if (pump_data_pointer->credit != NULL) {
			for (int i = 0; i < (fuel_amount * 2); i++) {

				if		(fuel_grade == 0) { pump_data_pointer->price = grade1 * pump_data_pointer->fuel_tank; }
				else if (fuel_grade == 1) { pump_data_pointer->price = grade2 * pump_data_pointer->fuel_tank; }
				else if (fuel_grade == 2) { pump_data_pointer->price = grade3 * pump_data_pointer->fuel_tank; }
				else if (fuel_grade == 3) { pump_data_pointer->price = grade4 * pump_data_pointer->fuel_tank; }
				else {
					fuel_grade = 0;
					pump_data_pointer->price = grade1 * pump_data_pointer->fuel_tank;
				}

				if (fuel_grade == 0) {
					if(g1fuel > RF){
						g1fuel -= 0.5;
						pump_data_pointer->fuel_tank += 0.50;
						pump_data_pointer->cost_litre = grade1;
					}
					else {
						Refill = FALSE;
						TEXT_COLOUR(12, 0);
						printf("Tank 1 Empty...(enter 'R' to refill all tanks)\n");
						TEXT_COLOUR();

						while (input != 'R' && Refill == FALSE) {
							//cin.get(input);
							//KeyboardMutex->Wait();
						}

					}
				} // end if(fuel_grade == 0)

				if (fuel_grade == 1){
					if (g2fuel > RF) {
						g2fuel -= 0.5;
						pump_data_pointer->fuel_tank += 0.50;
						pump_data_pointer->cost_litre = grade2;
					}
					else {
						Refill = FALSE;
						TEXT_COLOUR(12, 0);
						printf("Tank 2 Empty...(enter 'R' to refill all tanks)\n");
						cin >> Refill;
						TEXT_COLOUR();

						while (input != 'R' && Refill == FALSE) {
							//cin.get(input);
							//KeyboardMutex->Wait();
						}

					}
				} // end if(fuel_grade == 1)

				if (fuel_grade == 2){
					if (g3fuel > RF) {
						g3fuel -= 0.5;
						pump_data_pointer->fuel_tank += 0.50;
						pump_data_pointer->cost_litre = grade3;
					}
					else {
						Refill = FALSE;
						TEXT_COLOUR(12, 0);
						printf("Tank 3 Empty...(enter 'R' to refill all tanks)\n");
						//cin >> Refill;
						TEXT_COLOUR();

						while (input != 'R' && Refill == FALSE) {
							//cin.get(input);
							//KeyboardMutex->Wait();
						}

					}
				} // end if(fuel_grade == 2)

				if (fuel_grade == 3){ 
					if (g4fuel > RF) {
						g4fuel -= 0.5;
						pump_data_pointer->fuel_tank += 0.50;
						pump_data_pointer->cost_litre = grade4;
					}
					else {
						Refill = FALSE;
						TEXT_COLOUR(12, 0);
						printf("Tank 4 Empty...(enter 'R' to refill all tanks)\n");
						//cin >> Refill;
						TEXT_COLOUR();

						while (input != 'R' && Refill == FALSE) {
							//cin.get(input);
							//KeyboardMutex->Wait();
						}
					
					}
				} // end if(fuel_grade == 3)

				Sleep(100);	// To simulate amount of time to fill up gas
			} // end for
		} // end if

		Quantity.push_back(pump_data_pointer->fuel_tank);
		Grade.push_back(pump_data_pointer->fuel_grade);
		/*for (int foo = 0; foo < 16; foo++) {
			CreditCard.push_back(pump_data_pointer->credit[foo]);
		}*/
		Fill.Wait();
	} // end Fuel

	int main(void) {
	while((Exits.Read() == 0) && (Refill == TRUE) ) {
		// Customer to Pump Pipeline Connections:
		CustomerPipe = new CPipe("Pipe" + pump_num, 1024);
		CustomerPipe->Read(&credit_card, sizeof(credit_card));
		CustomerPipe->Read(&fuel_grade,  sizeof(fuel_grade));
		CustomerPipe->Read(&fuel_amount, sizeof(fuel_amount));
		CustomerPipe->Read(&fuel_tank,	 sizeof(fuel_tank));
		CustomerPipe->Read(&name,		 sizeof(name));

		// Pump to Station Datapool Connections:
		pump_data_pointer->fuel_amount = fuel_amount;
		pump_data_pointer->fuel_grade = fuel_grade;
		pump_data_pointer->price = 0;
		pump_data_pointer->fuel_tank = 0;
		pump_data_pointer->cost_litre = fuel_grade;
		pump_data_pointer->names = name;
		foo = name;
		for (int i = 0; i < 7; i++) {
			pump_data_pointer->credit[i] = credit_card[i];
		}

		LineUp.Signal();		// lets LINE amount of customers into each pump line
		Swipe.Signal();			// swipes credit card and chooses fuel grade
		SwipeCC();

		RemoveHose.Signal();	// removes pump hose
		printf("Hose on pump %i removed\n", pump_num);

		Fill.Signal();			// waits for customer to use pump
		Fuel();					// gas station attendant signals pump to begin dispensing fuel at rate of 0.5 liter per second.}

		ReturnHose.Signal();
		printf("Hose on pump %i returned\n", pump_num);
		printf("\nPump: %i, Fuel Grade: %i, Amount: %.2fL, Total Cost = $%.2f\n", pump_num, fuel_grade, pump_data_pointer->fuel_tank, pump_data_pointer->price);

		TEXT_COLOUR(2, 0);
		printf("%s has driven away.\n", pump_data_pointer->names );
		//printf("Customer at pump %i has driven away.\n", pump_num);
		//printf("%s has driven away.\n", foo);
		TEXT_COLOUR();		
		Exits.Signal();		// lets customer leave
		//Empty.Wait();
	}
	return 0;
} // end main

};


// customer class
class Customer : public ActiveClass {
private:
	CPipe *CustomerPipe;
	int	credit_card[8];
	int	fuel_grade;
	int fuel_amount;
	double fuel_tank;
	const char *name;

public:
	int customer_num;
	int whatever;

	// constructor
	Customer(int i) { 
		whatever = (i % 4) + 1;
		customer_num = i;
		fuel_grade = customer_num * 8  % 3;
		fuel_amount = (customer_num * 101 + 15) % 70;
		fuel_tank = 0;
		name = n[ ((customer_num + 1)*3) % 16 ];

		for (int j = 0; j < 7; j++) {
			credit_card[j] = ((customer_num + 2 * 3) + (j * j + 9) + (customer_num + 3 * 7) * 133) % 9;
		}

		// Customer to Pump Connection
		CustomerPipe = new CPipe("Pipe" + whatever, 1024);
		CustomerPipe->Write(&credit_card,sizeof(credit_card));
		CustomerPipe->Write(&fuel_grade, sizeof(fuel_grade));
		CustomerPipe->Write(&fuel_amount,sizeof(fuel_amount));
		CustomerPipe->Write(&fuel_tank,  sizeof(fuel_tank));
		CustomerPipe->Write(&name,		 sizeof(name));
	}

	int main(void) {
		// Customer to Pump Connection
		CustomerPipe = new CPipe("Pipe" + whatever, 1024);
		CustomerPipe->Write(&credit_card,sizeof(credit_card));
		CustomerPipe->Write(&fuel_grade, sizeof(fuel_grade));
		CustomerPipe->Write(&fuel_amount,sizeof(fuel_amount));
		CustomerPipe->Write(&fuel_tank,  sizeof(fuel_tank));
		CustomerPipe->Write(&name,		 sizeof(name));
		
		LineUp.Wait();			// waits to use pump
		RemoveHose.Wait();		// removes pump hose

		// customers doin' their thing

		ReturnHose.Wait();		// returns pump hose
		Exits.Wait();			// customer gets outta there
		//Empty.Signal();		// pump empty for next customer
		return 0;
	}
};
