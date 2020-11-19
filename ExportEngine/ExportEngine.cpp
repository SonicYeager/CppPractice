#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"

#include "ColorSpaceConverter.h"
#include "WrappedVideoEngine.h"
#include "FeatureProtection.h"
#include "FilesystemHandler.h"
#include "ProgressHandler.h"
#include "Measurement.h"
#include "LogHandler.h"
#include "ExportHandler.h"

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	int result{};
	try
	{
		result = -1;
		m_config = config;
		ExportHandler expHandler{m_config.pExporter, m_config.createExport, static_cast<ExportFlags>(m_config.flagsExport)};
		if(CheckBounceIsValid(expHandler.GetExportConfig()))
		{
			ThrowIfProtectedFeature(expHandler.GetExportConfig());

			Progress progress{config.pUserInterface};
			progress.OpenProgress(m_config.pPI->rangeEnd - m_config.pPI->rangeStart);

			m_config.targetFileName = ConfigDirectory(static_cast<ExportFlags>(m_config.flagsExport) == ExportFlags::RENAME_FILENAME_IF_EXIST, m_config.targetFileName);
			
			WrappedVideoEngine::Prepare(*m_config.pPI);

			expHandler.Initialize(m_config.targetFileName);

			LogExportRange(m_config.pPI->rangeStart, m_config.pPI->rangeEnd, m_config.targetFileName.string());
			
			Measurement measurement;
			measurement.Start();

			for(__int64 i = m_config.pPI->rangeStart; i < m_config.pPI->rangeEnd;)
			{
				progress.ThrowIfAbort(result);

				auto videoframe = WrappedVideoEngine::GetFrame(i);

				auto exConfig = expHandler.GetExportConfig();

				ConvertToYUV(videoframe, exConfig.format);

				size_t written = 0;
				bool success = expHandler.ExportVideoFrame(videoframe, written);
				if(success)
				{
					progress.AddProgress(written);

					i += static_cast<__int64>(m_config.pPI->frameRate);

					delete videoframe;
				}
				else
				{
					delete videoframe;
					throw std::exception("Encode error");
				}
			}

			measurement.Stop();
			LogExportTime(m_config.pPI->rangeEnd - m_config.pPI->rangeStart / m_config.pPI->frameRate, measurement.GetElapsedTime());

			result = 1;
		}
	}
	catch(std::exception ex)
	{
		std::cerr << "error during export occurred: " << ex.what();
	}
	catch(int)
	{
		std::cout << "aborted by user";
	}
	WrappedVideoEngine::ShutDown();
	m_config = {};
	return result == 1;
}

bool ExportEngine::CheckBounceIsValid(const ExportConfig& exConfig) const
{
	if(m_config.flagsExport & BOUNCE_IF_VALID and m_config.pPI)
	{
		return m_config.pPI->aspectRation == exConfig.aspectRatio
			and m_config.pPI->width >= exConfig.width
			and m_config.pPI->height >= exConfig.height
			and not m_config.targetFileName.empty();
	}
	return false;
}
