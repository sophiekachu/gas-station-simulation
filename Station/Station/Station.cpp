// Assignment 1		
// Name:		Sophia Ha
// Student ID:	41171142
// Demo Date:	Nov 8, 2018


#include	"..\..\rt.h"
#include	"Pump.h"
#include	<list>
#include	<stdio.h>

Pump p1(1), p2(2), p3(3), p4(4);
CMutex	*KeyboardMutex;

UINT __stdcall keyboard(void *args) {			// child  thread function
	while ( 1 ) {
		cin.get(input);
		//cin >> input;
		if (input == 'H') {
			list<double> amt_history = Quantity;
			list<int> grade_history = Grade;
			int tns = 1;

			TEXT_COLOUR(3, 0);
			cout << "History: \n";
			while( (!amt_history.empty() ) && (!grade_history.empty()) ) {
				cout << "Transaction: " << tns << "\nFuel Grade: " << grade_history.front() << "\n";
				grade_history.pop_front();
				cout << "Amount: " << amt_history.front() << "L\n\n";
				amt_history.pop_front();
				tns++;
			}
			TEXT_COLOUR();
			//input = NULL;
		}

		if (input == 'R') {
			g1fuel = g2fuel = g3fuel = g4fuel = LITRES;
			Refill = TRUE;
			printf("All tanks refueled.");
			TEXT_COLOUR();
			//input = NULL;
		}
		input == NULL;
	}
	return 0;
}

int main(void) {
	cout << "Change fuel prices? (y/n) \n";
	cin >> price_change;
	if (price_change == 'y') {
		cout << "Enter price of fuel grade 1: \n";
		cin >> grade1;
		cout << "Enter price of fuel grade 2: \n";
		cin >> grade2;
		cout << "Enter price of fuel grade 3: \n";
		cin >> grade3;
		cout << "Enter price of fuel grade 4: \n";
		cin >> grade4;
	}
	else {
		grade1 = 1.52;
		grade2 = 1.66;
		grade3 = 1.78;
		grade4 = 1.91;
	}

	CProcess pumps("D:\\Documents\\UBC\\CPEN333\\Assignments\\Assignment 1\\Station\\Debug\\Pumps.exe",	// pathlist to child program executable				
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);
	CThread *Input = new CThread(keyboard, ACTIVE);

	Customer *theCustomers[CUSTOMERS*4];

	for (int i = 0; i < 5; i++) {
		theCustomers[i] = new Customer(i);
		theCustomers[i]->Resume();
	}
	Sleep(100);

	p1.Resume();
	p2.Resume();

	for (int j = 6; j < 12; j++) {
		theCustomers[j] = new Customer(j);
		theCustomers[j]->Resume();
	}
	Sleep(100);

	p3.Resume();
	p4.Resume();

	p1.WaitForThread();
	p2.WaitForThread();
	p3.WaitForThread();
	p4.WaitForThread();

	return 0;
}