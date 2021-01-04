#include "gmock/gmock.h"
#include "ExportEngine.h"
#include <filesystem>

const std::filesystem::path exportEnginePath{"ExportEngine"};
const std::filesystem::path absolute = std::filesystem::absolute(exportEnginePath);

bool FolderExists()
{
	return std::filesystem::is_directory(absolute);
}

void CreateFolder()
{
	if(not FolderExists())
		std::filesystem::create_directory(absolute);
}

void DeleteFolder()
{
	if(FolderExists())
		std::filesystem::remove(absolute);
}

TEST(TestExportEngine, Bounce_WithFlagsBounceIfValidAndRenameFilenameIfExists_ReturnTrue)
{
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID | RENAME_FILENAME_IF_EXIST; // | RGB_EXPORT;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}

TEST(TestExportEngine, Bounce_WithFlagsBounceIfValidAndRenameFilenameIfExistsAndRGBExport_ReturnTrue)
{
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID | RENAME_FILENAME_IF_EXIST | RGB_EXPORT;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}

TEST(TestExportEngine, Bounce_WithFlagsBounceIfValidAndAndRGBExport_ReturnTrue)
{
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}

TEST(TestExportEngine, Bounce_WithExportEngineFolder_ReturnTrue)
{
	CreateFolder();
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}

TEST(TestExportEngine, Bounce_WithoutExportEngineFolder_ReturnTrue)
{
	DeleteFolder();
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}

TEST(TestExportEngine, BounceGrayscale_WithFlagsBounceIfValidAndRenameFilenameIfExists_ReturnTrue)
{
	ExportEngine exporter{};
	ProjectInfo PI{};
	PI.rangeEnd = 200;
	PI.width = 12;
	PI.height = 12;
	PI.aspectRation = 1.0;
	ExportEngineConfig config{};
	config.pPI = &PI;
	config.flagsExport = BOUNCE_IF_VALID | RENAME_FILENAME_IF_EXIST; // | RGB_EXPORT;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
	DeleteFolder();
}