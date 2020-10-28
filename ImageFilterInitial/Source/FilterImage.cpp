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

	// Anwenden des Kernels auf vorbereitete Bild in beiden Richtungen

	// Berechnen des Gradienten aus beiden Richtungen

	// Begrenzung der Werte auf gueltigen Wertebereich

	// Ergebnis in Ziel schreiben
}

const Matrix3x3 FilterKernel::SOBEL = {1, 0, -1, 2, 0, -2, 1, 0, -1};
const Matrix3x3 FilterKernel::PREWITT = {1, 0, -1, 1, 0, -1, 1, 0, -1};
