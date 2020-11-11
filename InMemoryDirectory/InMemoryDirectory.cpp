#include "InMemoryDirectory.h"
#include <algorithm>

void InMemoryDirectory::AddElement(std::unique_ptr<Element> pElement)
{
	m_elements.push_back(std::move(pElement));
	if (GetElement("index") != nullptr)
		GenerateIndex();
}

void InMemoryDirectory::GenerateIndex()
{
	auto index = GetElement("index");
	if (index == nullptr)
	{
		auto pNewElement = std::make_unique<Element>("index");
		pNewElement->AddText("index\n");
		for(auto& pElement : m_elements)
			pNewElement->AddText(pElement->GetName() + '\n');
		m_elements.insert(std::begin(m_elements), std::move(pNewElement));
	}
	else
		index->AddText(m_elements.back()->GetName() + "\n");
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


