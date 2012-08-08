// RussiaRectView.h : interface of the CRussiaRectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUSSIARECTVIEW_H__33A78811_B0A6_4C85_A4A2_308FB412924D__INCLUDED_)
#define AFX_RUSSIARECTVIEW_H__33A78811_B0A6_4C85_A4A2_308FB412924D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 宏变量：白色和黑色
#define WHITE	RGB(255,255,255)
#define BLACK	RGB(0,0,0)
#define GRAY	RGB(66,66,66)

#define RED		RGB(255,0,0)
#define GREEN	RGB(0,255,0)
#define BLUE	RGB(0,0,255)

#define COLOR1 RGB(20,50,90)
#define COLOR2 RGB(0,0,0)
#define COLOR3 RGB(20,20,210)
#define BACKGROUND RGB(20,20,90)		//深蓝色背景

//中断操作的运动趋势
#define LEFT	0      //向左移动
#define RIGHT	1      //向左移动
#define UP		2		//向上(变形)      
#define DOWN	3      //向下移动(加速)
#define LEFT2	20      //向左移动
#define RIGHT2	21      //向左移动
#define UP2		22		//向上(变形)      
#define DOWN2	23      //向下移动(加速)

//游戏区域地图最大限制
#define  RECT_LENGTH	25		//方块边长
#define  MAP_ROW		17		//地图的最大行数
#define  MAP_COL		10      //地图的最大列数

#define  GAME_WIDTH     MAP_COL*RECT_LENGTH		//游戏显示区域的宽度
#define  GAME_HEIGHT    (MAP_ROW-1)*RECT_LENGTH     //游戏显示区域的高度

//地图状态
#define MAP_STATE_EMPTY             0    //空(未被占据)
#define MAP_STATE_NOT_EMPTY         1    //被占据


//形状
struct SHAPE  
{
	int X[4];			//形状方块在单元格中的X坐标
	int Y[4];			//形状方块在单元格中的Y坐标
	int next;			//变形时，下一个形状的索引
	int color;			//形状的颜色索引
};

//坐标
struct XY
{
	int x;				//现状中（0，0）方格在游戏状态地图中行号
	int y;				//现状中（0，0）方格在游戏状态地图中列号
};

struct GAMESTATUSMAP
{
	int status;
	int color;
};

class CRussiaRectView : public CView
{
protected: // create from serialization only
	CRussiaRectView();
	DECLARE_DYNCREATE(CRussiaRectView)

// Attributes
public:
	CRussiaRectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussiaRectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRussiaRectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	SHAPE shape[28];			//7种形状，每种各有4种变形，最多共28种(实际只用19种)
	GAMESTATUSMAP gamestatusmap[MAP_ROW][MAP_COL];		//左边游戏区域状态图
	GAMESTATUSMAP gamestatusmap2[MAP_ROW][MAP_COL];		//右边游戏区域状态图

	XY position;				//左边形状中(0,0)方块在左边游戏地图中的坐标
	XY position2;				//右边形状中(0,0)方块在右边游戏地图中的坐标

	int m_iCurrentShape;		//左边当前形状索引
	int m_iCurrentShape2;		//右边当前形状索引
	int m_iNextShape;			//左边下一个形状索引
	int m_iNextShape2;			//右边下一个形状索引
	

	int m_nWidth;				//整个游戏子窗口的宽度
	int m_nHeight;				//整个游戏子窗口的高度
	int m_nWidth2;				//子窗口2的宽度
	int m_nHeight2;				//子窗口2的高度

	int m_iCol;					//游戏状态地图数组的列数
	int m_iRow;					//游戏状态地图数组的行数

	int m_iStartX;				//游戏区域方块的左上角X坐标
	int m_iStartY;				//游戏区域方块的左上角Y坐标
	int m_iStartX2;				//下一个方块提示区的左上角X坐标
	int m_iStartY2;				//下一个方块提示区的左上角Y坐标
	int m_iStartPositionX;
	int m_iStartPositionY;
	
	int m_iLarge;				//小方块的大小,所选的为25
	int m_iBlockStyle;			//当前选择的方块显示样式

	int m_iLevel;				//当前的级别，换算成速度的算法为：1500 - m_iLevel*200
	int m_iLevel2;				//当前的级别，换算成速度的算法为：1500 - m_iLevel*200
	
	bool m_bOnePlayer;			//单机模式下的单人模式:true为单人模式,false非单人模式
	bool m_bTwoPlayer;			//单机模式下的双人模式:true为双人模式,false非双人模式
	bool m_bConnectStatus;		//连接状态:true为已连接网络模式,false为单机模式

	bool m_bFistPlay;			//是否是第一次开始游戏,true为第一次运行,否则不是	
	bool m_bGameEnd;			//游戏是否结束，为true表示结束，否则为准备
	bool m_bGamePause;			//游戏是否暂停，为true表示暂停，否则为运行		
	bool m_isBottom;			//标识方块已到底的变量，到底为TRUE
	bool m_isBottom2;

	int m_iConnectStatus;		//网络模式时的联机状态:0为服务器,1为客户机
	
	int m_iTotalRow;			//统计左边总共消去的行数
	int m_iTotalRow2;	
	int m_iScore;				//统计左边的分数
	int m_iScore2;				//统计右边的分数
	int m_iRectHeight;			//游戏进行时方块累积的高度
	int m_iRectHeight2;			//游戏进行时方块累积的高度

	bool m_bMusic;				//是否有背景音乐
	bool m_bDrawGrid;			//是否有网格线

	bool m_bIsFull;
	bool m_bIsFull2;
	
	CIPAddressCtrl m_HostIP;		//服务器IP
	
	//OnDraw中需要用到的设备名称
	CPen *m_pBlackPen;
	CBrush *m_pBlackBrush;
	CBrush *m_pGrayBrush;
	CBrush *m_pBackGroundBrush;

	//内存绘图设备的处理
	CDC m_memDC;					//内存设备环境 
	CBitmap m_memBmp;				//内存位图
	//CBitmap m_memBmp_7[7];          //内存位图

	CDC m_memRectDC;				//方块内存设备环境
	HBITMAP m_hMemRectBmp;			//方块内存位图句柄

	CString m_sMusicName;			//背景音乐的名字
	bool m_bGameReady;
	bool m_bConnectReady;
	
// Generated message map functions
protected:
	int Random(int,int chaos = 137);	//

	void PlayMusic(CString);

	void GameOver();				//游戏结束函数
	void GameInitial();				//游戏数据的初始化工作

	void DcEnvInitial();
	void DCEnvClear();
	void DrawGame(CDC *pDC);

	void RectDown();				//左边形状下降函数
	void RectDown2();
	void RectArrow(int);			//左边当前方块加速函数：UP，左移：LEFT，右移：RIGHT
	void RectArrow2(int);
	void RectChange();
	void RectChange2();
	bool IsBottom();
	bool IsBottom2();

	void ShapeInMap(int,int);		//将当前形状在地图中的位置写入地图
	void ShapeInMap2(int,int);
	void InvalidateCurrent();
	void InvalidateCurrent2();
		
	bool IsLeftLimit();
	bool IsLeftLimit2();
	bool IsRightLimit();
	bool IsRightLimit2();

	int GetDecreaseRow();
	int GetDecreaseRow2();
	int GetHeight();
	int GetHeight2();

	//{{AFX_MSG(CRussiaRectView)
	afx_msg void OnOnePlayer();
	afx_msg void OnTwoPlayers();
	afx_msg void OnConnect();
	afx_msg void OnShowIP();
	afx_msg void OnRequest();
	afx_msg void OnGameStart();
	afx_msg void OnGamePause();
	afx_msg void OnGameEnd();
	afx_msg void OnGameExit();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateGameStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGamePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameExit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameEnd(CCmdUI* pCmdUI);
	afx_msg void OnLevel1();
	afx_msg void OnLevel2();
	afx_msg void OnLevel3();
	afx_msg void OnLevel4();
	afx_msg void OnLevel5();
	afx_msg void OnMusicOff();
	afx_msg void OnUserHelp();
	afx_msg void OnUpdateOnePlayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTwoPlayers(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRequest(CCmdUI* pCmdUI);
	afx_msg void OnFieldchangedIpHost(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateLevel1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMusicOff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnect(CCmdUI* pCmdUI);
	afx_msg void OnGrid();
	afx_msg void OnUpdateGrid(CCmdUI* pCmdUI);
	afx_msg void OnNogrid();
	afx_msg void OnUpdateNogrid(CCmdUI* pCmdUI);
	afx_msg void OnMusic1();
	afx_msg void OnMusic2();
	afx_msg void OnMusic3();
	afx_msg void OnMusic4();
	afx_msg void OnMusic5();
	afx_msg void OnUpdateOnmusic1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOnmusic2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOnmusic3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOnmusic4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOnmusic5(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RussiaRectView.cpp
inline CRussiaRectDoc* CRussiaRectView::GetDocument()
   { return (CRussiaRectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIARECTVIEW_H__33A78811_B0A6_4C85_A4A2_308FB412924D__INCLUDED_)
