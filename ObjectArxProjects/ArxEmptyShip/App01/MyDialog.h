#pragma once

#include <stdio.h>
#include <afxwin.h>

// Диалоговые окна
// CAdUiBaseDialog , CAdUiDialog , CAcUiDialog,
#include <acui.h>
#include <adui.h>

//#include "stdafx.h"


//*

//class CMyButton : CButton
//{
//
//};

//class ParametersDialog : public CAdUiBaseDialog
//{
//};

//class CMyDialog : CDialog
class CMyDialog : CAdUiBaseDialog
{
  CString m_value;
  CButton myButton;

public:  

#define IDC_MY_DIALOG			987654320
#define IDABOUT					987654321
#define IDC_LISTSC				987654322

#define IDC_EDIT_OF_MY_DIALOG   987654331
#define IDC_OKBTN_OF_MY_DIALOG  987654332

  //CMyDialog(CTestOutDialogDoc* pD, CWnd* pParent = NULL);   // standard constructor

  //CMyDialog() { ; }
  //CMyDialog() { ; }
  ~CMyDialog() {}

  CString GetValue() const
  {
	  return m_value;
  }

  void SetValue(const CString& value)
  {
	  m_value = value;
  }


  virtual BOOL OnInitDialog();
  virtual BOOL DestroyWindow();
  BOOL ShowWindow(int nCmdShow);

  virtual INT_PTR DoModal();

protected:
  virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

  DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();

};

//*/



/*

//-----------------------------------------------------------------------------
class CSomeInfo : public CAdUiBaseDialog
{
	#define IDC_MY_DIALOG			987654320
	#define IDABOUT					987654321
	#define IDC_LISTSC				987654322
	
	#define IDC_EDIT_OF_MY_DIALOG   987654331
	#define IDC_OKBTN_OF_MY_DIALOG  987654332

	DECLARE_DYNAMIC(CSomeInfo)

public:
	CSomeInfo(CWnd *pParent = NULL, HINSTANCE hInstance = NULL);

	enum { IDD = IDC_MY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	afx_msg LRESULT OnAcadKeepFocus(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_strListsc;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAbout();


};

//*/
