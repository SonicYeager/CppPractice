#include "pch.h"
#include <iostream>

struct Item
{
	int value = 0;
	Item* next = nullptr;
};

struct List
{
	Item* first = nullptr;
	Item* last = nullptr;
};

void PrintList(List* pList) {

	Item* actualItem = pList->first;

	while (actualItem)
	{
		std::cout << actualItem->value << std::endl;
		actualItem = actualItem->next;
	} 

}

void AppendLast(int newValue, List* pList) {

	Item* newItem = new Item;
	newItem->value = newValue;
	pList->last->next = newItem;
	pList->last = newItem;


}

bool IsIn(int value, List* pList) {

	Item* actualItem = pList->first;

	while (actualItem)
	{
		if (actualItem->value == value)
		{
			return true;
		}
		actualItem = actualItem->next;
	}
	return false;

}

void Delete(int value, List* pList) { // löscht erstes vorkommen

	Item* actualItem = pList->first;
	Item* previousItem = actualItem;

	while (actualItem)
	{

		if (actualItem->value == value)
		{
			previousItem->next = actualItem->next;
			delete actualItem;
			break;
		}
		previousItem = actualItem;
		actualItem = actualItem->next;
	}
}

void InsertBehind(int newValue, int existing, List* pList) {

	Item* actualItem = pList->first;

	while (actualItem)
	{

		if (actualItem->value == existing)
		{
			Item* newItem = new Item;
			newItem->value = newValue;
			newItem->next = actualItem->next;
			actualItem->next = newItem;
			break;
		}
		actualItem = actualItem->next;
	}

}

void InsertBefore(int newValue, int existing, List* pList) {

	Item* actualItem = pList->first;
	Item* previousItem = actualItem;

	while (actualItem)
	{

		if (actualItem->value == existing)
		{
			Item* newItem = new Item;
			newItem->value = newValue;
			newItem->next = actualItem;

			previousItem->next = newItem;
			break;
		}
		previousItem = actualItem;
		actualItem = actualItem->next;
	}

}

List* Intersect(const List* pLeft, const List* pRight) {

	List* intersectedList = new List;
	Item* toSearchLeft = pLeft->first;
	Item* toSearchRight = pRight->first;
	bool bCreated = false;
	bool bSecond = false;

	while (toSearchLeft) 
	{
		while (toSearchRight)
		{
			if (toSearchLeft->value == toSearchRight->value)
			{
				if (bCreated && bSecond)
				{
					AppendLast(toSearchLeft->value, intersectedList);
					break;
				}
				else if (!bSecond && bCreated)
				{

					Item* newItem = new Item;
					newItem->value = toSearchLeft->value;
					intersectedList->first->next = newItem;
					intersectedList->last = newItem;
					bSecond = true;

				}
				else
				{
					Item* newItem = new Item;
					newItem->value = toSearchLeft->value;
					intersectedList->first = newItem;

					bCreated = true;
					break;
				}
			}
			toSearchRight = toSearchRight->next;
		}
		toSearchRight = pRight->first;
		toSearchLeft = toSearchLeft->next;
	}



	return intersectedList;
}

int main()
{
	Item first = { 0, nullptr};
	Item last = { 1, nullptr };
	Item firstI = { 0, nullptr };
	Item lastI = { 1, nullptr };
	first.next = &last;
	firstI.next = &lastI;
	List theGreatListI = {&first, &last};
	List theGreatListII = { &firstI, &lastI };

	for (int infinity = 2; infinity < 60; infinity++)
	{
		AppendLast(infinity, &theGreatListI);
	}
	for (int infinity = 50; infinity < 100; infinity++)
	{
		AppendLast(infinity, &theGreatListII);
	}
	PrintList(&theGreatListI);
	PrintList(&theGreatListII);

	List* theGreatListIII = Intersect(&theGreatListI, &theGreatListII);
	PrintList(theGreatListIII);

}
