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
	void ShowAllCards();		//ī�� Ȯ��, ���
public:
	
	TrumpCard();				//ī��,ī����� ����
	void shuffle();				//ī�� �����Լ�
	int getorder();				//order[52] �� ��ȯ, �Ź� ���ο� ���� ����
	void TestProtectedFunc();	//�׽�Ʈ�� �Լ�
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
		int score;						//�� ���ھ�
		
		int cardslot[10];				//ī�彽��
		int carddeal[10];				//�������ִ� ī���� ��
		int acecount = 0;				//���̽� ����
		int condition = 0;				//Ư�����ǽ��� �ڵ�
	}player,dealer;
protected:
	
	
	//ī���� ������ġ 0-9�� �Է¹޾� �ش� ī���� ���� ��ȯ
	int get_carddeal(int cardorder);
	//ī�� ������ �Է�ĳ���Ϳ� �й�
	void get_card(charinfo&playerdealer);


	//ĳ���Ϳ� ������ �Է¹޾� acecount�� ���� ������ �Ǻ�
	void count_ace(int cardorder, charinfo& playerdealer);
	//���ھ ���
	void load_score(charinfo &playerdealer);		
	//��ð�� ����ǰ� ��������������� ����
	void cheak_special_condition(int cardorder,charinfo &playerdealer);	
	//�¸� Ǫ�� �й� �⺻������� ����
	void load_normal_conditon();


	//

public:
	//������
	BlackJack();
	//�׽�Ʈ�� �Լ�
	void TestProtectedFunc();
	//������ ���� ��Ʈ��
	void stream();
};



#endif // !_CLASS_H_
