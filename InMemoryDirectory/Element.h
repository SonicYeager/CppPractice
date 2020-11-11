#pragma once
#include <string>

class Element
{
public:
	explicit Element(const std::string& name);
	std::string GetName() const;
	void AddText(const std::string& txt);
	std::string GetText() const;
	bool operator==(const Element& right) const;

private:
	std::string m_name;
	std::string m_text;
};
