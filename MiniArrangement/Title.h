#pragma once
#include "Clip.h"
#include <string>

class Title : public Clip, public std::enable_shared_from_this<Title>
{
public:
	Title(std::chrono::milliseconds start, std::chrono::milliseconds length, std::string txt, int size);
	//Title(const Title&) = delete;
	~Title() override = default;
	void Visit(IOperations*) override;

	std::string text;
	int pointSize;
};
