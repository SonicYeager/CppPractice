
// stdafx.h: Includedatei für Standardsystem-Includedateien
// oder häufig verwendete projektspezifische Includedateien,
// die nur selten geändert werden.

#pragma once

#ifndef VC_EXTRALEAN
#	define VC_EXTRALEAN // Selten verwendete Komponenten aus Windows-Headern ausschließen
#endif

#include "SDKDDKVer.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS // einige CString-Konstruktoren sind explizit

// Deaktiviert das Ausblenden einiger häufiger und oft ignorierter Warnungen durch MFC
#define _AFX_ALL_WARNINGS

#include <afxwin.h> // MFC-Kern- und -Standardkomponenten
#include <afxext.h> // MFC-Erweiterungen


#ifndef _AFX_NO_OLE_SUPPORT
#	include <afxdtctl.h> // MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#	include <afxcmn.h> // MFC-Unterstützung für allgemeine Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h> // MFC-Unterstützung für Menübänder und Steuerleisten
