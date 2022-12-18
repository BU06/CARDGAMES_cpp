// CARDGAMES_Cpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS

//기본
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <istream>


//블랙잭 칩 반환계수
#define PUSH_prize 1
#define WIN_prize 2
#define LOSE_prize -1
#define BLACKJACK_prize 4
#define SURENDER_prize 0.5



using namespace std;

//선언
namespace basic{
	//전체---------------------------------------------------
	int chip,prize,bet;
	
	
	//&정수형변수A,&정수형변수B 를 받아 A와 B의 값을 바꾸는 함수
	void swapint(int* num1, int* num2) {
		int temp = *num1;
		*num1 = *num2;
		*num2 = temp;
	} 

	//선택 q w e r
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
	int getorder(int count) {
		if (Trump::ordercount > 51) {
			Trump::ordercount = 0;
			Trump::card_shuffle();
		}
		Trump::ordercount++;
		return(Trump::order[count]);
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
	
	
	
    int quit;//블랙잭 메인스트림  종료조건
	
	int player_slot[7] = { 0 }, dealer_slot[7] = { 0 };//플레이어와 딜러가 각각 가지고있는 카드들의 딜 배열
	
	int pase_count;//턴 수

	

    //interface
	namespace ui {
		

		
		//상단메세지
		//선택지1,2,3
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
			//9   수정완료
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
			cout << endl << setw(30) << "블랙잭" << endl <<setw(26)<<"칩 :  "<<basic::chip << endl << endl << setw(35) << "배팅하세요 : ";
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
		//블랙잭 판별
		if (playerAce != 0) {
			if (player_score + 10 == 21)
				return 0;//BLACK JACK!
		}
		if (dealerAce != 0) {
			if (dealer_score + 10 == 21)
				return 4;//Dealer BLACK JACK  lose
		}
		//딜러 21 넘겼나?
		else if (dealer_score > 21) {
			return 2;//win
		}
		//플레이어 21 넘겼나?
		else if (player_score > 21) {
			return 4;//lose
		}
		else if (player_score == dealer_score)//플레이어==딜러
				return 5;//tie
		//플레이어>딜러
		else if (player_score > dealer_score) {										
			return 1;//win			
		}
		else if (player_score < dealer_score)
			return 3;//lose
		else {
			return 6;
		}
			
	}

	//한 턴
	//카드분배, 즉시패배,즉시승리,블랙잭판별
	void pase() {
		int psn = blackjack::pase_count;

		blackjack::player_slot[psn] = Trump::getorder(Trump::ordercount);
		blackjack::dealer_slot[psn] = Trump::getorder(Trump::ordercount);
		
		
		blackjack::ui::select("카드 배치중...", "", "", "");
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
		char message[50] = "선택하세요 !";
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
		strcpy(message, "선택하세요 !");
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
			strcpy(message, "잘못된 입력입니다. 다시 선택하세요 !");
			break;
		}
	}
	void bet() {
		blackjack::ui::bet();
		cin >> basic::bet;
	}


	

	
	//블랙잭 메인 스트림
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

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴
