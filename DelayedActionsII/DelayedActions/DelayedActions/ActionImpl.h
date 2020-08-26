#pragma once
#include "Action.h"

class PushFront : public Action
{
public:
	PushFront(int val, MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};

protected:
	int val{};
};

class PushBack : public Action
{
public:
	PushBack(int val, MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};

protected:
	int val{};
};

class Erase : public Action
{
public:
	Erase(int val, MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};

protected:
	int val{};
};

class Clear : public Action
{
public:
	Clear(MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};
};

class Sort : public Action
{
public:
	Sort(MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};
};

class Display : public Action
{
public:
	Display(MemoryBlock* pMemory);
	void Execute() override;

private:
	MemoryBlock* pMemory{};
};

class StandartActionsFactory : public ActionsFactory
{
public:
	Action* CreatePushFront(int val, MemoryBlock* pMemory) override;
	Action* CreatePushBack(int val, MemoryBlock* pMemory) override;
	Action* CreateErase(int val, MemoryBlock* pMemory) override;
	Action* CreateClear(MemoryBlock* pMemory) override;
	Action* CreateSort(MemoryBlock* pMemory) override;
	Action* CreateDisplay(MemoryBlock* pMemory) override;
};

class DisplayExtensionFactory : public ActionsFactory
{
public:
	Action* CreateDisplay(MemoryBlock* pMemory) override;
	Action* CreatePushFront(int val, MemoryBlock* pMemory) override;
	Action* CreatePushBack(int val, MemoryBlock* pMemory) override;
	Action* CreateErase(int val, MemoryBlock* pMemory) override;
	Action* CreateClear(MemoryBlock* pMemory) override;
	Action* CreateSort(MemoryBlock* pMemory) override;
};

class PushFrontD : public PushFront
{
public:
	using PushFront::PushFront;
	void Execute() override;
};

class PushBackD : public PushBack
{
public:
	using PushBack::PushBack;
	void Execute() override;
};

class EraseD : public Erase
{
public:
	using Erase::Erase;
	void Execute() override;
};

class ClearD : public Clear
{
public:
	using Clear::Clear;
	void Execute() override;
};

class SortD : public Sort
{
public:
	using Sort::Sort;
	void Execute() override;
};
