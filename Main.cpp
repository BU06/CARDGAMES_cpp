// CARDGAMES_Cpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS

//기본
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <Windows.h>
#include <ctime>
#include <cstring>
#include <conio.h>

using namespace std;

//선언
namespace basic{
	//전체---------------------------------------------------

	
	
	//&정수형변수A,&정수형변수B 를 받아 A와 B의 값을 바꾸는 함수
	void swapint(int* num1, int* num2) {
		int temp = *num1;
		*num1 = *num2;
		*num2 = temp;
	} 

	//선택 q w e r
	//    0 1 2 3
	int select() {
		int order;
		order = _getch();
		enum trg{q=113,w=119,e=101,r=114};
		switch (order) 
		{
		case q:
			
			return 0;
		case w:
			return 1;
		case e:
			return 2;
		case r:
			return 3;
		default:
			system("cls");
			cout << "ERROR : [Main//basic::selct// -switch logic- ]"<<endl;
			exit(-1);
		}
	}


	//------------------------------------------------------
}

namespace Trump{
	//트럼프카드

	// 변수 및 구조체
	int order[52];			  //카드 순서(뽑을때사용) 배열 0~51
	int ordercount;			  //카드뽑은횟수
	struct CARD {              //카드슬롯
		char number[10];	  //카드 숫자,기호 [A,1,2,3,4,5,6,7,8,9,10,J,Q,K]
		char shape[10];		  //카드 모양     [♥♣◆♠]
		int deal;			  //딜량          [1,2,3,4,5,6,7,8,9,10,10,10,10]
	}card[52];                //카드 호출배열 0~51
	
	
	
	// 함수
	
	

	// 구조체 CARD의 정보를 채우는 세팅함수(완)
	void card_set() {
		for (int i = 0; i < 52; i++) {
			if (0 <= i && i <= 12)
				strcpy(Trump::card[i].shape, "\u2665");
			else if (13 <= i && i <= 25)
				strcpy(Trump::card[i].shape, "◆");
			else if (26 <= i && i <= 38)
				strcpy(Trump::card[i].shape, "\u2660");
			else if (39 <= i && i <= 51)
				strcpy(Trump::card[i].shape, "\u2663");
			else {
				cout << "ERROR : [main//trump//card_set()//-shape logic-에서 문제발생]" << endl << "프로그램 종료" << endl;
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
				cout << "ERROR : [main//trump::card_set()//-number&deal logic-에서 문제발생]" << endl << "프로그램 종료" << endl;
				exit(-1);
			}
		}
		for (int i = 0; i < 52; i++) {
			Trump::order[i] = i;
		}

	}

	// 카드의 순서를 나타내는 배열 order[] 의 순서 무작위 셔플(완)
	void card_shuffle() {
		int random_int;
		for (int i = 0; i < 52; i++) {
			random_int = rand() % 52;// = 0~51 난수로 초기화
			basic::swapint(&Trump::order[i], &Trump::order[random_int]);
			continue;
		}
	}

	// 순서배열 order[]의 순환, 그리고 카드번호 발행(완)
	int getorder() {
		int FirstOrder = Trump::order[0];
		if (Trump::ordercount <= 51) {
			for (int i = 0; i < 51; i++) {
				Trump::order[i] = Trump::order[i + 1];
			}Trump::order[51] = FirstOrder;
		}
		else {
			Trump::ordercount = 0;
			Trump::card_shuffle();
			FirstOrder = Trump::order[0];
		}
		Trump::ordercount++;
		return(FirstOrder);
	}

	//order[] 배열의 순서대로 카드의 정보를 확인하기
	void card_cheak() {
		int order_val;
		for (int i = 0; i < 52; i++) {
			order_val = Trump::order[i];
			printf("%-2d : Order :%-2d Card : %s%-2s  Deal :%d \n", i, Trump::order[i], Trump::card[order_val].shape, Trump::card[order_val].number, Trump::card[order_val].deal);
		}
	}

	//기본 초기설정
	void SimpleCardSet() {
		Trump::card_set();
		Trump::card_shuffle();
	}
	//------------------------------------------------------
}

namespace blackjack {
	//블랙잭
	
	void fin_BlackJack() {
		system("cls");
		cout << "blackjack" << endl;
	}

	void fin_win() {
		system("cls");
		cout << "win" << endl;
	}

	void fin_lose() {
		system("cls");
		cout << "lose" << endl;
	}


	//플레이어와 딜러가 각각 가지고있는 카드들의 딜 배열
	int player_slot[7] = { 0 }, dealer_slot[7] = { 0 };
	//턴 수
	int pase_count=0;
    //interface
	namespace ui {
		struct placedcardinfo
		{
			char shape[10];
			char number[10];
			int order;
			
		}userinfo[7],dealerinfo[7];

		//배치된 카드 정보 
		void setcardinfo() {
			
			for (int i = 0; i < 7; i++) {
				int userorder = blackjack::player_slot[i];
				int dealerorder = blackjack::dealer_slot[i];

				blackjack::ui::userinfo[i].order= userorder;
				strcpy(blackjack::ui::userinfo[i].shape, Trump::card[userorder].shape);
				strcpy(blackjack::ui::userinfo[i].number, Trump::card[userorder].number);

				blackjack::ui::dealerinfo[i].order = dealerorder;
				strcpy(blackjack::ui::dealerinfo[i].shape, Trump::card[userorder].shape);
				strcpy(blackjack::ui::dealerinfo[i].number, Trump::card[dealerorder].number);
			}
		}
	};
	//스코어 판별 플레이어의 딜슬롯과 딜러의 딜슬롯을받아 결과를 
	// 0 : 21            => 항상 win + blackjack
	// 1 : 딜러<플레이어  => 종료시 win
	// 2 : 딜러>21        => 항상 win
	// 3 : 딜러>플레이어  => 종료시 lose
	// 4 : 플레이어>21     => 항상 lose 
	// 5 : 플레이어=딜러  => 종료시 tie
	int  result(int player_slot[],int dealer_slot[]) {
		int dealer_score = 0, player_score = 0;
		int dealer_deal, player_deal;
		int Ace = 0;
		for (int i = 0; i < 7; i++) {
			dealer_deal = dealer_slot[i];
			player_deal = player_slot[i];
			if (player_slot[i] == 1|| dealer_slot[i] == 1) {
				Ace++;
			}			
			player_score += player_deal;
			dealer_score += dealer_deal;
		}
		//블랙잭 판별
		if (Ace != 0) {
			if (player_score + 10 == 21)
				return 0;//BLACK JACK!
		}
		//플레이어 21 넘겼나?
		else if (player_score > 21) {
			return 4;//lose
		}
		//딜러 21 넘겼나?
		else if (dealer_score > 21) {
			return 2;//win
		}

		else if (player_score >= dealer_score) {
			//플레이어==딜러
			if (player_score == dealer_score)
				return 5;//tie
			//플레이어>딜러
			else {

				return 1;//win

			}
		}
		else
			return 3;//lose
	}
	
	//한 턴
	//카드분배, 즉시패배,즉시승리,블랙잭판별
	void pase() {
		blackjack::player_slot[blackjack::pase_count] = Trump::getorder();
		blackjack::dealer_slot[blackjack::pase_count] = Trump::getorder();
		switch (blackjack::result(player_slot, dealer_slot))
		{
			case 0:
				blackjack::fin_BlackJack();
				break;
			case 2:
				blackjack::fin_win();
				break;
			case 4:
				blackjack::fin_lose();
				break;
		default:
			break;
		}
	}


	void player_select_pase(int *quit) {
		//interface select
		if (blackjack::pase_count == 2) {
			//std::cout << Trump::card[blackjack::player_slot[1]] << "q(Stay),w(Hit),e(surender)";
		}
		int input = basic::select();
		//q(Stay),w(Hit),e(surender)
		//q(stay),w(hit)
		switch (input)
		{
		case 0:
			//interface stay
			//endgame(1);
			quit++;
			break;
		case 1:
			//interface Hit
			pase();
			break;
		case 3: 
			if (blackjack::pase_count == 2) {
				//endgame(0);
				quit++;
				break;
			}
		default:
			//interface wrong input
			break;
		}
	}


	


	//블랙잭 메인 스트림
	void Stream() {
		int quit = 0;

		Trump::SimpleCardSet();
		blackjack::pase();
		blackjack::pase();
		
		while  (quit == 0) {
			blackjack::player_select_pase(&quit);		
		}
		
	}

	
}



int main()
{
	//메인스트림
	Trump::card_set();
	Trump::card_shuffle();

	Trump::card_cheak();
	
	cout<<"겟 오더 :" << Trump::getorder() << endl;
	Trump::card_cheak();



	


	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴
