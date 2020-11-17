#include "gmock/gmock.h"
#include "ExportEngine.h"
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
	config.flagsExport = BOUNCE_IF_VALID | RGB_EXPORT;
	config.pUserInterface = IUserInterface::Create();

	bool actual = exporter.Bounce(config);

	EXPECT_TRUE(actual);

	//cleanup
	delete config.pUserInterface;
}