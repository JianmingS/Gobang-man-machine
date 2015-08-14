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
	void SetDc(CDC*,CDC*);   //设置绘图dc
	void ReDraw();           //重画函数
	void NewGame(int);       //新游戏
	void BackGo();           //悔棋
	bool DownZi(int nx,int ny,int type,HWND hwnd); //外不调用此函数下子
	CChess();
	virtual ~CChess();
private:
	CDC *dc,*qp;
	char m_board[15][15];					//棋盘数组
	pos posinfo[225];						//下子信息数组，用于悔棋函数
	int posflag;							//下子信息数组下标
	void DrawQz(int nx,int ny,int type=0);//画棋子
	void DrawQp();							//画棋盘
	int PanYing(int nx,int ny);           //判断输赢
	int m_turn;								//下棋次序
	int m_flag;								//输赢标志，1白，2黑
	void AiGo(int &,int &);              //五子棋AI
	bool ForbiddenCheck(char board[15][15], int x, int y, HWND hwnd);
	bool KeyPointForbiddenCheck(char board[15][15], int x, int y, int adjsame, int direction, HWND hwnd);
	void Get(char board[15][15]);
};

#endif // !defined(AFX_CHESS_H__4C86C50F_92F7_4C8B_B48B_C7DC0567FFC3__INCLUDED_)
