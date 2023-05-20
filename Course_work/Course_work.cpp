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
		{
			PrintInsideMenu(4, 2);
			string name;
			string prevName;
			switch (EnterInsideChoice(2)) {
			case 1:
				cout << "1. Add first\n2. Add last\n3. Add after\n";
				switch (EnterInsideChoice(3)) {
				case 1:
					cout << "Enter name of product that you want to add first in your cart: ";
					cin >> name;
					AddFirst(headCart, MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				case 2:
					cout << "Enter name of product that you want to add last in your cart: ";
					cin >> name;
					AddLast(headCart, MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				case 3:
					cout << "Enter name of product that you want to add in your cart: ";
					cin >> name;
					cout << "Enter name of product after that you want to add in your cart: ";
					cin >> prevName;
					AddAfter(headCart, SearchByName(prevName, headCart), MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				}
				break;
			case 2:
			{
				cout << "1. Add first\n2. Add last\n3. Add after\n";
				PPM newMarketProduct;
				switch (EnterInsideChoice(3)) {
				case 1: {
					PPM newMarketProduct = Create(headMarket);
					AddFirst(headMarket, newMarketProduct);
					AddFirst(headStorage, MarketToStorage(newMarketProduct));
					cout << "You added that product!\n";
					break; }
				case 2: {
					PPM newMarketProduct = Create(headMarket);
					AddLast(headMarket, newMarketProduct);
					AddLast(headStorage, MarketToStorage(newMarketProduct));
					cout << "You added that product!\n";
					break; }
				case 3:
				{
					PPM newMarketProduct = Create(headMarket);
					string name;
					cout << "Enter title of product after that you want to add new product: ";
					cin >> name;
					AddAfter(headMarket, SearchByName(name, headMarket), newMarketProduct);
					AddAfter(headStorage, SearchByName(name, headStorage), MarketToStorage(newMarketProduct));
					cout << "You added that product!\n";
					break;
				}
				break;
				}
			}
			default:
				cout << "Some error in main in switch in case 4\n";
				break;
			}
			break;
		}
		case 5: {
			PrintInsideMenu(5, 2);
			string title;
			switch (EnterInsideChoice(2)) {
			case 1:
			{
				cout << "Enter title of deleting product";
				cin >> title;
				PPC oldProduct = SearchByName(title, headCart);
				if (not(oldProduct)) {
					Delete(headCart, oldProduct);
					cout << "\nProduct named " << title << " is deleted!\n\n";
					if (not(headCart.count)) {
						for (int i = 0; i < POINTS; i++) active[i] = false;
						active[1] = true;
						active[2] = true;
						active[3] = true;
						active[4] = true;
						active[5] = true;
						active[POINTS - 1] = true;
					}
				}
				else cout << "There are no product with that title!\n";
				break;
			}
			case 2:
			{
				cout << "Enter title of deleting product";
				cin >> title;
				PPM oldProduct = SearchByName(title, headMarket);
				if (not(oldProduct)) {
					Delete(headMarket, oldProduct);
					Delete(headStorage, MarketToStorage(oldProduct));
					cout << "\nProduct named " << title << " is deleted!\n\n";
					if (not(headCart.count)) {
						for (int i = 0; i < POINTS; i++) active[i] = false;
						active[1] = true;
						active[2] = true;
						active[3] = true;
						active[4] = true;
						active[5] = true;
						active[POINTS - 1] = true;
					}
				}
				else cout << "There are no product with that title!\n";
				break;
			}
			default:
				cout << "Some error in main in switch in case 5\n\n";
				break;
			}
			break;
		}
		case 6: {
			PrintInsideMenu(6, 3);
			string title;
			switch (EnterInsideChoice(3)) {
			case 1:
				cout << "Enter title for searching: ";
				cin >> title;
				PPC product = SearchByName(title, headCart);
				break;
			case 2:
				cout << "Enter title for searching: ";
				cin >> title;
				PPM product = SearchByName(title, headMarket);
				break;
			case 3:
				cout << "Enter title for searching: ";
				cin >> title;
				PPS product = SearchByName(title, headStorage);
				break;
			default:
				cout << "Some error in main in switch in case 6\n\n";
				break;
			}
			break;
		}
		case 7: {
			PrintInsideMenu(7, 3);
			switch (EnterInsideChoice(3)) {
			case 1: {

				break;
			}
			case 2: {

				break;
			}
			case 3: {

				break;
			}
			default:
				cout << "Some error in main in switch in case 7\n\n";
				break;
			}

			break;
		}
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
