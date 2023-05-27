#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
#include <string>

#include "Structs.h"
#define POINTS 11
#define POINTSUSER 9
#define WIDTH 20
using namespace std;

bool* InitializeActive(bool*& active) {
	active = new bool[POINTS];
	for (int i = 0; i < POINTS; i++) active[i] = false;

	active[0] = true;
	active[POINTS - 1] = true;

	active[9] = true;

	return active;
}

bool* InitializeActiveUser(bool*& activeUser) {
	activeUser = new bool[POINTSUSER];
	for (int i = 0; i < POINTSUSER; i++) activeUser[i] = false;

	activeUser[0] = true;
	activeUser[POINTSUSER - 1] = true;

	return activeUser;
}

void SetColor(int attr) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, attr);
}

void PrintAdminMenu(bool *active) {
	const char* Menu[] = {
	"1. Create empty market and empty storage",
	"2. Statictic",
	"3. Print",
	"4. Add",
	"5. Delete",
	"6. Search",
	"7. Change",
	"8. Buy",
	"9. Save in binary files",
	"10. Load from binary files",
	"11. Exit"
	};
	for (int i = 0; i < POINTS; i++) {
		active[i] ? SetColor(7) : SetColor(8);
		cout << Menu[i] << endl;
	}
	SetColor(7);
	cout << endl;
}

void PrintUserMenu(bool* activeUser) {
	const char* Menu[] = {
	"1. Create cart and load market",
	"2. Statictic",
	"3. Print",
	"4. Add",
	"5. Delete",
	"6. Search",
	"7. Change",
	"8. Buy",
	"9. Exit"
	};
	for (int i = 0; i < POINTSUSER; i++) {
		activeUser[i] ? SetColor(7) : SetColor(8);
		cout << Menu[i] << endl;
	}
	SetColor(7);
	cout << endl;
}

bool IsRightDigit(string& str)
{
	return ( !str.empty() && all_of(str.begin(), str.end(), ::isdigit) );
}

bool IsAlreadyIn(HPM headMarket, PPM product) {
	PPM q = headMarket.Head;
	while (q) {
		if ((q->Title == product->Title) && (q->Description == product->Description) && (q->Id == product->Id) &&
			q->Price == product->Price) return true;
		q = q->next;
	}
	return false;
}

bool IsAlreadyIn(HPS headStorage, PPS product) {
	PPS q = headStorage.Head;
	while (q) {
		if (not(q->Title == product->Title) && not(q->Count == product->Count) && not(q->Id == product->Id)) return true;
		q = q->next;
	}
	return false;
}

bool IsAlreadyIn(HPC headCart, PPC product) {
	PPC q = headCart.Head;
	while (q) {
		if (not(q->Title == product->Title) && not(q->count == product->count) && not(q->Id == product->Id) &&
			q->Price == product->Price && q->PriceForOne == product->PriceForOne) return true;
		q = q->next;
	}
	return false;
}

int EnterNum() {
	string buff;
	cin >> buff;
	while (not(IsRightDigit(buff))) {
		cout << "\nIncorrect input, try again: ";
		cin >> buff;
	}
	return stoi(buff);
}

int EnterChoice(bool *active) {
	int choice;
	cout << "Enter your choice: ";
	choice = EnterNum();
	while (choice < 1 || choice > POINTS || not(active[choice - 1])) {
		cout << "You cant pick this point!\n";
		cout << "Enter your choice: ";
		choice = EnterNum();
	}
	cout << endl;
	cin.get();
	return choice;
}

void PrintInsideMenu(int _case, int end) {
	string menu2[] {
	"1. Count products in cart",
	"2. Count products in market",
	"3. Count products in storage",
	};
	string menu3[]{
	"1. Print products in cart",
	"2. Print products in market",
	"3. Print products in storage",
	};
	string menu4[]{
	"1. Add products in cart",
	"2. Add products in market",
	};
	string menu5[]{
		"1. Delete product from cart",
		"2. Delete product from market and storage",
		"3. Delete all cart",
		"4. Delete all market and storage"
	};
	string menu6[]{
		"1. Search in cart",
		"2. Search in market",
		"3. Search in storage"
	};
	string menu7[]{
		"1. Change in cart",
		"2. Change in market",
		"3. Change in storage"
	};
	string menu9[]{
		"1. Save Cart",
		"2. Save Market",
		"3. Save Storage"
	};
	string menu10[]{
		"1. Load Cart",
		"2. Load Market",
		"3. Load Storage"
	};
	
	SetColor(7);
	for (int i = 0; i < end; i++) {
		switch (_case) {
		case 2: 
			cout << menu2[i] << endl;
			break;
		case 3:
			cout << menu3[i] << endl;
			break;
		case 4: 
			cout << menu4[i] << endl;
			break;
		case 5:
			cout << menu5[i] << endl;
			break;
		case 6:
			cout << menu6[i] << endl;
			break;
		case 7:
			cout << menu7[i] << endl;
			break;
		case 8:
			break;
		case 9:
			cout << menu9[i] << endl;
			break;
		case 10:
			cout << menu10[i] << endl;
			break;
		}
	}
	cout << endl;
}

void PrintInsideMenuUser(int _case, int end) {
	string menu4[]{
	"1. Add first",
	"2. Add after",
	"3. Add last",
	};

	SetColor(7);
	for (int i = 0; i < end; i++) {
		switch (_case) {
		case 4:
			cout << menu4[i] << endl;
			break;
		}
	}
	cout << endl;
}

void PrintList(HPC head) {
	PPC current = head.Head;
	int i = 0;
	cout << "N" << setw(WIDTH) << "Id" << setw(WIDTH) << "Title" << setw(WIDTH) << "Price for one" << setw(WIDTH) << "Price" << setw(WIDTH) << "Count" << endl;
	while (current != NULL) {
		i++;
		cout << i << setw(WIDTH) << current->Id << setw(WIDTH) << current->Title << setw(WIDTH) << current->PriceForOne << setw(WIDTH) << current->Price << setw(WIDTH) << current->count << endl;
		current = current->next;
	}
	cout << endl;
}

void PrintList(HPM head) {
	PPM current = head.Head;
	int i = 0;
	cout << "N" << setw(WIDTH) << "Id" << setw(WIDTH) << "Title" << setw(WIDTH) << "Price" << setw(WIDTH) << "Description" << setw(WIDTH) << "Available" << endl;
	while (current != NULL) {
		i++;
		current->Available ? SetColor(7) : SetColor(8);
		cout << i << setw(WIDTH) << current->Id << setw(WIDTH) << current->Title << setw(WIDTH) << current->Price << setw(WIDTH) << current->Description << setw(WIDTH) << current->Available << endl;
		SetColor(7);
		current = current->next;
	}
	cout << endl;
}

void PrintList(HPS head) {
	PPS current = head.Head;
	int i = 0;
	cout << "N" << setw(WIDTH) << "Id" << setw(WIDTH) << "Title" << setw(WIDTH) << "Count" << endl;
	while (current != NULL) {
		i++;
		cout << i << setw(WIDTH) << current->Id << setw(WIDTH) << current->Title << setw(WIDTH) << current->Count << endl;
		current = current->next;
	}
	cout << endl;
}

int EnterInsideChoice(int end) {
	int choice;
	cout << "Enter your choice: ";
	choice = EnterNum();

	while (choice < 1 || choice > end) {
		cout << "You cant pick this point!\n";
		cout << "Enter your choice: ";
		choice = EnterNum();
	}
	cout << endl;
	cin.get();
	return choice;
}



int GetNewId(HPM headMarket) {
	int maxId = 0;
	PPM current = headMarket.Head;
	while (current) {
		maxId = max(maxId, current->Id);
		current = current->next;
	}
	maxId++;
	return  maxId;
}





PPM Create(HPM headMarket) {
	PPM newProduct = new PM;
	if (newProduct) {
		newProduct->Id = GetNewId(headMarket);

		cout << "Enter title of a product: ";
		cin >> newProduct->Title;

		cout << "Enter description of a product: ";
		cin >> newProduct->Description;

		cout << "Enter price: ";
		newProduct->Price = EnterNum();

		newProduct->Available = false;

		newProduct->next = NULL;
		return newProduct;
	}
	else cout << "\nError with creating new product!\n";
	return NULL;
}



PPS MarketToStorage(PPM newProduct) {
	PPS newStorage = new PS;
	if (newStorage) {
		newStorage->Id = newProduct->Id;
		newStorage->Title = newProduct->Title;
		newStorage->Count = 0;
		newStorage->next = NULL;
	}
	else cout << "\nError with creating new product!\n";
	return newStorage;
}

PPC MarketToCart(PPM marketProduct) {
	if (marketProduct && marketProduct->Available) {
		PPC cartProduct = new PC;
		cartProduct->Id = marketProduct->Id;
		cartProduct->Title = marketProduct->Title;
		cartProduct->count = 1;
		cartProduct->Price = marketProduct->Price;
		cartProduct->PriceForOne = marketProduct->Price;
		cartProduct->next = NULL;
		return cartProduct;
	}
	return NULL;
}

void AddFirst(HPC& head, PPC new_book) {
	if (new_book && !IsAlreadyIn(head, new_book)) {
		new_book->next = head.Head;
		head.Head = new_book;
		head.count += 1;
	}
}

void AddFirst(HPM& head, PPM new_book) {
	if (new_book) {
		new_book->next = head.Head;
		head.Head = new_book;
		head.count += 1;
	}
}

void AddFirst(HPS& head, PPS new_book) {
	if (new_book) {
		new_book->next = head.Head;
		head.Head = new_book;
		head.count += 1;
	}
}

void AddFirst(HO& head, PO new_book) {
	if (new_book) {
		new_book->next = head.Head;
		head.Head = new_book;
		head.count += 1;
	}
}

void AddAfter(HPC& head, PPC first_book, PPC second_book) {
	if (first_book && second_book) {
		PPC temp = first_book->next;
		first_book->next = second_book;
		second_book->next = temp;
		head.count += 1;
	}
}

void AddAfter(HPM& head, PPM first_book, PPM second_book) {
	if (first_book && second_book) {
		PPM temp = first_book->next;
		first_book->next = second_book;
		second_book->next = temp;
		head.count += 1;
	}
}

void AddAfter(HPS& head, PPS first_book, PPS second_book) {
	if (first_book && second_book) {
		PPS temp = first_book->next;
		first_book->next = second_book;
		second_book->next = temp;
		head.count += 1;
	}
}

void AddAfter(HO& head, PO first_book, PO second_book) {
	if (first_book && second_book) {
		PO temp = first_book->next;
		first_book->next = second_book;
		second_book->next = temp;
		head.count += 1;
	}
}

void AddLast(HPC& head, PPC new_book) {
	PPC temp = head.Head;
	if (not(temp)) AddFirst(head, new_book);
	else {
		while (temp->next) {
			temp = temp->next;
		}
		AddAfter(head, temp, new_book);
	}
}

void AddLast(HPM& head, PPM new_book) {
	PPM temp = head.Head;
	if (not(temp)) AddFirst(head, new_book);
	else {
		while (temp->next) {
			temp = temp->next;
		}
		AddAfter(head, temp, new_book);
	}
}

void AddLast(HPS& head, PPS new_book) {
	PPS temp = head.Head;
	if (not(temp)) AddFirst(head, new_book);
	else {
		while (temp->next) {
			temp = temp->next;
		}
		AddAfter(head, temp, new_book);
	}
}

void AddLast(HO& head, PO new_book) {
	PO temp = head.Head;
	if (not(temp)) AddFirst(head, new_book);
	else {
		while (temp->next) {
			temp = temp->next;
		}
		AddAfter(head, temp, new_book);
	}
}

PPC SearchByName(string name, HPC head) {
	PPC current = head.Head;
	while (current && current->Title != name) current = current->next;

	return current;
}

PPM SearchByName(string name, HPM head) {
	PPM current = head.Head;
	while (current && current->Title != name) current = current->next;

	return current;
}

PPS SearchByName(string name, HPS head) {
	PPS current = head.Head;
	while (current && current->Title != name) current = current->next;

	return current;
}



void Delete(HPC &head, PPC oldProduct) {
	if (oldProduct) {
		if (head.Head == oldProduct) {
			PPC temp = oldProduct->next;
			delete (oldProduct);
			head.Head = temp;
		}
		else {
			PPC prevOldProduct = head.Head;
			while (prevOldProduct->next != oldProduct) {
				prevOldProduct = prevOldProduct->next;
			}
			PPC temp = oldProduct->next;
			delete (oldProduct);
			prevOldProduct->next = temp;
		}
		head.count -= 1;
	}
}

void Delete(HPM &head, PPM oldProduct) {
	if (head.Head == oldProduct) {
		PPM temp = oldProduct->next;
		delete (oldProduct);
		head.Head = temp;
	}
	else {
		PPM prevOldProduct = head.Head;
		while (prevOldProduct->next != oldProduct) {
			prevOldProduct = prevOldProduct->next;
		}
		PPM temp = oldProduct->next;
		delete (oldProduct);
		prevOldProduct->next = temp;
	}
	head.count -= 1;
}

void Delete(HPS &head, PPS oldProduct) {
	if (head.Head == oldProduct) {
		PPS temp = oldProduct->next;
		delete (oldProduct);
		head.Head = temp;
	}
	else {
		PPS prevOldProduct = head.Head;
		while (prevOldProduct->next != oldProduct) {
			prevOldProduct = prevOldProduct->next;
		}
		PPS temp = oldProduct->next;
		delete (oldProduct);
		prevOldProduct->next = temp;
	}
	head.count -= 1;
}

void DeleteAll(HPC &headCart) {
	PPC temp = headCart.Head;
	while (temp) {
		PPC temp2 = temp;
		temp = temp->next;
		delete (temp2);
		}
}

void DeleteAll(HPM& headMarket) {
	PPM temp = headMarket.Head;
	while (temp) {
		PPM temp2 = temp;
		temp = temp->next;
		delete (temp2);
	}
}

void DeleteAll(HPS& headStorage) {
	PPS temp_ = headStorage.Head;
	while (temp_) {
		PPS temp2_ = temp_;
		temp_ = temp_->next;
		delete (temp2_);
	}
	headStorage.Head = NULL;
}

void DeleteAll(HO& headOrder) {
	PO temp = headOrder.Head;
	while (temp) {
		PO temp2 = temp;
		temp = temp->next;
		delete (temp2);
	}
}


void Change(PPC product) {
	if (product) {
		int newCount;
		cout << "Enter new count: ";
		cin >> newCount;

		product->count = newCount;
		product->Price = product->PriceForOne * newCount;
	}
}

void Change(PPS product) {
	if (product) {
		int newCount;
		cout << "Enter new count: ";
		cin >> newCount;

		product->Count = newCount;
	}
}

void Change(PPS product, string title, int newCount) {
	if (product) {
		product->Title = title;
		product->Count = newCount;
	}
}

void Change(PPM product, HPS headStorage) {
	if (product) {
		cout << "What do you want to change?\n1. Title\n2. Description\n 3. Price\n4. Avaible\n";
		switch (EnterInsideChoice(4)) {
		case 1: {
			cout << "Enter new Title: ";
			string newTitle;
			getline(cin, newTitle);

			PPS storage = SearchByName(product->Title, headStorage);
			Change(storage, newTitle, storage->Count);

			product->Title = newTitle;


			break;
		}
		case 2: {
			cout << "Enter New Description: ";
			string NewDescription;
			getline(cin, NewDescription);
			product->Description = NewDescription;
			break;
		}
		case 3: {
			cout << "Enter New Price: ";
			int newPrice;
			newPrice = EnterNum();
			product->Price = newPrice;
			break;
		}
		case 4: {
			cout << "Enter new Avaible: ";
			int newAvaible;
			newAvaible = EnterNum();
			product->Available = newAvaible;
			break;
		}
		}
	}
}









void SaveMarket(HPM headMarket) {
	ofstream file("Market.txt", ios::binary | ios::out);
	if (file.is_open()) {
		PPM temp = headMarket.Head;
		while (temp != NULL) {
			file.write((char*)&(*temp), sizeof((*temp)));
			temp = temp->next;
		}
		file.close();
	}
}

void SaveStorage(HPS headStorage) {
	ofstream file("Storage.txt", ios::binary | ios::out);
	if (file.is_open()) {
		PPS temp = headStorage.Head;
		while (temp != NULL) {
			file.write((char*)&(*temp), sizeof((*temp)));
			temp = temp->next;
		}
		file.close();
	}
}

void SaveCart(HPC headCart) {
	ofstream file("Cart.txt", ios::binary | ios::out);
	if (file.is_open()) {
		PPC temp = headCart.Head;
		while (temp != NULL) {
			file.write((char*)&(*temp), sizeof((*temp)));
			temp = temp->next;
		}
		file.close();
	}
}

void SaveOrder(PO order) {
	ofstream file("Order.txt", ios::binary | ios::app);
	if (file.is_open()) {
		file.write((char*)&(*order), sizeof((*order)));
		file.close();
	}
	else cout << "Error with saving your order!\n";
}

void LoadMarket(HPM &headMarket) {
	if (not(headMarket.IsIntialized)) {
		headMarket.Head = NULL;
		headMarket.count = 0;
		headMarket.IsIntialized = true;
	}

	ifstream file("Market.txt", ios::binary | ios::in);

	if (file.is_open() && not(file.peek() == EOF)) {
		while (file.peek() != EOF) {
			PPM temp = new PM;
			if (headMarket.count == 0) {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				AddFirst(headMarket, temp);
			}
			else {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				if (not(IsAlreadyIn(headMarket, temp))) AddLast(headMarket, temp);
			}
		}
		file.close();
	}
	else cout << "Empty file or can't open!\n\n";
}

void LoadStorage(HPS& headStorage) {
	if (not(headStorage.IsIntialized)) {
		headStorage.Head = NULL;
		headStorage.count = 0;
		headStorage.IsIntialized = true;
	}

	ifstream file("Storage.txt", ios::binary | ios::in);

	if (file.is_open() && not(file.peek() == EOF)) {
		while (file.peek() != EOF) {
			PPS temp = new PS;
			if (headStorage.count == 0) {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				AddFirst(headStorage, temp);
			}
			else {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				if (not(IsAlreadyIn(headStorage, temp))) AddLast(headStorage, temp);
			}
		}
		file.close();
	}
	else cout << "Empty file or can't open!\n\n";
}

void LoadCart(HPC& headCart) {
	if (not(headCart.IsIntialized)) {
		headCart.Head = NULL;
		headCart.count = 0;
		headCart.IsIntialized = true;
	}

	ifstream file("Cart.txt", ios::binary | ios::in);

	if (file.is_open() && not(file.peek() == EOF)) {
		while (file.peek() != EOF) {
			PPC temp = new PC;
			if (headCart.count == 0) {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				AddFirst(headCart, temp);
			}
			else {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				if (not(IsAlreadyIn(headCart, temp))) AddLast(headCart, temp);
			}
		}
		file.close();
	}
	else cout << "Empty file or can't open!\n\n";
}

void LoadOrder(HO& headOrder) {
	if (not(headOrder.IsIntialized)) {
		headOrder.Head = NULL;
		headOrder.count = 0;
		headOrder.IsIntialized = true;
	}

	ifstream file("Order.txt", ios::binary | ios::in);

	if (file.is_open() && not(file.peek() == EOF)) {
		while (file.peek() != EOF) {
			PO temp = new O;
			PO right = new O;
			if (headOrder.count == 0) {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;

				right->Id = temp->Id;
				right->next = NULL;
				AddFirst(headOrder, right);
			}
			else {
				file.read((char*)&(*temp), sizeof((*temp)));
				temp->next = NULL;
				right->Id = temp->Id;
				right->next = NULL;
				AddLast(headOrder, right);
			}
		}
		file.close();
	}
	else cout << "Empty file or can't open!\n\n";
}

int GetNewId() {
	HO tempHead;
	tempHead.count = 0;
	tempHead.IsIntialized = true;
	tempHead.Head = NULL;

	LoadOrder(tempHead);
	int maxId = 0;
	PO current = tempHead.Head;
	while (current) {
		maxId = max(maxId, current->Id);
		current = current->next;
	}
	maxId++;

	DeleteAll(tempHead);
	return  maxId;
}

PO Create(HPC headCart) {
	PO newOrder = new O;
	if (newOrder) {
		newOrder->Id = GetNewId();
		newOrder->next = NULL;

		vector <PC> cart;
		PPC current = headCart.Head;
		for (int i = 0; i < headCart.count; i++) {
			cart.push_back((*current));
			current = current->next;
		}

		newOrder->Cart = cart;
		return newOrder;
	}
	return NULL;
}