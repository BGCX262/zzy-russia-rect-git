// RussiaRectView.h : interface of the CRussiaRectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUSSIARECTVIEW_H__33A78811_B0A6_4C85_A4A2_308FB412924D__INCLUDED_)
#define AFX_RUSSIARECTVIEW_H__33A78811_B0A6_4C85_A4A2_308FB412924D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ���������ɫ�ͺ�ɫ
#define WHITE	RGB(255,255,255)
#define BLACK	RGB(0,0,0)
#define GRAY	RGB(66,66,66)

#define RED		RGB(255,0,0)
#define GREEN	RGB(0,255,0)
#define BLUE	RGB(0,0,255)

#define COLOR1 RGB(20,50,90)
#define COLOR2 RGB(0,0,0)
#define COLOR3 RGB(20,20,210)
#define BACKGROUND RGB(20,20,90)		//����ɫ����

//�жϲ������˶�����
#define LEFT	0      //�����ƶ�
#define RIGHT	1      //�����ƶ�
#define UP		2		//����(����)      
#define DOWN	3      //�����ƶ�(����)
#define LEFT2	20      //�����ƶ�
#define RIGHT2	21      //�����ƶ�
#define UP2		22		//����(����)      
#define DOWN2	23      //�����ƶ�(����)

//��Ϸ�����ͼ�������
#define  RECT_LENGTH	25		//����߳�
#define  MAP_ROW		17		//��ͼ���������
#define  MAP_COL		10      //��ͼ���������

#define  GAME_WIDTH     MAP_COL*RECT_LENGTH		//��Ϸ��ʾ����Ŀ��
#define  GAME_HEIGHT    (MAP_ROW-1)*RECT_LENGTH     //��Ϸ��ʾ����ĸ߶�

//��ͼ״̬
#define MAP_STATE_EMPTY             0    //��(δ��ռ��)
#define MAP_STATE_NOT_EMPTY         1    //��ռ��


//��״
struct SHAPE  
{
	int X[4];			//��״�����ڵ�Ԫ���е�X����
	int Y[4];			//��״�����ڵ�Ԫ���е�Y����
	int next;			//����ʱ����һ����״������
	int color;			//��״����ɫ����
};

//����
struct XY
{
	int x;				//��״�У�0��0����������Ϸ״̬��ͼ���к�
	int y;				//��״�У�0��0����������Ϸ״̬��ͼ���к�
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
	SHAPE shape[28];			//7����״��ÿ�ָ���4�ֱ��Σ���๲28��(ʵ��ֻ��19��)
	GAMESTATUSMAP gamestatusmap[MAP_ROW][MAP_COL];		//�����Ϸ����״̬ͼ
	GAMESTATUSMAP gamestatusmap2[MAP_ROW][MAP_COL];		//�ұ���Ϸ����״̬ͼ

	XY position;				//�����״��(0,0)�����������Ϸ��ͼ�е�����
	XY position2;				//�ұ���״��(0,0)�������ұ���Ϸ��ͼ�е�����

	int m_iCurrentShape;		//��ߵ�ǰ��״����
	int m_iCurrentShape2;		//�ұߵ�ǰ��״����
	int m_iNextShape;			//�����һ����״����
	int m_iNextShape2;			//�ұ���һ����״����
	

	int m_nWidth;				//������Ϸ�Ӵ��ڵĿ��
	int m_nHeight;				//������Ϸ�Ӵ��ڵĸ߶�
	int m_nWidth2;				//�Ӵ���2�Ŀ��
	int m_nHeight2;				//�Ӵ���2�ĸ߶�

	int m_iCol;					//��Ϸ״̬��ͼ���������
	int m_iRow;					//��Ϸ״̬��ͼ���������

	int m_iStartX;				//��Ϸ���򷽿�����Ͻ�X����
	int m_iStartY;				//��Ϸ���򷽿�����Ͻ�Y����
	int m_iStartX2;				//��һ��������ʾ�������Ͻ�X����
	int m_iStartY2;				//��һ��������ʾ�������Ͻ�Y����
	int m_iStartPositionX;
	int m_iStartPositionY;
	
	int m_iLarge;				//С����Ĵ�С,��ѡ��Ϊ25
	int m_iBlockStyle;			//��ǰѡ��ķ�����ʾ��ʽ

	int m_iLevel;				//��ǰ�ļ��𣬻�����ٶȵ��㷨Ϊ��1500 - m_iLevel*200
	int m_iLevel2;				//��ǰ�ļ��𣬻�����ٶȵ��㷨Ϊ��1500 - m_iLevel*200
	
	bool m_bOnePlayer;			//����ģʽ�µĵ���ģʽ:trueΪ����ģʽ,false�ǵ���ģʽ
	bool m_bTwoPlayer;			//����ģʽ�µ�˫��ģʽ:trueΪ˫��ģʽ,false��˫��ģʽ
	bool m_bConnectStatus;		//����״̬:trueΪ����������ģʽ,falseΪ����ģʽ

	bool m_bFistPlay;			//�Ƿ��ǵ�һ�ο�ʼ��Ϸ,trueΪ��һ������,������	
	bool m_bGameEnd;			//��Ϸ�Ƿ������Ϊtrue��ʾ����������Ϊ׼��
	bool m_bGamePause;			//��Ϸ�Ƿ���ͣ��Ϊtrue��ʾ��ͣ������Ϊ����		
	bool m_isBottom;			//��ʶ�����ѵ��׵ı���������ΪTRUE
	bool m_isBottom2;

	int m_iConnectStatus;		//����ģʽʱ������״̬:0Ϊ������,1Ϊ�ͻ���
	
	int m_iTotalRow;			//ͳ������ܹ���ȥ������
	int m_iTotalRow2;	
	int m_iScore;				//ͳ����ߵķ���
	int m_iScore2;				//ͳ���ұߵķ���
	int m_iRectHeight;			//��Ϸ����ʱ�����ۻ��ĸ߶�
	int m_iRectHeight2;			//��Ϸ����ʱ�����ۻ��ĸ߶�

	bool m_bMusic;				//�Ƿ��б�������
	bool m_bDrawGrid;			//�Ƿ���������

	bool m_bIsFull;
	bool m_bIsFull2;
	
	CIPAddressCtrl m_HostIP;		//������IP
	
	//OnDraw����Ҫ�õ����豸����
	CPen *m_pBlackPen;
	CBrush *m_pBlackBrush;
	CBrush *m_pGrayBrush;
	CBrush *m_pBackGroundBrush;

	//�ڴ��ͼ�豸�Ĵ���
	CDC m_memDC;					//�ڴ��豸���� 
	CBitmap m_memBmp;				//�ڴ�λͼ
	//CBitmap m_memBmp_7[7];          //�ڴ�λͼ

	CDC m_memRectDC;				//�����ڴ��豸����
	HBITMAP m_hMemRectBmp;			//�����ڴ�λͼ���

	CString m_sMusicName;			//�������ֵ�����
	bool m_bGameReady;
	bool m_bConnectReady;
	
// Generated message map functions
protected:
	int Random(int,int chaos = 137);	//

	void PlayMusic(CString);

	void GameOver();				//��Ϸ��������
	void GameInitial();				//��Ϸ���ݵĳ�ʼ������

	void DcEnvInitial();
	void DCEnvClear();
	void DrawGame(CDC *pDC);

	void RectDown();				//�����״�½�����
	void RectDown2();
	void RectArrow(int);			//��ߵ�ǰ������ٺ�����UP�����ƣ�LEFT�����ƣ�RIGHT
	void RectArrow2(int);
	void RectChange();
	void RectChange2();
	bool IsBottom();
	bool IsBottom2();

	void ShapeInMap(int,int);		//����ǰ��״�ڵ�ͼ�е�λ��д���ͼ
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
