// RussiaRectView.cpp : implementation of the CRussiaRectView class
//

#include "stdafx.h"
#include "RussiaRect.h"

#include "RussiaRectDoc.h"
#include "RussiaRectView.h"

#include "ConnectDlg.h"
#include "UserHelp.h"
#include "GameExitDlg.h"

//���ֲ���
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
	m_iRow = MAP_ROW;			//��ͼ����
	m_iCol = MAP_COL;			//��ͼ����

	m_nWidth = 0;				//������Ϸ���ڵĿ��
	m_nHeight = 0;
	m_nWidth2 = 110;			//С���ڵĴ�С
	m_nHeight2 = 150;

	m_iStartX = 10;				//���Ͻ�X��Y����
	m_iStartY = 10;
	m_iStartX2 = m_iStartX;		
	m_iStartY2 = m_iStartY;

	m_iStartPositionX = 0;		//��״����ʱ�ڶ�������������
	m_iStartPositionY = 4;		//��״����ʱ�ڶ����ĺ�������

	m_iLarge = RECT_LENGTH;		//ȱʡ�����СΪm_iLarge������
	//m_iBlockStyle = 2;		//��һ����ʽ

	m_bOnePlayer = true;		//trueΪ����,falseΪ˫��ģʽ
	m_bTwoPlayer = false;		//trueΪ����,falseΪ˫��ģʽ

	m_bFistPlay = true;			//��һ�ο�ʼ��Ϸ
	m_bGameReady = true;		//ȱʡ��Ϸ�Ǵ���׼���õ�״̬
	m_bGameEnd = true;			//ȱʡ��Ϸ�Ѿ�����	
	m_bGamePause = false;		//ȱʡΪ������Ϸ��ͣ״̬
	m_bMusic = false;			//ȱʡΪû�б�������
	m_sMusicName = "";
	m_bDrawGrid = true;			//ȱʡΪ��������
	
	m_iLevel = 3 ;				//ȱʡ����Ϊ3��	
	m_iLevel2 = 3 ;

	m_bConnectStatus = false;	//����״̬,falseΪδ����״̬,trueΪ����״̬
	m_iConnectStatus = 0;		//����״̬,0Ϊ������,1Ϊ�ͻ���
	m_bConnectReady = false;

	GameInitial();				//��ʼ��

	//19����״�Ķ���:��Ű����º���,������ҵĴ���ֱ�Ϊ�ĸ�������
	//"1"
	shape[0].next=1;						//-0----------	
	shape[0].X[0]=0;shape[0].Y[0]=0;		//	-+--
	shape[0].X[1]=0;shape[0].Y[1]=-1;		//	-+--
	shape[0].X[2]=0;shape[0].Y[2]=-2;		//	-+--
	shape[0].X[3]=0;shape[0].Y[3]=-3;		//	-+--
	shape[0].color=0;
	//"1"����1
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
	//"7"����1
	shape[3].next=4;						//-3-----------
	shape[3].X[0]=0;shape[3].Y[0]=0;		//	----
	shape[3].X[1]=1;shape[3].Y[1]=-1;		//	----
	shape[3].X[2]=2;shape[3].Y[2]=-1;		//	-+++
	shape[3].X[3]=0;shape[3].Y[3]=-1;		//	-+--
	shape[3].color=1;
	//"7"����2
	shape[4].next=5;						//-4------------
	shape[4].X[0]=0;shape[4].Y[0]=0;		//	----
	shape[4].X[1]=0;shape[4].Y[1]=-1;		//	-+--
	shape[4].X[2]=0;shape[4].Y[2]=-2;		//	-+--
	shape[4].X[3]=1;shape[4].Y[3]=0;		//	-++-
	shape[4].color=1;
	//"7"����3
	shape[5].next=2;						//-5------------
	shape[5].X[0]=0;shape[5].Y[0]=0;		//	----
	shape[5].X[1]=1;shape[5].Y[1]=0;		//	----
	shape[5].X[2]=2;shape[5].Y[2]=0;		//	---+
	shape[5].X[3]=2;shape[5].Y[3]=-1;		//	-+++
	shape[5].color=1;
	//��"7"
	shape[6].next=7;						//-6------------
	shape[6].X[0]=0;shape[6].Y[0]=0;		//	----
	shape[6].X[1]=0;shape[6].Y[1]=-1;		//	-++-
	shape[6].X[2]=0;shape[6].Y[2]=-2;		//	-+--
	shape[6].X[3]=1;shape[6].Y[3]=-2;		//	-+--
	shape[6].color=2;
	//��"7"����1
	shape[7].next=8;						//-7------------
	shape[7].X[0]=0;shape[7].Y[0]=0;		//	----
	shape[7].X[1]=0;shape[7].Y[1]=-1;		//	----
	shape[7].X[2]=1;shape[7].Y[2]=0;		//	-+--
	shape[7].X[3]=2;shape[7].Y[3]=0;		//	-+++
	shape[7].color=2;
	//��"7"����2
	shape[8].next=9;						//-8------------
	shape[8].X[0]=0;shape[8].Y[0]=0;		//	----
	shape[8].X[1]=1;shape[8].Y[1]=0;		//	--+-
	shape[8].X[2]=1;shape[8].Y[2]=-2;		//	--+-
	shape[8].X[3]=1;shape[8].Y[3]=-1;		//	-++-
	shape[8].color=2;
	//��"7"����3
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
	//"T"����1
	shape[11].next=12;						//-11------------
	shape[11].X[0]=0;shape[11].Y[0]=0;		//	----
	shape[11].X[1]=1;shape[11].Y[1]=0;		//	----
	shape[11].X[2]=2;shape[11].Y[2]=0;		//	--+-
	shape[11].X[3]=1;shape[11].Y[3]=-1;		//	-+++
	shape[11].color=3;
	//"T"����2
	shape[12].next=13;						//-12------------
	shape[12].X[0]=1;shape[12].Y[0]=0;		//	----
	shape[12].X[1]=1;shape[12].Y[1]=-1;		//	--+-
	shape[12].X[2]=1;shape[12].Y[2]=-2;		//	-++-
	shape[12].X[3]=0;shape[12].Y[3]=-1;		//	--+-
	shape[12].color=3;
	//"T"����3
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
	//S����1
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
	//Z����1
	shape[17].next=16;						//-17-------------
	shape[17].X[0]=0;shape[17].Y[0]=0;		//	----
	shape[17].X[1]=0;shape[17].Y[1]=-1;		//	--+-
	shape[17].X[2]=1;shape[17].Y[2]=-1;		//	-++-
	shape[17].X[3]=1;shape[17].Y[3]=-2;		//	-+--
	shape[17].color=5;
	//����
	shape[18].next=18;						//-18------------
	shape[18].X[0]=0;shape[18].Y[0]=0;		//	----
	shape[18].X[1]=1;shape[18].Y[1]=0;		//	----
	shape[18].X[2]=0;shape[18].Y[2]=-1;		//	-++-
	shape[18].X[3]=1;shape[18].Y[3]=-1;		//	-++-
	shape[18].color=6;	

}

//////////////////////////////////////
//~CRussiaRectView()
//��������
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
//������ͼ����
void CRussiaRectView::OnDraw(CDC* pDC)
{
	CRussiaRectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	DcEnvInitial();
	DrawGame(&m_memDC);  //���ڴ�λͼ����Ϸ�������

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
//�����豸�����ĳ�ʼ��
void CRussiaRectView::DcEnvInitial()
{
	if(m_bFistPlay)
	{
		m_bFistPlay = false;
		//��Ĭ�ϵĲ�������ȡ��ǰ��Ļ�豸����
		CDC *pWindowDC = GetDC();

		//1.����ӳ����Ļ���ڴ��豸����
		//��ȡ��Ϸ���ڵĴ�С�������������ڴ�λͼ�ĳߴ�
		CRect windowRect;
		GetClientRect(&windowRect);
		m_nWidth = windowRect.Width();
		m_nHeight = windowRect.Height();
		
		m_memDC.CreateCompatibleDC(pWindowDC);		//�ڴ��豸��������Ļ�豸�������������ݣ�
		m_memBmp.CreateCompatibleBitmap(pWindowDC,m_nWidth,m_nHeight);	//�ڴ�λͼ������Ļ����(����),��СΪ��Ϸ���ڵĳߴ�
		m_memDC.SelectObject(&m_memBmp);	//�ڴ��豸�������ڴ�λͼ�������Ա�ͨ��m_memDC���ڴ�λͼ������

		//2.�洢����λͼ���ڴ���Դ
		m_memRectDC.CreateCompatibleDC(pWindowDC);	//�ڴ��豸��������Ļ�豸�������������ݣ�
		m_hMemRectBmp=(HBITMAP)LoadImage(NULL,"rect.bmp",IMAGE_BITMAP,175,25,LR_LOADFROMFILE);	//�൱�ڽ��ⲿλͼrect.bmp��̬����m_hMemRectBmp��
		SelectObject(m_memRectDC.m_hDC, m_hMemRectBmp);		//�ڴ��豸�������ڴ�λͼ�������Ա�ͨ��m_memDC���ڴ�λͼ������
		
		m_pBlackPen  = new CPen(PS_SOLID,1,BACKGROUND);	//��ɫ�Ļ���	
		m_pGrayBrush  = new CBrush(GRAY);				//��ˢ
		m_pBlackBrush  = new CBrush(BLACK);				//��ˢ
		m_pBackGroundBrush  = new CBrush(BACKGROUND);
	}
}

//////////////////////////////////
//void DCEnvClear()
//�豸��������
void CRussiaRectView::DCEnvClear()
{
	//�豸����
	m_memDC.DeleteDC();
	m_memRectDC.DeleteDC();
	//λͼ��Դ
	DeleteObject(m_memBmp);
	DeleteObject(m_hMemRectBmp);

	delete(m_pBlackPen);
	delete(m_pBlackBrush);
	delete(m_pGrayBrush);
	delete(m_pBackGroundBrush);
}

//////////////////////////////////////////
//void DrawGame(CDC *pDC)
//����ͼ��
void CRussiaRectView::DrawGame(CDC *pDC)
{
	//ѡ�ñ���ɫ��ˢ������������Ϸ���ڴ��ڵı���
	pDC -> SelectObject(m_pBackGroundBrush);
	CRect rect;
	GetClientRect(&rect);
	pDC -> Rectangle(rect);

	//ѡ�ú�ɫ��ˢ��������Ϸ����ı���
	pDC -> SelectObject(m_pBlackBrush);		//ѡ���ɫ��ˢ
	//������������Ϸ��
	pDC -> Rectangle(m_iStartX,m_iStartY, m_iStartX+GAME_WIDTH, m_iStartY+GAME_HEIGHT);
	pDC -> Rectangle(m_nWidth-m_iStartX-GAME_WIDTH,m_iStartY, m_nWidth-m_iStartX, m_iStartY+GAME_HEIGHT);
	//���м�������ʾ��һ�����������
	pDC -> Rectangle(m_nWidth/2-m_nWidth2,m_iStartY+10, m_nWidth/2-2, m_iStartY+10+m_nHeight2);
	pDC -> Rectangle(m_nWidth/2+2,m_iStartY+10, m_nWidth/2+m_nWidth2, m_iStartY+10+m_nHeight2);
	//���м��²���������ʾ��
	pDC -> Rectangle(m_nWidth/2-100,m_iStartY+m_nHeight2+50,m_nWidth/2+100, m_iStartY+m_nHeight2+250);
	
	//��������
	if(m_bDrawGrid)
	{
		pDC->SelectObject(m_pBlackPen);
		for (int i=0;i<m_iRow;i++)		//������
		{
			//��ߵ�����	
			pDC->MoveTo(m_iStartX, m_iStartY + i*m_iLarge);
			pDC->LineTo(m_iStartX+GAME_WIDTH, m_iStartY +i*m_iLarge);
			//�ұߵ�����
			pDC->MoveTo(m_nWidth-m_iStartX-GAME_WIDTH, m_iStartY + i*m_iLarge);
			pDC->LineTo(m_nWidth-m_iStartX, m_iStartY+i*m_iLarge);
		}		
		for (i=0;i<m_iCol;i++)		//������
		{
			//��ߵ�����
			pDC->MoveTo(m_iStartX+i*m_iLarge, m_iStartY);
			pDC->LineTo(m_iStartX+i*m_iLarge, m_iStartY+GAME_HEIGHT);
			//�ұߵ�����
			pDC->MoveTo(m_nWidth-m_iStartX-i*m_iLarge, m_iStartY);
			pDC->LineTo(m_nWidth-m_iStartX-i*m_iLarge, m_iStartY+GAME_HEIGHT);
		}
	}

	int x,y,nW,nH;
	//С����Ļ���
	for (int i=0 ; i<m_iRow ; i++)
		for (int j=0 ; j<m_iCol ; j++)
		{
			//�������
			if (gamestatusmap[i][j].status == 1)
			{
				//����Ϸ������״̬Ϊ��ռ��״̬���������С����
				x = m_iStartX+j*m_iLarge ;
				y = m_iStartY+(i-1)*m_iLarge ;
				nW = m_iLarge ;
				nH = m_iLarge ;
				pDC->BitBlt(x,y,nW,nH,&m_memRectDC,gamestatusmap[i][j].color*m_iLarge,0,SRCCOPY);
			}
			//˫��ģʽ��
			if(!m_bOnePlayer)
			{
				//�ұ�����
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

	//��ʾ��Ϸ������Ϸ����ĺ�������
	pDC -> SetBkColor(BLACK);
	pDC -> SetTextColor(WHITE);
	pDC -> TextOut(m_nWidth/2-m_nWidth2+10, m_iStartY+20, "��һ������:");
	pDC -> TextOut(m_nWidth/2+2+10, m_iStartY+20, "��һ������:");
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30, "��Ϸ����");
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30+40,"�ۻ��߶�");	
	pDC -> TextOut(m_nWidth/2-100+70, m_iStartY+m_nHeight2+50+30+80, "��ȥ����");				
	pDC -> TextOut(m_nWidth/2-100+75, m_iStartY+m_nHeight2+50+30+120,"��    ��");
	if (!m_bGameEnd)
	{
		pDC -> SetBkColor(BLACK);
		pDC -> SetTextColor(RED);
		
		//��Ϸ����
		CString strLevel;	
		strLevel.Format("%d",m_iLevel);
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30, strLevel);
		if(!m_bOnePlayer)
		{
			CString strLevel2;	
			strLevel2.Format("%d",m_iLevel2);
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30, strLevel2);
		}

		//�ۻ��߶�
		CString strHeight;	
		strHeight.Format("%d",m_iRectHeight);	
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30+40, strHeight);
		if(!m_bOnePlayer)
		{
			CString strHeight2;	
			strHeight2.Format("%d",m_iRectHeight2);	
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30+40, strHeight2);
		}
		
		//��ȥ����
		CString strRow;	
		strRow.Format("%d",m_iTotalRow);	
		pDC -> TextOut(m_nWidth/2-100+30, m_iStartY+m_nHeight2+50+30+80, strRow);
		if(!m_bOnePlayer)
		{
			CString strRow2;	
			strRow2.Format("%d",m_iTotalRow2);
			pDC -> TextOut(m_nWidth/2+50, m_iStartY+m_nHeight2+50+30+80, strRow2);
		}
		
		//�÷�
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

	//����һ�ν�Ҫ���ֵķ��飬������ʾ�û�
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

		//�ǵ���ģʽ��,�����ұߵ���һ��ͼ��
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
//ѡ����ģʽ
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
//ѡ��˫��ģʽ
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
//��������
void CRussiaRectView::OnConnect() 
{
	// TODO: Add your command handler code here
	//������
	if(!m_bConnectStatus && m_bGameEnd)
	{
		CConnectDlg dlg;
		DWORD dwIP;
		
		int command = dlg.DoModal();					//�����Ի���
		dlg.m_iConnectStatus = m_iConnectStatus;		//����״̬��ѡ��

		if(IDOK == command)								//ȷ������
		{
			//m_bGameEnd = false;
			m_bConnectStatus = true;					//������ʼ
			m_iConnectStatus = dlg.m_iConnectStatus;	//��������״̬
			//���ͻ���
			if(m_iConnectStatus == 2)
			{
				//�Ѿ���ʼ
				//if(m_bConnectReady)m_bGameEnd = false;
				((CIPAddressCtrl*)GetDlgItem(IDC_IP_HOST))->GetAddress(dwIP);
			}
			//��������
			else if(m_iConnectStatus == 1)
			{
				//if(m_bConnectReady)m_bGameEnd = true;
			}
		}
		else if(IDCANCEL == command)
		{
			m_bGameEnd = true;
			m_bConnectStatus = false;					//ȡ��ѡ��
		}  
	}
	else
	{
		m_bConnectStatus = false;
	}
}

///////////////////////////////////////
//void OnShowIP() 
//��ʾ������IP
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
	MessageBox(str,"����IP");
}


//DEL void CRussiaRectView::OnDoubleclickedOk() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }

////////////////////////////////
//void OnRequest() 
//����ս
void CRussiaRectView::OnRequest() 
{
	// TODO: Add your command handler code here
	m_bGameEnd = true;
	//������ģʽ��
	if(m_bConnectStatus == true)
	{
		//////////////////////
		//TO ADD:�ر�������Ϸģʽ
		m_bConnectStatus = false;
	}
	//�ڵ���ģʽ��
	else
	{
		m_bConnectStatus =true;
		///////////////////////////
		//TO ADD: ����������Ϸģʽ
		//...
	}
}

//////////////////////////////////////
//void OnGameStart()
//��Ϸ��ʼ
void CRussiaRectView::OnGameStart() 
{
	// TODO: Add your command handler code here
	//���������Ϸ��ͣ״̬���������Щ��ʼ����
	if (!m_bGamePause)  
	{
		//����Ϸ�����ı�־��Ϊfalse
		m_bGameEnd = false;	
		//����һЩ��ʼ���Ĺ���
		GameInitial();
		//
		Invalidate(false);
		//˫��ģʽ
		if(!m_bOnePlayer)
		{
			SetTimer(2,1600-250*m_iLevel2,NULL);	
		}
	}
	m_bGamePause = false;
	SetTimer(1,1600-250*m_iLevel,NULL);		//���ü�ʱ��
	sndPlaySound(".\\kaishi.wav",SND_ASYNC);
}

///////////////////////////////////////
//void OnGamePause() 
//��Ϸ��ͣ
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
//��Ϸ����
void CRussiaRectView::OnGameEnd() 
{
	// TODO: Add your command handler code here
	m_bGameEnd = true;			//��Ϸ����
	m_bConnectStatus = false;	//�Ͽ�����
	
	//��Ϸ״̬��ͼ����
	for (int i=0;i<m_iRow;i++)
		for (int j=0;j<m_iCol;j++)
		{
			gamestatusmap[i][j].status=0;
			if(!m_bOnePlayer)gamestatusmap2[i][j].status=0;
		}

	//����������Ϸ������ʾͼ
	CRect rect(0,0,m_nWidth,m_nHeight);
	InvalidateRect(&rect);

	m_bGamePause = false;;  //�����Ϸ��ͣ״̬

	KillTimer(1);	
	if(!m_bOnePlayer)KillTimer(2);
}

///////////////////////////////////////
//void OnGameExit() 
//�˳���Ϸ
void CRussiaRectView::OnGameExit() 
{
	// TODO: Add your command handler code here
	////�����ڴ��豸�������ͷ���Դ
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
	case 'A':					//A ����һ��
		RectArrow(LEFT);
		break;
	case 'D':					//D	����һ��
		RectArrow(RIGHT);
		break;
	case 'W':					//W	�������
		RectChange();
		break;
	case 'S':					//S	����һ��
		RectArrow(DOWN);
		break;
	case VK_SPACE:				//SPACE ֱ�����䵽�ײ�
		while(!IsBottom())
			RectDown();
		break;
	//˫��ģʽ
	case VK_LEFT:				//LEFT ����һ��
		if(!m_bOnePlayer) 
			RectArrow2(LEFT2);
		break;
	case VK_RIGHT:				//RIGHT	����һ��	
		if(!m_bOnePlayer) 
			RectArrow2(RIGHT2);
		break;
	case VK_UP:					//UP �������
		if(!m_bOnePlayer) 
			RectChange2();
		break;
	case VK_DOWN:				//DOWN ����һ��
		if(!m_bOnePlayer) 
			RectArrow2(DOWN2);
		break;
	case VK_NUMPAD0:			//Number 0 ֱ�����䵽�ײ�
		if(!m_bOnePlayer)
			while(!IsBottom2())
				RectDown2();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////
//void RectArrow(int m_Type)
//���ݼ���������Ʒ���Ķ���
void CRussiaRectView::RectArrow(int m_Type)
{
	switch(m_Type)
	{
	case LEFT:
		if(!IsLeftLimit() && !m_isBottom)	//�����û������ ��û�е���ײ�
		{
			ShapeInMap(m_iCurrentShape,0);	//��ԭ��״���
			//InvalidateCurrent();

			position.y--;					//����һ����λ

			ShapeInMap(m_iCurrentShape,1);	//��ʾ���ƺ����״	
			InvalidateCurrent();	
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
			
		}
		break;

	case RIGHT:
		if(!IsRightLimit() && !m_isBottom)	//�����û������ ��û�е���ײ�
		{
			ShapeInMap(m_iCurrentShape,0);	//��ԭ��״���
			//InvalidateCurrent();

			position.y++;					//����һ����λ

			ShapeInMap(m_iCurrentShape,1);	//��ʾ���ƺ����״	
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
//�ұ߸��ݼ���������Ʒ���Ķ���
void CRussiaRectView::RectArrow2(int m_Type)
{
	switch(m_Type)
	{
	case LEFT2:
		if(!IsLeftLimit2() && !m_isBottom2)	//�����û������ ��û�е���ײ�
		{
			ShapeInMap2(m_iCurrentShape2,0);	//��ԭ��״���
			//InvalidateCurrent2();

			position2.y--;					//����һ����λ

			ShapeInMap2(m_iCurrentShape2,1);	//��ʾ���ƺ����״	
			InvalidateCurrent2();
			sndPlaySound(".\\yidong.wav",SND_ASYNC);
		}
		break;
	case RIGHT2:
		if(!IsRightLimit2() && !m_isBottom2)	//�����û������ ��û�е���ײ�
		{
			ShapeInMap2(m_iCurrentShape2,0);	//��ԭ��״���
			//InvalidateCurrent2();

			position2.y++;					//����һ����λ

			ShapeInMap2(m_iCurrentShape2,1);	//��ʾ���ƺ����״	
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
//��߷������ƺ���
void CRussiaRectView::RectDown()
{
	//�鿴�Ƿ񵽴�ײ�
	m_isBottom = IsBottom();
	//1.��û�е���ײ�,���������
	if (!m_isBottom)
	{
		//m_isBottom = false;
		//1.1 �����ǰ�ķ���
		ShapeInMap(m_iCurrentShape,0);
		//1.2 ��������
		position.x++;
		//1.3 �����µĵ�ͼ����
		ShapeInMap(m_iCurrentShape,1);
		//1.4 ��ʾ�µ�ͼ��
		InvalidateCurrent();
	}
}

//////////////////////////////
//void RectDown2()
//�ұ߷������ƺ���
void CRussiaRectView::RectDown2()
{	
	//�鿴�Ƿ񵽴�ײ�
	m_isBottom2 = IsBottom2();
	//1.��û�е���ײ�,���������
	if (!m_isBottom2)
	{
		//1.1 �����ǰ�ķ���
		ShapeInMap2(m_iCurrentShape2,0);
		//1.2 ��������
		position2.x++;
		//1.3 �����µĵ�ͼ����
		ShapeInMap2(m_iCurrentShape2,1);
		//1.4 ��ʾ�µ�ͼ��
		InvalidateCurrent2();
	}
}

///////////////////////////////////
//bool IsLeftLimit()
//����ж��Ƿ������Ƶ�����,true˵����߱�����,false˵�����û�б�����
bool CRussiaRectView::IsLeftLimit()
{
	//1. ��ʱ�����ͼ�е���״
	ShapeInMap(m_iCurrentShape,0);		
	//2. �жϷ�������һ����λ��,�Ƿ���λ���ѱ�ռ��
	for(int i=0 ; i<4 ; i++)
	{	//2.1 ��������߽����ߵ�����ռ��
		if(position.y+shape[m_iCurrentShape].X[i] <= 0 || gamestatusmap[position.x+shape[m_iCurrentShape].Y[i]][position.y-1+shape[m_iCurrentShape].X[i]].status == 1)
		{
			//2.1.1 �ָ���ʱ�����ͼ�е���״
			ShapeInMap(m_iCurrentShape,1);
			//2.1.2 ������߱�����
			return true;					
		}
	}
	//3. ��û��������������,��ָ���ʱ�����ͼ�е���״
	ShapeInMap(m_iCurrentShape,1);
	//4. ����û�б�����
	return false;					
}

///////////////////////////////////
//bool IsLeftLimit2()
//�ұ��ж��Ƿ������Ƶ�����,true˵����߱�����,false˵�����û�б�����
bool CRussiaRectView::IsLeftLimit2()
{
	//1. ��ʱ�����ͼ�е���״
	ShapeInMap2(m_iCurrentShape2,0);		
	//2. �жϷ�������һ����λ��,�Ƿ���λ���ѱ�ռ��
	for(int i=0 ; i<4 ; i++)
	{	//2.1 ��������߽����ߵ�����ռ��
		if(position2.y+shape[m_iCurrentShape2].X[i] <= 0 || gamestatusmap2[position2.x+shape[m_iCurrentShape2].Y[i]][position2.y-1+shape[m_iCurrentShape2].X[i]].status == 1)
		{
			//2.1.1 �ָ���ʱ�����ͼ�е���״
			ShapeInMap2(m_iCurrentShape2,1);
			//2.1.2 ������߱�����
			return true;					
		}
	}
	//3. ��û��������������,��ָ���ʱ�����ͼ�е���״
	ShapeInMap2(m_iCurrentShape2,1);
	//4. ����û�б�����
	return false;					
}

/////////////////////////////////////
//bool IsRightLimit()
//
bool CRussiaRectView::IsRightLimit()
{
	//1. ��ʱ�����ͼ�е���״
	ShapeInMap(m_iCurrentShape,0);		
	//2. �жϷ�������һ����λ��,�Ƿ���λ���ѱ�ռ��
	for(int i=0 ; i<4 ; i++)
	{	//2.1 �������ұ߽�����ƺ�ĵ�����ռ��
		if(position.y+shape[m_iCurrentShape].X[i] >= 9 || gamestatusmap[position.x+shape[m_iCurrentShape].Y[i]][position.y+1+shape[m_iCurrentShape].X[i]].status == 1)
		{
			//2.2 �ָ���ʱ�����ͼ�е���״
			ShapeInMap(m_iCurrentShape,1);
			//2.3 �����ұ߱�����
			return true;	
		}
	}
	//3. �ָ���ʱ�����ͼ�е���״
	ShapeInMap(m_iCurrentShape,1);	
	//4. ����û�б�����
	return false;	
}

/////////////////////////////////////
//bool IsRightLimit2()
//
bool CRussiaRectView::IsRightLimit2()
{
	//1. ��ʱ�����ͼ�е���״
	ShapeInMap2(m_iCurrentShape2,0);		
	//2. �жϷ�������һ����λ��,�Ƿ���λ���ѱ�ռ��
	for(int i=0 ; i<4 ; i++)
	{	//2.1 �������ұ߽�����ƺ�ĵ�����ռ��
		if(position2.y+shape[m_iCurrentShape2].X[i] >= 9 || gamestatusmap2[position2.x+shape[m_iCurrentShape2].Y[i]][position2.y+1+shape[m_iCurrentShape2].X[i]].status == 1)
		{
			//2.2 �ָ���ʱ�����ͼ�е���״
			ShapeInMap2(m_iCurrentShape2,1);
			//2.3 �����ұ߱�����
			return true;	
		}
	}
	//3. �ָ���ʱ�����ͼ�е���״
	ShapeInMap2(m_iCurrentShape2,1);	
	//4. ����û�б�����
	return false;	
}

////////////////////////////////////
//void RectChange()
//������κ���,���ݵ�ǰ�ķ���任��˳ʱ����ת��ķ���
void CRussiaRectView::RectChange()
{
	if(!m_isBottom)
	{
		//1. ���ԭ����λͼӳ��
		ShapeInMap(m_iCurrentShape,0);	
		//2. �ݴ���κ��������
		int m_itempNextShape = shape[m_iCurrentShape].next;
		//3. �����κ�,�ж��Ƿ��г�ͻ 
		for(int i=0 ; i<4 ; i++)
		{	//3.1 ���κ��з��������ռ��
			if(gamestatusmap[position.x+shape[m_itempNextShape].Y[i]][position.y+shape[m_itempNextShape].X[i]].status != 0)
			{
				ShapeInMap(m_iCurrentShape,1);	//�ָ���ʱ�����ͼ�е���״
				return;							//����
			}
			//3.2 ���κ�Խ��(������)
			if(position.y+shape[m_itempNextShape].X[i] < 0 || position.y+shape[m_itempNextShape].X[i] > 9 || position.x+shape[m_itempNextShape].Y[i] > 15)
			{
				//�ָ���ʱ�����ͼ�е���״
				ShapeInMap(m_iCurrentShape,1);
				//����
				return ;					
			}
		}
		//4. �����κ�,û�г�ͻ,����ǰ��״����Ϊ��һ����״
		m_iCurrentShape = shape[m_iCurrentShape].next;
		//5. ���±��κ��λͼӳ��
		ShapeInMap(m_iCurrentShape,1);
		//6. ��ʾ���κ��λͼ
		InvalidateCurrent();
		sndPlaySound(".\\bianxin.wav",SND_ASYNC);
	}
}

////////////////////////////////////
//void RectChange2()
//������κ���,���ݵ�ǰ�ķ���任��˳ʱ����ת��ķ���
void CRussiaRectView::RectChange2()
{
	if(!m_isBottom2)
	{
		//1. ���ԭ����λͼӳ��
		ShapeInMap2(m_iCurrentShape2,0);	
		//2. �ݴ���κ��������
		int m_itempNextShape2 = shape[m_iCurrentShape2].next;
		//3. �����κ�,�ж��Ƿ��г�ͻ 
		for(int i=0 ; i<4 ; i++)
		{	//3.1 ���κ��з��������ռ��
			if(gamestatusmap2[position2.x+shape[m_itempNextShape2].Y[i]][position2.y+shape[m_itempNextShape2].X[i]].status != 0)
			{
				ShapeInMap2(m_iCurrentShape2,1);	//�ָ���ʱ�����ͼ�е���״
				return;							//����
			}
			//3.2 ���κ�Խ��(������)
			if(position2.y+shape[m_itempNextShape2].X[i] < 0 || position2.y+shape[m_itempNextShape2].X[i] > 9 || position2.x+shape[m_itempNextShape2].Y[i] > 15)
			{
				//�ָ���ʱ�����ͼ�е���״
				ShapeInMap2(m_iCurrentShape2,1);
				//����
				return ;					
			}
		}
		//4. �����κ�,û�г�ͻ,����ǰ��״����Ϊ��һ����״
		m_iCurrentShape2 = shape[m_iCurrentShape2].next;
		//5. ���±��κ��λͼӳ��
		ShapeInMap2(m_iCurrentShape2,1);
		//6. ��ʾ���κ��λͼ
		InvalidateCurrent2();
		sndPlaySound(".\\bianxin.wav",SND_ASYNC);
	}
}

//////////////////////////////////////////
//int Random(int MaxNumber)
//���������,MaxNumberΪģ,chaosΪ�Ŷ�����,��ֹ�������øú���ʱ,��ʱ�����ӵĲ��̫С���ܲ�����ͬ��������
int CRussiaRectView::Random(int MaxNumber ,int chaos)
{
	srand( (unsigned)time( NULL ) );	//�����������
	int random = (rand()+chaos) % MaxNumber;	//���������
	
	return random;
}

///////////////////////////////////////////
//void OnTimer(UINT nIDEvent)
//��ʱ������,Ϊ���������е�ʱ�Ӷ����ṩ����
void CRussiaRectView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//1. ���ԭ���ķ����ѵ��׻���Ϸ�տ�ʼ
	if (m_isBottom)
	{
		//1 ����ǰ�ķ���λ�ñ��浽��ͼ������
		ShapeInMap(m_iCurrentShape,1);

		//2 ��ü��ٵ������ͷ���
		m_iTotalRow += GetDecreaseRow();
		//2.3 �õ���ʱ�����ۻ��ĸ߶�
		m_iRectHeight = GetHeight();
		//3. ����ǰ��������һ���������
		m_iCurrentShape = m_iNextShape;
		//4. ����õ���һ�εķ�����ʽ
		m_iNextShape = Random(19);  
		//5. ��ʼ����ǰ�·���ĳ�ʼ��λ��
		position.x = m_iStartPositionX;
		position.y = m_iStartPositionY;	
		//2.6 ��ʾ��ͼ��
		InvalidateCurrent();

		//6. ������ײ�
		if(IsBottom())
		{
			//2.4 �����������ۻ��߶ȳ����˴��ڵĶ���
			if(m_iRectHeight >= m_iRow -1)
			{
				//2.5 ��Ϸ����
				GameOver();
			} 
		}
		
		RectDown();
	}
	//2.����û�е���ײ�
	else  
	{
		//2.1�����½�
		RectDown();
	}
	//�ұ�:���ԭ���ķ����ѵ��׻���Ϸ�տ�ʼ�������һ���µķ���
	if(!m_bOnePlayer)
	{
		//1. ���ԭ���ķ����ѵ��׻���Ϸ�տ�ʼ
		if (m_isBottom2)
		{
			//1 ����ǰ�ķ���λ�ñ��浽��ͼ������
			ShapeInMap2(m_iCurrentShape2,1);

			//2 ��ü��ٵ������ͷ���
			m_iTotalRow2 += GetDecreaseRow2();
			//2.3 �õ���ʱ�����ۻ��ĸ߶�
			m_iRectHeight2 = GetHeight2();
			//3. ����ǰ��������һ���������
			m_iCurrentShape2 = m_iNextShape2;
			//4. ����õ���һ�εķ�����ʽ
			m_iNextShape2 = Random(19);  
			//5. ��ʼ����ǰ�·���ĳ�ʼ��λ��
			position2.x = m_iStartPositionX;
			position2.y = m_iStartPositionY;	
			//2.6 ��ʾ��ͼ��
			InvalidateCurrent2();

			//6. ������ײ�
			if(IsBottom2())
			{
				//2.4 �����������ۻ��߶ȳ����˴��ڵĶ���
				if(m_iRectHeight2 >= m_iRow -1)
				{
					//2.5 ��Ϸ����
					GameOver();
				} 
			}			
			RectDown2();
		}
		//2. ����,��ǰ�����½�
		else  
		{
			RectDown2();
		}
	}

	CView::OnTimer(nIDEvent);
}

///////////////////////////////
//IsBottom()
//�ж��Ƿ񵽴�ײ�
bool CRussiaRectView::IsBottom()
{
	//1.������Ϸ���ײ�,��ֹͣ�ƶ�,�õ��׵ı�־Ϊtrue,������
	if(position.x >= m_iRow-1)
	{
		m_isBottom = true;
		position.x = m_iRow-1;

		sndPlaySound(".\\zhuangdi.wav",SND_ASYNC);
		return m_isBottom;
	}
	//2.����û�е�����Ϸ���ײ�,������½���ײ����
	//2.1 ���ԭ��״�ڵ�ͼ�е�ӳ��
	ShapeInMap(m_iCurrentShape,0);
	//2.2 �ж���״����һ��λ�ú�,�Ƿ��з����������λ���ѱ�ռ��
	for(int ii=0 ; ii < 4 ; ii++)
	{
		//2.3 ������κ�һ����ռ��,��˵���·��з����赲
		if(gamestatusmap[position.x+1+shape[m_iCurrentShape].Y[ii]][position.y+shape[m_iCurrentShape].X[ii]].status == 1)
		{
			//2.4 �õ��׵ı�־Ϊtrue
			m_isBottom = true;				
			//2.5 �޸Ļָ�ԭ��״�ڵ�ͼ�е�ӳ��
			ShapeInMap(m_iCurrentShape,1);
			//2.6 ������ײ����Ч
			sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
			//2.7 �����ѵ��ײ��ı�־
			return m_isBottom;							
		}
	}
	//3. û�������,�򷽿�û�е���ײ�,�õ��ױ�־Ϊfalse
	m_isBottom = false;	
	//4. �ָ������ڵ�ͼ�е�λ��
	ShapeInMap(m_iCurrentShape,1);
	//5. ���ص���ײ��ı�־
	return m_isBottom;
}

bool CRussiaRectView::IsBottom2()
{
	//1.������Ϸ���ײ�,��ֹͣ�ƶ�,�õ��׵ı�־Ϊtrue,������
	if(position2.x >= m_iRow-1)
	{
		//MessageBox("1");
		m_isBottom2 = true;
		position2.x = m_iRow-1;

		sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
		return m_isBottom2;
	}
	//2.����û�е�����Ϸ���ײ�,������½���ײ����
	//2.1 ���ԭ��״�ڵ�ͼ�е�ӳ��
	ShapeInMap2(m_iCurrentShape2,0);
	//2.2 �ж���״����һ��λ�ú�,�Ƿ��з����������λ���ѱ�ռ��
	for(int ii=0 ; ii < 4 ; ii++)
	{
		//2.3 ������κ�һ����ռ��,��˵���·��з����赲
		if(gamestatusmap2[position2.x+1+shape[m_iCurrentShape2].Y[ii]][position2.y+shape[m_iCurrentShape2].X[ii]].status == 1)
		{
			//2.4 �õ��׵ı�־Ϊtrue
			m_isBottom2 = true;				
			//2.5 �޸Ļָ�ԭ��״�ڵ�ͼ�е�ӳ��
			ShapeInMap2(m_iCurrentShape2,1);
			//2.6 ������ײ����Ч
			sndPlaySound(".\\zhuangdi.WAV",SND_ASYNC);
			//2.7 �����ѵ��ײ��ı�־
			return m_isBottom2;							
		}
	}
	//3. û�������,�򷽿�û�е���ײ�,�õ��ױ�־Ϊfalse
	m_isBottom2 = false;	
	//4. �ָ������ڵ�ͼ�е�λ��
	ShapeInMap2(m_iCurrentShape2,1);
	//5. ���ص���ײ��ı�־
	return m_isBottom2;
}

////////////////////////////////////
//void InvalidateCurrent()
//������������ɵķ�������,��ֹȫ��������ɵ���Ļ����
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
//������������ɵķ�������,��ֹȫ��������ɵ���Ļ����
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
//������״�ڵ�ͼ�����е�״̬
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
	//��Ϸ������û�����������ʱ����ʾ�ò˵�
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
//�Ѷ�ѡ��
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
//DEL 	//���������ַ������壬������Ϣ���滺�壬���ŵ��ļ���
//DEL 	char szCmdBuf[300],errBuf[60],szfileName[255];
//DEL 	//������
//DEL 	MCIERROR mciError;
//DEL 
//DEL 	//��ʼ���豸Ԫ��
//DEL 	strcpy(szfileName,"music2_XJ.mid"); 
//DEL 	//��ʼ�������ַ���
//DEL 	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
//DEL 	//���豸
//DEL 	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
//DEL 	if (mciError == 0)
//DEL 	{//����򿪳ɹ��򲥷�
//DEL 		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
//DEL 		//���ݲ��Ų����Ƿ�ɹ������Ƿ�ر��豸
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
//�õ���ǰ�ķ���,������ȥ������
int CRussiaRectView::GetDecreaseRow()
{
	int DecreaseRow = 0 ;

	//1. �ж��Ƿ��ѵ÷�
	for (int i=0;i<m_iRow;i++)
	{
		//1.1 ����� i ����
		m_bIsFull = true;		
		//1.2 �Ե� i �н��м��
		for (int j=0;j<m_iCol;j++)
			//1.3 ��������һ��Ϊ�յ�
			if (gamestatusmap[i][j].status == 0)	
			{
				//1.3.1 �������Ϊ��
				m_bIsFull = false;	
				//1.3.2 �����˳�����ѭ��
				break;					
			}
		//1.4 ������������
		if(m_bIsFull == true) 
		{
			//1.4.1 ��ȥ�� i ��
			for (int k=i;k>0;k--)
				for (j=0;j<m_iCol;j++)
				{
					//�����Ӹ������������һ��,ÿ�е�״̬��Ϊ������һ�е�״̬
					gamestatusmap[k][j].status = gamestatusmap[k-1][j].status;
					gamestatusmap[k][j].color = gamestatusmap[k-1][j].color;
				}

			//1.4.2 ������һ���ÿ�
			for (j=0;j<m_iCol;j++)
				gamestatusmap[0][j].status = 0;
			//1.4.3 ���ٵ������� 1
			DecreaseRow++;
		}		
	}
	//2. ����ȥ�������� 0  
	if(DecreaseRow > 0)
	{
		//2.1 ͳ�Ʒ���
		m_iScore += (DecreaseRow + 1) * DecreaseRow * 100 / 2;
		//2.2 ���ݷ������ĵȼ�
		if(m_iScore >= (m_iLevel+1)* m_iLevel* 100 * 3)
		{
			m_iLevel++;
			SetTimer(1,1600-250*m_iLevel,NULL);	
		}
		sndPlaySound(".\\xiaoqu.wav",SND_ASYNC);		//���е�����
		//2.3 ������ͼ
		InvalidateCurrent();
		//2.4 ������ȥ������	
		return DecreaseRow ;
	}
	//3. ����û����ȥ����
	return 0 ;
}

//////////////////////////////
//int GetDecreaseRow2()
//�õ���ǰ�ķ���,������ȥ������
int CRussiaRectView::GetDecreaseRow2()
{
	int DecreaseRow2 = 0 ;

	//1. �ж��Ƿ�����������
	for (int i=0;i<m_iRow;i++)
	{
		//1.1 ����� i ����
		m_bIsFull2 = true;		
		//1.2 �Ե� i �н��м��
		for (int j=0;j<m_iCol;j++)
			//1.3 ��������һ��Ϊ�յ�
			if (gamestatusmap2[i][j].status == 0)	
			{
				//1.3.1 �������Ϊ��
				m_bIsFull2 = false;	
				//1.3.2 �����˳�����ѭ��
				break;					
			}
		//1.4 ������������
		if(m_bIsFull2 == true) 
		{
			//1.4.1 ��ȥ�� i ��
			for (int k=i ; k>0 ; k--)
				for (j=0 ; j<m_iCol ; j++)
				{
					//�����Ӹ������������һ��,ÿ�е�״̬��Ϊ������һ�е�״̬
					gamestatusmap2[k][j].status = gamestatusmap2[k-1][j].status;
					gamestatusmap2[k][j].color = gamestatusmap2[k-1][j].color;
				}

			//1.4.2 ������һ���ÿ�
			for (j=0 ; j<m_iCol ; j++)
				gamestatusmap2[0][j].status = 0;
			//1.4.3 ���ٵ������� 1
			DecreaseRow2++;
		}		
	}
	//2. ����ȥ�������� 0  
	if(DecreaseRow2 > 0)
	{
		//2.1 ͳ�Ʒ���
		m_iScore2 += (DecreaseRow2 + 1) * DecreaseRow2 * 100 / 2;
		//2.2 ���ݷ������ĵȼ�
		if(m_iScore2 >= (m_iLevel2+1)* m_iLevel2* 100 * 2)
		{
			m_iLevel2++;
			SetTimer(2,1600-250*m_iLevel2,NULL);	
		}
		//2.3 ������ͼ
		InvalidateCurrent2();
		//2.4 ������ȥ������	
		return DecreaseRow2 ;
	}
	//3. ����û����ȥ����
	return 0 ;
}


/////////////////////////////////
//int GetHeight()
//�õ���Ϸ�з�������ĸ߶�
int CRussiaRectView::GetHeight()
{
	//1. �ó�ֵ
	int temp = m_iRow ;
	//2. �����ҶԸ��н����ж�
	for (int i=0 ; i<m_iCol ; i++)
	{
		//2.1 ÿ�е�״̬���������ϵ�˳������ж�
		for (int j=m_iRow ; j>0 ; j--)
			//2.2 �����е� j ��Ϊ��,����ֵС��temp
			if (gamestatusmap[j][i].status == 1 && temp > j)	
				//2.3 ����ֵ����temp
				temp = j;		
	}

	return m_iRow-temp;
}

/////////////////////////////////
//int GetHeight2()
//�õ���Ϸ�з�������ĸ߶�
int CRussiaRectView::GetHeight2()
{
	//1. �ó�ֵ
	int temp2 = m_iRow ;
	//2. �����ҶԸ��н����ж�
	for (int i=0 ; i<m_iCol ; i++)
	{
		//2.1 ÿ�е�״̬���������ϵ�˳������ж�
		for (int j=m_iRow ; j>0 ; j--)
			//2.2 �����е� j ��Ϊ��,����ֵС��temp
			if (gamestatusmap2[j][i].status == 1 && temp2 > j)	
				//2.3 ����ֵ����temp
				temp2 = j;		
	}

	return m_iRow-temp2;
}

////////////////////////////////////
//void GameInitial()
//���к���Ϸ��ʼ�йص����ݳ�ʼ������
void CRussiaRectView::GameInitial()
{	
	m_iScore = 0;						//�ܷ�ֵ����
	m_iScore2 = 0;
	m_iTotalRow = 0;					//��ȥ������������
	m_iTotalRow2 = 0;
	m_iRectHeight = 0;					//��Ϸ���з����ۼӵĸ߶�
	m_iRectHeight2 = 0;

	position.x = 0;						//�����״��(0,0)�����ڵ�ͼ�е���������
	position.y = 4;						//�����״��(0,0)�����ڵ�ͼ�еĺ�������
	position2.x = 0;					//�Ҳ���״��(0,0)�����ڵ�ͼ2�е���������
	position2.y = 4;					//�Ҳ���״��(0,0)�����ڵ�ͼ2�еĺ�������

	m_iCurrentShape = Random(19,107);		//�����Ϸ����ǰ��״������	
	m_iCurrentShape2 = Random(19,131);		//�Ҳ���Ϸ����ǰ��״������
	m_iNextShape = Random(19,251);			//�����Ϸ������һ����״������	
	m_iNextShape2 = Random(19,379);			//�Ҳ���Ϸ������һ����״������	

	m_isBottom = false;					//���ȱʡΪû�е���ײ�
	m_isBottom2 = false;				//�Ҳ�ȱʡΪû�е���ײ�

	m_bIsFull = true;					//�ײ�������
	m_bIsFull2 = true;

	//����ͼ��״̬����
	for (int i=0;i<MAP_ROW;i++)
		for (int j=0;j<MAP_COL;j++)
		{
			gamestatusmap[i][j].status = 0;
			gamestatusmap2[i][j].status = 0;
		}
}

////////////////////////////////
//void GameOver()
//��Ϸʧ�ܽ���
void CRussiaRectView::GameOver()
{
	KillTimer(1);
	if(!m_bOnePlayer)KillTimer(2);	

	sndPlaySound(".\\fail.wav",SND_ASYNC);

	if(MessageBox("��Ϸ����!!!") == 1)
	{
		OnGameEnd() ;
	}
}

/////////////////////////////////
//OnUserHelp() 
//��ʾ������ʾ�Ի���
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
//����ѡ��ı�������
void CRussiaRectView::PlayMusic(CString str)
{
	m_bMusic = true;
	HWND hWnd;
	hWnd = GetSafeHwnd();
	//���������ַ������壬������Ϣ���滺�壬���ŵ��ļ���
	char szCmdBuf[300],errBuf[60],szfileName[255];
	//������
	MCIERROR mciError;

	//��ʼ���豸Ԫ��
	strcpy(szfileName,str); 
	//��ʼ�������ַ���
	wsprintf( szCmdBuf,"open %s type sequencer alias bkMusic",szfileName);
	//���豸
	mciError = mciSendString( szCmdBuf, errBuf, sizeof(errBuf), NULL);
	if (mciError == 0)
	{	//����򿪳ɹ��򲥷�
		mciError = mciSendString("play bkMusic notify",NULL,0, hWnd);
		//���ݲ��Ų����Ƿ�ɹ������Ƿ�ر��豸
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
