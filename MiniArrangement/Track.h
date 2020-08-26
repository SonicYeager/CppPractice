#pragma once
#include "Clip.h"
#include <memory>
#include <vector>
#include <algorithm>

using ClipPtr = std::shared_ptr<Clip>;
using ClipPtrs = std::vector<std::shared_ptr<Clip>>;

class Track : public IVisitable
{
public:
	Track() = default;
	~Track() = default;

	void Visit(IOperations*) override;

	void AddClip(ClipPtr);
	ClipPtr FindByNumber(int) const;

	ClipPtrs clips{};
};



