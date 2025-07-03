
// ArrayDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Array.h"
#include "ArrayDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CArrayDlg dialog



CArrayDlg::CArrayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARRAY_DIALOG, pParent)
	, m_SelectedButton(0)
	, m_TotalObjects(0)
	, m_XExcursion(0)
	, m_YExcursion(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Z_SHAPE, m_ZShape);
	DDX_Control(pDX, IDC_S_SHAPE, m_SShape);
	DDX_Radio(pDX, IDC_RECTANGLE_ARRAY, m_SelectedButton);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_TOTAL_OBJECTS, m_TotalObjects);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_X_EXCURSION, m_XExcursion);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_Y_EXCURSION, m_YExcursion);
	DDX_Control(pDX, IDC_STATIC_TRANSLATION_DRAWING_AREA, m_DrawingArea);
}

BEGIN_MESSAGE_MAP(CArrayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_RECTANGLE_ARRAY, &CArrayDlg::OnBnClickedRectangleArray)
	ON_BN_CLICKED(IDC_CIRCULAR_ARRAY, &CArrayDlg::OnBnClickedCircularArray)
	ON_BN_CLICKED(IDC_MIRROR, &CArrayDlg::OnBnClickedMirror)
	ON_BN_CLICKED(IDC_TRANSLATION, &CArrayDlg::OnBnClickedTranslation)
	
	ON_BN_CLICKED(IDC_SAVE, &CArrayDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BACK, &CArrayDlg::OnBnClickedBack)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS, &CArrayDlg::OnEnChangeEditTranslationTotalObjects)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_X_EXCURSION, &CArrayDlg::OnEnChangeEditTranslationXExcursion)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_Y_EXCURSION, &CArrayDlg::OnEnChangeEditTranslationYExcursion)
	ON_STN_CLICKED(IDC_STATIC_TRANSLATION_DRAWING_AREA, &CArrayDlg::UpdatePictureControl)
END_MESSAGE_MAP()


// CArrayDlg message handlers

BOOL CArrayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	

	// set fixed position to the Dialog Box 

	/*CWnd* DialogBoxSize = GetDlgItem(IDD_ARRAY_DIALOG);

	if (DialogBoxSize)
	{
		DialogBoxSize->SetWindowPos(NULL, 0, 0, 1000, 300, SWP_NOMOVE | SWP_NOZORDER);
	}*/


	/// -----> rectangle 
	 // Initially hide Z Shape and S Shape radio buttons
	m_ZShape.ShowWindow(SW_SHOW);
	m_SShape.ShowWindow(SW_SHOW);

	GetDlgItem(IDC_ROW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COLUMN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ROW_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COLUMN_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_ROW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_COLUMN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ROW_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_COLUMN_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	// Set Rectangle Array as the default selected button
	m_SelectedButton =0;  // Default to Rectangle Array
	CheckDlgButton(IDC_RECTANGLE_ARRAY, BST_CHECKED);

	///----> for Translation 

	GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Mm)->ShowWindow(SW_HIDE);

	// ---> FOR MIRROR 
	GetDlgItem(IDC_RADIO_MIRROR_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_MIRROR_VERTICAL)->ShowWindow(SW_HIDE);

	//----> FOR CIRCULAR ARRAY
	GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	/*GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);*/
	GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CArrayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CArrayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CPaintDC dc(this);
	DrawGraph(dc); // Call your custom drawing logic

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CArrayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CArrayDlg::OnBnClickedRectangleArray()
{
	// TODO: Add your control notification handler code here
	
	m_SelectedButton = 0;
	// Show Z Shape and S Shape buttons
	GetDlgItem(IDC_Z_SHAPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_S_SHAPE)->ShowWindow(SW_SHOW);

	// Show additional controls for Rectangle Array
	GetDlgItem(IDC_ROW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COLUMN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ROW_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COLUMN_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);

	// Hide the corresponding static text controls
	GetDlgItem(IDC_STATIC_ROW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_COLUMN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ROW_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_COLUMN_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_RECTANGLE_MM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_RECTANGLE_Mm)->ShowWindow(SW_SHOW);



	
	//CWnd* pEditRectColExc = GetDlgItem(IDC_COLUMN_EXCURSION);
	//CWnd* pStaticRectColExc = GetDlgItem(IDC_STATIC_COLUMN_EXCURSION);
	//CWnd* pEditRectRowExc = GetDlgItem(IDC_ROW);
	//CWnd* pStaticRectRowExc = GetDlgItem(IDC_STATIC_ROW);


	//if (pEditRectColExc && pStaticRectColExc && pEditRectRowExc && pStaticRectRowExc)
	//{
	//	pEditRectColExc->SetWindowPos(
	//		nullptr,   // No Z-order change
	//		218,        // x-coordinate
	//		270,       // y-coordinate
	//		127,       // width
	//		23,        // height
	//		SWP_NOZORDER | SWP_NOACTIVATE
	//	);
	//	pStaticRectColExc->SetWindowPos(
	//		nullptr,   // No Z-order change
	//		77,        // x-coordinate
	//		270,       // y-coordinate
	//		200,       // width
	//		23,        // height
	//		SWP_NOZORDER | SWP_NOACTIVATE
	//	);


	//	pEditRectRowExc->SetWindowPos(
	//		nullptr,   // No Z-order change
	//		218,        // x-coordinate
	//		236,       // y-coordinate
	//		127,       // width
	//		23,        // height
	//		SWP_NOZORDER | SWP_NOACTIVATE
	//	);
	//	pStaticRectRowExc->SetWindowPos(
	//		nullptr,   // No Z-order change
	//		77,        // x-coordinate
	//		236,       // y-coordinate
	//		200,       // width
	//		23,        // height
	//		SWP_NOZORDER | SWP_NOACTIVATE
	//	);
	//}


	///----> for Translation 

	GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Mm)->ShowWindow(SW_HIDE);


	// ----> FOR MIRROR 

	GetDlgItem(IDC_RADIO_MIRROR_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_MIRROR_VERTICAL)->ShowWindow(SW_HIDE);

	//----> FOR CIRCULAR ARRAY
	GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	/*GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);*/
	GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);

	CClientDC dc(&m_DrawingArea);
	ClearDrawingArea(dc);
	
}


void CArrayDlg::OnBnClickedCircularArray()
{
	// TODO: Add your control notification handler code here
	m_SelectedButton = 1;
	/// -----> for  rectangle 
	 // Hide Z Shape and S Shape
	GetDlgItem(IDC_Z_SHAPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_SHAPE)->ShowWindow(SW_HIDE);

	// Hide additional controls for Rectangle Array
	GetDlgItem(IDC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	

	// Hide the corresponding static text controls
	GetDlgItem(IDC_STATIC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_Mm)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_MM)->ShowWindow(SW_HIDE);


	///----> for Translation 

	GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Mm)->ShowWindow(SW_HIDE);



	// ----> FOR MIRROR 

	GetDlgItem(IDC_RADIO_MIRROR_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_MIRROR_VERTICAL)->ShowWindow(SW_HIDE);

	//----> FOR CIRCULAR ARRAY
	//----> FOR CIRCULAR ARRAY
	GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_SHOW);


	// set positions for tools on dialog box 

	// Set positions for specific controls using SetWindowPos
	CWnd* pEditFillingAngle = GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE);
	CWnd* pStaticFillingAngle = GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE);
	/*CWnd* pEditRECT_BENCHMARK = GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK);
	CWnd* pStaticRECT_BENCHMARK = GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK);*/
	CWnd* pEditCircularTO = GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT);
	CWnd* pStaticCircularTO = GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT);


	CClientDC dc(&m_DrawingArea);
	ClearDrawingArea(dc);


	if (pEditCircularTO && pStaticCircularTO && pEditFillingAngle && pStaticFillingAngle)
	{
		pEditCircularTO->SetWindowPos(
			nullptr,   // No Z-order change
			218,        // x-coordinate
			289,       // y-coordinate
			127,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);
		pStaticCircularTO->SetWindowPos(
			nullptr,   // No Z-order change
			132,        // x-coordinate
			291,       // y-coordinate
			127,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		// Move the edit box control
		pEditFillingAngle->SetWindowPos(
			nullptr,   // No Z-order change
			218,        // x-coordinate
			331,       // y-coordinate
			127,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		// Move the static text control
		pStaticFillingAngle->SetWindowPos(
			nullptr,   // No Z-order change
			133,        // x-coordinate
			332,        // y-coordinate
			127,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		//pEditRECT_BENCHMARK->SetWindowPos(
		//	nullptr,   // No Z-order change
		//	218,        // x-coordinate
		//	369,       // y-coordinate
		//	127,       // width
		//	23,        // height
		//	SWP_NOZORDER | SWP_NOACTIVATE
		//);
		//pStaticRECT_BENCHMARK->SetWindowPos(
		//	nullptr,   // No Z-order change
		//	77,        // x-coordinate
		//	369,       // y-coordinate
		//	200,       // width
		//	23,        // height
		//	SWP_NOZORDER | SWP_NOACTIVATE
		//);

	}

}


void CArrayDlg::OnBnClickedMirror()
{
	// TODO: Add your control notification handler code here
	
	m_SelectedButton = 2;
	/// -----> rectangle 
	 // Hide Z Shape and S Shape
	GetDlgItem(IDC_Z_SHAPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_SHAPE)->ShowWindow(SW_HIDE);

	// Hide additional controls for Rectangle Array
	GetDlgItem(IDC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);

	// Hide the corresponding static text controls
	GetDlgItem(IDC_STATIC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_MM)->ShowWindow(SW_HIDE);

	///----> for Translation 

	GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_HIDE);
//	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TRANSLATION_Mm)->ShowWindow(SW_HIDE);



	// ----> FOR MIRROR 

	GetDlgItem(IDC_RADIO_MIRROR_LEVEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO_MIRROR_VERTICAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_SHOW);
	

	//----> FOR CIRCULAR ARRAY
	GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);

	CClientDC dc(&m_DrawingArea);
	ClearDrawingArea(dc);
}


void CArrayDlg::OnBnClickedTranslation()
{
	// TODO: Add your control notification handler code here
	m_SelectedButton = 3;

	
	/// -----> rectangle 
	 // Hide Z Shape and S Shape
	GetDlgItem(IDC_Z_SHAPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_S_SHAPE)->ShowWindow(SW_HIDE);

	// Hide additional controls for Rectangle Array
	GetDlgItem(IDC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);

	// Hide the corresponding static text controls
	GetDlgItem(IDC_STATIC_ROW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ROW_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLUMN_EXCURSION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_MM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECTANGLE_Mm)->ShowWindow(SW_HIDE);


	    
	///----> for Translation 

	GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_MM)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_TRANSLATION_Mm)->ShowWindow(SW_SHOW);



	// ----> FOR MIRROR 

	GetDlgItem(IDC_RADIO_MIRROR_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_MIRROR_VERTICAL)->ShowWindow(SW_HIDE);

	//----> FOR CIRCULAR ARRAY
	GetDlgItem(IDC_EDIT_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_TOTAL_OBJECT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ARRAY_BENCHMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_CIRCULAR_FILLING_ANGLE)->ShowWindow(SW_HIDE);

     


	CWnd* pStaticTranslationTO = GetDlgItem(IDC_STATIC_TRANSLATION_TOTAL_OBJECTS);
	CWnd* pEditTranslationTO = GetDlgItem(IDC_EDIT_TRANSLATION_TOTAL_OBJECTS);
	CWnd* pStaticTranslationX = GetDlgItem(IDC_STATIC_TRANSLATION_X_EXCURSION);
	CWnd* pEditTranslationX = GetDlgItem(IDC_EDIT_TRANSLATION_X_EXCURSION);
	CWnd* pStaticTranslationY = GetDlgItem(IDC_STATIC_TRANSLATION_Y_EXCURSION);
	CWnd* pEditTranslationY = GetDlgItem(IDC_EDIT_TRANSLATION_Y_EXCURSION);
	CWnd* pStaticTranslationBenchMark= GetDlgItem(IDC_STATIC_TRANSLATION_BENCHMARK);
	CWnd* pEditTranslationBenchMark = GetDlgItem(IDC_COMBO_TRANSLATION_BENCHMARK);


	if (pStaticTranslationTO && pEditTranslationTO && pStaticTranslationX && pEditTranslationX && pStaticTranslationY && pEditTranslationY && pStaticTranslationBenchMark && pEditTranslationBenchMark)
	{
		pStaticTranslationTO->SetWindowPos(
			nullptr,   // No Z-order change
			166,        // x-coordinate
			232,       // y-coordinate
			88,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		pEditTranslationTO->SetWindowPos(
			nullptr,   // No Z-order change
			255,        // x-coordinate
			232,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);
		pStaticTranslationX->SetWindowPos(
			nullptr,   // No Z-order change
			148,        // x-coordinate
			268,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		pEditTranslationX->SetWindowPos(
			nullptr,   // No Z-order change
			255,        // x-coordinate
			268,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);
		pStaticTranslationY->SetWindowPos(
			nullptr,   // No Z-order change
			148,        // x-coordinate
			308,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		pEditTranslationY->SetWindowPos(
			nullptr,   // No Z-order change
			255,        // x-coordinate
			308,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);
		pStaticTranslationBenchMark->SetWindowPos(
			nullptr,   // No Z-order change
			118,        // x-coordinate
			348,       // y-coordinate
			130,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);

		pEditTranslationBenchMark->SetWindowPos(
			nullptr,   // No Z-order change
			255,        // x-coordinate
			348,       // y-coordinate
			100,       // width
			23,        // height
			SWP_NOZORDER | SWP_NOACTIVATE
		);



	}






	// Set default values for Translation inputs
	m_TotalObjects = 4; // Default total objects
	m_XExcursion = 10;   // Default X excursion
	m_YExcursion = 10;  // Default Y excursion

	// Update the UI with these default values
	UpdateData(FALSE);  // FALSE to transfer data from variables to controls

	// Immediately update the picture control
	CClientDC dc(&m_DrawingArea);
	DrawGraph(dc);       // Draw axes
	DrawRectangles(dc);  // Draw rectangles based on default values
		
}


void CArrayDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here	
	UpdateData(TRUE); // Get inputs from UI	
	
	if ((m_SelectedButton == 3)) {
		// Repaint the drawing area
		
		CClientDC dc(&m_DrawingArea);
		ClearDrawingArea(dc);
		DrawGraph(dc);       // Draw axes
		DrawRectangles(dc);  // Draw rectangles 

	}
	 
}

void CArrayDlg::ClearDrawingArea(CDC& dc)
{
	// Clear the drawing area by filling it with the background color
	CBrush brush(::GetSysColor(COLOR_WINDOW)); // Default window background color
	CRect rect;
	m_DrawingArea.GetClientRect(&rect);
	dc.FillRect(&rect, &brush);
}

void CArrayDlg::DrawGraph(CDC& dc)
{
	// TODO: Add your implementation code here.
	CRect rect;
	m_DrawingArea.GetClientRect(&rect);
	int midX = rect.Width() / 2;
	int midY = rect.Height() / 2;

	dc.MoveTo(midX, 0);
	dc.LineTo(midX, rect.Height()); // Y-axis

	dc.MoveTo(0, midY);
	dc.LineTo(rect.Width(), midY); // X-axis
}
void CArrayDlg::DrawRectangles(CDC& dc)
{
	// Get the client area of the drawing area
	CRect rect;
	m_DrawingArea.GetClientRect(&rect);

	// Center of the drawing area
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;

	// Parse input values
	int totalObjects = m_TotalObjects;
	double xExcursion = m_XExcursion;
	double yExcursion = m_YExcursion;

	// Validation for total objects
	if (totalObjects <= 0)
	{
		AfxMessageBox(_T("Total Objects must be greater than 0."));
		return;
	}

	// Define rectangle size
	int rectWidth = 15;
	int rectHeight = 6;

	// Fixed step size for distance between rectangles
	int stepSize = 17; // You can adjust this distance between rectangles

	// Normalize the excursion values to get direction
	double magnitude = sqrt(xExcursion * xExcursion + yExcursion * yExcursion);
	if (magnitude != 0)
	{
		xExcursion /= magnitude;  // Normalize to unit vector along X direction
		yExcursion /= magnitude;  // Normalize to unit vector along Y direction
	}

	// Initial position of the first rectangle (center of the drawing area)
	int x = centerX;
	int y = centerY;

	// Create a darker pen for the first rectangle's border

	
	// Draw rectangles
	for (int i = 0; i < totalObjects; ++i)
	{
		// Calculate the top-left and bottom-right corners of the rectangle
		int left = x - (rectWidth / 2);
		int top = y - (rectHeight / 2);
		int right = x + (rectWidth / 2);
		int bottom = y + (rectHeight / 2);

		// Check if the rectangle goes beyond the picture controller boundaries
		if (left >= 0 && right <= rect.Width() && top >= 0 && bottom <= rect.Height())
		{
			if (i == 0)
			{
				// Draw the first rectangle's perimeter with the dark pen
				dc.Rectangle(left, top, right, bottom);
			}
			else
			{
				// Restore the default pen for subsequent rectangles
				dc.Rectangle(left, top, right, bottom);
			}
		}
		else
		{
			// Stop drawing if the next rectangle goes out of bounds
			break;
		}

		// Move to the next position based on the normalized direction and constant distance (stepSize)
		x += static_cast<int>(xExcursion * stepSize);  // Move by normalized direction and fixed distance
		y -= static_cast<int>(yExcursion * stepSize);  // Move by normalized direction and fixed distance
	}

	
}


void CArrayDlg::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	OnOK(); 
}

void CArrayDlg::OnEnChangeEditTranslationTotalObjects()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// Update and redraw immediately when Total Objects changes
	UpdateData(TRUE);
	UpdatePictureControl();

}


void CArrayDlg::OnEnChangeEditTranslationXExcursion()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
		// Update and redraw immediately when X Excursion changes
	UpdateData(TRUE);
	UpdatePictureControl();

}


void CArrayDlg::OnEnChangeEditTranslationYExcursion()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// Update and redraw immediately when Y Excursion changes
	UpdateData(TRUE);
	UpdatePictureControl();
}


void CArrayDlg::UpdatePictureControl()
{
	// Redraw the graph and rectangles with the updated data
	CClientDC dc(&m_DrawingArea);

	// Clear the previous drawing
	ClearDrawingArea(dc);

	// Draw the updated graph and rectangles
	DrawGraph(dc);
	DrawRectangles(dc);
}


