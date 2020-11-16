#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"
#include "ColorSpaceConverter.h"
#include "FilesystemHandler.h"
#include "ProgressHandler.h"
#include "Measurement.h"
#include "Log.h"

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	VideoEngine vidEngine{};
	try
	{
		size_t totalWritten = 0;
		m_config = config;
		m_Result = -1;
		m_pExporter = IVideoExport::ConfigExporter(m_config);
		if(CheckBounceIsValid())
		{
			Log log{};
			CheckFeatureProtection(m_config.pExporter);
			FilesystemHandler fsHandler{};
			fsHandler.FindOtherFile(m_config);
			fsHandler.ConfigPath(m_config, log);
			ProgressHandler prgHandler{m_config.pUserInterface};
			prgHandler.OpenProgress(m_config);
			vidEngine.PrepareVideoEngine(*m_config.pPI);
			m_pExporter->Initialize(m_config.targetFileName);
			log.LogFileName(m_config);
			log.LogRange(m_config);
			Measurement measure{};
			measure.Start();
			//{ VALIDATEFRAMES-this | CONVERTFRAMES-Converter | WRITEFRAMES-this
			for(__int64 i = m_config.pPI->rangeStart; i < m_config.pPI->rangeEnd;)
			{
				prgHandler.ThrowIFProgressAbort(m_Result);
				auto videoframe = vidEngine.VideoEngineGetFrame(i);
				if(videoframe == nullptr)
					throw std::exception("GetFrame error");
				ColorSpaceConverter csc{};
				csc.ConvertFrameColorFormat(m_pExporter, videoframe);
				m_pExporter->WriteFrame(m_pExporter, m_config.pPI->frameRate, videoframe, totalWritten, prgHandler, i);
			}
			//}
			measure.Stop();
			log.LogExport(measure, m_config);
			m_Result = 1;
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
	vidEngine.ShutdownVideoEngine();
	m_pExporter = nullptr;
	m_config = {};
	return m_Result == 1;
}

bool ExportEngine::CheckBounceIsValid() const
{
	if(m_config.flagsExport & BOUNCE_IF_VALID and m_pExporter and m_config.pPI)
	{
		ExportConfig exConfig{};
		m_pExporter->GetExportInfo(&exConfig);
		return m_config.pPI->aspectRation == exConfig.aspectRatio //
			and m_config.pPI->width >= exConfig.width //
			and m_config.pPI->height >= exConfig.height //
			and not m_config.targetFileName.empty();
	}
	return false;
}

void ExportEngine::CheckFeatureProtection(IVideoExport* pExporter) const
{
	if(pExporter)
	{
		ExportConfig config{};
		pExporter->GetExportInfo(&config);
		if(not(config.type == ExportType::DVD) or not (config.type == ExportType::MP4))
			throw std::exception("Feature not allowed");
	}
}
