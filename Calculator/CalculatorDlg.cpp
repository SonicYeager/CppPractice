#include "stdafx.h"
#include "CalculatorDlg.h"
#include "Resource.h"
#include <cmath>

IMPLEMENT_DYNAMIC(CalculatorDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CalculatorDlg, CDialogEx)
ON_WM_CREATE()
ON_BN_CLICKED(IDC_ADD, OnAdd)
ON_BN_CLICKED(IDC_SUB, OnSub)
ON_BN_CLICKED(IDC_MUL, OnMul)
ON_BN_CLICKED(IDC_DIV, OnDiv)
ON_BN_CLICKED(IDC_MOD, OnMod)
ON_BN_CLICKED(IDC_EXP, OnExp)
ON_EN_CHANGE(IDC_NUM1, OnNum)
ON_EN_CHANGE(IDC_NUM2, OnNum)
END_MESSAGE_MAP()

CalculatorDlg::CalculatorDlg() noexcept //standalone
	: CDialogEx(IDD_CALCULATOR)
	, num1(0)
	, num2(0)
	, result("0")
	, operation(' ')
	, history{}
{}

//void CalculatorDlg::Init()
//{
//	DoModal();
//}
//
//void CalculatorDlg::SetResult(const std::string& strRes)
//{
//	CString c{strRes.c_str()};
//	result.SetString(c);
//	UpdateData(FALSE);
//}
//
//void CalculatorDlg::AddHistory(const std::string& his)
//{
//	CString txt{his.c_str()};
//	int count = history.AddString(txt);
//	history.SetCurSel(count);
//	UpdateData(FALSE);
//}
//
//std::pair<double, double> CalculatorDlg::GetValues()
//{
//	UpdateData(TRUE);
//	return std::make_pair(num1, num2);
//}

void CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	::DDX_Text(pDX, IDC_NUM1, num1);
	::DDX_Text(pDX, IDC_NUM2, num2);
	::DDX_Text(pDX, IDC_RESULT, result);
	::DDX_Control(pDX, IDC_HIST, history);
}

BOOL CalculatorDlg::OnInitDialog()
{
	BOOL res = CDialogEx::OnInitDialog();
	if(res != FALSE)
		history.SetWindowText(L"History");
	return res;
}

void CalculatorDlg::OnAdd()
{
	UpdateData();
	auto res = calc.Add(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '+';
	CString txt;
	txt.Format(L"%g + %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnSub()
{
	UpdateData();
	auto res = calc.Sub(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '-';
	CString txt;
	txt.Format(L"%g - %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnMul()
{
	UpdateData();
	auto res = calc.Mul(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '*';
	CString txt;
	txt.Format(L"%g * %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnDiv()
{
	UpdateData();
	auto res = calc.Div(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '/';
	CString txt;
	txt.Format(L"%g / %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnMod()
{
	UpdateData();
	auto res = calc.Mod(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '%';
	CString txt;
	txt.Format(L"%g mod %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnExp()
{
	UpdateData();
	auto res = calc.Exp(num1, num2);
	result.SetString(CString(res.str().c_str()));
	operation = '^';
	CString txt;
	txt.Format(L"%g ^ %g = %s", num1, num2, result);
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

void CalculatorDlg::OnNum()
{
	switch(operation)
	{
	case '+':
		OnAdd();
		break;
	case '-':
		OnSub();
		break;
	case '*':
		OnMul();
		break;
	case '/':
		OnDiv();
		break;
	case '%':
		OnMod();
		break;
	case '^':
		OnExp();
		break;
	}
}

void CalculatorDlg::OnOK()
{
	//Keep empty to prevent close dialog if press key 'ENTER'
}
