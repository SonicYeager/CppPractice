
// CalculatorInitial.h: Hauptheaderdatei für die CalculatorInitial-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CalculatorInitialApp:
// Siehe CalculatorInitial.cpp für die Implementierung dieser Klasse
//

class CalculatorApp : public CWinApp
{
public:
	CalculatorApp() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	DECLARE_MESSAGE_MAP()
};

extern CalculatorApp theApp;
