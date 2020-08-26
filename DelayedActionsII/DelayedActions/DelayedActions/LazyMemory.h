#pragma once

#include "Action.h"

class LazyMemory
{
public:
	LazyMemory();
	LazyMemory(int id);
	explicit LazyMemory(ActionsFactory* factory);
	~LazyMemory();

	// Schreibfunktionen
	void PushBack(int);
	void PushFront(int);
	void Erase(int);
	void Clear();
	void Sort();

	//Anzeigefunktionen
	void Display();

	// Lesefunktionen
	int operator[](size_t index);
	bool IsEmpty();
	size_t Size();

private:
	// Aenderungen auf Objektliste uebertragen
	void Update();

private:
	MemoryBlock m_buffer = {};
	ActionsFactory* m_pFactory = nullptr;
	Action* m_pActions[20] = {};
	int m_numberActions = 0;
};
