
// 电子相册Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "map"

#include "SelectFolderDlg.h"

// C电子相册Dlg 对话框
class C电子相册Dlg : public CDialogEx
{
// 构造
public:
	C电子相册Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	//##################################### 自编写部分 #####################################
	std::map<int, std::pair<CString, CString> > m_AllPhoto;//保存全部路径与名称
	std::map<int, std::pair<CString, CString> >::iterator i_Search;//用于搜寻全部照片信息容器的迭代器

	int nPos;//当前显示的图片编号

	CSelectFolderDlg m_SelectFolder;

	//######################################################################################
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl m_PhotoList;
	afx_msg void OnBnClickedOpenphoto();
	afx_msg void OnBnClickedTurnfirst();
	afx_msg void OnBnClickedFront();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedTurnlast();
	afx_msg void OnBnClickedOutputphoto();
	int ReadFile();
	int SaveFile();
	int ResizePhoto(CString path, CImage& photo, int& nPos_x, int& nPos_y, int& nWidth, int& nHeight);
	CRichEditCtrl m_ShowPhoto;
	afx_msg void OnNMClickPhotolist(NMHDR *pNMHDR, LRESULT *pResult);
	int ShowPhotoList();
	afx_msg void OnBnClickedDelete();
};
