#include "Element.h"


Element::Element(const std::string& name)
	: m_name(name)
	, m_text{}
{}

std::string Element::GetName() const
{
	return m_name;
}

void Element::AddText(const std::string& txt)
{
	m_text.append(txt);
}

std::string Element::GetText() const
{
	return m_text;
}
