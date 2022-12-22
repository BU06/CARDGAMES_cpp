#include "basic.h"

//CLASS BasicOrder-------------------------------------
//BasicOrder	Public:
void BasicOrder::swap_int(int& num1, int& num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}


//CLASS TrumpCard--------------------------------------
//FOR TEST TrumpCard	Public
void TrumpCard::TestProtectedFunc() {
	//프로텍티드 및 클래스 내 함수 테스트를 위한 함수
	ShowAllCards();
	cout << "---------------------------------------------"<<endl;
	shuffle();
	ShowAllCards();
}
//TrumpCard	Public:
TrumpCard::TrumpCard() {
	srand((unsigned int)time(NULL));//난수생성을위한 초기설정
	for (int cardslot = 0; cardslot < 52; cardslot++) {
		if (cardslot <= 12)
			strcpy(slot[cardslot].cardshape, "\u2665");
		else if (cardslot <= 25)
			strcpy(slot[cardslot].cardshape, "◆");
		else if (cardslot <= 38)
			strcpy(slot[cardslot].cardshape, "\u2660");
		else if (cardslot <= 51)
			strcpy(slot[cardslot].cardshape, "\u2663");
		else {
			system("cls");
			cout << "ERROR from : seting shape logic in class TrumpCard" << endl;
			exit(-1);
		}
			
		int cardnumbersettingtrg = ((cardslot + 1) % 13); // 카드숫자칸 선정 트리거 설정
		enum CARDNUM{nA=1,n2,n3,n4,n5,n6,n7,n8,n9,n10,nJ,nQ,nK=0};
		switch (cardnumbersettingtrg) {
		case nA:
			strcpy(slot[cardslot].cardnumber, "A");
			break;
		case n2:
			strcpy(slot[cardslot].cardnumber, "2");
			break;
		case n3:
			strcpy(slot[cardslot].cardnumber, "3");
			break;
		case n4:
			strcpy(slot[cardslot].cardnumber, "4");
			break;
		case n5:
			strcpy(slot[cardslot].cardnumber, "5");
			break;
		case n6:
			strcpy(slot[cardslot].cardnumber, "6");
			break;
		case n7:
			strcpy(slot[cardslot].cardnumber, "7");
			break;
		case n8:
			strcpy(slot[cardslot].cardnumber, "8");
			break;
		case n9:
			strcpy(slot[cardslot].cardnumber, "9");
			break;
		case n10:
			strcpy(slot[cardslot].cardnumber, "10");
			break;
		case nJ:
			strcpy(slot[cardslot].cardnumber, "J");
			break;
		case nQ:
			strcpy(slot[cardslot].cardnumber, "Q");
			break;
		case nK:
			strcpy(slot[cardslot].cardnumber, "K");
			break;
		default:
			system("cls");
			cout << "ERROR from : seting number logic in class TrumpCard" << endl;
			exit(-1);
		}
		order[cardslot] = cardslot;
	}
}
int TrumpCard::getorder() {
	order_count++;
	if (order_count > 52) {
		order_count = 0;
		shuffle();
	}
	return order[order_count];
}
void TrumpCard::shuffle() {
	for (int i = 0; i < 52; i++) {
		Trumpcard_bs.swap_int(order[i], order[rand() % 52]);
		//random_int = rand() % 52;// = 0~51 난수로 초기화
		//basic::swapint(&Trump::order[i], &Trump::order[random_int]);
	}
}
//TrumpCard	protected:
void TrumpCard::ShowAllCards() {
	for (int cardslot = 0;cardslot<52;cardslot++){
		cout <<right<<setw(2)<< cardslot <<left<<setw(11)<< ": order"<<order[cardslot];
		cout << right << setw(10) << slot[cardslot].cardshape <<left<<setw(5)<<slot[cardslot].cardnumber;
		cout << endl;
	}
}



//CLASS Blackjack--------------------------------------
//FOR TEST Blackjack	Public
void BlackJack::TestProtectedFunc() {

}
//Blackjack Public:
BlackJack::BlackJack() {
	pasecount = 0;
	player.acecount = 0;
	dealer.acecount = 0;
	player.condition = 0;
	dealer.condition = 0;
	for (int i = 0; i < 10; i++) {
		player.cardslot[i] = 0;
		player.carddeal[i] = 0;
		dealer.cardslot[i] = 0;
		dealer.carddeal[i] = 0;
	}
}
void BlackJack::stream(){
	deck.shuffle();

}
//Blackjack Protected:
int BlackJack::get_carddeal(int cardorder){
	int deal = ((cardorder + 1) % 13);
	switch (deal)
	{
	case 11://J
	case 12://Q
	case 0://K
		return 10;
		break;
	default:
		return deal;
		break;
	}
}
void BlackJack::get_card(charinfo&playerdealer){
	int newplace=0;
	for (int count = 0; playerdealer.carddeal[count] != 0; count++) {
		newplace++;
	}
	int neworder = deck.getorder();
	playerdealer.cardslot[newplace] = neworder;
	playerdealer.carddeal[newplace] = get_carddeal(neworder);
}
void BlackJack::load_score(charinfo& playerdealer) {
	int score = 0;
	for (int cardslot = 0; playerdealer.carddeal != 0; cardslot++) {
		score += playerdealer.carddeal[cardslot];
		count_ace(cardslot, playerdealer);
	}
	playerdealer.score = score;
}
void BlackJack::cheak_special_condition(int cardorder, charinfo& playerdealer) {
	load_score(playerdealer);
	if (playerdealer.acecount != 0 && playerdealer.score + 10 == 21) 
		playerdealer.condition = BLACKJACK;
	else if (playerdealer.score > 21)
		playerdealer.condition = BUST;
	else
		playerdealer.condition = DEFAULT;
	if (&playerdealer == &dealer && dealer.score < 16)
		dealer.condition = DEALERCONTINUE;
	else
		playerdealer.condition = DEFAULT;
}
void BlackJack::count_ace(int cardorder, charinfo& playerdealer) {
		if (playerdealer.carddeal[cardorder] == 1)
			playerdealer.acecount++;
}
void BlackJack::load_normal_conditon() {
	
	load_score(player); load_score(dealer);

	if (player.score > dealer.score) {
		player.condition = WIN; dealer.condition = LOSE;
	}
	else if (player.score == dealer.score) {
		player.condition = PUSH; dealer.condition = PUSH;
	}
	else if (player.score < dealer.score) {
		player.condition = LOSE; dealer.condition = WIN;
	}
}
