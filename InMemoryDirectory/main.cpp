#include "InMemoryDirectory.h"

int main()
{
	InMemoryDirectory directory;

	directory.AddElement(std::make_unique<Element>("Henry"));
	directory.AddElement(std::make_unique<Element>("Kuno"));
	directory.AddElement(std::make_unique<Element>("Marta"));
	directory.GenerateIndex();
	auto index = directory.GetElement("index");
	if(index->GetText() == "Henry\nKuno\nMarta\n")
	{
		directory.AddElement(std::make_unique<Element>("Judith"));
		directory.AddElement(std::make_unique<Element>("Peter"));
		directory.GenerateIndex();
	}
	index = directory.GetElement("index");
	return index->GetText() == "Henry\nKuno\nMarta\nJudith\nPeter\n";
}
