#pragma once
#include <memory>

class Video;
class Audio;
class Title;
class Track;
class Arrangment;
class IOperations;

class IVisitable //basiselement
{
public:
	virtual void Visit(IOperations*) = 0; //accept the visit
	virtual ~IVisitable() = default;
};

using VideoPtr = std::shared_ptr<Video>;
using AudioPtr = std::shared_ptr<Audio>;
using TitlePtr = std::shared_ptr<Title>;

class IOperations //visitor
{
public:

	inline void operator()(IVisitable* performOn) //perform corresponding "visit"
	{
		performOn->Visit(this); // possible to use for redirection?
	}
	virtual void PerformOn(const VideoPtr&) = 0;
	virtual void PerformOn(const AudioPtr&) = 0;
	virtual void PerformOn(const TitlePtr&) = 0;
	virtual void PerformOn(Track*) = 0;
	virtual void PerformOn(Arrangment*) = 0;
	~IOperations() = default;
};
