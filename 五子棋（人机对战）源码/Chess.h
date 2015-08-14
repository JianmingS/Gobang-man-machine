// Chess.h: interface for the CChess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESS_H__4C86C50F_92F7_4C8B_B48B_C7DC0567FFC3__INCLUDED_)
#define AFX_CHESS_H__4C86C50F_92F7_4C8B_B48B_C7DC0567FFC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct pos
{
	int x,y;
	int flag;
};

class CChess : public CWnd  
{
public:
	void SetDc(CDC*,CDC*);   //���û�ͼdc
	void ReDraw();           //�ػ�����
	void NewGame(int);       //����Ϸ
	void BackGo();           //����
	bool DownZi(int nx,int ny,int type,HWND hwnd); //�ⲻ���ô˺�������
	CChess();
	virtual ~CChess();
private:
	CDC *dc,*qp;
	char m_board[15][15];					//��������
	pos posinfo[225];						//������Ϣ���飬���ڻ��庯��
	int posflag;							//������Ϣ�����±�
	void DrawQz(int nx,int ny,int type=0);//������
	void DrawQp();							//������
	int PanYing(int nx,int ny);           //�ж���Ӯ
	int m_turn;								//�������
	int m_flag;								//��Ӯ��־��1�ף�2��
	void AiGo(int &,int &);              //������AI
	bool ForbiddenCheck(char board[15][15], int x, int y, HWND hwnd);
	bool KeyPointForbiddenCheck(char board[15][15], int x, int y, int adjsame, int direction, HWND hwnd);
	void Get(char board[15][15]);
};

#endif // !defined(AFX_CHESS_H__4C86C50F_92F7_4C8B_B48B_C7DC0567FFC3__INCLUDED_)
