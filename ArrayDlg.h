
// ArrayDlg.h : header file
//

#pragma once


// CArrayDlg dialog
class CArrayDlg : public CDialogEx
{
// Construction
public:
	CArrayDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARRAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_ZShape;
	CButton m_SShape;
	int m_SelectedButton;

	afx_msg void OnBnClickedRectangleArray();
	afx_msg void OnBnClickedCircularArray();
	afx_msg void OnBnClickedMirror();
	afx_msg void OnBnClickedTranslation();
	
	int m_TotalObjects;
	double m_XExcursion;
	double m_YExcursion;
	afx_msg void OnBnClickedSave();
	CStatic m_DrawingArea;
	void DrawGraph(CDC& dc);
	void DrawRectangles(CDC& dc);
	afx_msg void OnBnClickedBack();

	afx_msg void ClearDrawingArea(CDC& dc);
	afx_msg void OnEnChangeEditTranslationTotalObjects();
	afx_msg void OnEnChangeEditTranslationXExcursion();
	afx_msg void OnEnChangeEditTranslationYExcursion();
	afx_msg void UpdatePictureControl();
//	afx_msg void OnBnClickedRadioMirrorVertical();
};
