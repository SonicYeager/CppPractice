#pragma once
#include "Clip.h"
#include <filesystem>

class Video : public Clip, public std::enable_shared_from_this<Video>
{
public:
	Video(std::chrono::milliseconds start, std::chrono::milliseconds length, std::filesystem::path filePath);
	~Video() override = default;

	void Visit(IOperations*) override;

	std::filesystem::path filePath;
};
