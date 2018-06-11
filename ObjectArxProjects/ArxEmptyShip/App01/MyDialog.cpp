#include "stdafx.h"

#include "MyDialog.h"


//*

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	myButton.Create(_T("My button"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(10, 10, 100, 30), this, 1);

	//SetDlgItemText(IDC_EDIT_OF_MY_DIALOG, m_value);

	return TRUE;
}

BOOL CMyDialog::DestroyWindow()
{
	//GetDlgItemText(IDC_EDIT_OF_MY_DIALOG, m_value);

	return CDialog::DestroyWindow();
}

INT_PTR CMyDialog::DoModal()
{
	//GetDlgItemText(IDC_EDIT_OF_MY_DIALOG, m_value);

	return CDialog::DoModal();
}

BOOL CMyDialog::ShowWindow(int nCmdShow)
{
	return CDialog::ShowWindow(nCmdShow);
}

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_BN_CLICKED(IDC_OKBTN_OF_MY_DIALOG, &CMyDialog::OnBnClickedOk)
END_MESSAGE_MAP()


void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OKBTN_OF_MY_DIALOG, myButton);
}



void CMyDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

//*/



/*

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CSomeInfo, CAdUiBaseDialog)

BEGIN_MESSAGE_MAP(CSomeInfo, CAdUiBaseDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDABOUT, &CSomeInfo::OnBnClickedAbout)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CSomeInfo::CSomeInfo(CWnd *pParent //=NULL
					, HINSTANCE hInstance //=NULL
					) : CAdUiBaseDialog(CSomeInfo::IDD, pParent, hInstance)
{
}

//-----------------------------------------------------------------------------
void CSomeInfo::DoDataExchange(CDataExchange *pDX)
{
	CAdUiBaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSC, m_strListsc);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CSomeInfo::OnAcadKeepFocus(WPARAM, LPARAM) 
{
	return (TRUE);
}


BOOL CSomeInfo::OnInitDialog()
{
	CAdUiBaseDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	CString s = "Информацию о системе\r\n";
	s += "можно найти на сайте:\r\n";
	s += "http://poleshchuk.spb.ru/cad/2014/r-ship-plus.htm\r\n";
	m_strListsc.SetWindowText(s);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CSomeInfo::OnBnClickedAbout()
{
	// TODO: добавьте свой код обработчика уведомлений
	MessageBox(L"Группа RSHIP\nСанкт-Петербург, Российская Федерация, 2014", L"Разработчики", MB_OK | MB_ICONINFORMATION);
}

//*/

