#pragma once
#include "IVisitor.h"
#include <iostream>

class Tracer : public IOperations
{
	virtual void PerformOn(const VideoPtr&) override; //visit Video
	virtual void PerformOn(const AudioPtr&) override; //visit Audio
	virtual void PerformOn(const TitlePtr&) override; //visit Title
	virtual void PerformOn(Track*) override; //visit Track
	virtual void PerformOn(Arrangment*) override; //visit Arrangement
private:
	size_t m_trackCount = 1;
};
