#include "FilterImage.h"

void FilterImage::ApplyOneDirection(const RGBImage& source, RGBImage& destination)
{
	// Farbige Bilder führen zu schlechterer Kantenerkennung
	const GrayscaleImage grayscale = Utils::ToGrayscale(source);

	// Anwenden des Kernels auf das Bild
	GrayscaleImage result = Utils::Convolute(grayscale, this->kernel);

	// Begrenzung der Werte auf gueltigen Wertebereich
	rectifyValues(result);

	Utils::CopyFromTo(result, destination);
}

void FilterImage::ApplyBothDirection(const RGBImage& source, RGBImage& destination)
{
	// Vorbereiten des Ausgangsbildes
	const GrayscaleImage grayscale = Utils::ToGrayscale(source);

	// Anwenden des Kernels auf vorbereitete Bild in beiden Richtungen
	GrayscaleImage resultVert = Utils::Convolute(grayscale, this->kernel);
	auto kernelHori = Transpose(kernel);
	GrayscaleImage resultHori = Utils::Convolute(grayscale, kernelHori);

	// Berechnen des Gradienten aus beiden Richtungen
	auto result = Utils::Gradient(resultVert, resultHori);

	// Begrenzung der Werte auf gueltigen Wertebereich
	rectifyValues(result);

	// Ergebnis in Ziel schreiben
	Utils::CopyFromTo(result, destination);
}

const Matrix3x3 FilterKernel::SOBEL = 
{
	1, 0, -1, 
	2, 0, -2,
	1, 0, -1
};
const Matrix3x3 FilterKernel::PREWITT = 
{
	1, 0, -1,
	1, 0, -1,
	1, 0, -1};
