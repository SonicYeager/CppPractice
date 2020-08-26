#pragma once

// Der Buffer wird durch einen array von int abgebildet und wird dynamisch angepasst
struct MemoryBlock
{
	int* memory = nullptr;
	size_t elementCount = 0;
};

// Jede Implementierung einer Operation muss von Action erben
class Action
{
public:
	virtual void Execute() = 0;
	virtual ~Action() = default;
};

// Alle Operationen werden durch die ActionsFactory erstellt, damit kann man schnell alle Operationen auf einen Schlag tauschen
// Die Implementierung muss von ActionsFactory erben
class ActionsFactory
{
public:
	virtual Action* CreatePushFront(int val, MemoryBlock* pMemory) = 0;
	virtual Action* CreatePushBack(int val, MemoryBlock* pMemory) = 0;
	virtual Action* CreateErase(int val, MemoryBlock* pMemory) = 0;
	virtual Action* CreateClear(MemoryBlock* pMemory) = 0;
	virtual Action* CreateSort(MemoryBlock* pMemory) = 0;
	virtual ~ActionsFactory() = default;
};

// Hier wird die passende factory erzeugt, je nach id
ActionsFactory* CreateFactory(int id);
