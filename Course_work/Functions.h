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


int GetNewId();

PPM Create();

void AddFirst(HPC& head, PPC new_book);

void AddFirst(HPM& head, PPM new_book);

void AddAfter(HPC& head, PPC first_book, PPC second_book);

void AddAfter(HPM& head, PPM first_book, PPM second_book);

void AddLast(HPC& head, PPC new_book);

void AddLast(HPM& head, PPM new_book);
