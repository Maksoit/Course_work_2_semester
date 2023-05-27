#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>

#include "Structs.h"
#include "Functions.h"

using namespace std;

int main()
{
	HPC headCart;
	HPM headMarket;
	HPS headStorage;
	bool mainFlag = true,*active = InitializeActive(active), *activeUser = InitializeActiveUser(activeUser);

	cout << "Login as:\n1 - User\n2 - Admin\n";
	switch (EnterInsideChoice(2)) {
	case 1: {
		while (mainFlag) {
			system("cls");
			PrintUserMenu(activeUser);
			switch (EnterChoice(activeUser)) {
			case 1: {
				headCart.Head = NULL;
				headMarket.Head = NULL;
				headStorage.Head = NULL;
				headCart.count = 0;
				headMarket.count = 0;
				headStorage.count = 0;

				LoadMarket(headMarket);
				LoadStorage(headStorage);

				for (int i = 0; i < POINTSUSER; i++) activeUser[i] = false;
				activeUser[1] = true;
				activeUser[2] = true;
				activeUser[3] = true;
				activeUser[POINTSUSER - 1] = true;
				cout << "Empty cart list created!\n\n";
				break;
			}
			case 2: {
				cout << "Now in your cart " << headCart.count << " products\n\n";
				break;
			}
			case 3: {
				cout << "1 - Print market\n2 - Print cart\n";
				switch (EnterInsideChoice(2)) {
				case 1:
					PrintList(headMarket);
					break;
				case 2:
					PrintList(headCart);
					break;
				}
				break;
			}
			case 4: {
				PrintInsideMenuUser(4, 3);
				string name;
				string prevName;
				if (!headCart.IsIntialized) {
					headCart.Head = NULL; headCart.count = 0; headCart.IsIntialized = true;
				}
				if (!headMarket.IsIntialized) {
					headMarket.Head = NULL; headMarket.count = 0; headMarket.IsIntialized = true;
				}
				if (!headStorage.IsIntialized) {
					headStorage.Head = NULL; headStorage.count = 0; headStorage.IsIntialized = true;
				}
				switch (EnterInsideChoice(3)) {
				case 1: {
					cout << "Enter name of product that you want to add first in your cart: ";
					cin >> name;
					AddFirst(headCart, MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				}
				case 2: {
					cout << "Enter name of product that you want to add in your cart: ";
					cin >> name;
					cout << "Enter name of product after that you want to add in your cart: ";
					cin >> prevName;
					AddAfter(headCart, SearchByName(prevName, headCart), MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				}
				case 3: {
					cout << "Enter name of product that you want to add last in your cart: ";
					cin >> name;
					AddLast(headCart, MarketToCart(SearchByName(name, headMarket)));
					cout << "You added that product!\n";
					break;
				}
				}
				cin.get();
				for (int i = 4; i < 8; i++) activeUser[i] = true;
				break;
			}
			case 5: {
				string title;
				cout << "Enter title of deleting product: ";
				cin >> title;
				PPC oldProduct = SearchByName(title, headCart);
				if (oldProduct) {
					Delete(headCart, oldProduct);
					cout << "\nProduct named " << title << " is deleted!\n\n";
					cin.get();
					if (not(headCart.count)) {
						for (int i = 0; i < POINTSUSER; i++) activeUser[i] = false;
						activeUser[1] = true;
						activeUser[2] = true;
						activeUser[3] = true;
						activeUser[POINTSUSER - 1] = true;
					}
				}
				else {
					cout << "There are no product with that title!\n"; cin.get();
				}
				break;
			}
			case 6: {
				string title;
				cout << "Enter title for searching: ";
				cin >> title;
				PPC product = SearchByName(title, headCart);
				cout << "Id" << setw(WIDTH) << "Title" << setw(WIDTH) << "Count" << endl;
				cout << product->Id << setw(WIDTH) << product->Title << setw(WIDTH) << product->count << endl;
				cin.get();
				break;
			}
			case 7: {
				string Title;
				cout << "Enter name of product, that you want to change: ";
				getline(cin, Title);
				Change(SearchByName(Title, headCart));
				break;
			}
			case 8: {
				PO order = Create(headCart);
				SaveOrder(order);
				break;
			}
			case 9: {
				cout << "Thanks for using my system!\nGoodbye!\nMV\n";
				mainFlag = false;
				break;
			}
			}
			cout << "\nPress any key to continue\n\n";
			cin.get();
		}
		break;
	}

	case 2: {
		while (mainFlag) {
			system("cls");
			PrintAdminMenu(active);
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
				active[9] = true;
				active[POINTS - 1] = true;
				cout << "Empty cart list, market list and storage list created!\n\n";
				break;
			case 2:
				PrintInsideMenu(2, 3);
				switch (EnterInsideChoice(3)) {
				case 1:
					cout << "Now in your cart " << headCart.count << " products\n\n";
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
				if (!headCart.IsIntialized) {
					headCart.Head = NULL; headCart.count = 0; headCart.IsIntialized = true;
				}
				if (!headMarket.IsIntialized) {
					headMarket.Head = NULL; headMarket.count = 0; headMarket.IsIntialized = true;
				}
				if (!headStorage.IsIntialized) {
					headStorage.Head = NULL; headStorage.count = 0; headStorage.IsIntialized = true;
				}
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
					cin.get();
					active[6] = true;
					active[7] = true;
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
					active[6] = true;
					break;
					}
				}
				default:
					cout << "Some error in main in switch in case 4\n";
					break;
				}
				active[6] = true;
				active[8] = true;
				break;
			}
			case 5: {
				PrintInsideMenu(5, 4);
				string title;
				switch (EnterInsideChoice(4)) {
				case 1:
				{
					cout << "Enter title of deleting product";
					cin >> title;
					PPC oldProduct = SearchByName(title, headCart);
					if (oldProduct) {
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
				case 3:
					DeleteAll(headCart);
					break;
				case 4:
					DeleteAll(headMarket);
					DeleteAll(headStorage);
					break;
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
				case 1: {
					cout << "Enter title for searching: ";
					cin >> title;
					PPC product = SearchByName(title, headCart);
					break;
				}
				case 2: {
					cout << "Enter title for searching: ";
					cin >> title;
					PPM product = SearchByName(title, headMarket);
					break;
				}
				case 3: {
					cout << "Enter title for searching: ";
					cin >> title;
					PPS product = SearchByName(title, headStorage);
					break;
				}
				default:
					cout << "Some error in main in switch in case 6\n\n";
					break;
				}
				break;
			}
			case 7: {
				PrintInsideMenu(7, 3);
				string Title;
				switch (EnterInsideChoice(3)) {
				case 1: {
					cout << "Enter name of product, that you want to change: ";
					getline(cin, Title);
					Change(SearchByName(Title, headCart));
					break;
				}
				case 2: {
					cout << "Enter name of product, that you want to change: ";
					getline(cin, Title);
					Change(SearchByName(Title, headMarket), headStorage);
					break;
				}
				case 3: {
					cout << "Enter name of product, that you want to change: ";
					getline(cin, Title);
					Change(SearchByName(Title, headStorage));
					break;
				}
				default:
					cout << "Some error in main in switch in case 7\n\n";
					break;
				}

				break;
			}
			case 8: {
				PO order = Create(headCart);
				SaveOrder(order);
				break;
			}
			case 9: {
				PrintInsideMenu(9, 2);
				switch (EnterInsideChoice(2)) {
				case 1:
					SaveCart(headCart);
					cout << "\nCart saved in cart.txt!\n\n";
					break;
				case 2:
					SaveMarket(headMarket);
					SaveStorage(headStorage);
					cout << "\Storage saved in storage.txt!\n\n";
					cout << "\nMarket saved in market.txt!\n\n";
					break;
				case 3:
					SaveStorage(headStorage);
					cout << "\Storage saved in storage.txt!\n\n";
					break;
				}
				break;
			}
			case 10: {
				PrintInsideMenu(10, 2);
				switch (EnterInsideChoice(2)) {
				case 1:
					LoadCart(headCart);
					cout << "\nCart loaded from cart.txt!\n\n";
					break;
				case 2:
					LoadMarket(headMarket);
					LoadStorage(headStorage);
					cout << "\nMarket loaded from market.txt!\n\n";
					cout << "\Storage loaded from storage.txt!\n\n";
					break;
				case 3:
					LoadStorage(headStorage);
					cout << "\Storage loaded from storage.txt!\n\n";
					break;
				}
				for (int i = 0; i < POINTS; i++) active[i] = false;
				active[1] = true;
				active[2] = true;
				active[3] = true;
				active[4] = true;
				active[5] = true;
				active[6] = true;
				active[8] = true;
				active[9] = true;
				active[POINTS - 1] = true;
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
			cout << "\nPress any key to continue\n\n";
			cin.get();
		}
		break;
		}
	}
}
