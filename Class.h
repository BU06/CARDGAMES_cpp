#include "basic.h"
#ifndef _CLASS_H_
#define _CLASS_H_

enum choice {a,b,c};

class BasicOrder {
public:
	void swap_int(int& num1, int& num2);
};
class TrumpCard {
private:
	BasicOrder Trumpcard_bs;
	int order[52];				//카드 순서 배열 0~51
	int order_count;			//카드 순서 배열에서 카드를 뽑은 횟수
	struct CardSlot				//카드 덱 정보 구조체
	{
		char cardnumber[10];	//카드숫자
		char cardshape[10];		//카드문양				
	}slot[52];					//카드덱의 카드개수는 52개, 0~51
protected:
	int getorder();				//order[52] 를 순환, 매번 새로운 오더 생성
	void shuffle();				//카드 셔플함수
	void ShowAllCards();		//카드 확인, 출력
public:
	TrumpCard();				//카드,카드순서 세팅
	void TestProtectedFunc();	//테스트용 함수
};

class BlackJack : TrumpCard{
private:
	TrumpCard deck;
	enum result { DEFAULT = 0, DEALERCONTINUE = 16, BUST = 22, BLACKJACK = 21 };
	int pasecount;
	struct charinfo{
		int score;					//총 스코어
		
		int cardslot[10];	//카드슬롯
		int carddeal[10];			//가지고있는 카드의 딜
		int acecount = 0;				//에이스 보유
		int condition = 0;				//특수조건승패 코드
	}player,dealer;
protected:
	
	void getcondition(int cardorder,charinfo &playerdealer);
	void conditionresult();
	void countace(int cardorder, charinfo& playerdealer);
	void loadscore();
public:
	BlackJack();
	void TestProtectedFunc();

};



#endif // !_CLASS_H_
