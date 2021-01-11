
// �������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�������.h"
#include "�������Dlg.h"
#include "afxdialogex.h"

#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C�������Dlg �Ի���



C�������Dlg::C�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHOTOLIST, m_PhotoList);
	DDX_Control(pDX, IDC_SHOWPHOTO, m_ShowPhoto);
}

BEGIN_MESSAGE_MAP(C�������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C�������Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C�������Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPENPHOTO, &C�������Dlg::OnBnClickedOpenphoto)
	ON_BN_CLICKED(IDC_TURNFIRST, &C�������Dlg::OnBnClickedTurnfirst)
	ON_BN_CLICKED(IDC_FRONT, &C�������Dlg::OnBnClickedFront)
	ON_BN_CLICKED(IDC_NEXT, &C�������Dlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_TURNLAST, &C�������Dlg::OnBnClickedTurnlast)
	ON_BN_CLICKED(IDC_OUTPUTPHOTO, &C�������Dlg::OnBnClickedOutputphoto)
	ON_NOTIFY(NM_CLICK, IDC_PHOTOLIST, &C�������Dlg::OnNMClickPhotolist)
	ON_BN_CLICKED(IDC_DELETE, &C�������Dlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// C�������Dlg ��Ϣ�������

BOOL C�������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//##################################### �Ա�д���� #####################################
	m_PhotoList.InsertColumn(0, _T("�ļ���"),2,80);
	m_PhotoList.InsertColumn(1, _T("�ļ�·��"), 2, 200);

	ReadFile();
	ShowPhotoList();
	GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);

	//######################################################################################
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C�������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C�������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C�������Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void C�������Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SaveFile();
	CDialogEx::OnCancel();
}

//========================================== ����Ƭ =================================================
void C�������Dlg::OnBnClickedOpenphoto()
{
	CString sName;
	CString sPath;
	CFileDialog m_OpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files(*.*)|*.*||"));
	if (m_OpenDlg.DoModal()==IDOK)
	{
		sName = m_OpenDlg.GetFileName();
		sPath = m_OpenDlg.GetPathName();
		m_AllPhoto.insert(std::make_pair(m_AllPhoto.size(), std::make_pair(sName, sPath)));
		ShowPhotoList();

	}
}

//========================================== ת������ =================================================
void C�������Dlg::OnBnClickedTurnfirst()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
	pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
	int nPos_X;
	int nPos_Y;
	int nWidth;
	int nHeight;
	CImage m_Photo;
	if (m_AllPhoto.size()!=0)
	{
		nPos = 0;
		ResizePhoto(m_AllPhoto[0].second, m_Photo, nPos_X,nPos_Y, nWidth, nHeight);
		pDC = m_ShowPhoto.GetDC();
		pDC->SelectObject(m_Brush);
		pDC->Rectangle(rect);
		m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);

		GetDlgItem(IDC_TURNFIRST)->EnableWindow(FALSE);
		GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_TURNLAST)->EnableWindow(TRUE);
	}
}

//========================================== ��һ�� =================================================
void C�������Dlg::OnBnClickedFront()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
	pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
	int nPos_X;
	int nPos_Y;
	int nWidth;
	int nHeight;
	CImage m_Photo;
	if (m_AllPhoto.size() != 0)
	{
		nPos--;
		ResizePhoto(m_AllPhoto[nPos].second, m_Photo, nPos_X, nPos_Y, nWidth, nHeight);
		pDC = m_ShowPhoto.GetDC();
		pDC->SelectObject(m_Brush);
		pDC->Rectangle(rect);
		m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);
		if (nPos==0)
		{
			GetDlgItem(IDC_TURNFIRST)->EnableWindow(FALSE);
			GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_TURNLAST)->EnableWindow(TRUE);
		}
	}
}

//========================================== ��һ�� =================================================
void C�������Dlg::OnBnClickedNext()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
	pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
	int nPos_X;
	int nPos_Y;
	int nWidth;
	int nHeight;
	CImage m_Photo;
	if (m_AllPhoto.size() != 0)
	{
		nPos++;
		ResizePhoto(m_AllPhoto[nPos].second, m_Photo, nPos_X, nPos_Y, nWidth, nHeight);
		pDC = m_ShowPhoto.GetDC();
		pDC->SelectObject(m_Brush);
		pDC->Rectangle(rect);
		m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);
		if (nPos == m_AllPhoto.size()-1)
		{
			GetDlgItem(IDC_TURNFIRST)->EnableWindow(TRUE);
			GetDlgItem(IDC_FRONT)->EnableWindow(TRUE);
			GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
			GetDlgItem(IDC_TURNLAST)->EnableWindow(FALSE);
		}
	}
}

//========================================== ת�����һ�� ===========================================
void C�������Dlg::OnBnClickedTurnlast()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
	pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
	int nPos_X;
	int nPos_Y;
	int nWidth;
	int nHeight;
	CImage m_Photo;
	if (m_AllPhoto.size() != 0)
	{
		nPos = m_AllPhoto.size() - 1;
		ResizePhoto(m_AllPhoto[m_AllPhoto.size()-1].second, m_Photo, nPos_X, nPos_Y,nWidth,nHeight);
		pDC = m_ShowPhoto.GetDC();
		pDC->SelectObject(m_Brush);
		pDC->Rectangle(rect);
		m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);

		GetDlgItem(IDC_TURNFIRST)->EnableWindow(TRUE);
		GetDlgItem(IDC_FRONT)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TURNLAST)->EnableWindow(FALSE);
	}
}

//========================================== ������� ===============================================
void C�������Dlg::OnBnClickedOutputphoto()
{
	CString sNewPath;
	CString sPath;
	sPath = m_SelectFolder.Show();
	if (!sPath.IsEmpty())
	{
		i_Search = m_AllPhoto.begin();
		while (i_Search!=m_AllPhoto.end())
		{
			sNewPath = sPath + _T("\\") + i_Search->second.first;
			CopyFile(i_Search->second.second, sNewPath, FALSE);//�����ļ�
			i_Search++;
		}
		MessageBox(_T("��ᵼ���ɹ���"),_T("ϵͳ��ʾ"));
	}
}

//========================================== ��ȡ�ļ� ===============================================
int C�������Dlg::ReadFile()
{
	setlocale(LC_CTYPE, "chs");
	int nCount = 0;
	CString sOneline;
	CString sName;
	CString sPath;
	int nBit;
	CStdioFile m_ReadFile;
	m_AllPhoto.clear();//��ձ�����Ϣ������
	m_ReadFile.Open(_T("path.txt"),CFile::modeRead);//���ļ�
	while (m_ReadFile.ReadString(sOneline))//��ȡ�ļ�һ��
	{
		nBit = sOneline.Find(_T(","));
		sName = sOneline.Left(nBit);
		sOneline.Delete(0, nBit + 1);
		sPath = sOneline;
		m_AllPhoto.insert(std::make_pair(nCount, std::make_pair(sName, sPath)));//��������������·����������
		nCount++;//���+1
	}
	m_ReadFile.Close();
	return 0;
}

//========================================== �����ļ� ===============================================
int C�������Dlg::SaveFile()
{

	setlocale(LC_CTYPE, "chs");
	CString sOneline;
	CStdioFile m_SaveFile;
	m_SaveFile.Open(_T("path.txt"),CFile::modeCreate|CFile::modeWrite);
	i_Search = m_AllPhoto.begin();
	while (i_Search!=m_AllPhoto.end())
	{
		sOneline = i_Search->second.first + _T(",") + i_Search->second.second + _T("\n");
		m_SaveFile.WriteString(sOneline);
		i_Search++;
	}
	m_SaveFile.Close();
	return 0;
}

//====================================== �޸���Ƭ�ߴ���������ʾ =====================================
int C�������Dlg::ResizePhoto(CString path, CImage& photo,int& nPos_x,int& nPos_y,int& nWidth,int& nHeight)
{
	CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
	pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
	int WIDTH = rect.Width();
	int HEIGHT = rect.Height();
	CImage m_OriPhoto;
	photo.Destroy();
	m_OriPhoto.Load(path);
	if (m_OriPhoto.IsNull())
	{
		MessageBox(_T("δ���ļ�"));
	}
	nWidth = 0;
	nHeight = 0;

	nWidth = m_OriPhoto.GetWidth();//��Ƭʵ�ʳߴ�
	nHeight = m_OriPhoto.GetHeight();//��Ƭʵ�ʳߴ�

	double fX_Rate;//X�ı���
	double fY_Rate;//Y�ı���

	fX_Rate = (double)nWidth / (double)WIDTH;//�����
	fY_Rate = (double)nHeight / (double)HEIGHT;//�����
	

	if (fX_Rate<=1&&fY_Rate<=1)
	{
		//��ʾͼƬ�ĳߴ����ʾ����С
		//����λ��
		
		nPos_x = WIDTH / 2 - nWidth / 2;
		nPos_y = HEIGHT / 2 - nHeight / 2;
	} 
	else
	{
		if (fX_Rate<=1&&fY_Rate>1)//��Ƭ�߶�Խ�磬���ݸ߶ȵı�����������ȳ߶�
		{
			nHeight = HEIGHT;
			nWidth = (double)nWidth / fY_Rate;//����������Ŀ���
			nPos_y = 0;
			nPos_x = WIDTH / 2.0 - nWidth / 2.0;
		} 
		else
		{
			if (fY_Rate <= 1 && fX_Rate>1)//��Ƭ���Խ�磬���ݿ�ȵı����������߶ȳ߶�
			{
				nWidth = WIDTH;
				nHeight = (double)nHeight / fX_Rate;//����������ĸ߶�
				nPos_x = 0;
				nPos_y = HEIGHT / 2 - nHeight / 2;
			} 
			else
			{
				if (fX_Rate>fY_Rate)//�߶�˫˫Խ�磬��ȷ����Խ�������
				{
					nWidth = WIDTH;
					nHeight = (double)nHeight / fX_Rate;
					nPos_x = 0;
					nPos_y = HEIGHT / 2 - nHeight / 2;
				} 
				else
				{
					//�߶ȷ����Խ�������
					nHeight = HEIGHT;
					nWidth = (double)nWidth / fY_Rate;
					nPos_y = 0;
					nPos_x= WIDTH / 2.0 - nWidth / 2.0;

				}
			}
		}
	}
	if (!photo.CreateEx(nWidth, nHeight, 24, BI_RGB))
	{
		MessageBox(_T("����ʧ��"));
	}

	int nPreMode = ::SetStretchBltMode(photo.GetDC(), HALFTONE);
	photo.ReleaseDC();
	m_OriPhoto.Draw(photo.GetDC(), 0, 0, nWidth, nHeight, 0, 0, m_OriPhoto.GetWidth(), m_OriPhoto.GetHeight());
	photo.ReleaseDC();
	::SetBrushOrgEx(photo.GetDC(), 0, 0, NULL);
	photo.ReleaseDC();
	::SetStretchBltMode(photo.GetDC(), nPreMode);
	photo.ReleaseDC();

	return 0;
}

//======================================= ѡ���б��е�һ����Ƭ ======================================
void C�������Dlg::OnNMClickPhotolist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nSelect;
	nSelect = m_PhotoList.GetSelectionMark();
	if (nSelect!=-1)
	{
		nPos = nSelect;
		CBrush m_Brush(RGB(100, 100, 100));
		CDC* pDC;
		CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
		CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
		pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
		int nPos_X;
		int nPos_Y;
		int nWidth;
		int nHeight;
		CImage m_Photo;
		if (m_AllPhoto.size() != 0)
		{
			ResizePhoto(m_AllPhoto[nSelect].second, m_Photo, nPos_X, nPos_Y, nWidth, nHeight);
			pDC = m_ShowPhoto.GetDC();
			pDC->SelectObject(m_Brush);
			pDC->Rectangle(rect);
			m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);
		}
		if (nPos==0)
		{
			GetDlgItem(IDC_TURNFIRST)->EnableWindow(FALSE);
			GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_TURNLAST)->EnableWindow(TRUE);
		}
		else
		{
			if (nPos == m_AllPhoto.size() - 1)
			{
				GetDlgItem(IDC_TURNFIRST)->EnableWindow(TRUE);
				GetDlgItem(IDC_FRONT)->EnableWindow(TRUE);
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_TURNLAST)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_TURNFIRST)->EnableWindow(TRUE);
				GetDlgItem(IDC_FRONT)->EnableWindow(TRUE);
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_TURNLAST)->EnableWindow(TRUE);
			}
		}

	}

	*pResult = 0;
}

//========================================= ��ʾ��Ϣ ================================================
int C�������Dlg::ShowPhotoList()
{
	int n = 0;
	m_PhotoList.DeleteAllItems();
	i_Search = m_AllPhoto.begin();
	while (i_Search!=m_AllPhoto.end())
	{
		m_PhotoList.InsertItem(n,i_Search->second.first);
		m_PhotoList.SetItemText(n, 1, i_Search->second.second);
		i_Search++;
		n++;
	}
	return 0;
}

//========================================== ɾ��ͼƬ ===============================================
void C�������Dlg::OnBnClickedDelete()
{
	int nSelect;
	nSelect = m_PhotoList.GetSelectionMark();
	if (nSelect==-1)
	{
		MessageBox(_T("�����б���ѡ��һ��ͼƬ����ɾ��"),_T("��ʾ"));
	} 
	else
	{
		i_Search = m_AllPhoto.begin();
		for (int i=0;i<nSelect;i++)
		{
			i_Search++;
		}
		m_AllPhoto.erase(i_Search);
		MessageBox(_T("ɾ���ɹ���"));
		SaveFile();
		ReadFile();
		ShowPhotoList();
		CBrush m_Brush(RGB(100, 100, 100));
		CDC* pDC;
		CRect rect;//��ȡ��ʾͼƬ��Rich�ؼ��ĳߴ�
		CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//��ȡRich�ؼ���ָ��
		pWnd->GetClientRect(&rect);//��ȡRich�ؼ��ĳߴ�
		int nPos_X;
		int nPos_Y;
		int nWidth;
		int nHeight;
		CImage m_Photo;
		if (m_AllPhoto.size() != 0)
		{
			nPos = 0;
			ResizePhoto(m_AllPhoto[0].second, m_Photo, nPos_X, nPos_Y, nWidth, nHeight);
			pDC = m_ShowPhoto.GetDC();
			pDC->SelectObject(m_Brush);
			pDC->Rectangle(rect);
			m_Photo.Draw(m_ShowPhoto.GetDC()->m_hDC, nPos_X, nPos_Y, nWidth, nHeight);

			GetDlgItem(IDC_TURNFIRST)->EnableWindow(FALSE);
			GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
			GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_TURNLAST)->EnableWindow(TRUE);
		}

	}
}
