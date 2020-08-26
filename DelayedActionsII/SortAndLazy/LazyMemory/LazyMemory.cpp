#include "LazyMemory.h"

LazyMemory::LazyMemory()
	: LazyMemory(CreateFactory(0))
{}
//Hier passenden Konstruktor und Destruktor implementieren

void LazyMemory::PushBack(int val)
{
	//Hier passende Aktion der Liste hinzufügen
	m_changed = true;
}

//Hier restlichen Methoden implementieren


int LazyMemory::operator[] (size_t index)
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
	if(m_changed)
	{
		// ausstehende Aktionen durchfuehren
	    for (...) {
	        // Aktion ausführen
            // Zeiger auf Action-Element löschen  
	    }
        // Liste der Aktionen leeren
	}
}
