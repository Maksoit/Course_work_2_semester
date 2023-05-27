#pragma once
#define POINTS 11
#define POINTSUSER 9
#define WIDTH 20
#include <string>

using namespace std;

bool* InitializeActive(bool*& active);

bool* InitializeActiveUser(bool*& activeUser);

void SetColor(int attr);

void PrintAdminMenu(bool* active);

void PrintUserMenu(bool* activeUser);

void PrintInsideMenu(int _case, int end);

void PrintInsideMenuUser(int _case, int end);

void PrintList(HPC head);

void PrintList(HPM head);

void PrintList(HPS head);

bool IsRightDigit(string& str);

int EnterNum();

int EnterChoice(bool* active);

int EnterInsideChoice(int end);


int GetNewId(HPM headMarket);

int GetNewId();

PPM Create(HPM headMarket);

PO Create(HPC headCart);

PPS MarketToStorage(PPM newProduct);

PPC MarketToCart(PPM marketProduct);

void AddFirst(HPC& head, PPC new_book);

void AddFirst(HPM& head, PPM new_book);

void AddFirst(HPS& head, PPS new_book);

void AddFirst(HO& head, PO new_book);

void AddAfter(HPC& head, PPC first_book, PPC second_book);

void AddAfter(HPM& head, PPM first_book, PPM second_book);

void AddAfter(HPS& head, PPS first_book, PPS second_book);

void AddAfter(HO& head, PO first_book, PO second_book);

void AddLast(HPC& head, PPC new_book);

void AddLast(HPM& head, PPM new_book);

void AddLast(HPS& head, PPS new_book);

void AddLast(HO& head, PO new_book);

PPC SearchByName(string name, HPC head);

PPM SearchByName(string name, HPM head);

PPS SearchByName(string name, HPS head);

void Delete(HPC& head, PPC oldProduct);

void Delete(HPM& head, PPM oldProduct);

void Delete(HPS& head, PPS oldProduct);

void DeleteAll(HPC& headCart);

void DeleteAll(HPM& headMarket);

void DeleteAll(HPS& headStorage);

void DeleteAll(HO& headOrder);


void Change(PPC product);

void Change(PPS product);

void Change(PPS product, string title, int newCount);

void Change(PPM product, HPS headStorage);

void SaveStorage(HPS headStorage);

void SaveCart(HPC headCart);

void SaveMarket(HPM headMarket);

void SaveOrder(PO order);

void LoadMarket(HPM &headMarket);

void LoadStorage(HPS& headStorage);

void LoadCart(HPC& headCart);