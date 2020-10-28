#include "Configure.h"
#include "LoadSaveImage.h"
#include "ImageUtils.h"

Configure::Configure()
{
	algorithm = [this](const RGBImage& source, RGBImage& result) { filter.ApplyOneDirection(source, result); };
	filter.kernel = FilterKernel::PREWITT;
	filter.rectifyValues = Utils::ClipTo255;
}

void Configure::SetOrientation(const std::string& orient)
{
	if(orient == "horizontal")
		filter.kernel = Transpose(filter.kernel);
	else if(orient == "both")
		algorithm = [this](const RGBImage& source, RGBImage& result) { filter.ApplyBothDirection(source, result); };
}

void Configure::SetScaleFactor(float scale)
{
	filter.kernel *= scale;
}

void Configure::ChooseKernel(const std::string& kernel)
{
	if(kernel == "sobel")
		filter.kernel = FilterKernel::SOBEL;
	else if(kernel == "prewitt")
		filter.kernel = FilterKernel::PREWITT;
}

void Configure::SetSourceFilePath(const std::string& src)
{
	sourcePath = src;
}

void Configure::SetDestinationFilePath(const std::string& dest)
{
	destinationPath = dest;
}

void Configure::UseNormalization()
{
	filter.rectifyValues = Utils::Normalize;
}

int Configure::Validate()
{
	if(sourcePath.empty())
		return -1;

	if(destinationPath.empty())
	{
		// Use sourcePath without extension '.bmp';
		destinationPath.assign(std::begin(sourcePath), std::end(sourcePath) - 4);
		destinationPath.append("Result.bmp");
	}

	this->onValid(sourcePath, destinationPath, algorithm);
	return 0;
}
