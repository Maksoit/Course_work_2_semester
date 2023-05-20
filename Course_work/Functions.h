#pragma once
#define POINTS 11
#define WIDTH 20
#include <string>

using namespace std;

bool* InitializeActive(bool*& active);

void SetColor(int attr);

void PrintMenu(bool* active);

void PrintInsideMenu(int _case, int end);

void PrintList(HPC head);

void PrintList(HPM head);

void PrintList(HPS head);

bool IsRightDigit(string& str);

int EnterNum();

int EnterChoice(bool* active);

int EnterInsideChoice(int end);


int GetNewId(HPM headMarket);

PPM Create(HPM headMarket);

PPS MarketToStorage(PPM newProduct);

PPC MarketToCart(PPM marketProduct);

void AddFirst(HPC& head, PPC new_book);

void AddFirst(HPM& head, PPM new_book);

void AddFirst(HPS& head, PPS new_book);

void AddAfter(HPC& head, PPC first_book, PPC second_book);

void AddAfter(HPM& head, PPM first_book, PPM second_book);

void AddAfter(HPS& head, PPS first_book, PPS second_book);

void AddLast(HPC& head, PPC new_book);

void AddLast(HPM& head, PPM new_book);

void AddLast(HPS& head, PPS new_book);

PPC SearchByName(string name, HPC head);

PPM SearchByName(string name, HPM head);

PPS SearchByName(string name, HPS head);

void Delete(HPC head, PPC oldProduct);

void Delete(HPM head, PPM oldProduct);

void Delete(HPS head, PPS oldProduct);


void Change(PPC product);