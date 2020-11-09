#include "stdafx.h"
#include "CalculatorDlg.h"
#include "Resource.h"

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
	, history{}
{}

void CalculatorDlg::Init()
{
	DoModal();
}

void CalculatorDlg::SetResult(const std::string& strRes)
{
	CString c{strRes.c_str()};
	result.SetString(c);
	UpdateData(FALSE);
}

void CalculatorDlg::AddHistory(const std::string& his)
{
	CString txt{his.c_str()};
	int count = history.AddString(txt);
	history.SetCurSel(count);
	UpdateData(FALSE);
}

std::pair<double, double> CalculatorDlg::GetValues()
{
	UpdateData(TRUE);
	return std::make_pair(num1, num2);
}

std::string ComposeHistory(double left, double right, char op, const std::stringstream& result)
{
	std::stringstream res;
	res << left << " " << op << " " << right << " = " << result.str();
	return res.str();
}

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
	onAdd();
}

void CalculatorDlg::OnSub()
{
	onSub();
}

void CalculatorDlg::OnMul()
{
	onMul();
}

void CalculatorDlg::OnDiv()
{
	onDiv();
}

void CalculatorDlg::OnMod()
{
	onMod();
}

void CalculatorDlg::OnExp()
{
	onExp();
}

void CalculatorDlg::OnNum()
{
	onNum();
}

void CalculatorDlg::OnOK()
{
	//Keep empty to prevent close dialog if press key 'ENTER'
}
