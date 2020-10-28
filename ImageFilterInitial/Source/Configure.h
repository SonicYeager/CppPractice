#pragma once
#include "FilterImage.h"
#include <string>
#include "Event.h"

class Configure
{
public:
	Configure();
	void SetOrientation(const std::string&);
	void SetScaleFactor(float);
	void ChooseKernel(const std::string&);
	void SetSourceFilePath(const std::string&);
	void SetDestinationFilePath(const std::string&);
	void UseNormalization();
	int Validate();

	Event<const std::string&, const std::string&, const FilterAlgorithm&> onValid;

private:
	std::string sourcePath = {};
	std::string destinationPath = {};
	FilterImage filter = {};
	FilterAlgorithm algorithm = {};
};
