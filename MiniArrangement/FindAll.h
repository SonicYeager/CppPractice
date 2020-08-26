#pragma once
#include "IVisitor.h"
#include "Clip.h"
#include <vector>
#include <memory>

template<class C>
class FindAll : public IOperations
{
public:

	virtual void PerformOn(const VideoPtr&) override; //visit Video
	virtual void PerformOn(const AudioPtr&) override; //visit Audio
	virtual void PerformOn(const TitlePtr&) override; //visit Title
	virtual void PerformOn(Track*) override; //visit Track
	virtual void PerformOn(Arrangment*) override; //visit Arrangement

	std::vector<std::shared_ptr<Clip>> foundAll;
};

#include "FindAll.h"
#include "Tracer.h"
#include "Arrangement.h"
#include "Track.h"
#include "Audio.h"
#include "Video.h"
#include "Title.h"

template<class C>
void FindAll<C>::PerformOn(const VideoPtr& vid)
{
	if constexpr(std::is_same<C, Video>())
		foundAll.push_back(vid);
}

template<class C>
void FindAll<C>::PerformOn(const AudioPtr& aud)
{
	if constexpr(std::is_same<C, Audio>())
		foundAll.push_back(aud);
}

template<class C>
void FindAll<C>::PerformOn(const TitlePtr& tit)
{
	if constexpr(std::is_same<C, Title>())
		foundAll.push_back(tit);
}

template<class C>
void FindAll<C>::PerformOn(Track*)
{}

template<class C>
void FindAll<C>::PerformOn(Arrangment*)
{}