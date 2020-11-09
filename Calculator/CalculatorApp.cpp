#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CalculatorApp.h"
#include "CalculatorDlg.h"
#include "Controller.h"
#include "Calc.h"

BEGIN_MESSAGE_MAP(CalculatorApp, CWinApp)
END_MESSAGE_MAP()

// CalculatorInitialApp-Erstellung
CalculatorApp::CalculatorApp() noexcept
{
	// TODO: Ersetzen Sie die Anwendungs-ID-Zeichenfolge unten durch eine eindeutige ID-Zeichenfolge; empfohlen
	// Das Format für die Zeichenfolge ist: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CalculatorInitial.AppID.NoVersion"));
}

// Das einzige CalculatorInitialApp-Objekt
CalculatorApp theApp;


BOOL CalculatorApp::InitInstance()
{
	CWinApp::InitInstance();
	//CalculatorDlg dlg;
	//dlg.DoModal();

	//new
	CalculatorDlg dlg;
	Calc calc;
	Controller cntr{dlg, calc};
	return TRUE;
}
