#pragma once
#include "Contracts.h"

class CalculatorDlg : public CDialogEx //, public Ui
{
	DECLARE_DYNAMIC(CalculatorDlg)
public:
	CalculatorDlg() noexcept;

	//void Init() override;
	//void SetResult(const std::string&) override;
	//void AddHistory(const std::string&) override;
	//std::pair<double, double> GetValues() override;

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
