#pragma once

class CalculatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CalculatorDlg)
public:
	CalculatorDlg() noexcept;

protected:
	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog() override;
	afx_msg void OnAdd();
	afx_msg void OnSub();
	afx_msg void OnMul();
	afx_msg void OnDiv();
	afx_msg void OnMod();
	afx_msg void OnExp();
	afx_msg void OnNum();
	void OnOK() override;
	DECLARE_MESSAGE_MAP()

private:
	double num1;
	double num2;
	CString result;
	char operation;
	CListBox history;
};
