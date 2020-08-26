#pragma once
#include "Exceptions.h"

template<typename T>
class Puffer
{
public:
	//ändern move hinzufügen

	Puffer(size_t size) 
		: m_size(size) ,mp_var(new T[m_size])
	{}

	Puffer(const Puffer<T>& otherBuffer)
		: m_size(otherBuffer.m_size), mp_var(new T[m_size])
	{
		for (size_t i = 0; i < m_size; i++)
			this->mp_var[i] = otherBuffer[i];
	}

	Puffer(size_t size, T* array) : m_size(size), mp_var(new T[m_size])
	{
		for (size_t i = 0; i < m_size; i++)
			this->mp_var[i] = array[i];
	}

	Puffer(Puffer<T>&& otherBuffer)
		: m_size(otherBuffer.m_size), mp_var(otherBuffer.mp_var)
	{		
		otherBuffer.mp_var = nullptr;
		otherBuffer.m_size = 0;
	}

	~Puffer()
	{
		if (mp_var != nullptr)
		{
			delete[] mp_var;
		}
	}

	void operator=(const Puffer<T>& otherBuffer)
	{
		if (*this != otherBuffer)
		{
			if (mp_var != nullptr)
				delete[] mp_var;

			m_size = otherBuffer.m_size;
			mp_var = new T[m_size];

			for (size_t i = 0; i < m_size; i++)
				this->mp_var[i] = otherBuffer[i];
		}
	}

	void Add(T newValue)
	{
		Resize(m_size+1);
		mp_var[m_size-1] = newValue;
	}

	bool operator==(const Puffer<T>& otherBuffer) const
	{
		if (otherBuffer.Size() != this->m_size)
			return false;
		else 
			for (size_t i = 0; i < m_size; i++)
				if (otherBuffer[i] == mp_var[i])
					return true;
	}

	bool operator!=(const Puffer<T>& otherBuffer) const
	{
		if (*this == otherBuffer)
			return false;
		else
			return true;
	}

	T& operator[](int index) const
	{
		return this->mp_var[index];
	}

	T* Data() const
	{
		return this->mp_var;
	}

	void Data(const T& data)
	{
		this->Add(data);
	}

	size_t Size() const
	{
		return m_size;
	}

	void Resize(size_t newSize)
	{
		T* newSized = new T[newSize]{};

		if (newSize > m_size)
		{
			for (size_t i = 0; i < m_size; i++)
				newSized[i] = this->mp_var[i];
		}
		else 
		{
			for (size_t i = 0; i < newSize; i++)
				newSized[i] = this->mp_var[i];
		}

		delete[] mp_var;
		mp_var = newSized;

		m_size = newSize;
	}


private:
	size_t m_size{};
	T* mp_var{};
};