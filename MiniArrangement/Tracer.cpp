#include "Tracer.h"
#include "Arrangement.h"
#include "Track.h"
#include "Audio.h"
#include "Video.h"
#include "Title.h"

void Tracer::PerformOn(const VideoPtr& vid)
{
	std::cout << "\t\tClip " << vid->number << ": Video, " << vid->start.count() << ", " << vid->length.count() << ", " << vid->filePath << std::endl;
}

void Tracer::PerformOn(const AudioPtr& aud)
{
	std::cout << "\t\tClip " << aud->number << ": Audio, " << aud->start.count() << ", " << aud->length.count() << ", " << aud->filePath << ", " << aud->volume << "%" << std::endl;
}

void Tracer::PerformOn(const TitlePtr& tit)
{
	std::cout << "\t\tClip " << tit->number << ": Titel, " << tit->start.count() << ", " << tit->length.count() << ", " << "\"" << tit->text << "\"" << ", " << tit->pointSize << "pt" << std::endl;
}

void Tracer::PerformOn(Track* trc)
{
	std::cout << "\tTrack " << m_trackCount << "(Clips: " << trc->clips.size() << ")" << std::endl; 
	m_trackCount++;
}

void Tracer::PerformOn(Arrangment* arr)
{
	std::cout << "Arrangement (" << arr->TotalLength().count() << ", Tracks: " << arr->tracks.size() << ")" << std::endl;
}
