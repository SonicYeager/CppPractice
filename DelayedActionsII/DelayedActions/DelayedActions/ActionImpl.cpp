#include "Action.h"
#include "LazyMemory.h"
#include "ActionImpl.h"
#include <iostream>

ActionsFactory* CreateFactory(int id)
{
	if(id == 0)
	{
		ActionsFactory* factory = new StandartActionsFactory;
		return factory;
	}
	if(id == 1)
	{
		ActionsFactory* factory = new DisplayExtensionFactory;
		return factory;
	}
}

PushFront::PushFront(int val, MemoryBlock* pMemory)
	: val(val)
	, pMemory(pMemory)
{}

void PushFront::Execute()
{
	if(this->pMemory->memory == nullptr)
	{
		this->pMemory->memory = new int[this->pMemory->elementCount + 1];
		this->pMemory->memory[0] = this->val;
	}
	else
	{
		int* pTemp = this->pMemory->memory;
		this->pMemory->memory = new int[this->pMemory->elementCount + 1];
		this->pMemory->memory[0] = this->val;
		for(int i = 0; i < this->pMemory->elementCount; i++)
		{
			this->pMemory->memory[i + 1] = pTemp[i];
		}
		delete[] pTemp;
	}
	this->pMemory->elementCount++;
}

PushBack::PushBack(int val, MemoryBlock* pMemory)
	: val(val)
	, pMemory(pMemory)
{}

void PushBack::Execute()
{
	if(this->pMemory->memory == nullptr)
	{
		this->pMemory->memory = new int[this->pMemory->elementCount + 1];
		this->pMemory->memory[0] = this->val;
	}
	else
	{
		int* pTemp = this->pMemory->memory;
		this->pMemory->memory = new int[this->pMemory->elementCount + 1];
		for(int i = 0; i < this->pMemory->elementCount; i++)
		{
			this->pMemory->memory[i] = pTemp[i];
		}
		this->pMemory->memory[this->pMemory->elementCount] = this->val;
		delete[] pTemp;
	}
	this->pMemory->elementCount++;
}

Erase::Erase(int val, MemoryBlock* pMemory)
	: val(val)
	, pMemory(pMemory)
{}

void Erase::Execute()
{
	int erasedElements{};
	int iSec{};
	int* pTemp = this->pMemory->memory;
	this->pMemory->memory = new int[this->pMemory->elementCount];
	for(int i = 0; i < this->pMemory->elementCount; i++)
	{
		if(pTemp[i] == this->val)
		{
			iSec--;
			erasedElements++;
		}
		else
		{
			this->pMemory->memory[iSec] = pTemp[i];
		}
		iSec++;
	}

	delete[] pTemp;
	this->pMemory->elementCount -= erasedElements;
	int* pTempII = this->pMemory->memory;
	this->pMemory->memory = new int[this->pMemory->elementCount];
	for(int i = 0; i < pMemory->elementCount; i++)
	{
		this->pMemory->memory[i] = pTempII[i];
	}
	delete[] pTempII;
}

Clear::Clear(MemoryBlock* pMemory)
	: pMemory(pMemory)
{}

void Clear::Execute()
{
	if(!(this->pMemory->memory == nullptr))
	{
		delete[] this->pMemory->memory;
		this->pMemory->memory = nullptr;
		this->pMemory->elementCount = 0;
	}
}

Sort::Sort(MemoryBlock* pMemory)
	: pMemory(pMemory)
{}

void Sort::Execute()
{ //InsertionSort vom vorhergehenden Projekt geklaut ^^
	for(int k = 1; k < this->pMemory->elementCount; k++)
	{
		if(this->pMemory->memory[k] < this->pMemory->memory[k - 1])
		{
			int x = this->pMemory->memory[k];
			int i = 0;
			for(i = k; ((i > 0) && (this->pMemory->memory[i - 1] > x)); i--)
			{
				this->pMemory->memory[i] = this->pMemory->memory[i - 1];
			}
			this->pMemory->memory[i] = x;
		}
	}
}

Action* StandartActionsFactory::CreatePushFront(int val, MemoryBlock* pMemory)
{
	Action* pushFront = new PushFront(val, pMemory);
	return pushFront;
}

Action* StandartActionsFactory::CreatePushBack(int val, MemoryBlock* pMemory)
{
	Action* pushBack = new PushBack(val, pMemory);
	return pushBack;
}

Action* StandartActionsFactory::CreateErase(int val, MemoryBlock* pMemory)
{
	Action* erase = new Erase(val, pMemory);
	return erase;
}

Action* StandartActionsFactory::CreateClear(MemoryBlock* pMemory)
{
	Action* clear = new Clear(pMemory);
	return clear;
}

Action* StandartActionsFactory::CreateSort(MemoryBlock* pMemory)
{
	Action* sort = new Sort(pMemory);
	return sort;
}

Action* StandartActionsFactory::CreateDisplay(MemoryBlock* pMemory)
{
	Action* display = new Display(pMemory);
	return display;
}

Display::Display(MemoryBlock* pMemory)
	: pMemory(pMemory)
{}

void Display::Execute()
{
	if(!(pMemory->memory == nullptr))
	{
		for(int i = 0; i < pMemory->elementCount; i++)
		{
			std::cout << pMemory->memory[i] << std::endl;
		}
	}
}

void PushFrontD::Execute()
{
	std::cout << "PushFront (" << val << ")\n";
	PushFront::Execute();
}

void PushBackD::Execute()
{
	std::cout << "PushBack (" << val << ")\n";
	PushBack::Execute();
}

void EraseD::Execute()
{
	std::cout << "Erase (" << val << ")\n";
	Erase::Execute();
}

void ClearD::Execute()
{
	std::cout << "Clear\n";
	Clear::Execute();
}

void SortD::Execute()
{ //InsertionSort vom vorhergehenden Projekt geklaut ^^
	std::cout << "Sort\n";
	Sort::Execute();
}

Action* DisplayExtensionFactory::CreateDisplay(MemoryBlock* pMemory)
{
	Action* display = new Display(pMemory);
	return display;
}

Action* DisplayExtensionFactory::CreatePushFront(int val, MemoryBlock* pMemory)
{
	Action* pushFrontD = new PushFrontD(val, pMemory);
	return pushFrontD;
}

Action* DisplayExtensionFactory::CreatePushBack(int val, MemoryBlock* pMemory)
{
	Action* pushBackD = new PushBackD(val, pMemory);
	return pushBackD;
}

Action* DisplayExtensionFactory::CreateErase(int val, MemoryBlock* pMemory)
{
	Action* eraseD = new EraseD(val, pMemory);
	return eraseD;
}

Action* DisplayExtensionFactory::CreateClear(MemoryBlock* pMemory)
{
	Action* clearD = new ClearD(pMemory);
	return clearD;
}

Action* DisplayExtensionFactory::CreateSort(MemoryBlock* pMemory)
{
	Action* sortD = new SortD(pMemory);
	return sortD;
}
