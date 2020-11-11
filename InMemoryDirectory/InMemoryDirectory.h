#pragma once
#include "Element.h"
#include <memory>
#include <vector>

class InMemoryDirectory
{
public:
	void AddElement(std::unique_ptr<Element>);
	void GenerateIndex();
	size_t GetElementCount() const;
	Element* GetElement(const std::string& name) const;

private:
	std::vector<std::unique_ptr<Element>> m_elements = {};
};
