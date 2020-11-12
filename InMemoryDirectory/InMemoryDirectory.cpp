#include "InMemoryDirectory.h"
#include <algorithm>

void InMemoryDirectory::AddElement(std::unique_ptr<Element> pElement)
{
	m_elements.push_back(std::move(pElement));
}

void InMemoryDirectory::GenerateIndex()
{
	auto pNewElement = std::make_unique<Element>("index");
	for(auto& pElement : m_elements)
		pNewElement->AddText(pElement->GetName() + '\n');

	auto oldElement = GetElement("index");
	if (oldElement == nullptr)
		m_elements.push_back(std::move(pNewElement));
	else
	{
		*oldElement = *pNewElement.get();
	}
}

size_t InMemoryDirectory::GetElementCount() const
{
	return m_elements.size();
}

Element* InMemoryDirectory::GetElement(const std::string& name) const
{
	auto byName = [&name](auto& pElement) { return pElement->GetName() == name; };
	auto pos = std::find_if(std::begin(m_elements), std::end(m_elements), byName);
	return pos == std::end(m_elements) ? nullptr : pos->get();
}


