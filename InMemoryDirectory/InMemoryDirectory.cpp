#include "InMemoryDirectory.h"
#include <algorithm>

void InMemoryDirectory::AddElement(std::unique_ptr<Element> pElement)
{
	auto index = GetElement("index");
	if (index != nullptr)
		index->AddText(pElement->GetName() + "\n");
	m_elements.push_back(std::move(pElement));
}

void InMemoryDirectory::GenerateIndex()
{
	if (GetElement("index") == nullptr)
	{
		auto pNewElement = std::make_unique<Element>("index");
		for(auto& pElement : m_elements)
			pNewElement->AddText(pElement->GetName() + '\n');
		m_elements.push_back(std::move(pNewElement));
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


