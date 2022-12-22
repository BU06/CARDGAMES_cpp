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
	void ShowAllCards();		//카드 확인, 출력
public:
	
	TrumpCard();				//카드,카드순서 세팅
	void shuffle();				//카드 셔플함수
	int getorder();				//order[52] 를 순환, 매번 새로운 오더 생성
	void TestProtectedFunc();	//테스트용 함수
};

class BlackJack : TrumpCard{
private:
	TrumpCard deck;
	enum condition { 
		DEFAULT = 0
		
		,DEALERCONTINUE = 16
		
		,BUST = 22
		,BLACKJACK = 21

		,WIN =1
		,PUSH = 100
		,LOSE=2
	};
	int pasecount;
	struct charinfo{
		int score;						//총 스코어
		
		int cardslot[10];				//카드슬롯
		int carddeal[10];				//가지고있는 카드의 딜
		int acecount = 0;				//에이스 보유
		int condition = 0;				//특수조건승패 코드
	}player,dealer;
protected:
	
	
	//카드의 슬롯위치 0-9를 입력받아 해당 카드의 딜을 반환
	int get_carddeal(int cardorder);
	//카드 한장을 입력캐릭터에 분배
	void get_card(charinfo&playerdealer);


	//캐릭터와 슬롯을 입력받아 acecount의 값을 더할지 판별
	void count_ace(int cardorder, charinfo& playerdealer);
	//스코어를 계산
	void load_score(charinfo &playerdealer);		
	//즉시결과 컨디션과 딜러진행컨디션을 얻음
	void cheak_special_condition(int cardorder,charinfo &playerdealer);	
	//승리 푸시 패배 기본컨디션을 얻음
	void load_normal_conditon();


	//

public:
	//생성자
	BlackJack();
	//테스트용 함수
	void TestProtectedFunc();
	//블랙잭의 메인 스트림
	void stream();
};



#endif // !_CLASS_H_
