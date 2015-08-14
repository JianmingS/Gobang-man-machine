// Chess.cpp: implementation of the CChess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "������.h"
#include "Chess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChess::CChess()
{
	memset(m_board,0,sizeof(m_board));
	m_turn=1;
	m_flag=0;
	posflag=0;
}

CChess::~CChess()
{

}

void CChess::SetDc(CDC* tqp, CDC *qz)
{
	qp=tqp;
	dc=qz;
}

void CChess::NewGame(int type)
{
	memset(m_board,0,sizeof(m_board));
	m_flag=0;
	m_turn=1;
	posflag=0;
	if(type==0){m_board[7][7]=1;m_turn=2;
	posinfo[posflag].x=7;posinfo[posflag].y=7;posinfo[posflag].flag=2;
	posflag++;}
	ReDraw();
}

void CChess::DrawQp()
{
	dc->BitBlt(0,0,446,446,qp,0,0,SRCCOPY);
}

void CChess::DrawQz(int nx,int ny,int type)
{
	if(type==0)
	{
		if(m_turn==1){dc->Ellipse(nx*29+7,ny*29+7,nx*29+34,ny*29+34);
			posinfo[posflag].x=nx;
			posinfo[posflag].y=ny;
			posinfo[posflag].flag=m_turn;
			posflag++;
		}
		else
		{
			CBrush *brush;
			CBrush brush1(RGB(0,0,0));
			brush=dc->SelectObject(&brush1);
			dc->Ellipse(nx*29+7,ny*29+7,nx*29+34,ny*29+34);
			posinfo[posflag].x=nx;
			posinfo[posflag].y=ny;
			posinfo[posflag].flag=m_turn;
			posflag++;
			dc->SelectObject(brush);
		}
	}
	else if(type==1)
	{
		dc->Ellipse(nx*29+7,ny*29+7,nx*29+34,ny*29+34);
		posinfo[posflag].x=nx;
		posinfo[posflag].y=ny;
		posinfo[posflag].flag=m_turn;
		posflag++;
	}
	else
	{
		CBrush *brush;
		CBrush brush1(RGB(0,0,0));
		brush=dc->SelectObject(&brush1);
		dc->Ellipse(nx*29+7,ny*29+7,nx*29+34,ny*29+34);
		posinfo[posflag].x=nx;
		posinfo[posflag].y=ny;
		posinfo[posflag].flag=m_turn;
		posflag++;
		dc->SelectObject(brush);
	}
}

void CChess::ReDraw()
{
	DrawQp();
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			if(m_board[i][j]==1){DrawQz(j,i,1);}
			if(m_board[i][j]==2){DrawQz(j,i,2);}
		}
}

bool CChess::DownZi(int nx, int ny,int type,HWND hwnd)
{
	int x,y;
	if(nx<0||nx>14||ny<0||ny>14) 
	{
		::MessageBox(hwnd,"����ȷ������λ��!", NULL,MB_OK);
		return false;
	}
	char board[15][15];
	Get(board);
	if (1==m_turn && !ForbiddenCheck(board, ny, nx, hwnd))
	{
		::MessageBox(hwnd,"����!", NULL,MB_OK);
		return false;
	}
	if(CChess::m_flag!=0)//�ѷֳ�ʤ��
	{
		if(m_flag==1){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
		else{::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
	}
	if(m_board[ny][nx]==0)
	{
		if(type==2)//���˶�ս
		{
			m_board[ny][nx]=m_turn;
			DrawQz(nx,ny);
			m_flag=PanYing(nx,ny);
			m_turn=(m_turn==1?2:1);
			if(m_flag==1){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			if(m_flag==2){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			return true;
		}
		else //�˻���ս
		{
			m_board[ny][nx]=m_turn;
			DrawQz(nx,ny);
			m_flag=PanYing(nx,ny);
			m_turn=(m_turn==1?2:1);
			if(m_flag==1){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			if(m_flag==2){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			CChess::AiGo(x,y);
			m_board[y][x]=m_turn;
			DrawQz(x,y);
			m_flag=PanYing(x,y);
			m_turn=(m_turn==1?2:1);
			if(m_flag==1){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			if(m_flag==2){::MessageBox(hwnd,"�����ʤ!", NULL,MB_OK);return true;}
			return true;
		}
		
	}
	return false;
}

void CChess::BackGo()
{
	m_board[posinfo[posflag-1].y][posinfo[posflag-1].x]=0;
	ReDraw();
}

int CChess::PanYing(int nx, int ny)
{
	int count=0;
	for(int i=-4;i<5;i++)
	{
		if(m_board[ny][nx+i]==m_turn) {count++;if(count==5) return m_turn;}
		else count=0;
	}
	count=0;
	for(i=-4;i<5;i++)
	{
		if(m_board[ny+i][nx]==m_turn) {count++;if(count==5) return m_turn;}
		else count=0;
	}
	count=0;
	for(i=-4;i<5;i++)
	{
		if(m_board[ny+i][nx+i]==m_turn) {count++;if(count==5) return m_turn;}
		else count=0;
		
	}
	count=0;
	for(i=-4;i<5;i++)
	{
		if(m_board[ny+i][nx-i]==m_turn) {count++;if(count==5) return m_turn;}
		else count=0;
	}
	count=0;
	return 0;
}

void CChess::AiGo(int& t, int &h)
{
	int qiju[2][15][15][8][2]={0};     /* ��������*/
	int k,i,j,q,b=0,a=1,d,y1=0,y2=0,x1=0,x2=0;
	int a1[15][15]={0},a2[15][15]={0};
	/****************Ϊ˫����д���ͱ�************/
	for(k=0;k<2;k++)
		for(i=0;i<15;i++)
			for(j=0;j<15;j++)
			{
				if(m_board[i][j]==0)
				{
					for(q=0;q<8;q++)
					{
						if(k==0) d=1;
						else d=2;
						if(q==0&&j>=0)
						{
							for(;j-a>=0;)   // ��
							{
								if(m_board[i][j-a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i][j-a]==0&&j-a>=0){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==1&&i>=0&&j>=0)  // ����
						{
							for(;i-a>=0&&j-a>=0;)
							{
								if(m_board[i-a][j-a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i-a][j-a]==0&&j-a>=0&&i-a>=0){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==2&&i>=0)   // ��
						{
							for(;i-a>=0;)
							{
								if(m_board[i-a][j]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i-a][j]==0&&i-a>=0){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==3&&i>=0&&j<15)   // ����
						{
							for(;i-a>=0&&j+a<15;)   
							{
								if(m_board[i-a][j+a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i-a][j+a]==0&&i-a>=0&&j+a<15){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==4&&j<15)     // ��
						{
							for(;j+a<15;)
							{
								if(m_board[i][j+a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i][j+a]==0&&j+a<15){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==5&&i<15&&j<15)
						{
							for(;i+a<15&&j+a<15;)   // ����
							{
								if(m_board[i+a][j+a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i+a][j+a]==0&&i+a<15&&j+a<15){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==6&&i<15)
						{
							for(;i+a<15;)   // ��
							{
								if(m_board[i+a][j]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i+a][j]==0&&i+a<15){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
						if(q==7&&j>=0&&i<15)   // ����
						{
							for(;i+a<15&&j-a>=0;)
							{
								if(m_board[i+a][j-a]==d){b++;a++;continue;}
								else break;
							}
							qiju[k][i][j][q][0]=b;b=0;
							if(m_board[i+a][j-a]==0&&i+a<15&&j-a>=0){qiju[k][i][j][q][1]=1;a=1;}
							else {qiju[k][i][j][q][1]=0;a=1;}
						}
					}
				}
			}
			/******************�������ֹ����ÿһ���ո�����***************/
			for(k=0;k<2;k++)
				for(i=0;i<15;i++)
					for(j=0;j<15;j++)
					{
						if(k==0) /*Ϊ��������*/
						{
							for(q=0;q<4;q++)
							{
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4   
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=7000;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=301;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=43;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=11;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
									&&((qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0)))
									b+=7000;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=63;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=6;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=1;
							}
							if(b==126||b==189||b==252) b=1500;
							if(b==106) b=1000;
							
							a1[i][j]=b;b=0;
						}
						if(k==1)  /*Ϊ��������*/
						{
							for(q=0;q<4;q++)
							{
								
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=30000;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=1500;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=51;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
									&&qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==1)
									b+=16;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==4
									&&((qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0)))
									b+=30000;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==3
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=71;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==2
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=7;
								if((qiju[k][i][j][q][0]+qiju[k][i][j][q+4][0])==1
									&&((qiju[k][i][j][q][1]==1&&qiju[k][i][j][q+4][1]==0)
									||(qiju[k][i][j][q][1]==0&&qiju[k][i][j][q+4][1]==1)))
									b+=2;
							}
							if(b==142||b==213||b==284) b=1500;
							if(b==122) b=1300;
							
							a2[i][j]=b;b=0;
						}
					}
					/****************���������ߵĿ�λ����д����*********************/
					for(i=0;i<15;i++)
						for(j=0;j<15;j++)
						{
							if(a1[y1][x1]<a1[i][j]) {y1=i;x1=j;}
						}
					for(i=0;i<15;i++)
						for(j=0;j<15;j++)
						{
							if(a2[y2][x2]<a2[i][j]) {y2=i;x2=j;}
						}
					if(a2[y2][x2]>=a1[y1][x1]) {t=x2;h=y2;}
					else {t=x1;h=y1;}
}


bool CChess::ForbiddenCheck(char board[15][15], int y, int x, HWND hwnd)
{

	int i;
	int adjsame[8];  // ��¼��(x, y)����������ɫ��������
	int adjempty[8]; // ��¼adjsame������������λ��
	int jumpsame[8];  // ��¼adjempty������������ɫ������
	int jumpempty[8];  // ��¼jumpsame���λ��
	int jumpjumpsame[8]; // ��¼��jumpempty������ɫ������
	//��ʼ��
	for (i=0; i<8; i++)
	{
		adjsame[i] = adjempty[i] = jumpsame[i] = 0;
		jumpempty[i] = jumpjumpsame[i] = 0;
	}
	board[y][x] = 1;

	// ����
	int _x, _y;
	// ��
	for (_y = y - 1; _y >= 0 && 1 == board[_y][x]; _y--, adjsame[0]++);
	for (; _y >= 0 && 0 == board[_y][x]; _y--, adjempty[0]++);
	for (; _y >= 0 && 1 == board[_y][x]; _y--, jumpsame[0]++);
	for (; _y >= 0 && 0 == board[_y][x]; _y--, jumpempty[0]++);
	for (; _y >= 0 && 1 == board[_y][x]; _y--, jumpjumpsame[0]++);

	// ����
	for (_x = x + 1, _y = y - 1; _x < 15 && _y >= 0 && 1 == board[_y][_x]; _x++, _y--, adjsame[1]++);
	for (; _x < 15 && _y >= 0 && 0 == board[_y][_x]; _x++, _y--, adjempty[1]++);
	for (; _x < 15 && _y >= 0 && 1 == board[_y][_x]; _x++, _y--, jumpsame[1]++);
	for (; _x < 15 && _y >= 0 && 0 == board[_y][_x]; _x++, _y--, jumpempty[1]++);
	for (; _x < 15 && _y >= 0 && 1 == board[_y][_x]; _x++, _y--, jumpjumpsame[1]++);

	// ��
	for (_x = x + 1; _x < 15 && 1 == board[y][_x]; _x++, adjsame[2]++);
	for (; _x < 15 && 0 == board[y][_x]; _x++, adjempty[2]++);
	for (; _x < 15 && 1 == board[y][_x]; _x++, jumpsame[2]++);
	for (; _x < 15 && 0 == board[y][_x]; _x++, jumpempty[2]++);
	for (; _x < 15 && 1 == board[y][_x]; _x++, jumpjumpsame[2]++);

	// ����
	for (_x = x + 1, _y = y + 1; _x < 15 && _y < 15 && 1 == board[_y][_x]; _x++, _y++, adjsame[3]++);
	for (; _x < 15 && _y < 15 && 0 == board[_y][_x]; _x++, _y++, adjempty[3]++);
	for (; _x < 15 && _y < 15 && 1 == board[_y][_x]; _x++, _y++, jumpsame[3]++);
	for (; _x < 15 && _y < 15 && 0 == board[_y][_x]; _x++, _y++, jumpempty[3]++);
	for (; _x < 15 && _y < 15 && 1 == board[_y][_x]; _x++, _y++, jumpjumpsame[3]++);

	// ��
	for (_y = y + 1; _y < 15 && 1 == board[_y][x]; _y++, adjsame[4]++);
	for (; _y < 15 && 0 == board[_y][x]; _y++, adjempty[4]++);
	for (; _y < 15 && 1 == board[_y][x]; _y++, jumpsame[4]++);
	for (; _y < 15 && 0 == board[_y][x]; _y++, jumpempty[4]++);
	for (; _y < 15 && 1 == board[_y][x]; _y++, jumpjumpsame[4]++);
	// ����
	for (_x = x - 1, _y = y + 1; _x >= 0 && _y < 15 && 1 == board[_y][_x]; _x--, _y++, adjsame[5]++);
	for (; _x >= 0 && _y < 15 && 0 == board[_y][_x]; _x--, _y++, adjempty[5]++);
	for (; _x >= 0 && _y < 15 && 1 == board[_y][_x]; _x--, _y++, jumpsame[5]++);
	for (; _x >= 0 && _y < 15 && 0 == board[_y][_x]; _x--, _y++, jumpempty[5]++);
	for (; _x >= 0 && _y < 15 && 1 == board[_y][_x]; _x--, _y++, jumpjumpsame[5]++);
	// ��
	for (_x = x - 1; _x >= 0 && 1 == board[y][_x]; _x--, adjsame[6]++);
	for (; _x >= 0 && 0 == board[y][_x]; _x--, adjempty[6]++);
	for (; _x >= 0 && 1 == board[y][_x]; _x--, jumpsame[6]++);
	for (; _x >= 0 && 0 == board[y][_x]; _x--, jumpempty[6]++);
	for (; _x >= 0 && 1 == board[y][_x]; _x--, jumpjumpsame[6]++);
	// ����
	for (_x = x - 1, _y = y - 1; _x >= 0 && _y >=0 && 1 == board[_y][_x]; _x--, _y--, adjsame[7]++);
	for (; _x >= 0 && _y > 0 && 0 == board[_y][_x]; _x--, _y--, adjempty[7]++);
	for (; _x >= 0 && _y > 0 && 1 == board[_y][_x]; _x--, _y--, jumpsame[7]++);
	for (; _x >= 0 && _y > 0 && 0 == board[_y][_x]; _x--, _y--, jumpempty[7]++);
	for (; _x >= 0 && _y > 0 && 1 == board[_y][_x]; _x--, _y--, jumpjumpsame[7]++);

	// --��������--
	board[y][x] = 0;
	/*
	// �����ж�
	for (i = 0; i < 4; i++)
	{
		
		if (4 == adjsame[i] + adjsame[i + 4])
		{
			//MessageBox(hwnd,"����!", NULL,MB_OK);
			return true;   // �޽��֣����´˴�����ʤ
		}
	}
	*/
	// ���ַ���
	int threecount = 0, fourcount = 0;

	for (i = 0; i < 4; i++)
	{
		if (adjsame[i] + adjsame[i + 4] >= 5)  // ������������, ��������
		{
			//MessageBox(hwnd,"��������!", NULL,MB_OK);
			return false;                           
		}
		else if (3 == adjsame[i] + adjsame[i + 4])  // �������� ?0000?
		{
			// ���ĳ����ж�
			bool isFour = false;
			if (adjempty[i] > 0) // ?+0000?
			{
				// ͨ���ݹ��жϹؼ����Ƿ����
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd)) // ���޽���
				{
					//MessageBox(hwnd,"��01����!", NULL,MB_OK);
					isFour = true;
				}
			}
			if (adjempty[i + 4] > 0) // ?0000+?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd)) // ���޽���
				{
					//MessageBox(hwnd,"��02����!", NULL,MB_OK);
					isFour = true;
				}
			}
			if (isFour)
			{
				//MessageBox(hwnd,"��asdgasgdhag����!", NULL,MB_OK);
				fourcount++;
			}
		}
		else if (2 == adjsame[i] + adjsame[i + 4]) // �������� ?000?
		{
			// ���ĳ��ļ��
			if (1 == adjempty[i] && 1 == jumpsame[i]) // ?0+000?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd))// ���޽���
				{
					fourcount++;
				}
			}
			if (1 == adjempty[i + 4] && 1 == jumpsame[i + 4])  // ?000+0?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd))// ���޽���
				{
					fourcount++;
				}
			}
			// �������
			bool isThree = false;

			// ?++000+?
			if ((adjempty[i] > 2 || adjempty[i] == 2 && jumpsame[i] == 0) &&
				(adjempty[i + 4] > 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd))// ���޽���
				{
					isThree = true;
				}
			}

			// ?+000++?
			if ((adjsame[i + 4] > 2 || adjempty[i + 4] == 2 && jumpsame[i + 4] == 0) &&
				(adjempty[i] > 1 || adjempty[i] == 1 && jumpsame[i] == 0))
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd))// ���޽���
				{
					isThree = true;
				}
			}
			if (isThree)
				threecount++;
		}
		else if (adjsame[i] + adjsame[i + 4] == 1)   // �������� ?00?
		{
			// ���ĳ����ж�
			if (1 == adjempty[i] && 2 == jumpsame[i])  // ?00+00?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd)) // ���޽���
				{
					fourcount++;
				}
			}
			if (1 == adjempty[i + 4] && 2 == jumpsame[i + 4])   // ?00+00?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd))  // ���޽���
				{
					fourcount++;
				}
			}
			// �����ж�
			if (1 == adjempty[i] && 1 == jumpsame[i] && (jumpempty[i] > 1
				|| 1 == jumpempty[i] && 0 == jumpjumpsame[i]) && (adjempty[i + 4] > 1
				|| 1 == adjempty[i + 4] && 0 == jumpsame[i + 4]))  // ?+0+00+?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd)) // ���޽���
				{
					threecount++;
				}
			}
			if (1 == adjempty[i + 4] && 1 == jumpsame[i + 4] && (jumpempty[i + 4] > 1
				|| 1 == jumpempty[i + 4] && 0 == jumpjumpsame[i + 4]) && (adjempty[i] > 1
				|| 1 == adjempty[i] && 0 == jumpsame[i]))  // ?+00+0+?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd)) // ���޽���
				{
					threecount++;
				}
			}
		}
		else if (0 == adjsame[i] + adjsame[i + 4])  // ����һ�� ?0?
		{
			// ���ĳ����ж�
			if (1 == adjempty[i] && 3 == jumpsame[i])  // ?000+0?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd)) // ���޽���
				{
					fourcount++;
				}
			}
			if (1 == adjempty[i + 4] && 3 == jumpsame[i + 4]) // 0+000
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd))  // ���޽���
				{
					fourcount++;
				}
			}
			// �����ж�
			if (1 == adjempty[i] && 2 == jumpsame[i] && (jumpempty[i] > 1
				|| 1 == jumpempty[i] && 0 == jumpjumpsame[i]) &&
				(adjempty[i + 4] > 1 || 1 == adjempty[i + 4] && 0 == jumpsame[i + 4]))  // ?+00+0+?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i], i, hwnd)) // ���޽���
				{
					threecount++;
				}
			}
			if (1 == adjempty[i + 4] && 2 == jumpsame[i + 4] && (jumpempty[i + 4] > 1
				|| 1 == jumpempty[i + 4] && 0 == jumpjumpsame[i + 4]) &&
				(adjempty[i] > 1 || 1 == adjempty[i] && 0 == jumpsame[i]))  // ?+0+00+?
			{
				if (KeyPointForbiddenCheck(board, x, y, adjsame[i + 4], i + 4, hwnd)) // ���޽���
				{
					threecount++;
				}
			}
		}
	}
	// --���ַ�������--
	if (fourcount > 1)
	{
		//MessageBox(hwnd,"���Ľ���!", NULL,MB_OK);
		return false;   // �γ�һ�����ϵĻ��ġ����ģ����Ľ���
	}
	else if (threecount > 1)
	{
		//MessageBox(hwnd,"��������!", NULL,MB_OK);
		return false;  // �γ�һ�����ϵĻ�������������
	}
	return true;  // �޽���
}

/*
�����в������ֱ�ʾ���򣬷����֣��˷������ķ���
�˷���
0�����ϣ� 1�����ϣ� 2���ң� 3������
4�����£� 5�����£� 6���� 7������
*/

bool CChess::KeyPointForbiddenCheck(char board[15][15], int x, int y, int adjsame, int direction, HWND hwnd)
/*
�жϵ�(x, y)�����������Ϲ��ɽ���
xΪ������꣬������
yΪ�������꣬������
*/
{
	int i, j;   // �ؼ�������(i, j)
	adjsame++;
	if (direction >= 4)
		adjsame = -adjsame;

	// ����ؼ�������
	switch (direction%4)
	{
	case 0:
		i = x;
		j = y - adjsame;
		break;
	case 1:
		i = x + adjsame;
		j = y - adjsame;
		break;
	case 2:
		i = x + adjsame;
		j = y;
		break;
	default:
		i = x + adjsame;
		j = y + adjsame;
		break;
	}
	// �������з�������
	board[y][x] = 1;
	board[j][i] = 1;

	// ���ؼ���
	bool result = ForbiddenCheck(board, j, i, hwnd);

	// ��ԭ����
	board[y][x] = 0;
	board[j][i] = 0;

	return result;
}

void CChess::Get(char board[15][15])
{
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			board[i][j] = m_board[i][j];
}