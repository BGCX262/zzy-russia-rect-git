// RussiaRectView.cpp : implementation of the CRussiaRectView class
//

#include "stdafx.h"
#include "RussiaRect.h"

#include "RussiaRectDoc.h"
#include "RussiaRectView.h"

#include "ConnectDlg.h"
#include "UserHelp.h"
#include "GameExitDlg.h"

//音乐播放
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectView

IMPLEMENT_DYNCREATE(CRussiaRectView, CView)

BEGIN_MESSAGE_MAP(CRussiaRectView, CView)
	//{{AFX_MSG_MAP(CRussiaRectView)
	ON_COMMAND(IDM_OnePlayer, OnOnePlayer)
	ON_COMMAND(IDM_TwoPlayers, OnTwoPlayers)
	ON_COMMAND(IDM_Connect, OnConnect)
	ON_COMMAND(IDM_ShowIP, OnShowIP)
	ON_COMMAND(IDM_Request, OnRequest)
	ON_COMMAND(IDM_GameStart, OnGameStart)
	ON_COMMAND(IDM_GamePause, OnGamePause)
	ON_COMMAND(IDM_GameEnd, OnGameEnd)
	ON_COMMAND(IDM_GameExit, OnGameExit)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(IDM_GameStart, OnUpdateGameStart)
	ON_UPDATE_COMMAND_UI(IDM_GamePause, OnUpdateGamePause)
	ON_UPDATE_COMMAND_UI(IDM_GameExit, OnUpdateGameExit)
	ON_UPDATE_COMMAND_UI(IDM_GameEnd, OnUpdateGameEnd)
	ON_COMMAND(IDM_LEVEL_1, OnLevel1)
	ON_COMMAND(IDM_LEVEL_2, OnLevel2)
	ON_COMMAND(IDM_LEVEL_3, OnLevel3)
	ON_COMMAND(IDM_LEVEL_4, OnLevel4)
	ON_COMMAND(IDM_LEVEL_5, OnLevel5)
	ON_COMMAND(IDM_MUSIC_OFF, OnMusicOff)
	ON_COMMAND(IDM_UserHelp, OnUserHelp)
	ON_UPDATE_COMMAND_UI(IDM_OnePlayer, OnUpdateOnePlayer)
	ON_UPDATE_COMMAND_UI(IDM_TwoPlayers, OnUpdateTwoPlayers)
	ON_UPDATE_COMMAND_UI(IDM_Request, OnUpdateRequest)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IP_HOST, OnFieldchangedIpHost)
	ON_UPDATE_COMMAND_UI(IDM_LEVEL_1, OnUpdateLevel1)
	ON_UPDATE_COMMAND_UI(IDM_LEVEL_2, OnUpdateLevel2)
	ON_UPDATE_COMMAND_UI(IDM_LEVEL_3, OnUpdateLevel3)
	ON_UPDATE_COMMAND_UI(IDM_LEVEL_4, OnUpdateLevel4)
	ON_UPDATE_COMMAND_UI(IDM_LEVEL_5, OnUpdateLevel5)
	ON_UPDATE_COMMAND_UI(IDM_MUSIC_OFF, OnUpdateMusicOff)
	ON_UPDATE_COMMAND_UI(IDM_Connect, OnUpdateConnect)
	ON_COMMAND(IDM_GRID, OnGrid)
	ON_UPDATE_COMMAND_UI(IDM_GRID, OnUpdateGrid)
	ON_COMMAND(IDM_NOGRID, OnNogrid)
	ON_UPDATE_COMMAND_UI(IDM_NOGRID, OnUpdateNogrid)
	ON_COMMAND(IDM_ONMUSIC1, OnMusic1)
	ON_COMMAND(IDM_ONMUSIC2, OnMusic2)
	ON_COMMAND(IDM_ONMUSIC3, OnMusic3)
	ON_COMMAND(IDM_ONMUSIC4, OnMusic4)
	ON_COMMAND(IDM_ONMUSIC5, OnMusic5)
	ON_UPDATE_COMMAND_UI(IDM_ONMUSIC1, OnUpdateOnmusic1)
	ON_UPDATE_COMMAND_UI(IDM_ONMUSIC2, OnUpdateOnmusic2)
	ON_UPDATE_COMMAND_UI(IDM_ONMUSIC3, OnUpdateOnmusic3)
	ON_UPDATE_COMMAND_UI(IDM_ONMUSIC4, OnUpdateOnmusic4)
	ON_UPDATE_COMMAND_UI(IDM_ONMUSIC5, OnUpdateOnmusic5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectView construction/destruction

CRussiaRectView::CRussiaRectView()
{
	// TODO: add construction code here
	m_iRow = MAP_ROW;			//地图行数
	m_iCol = MAP_COL;			//地图列数

	m_nWidth = 0;				//整个游戏窗口的宽度
	m_nHeight = 0;
	m_nWidth2 = 110;			//小窗口的大小
	m_nHeight2 = 150;

	m_iStartX = 10;				//左上角X，Y坐标
	m_iStartY = 10;
	m_iStartX2 = m_iStartX;		
	m_iStartY2 = m_iStartY;

	m_iStartPositionX = 0;		//形状生成时在顶部的纵向坐标
	m_iStartPositionY = 4;		//形状生成时在顶部的横向坐标

	m_iLarge = RECT_LENGTH;		//缺省方块大小为m_iLarge个象素
	//m_iBlockStyle = 2;		//第一种样式

	m_bOnePlayer = true;		//true为单人,false为双人模式
	m_bTwoPlayer = false;		//true为单人,false为双人模式

	m_bFistPlay = true;			//第一次开始游戏
	m_bGameReady = true;		//缺省游戏是处于准备好的状态
	m_bGameEnd = true;			//缺省游戏已经结束	
	m_bGamePause = false;		//缺省为不是游戏暂停状态
	m_bMusic = false;			//缺省为没有背景音乐
	m_sMusicName = "";
	m_bDrawGrid = true;			//缺省为画网格线
	
	m_iLevel = 3 ;				//缺省级别为3级	
	m_iLevel2 = 3 ;

	m_bConnectStatus = false;	//联机状态,false为未联机状态,true为联机状态
	m_iConnectStatus = 0;		//连接状态,0为服务器,1为客户机
	m_bConnectReady = false;

	GameInitial();				//初始化

	//19种形状的定义:编号按先下后上,先左后右的次序分别为四个方块编号
	//"1"
	shape[0].next=1;						//-0----------	
	shape[0].X[0]=0;shape[0].Y[0]=0;		//	-+--
	shape[0].X[1]=0;shape[0].Y[1]=-1;		//	-+--
	shape[0].X[2]=0;shape[0].Y[2]=-2;		//	-+--
	shape[0].X[3]=0;shape[0].Y[3]=-3;		//	-+--
	shape[0].color=0;
	//"1"变形1
	shape[1].next=0;						//-1-----------
	shape[1].X[0]=0;shape[1].Y[0]=0;		//	----
	shape[1].X[1]=1;shape[1].Y[1]=0;		//	----
	shape[1].X[2]=2;shape[1].Y[2]=0;		//	----
	shape[1].X[3]=-1;shape[1].Y[3]=0;		//	++++
	shape[1].color=0;
	//"7"
	shape[2].next=3;						//-2-----------
	shape[2].X[0]=0;shape[2].Y[0]=-2;		//	----
	shape[2].X[1]=1;shape[2].Y[1]=-2;		//	-++-
	shape[2].X[2]=1;shape[2].Y[2]=-1;		//	--+-
	shape[2].X[3]=1;shape[2].Y[3]=0;		//	--+-
	shape[2].color=1;
	//"7"变形1
	shape[3].next=4;						//-3-----------
	shape[3].X[0]=0;shape[3].Y[0]=0;		//	----
	shape[3].X[1]=1;shape[3].Y[1]=-1;		//	----
	shape[3].X[2]=2;shape[3].Y[2]=-1;		//	-+++
	shape[3].X[3]=0;shape[3].Y[3]=-1;		//	-+--
	shape[3].color=1;
	//"7"变形2
	shape[4].next=5;						//-4------------
	shape[4].X[0]=0;shape[4].Y[0]=0;		//	----
	shape[4].X[1]=0;shape[4].Y[1]=-1;		//	-+--
	shape[4].X[2]=0;shape[4].Y[2]=-2;		//	-+--
	shape[4].X[3]=1;shape[4].Y[3]=0;		//	-++-
	shape[4].color=1;
	//"7"变形3
	shape[5].next=2;						//-5------------
	shape[5].X[0]=0;shape[5].Y[0]=0;		//	----
	shape[5].X[1]=1;shape[5].Y[1]=0;		//	----
	shape[5].X[2]=2;shape[5].Y[2]=0;		//	---+
	shape[5].X[3]=2;shape[5].Y[3]=-1;		//	-+++
	shape[5].color=1;
	//反"7"
	shape[6].next=7;						//-6------------
	shape[6].X[0]=0;shape[6].Y[0]=0;		//	----
	shape[6].X[1]=0;shape[6].Y[1]=-1;		//	-++-
	shape[6].X[2]=0;shape[6].Y[2]=-2;		//	-+--
	shape[6].X[3]=1;shape[6].Y[3]=-2;		//	-+--
	shape[6].color=2;
	//反"7"变形1
	shape[7].next=8;						//-7------------
	shape[7].X[0]=0;shape[7].Y[0]=0;		//	----
	shape[7].X[1]=0;shape[7].Y[1]=-1;		//	----
	shape[7].X[2]=1;shape[7].Y[2]=0;		//	-+--
	shape[7].X[3]=2;shape[7].Y[3]=0;		//	-+++
	shape[7].color=2;
	//反"7"变形2
	shape[8].next=9;						//-8------------
	shape[8].X[0]=0;shape[8].Y[0]=0;		//	----
	shape[8].X[1]=1;shape[8].Y[1]=0;		//	--+-
	shape[8].X[2]=1;shape[8].Y[2]=-2;		//	--+-
	shape[8].X[3]=1;shape[8].Y[3]=-1;		//	-++-
	shape[8].color=2;
	//反"7"变形3
	shape[9].next=6;						//-9------------
	shape[9].X[0]=0;shape[9].Y[0]=-1;		//	----
	shape[9].X[1]=1;shape[9].Y[1]=-1;		//	----
	shape[9].X[2]=2;shape[9].Y[2]=-1;		//	-+++
	shape[9].X[3]=2;shape[9].Y[3]=0;		//	---+
	shape[9].color=2;
	//"T"
	shape[10].next=11;						//-10------------
	shape[10].X[0]=0;shape[10].Y[0]=0;		//	----
	shape[10].X[1]=0;shape[10].Y[1]=-1;		//	-+--
	shape[10].X[2]=0;shape[10].Y[2]=-2;		//	-++-
	shape[10].X[3]=1;shape[10].Y[3]=-1;		//	-+--
	shape[10].color=3;
	//"T"变形1
	shape[11].next=12;						//-11------------
	shape[11].X[0]=0;shape[11].Y[0]=0;		//	----
	shape[11].X[1]=1;shape[11].Y[1]=0;		//	----
	shape[11].X[2]=2;shape[11].Y[2]=0;		//	--+-
	shape[11].X[3]=1;shape[11].Y[3]=-1;		//	-+++
	shape[11].color=3;
	//"T"变形2
	shape[12].next=13;						//-12------------
	shape[12].X[0]=1;shape[12].Y[0]=0;		//	----
	shape[12].X[1]=1;shape[12].Y[1]=-1;		//	--+-
	shape[12].X[2]=1;shape[12].Y[2]=-2;		//	-++-
	shape[12].X[3]=0;shape[12].Y[3]=-1;		//	--+-
	shape[12].color=3;
	//"T"变形3
	shape[13].next=10;						//-13------------
	shape[13].X[0]=0;shape[13].Y[0]=-1;		//	----
	shape[13].X[1]=1;shape[13].Y[1]=0;		//	----
	shape[13].X[2]=2;shape[13].Y[2]=-1;		//	-+++
	shape[13].X[3]=1;shape[13].Y[3]=-1;		//	--+-
	shape[13].color=3;
	//S
	shape[14].next=15;						//-14------------
	shape[14].X[0]=0;shape[14].Y[0]=0;		//	----
	shape[14].X[1]=1;shape[14].Y[1]=0;		//	----
	shape[14].X[2]=1;shape[14].Y[2]=-1;		//	--++
	shape[14].X[3]=2;shape[14].Y[3]=-1;		//	-++-
	shape[14].color=4;
	//S变形1
	shape[15].next=14;						//-15------------
	shape[15].X[0]=0;shape[15].Y[0]=-1;		//	----
	shape[15].X[1]=0;shape[15].Y[1]=-2;		//	-+--	
	shape[15].X[2]=1;shape[15].Y[2]=-1;		//	-++-
	shape[15].X[3]=1;shape[15].Y[3]=0;		//	--+-	
	shape[15].color=4;
	//Z
	shape[16].next=17;						//-16------------
	shape[16].X[0]=0;shape[16].Y[0]=-1;		//	----
	shape[16].X[1]=1;shape[16].Y[1]=-1;		//	----
	shape[16].X[2]=1;shape[16].Y[2]=0;		//	-++-	
	shape[16].X[3]=2;shape[16].Y[3]=0;		//	--++
	shape[16].color=5;
	//Z变形1
	shape[17].next=16;						//-17-------------
	shape[17].X[0]=0;shape[17].Y[0]=0;		//	----
	shape[17].X[1]=0;shape[17].Y[1]=-1;		//	--+-
	shape[17].X[2]=1;shape[17].Y[2]=-1;		//	-++-
	shape[17].X[3]=1;shape[17].Y[3]=-2;		//	-+--
	shape[17].color=5;
	//方块
	shape[18].next=18;						//-18------------
	shape[18].X[0]=0;shape[18].Y[0]=0;		//	----
	shape[18].X[1]=1;shape[18].Y[1]=0;		//	----
	shape[18].X[2]=0;shape[18].Y[2]=-1;		//	-++-
	shape[18].X[3]=1;shape[18].Y[3]=-1;		//	-++-
	shape[18].color=6;	

}

//////////////////////////////////////
//~CRussiaRectView()
//析构函数
CRussiaRectView::~CRussiaRectView()
{
}

BOOL CRussiaRectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
//void OnDraw(CDC* pDC)
//启动作图函数
void CRussiaRectView::OnDraw(CDC* pDC)
{
	CRussiaRectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	DcEnvInitial();
	DrawGame(&m_memDC);  //在内存位图的游戏区域绘制

	pDC->BitBlt(0,0,m_nWidth,m_nHeight,&m_memDC,0,0,SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectView diagnostics
#ifdef _DEBUG
void CRussiaRectView::AssertValid() const
{
	CView::AssertValid();
}

void CRussiaRectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRussiaRectDoc* CRussiaRectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRussiaRectDoc)));
	return (CRussiaRectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRussiaRectView message handlers
//绘制设备环境的初始化
void CRussiaRectView::DcEnvInitial()
{
	if(m_bFistPlay)
	{
		m_bFistPlay = false;
		//用默认的参数，获取当前屏幕设备环境
		CDC *pWindowDC = GetDC();

		//1.用于映射屏幕的内存设备环境
		//获取游戏窗口的大小用于下面设置内存位图的尺寸
		CRect windowRect;
		GetClientRect(&windowRect);
		m_nWidth = windowRect.Width();
		m_nHeight = windowRect.Height();
		
		m_memDC.CreateCompatibleDC(pWindowDC);		//内存设备环境与屏幕设备环境关联（兼容）
		m_memBmp.CreateCompatibleBitmap(pWindowDC,m_nWidth,m_nHeight);	//内存位图与与屏幕关联(兼容),大小为游戏窗口的尺寸
		m_memDC.SelectObject(&m_memBmp);	//内存设备环境与内存位图关联，以便通过m_memDC在内存位图上作画

		//2.存储方块位图的内存资源
		m_memRectDC.CreateCompatibleDC(pWindowDC);	//内存设备环境与屏幕设备环境关联（兼容）
		m_hMemRectBmp=(HBITMAP)LoadImage(NULL,"rect.bmp",IMAGE_BITMAP,175,25,LR_LOADFROMFILE);	//相当于将外部位图rect.bmp动态载入m_hMemRectBmp中
		SelectObject(m_memRectDC.m_hDC, m_hMemRectBmp);		//内存设备环境与内存位图关联，以便通过m_memDC在内存位图上作画
		
		m_pBlackPen  = new CPen(PS_SOLID,1,BACKGROUND);	//黑色的画笔	
		m_pGrayBrush  = new CBrush(GRAY);				//画刷
		m_pBlackBrush  = new CBrush(BLACK);				//画刷
		m_pBackGroundBrush  = new CBrush(BACKGROUND);
	}
}

//////////////////////////////////
//void DCEnvClear()
//设备环境清理
void CRussiaRectView::DCEnvClear()
{
	//设备环境
	m_memDC.DeleteDC();
	m_memRectDC.DeleteDC();
	//位图资源
	DeleteObject(m_memBmp);
	DeleteObject(m_hMemRectBmp);

	delete(m_pBlackPen);
	delete(m_pBlackBrush);
	delete(m_pGrayBrush);
	delete(m_pBackGroundBrush);
}

//////////////////////////////////////////
//void DrawGame(CDC *pDC)
//绘制图形
void CRussiaRectView::DrawGame(CDC *pDC)
{
	//选用背景色画刷，绘制整个游戏所在窗口的背景
	pDC -> SelectObject(m_pBackGroundBrush);
	CRect rect;
	GetClientRect(&rect);
	pDC -> Rectangle(rect);

	//选用黑色画刷，绘制游戏区域的背景
	pDC -> SelectObject(m_pBlackBrush);		//选择黑色笔刷
	//画左右两块游戏区
	pDC -> Rectangle(m_iStartX,m_iStartY, m_iStartX+GAME_WIDTH, m_iStartY+GAME_HEIGHT);
	pDC -> Rectangle(m_nWidth-m_iStartX-GAME_WIDTH,m_iStartY, m_nWidth-m_iStartX, m_iStartY+GAME_HEIGHT);
	//画中间两块显示下一个方块的区域
	pDC -> Rectangle(m_nWidth/2-m_nWidth2,m_iStartY+10, m_nWidth/2-2, m_iStartY+10+m_nHeight2);
	pDC -> Rectangle(m_nWidth/2+2,m_iStartY+10, m_nWidth/2+m_nWidth2, m_iStartY+10+m_nHeight2);
	//画中间下部的文字提示区
	pDC -> Rectangle(m_nWidth/2-100,m_iStartY+m_nHeight2+50,m_nWidth/2+100, m_iStartY+m_nHeight2+250);
	
	//画网格线
	if(m_bDrawGrid)
	{
		pDC->SelectObject(m_pBlackPen);
		for (int i=0;i<m_iRow;i++)		//画横线
		{
			//左边的区域	
			pDC->MoveTo(m_iStartX, m_iStartY + i*m_iLarge);
			pDC->LineTo(m_iStartX+GAME_WIDTH, m_iStartY +i*m_iLarge);
			//右边的区域
			pDC->MoveTo(m_nWidth-m_iStartX-GAME_WIDTH, m_iStartY + i*m_iLarge);
			pDC->LineTo(m_nWidth-m_iStartX, m_iStartY+i*m_iLarge);
		}		
		for (i=0;i<m_iCol;i++)		//画竖线
		{
			//左边的区域
			pDC->MoveTo(m_iStartX+i*m_iLarge, m_iStartY);
			pDC->LineTo(m_iStartX+i*m_iLarge, m_iStartY+GAME_HEIGHT);
			//右边的区域
			pDC->MoveTo(m_nWidth-m_iStartX-i*m_iLarge, m_iStartY);
			pDC->LineTo(m_nWidth-m_iStartX-i*m_iLarge, m_iStartY+GAME_HEIGHT);
		}
	}

	int x,y,nW,nH;
	//小方块的绘制
	for (int i=0 ; i<m_iRow ; i++)
		for (int j=0 ; j<m_iCol ; j++)
		{
			//左边区域
			if (gamestatusmap[i][j].status == 1)
			{
				//在游戏区域中状态为被占用状态的区域绘制小方块
				x = m_iStartX+j*m_iLarge ;
				y = m_iStartY+(i-1)*m_iLarge ;
				nW = m_iLarge ;
				nH = m_iLarge ;
				pDC->BitBlt(x,y,nW,nH,&m_memRectDC,gamestatusmap[i][j].color*m_iLarge,0,SRCCOPY);
			}
			//双人模式下
			if(!m_bOnePlayer)
			{
				//右边区域
				if(gamestatusmap2[i][j].status == 1)
				{
					x = m_nWidth-m_iStartX-GAME_WIDTH +j*m_iLarge;
					y = m_iStartY+(i-1)*m_iLarge ;
					nW = m_iLarge ;
					nH = m_iLarge ;
					pDC->BitBlt(x,y,nW,nH,&m_memRectDC,gamestatusmap2[i][j].color*m_iLarge,0,SRCCOPY);
				}
			}  
		}

	//显示游戏区域及游戏级别的汉字描述
	pDC -> SetBkColor(BLACK);
	pDC -> SetTextColor(WHITE);
	pDC -> TextOut(m_nWidth/2-m_nWidth2+10, m_iStartY+20, "下一个方块:");
	pDC -> TextOut(m_nWidth/2+2+10, m_iStartY+20, "下一个方块:");
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30, "游戏级别");
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30+40,"累积高度");	
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30+80, "消去层数");				
	pDC -> TextOut(m_nWidth/2-100+75, m_iStartY+m_nHeight2+50+30+120,"得    分");
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(RED);
		
		//游戏级别
		CString strLevel;	
		strLevel.Format("%d",m_iLevel);
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30, strLevel);
		if(!m_bOnePlayer)
		{
			CString strLevel2;	
			strLevel2.Format("%d",m_iLevel2);
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30, strLevel2);
		}

		//累积高度
		CString strHeight;	
		strHeight.Format("%d",m_iRectHeight);	
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30+40, strHeight);
		if(!m_bOnePlayer)
		{
			CString strHeight2;	
			strHeight2.Format("%d",m_iRectHeight2);	
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30+40, strHeight2);
		}
		
		//消去层数
		CString strRow;	
		strRow.Format("%d",m_iTotalRow);	
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30+80, strRow);
		if(!m_bOnePlayer)
		{
			CString strRow2;	
			strRow2.Format("%d",m_iTotalRow2);
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30+80, strRow2);
		}
		
		//得分
		CString strScore;	
		strScore.Format("%d",m_iScore);		
		pDC -> TextOut(m_nWidth/2-100+25, m_iStartY+m_nHeight2+50+30+120,strScore);
		if(!m_bOnePlayer)
		{
			CString strScore2;	
			strScore2.Format("%d",m_iScore2);	
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30+120,strScore2);
		} 
	}

	//画下一次将要出现的方块，用于提示用户
	if (!m_bGameEnd)
	{
		int x1,y1,nW1,nH1;		
		for (int k=0;k<4;k++)
		{
			x1 = m_nWidth/2-m_nWidth2+30+(shape[m_iNextShape].X[k])*m_iLarge;
			y1 = m_iStartY+20+70+(shape[m_iNextShape].Y[k]+1) *m_iLarge ;
			nW1 = m_iLarge ;
			nH1 = m_iLarge ;
			pDC->BitBlt(x1,y1,nW1,nH1,&m_memRectDC,shape[m_iNextShape].color*m_iLarge,0,SRCCOPY);
		}

		//非单人模式下,绘制右边的下一个图像
		if(!m_bOnePlayer)
		{
			int x2,y2,nW2,nH2;		
			for (int k2=0;k2<4;k2++)
			{
				x2 = m_nWidth/2+30+(shape[m_iNextShape2].X[k2])*m_iLarge;
				y2 = m_iStartY+20+70+(shape[m_iNextShape2].Y[k2]+1) *m_iLarge ;
				nW2 = m_iLarge ;
				nH2 = m_iLarge ;
				pDC->BitBlt(x2,y2,nW2,nH2,&m_memRectDC,shape[m_iNextShape2].color*m_iLarge,0,SRCCOPY);
			}
		}
	}	
}

////////////////////////////////
//void OnOnePlayer()
//选择单人模式
void CRussiaRectView::OnOnePlayer() 
{
	// TODO: Add your command handler code here
	
	m_bOnePlayer = true;
	m_bTwoPlayer = false;

	m_bConnectStatus = false;
	//m_bGameEnd = true;
}


//////////////////////////////////////
//void OnTwoPlayers() 
//选择双人模式
void CRussiaRectView::OnTwoPlayers() 
{
	// TODO: Add your command handler code here
	m_bTwoPlayer = true;
	m_bOnePlayer = false;	
	m_bConnectStatus = false;
	//m_bGameEnd = true;
}

////////////////////////////////
//void OnConnect()
//网络连接
void CRussiaRectView::OnConnect() 
{
	// TODO: Add your command handler code here
	//当联机
	if(!m_bConnectStatus && m_bGameEnd)
	{
		CConnectDlg dlg;
		DWORD dwIP;
		
		int command = dlg.DoModal();					//产生对话框
		dlg.m_iConnectStatus = m_iConnectStatus;		//联机状态的选择

		if(IDOK == command)								//确认联机
		{
			//m_bGameEnd = false;
			m_bConnectStatus = true;					//联机开始
			m_iConnectStatus = dlg.m_iConnectStatus;	//保存联机状态
			//做客户端
			if(m_iConnectStatus == 2)
			{
				//已经开始
				//if(m_bConnectReady)m_bGameEnd = false;
				((CIPAddressCtrl*)GetDlgItem(IDC_IP_HOST))->GetAddress(dwIP);
			}
			//做服务器
			else if(m_iConnectStatus == 1)
			{
				//if(m_bConnectReady)m_bGameEnd = true;
			}
		}
		else if(IDCANCEL == command)
		{
			m_bGameEnd = true;
			m_bConnectStatus = false;					//取消选择
		}  
	}
	else
	{
		m_bConnectStatus = false;
	}
}

///////////////////////////////////////
//void OnShowIP() 
//显示本机的IP
void CRussiaRectView::OnShowIP() 
{
	// TODO: Add your command handler code here
	char szhostname[128];
	CString str;
	
	if(gethostname(szhostname,128) == 0)
	{
		struct hostent * phost;
		phost = gethostbyname(szhostname);

		int h_length = 4;
		for(int i=0,j=0;j<h_length;j++)
		{
			CString addr;
			if(j>0) str+=".";
			addr.Format ("%u",(unsigned int)((unsigned char *)phost->h_addr_list[i])[j]);
			str += addr;
		}
	}	
	MessageBox(str,"本机IP");
}


//DEL void CRussiaRectView::OnDoubleclickedOk() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }

////////////////////////////////
//void OnRequest() 
//请求开战
void CRussiaRectView::OnRequest() 
{
	// TODO: Add your command handler code here
	m_bGameEnd = true;
	//在联机模式下
	if(m_bConnectStatus == true)
	{
		//////////////////////
		//TO ADD:关闭网络游戏模式
		m_bConnectStatus = false;
	}
	//在单机模式下
	else
	{
		m_bConnectStatus =true;
		///////////////////////////
		//TO ADD: 启动网络游戏模式
		//...
	}
}

//////////////////////////////////////
//void OnGameStart()
//游戏开始
void CRussiaRectView::OnGameStart() 
{
	// TODO: Add your command handler code here
	//如果不是游戏暂停状态，则必须作些初始工作
	if (!m_bGamePause)  
	{
		//将游戏结束的标志设为false
		m_bGameEnd = false;	
		//进行一些初始化的工作
		GameInitial();
		//
		Invalidate(false);
		//双人模式
		if(!m_bOnePlayer)
		{
			SetTimer(2,1600-250*m_iLevel2,NULL);	
		}
	}
	m_bGamePause = false;
	SetTimer(1,1600-250*m_iLevel,NULL);		//设置计时器
	sndPlaySound(".\\kaishi.wav",SND_ASYNC);
}

///////////////////////////////////////
//void OnGamePause() 
//游戏暂停
void CRussiaRectView::OnGamePause() 
{
	// TODO: Add your command handler code here
	if(!m_bGamePause)
	{
		m_bGamePause = true;
		m_bGameEnd = false;
		KillTimer(1);
		if(!m_bOnePlayer)KillTimer(2);
	}
	else
	{
		m_bGamePause = false;
	}
}

////////////////////////////////////////
//void OnGameEnd() 
//游戏结束
void CRussiaRectView::OnGameEnd() 
{
	// TODO: Add your command handler code here
	m_bGameEnd = true;			//游戏结束
	m_bConnectStatus = false;	//断开网络
	
	//游戏状态地图清零
	for (int i=0;i<m_iRow;i++)
		for (int j=0;j<m_iCol;j++)
		{
			gamestatusmap[i][j].status=0;
			if(!m_bOnePlayer)gamestatusmap2[i][j].status=0;
		}

	//更新整个游戏区域显示图
	CRect rect(0,0,m_nWidth,m_nHeight);
	InvalidateRect(&rect);

	m_bGamePause = false;;  //清除游戏暂停状态

	KillTimer(1);	
	if(!m_bOnePlayer)KillTimer(2);
}

///////////////////////////////////////
//void OnGameExit() 
//退出游戏
void CRussiaRectView::OnGameExit() 
{
	// TODO: Add your command handler code here
	////清理内存设备环境，释放资源
	//DCEnvClear();

	CGameExitDlg dlg;
	dlg.DoModal();
}

/////////////////////////////////////
//
//
void CRussiaRectView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case 'A':					//A 左移一格
		RectArrow(LEFT);
		break;
	case 'D':					//D	右移一格
		RectArrow(RIGHT);
		break;
	case 'W':					//W	方块变形
		RectChange();
		break;
	case 'S':					//S	下移一格
		RectArrow(DOWN);
		break;
	case VK_SPACE:				//SPACE 直接下落到底部
		while(!IsBottom())
			RectDown();
		break;
	//双人模式
	case VK_LEFT:				//LEFT 左移一格
		if(!m_bOnePlayer) 
			RectArrow2(LEFT2);
		break;
	case VK_RIGHT:				//RIGHT	右移一格	
		if(!m_bOnePlayer) 
			RectArrow2(RIGHT2);
		break;
	case VK_UP:					//UP 方块变形
		if(!m_bOnePlayer) 
			RectChange2();
		break;
	case VK_DOWN:				//DOWN 下移一格
		if(!m_bOnePlayer) 
			RectArrow2(DOWN2);
		break;
	case VK_NUMPAD0:			//Number 0 直接下落到底部
		if(!m_bOnePlayer)
			while(!IsBottom2())
				RectDown2();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////
//void RectArrow(int m_Type)
//根据键盘输入控制方块的动作
void CRussiaRectView::RectArrow(int m_Type)
{
	switch(m_Type)
	{
	case LEFT:
		if(!IsLeftLimit() && !m_isBottom)	//若左边没有限制 且没有到达底部
		{
			ShapeInMap(m_iCurrentShape,0);	//将原形状清除
			//InvalidateCurrent();

			position.y--;					//左移一个单位

			ShapeInMap(m_iCurrentShape,1);	//显示左移后的形状	
			InvalidateCurrent();	
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
			
		}
		break;

	case RIGHT:
		if(!IsRightLimit() && !m_isBottom)	//若左边没有限制 且没有到达底部
		{
			ShapeInMap(m_iCurrentShape,0);	//将原形状清除
			//InvalidateCurrent();

			position.y++;					//左移一个单位

			ShapeInMap(m_iCurrentShape,1);	//显示左移后的形状	
			InvalidateCurrent();	
			
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
		}
		break;

	case DOWN:
		RectDown();
		break;
	}
}

//////////////////////////////////////////
//void RectArrow2(int m_Type)
//右边根据键盘输入控制方块的动作
void CRussiaRectView::RectArrow2(int m_Type)
{
	switch(m_Type)
	{
	case LEFT2:
		if(!IsLeftLimit2() && !m_isBottom2)	//若左边没有限制 且没有到达底部
		{
			ShapeInMap2(m_iCurrentShape2,0);	//将原形状清除
			//InvalidateCurrent2();

			position2.y--;					//左移一个单位

			ShapeInMap2(m_iCurrentShape2,1);	//显示左移后的形状	
			InvalidateCurrent2();
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
		}
		break;
	case RIGHT2:
		if(!IsRightLimit2() && !m_isBottom2)	//若左边没有限制 且没有到达底部
		{
			ShapeInMap2(m_iCurrentShape2,0);	//将原形状清除
			//InvalidateCurrent2();

			position2.y++;					//左移一个单位

			ShapeInMap2(m_iCurrentShape2,1);	//显示左移后的形状	
			InvalidateCurrent2();
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
		}
		break;

	case DOWN2:
		RectDown2();
		break;
	}
}

//////////////////////////////
//void RectDown()
//左边方块下移函数
void CRussiaRectView::RectDown()
{
	//查看是否到达底部
	m_isBottom = IsBottom();
	//1.若没有到达底部,便可以下移
	if (!m_isBottom)
	{
		//m_isBottom = false;
		//1.1 清除以前的方块
		ShapeInMap(m_iCurrentShape,0);
		//1.2 方块下落
		position.x++;
		//1.3 更新新的地图数组
		ShapeInMap(m_iCurrentShape,1);
		//1.4 显示新的图像
		InvalidateCurrent();
	}
}

//////////////////////////////
//void RectDown2()
//右边方块下移函数
void CRussiaRectView::RectDown2()
{	
	//查看是否到达底部
	m_isBottom2 = IsBottom2();
	//1.若没有到达底部,便可以下移
	if (!m_isBottom2)
	{
		//1.1 清除以前的方块
		ShapeInMap2(m_iCurrentShape2,0);
		//1.2 方块下落
		position2.x++;
		//1.3 更新新的地图数组
		ShapeInMap2(m_iCurrentShape2,1);
		//1.4 显示新的图像
		InvalidateCurrent2();
	}
}

///////////////////////////////////
//bool IsLeftLimit()
//左边判断是否有左移的限制,true说明左边被限制,false说明左边没有被限制
bool CRussiaRectView::IsLeftLimit()
{
	//1. 暂时清除地图中的形状
	ShapeInMap(m_iCurrentShape,0);		
	//2. 判断方块左移一个单位后,是否有位置已被占据
	for(int i=0 ; i<4 ; i++)
	{	//2.1 若超出左边界或左边的区域被占有
		if(position.y+shape[m_iCurrentShape].X[i] <= 0 || gamestatusmap[position.x+shape[m_iCurrentShape].Y[i]][position.y-1+shape[m_iCurrentShape].X[i]].status == 1)
		{
			//2.1.1 恢复暂时清除地图中的形状
			ShapeInMap(m_iCurrentShape,1);
			//2.1.2 返回左边被限制
			return true;					
		}
	}
	//3. 若没有上面的情况发生,则恢复暂时清除地图中的形状
	ShapeInMap(m_iCurrentShape,1);
	//4. 返回没有被限制
	return false;					
}

///////////////////////////////////
//bool IsLeftLimit2()
//右边判断是否有左移的限制,true说明左边被限制,false说明左边没有被限制
bool CRussiaRectView::IsLeftLimit2()
{
	//1. 暂时清除地图中的形状
	ShapeInMap2(m_iCurrentShape2,0);		
	//2. 判断方块左移一个单位后,是否有位置已被占据
	for(int i=0 ; i<4 ; i++)
	{	//2.1 若超出左边界或左边的区域被占有
		if(position2.y+shape[m_iCurrentShape2].X[i] <= 0 || gamestatusmap2[position2.x+shape[m_iCurrentShape2].Y[i]][position2.y-1+shape[m_iCurrentShape2].X[i]].status == 1)
		{
			//2.1.1 恢复暂时清除地图中的形状
			ShapeInMap2(m_iCurrentShape2,1);
			//2.1.2 返回左边被限制
			return true;					
		}
	}
	//3. 若没有上面的情况发生,则恢复暂时清除地图中的形状
	ShapeInMap2(m_iCurrentShape2,1);
	//4. 返回没有被限制
	return false;					
}

/////////////////////////////////////
//bool IsRightLimit()
//
bool CRussiaRectView::IsRightLimit()
{
	//1. 暂时清除地图中的形状
	ShapeInMap(m_iCurrentShape,0);		
	//2. 判断方块右移一个单位后,是否有位置已被占据
	for(int i=0 ; i<4 ; i++)
	{	//2.1 若超出右边界或右移后的的区域被占有
		if(position.y+shape[m_iCurrentShape].X[i] >= 9 || gamestatusmap[position.x+shape[m_iCurrentShape].Y[i]][position.y+1+shape[m_iCurrentShape].X[i]].status == 1)
		{
			//2.2 恢复暂时清除地图中的形状
			ShapeInMap(m_iCurrentShape,1);
			//2.3 返回右边被限制
			return true;	
		}
	}
	//3. 恢复暂时清除地图中的形状
	ShapeInMap(m_iCurrentShape,1);	
	//4. 返回没有被限制
	return false;	
}

/////////////////////////////////////
//bool IsRightLimit2()
//
bool CRussiaRectView::IsRightLimit2()
{
	//1. 暂时清除地图中的形状
	ShapeInMap2(m_iCurrentShape2,0);		
	//2. 判断方块右移一个单位后,是否有位置已被占据
	for(int i=0 ; i<4 ; i++)
	{	//2.1 若超出右边界或右移后的的区域被占有
		if(position2.y+shape[m_iCurrentShape2].X[i] >= 9 || gamestatusmap2[position2.x+shape[m_iCurrentShape2].Y[i]][position2.y+1+shape[m_iCurrentShape2].X[i]].status == 1)
		{
			//2.2 恢复暂时清除地图中的形状
			ShapeInMap2(m_iCurrentShape2,1);
			//2.3 返回右边被限制
			return true;	
		}
	}
	//3. 恢复暂时清除地图中的形状
	ShapeInMap2(m_iCurrentShape2,1);	
	//4. 返回没有被限制
	return false;	
}

////////////////////////////////////
//void RectChange()
//方块变形函数,根据当前的方块变换出顺时针旋转后的方块
void CRussiaRectView::RectChange()
{
	if(!m_isBottom)
	{
		//1. 清除原来的位图映像
		ShapeInMap(m_iCurrentShape,0);	
		//2. 暂存变形后的索引号
		int m_itempNextShape = shape[m_iCurrentShape].next;
		//3. 若变形后,判断是否有冲突 
		for(int i=0 ; i<4 ; i++)
		{	//3.1 变形后有方块的区域被占有
			if(gamestatusmap[position.x+shape[m_itempNextShape].Y[i]][position.y+shape[m_itempNextShape].X[i]].status != 0)
			{
				ShapeInMap(m_iCurrentShape,1);	//恢复暂时清除地图中的形状
				return;							//返回
			}
			//3.2 变形后越界(左右下)
			if(position.y+shape[m_itempNextShape].X[i] < 0 || position.y+shape[m_itempNextShape].X[i] > 9 || position.x+shape[m_itempNextShape].Y[i] > 15)
			{
				//恢复暂时清除地图中的形状
				ShapeInMap(m_iCurrentShape,1);
				//返回
				return ;					
			}
		}
		//4. 若变形后,没有冲突,将当前形状变形为下一个形状
		m_iCurrentShape = shape[m_iCurrentShape].next;
		//5. 更新变形后的位图映像
		ShapeInMap(m_iCurrentShape,1);
		//6. 显示变形后的位图
		InvalidateCurrent();
		sndPlaySound(".\\bianxin.wav",SND_ASYNC);
	}
}

////////////////////////////////////
//void RectChange2()
//方块变形函数,根据当前的方块变换出顺时针旋转后的方块
void CRussiaRectView::RectChange2()
{
	if(!m_isBottom2)
	{
		//1. 清除原来的位图映像
		ShapeInMap2(m_iCurrentShape2,0);	
		//2. 暂存变形后的索引号
		int m_itempNextShape2 = shape[m_iCurrentShape2].next;
		//3. 若变形后,判断是否有冲突 
		for(int i=0 ; i<4 ; i++)
		{	//3.1 变形后有方块的区域被占有
			if(gamestatusmap2[position2.x+shape[m_itempNextShape2].Y[i]][position2.y+shape[m_itempNextShape2].X[i]].status != 0)
			{
				ShapeInMap2(m_iCurrentShape2,1);	//恢复暂时清除地图中的形状
				return;							//返回
			}
			//3.2 变形后越界(左右下)
			if(position2.y+shape[m_itempNextShape2].X[i] < 0 || position2.y+shape[m_itempNextShape2].X[i] > 9 || position2.x+shape[m_itempNextShape2].Y[i] > 15)
			{
				//恢复暂时清除地图中的形状
				ShapeInMap2(m_iCurrentShape2,1);
				//返回
				return ;					
			}
		}
		//4. 若变形后,没有冲突,将当前形状变形为下一个形状
		m_iCurrentShape2 = shape[m_iCurrentShape2].next;
		//5. 更新变形后的位图映像
		ShapeInMap2(m_iCurrentShape2,1);
		//6. 显示变形后的位图
		InvalidateCurrent2();
		sndPlaySound(".\\bianxin.wav",SND_ASYNC);
	}
}

//////////////////////////////////////////
//int Random(int MaxNumber)
//产生随机数,MaxNumber为模,chaos为扰动因子,防止连续调用该函数时,因时间因子的差别太小而总产生相同结果的情况
int CRussiaRectView::Random(int MaxNumber ,int chaos)
{
	srand( (unsigned)time( NULL ) );	//布下随机种子
	int random = (rand()+chaos) % MaxNumber;	//产生随机数
	
	return random;
}

///////////////////////////////////////////
//void OnTimer(UINT nIDEvent)
//计时器函数,为程序中所有的时钟动作提供驱动
void CRussiaRectView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//1. 如果原来的方块已到底或游戏刚开始
	if (m_isBottom)
	{
		//1 将当前的方块位置保存到地图数组中
		ShapeInMap(m_iCurrentShape,1);

		//2 获得减少的行数和分数
		m_iTotalRow += GetDecreaseRow();
		//2.3 得到此时方块累积的高度
		m_iRectHeight = GetHeight();
		//3. 将当前方块用下一个方块代替
		m_iCurrentShape = m_iNextShape;
		//4. 随机得到下一次的方块样式
		m_iNextShape = Random(19);  
		//5. 初始化当前新方块的初始化位置
		position.x = m_iStartPositionX;
		position.y = m_iStartPositionY;	
		//2.6 显示该图像
		InvalidateCurrent();

		//6. 若到达底部
		if(IsBottom())
		{
			//2.4 若方块的最高累积高度超过了窗口的顶部
			if(m_iRectHeight >= m_iRow -1)
			{
				//2.5 游戏结束
				GameOver();
			} 
		}
		
		RectDown();
	}
	//2.否则没有到达底部
	else  
	{
		//2.1方块下降
		RectDown();
	}
	//右边:如果原来的方块已到底或游戏刚开始，则掉下一个新的方块
	if(!m_bOnePlayer)
	{
		//1. 如果原来的方块已到底或游戏刚开始
		if (m_isBottom2)
		{
			//1 将当前的方块位置保存到地图数组中
			ShapeInMap2(m_iCurrentShape2,1);

			//2 获得减少的行数和分数
			m_iTotalRow2 += GetDecreaseRow2();
			//2.3 得到此时方块累积的高度
			m_iRectHeight2 = GetHeight2();
			//3. 将当前方块用下一个方块代替
			m_iCurrentShape2 = m_iNextShape2;
			//4. 随机得到下一次的方块样式
			m_iNextShape2 = Random(19);  
			//5. 初始化当前新方块的初始化位置
			position2.x = m_iStartPositionX;
			position2.y = m_iStartPositionY;	
			//2.6 显示该图像
			InvalidateCurrent2();

			//6. 若到达底部
			if(IsBottom2())
			{
				//2.4 若方块的最高累积高度超过了窗口的顶部
				if(m_iRectHeight2 >= m_iRow -1)
				{
					//2.5 游戏结束
					GameOver();
				} 
			}			
			RectDown2();
		}
		//2. 否则,当前方块下降
		else  
		{
			RectDown2();
		}
	}

	CView::OnTimer(nIDEvent);
}

///////////////////////////////
//IsBottom()
//判断是否到达底部
bool CRussiaRectView::IsBottom()
{
	//1.若到游戏区底部,则停止移动,置到底的标志为true,并返回
	if(position.x >= m_iRow-1)
	{
		m_isBottom = true;
		position.x = m_iRow-1;

		sndPlaySound(".\\zhuangdi.wav",SND_ASYNC);
		return m_isBottom;
	}
	//2.否则没有到达游戏区底部,则进行下降碰撞分析
	//2.1 清除原形状在地图中的映像
	ShapeInMap(m_iCurrentShape,0);
	//2.2 判断形状下移一个位置后,是否有方块和所处的位置已被占有
	for(int ii=0 ; ii < 4 ; ii++)
	{
		//2.3 如果有任何一个被占有,则说明下方有方块阻挡
		if(gamestatusmap[position.x+1+shape[m_iCurrentShape].Y[ii]][position.y+shape[m_iCurrentShape].X[ii]].status == 1)
		{
			//2.4 置到底的标志为true
			m_isBottom = true;				
			//2.5 修改恢复原形状在地图中的映像
			ShapeInMap(m_iCurrentShape,1);
			//2.6 发出碰撞的音效
			sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
			//2.7 返回已到底部的标志
			return m_isBottom;							
		}
	}
	//3. 没以上情况,则方块没有到达底部,置到底标志为false
	m_isBottom = false;	
	//4. 恢复方块在地图中的位置
	ShapeInMap(m_iCurrentShape,1);
	//5. 返回到达底部的标志
	return m_isBottom;
}

bool CRussiaRectView::IsBottom2()
{
	//1.若到游戏区底部,则停止移动,置到底的标志为true,并返回
	if(position2.x >= m_iRow-1)
	{
		//MessageBox("1");
		m_isBottom2 = true;
		position2.x = m_iRow-1;

		sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
		return m_isBottom2;
	}
	//2.否则没有到达游戏区底部,则进行下降碰撞分析
	//2.1 清除原形状在地图中的映像
	ShapeInMap2(m_iCurrentShape2,0);
	//2.2 判断形状下移一个位置后,是否有方块和所处的位置已被占有
	for(int ii=0 ; ii < 4 ; ii++)
	{
		//2.3 如果有任何一个被占有,则说明下方有方块阻挡
		if(gamestatusmap2[position2.x+1+shape[m_iCurrentShape2].Y[ii]][position2.y+shape[m_iCurrentShape2].X[ii]].status == 1)
		{
			//2.4 置到底的标志为true
			m_isBottom2 = true;				
			//2.5 修改恢复原形状在地图中的映像
			ShapeInMap2(m_iCurrentShape2,1);
			//2.6 发出碰撞的音效
			sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
			//2.7 返回已到底部的标志
			return m_isBottom2;							
		}
	}
	//3. 没以上情况,则方块没有到达底部,置到底标志为false
	m_isBottom2 = false;	
	//4. 恢复方块在地图中的位置
	ShapeInMap2(m_iCurrentShape2,1);
	//5. 返回到达底部的标志
	return m_isBottom2;
}

////////////////////////////////////
//void InvalidateCurrent()
//更新左边新生成的方块区域,防止全部更新造成的屏幕抖动
void CRussiaRectView::InvalidateCurrent()
{
	for(int i=0;i<4;i++)
	{	
		CRect rect(
				m_iStartX+(position.x+shape[m_iCurrentShape].X[i])*m_iLarge, 
				m_iStartY+(position.y+shape[m_iCurrentShape].Y[i])*m_iLarge,
				m_iStartX+(position.x+shape[m_iCurrentShape].X[i]+1)*m_iLarge,
				m_iStartY+(position.y+shape[m_iCurrentShape].Y[i]+1)*m_iLarge
				);
		//InvalidateRect(&rect);
		Invalidate(FALSE);
	}
}

////////////////////////////////////
//void InvalidateCurrent2()
//更新左边新生成的方块区域,防止全部更新造成的屏幕抖动
void CRussiaRectView::InvalidateCurrent2()
{
	for (int i2=0;i2<4;i2++)
	{	
		CRect rect(
				m_nWidth-m_iStartX-GAME_WIDTH+(position2.x+shape[m_iCurrentShape2].X[i2])*m_iLarge, 
				m_iStartY2+(position2.y+shape[m_iCurrentShape2].Y[i2])*m_iLarge,
				m_nWidth-m_iStartX-GAME_WIDTH+(position2.x+shape[m_iCurrentShape2].X[i2]+1)*m_iLarge,
				m_iStartY2+(position2.y+shape[m_iCurrentShape2].Y[i2]+1)*m_iLarge
				);
		//InvalidateRect(&rect);
		Invalidate(FALSE);
	}
}

/////////////////////////////////////////////////////
//void ShapeInMap(int index,int status)
//更新形状在地图数组中的状态
void CRussiaRectView::ShapeInMap(int index,int status)
{
	for (int i=0;i<4;i++)
	{
		int y = position.y + shape[index].X[i];
		int x = position.x + shape[index].Y[i];
		if(x>=0&&y>=0)
		{
			gamestatusmap[x][y].status = status;
			gamestatusmap[x][y].status = status;
			if(status == 1)
			{
				gamestatusmap[x][y].color = shape[index].color;
			}
		}
	}
}

void CRussiaRectView::ShapeInMap2(int index, int status)
{
	for (int i=0;i<4;i++)
	{
		int y = position2.y + shape[index].X[i];
		int x = position2.x + shape[index].Y[i];
		if(x>=0&&y>=0)
		{
			gamestatusmap2[x][y].status = status;
			gamestatusmap2[x][y].status = status;
			if(status == 1)
			{
				gamestatusmap2[x][y].color = shape[index].color;
			}
		}
	}
}

void CRussiaRectView::OnUpdateGameStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd || m_bGamePause)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CRussiaRectView::OnUpdateGamePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CRussiaRectView::OnUpdateGameExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CRussiaRectView::OnUpdateGameEnd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (!m_bGameEnd)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CRussiaRectView::OnUpdateOnePlayer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//游戏结束且没有连接网络的时候显示该菜单
	if (m_bGameEnd && !m_bConnectStatus)
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_bOnePlayer);
	}
	else
	{
		pCmdUI->SetCheck(false);
		pCmdUI->Enable(false);
	}
}

void CRussiaRectView::OnUpdateTwoPlayers(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bGameEnd && !m_bConnectStatus)
	{
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(m_bTwoPlayer);
	}
	else
	{
		pCmdUI->SetCheck(false);
		pCmdUI->Enable(false);
	}
}

void CRussiaRectView::OnUpdateRequest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bConnectStatus)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

/////////////////////////////////
//难度选择
void CRussiaRectView::OnLevel1() 
{
	// TODO: Add your command handler code here
	m_iLevel = 1 ;
	
	if(!m_bOnePlayer)
	{
		m_iLevel2 = m_iLevel ;
	}
}
void CRussiaRectView::OnLevel2() 
{
	// TODO: Add your command handler code here
	m_iLevel = 2 ;
	if(!m_bOnePlayer)
	{
		m_iLevel2 = m_iLevel ;
	}
}
void CRussiaRectView::OnLevel3() 
{
	// TODO: Add your command handler code here
	m_iLevel = 3 ;
	if(!m_bOnePlayer)
	{
		m_iLevel2 = m_iLevel ;
	}
}
void CRussiaRectView::OnLevel4() 
{
	// TODO: Add your command handler code here
	m_iLevel = 4 ;
	if(!m_bOnePlayer)
	{
		m_iLevel2 = m_iLevel ;
	}
}
void CRussiaRectView::OnLevel5() 
{
	// TODO: Add your command handler code here
	m_iLevel = 5 ;
	if(!m_bOnePlayer)
	{
		m_iLevel2 = m_iLevel ;
	}
}

//DEL void CRussiaRectView::OnMusicOn() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	m_bMusic = true;
//DEL 	HWND hWnd;
//DEL 	hWnd = GetSafeHwnd();
//DEL 	//分配命令字符串缓冲，错误信息储存缓冲，播放的文件名
//DEL 	char szCmdBuf[300],errBuf[60],szfileName[255];
//DEL 	//错误码
//DEL 	MCIERROR mciError;
//DEL 
//DEL 	//初始化设备元素
//DEL 	strcpy(szfileName,"music2_XJ.mid"); 
//DEL 	//初始化命令字符串
//DEL 	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
//DEL 	//打开设备
//DEL 	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
//DEL 	if (mciError == 0)
//DEL 	{//如果打开成功则播放
//DEL 		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
//DEL 		//根据播放操作是否成功决定是否关闭设备
//DEL 		if (mciError != 0)
//DEL 			mciSendString("close bkMusic",NULL,0,NULL);
//DEL 	}
//DEL }

void CRussiaRectView::OnMusicOff() 
{
	// TODO: Add your command handler code here
	m_bMusic = false;
	mciSendString("close bkMusic",NULL,0,NULL);
}

//////////////////////////////
//int GetDecreaseRow()
//得到当前的分数,返回消去的行数
int CRussiaRectView::GetDecreaseRow()
{
	int DecreaseRow = 0 ;

	//1. 判断是否已得分
	for (int i=0;i<m_iRow;i++)
	{
		//1.1 假设第 i 行满
		m_bIsFull = true;		
		//1.2 对第 i 行进行检查
		for (int j=0;j<m_iCol;j++)
			//1.3 若该行有一个为空的
			if (gamestatusmap[i][j].status == 0)	
			{
				//1.3.1 则该行满为假
				m_bIsFull = false;	
				//1.3.2 立即退出本次循环
				break;					
			}
		//1.4 若该行是满的
		if(m_bIsFull == true) 
		{
			//1.4.1 销去第 i 行
			for (int k=i;k>0;k--)
				for (j=0;j<m_iCol;j++)
				{
					//即将从该行起到最上面的一行,每行的状态改为其上面一行的状态
					gamestatusmap[k][j].status = gamestatusmap[k-1][j].status;
					gamestatusmap[k][j].color = gamestatusmap[k-1][j].color;
				}

			//1.4.2 最上面一行置空
			for (j=0;j<m_iCol;j++)
				gamestatusmap[0][j].status = 0;
			//1.4.3 减少的行数加 1
			DecreaseRow++;
		}		
	}
	//2. 若销去行数大于 0  
	if(DecreaseRow > 0)
	{
		//2.1 统计分数
		m_iScore += (DecreaseRow + 1) * DecreaseRow * 100 / 2;
		//2.2 根据分数更改等级
		if(m_iScore >= (m_iLevel+1)* m_iLevel* 100 * 3)
		{
			m_iLevel++;
			SetTimer(1,1600-250*m_iLevel,NULL);	
		}
		sndPlaySound(".\\xiaoqu.wav",SND_ASYNC);		//销行的声音
		//2.3 更新视图
		InvalidateCurrent();
		//2.4 返回销去的行数	
		return DecreaseRow ;
	}
	//3. 否则没有销去方块
	return 0 ;
}

//////////////////////////////
//int GetDecreaseRow2()
//得到当前的分数,返回消去的行数
int CRussiaRectView::GetDecreaseRow2()
{
	int DecreaseRow2 = 0 ;

	//1. 判断是否有行是满的
	for (int i=0;i<m_iRow;i++)
	{
		//1.1 假设第 i 行满
		m_bIsFull2 = true;		
		//1.2 对第 i 行进行检查
		for (int j=0;j<m_iCol;j++)
			//1.3 若该行有一个为空的
			if (gamestatusmap2[i][j].status == 0)	
			{
				//1.3.1 则该行满为假
				m_bIsFull2 = false;	
				//1.3.2 立即退出本次循环
				break;					
			}
		//1.4 若该行是满的
		if(m_bIsFull2 == true) 
		{
			//1.4.1 销去第 i 行
			for (int k=i ; k>0 ; k--)
				for (j=0 ; j<m_iCol ; j++)
				{
					//即将从该行起到最上面的一行,每行的状态改为其上面一行的状态
					gamestatusmap2[k][j].status = gamestatusmap2[k-1][j].status;
					gamestatusmap2[k][j].color = gamestatusmap2[k-1][j].color;
				}

			//1.4.2 最上面一行置空
			for (j=0 ; j<m_iCol ; j++)
				gamestatusmap2[0][j].status = 0;
			//1.4.3 减少的行数加 1
			DecreaseRow2++;
		}		
	}
	//2. 若销去行数大于 0  
	if(DecreaseRow2 > 0)
	{
		//2.1 统计分数
		m_iScore2 += (DecreaseRow2 + 1) * DecreaseRow2 * 100 / 2;
		//2.2 根据分数更改等级
		if(m_iScore2 >= (m_iLevel2+1)* m_iLevel2* 100 * 2)
		{
			m_iLevel2++;
			SetTimer(2,1600-250*m_iLevel2,NULL);	
		}
		//2.3 更新视图
		InvalidateCurrent2();
		//2.4 返回销去的行数	
		return DecreaseRow2 ;
	}
	//3. 否则没有销去方块
	return 0 ;
}


/////////////////////////////////
//int GetHeight()
//得到游戏中方块垒起的高度
int CRussiaRectView::GetHeight()
{
	//1. 置初值
	int temp = m_iRow ;
	//2. 从左到右对各列进行判断
	for (int i=0 ; i<m_iCol ; i++)
	{
		//2.1 每列的状态按从下往上的顺序进行判断
		for (int j=m_iRow ; j>0 ; j--)
			//2.2 若该列第 j 行为空,且其值小于temp
			if (gamestatusmap[j][i].status == 1 && temp > j)	
				//2.3 将该值付给temp
				temp = j;		
	}

	return m_iRow-temp;
}

/////////////////////////////////
//int GetHeight2()
//得到游戏中方块垒起的高度
int CRussiaRectView::GetHeight2()
{
	//1. 置初值
	int temp2 = m_iRow ;
	//2. 从左到右对各列进行判断
	for (int i=0 ; i<m_iCol ; i++)
	{
		//2.1 每列的状态按从下往上的顺序进行判断
		for (int j=m_iRow ; j>0 ; j--)
			//2.2 若该列第 j 行为空,且其值小于temp
			if (gamestatusmap2[j][i].status == 1 && temp2 > j)	
				//2.3 将该值付给temp
				temp2 = j;		
	}

	return m_iRow-temp2;
}

////////////////////////////////////
//void GameInitial()
//进行和游戏开始有关的数据初始化工作
void CRussiaRectView::GameInitial()
{	
	m_iScore = 0;						//总分值清零
	m_iScore2 = 0;
	m_iTotalRow = 0;					//销去的总行数清零
	m_iTotalRow2 = 0;
	m_iRectHeight = 0;					//游戏区中方块累加的高度
	m_iRectHeight2 = 0;

	position.x = 0;						//左侧形状中(0,0)方块在地图中的纵向坐标
	position.y = 4;						//左侧形状中(0,0)方块在地图中的横向坐标
	position2.x = 0;					//右侧形状中(0,0)方块在地图2中的纵向坐标
	position2.y = 4;					//右侧形状中(0,0)方块在地图2中的横向坐标

	m_iCurrentShape = Random(19,107);		//左侧游戏区域当前形状的索引	
	m_iCurrentShape2 = Random(19,131);		//右侧游戏区域当前形状的索引
	m_iNextShape = Random(19,251);			//左侧游戏区域下一个形状的索引	
	m_iNextShape2 = Random(19,379);			//右侧游戏区域下一个形状的索引	

	m_isBottom = false;					//左侧缺省为没有到达底部
	m_isBottom2 = false;				//右侧缺省为没有到达底部

	m_bIsFull = true;					//底部有满的
	m_bIsFull2 = true;

	//将地图的状态清零
	for (int i=0;i<MAP_ROW;i++)
		for (int j=0;j<MAP_COL;j++)
		{
			gamestatusmap[i][j].status = 0;
			gamestatusmap2[i][j].status = 0;
		}
}

////////////////////////////////
//void GameOver()
//游戏失败结束
void CRussiaRectView::GameOver()
{
	KillTimer(1);
	if(!m_bOnePlayer)KillTimer(2);	

	sndPlaySound(".\\fail.wav",SND_ASYNC);

	if(MessageBox("游戏结束!!!") == 1)
	{
		OnGameEnd() ;
	}
}

/////////////////////////////////
//OnUserHelp() 
//显示帮助提示对话框
void CRussiaRectView::OnUserHelp() 
{
	// TODO: Add your command handler code here
	CUserHelp dlg;
	dlg.DoModal();
}

void CRussiaRectView::OnFieldchangedIpHost(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CRussiaRectView::OnUpdateLevel1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_iLevel==1);
}

void CRussiaRectView::OnUpdateLevel2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_iLevel==2);
	
}

void CRussiaRectView::OnUpdateLevel3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_iLevel==3);
	
}

void CRussiaRectView::OnUpdateLevel4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_iLevel==4);
	
}

void CRussiaRectView::OnUpdateLevel5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_iLevel==5);
}

//DEL void CRussiaRectView::OnUpdateMusicOn(CCmdUI* pCmdUI) 
//DEL {
//DEL 	// TODO: Add your command update UI handler code here
//DEL 	pCmdUI->SetCheck(m_bMusic);
//DEL }

void CRussiaRectView::OnUpdateMusicOff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bMusic);
}

void CRussiaRectView::OnUpdateConnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bGameEnd)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CRussiaRectView::OnGrid() 
{
	// TODO: Add your command handler code here
	m_bDrawGrid = true ;
	Invalidate(false);
}

void CRussiaRectView::OnUpdateGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDrawGrid);
}

void CRussiaRectView::OnNogrid() 
{
	// TODO: Add your command handler code here
	m_bDrawGrid = false ;
	Invalidate(false);
}

void CRussiaRectView::OnUpdateNogrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bDrawGrid);			
}

void CRussiaRectView::OnMusic1() 
{
	// TODO: Add your command handler code here
	if(m_bMusic = true) mciSendString("close bkMusic",NULL,0,NULL);
	m_bMusic = true;
	m_sMusicName = "music1_tkzc.mid";
	PlayMusic(m_sMusicName);
}

void CRussiaRectView::OnMusic2() 
{
	// TODO: Add your command handler code here
	if(m_bMusic = true) mciSendString("close bkMusic",NULL,0,NULL);
	m_bMusic = true;
	m_sMusicName = "music2_ylgz.mid";
	PlayMusic(m_sMusicName);
}

void CRussiaRectView::OnMusic3() 
{
	// TODO: Add your command handler code here
	if(m_bMusic = true) mciSendString("close bkMusic",NULL,0,NULL);
	m_bMusic = true;
	m_sMusicName = "music3_xyj.mid";
	PlayMusic(m_sMusicName);
}

void CRussiaRectView::OnMusic4() 
{
	// TODO: Add your command handler code here
	if(m_bMusic = true) mciSendString("close bkMusic",NULL,0,NULL);
	m_bMusic = true;
	m_sMusicName = "music4_ppt.mid";
	PlayMusic(m_sMusicName);
}

void CRussiaRectView::OnMusic5() 
{
	// TODO: Add your command handler code here
	if(m_bMusic = true) mciSendString("close bkMusic",NULL,0,NULL);
	m_bMusic = true;
	m_sMusicName = "music5_lextd.mid";
	PlayMusic(m_sMusicName);
}

////////////////////////////////////
//void PlayMusic(CString str)
//播放选择的背景音乐
void CRussiaRectView::PlayMusic(CString str)
{
	m_bMusic = true;
	HWND hWnd;
	hWnd = GetSafeHwnd();
	//分配命令字符串缓冲，错误信息储存缓冲，播放的文件名
	char szCmdBuf[300],errBuf[60],szfileName[255];
	//错误码
	MCIERROR mciError;

	//初始化设备元素
	strcpy(szfileName,str); 
	//初始化命令字符串
	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
	//打开设备
	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
	if (mciError == 0)
	{	//如果打开成功则播放
		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
		//根据播放操作是否成功决定是否关闭设备
		if (mciError != 0)
			mciSendString("close bkMusic",NULL,0,NULL);
	}
}

void CRussiaRectView::OnUpdateOnmusic1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bMusic == true)pCmdUI->SetCheck(m_sMusicName == "music1_tkzc.mid");
	else pCmdUI->SetCheck(false);
}

void CRussiaRectView::OnUpdateOnmusic2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bMusic == true)pCmdUI->SetCheck(m_sMusicName == "music2_ylgz.mid");
	else pCmdUI->SetCheck(false);
}

void CRussiaRectView::OnUpdateOnmusic3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bMusic == true)pCmdUI->SetCheck(m_sMusicName == "music3_xyj.mid");
	else pCmdUI->SetCheck(false);
}

void CRussiaRectView::OnUpdateOnmusic4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bMusic == true)pCmdUI->SetCheck(m_sMusicName == "music4_ppt.mid");
	else pCmdUI->SetCheck(false);
}

void CRussiaRectView::OnUpdateOnmusic5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bMusic == true)pCmdUI->SetCheck(m_sMusicName == "music5_lextd.mid");
	else pCmdUI->SetCheck(false);
}
