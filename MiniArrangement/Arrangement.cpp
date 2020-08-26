#include "Arrangement.h"
#include "Video.h"
#include "Title.h"
#include "FindAll.h"
#include <memory>
#include <typeinfo>
#include <type_traits>
#include <iostream>


void Arrangment::Visit(IOperations* visitor)
{
	//(*visitor)(this);
	visitor->PerformOn(this); //Visitor

	auto lamb = [visitor](auto& track) 
	{
		track.second->Visit(visitor);
	};

	std::for_each(tracks.begin(), tracks.end(), lamb);
}

void Arrangment::AddClip(int tracknumber, ClipPtr clip)
{
	clips.push_back(clip);
	if(tracks.find(tracknumber) != tracks.end())
		tracks[tracknumber]->AddClip(clip);
	else
	{
		tracks.emplace(tracknumber, std::make_unique<Track>(Track()));
		tracks[tracknumber]->AddClip(clip);
	}
}

std::chrono::milliseconds Arrangment::TotalLength() const
{
	//1.3.4 b) wants to be implemented
	auto lamb = [](const ClipPtr& largest, const ClipPtr& first)
	{
		if((largest->start + largest->length) < (first->start + first->length))
			return true;
		else
			return false;
	};

	auto lastClip = std::max_element(clips.begin(), clips.end(), lamb);
	return (*lastClip)->start + (*lastClip)->length;
}

ClipPtr Arrangment::FindByNumber(int num) const
{
	//Find
	auto lamb = [num](const ClipPtr& clip)
	{
		if(clip->number == num)
			return true;
		return false;
	};

	auto found = std::find_if(clips.begin(), clips.end(), lamb);
	if(found == clips.end())
		return nullptr;

	return *found;
}

ClipPtrs Arrangment::FindAllVideos() const
{
	//Find
	FindAll<Video> fa;

	auto lamb = [&fa](const ClipPtr& clip)
	{
		clip->Visit(&fa);
	};

	std::for_each(clips.begin(),
				  clips.end(), lamb);
	return fa.foundAll;
}

ClipPtrs Arrangment::FindAllTitle() const
{
	//Find
	FindAll<Title> fa;

	auto lamb = [&fa](const ClipPtr& clip) 
	{
		clip->Visit(&fa);
	};

	std::for_each(clips.begin(),
				  clips.end(), lamb);
	return fa.foundAll;
}
