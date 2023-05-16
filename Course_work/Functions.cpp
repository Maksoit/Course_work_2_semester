#include <iostream>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
#include <string>

#include "Structs.h"
#define POINTS 11
#define INSIDE_MENUS 1
#define WIDTH 20
using namespace std;

bool* InitializeActive(bool*& active) {
	active = new bool[POINTS];
	for (int i = 0; i < POINTS; i++) active[i] = false;

	active[0] = true;
	active[POINTS - 1] = true;

	return active;
}

void SetColor(int attr) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, attr);
}

void PrintMenu(bool *active) {
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

bool IsRightDigit(string& str)
{
	return ( !str.empty() && all_of(str.begin(), str.end(), ::isdigit) );
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
	
	SetColor(7);
	for (int i = 0; i < end; i++) {
		switch (_case) {
		case 2: 
			cout << menu2[i] << endl;
			break;
		case 3:
			cout << menu3[i] << endl;
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
		cout << i << setw(WIDTH) << current->Id << setw(WIDTH) << current->Title << setw(WIDTH) << current->Price << setw(WIDTH) << current->Description << setw(WIDTH) << current->Available << endl;
		current = current->next;
	}
	cout << endl;
}

void PrintList(HPS head) {
	PPS current = head.Head;
	int i = 0;
	cout << "N" << setw(WIDTH) << "Id" << setw(WIDTH) << "Title" << setw(WIDTH) << "Count" << setw(WIDTH) << endl;
	while (current != NULL) {
		i++;
		cout << i << setw(WIDTH) << current->Id << setw(WIDTH) << current->Title << setw(WIDTH) << current->Count << setw(WIDTH) << endl;
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
	return choice;
}



int GetNewId() {
	//somehow
}

PPM Create() {
	PPM newProduct = new PM;
	if (newProduct) {
		newProduct->Id = GetNewId();

		cout << "Enter title of a product: ";
		cin >> newProduct->Title;

		cout << "Enter description of a product: ";
		cin >> newProduct->Description;

		cout << "Enter price: ";
		newProduct->Price = EnterNum();

		newProduct->Available = false;

		newProduct->next = NULL;
	}
	else cout << "\nError with creating new product!\n";
	return newProduct;
}

void AddFirst(HPC& head, PPC new_book) {
	new_book->next = head.Head;
	head.Head = new_book;
	head.count += 1;
}

void AddFirst(HPM& head, PPM new_book) {
	new_book->next = head.Head;
	head.Head = new_book;
	head.count += 1;
}

void AddAfter(HPC& head, PPC first_book, PPC second_book) {
	PPC temp = first_book->next;
	first_book->next = second_book;
	second_book->next = temp;
	head.count += 1;
}

void AddAfter(HPM& head, PPM first_book, PPM second_book) {
	PPM temp = first_book->next;
	first_book->next = second_book;
	second_book->next = temp;
	head.count += 1;
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