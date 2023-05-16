//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <Windows.h>
//#define POINTS 11
//#define WIDTH 20
//using namespace std;
//
//struct Book {
//	char name[100];
//	char author[50];
//	int year;
//	char publisher[100];
//	int pages;
//
//	Book* next;
//};
//typedef Book* PBook;
//
//struct Head_Book {
//	PBook first;
//	int quantity_of_elements;
//};
//
//void SetColor(int attr) {
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, attr);
//}
//
//bool is_right_digit(char buff[]) {
//	for (int i = 0; i < strlen(buff); i++) {
//		if (not(isdigit(buff[i]))) return false;
//	}
//	return true;
//}
//
//int enter_num() {
//	char buff[200];
//	cin.getline(buff, 200);
//	while (not(is_right_digit(buff))) {
//		cout << "\nIncorrect input, try again: ";
//		cin.getline(buff, 200);
//	}
//	return atoi(buff);
//}
//
//void PrintMenu(bool active[]) {
//	const char* Menu[] = {
//	"1. Create empty list",
//	"2. Count elements",
//	"3. Print list",
//	"4. Add book in list",
//	"5. Delete book of list",
//	"6. Search book by",
//	"7. Save list in binary file",
//	"8. Load list from binary file",
//	"9. ??????",
//	"10. Delete list",
//	"11. Exit"
//	};
//
//	for (int i = 0; i < POINTS; i++) {
//		active[i] ? SetColor(7) : SetColor(8);
//		cout << Menu[i] << endl;
//	}
//	SetColor(7);
//	cout << endl;
//}
//
//void Print_books(Head_Book head) {
//	PBook temp = head.first;
//	int i = 0;
//	cout << "N" << setw(WIDTH) << "Name" << setw(WIDTH) << "Author" << setw(WIDTH) << "Year of publish" << setw(WIDTH) << "Publisher" << setw(WIDTH) << "Pages" << endl;
//	while (temp != NULL) {
//		i++;
//		cout << i << setw(WIDTH) << temp->name << setw(WIDTH) << temp->author << setw(WIDTH) << temp->year << setw(WIDTH) << temp->publisher << setw(WIDTH) << temp->pages << endl;
//		temp = temp->next;
//	}
//}
//
//int EnterChoice(bool active[]) {
//	int n;
//	cout << "Enter your choice: ";
//	n = enter_num();
//	while (n < 1 || n > POINTS || not(active[n - 1])) {
//		cout << "You cant pick this point!\n";
//		cout << "Enter your choice: ";
//		n = enter_num();
//	}
//	cout << endl;
//	return n;
//}
//
//int EnterInsideChoice(Head_Book head, int ver) {
//	int InsideChoice;
//	bool zero_el = head.quantity_of_elements == 0;
//	switch (ver) {
//	case 4:
//		cout << "1. At start\n2. At end\n";
//
//		if (zero_el) SetColor(8);
//		cout << "3. After i\n";
//		SetColor(7);
//		cout << "Enter your choice : ";
//		break;
//	case 6:
//		cout << "1. Name\n2. Author\n3. Year of publishing\nEnter your choice: ";
//		break;
//	}
//
//	InsideChoice = enter_num();
//	while ((ver == 4 && (InsideChoice < 1 || InsideChoice >(3 - (zero_el)))) || (ver == 6 && (InsideChoice < 1 || InsideChoice > 3))) {
//		cout << "You cant pick that point!\nEnter your choice: ";
//		InsideChoice = enter_num();
//	}
//	return InsideChoice;
//}
//
//
//
//PBook create_book() {
//	PBook new_book = new Book;
//	if (new_book) {
//		char buff[200];
//		cout << "Enter name of a book: ";
//		//cin.get();
//		cin.getline(buff, 100);
//		strcpy(new_book->name, buff);
//
//		cout << "Enter author of a book: ";
//		cin.getline(buff, 50);
//		strcpy(new_book->author, buff);
//
//		cout << "Enter year, when book published: ";
//		new_book->year = enter_num();
//
//		cout << "Enter publisher of a book: ";
//		cin.getline(buff, 100);
//		strcpy(new_book->publisher, buff);
//
//		cout << "Enter count of pages in a book: ";
//		new_book->pages = enter_num();
//
//		new_book->next = NULL;
//	}
//	else cout << "\nError with creating new book!\n";
//	return new_book;
//}
//
//void add_first_book(Head_Book& head, PBook new_book) {
//	new_book->next = head.first;
//	head.first = new_book;
//	head.quantity_of_elements += 1;
//}
//
//void add_after_book(Head_Book& head, PBook first_book, PBook second_book) {
//	PBook temp = first_book->next;
//	first_book->next = second_book;
//	second_book->next = temp;
//	head.quantity_of_elements += 1;
//}
//
//void add_last_book(Head_Book& head, PBook new_book) {
//	PBook temp = head.first;
//	if (not(temp)) add_first_book(head, new_book);
//	else {
//		while (temp->next) {
//			temp = temp->next;
//		}
//		add_after_book(head, temp, new_book);
//	}
//
//}
//
//void delete_book(Head_Book& head, PBook old_book) {
//	if (head.first == old_book) {
//		PBook temp = old_book->next;
//		delete (old_book);
//		head.first = temp;
//	}
//	else {
//		PBook prev_old_book = head.first;
//		while (prev_old_book->next != old_book) {
//			prev_old_book = prev_old_book->next;
//		}
//		PBook temp = old_book->next;
//		delete (old_book);
//		prev_old_book->next = temp;
//	}
//
//	head.quantity_of_elements -= 1;
//}
//
//void delete_book_list(Head_Book head) {
//	PBook temp = head.first;
//	while (temp) {
//		PBook temp2 = temp;
//		temp = temp->next;
//		delete (temp2);
//	}
//}
//
//PBook search_book_by_sequence_number(Head_Book head, int sequence_number) {
//	bool is_correctly = sequence_number > 0 && sequence_number <= head.quantity_of_elements;
//	PBook book = head.first;
//	if (is_correctly) {
//		int n = 1;
//		while ((book->next) && n < sequence_number) {
//			book = book->next;
//			n++;
//		}
//	}
//	else return NULL;
//	return book;
//}
//
//PBook search_book_by_name(Head_Book head, char name[100]) {
//	PBook searched_book = head.first;
//	while (searched_book && strcmp(searched_book->name, name)) {
//		searched_book = searched_book->next;
//	}
//	return searched_book;
//}
//
//PBook search_book_by_author(Head_Book head, char author[50]) {
//	PBook searched_book = head.first;
//	while (searched_book && strcmp(searched_book->author, author)) {
//		searched_book = searched_book->next;
//	}
//	return searched_book;
//}
//
//PBook search_book_by_year(Head_Book head, int year) {
//	PBook searched_book = head.first;
//	while (searched_book && (searched_book->year) != year) {
//		searched_book = searched_book->next;
//	}
//	return searched_book;
//}
//
//int main() {
//	Head_Book head;
//	bool flag = true, active[11];
//	active[0] = true;
//	active[7] = true;
//	active[10] = true;
//	for (int i = 1; i < 7; i++) active[i] = false;
//	active[8] = false; active[9] = false;
//
//	while (flag) {
//		PrintMenu(active);
//		switch (EnterChoice(active)) {
//		case 1:
//			head.first = NULL;
//			head.quantity_of_elements = 0;
//			active[0] = false;
//			for (int i = 1; i < 4; i++) active[i] = true;
//			active[6] = true; active[9] = true;
//			active[7] = false; active[10] = false;
//			cout << "Empty list created!\n\n";
//			break;
//		case 2:
//			cout << "Now in your list " << head.quantity_of_elements << " books!\n\n";
//			break;
//		case 3:
//			Print_books(head);
//			cout << endl;
//			break;
//		case 4:
//			switch (EnterInsideChoice(head, 4)) {
//			case 1:
//				add_first_book(head, create_book());
//				break;
//			case 2:
//				add_last_book(head, create_book());
//				break;
//			case 3:
//				int sequence_number;
//				cout << "Enter number, after which you want add book: ";
//				sequence_number = enter_num();
//				PBook Book_before = search_book_by_sequence_number(head, sequence_number);
//				if (Book_before) add_after_book(head, Book_before, create_book());
//				else cout << "There are no book with that number!\n";
//				break;
//			}
//			cout << "\nDone!\n\n";
//			active[4] = true;
//			active[5] = true;
//			break;
//		case 5: {
//			int number;
//			cout << "Enter number, which one you want to delete: ";
//			number = enter_num();
//			PBook old_node = search_book_by_sequence_number(head, number);
//			if (not(old_node)) {
//				delete_book(head, old_node);
//				cout << "\nBook number " << number << " is deleted!\n\n";
//				if (not(head.quantity_of_elements)) {
//					active[4] = false;
//					active[5] = false;
//				}
//			}
//			else cout << "There are no book with that number!\n";
//			break; }
//		case 6:
//			switch (EnterInsideChoice(head, 6)) {
//			case 1: {
//				char name[100];
//				cout << "Enter name: ";
//				cin >> name;
//				PBook searched = search_book_by_name(head, name);
//				if (searched) {
//					cout << "Name" << setw(WIDTH) << "Author" << setw(WIDTH) << "Year of publish" << setw(WIDTH) << "Publisher" << setw(WIDTH) << "Pages" << endl;
//					cout << searched->name << setw(WIDTH) << searched->author << setw(WIDTH) << searched->year << setw(WIDTH) << searched->publisher << setw(WIDTH) << searched->pages << endl;
//				}
//				else cout << "No book with that name!\n\n";
//				break; }
//			case 2: {
//				char author[50];
//				cout << "Enter author: ";
//				cin >> author;
//				PBook searched = search_book_by_author(head, author);
//				if (searched) {
//					cout << "Name" << setw(WIDTH) << "Author" << setw(WIDTH) << "Year of publish" << setw(WIDTH) << "Publisher" << setw(WIDTH) << "Pages" << endl;
//					cout << searched->name << setw(WIDTH) << searched->author << setw(WIDTH) << searched->year << setw(WIDTH) << searched->publisher << setw(WIDTH) << searched->pages << endl;
//				} cout << "No book with that author!\n\n";
//				break; }
//			case 3: {
//				int year;
//				cout << "Enter year: ";
//				cin >> year;
//				PBook searched = search_book_by_year(head, year);
//				if (searched) {
//					cout << "Name" << setw(WIDTH) << "Author" << setw(WIDTH) << "Year of publish" << setw(WIDTH) << "Publisher" << setw(WIDTH) << "Pages" << endl;
//					cout << searched->name << setw(WIDTH) << searched->author << setw(WIDTH) << searched->year << setw(WIDTH) << searched->publisher << setw(WIDTH) << searched->pages << endl;
//				}
//				else cout << "No book with that year!\n\n";
//				break; }
//			}
//			break;
//		case 7: {
//			ofstream file("Books.txt", ios::binary | ios::out);
//			if (file.is_open()) {
//				PBook temp = head.first;
//				while (temp != NULL) {
//					file.write((char*)&(*temp), sizeof((*temp)));
//					temp = temp->next;
//				}
//				file.close();
//			}
//			break; }
//		case 8: {
//			head.first = NULL;
//			head.quantity_of_elements = 0;
//			ifstream file("Books.txt", ios::binary | ios::in);
//
//			if (file.is_open() && not(file.peek() == EOF)) {
//				while (file.peek() != EOF) {
//					PBook temp = new Book;
//					if (head.quantity_of_elements == 0) {
//						file.read((char*)&(*temp), sizeof((*temp)));
//						add_first_book(head, temp);
//					}
//					else {
//						file.read((char*)&(*temp), sizeof((*temp)));
//						add_last_book(head, temp);
//					}
//				}
//				file.close();
//				for (int i = 1; i < 7; i++) active[i] = true;
//				active[7] = false; active[0] = false; active[10] = false; active[9] = true;
//			}
//			else cout << "Empty file or can't open!\n\n";
//			break; }
//		case 9:
//			break;
//		case 10:
//			delete_book_list(head);
//			head.first = NULL;
//			head.quantity_of_elements = 0;
//			cout << "Your list is deleted!\n\n";
//			active[0] = true;
//			active[7] = true;
//			active[10] = true;
//			for (int i = 1; i < 7; i++) active[i] = false;
//			active[8] = false; active[9] = false;
//			break;
//		case 11:
//			flag = false;
//			cout << "Bye!\n";
//			break;
//		}
//	}
//
//	return 0;
//}