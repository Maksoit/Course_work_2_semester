#pragma once
#include <string>
using namespace std;

struct ProductCart {
	int Id;
	string Title;
	int PriceForOne;
	int Price;
	int count;

	ProductCart* next;
};
typedef ProductCart PC;
typedef ProductCart* PPC;

struct HeadProductCart {
	ProductCart* Head;
	bool IsIntialized = false;
	int count;
};
typedef HeadProductCart HPC;

struct ProductMarket {
	int Id;
	int Price;
	string Title;
	string Description;
	bool Available;

	ProductMarket* next;
};
typedef ProductMarket PM;
typedef ProductMarket* PPM;

struct HeadProductMarket {
	ProductMarket* Head;
	bool IsIntialized = false;
	int count;
};
typedef HeadProductMarket HPM;

struct ProductStorage {
	int Id;
	string Title;
	int Count;

	ProductStorage* next;
};
typedef ProductStorage PS;
typedef ProductStorage* PPS;

struct HeadProductStorage {
	ProductStorage* Head;
	bool IsIntialized = false;
	int count;
};
typedef HeadProductStorage HPS;