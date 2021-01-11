
// 电子相册Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "电子相册.h"
#include "电子相册Dlg.h"
#include "afxdialogex.h"

#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C电子相册Dlg 对话框



C电子相册Dlg::C电子相册Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C电子相册Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHOTOLIST, m_PhotoList);
	DDX_Control(pDX, IDC_SHOWPHOTO, m_ShowPhoto);
}

BEGIN_MESSAGE_MAP(C电子相册Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &C电子相册Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C电子相册Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPENPHOTO, &C电子相册Dlg::OnBnClickedOpenphoto)
	ON_BN_CLICKED(IDC_TURNFIRST, &C电子相册Dlg::OnBnClickedTurnfirst)
	ON_BN_CLICKED(IDC_FRONT, &C电子相册Dlg::OnBnClickedFront)
	ON_BN_CLICKED(IDC_NEXT, &C电子相册Dlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_TURNLAST, &C电子相册Dlg::OnBnClickedTurnlast)
	ON_BN_CLICKED(IDC_OUTPUTPHOTO, &C电子相册Dlg::OnBnClickedOutputphoto)
	ON_NOTIFY(NM_CLICK, IDC_PHOTOLIST, &C电子相册Dlg::OnNMClickPhotolist)
	ON_BN_CLICKED(IDC_DELETE, &C电子相册Dlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// C电子相册Dlg 消息处理程序

BOOL C电子相册Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//##################################### 自编写部分 #####################################
	m_PhotoList.InsertColumn(0, _T("文件名"),2,80);
	m_PhotoList.InsertColumn(1, _T("文件路径"), 2, 200);

	ReadFile();
	ShowPhotoList();
	GetDlgItem(IDC_FRONT)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);

	//######################################################################################
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C电子相册Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C电子相册Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C电子相册Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C电子相册Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void C电子相册Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveFile();
	CDialogEx::OnCancel();
}

//========================================== 打开照片 =================================================
void C电子相册Dlg::OnBnClickedOpenphoto()
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

//========================================== 转到首张 =================================================
void C电子相册Dlg::OnBnClickedTurnfirst()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//获取显示图片的Rich控件的尺寸
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
	pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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

//========================================== 上一张 =================================================
void C电子相册Dlg::OnBnClickedFront()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//获取显示图片的Rich控件的尺寸
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
	pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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

//========================================== 下一张 =================================================
void C电子相册Dlg::OnBnClickedNext()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//获取显示图片的Rich控件的尺寸
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
	pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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

//========================================== 转到最后一张 ===========================================
void C电子相册Dlg::OnBnClickedTurnlast()
{
	CBrush m_Brush(RGB(100, 100, 100));
	CDC* pDC;
	CRect rect;//获取显示图片的Rich控件的尺寸
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
	pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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

//========================================== 导出相册 ===============================================
void C电子相册Dlg::OnBnClickedOutputphoto()
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
			CopyFile(i_Search->second.second, sNewPath, FALSE);//复制文件
			i_Search++;
		}
		MessageBox(_T("相册导出成功！"),_T("系统提示"));
	}
}

//========================================== 读取文件 ===============================================
int C电子相册Dlg::ReadFile()
{
	setlocale(LC_CTYPE, "chs");
	int nCount = 0;
	CString sOneline;
	CString sName;
	CString sPath;
	int nBit;
	CStdioFile m_ReadFile;
	m_AllPhoto.clear();//清空保存信息的容器
	m_ReadFile.Open(_T("path.txt"),CFile::modeRead);//打开文件
	while (m_ReadFile.ReadString(sOneline))//读取文件一行
	{
		nBit = sOneline.Find(_T(","));
		sName = sOneline.Left(nBit);
		sOneline.Delete(0, nBit + 1);
		sPath = sOneline;
		m_AllPhoto.insert(std::make_pair(nCount, std::make_pair(sName, sPath)));//保存编号与名字与路径到容器里
		nCount++;//编号+1
	}
	m_ReadFile.Close();
	return 0;
}

//========================================== 保存文件 ===============================================
int C电子相册Dlg::SaveFile()
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

//====================================== 修改照片尺寸来用于显示 =====================================
int C电子相册Dlg::ResizePhoto(CString path, CImage& photo,int& nPos_x,int& nPos_y,int& nWidth,int& nHeight)
{
	CRect rect;//获取显示图片的Rich控件的尺寸
	CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
	pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
	int WIDTH = rect.Width();
	int HEIGHT = rect.Height();
	CImage m_OriPhoto;
	photo.Destroy();
	m_OriPhoto.Load(path);
	if (m_OriPhoto.IsNull())
	{
		MessageBox(_T("未打开文件"));
	}
	nWidth = 0;
	nHeight = 0;

	nWidth = m_OriPhoto.GetWidth();//照片实际尺寸
	nHeight = m_OriPhoto.GetHeight();//照片实际尺寸

	double fX_Rate;//X的比例
	double fY_Rate;//Y的比例

	fX_Rate = (double)nWidth / (double)WIDTH;//求比例
	fY_Rate = (double)nHeight / (double)HEIGHT;//求比例
	

	if (fX_Rate<=1&&fY_Rate<=1)
	{
		//表示图片的尺寸比显示界面小
		//计算位置
		
		nPos_x = WIDTH / 2 - nWidth / 2;
		nPos_y = HEIGHT / 2 - nHeight / 2;
	} 
	else
	{
		if (fX_Rate<=1&&fY_Rate>1)//照片高度越界，根据高度的比例，缩减宽度尺度
		{
			nHeight = HEIGHT;
			nWidth = (double)nWidth / fY_Rate;//计算缩减后的快宽度
			nPos_y = 0;
			nPos_x = WIDTH / 2.0 - nWidth / 2.0;
		} 
		else
		{
			if (fY_Rate <= 1 && fX_Rate>1)//照片宽度越界，根据宽度的比例，缩减高度尺度
			{
				nWidth = WIDTH;
				nHeight = (double)nHeight / fX_Rate;//计算缩减后的高度
				nPos_x = 0;
				nPos_y = HEIGHT / 2 - nHeight / 2;
			} 
			else
			{
				if (fX_Rate>fY_Rate)//尺度双双越界，宽度方向的越界更严重
				{
					nWidth = WIDTH;
					nHeight = (double)nHeight / fX_Rate;
					nPos_x = 0;
					nPos_y = HEIGHT / 2 - nHeight / 2;
				} 
				else
				{
					//高度反向的越界更严重
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
		MessageBox(_T("创建失败"));
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

//======================================= 选择列表中的一个照片 ======================================
void C电子相册Dlg::OnNMClickPhotolist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nSelect;
	nSelect = m_PhotoList.GetSelectionMark();
	if (nSelect!=-1)
	{
		nPos = nSelect;
		CBrush m_Brush(RGB(100, 100, 100));
		CDC* pDC;
		CRect rect;//获取显示图片的Rich控件的尺寸
		CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
		pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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

//========================================= 显示信息 ================================================
int C电子相册Dlg::ShowPhotoList()
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

//========================================== 删除图片 ===============================================
void C电子相册Dlg::OnBnClickedDelete()
{
	int nSelect;
	nSelect = m_PhotoList.GetSelectionMark();
	if (nSelect==-1)
	{
		MessageBox(_T("请在列表中选择一个图片进行删除"),_T("提示"));
	} 
	else
	{
		i_Search = m_AllPhoto.begin();
		for (int i=0;i<nSelect;i++)
		{
			i_Search++;
		}
		m_AllPhoto.erase(i_Search);
		MessageBox(_T("删除成功！"));
		SaveFile();
		ReadFile();
		ShowPhotoList();
		CBrush m_Brush(RGB(100, 100, 100));
		CDC* pDC;
		CRect rect;//获取显示图片的Rich控件的尺寸
		CWnd *pWnd = GetDlgItem(IDC_SHOWPHOTO);//获取Rich控件的指针
		pWnd->GetClientRect(&rect);//获取Rich控件的尺寸
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
