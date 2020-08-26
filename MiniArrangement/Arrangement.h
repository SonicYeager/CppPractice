#pragma once
#include "Track.h"
#include <map>
#include <memory>

class Arrangment : public IVisitable
{
public:
	Arrangment() = default;
	~Arrangment() = default;

	void Visit(IOperations*) override;

	void AddClip(int tracknumber, ClipPtr);
	std::chrono::milliseconds TotalLength() const;

	ClipPtr FindByNumber(int) const;
	ClipPtrs FindAllVideos() const; // will be done with visitor pattern
	ClipPtrs FindAllTitle() const; // will be done with visitor pattern

	std::map<int, std::unique_ptr<Track>> tracks{};
	ClipPtrs clips{};
};
