#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <Windows.h>
#include <ctime>
#include <cstring>







namespace card {

	int card_order_arr0to51[52];
	int card_order_count = 0;


	struct Card_set {
	char shape[10];
	char number[10];
	int deal_rate;
	}slot[52];

	void set(){
		for (int i = 0; i < 52; i++) {
			if (0 <= i && i <= 12)
				strcpy(slot[i].shape, "\u2665");
			else if (13 <= i && i <= 25)
				strcpy(slot[i].shape, "¡ß");
			else if (26 <= i && i <= 38)
				strcpy(slot[i].shape, "\u2660");
			else if (39 <= i && i <= 51)
				strcpy(slot[i].shape, "\u2663");
			else {
				std::cout << "Error on [card.set -shape logic- ] " << std::endl;
			}

			if ((i + 1) % 13 == 1) {
				strcpy(slot[i].number, "A");
				slot[i].deal_rate = 1;
			}
			else if ((i + 1) % 13 == 2) {
				strcpy(slot[i].number, "2");
				slot[i].deal_rate = 2;
			}
			else if ((i + 1) % 13 == 3) {
				strcpy(slot[i].number, "3");
				slot[i].deal_rate = 3;
			}
			else if ((i + 1) % 13 == 4) {
				strcpy(slot[i].number, "4");
				slot[i].deal_rate = 4;
			}
			else if ((i + 1) % 13 == 5) {
				strcpy(slot[i].number, "5");
				slot[i].deal_rate = 5;
			}
			else if ((i + 1) % 13 == 6) {
				strcpy(slot[i].number, "6");
				slot[i].deal_rate = 6;
			}
			else if ((i + 1) % 13 == 7) {
				strcpy(slot[i].number, "7");
				slot[i].deal_rate = 7;
			}
			else if ((i + 1) % 13 == 8) {
				strcpy(slot[i].number, "8");
				slot[i].deal_rate = 8;
			}
			else if ((i + 1) % 13 == 9) {
				strcpy(slot[i].number, "9");
				slot[i].deal_rate = 9;
			}
			else if ((i + 1) % 13 == 10) {
				strcpy(slot[i].number, "10");
				slot[i].deal_rate = 10;
			}
			else if ((i + 1) % 13 == 11) {
				strcpy(slot[i].number, "J");
				slot[i].deal_rate = 10;
			}
			else if ((i + 1) % 13 == 12) {
				strcpy(slot[i].number, "Q");
				slot[i].deal_rate = 10;
			}
			else if ((i + 1) % 13 == 0) {
				strcpy(slot[i].number, "K");
				slot[i].deal_rate = 10;
			}
			else {
				std::cout << "ERROR in [card.set -number logic-]" << std::endl;
			}
		}
		for (int i = 0; i < 52; i++) {
			card_order_arr0to51[i] = i;
		}


	}
}