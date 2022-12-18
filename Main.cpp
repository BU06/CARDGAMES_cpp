// CARDGAMES_Cpp.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#define _CRT_SECURE_NO_WARNINGS

//�⺻
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <istream>


//���� Ĩ ��ȯ���
#define PUSH_prize 1
#define WIN_prize 2
#define LOSE_prize -1
#define BLACKJACK_prize 4
#define SURENDER_prize 0.5



using namespace std;

//����
namespace basic{
	//��ü---------------------------------------------------
	int chip,prize,bet;
	
	
	//&����������A,&����������B �� �޾� A�� B�� ���� �ٲٴ� �Լ�
	void swapint(int* num1, int* num2) {
		int temp = *num1;
		*num1 = *num2;
		*num2 = temp;
	} 

	//���� q w e r
	//    0 1 2 3
	int select_qwer() {
		
		int order;
		cin >> order;
		
		switch (order) 
		{
		case 113:
			
			return 0;
		case 119:
			return 1;
		case 101:
			return 2;
		case 114:
			return 3;
		default:
			return 5;;
		}
	}

	void chipsum(int x) {
		basic::chip = basic::bet * x;
		basic::prize = basic::bet - basic::chip;
	}
	//------------------------------------------------------
}

namespace Trump{
	//Ʈ����ī��

	// ���� �� ����ü
	int order[52];			  //ī�� ����(���������) �迭 0~51
	int ordercount;			  //ī�����Ƚ��
	struct CARD {              //ī�彽��
		char number[10];	  //ī�� ����,��ȣ [A,1,2,3,4,5,6,7,8,9,10,J,Q,K]
		char shape[10];		  //ī�� ���     [�����ߢ�]
		int deal;			  //����          [1,2,3,4,5,6,7,8,9,10,10,10,10]
	}card[52];                //ī�� ȣ��迭 0~51
	
	
	
	// �Լ�
	
	

	// ����ü CARD�� ������ ä��� �����Լ�(��)
	void card_set() {
		for (int i = 0; i < 52; i++) {
			if (0 <= i && i <= 12)
				strcpy(Trump::card[i].shape, "\u2665");
			else if (13 <= i && i <= 25)
				strcpy(Trump::card[i].shape, "��");
			else if (26 <= i && i <= 38)
				strcpy(Trump::card[i].shape, "\u2660");
			else if (39 <= i && i <= 51)
				strcpy(Trump::card[i].shape, "\u2663");
			else {
				cout << "ERROR : [main//trump//card_set()//-shape logic-���� �����߻�]" << endl << "���α׷� ����" << endl;
				exit(-1);
			}

			if ((i + 1) % 13 == 1) {
				strcpy(Trump::card[i].number, "A");
				Trump::card[i].deal = 1;
			}
			else if ((i + 1) % 13 == 2) {
				strcpy(Trump::card[i].number, "2");
				Trump::card[i].deal = 2;
			}
			else if ((i + 1) % 13 == 3) {
				strcpy(Trump::card[i].number, "3");
				Trump::card[i].deal = 3;
			}
			else if ((i + 1) % 13 == 4) {
				strcpy(Trump::card[i].number, "4");
				Trump::card[i].deal = 4;
			}
			else if ((i + 1) % 13 == 5) {
				strcpy(Trump::card[i].number, "5");
				Trump::card[i].deal = 5;
			}
			else if ((i + 1) % 13 == 6) {
				strcpy(Trump::card[i].number, "6");
				Trump::card[i].deal = 6;
			}
			else if ((i + 1) % 13 == 7) {
				strcpy(Trump::card[i].number, "7");
				Trump::card[i].deal = 7;
			}
			else if ((i + 1) % 13 == 8) {
				strcpy(Trump::card[i].number, "8");
				Trump::card[i].deal = 8;
			}
			else if ((i + 1) % 13 == 9) {
				strcpy(Trump::card[i].number, "9");
				Trump::card[i].deal = 9;
			}
			else if ((i + 1) % 13 == 10) {
				strcpy(Trump::card[i].number, "10");
				Trump::card[i].deal = 10;
			}
			else if ((i + 1) % 13 == 11) {
				strcpy(Trump::card[i].number, "J");
				Trump::card[i].deal = 10;
			}
			else if ((i + 1) % 13 == 12) {
				strcpy(Trump::card[i].number, "Q");
				Trump::card[i].deal = 10;
			}
			else if ((i + 1) % 13 == 0) {
				strcpy(Trump::card[i].number, "K");
				Trump::card[i].deal = 10;
			}
			else {
				cout << "ERROR : [main//trump::card_set()//-number&deal logic-���� �����߻�]" << endl << "���α׷� ����" << endl;
				exit(-1);
			}
		}
		for (int i = 0; i < 52; i++) {
			Trump::order[i] = i;
		}

	}

	// ī���� ������ ��Ÿ���� �迭 order[] �� ���� ������ ����(��)
	void card_shuffle() {
		int random_int;
		for (int i = 0; i < 52; i++) {
			random_int = rand() % 52;// = 0~51 ������ �ʱ�ȭ
			basic::swapint(&Trump::order[i], &Trump::order[random_int]);
			continue;
		}
	}

	// �����迭 order[]�� ��ȯ, �׸��� ī���ȣ ����(��)
	int getorder(int count) {
		if (Trump::ordercount > 51) {
			Trump::ordercount = 0;
			Trump::card_shuffle();
		}
		Trump::ordercount++;
		return(Trump::order[count]);
	}

	//order[] �迭�� ������� ī���� ������ Ȯ���ϱ�
	void card_cheak() {
		int order_val;
		for (int i = 0; i < 52; i++) {
			order_val = Trump::order[i];
			printf("%-2d : Order :%-2d Card : %s%-2s  Deal :%d \n", i, Trump::order[i], Trump::card[order_val].shape, Trump::card[order_val].number, Trump::card[order_val].deal);
		}
	}

	//�⺻ �ʱ⼳��
	void SimpleCardSet() {
		Trump::card_set();
		Trump::card_shuffle();
	}
	//------------------------------------------------------
}

namespace blackjack {
	//����
	
	
	
    int quit;//���� ���ν�Ʈ��  ��������
	
	int player_slot[7] = { 0 }, dealer_slot[7] = { 0 };//�÷��̾�� ������ ���� �������ִ� ī����� �� �迭
	
	int pase_count;//�� ��

	

    //interface
	namespace ui {
		

		
		//��ܸ޼���
		//������1,2,3
		void select(const char message[], const char selection1[], const char selection2[],const char selection3[]) {
			
			int countlogic1, countlogic2 , callinfo_1, callinfo_2;
			
			system("cls");

			//1
			cout << left << setw(1) << "|"; cout << left << setw(30) << "BlackJack   madeby bu"; cout << setw(15) << "| my chip : " << setw(6) << basic::chip; cout << right << setw(1) << "|" << endl;
			//2
			cout << left << setw(1) << "|"; cout << left << setw(51) << "==================================================="; cout << right << setw(1) << "|" << endl;
			//3
			cout << left << setw(1) << "|"; cout << left << setw(51) << message; cout << right << setw(1) << "|" << endl;
			//4
			cout << left << setw(1) << "|"; cout << left << setw(51) << "==================================================="; cout << right << setw(1) << "|" << endl;
			//5
			cout << left << setw(1) << "|"; cout << right << setw(15) << "Player" << right << setw(11) << "|"; cout << right << setw(15) << "Dealer"; cout << right << setw(11) << "|" << endl;
			//6
			cout << left << setw(1) << "|"; cout << left << setw(25) << "=========================" << setw(1) << "|"; cout << left << setw(25) << "========================="; cout << right << setw(1) << "|" << endl;
			//7
			cout << left << setw(1) << "|"; 
			
			if (pase_count >= 1) {
				

				cout << right << setw(8) << Trump::card[blackjack::player_slot[0]].shape <<left<< setw(2) << Trump::card[blackjack::player_slot[0]].number<< setw(5) << " " ;                                   
				if (pase_count >= 2)
					cout << right << setw(8) << Trump::card[blackjack::player_slot[1]].shape <<left<< setw(2) << Trump::card[blackjack::player_slot[1]].number;
				else
					cout << setw(9) << " ";
				cout <<right<< setw(3) << "|";
				cout << right << setw(8) << Trump::card[blackjack::dealer_slot[0]].shape << left << setw(2) << Trump::card[blackjack::dealer_slot[0]].number << setw(5) << " ";
				if (pase_count >= 2)
					cout << left << right << setw(8) << Trump::card[blackjack::dealer_slot[1]].shape << left << setw(2) << Trump::card[blackjack::dealer_slot[1]].number;
				else
					cout << setw(9) << " ";
			}
			else
				cout << right << setw(26) << "|" << setw(23) << " ";
			cout << right << setw(3) << "|" << endl;
			//8
			cout << left << setw(1) << "|"; cout << left << setw(25) << " " << setw(1) << "|"; cout << left << setw(25) << " "; cout << right << setw(1) << "|" << endl;
			//9   �����Ϸ�
			cout << left << setw(1) << "|";
			
			if (pase_count >= 3) {


				cout << right << setw(8) << Trump::card[blackjack::player_slot[2]].shape << left << setw(2) << Trump::card[blackjack::player_slot[2]].number << setw(5) << " ";
				if (pase_count >= 4)
					cout << right << setw(8) << Trump::card[blackjack::player_slot[3]].shape << left << setw(2) << Trump::card[blackjack::player_slot[3]].number;
				else
					cout << setw(9) << " ";

				cout << right << setw(3) << "|";
				cout << right << setw(8) << Trump::card[blackjack::dealer_slot[2]].shape<< left << setw(2) << Trump::card[blackjack::dealer_slot[2]].number << setw(5) << " ";
				if (pase_count >= 4)
					cout << left << right << setw(8) << Trump::card[blackjack::dealer_slot[3]].shape << left << setw(2) << Trump::card[blackjack::dealer_slot[3]].number;
				else
					cout << setw(9) << " ";
			}
			else
				cout << right << setw(26) << "|" << setw(23) << " ";
			cout << right << setw(3) << "|" << endl;

			//10
			cout << left << setw(1) << "|"; cout << left << setw(25) << " " << setw(1) << "|"; cout << left << setw(25) << " "; cout << right << setw(1) << "|" << endl;
			//11
			cout << left << setw(1) << "|";
			if (pase_count >= 5) {
				

				cout << right << setw(8) << Trump::card[blackjack::player_slot[4]].shape << left << setw(2) << Trump::card[blackjack::player_slot[4]].number << setw(5) << " ";
				if (pase_count >= 6)
					cout << left << right << setw(8) << Trump::card[blackjack::player_slot[5]].shape << left << setw(2) << Trump::card[blackjack::player_slot[5]].number;
				else
					cout << setw(9) << " ";
				cout <<right<< setw(3) << "|";
				cout << right << setw(8) << Trump::card[blackjack::dealer_slot[4]].shape << left << setw(2) << Trump::card[blackjack::dealer_slot[4]].number << setw(5) << " ";
				if (pase_count >= 6)
					cout << left << right << setw(8) << Trump::card[blackjack::dealer_slot[5]].shape << left << setw(2) << Trump::card[blackjack::dealer_slot[5]].number;
				else
					cout << setw(9) << " ";
			}
			else
				cout << right << setw(26) << "|" << setw(23) << " ";
			cout << right << setw(3) << "|"<<endl;
			//12
			cout << left << setw(1) << "|"; cout << left << setw(51) << "==================================================="; cout << right << setw(1) << "|" << endl;
			//13
			cout << left << setw(10) << "| Select : |"; cout << left << setw(10) << selection1 << left << setw(10) << selection2 << left << setw(15) << selection3; cout << right << setw(6) << "|" << endl;
			//14
			cout << left << setw(1) << "|"; cout << left << setw(51) << "==================================================="; cout << right << setw(1) << "|" << endl;

		}

		void push() {
			system("cls");
			
			cout << endl << setw(30) << "Push" << endl << endl << setw(35)<<"price : +" <<basic::prize;
		}
		void win() {
			system("cls");

			cout << endl << setw(30) << "Win" << endl << endl << setw(35) << "price : +" << basic::prize;
		}
		void lose() {
			system("cls");

			cout << endl << setw(30) << "Lose" << endl << endl << setw(35) << "price : +" << basic::prize;
		}
		void BLACKJACK() {
			system("cls");

			cout << endl << setw(30) << "Win" << endl << endl << setw(35) << "price : " << basic::prize;
		}
		void bet() {
			cout << endl << setw(30) << "����" << endl <<setw(26)<<"Ĩ :  "<<basic::chip << endl << endl << setw(35) << "�����ϼ��� : ";
		}
	};


	//���ھ� �Ǻ� �÷��̾��� �����԰� ������ ���������޾� ����� 
	// 0 : 21            => �׻� win + blackjack
	// 1 : ����<�÷��̾�  => ����� win
	// 2 : ����>21        => �׻� win
	// 3 : ����>�÷��̾�  => ����� lose
	// 4 : �÷��̾�>21     => �׻� lose 
	// 5 : �÷��̾�=����  => ����� tie
	int  result(int player_slot[],int dealer_slot[]) {
		int dealer_score = 0, player_score = 0;
		int dealer_deal, player_deal;
		int dealer_order, player_order;
		int playerAce = 0,dealerAce=0;
		for (int i = 0; i < 7; i++) {
			dealer_order = dealer_slot[i];
			player_order = player_slot[i];
			dealer_deal = Trump::card[dealer_order].deal;
			player_deal = Trump::card[player_order].deal;
			if (player_deal == 1)
				playerAce++;
			if (dealer_deal == 1)
				dealerAce++;
			player_score += player_deal;
			dealer_score += dealer_deal;
		}
		//���� �Ǻ�
		if (playerAce != 0) {
			if (player_score + 10 == 21)
				return 0;//BLACK JACK!
		}
		if (dealerAce != 0) {
			if (dealer_score + 10 == 21)
				return 4;//Dealer BLACK JACK  lose
		}
		//���� 21 �Ѱ峪?
		else if (dealer_score > 21) {
			return 2;//win
		}
		//�÷��̾� 21 �Ѱ峪?
		else if (player_score > 21) {
			return 4;//lose
		}
		else if (player_score == dealer_score)//�÷��̾�==����
				return 5;//tie
		//�÷��̾�>����
		else if (player_score > dealer_score) {										
			return 1;//win			
		}
		else if (player_score < dealer_score)
			return 3;//lose
		else {
			return 6;
		}
			
	}

	//�� ��
	//ī��й�, ����й�,��ý¸�,�����Ǻ�
	void pase() {
		int psn = blackjack::pase_count;

		blackjack::player_slot[psn] = Trump::getorder(Trump::ordercount);
		blackjack::dealer_slot[psn] = Trump::getorder(Trump::ordercount);
		
		
		blackjack::ui::select("ī�� ��ġ��...", "", "", "");
		Sleep(1500);

		switch (blackjack::result(player_slot, dealer_slot))
		{
		case 0:
			blackjack::ui::BLACKJACK();
			blackjack::quit++;			
			break;
		case 2:
			blackjack::ui::win();
			blackjack::quit++;
			break;
		case 4:
			blackjack::ui::lose();
			blackjack::quit++;
			break;
		default:
			break;
		}
		blackjack::pase_count++;
	}

	void stay() {
		int call_result = blackjack::result(blackjack::player_slot, blackjack::dealer_slot);
		switch (call_result) {
		case 1://win
			basic::chipsum(WIN_prize);
			blackjack::ui::win();
			Sleep(1500);
			break;
		case 2://lose
			basic::chipsum(LOSE_prize);
			blackjack::ui::lose();
			Sleep(1500);
			break;
		case 3://tie
			basic::chipsum(PUSH_prize);
			blackjack::ui::push();
			Sleep(1500);
			break;
		default:
			break;
		}
		blackjack::quit++;
	}
	void surrender() {
		basic::chipsum(SURENDER_prize);
		blackjack::ui::push();
		Sleep(1500);
		blackjack::quit++;
	}
	void player_select_pase() {
		char message[50] = "�����ϼ��� !";
		if (pase_count == 2) {
			blackjack::ui::select(message, "(q)Hit", "(w)Stay", "(e)Surrender");
		}
		else
		{
			blackjack::ui::select(message, "(q)Hit", "(w)Stay", "");
		}

		int input = basic::select_qwer();
		//q(Hit),w(Stay),e(surender)
		//q(hit),w(stay)
		strcpy(message, "�����ϼ��� !");
		switch (input)
		{
		case 1:
			
			stay();
			
			break;
		case 0:
			
			pase();

			break;
		case 2: 
			if (blackjack::pase_count == 2) {
				surrender();
				blackjack::quit++;
				break;
			}
		default:
			//interface wrong input
			strcpy(message, "�߸��� �Է��Դϴ�. �ٽ� �����ϼ��� !");
			break;
		}
	}
	void bet() {
		blackjack::ui::bet();
		cin >> basic::bet;
	}


	

	
	//���� ���� ��Ʈ��
	void Stream() {


		blackjack::pase_count = 0;
		blackjack::quit = 0;
		
		blackjack::bet();

		Trump::SimpleCardSet();
		
		blackjack::pase();
		blackjack::pase();
		while  (blackjack::quit == 0) {
			blackjack::player_select_pase();		
		}
		
	}

	
}



int main()
{
	srand((unsigned int)time(NULL));

	blackjack::Stream();
	return 0;
}

// ���α׷� ����: <Ctrl+F5> �Ǵ� [�����] > [��������� �ʰ� ����] �޴�
// ���α׷� �����: <F5> Ű �Ǵ� [�����] > [����� ����] �޴�
