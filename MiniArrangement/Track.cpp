#include "Track.h"

struct TrackCompByStartTime
{
	bool operator()(ClipPtr, ClipPtr);
} Comparator;

void Track::AddClip(ClipPtr clip)
{
	clips.push_back(clip); //Add clip to clips
	std::sort(clips.begin(), clips.end(), Comparator); //Sort clips array by start time, use std::sort
	for(size_t i = 1; i < clips.size(); ++i) //Adapt start of overlapping clips
		if((clips[i]->start + clips[i - 1]->length) > clips[i]->start)
			clips[i]->start = clips[i - 1]->start + clips[i - 1]->length + 1ms;
}

ClipPtr Track::FindByNumber(int num) const
{
	//Find
	auto FindIfComp = [num](const ClipPtr& clip) {
		if(clip->number == num)
			return true;
		return false;
	};

	auto found = std::find_if(std::begin(clips), std::end(clips), FindIfComp);
	if(found == clips.end())
		return nullptr;
	return *found;
}

void Track::Visit(IOperations* visitor)
{
	visitor->PerformOn(this); //Visitor
	for(auto clip : clips)
	{
		clip->Visit(visitor);
	}
}

bool TrackCompByStartTime::operator()(ClipPtr left, ClipPtr right)
{
	return left->start < right->start;
}