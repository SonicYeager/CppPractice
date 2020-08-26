#pragma once
#include "Clip.h"
#include <filesystem>

class Audio : public Clip, public std::enable_shared_from_this<Audio>
{
public:
	Audio(std::chrono::milliseconds start, std::chrono::milliseconds length, std::filesystem::path filePath, int volume);
	~Audio() override = default;

	void Visit(IOperations*) override;

	std::filesystem::path filePath;
	int volume;
};
