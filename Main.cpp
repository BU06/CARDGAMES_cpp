// CARDGAMES_Cpp.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#define _CRT_SECURE_NO_WARNINGS

//�⺻
#include "header.h"


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
		enum qwer{Q,W,E,R};
		int order,input=1;
		while (input == 1) {
			if (_kbhit()) {
				order = _getch();
				input++;
			}
		}
		switch (order) 
		{
		case 113:
			return Q;
		case 119:
			return W;
		case 101:
			return E;
		case 114:
			return R;
		default:
			cout<<"ERROR : [Main//basic::select_qwer -switch(order) logic  = defalut-  ]";
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
}// all refactoried

namespace blackjack {
	//����
	
	int dealer_score = 0, player_score = 0;							//�� ���ھ� 
	int dealer_ace_count = 0, player_ace_count = 0;
	
    int quit;//���� ���ν�Ʈ��  ��������
	int statyswitch;
	
	int player_slot[6] = { 0 }, dealer_slot[6] = { 0 };//�÷��̾�� ������ ���� �������ִ� ī����� �� �迭
	int testresult;
	int pase_count;//�� ��

	

    //interface
	namespace ui {
		//��ܸ޼���
		//������1,2,3
		void select(const char message[], const char selection1[], const char selection2[],const char selection3[]) {
			
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
		void bet() {
			cout << endl << setw(30) << "����" << endl << setw(26) << "Ĩ :  " << basic::chip << endl << endl << setw(35) << "�����ϼ��� : ";
		}
		namespace result {

			void push() {
				system("cls");

				cout << endl << setw(30) << "Push" << endl << endl << setw(35) << "price : +" << basic::prize;
			}
			void win() {
				system("cls");

				cout << endl << setw(30) << "Win" << endl << endl << setw(35) << "price : +" << basic::prize;
			}
			void lose() {
				system("cls");

				cout << endl << setw(30) << "Lose" << endl << endl << setw(35) << "price : +" << basic::prize;
			}
			void blackjack() {
				system("cls");

				cout << endl << setw(30) << "Win" << endl << endl << setw(35) << "price : " << basic::prize;
			}
			void dealer_blackjack() {
				system("cls");

				cout << endl << setw(30) << "Lose by Dealer Blackjack" << endl << endl << setw(35) << "price : +" << basic::prize;
			}
			
			
		}
	};
	void getscore(int player_slot[], int dealer_slot[]) {
		int dealer_score = 0, player_score = 0;							//�� ���ھ� 
		int dealer_ace_count = 0, player_ace_count = 0;					//ACEī�� ��������
		int dealer_slot_deal, player_slot_deal;							//�ش� ���� ī�� ��
		int dealer_order, player_order;									//Trump::order

		// �� ���
		for (int i = 0; i < 7; i++) {

			dealer_order = dealer_slot[i], player_order = player_slot[i];	// order �ҷ�����

			dealer_slot_deal = Trump::card[dealer_order].deal;				// ����� ����
			player_slot_deal = Trump::card[player_order].deal;

			if (player_slot_deal == 1)		// ace ���� �߰� 
				player_ace_count++;
			else if (dealer_slot_deal == 1)
				dealer_ace_count++;

			player_score += player_slot_deal, dealer_score += dealer_slot_deal; // �� ���ھ� ���
		}
		blackjack::player_score=player_score ;
		blackjack::player_ace_count=player_ace_count ; 
		blackjack::dealer_score=dealer_score ;
		blackjack::dealer_ace_count = dealer_ace_count ;
	}

	//���ھ� �Ǻ� �÷��̾��� �����԰� ������ ���������޾� ����� 
	//�Ǻ�����  ����         ���               return();    enum
	// 1 : 21            => �׻� win + blackjack		0	BLACKJACK
	// 2 : �÷��̾�>21     => �׻� lose				1	PLAYER_BUST
	// 3 : ����>21        => �׻� win					2	DEALER_BUST
	// 4 : ����21          => �׻� lose + blackjack	3	DEALER_BLACKJACK
	// 5 : ����<�÷��̾�  => ����� win					4	WIN
	// 6 : ����>�÷��̾�  => ����� lose				5	LOSE
	// 7 : �÷��̾�=����  => ����� tie					6	PUSH
	//else{}										7	ERROR
	void result() {
		//enum Return { BLACKJACK=0,PLAYER_BUST, DEALER_BUST,DEALER_BLACKJACK,WIN,LOSE,PUSH,ERROR_};
		blackjack::getscore(blackjack::player_slot,blackjack::dealer_slot);

		//����,return(Return)
		if (blackjack::player_ace_count != 0 || blackjack::player_score == 21) {
			if (blackjack::player_score == 21) {
				blackjack::statyswitch = 0;
				
			}
			else if (blackjack::player_score + 10 == 21 && blackjack::player_ace_count != 0) {
				blackjack::statyswitch = 0;
			}
		}
		else if (blackjack::player_score > 21) {
			blackjack::statyswitch = 1;
		}
		else if (blackjack::dealer_score > 21) {
			blackjack::statyswitch = 2;
		}
		else if (dealer_ace_count != 0 || blackjack::dealer_score == 21) {
			if (blackjack::dealer_score == 21) {
				blackjack::statyswitch = 3;
			}
			else if (blackjack::dealer_score + 10 == 21 && blackjack::dealer_ace_count != 0) {
				blackjack::statyswitch = 4;
			}
		}
		else if (blackjack::dealer_score< blackjack::player_score){
			blackjack::statyswitch = 5;
		}
		else if (blackjack::dealer_score > blackjack::player_score) {
			blackjack::statyswitch = 6;
		}
		else if (blackjack::dealer_score == blackjack::player_score) {
			blackjack::statyswitch = 7;
		}
		else {
			blackjack::statyswitch = 8;
		}
	}

	//�� ��
	//ī��й�, ����й�,��ý¸�,�����Ǻ�
	
	void pase() {
		enum Return { BLACKJACK, PLAYER_BUST, DEALER_BUST, DEALER_BLACKJACK, WIN, LOSE, PUSH, ERROR_ };
		int psn = blackjack::pase_count;
		cout << blackjack::pase_count << " //1: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
		blackjack::player_slot[psn] = Trump::getorder(Trump::ordercount);
		cout << blackjack::pase_count << " //2: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
		blackjack::dealer_slot[psn] = Trump::getorder(Trump::ordercount);
		cout << blackjack::pase_count << " //3: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
		blackjack::testresult = blackjack::statyswitch;
		blackjack::ui::select("ī�� ��ġ��...", "", "", "");
		cout << blackjack::pase_count << " //4: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
		Sleep(1500);

		switch (blackjack::statyswitch)
		{
		case BLACKJACK:
			cout << blackjack::pase_count << " //5B: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
			blackjack::ui::result::blackjack;		
			blackjack::quit++;				
			break;		
		case DEALER_BLACKJACK:
			cout << blackjack::pase_count << " //5DBL: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
			blackjack::ui::result::dealer_blackjack();
			blackjack::quit++;
			break;
		case DEALER_BUST:
			cout << blackjack::pase_count << " //5DB: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
			blackjack::ui::result::win();
			blackjack::quit++;
			break;
		case PLAYER_BUST:
			cout << blackjack::pase_count << " //PB: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
			blackjack::ui::result::lose();
			blackjack::quit++;
			break;
		default:
			cout << blackjack::pase_count << " //5default: " << blackjack::player_score << " - " << blackjack::dealer_score << "result : " << blackjack::statyswitch << endl;
			break;
		}
		blackjack::pase_count++;
	}

	//������ ���
	//using
	//blackjack::ui::result::blackjack
	//blackjack::ui::result::dealer_blackjack();
	//blackjack::ui::result::win();
	//blackjack::ui::result::lose();
	//blackjack::ui::result::win();
	void stay() {
		enum Return { BLACKJACK, PLAYER_BUST, DEALER_BUST, DEALER_BLACKJACK, WIN, LOSE, PUSH, ERROR_ };
		int call_result = blackjack::statyswitch;
		switch (call_result) {
			
		case BLACKJACK:
			blackjack::ui::result::blackjack;
			Sleep(1500);
			blackjack::quit++;
			break;
		case DEALER_BLACKJACK:
			blackjack::ui::result::dealer_blackjack();
			blackjack::quit++;
			Sleep(1500);
			break;
		case DEALER_BUST:
			blackjack::ui::result::win();
			blackjack::quit++;
			Sleep(1500);
			break;
		case PLAYER_BUST:
			blackjack::ui::result::lose();
			blackjack::quit++;
			Sleep(1500);
			break;
		case WIN://win
			basic::chipsum(WIN_prize);
			blackjack::ui::result::win();
			Sleep(1500);
			break;
		case LOSE://lose
			basic::chipsum(LOSE_prize);
			blackjack::ui::result::lose();
			Sleep(1500);
			break;
		case PUSH://tie
			basic::chipsum(PUSH_prize);
			blackjack::ui::result::push();
			Sleep(1500);
			break;
		default:
			system("cls");
			cout << "ERROR : [Main//blackjack::stay() -switch logic(defalt)-] result : "<< blackjack::statyswitch << endl;

			exit(-1);
		}
		blackjack::quit++;
	}
	void surrender() {
		basic::chipsum(SURENDER_prize);
		blackjack::ui::result::push();
		Sleep(1500);
		blackjack::quit++;
	}
	void player_select_pase() {
		char message[50] = "�����ϼ��� !";
		blackjack::testresult = blackjack::statyswitch;
		if (pase_count == 2) {
			blackjack::ui::select(message, "(q)Hit", "(w)Stay", "(e)Surrender");
		}
		else
		{
			blackjack::ui::select(message, "(q)Hit", "(w)Stay", "");
		}

		int input = basic::select_qwer();
		enum qwer { Q, W, E, R };
		//q(Hit),w(Stay),e(surender)
		//q(hit),w(stay)
		strcpy(message, "�����ϼ��� !");
		switch (input)
		{
		case W:
			
			blackjack::stay();
			blackjack::quit++;
			break;
		case Q:
			blackjack::pase();
			break;
		case E: 
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


		blackjack::pase_count = 0;//������ī��Ʈ�ʱ�ȭ
		blackjack::quit = 0;//���� �������� �ʱ�ȭ
		
		blackjack::bet();//����ui

		Trump::SimpleCardSet();//ī���غ�
		
		blackjack::pase();//������1
		blackjack::pase();//������2
		while  (blackjack::quit == 0) {
			blackjack::player_select_pase();//���������� ��������		
		}
		
	}

	
}



int main()
{
	srand((unsigned int)time(NULL));//�������������� �ʱ⼳��

	blackjack::Stream();

	return 0;
}

// ���α׷� ����: <Ctrl+F5> �Ǵ� [�����] > [��������� �ʰ� ����] �޴�
// ���α׷� �����: <F5> Ű �Ǵ� [�����] > [����� ����] �޴�
