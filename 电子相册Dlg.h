
// �������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "map"

#include "SelectFolderDlg.h"

// C�������Dlg �Ի���
class C�������Dlg : public CDialogEx
{
// ����
public:
	C�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	//##################################### �Ա�д���� #####################################
	std::map<int, std::pair<CString, CString> > m_AllPhoto;//����ȫ��·��������
	std::map<int, std::pair<CString, CString> >::iterator i_Search;//������Ѱȫ����Ƭ��Ϣ�����ĵ�����

	int nPos;//��ǰ��ʾ��ͼƬ���

	CSelectFolderDlg m_SelectFolder;

	//######################################################################################
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
