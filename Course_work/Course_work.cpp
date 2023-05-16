#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <string>

#include "Structs.h"
#include "Functions.h"

using namespace std;

int main()
{
	HPC headCart;
	HPM headMarket;
	HPS headStorage;
	bool mainFlag = true,*active = InitializeActive(active);

	while (mainFlag) {
		PrintMenu(active);
		switch (EnterChoice(active)) {
		case 1:
			headCart.Head = NULL;
			headMarket.Head = NULL;
			headStorage.Head = NULL;
			headCart.count = 0;
			headMarket.count = 0;
			headStorage.count = 0;

			for (int i = 0; i < POINTS; i++) active[i] = false;
			active[1] = true;
			active[2] = true;
			active[3] = true;
			active[4] = true;
			active[5] = true;
			active[POINTS - 1] = true;
			cout << "Empty cart list, market list and storage list created!\n\n";
			break;
		case 2:
			PrintInsideMenu(2, 3);
			switch (EnterInsideChoice(3)) {
			case 1: 
				cout << "Now in your cart " << headCart.count <<  " products\n\n";
				break;
			case 2:
				cout << "Now in your market " << headMarket.count << " products\n\n";
				break;
			case 3:
				cout << "Now in your storage " << headStorage.count << " products\n\n";
				break;
			default:
				cout << "Some error in main in switch in case 2\n";
				break;
			}
			break;
		case 3:
			PrintInsideMenu(3, 3);
			switch (EnterInsideChoice(3)) {
			case 1: 
				PrintList(headCart);
				break;
			case 2:
				PrintList(headMarket);
				break;
			case 3:
				PrintList(headStorage);
				break;
			default:
				cout << "Some error in main in switch in case 3\n";
				break;
			}
			break;
		case 4:
			PrintInsideMenu(4, 2);
			switch (EnterInsideChoice(2)) {
			case 1:
				cout << "1. Add first\n2. Add last\n3. Add after";
				switch (EnterInsideChoice(3)) {
				case 1:
					AddFirst(headCart, CartByName());
					break;
				case 2:
					break;
				case 3:
					break;
				}
				break;
			case 2:
				PrintList(headMarket);
				break;
			default:
				cout << "Some error in main in switch in case 3\n";
				break;
			}
			break;
		case 11:
			cout << "Thanks for using my system!\nGoodbye!\nMV\n";
			mainFlag = false;
			break;
		default:
			cout << "Some error in main in switch\n";
			break;
		}
	}
	
}
