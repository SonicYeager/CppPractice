#include "LazyMemory.h"

LazyMemory::LazyMemory()
	: LazyMemory(CreateFactory(0))
{}
LazyMemory::LazyMemory(int id)
	: LazyMemory(CreateFactory(id))
{}
LazyMemory::LazyMemory(ActionsFactory* factory)
	: m_pFactory(factory)
{}
LazyMemory::~LazyMemory()
{
	delete m_pFactory;
}

void LazyMemory::PushBack(int val)
{
	m_pActions[m_numberActions] = m_pFactory->CreatePushBack(val, &m_buffer);
	m_numberActions++;
}

void LazyMemory::PushFront(int val)
{
	this->m_pActions[this->m_numberActions] = m_pFactory->CreatePushFront(val, &m_buffer);
	this->m_numberActions++;
}

void LazyMemory::Erase(int val)
{
	this->m_pActions[this->m_numberActions] = m_pFactory->CreateErase(val, &m_buffer);
	this->m_numberActions++;
}

void LazyMemory::Clear()
{
	m_pActions[m_numberActions] = m_pFactory->CreateClear(&m_buffer);
	m_numberActions++;
}

void LazyMemory::Sort()
{
	m_pActions[m_numberActions] = m_pFactory->CreateSort(&m_buffer);
	m_numberActions++;
}

void LazyMemory::Display()
{
	m_pActions[m_numberActions] = m_pFactory->CreateDisplay(&m_buffer);
	m_numberActions++;
}


int LazyMemory::operator[](size_t index)
{
	if(index < this->Size())
		return m_buffer.memory[index];
	return 112;
}

bool LazyMemory::IsEmpty()
{
	return this->Size() == 0;
}

size_t LazyMemory::Size()
{
	this->Update();
	return m_buffer.elementCount;
}

void LazyMemory::Update()
{
	for(int i = 0; i < this->m_numberActions; i++)
	{
		m_pActions[i]->Execute();
		delete this->m_pActions[i];
	}
	for(int i = 0; i < 20; i++)
	{
		this->m_pActions[i] = {};
	}
	m_numberActions = 0;
}
