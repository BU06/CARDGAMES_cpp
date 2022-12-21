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
	int order[52];				//ī�� ���� �迭 0~51
	int order_count;			//ī�� ���� �迭���� ī�带 ���� Ƚ��
	struct CardSlot				//ī�� �� ���� ����ü
	{
		char cardnumber[10];	//ī�����
		char cardshape[10];		//ī�幮��				
	}slot[52];					//ī�嵦�� ī�尳���� 52��, 0~51
protected:
	int getorder();				//order[52] �� ��ȯ, �Ź� ���ο� ���� ����
	void shuffle();				//ī�� �����Լ�
	void ShowAllCards();		//ī�� Ȯ��, ���
public:
	TrumpCard();				//ī��,ī����� ����
	void TestProtectedFunc();	//�׽�Ʈ�� �Լ�
};

class BlackJack : TrumpCard{
private:
	TrumpCard deck;
	enum result { DEFAULT = 0, DEALERCONTINUE = 16, BUST = 22, BLACKJACK = 21 };
	int pasecount;
	struct charinfo{
		int score;					//�� ���ھ�
		
		int cardslot[10];	//ī�彽��
		int carddeal[10];			//�������ִ� ī���� ��
		int acecount = 0;				//���̽� ����
		int condition = 0;				//Ư�����ǽ��� �ڵ�
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
