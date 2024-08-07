#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Structures

struct card{
	char suit[9];
	int value; //jack = 11 queen = 12 king = 13 ace = 14
};

struct tableDeck{
	struct card deck[52];
};

struct player{
	struct card playerDeck[7];
	int chips;
};

//tableDeck functions

void shuffleDeck(struct tableDeck* deck){

	srand(time(NULL));
	int randomSwap;
	struct card carryOver;

	for(int i = 0; i < 52; i++){
		randomSwap = rand() % 52;
		carryOver = deck->deck[randomSwap];
		deck->deck[randomSwap] = deck->deck[i];
		deck->deck[i] = carryOver;
	}

}

//function prototypes (so to call functions farther down the list (forward declaration))

int userDecision_1(int*, struct player*, struct player*, int, int*, int*, int*, int, int);
int userDecision_2(int*, struct player*, struct player*, int*, int, int, int); 
int compDecision_1(int*, struct player*, struct player*, int, int*, int*, int*, int, int);
int compDecision_2(int*, struct player*, struct player*, int, int*, int, int);
int compDecision_1_1(int*, struct player*, struct player*, int, int*, int, int);
void printOptions_1(void);
//player functions

int userDecision_1(int* userDecision, struct player* userPlayer, struct player* compPlayer, int maxBet, int* smallBlind, int* bigBlind, int* potTotal, int roundNum, int compBluff){
	fflush(stdout);
	scanf("%d", userDecision);
	int computerDecision;

	//user decision for 1st hand
	if(*userDecision == 1) { //user chooses to call
		printf("\nUser chose to call");
		userPlayer->chips -= *bigBlind;
		printf("\nUser puts %d chips in pot with %d remaining\n\n", *bigBlind, userPlayer->chips);
		*potTotal += *bigBlind;
		computerDecision = compDecision_1(userDecision, userPlayer, compPlayer, maxBet, smallBlind, bigBlind, potTotal, roundNum, compBluff);
		return computerDecision;
	} else if(*userDecision == 2) { //user chooses to raise
		printf("\nUser chose to raise");
		printf("\nPlease enter how much you would like to raise:");
		fflush(stdout);
		scanf("%d", userDecision);
		printf("\nUser raises %d", *userDecision);
		userPlayer->chips -= *userDecision;
		*potTotal += *userDecision;
		return compDecision_1_1(userDecision, userPlayer, compPlayer, maxBet, potTotal, roundNum, compBluff);
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round)
		printf("\nUser chose to fold");
		printf("\n\nComputer wins the pot");
		compPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed)
		printf("\nUser chose to leave game");
		return 2;
	} else { //user chose invalid input
		printf("\nUser chose to call");
		userPlayer->chips -= *bigBlind;
		printf("\nUser puts %d chips in pot with %d remaining\n\n", *bigBlind, userPlayer->chips);
		return 0;
	}

}
//hi
//user decision after the 1st hand if user going first
int userDecision_2(int* userDecision, struct player* userPlayer, struct player* compPlayer, int* potTotal, int maxBet, int roundNum, int compBluff){ 
	fflush(stdout);
	scanf("%d", userDecision);
	int computerDecision;

	//user decision for 2nd hand
	if(*userDecision == 1){ //user chooses to check 
		printf("\nUser chose to check");
		computerDecision = compDecision_2(userDecision, userPlayer, compPlayer, maxBet, potTotal, roundNum, compBluff);
		return computerDecision;
	} else if(*userDecision == 2){ //user chooses to bet
		printf("\nUser chose to bet");
		printf("\nPlease enter how much you would like to bet: ");
		fflush(stdout);
		scanf("%d", userDecision);
		printf("\nUser bet %d", *userDecision);
		userPlayer->chips -= *userDecision;
		*potTotal += *userDecision;
		return compDecision_1_1(userDecision, userPlayer, compPlayer, maxBet, potTotal, roundNum, compBluff);
	} else if(*userDecision == 3){ //user chooses to fold (announce winner of hand and move on to next round)
		printf("\nUser chose to fold"); //will use the continue keyword after displaying winner of round
		printf("\n\nComputer wins the pot");
		compPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	} else if(*userDecision == 4){ //user chooses to leave (game is over and end game result is displayed)
		printf("\nUser chose to leave game"); //will use break keyword to breakout of loop to then show final stats of game
		return 2;
	} else { //user chose invalid input 
		printf("\nUser chose to check");
		computerDecision = compDecision_2(userDecision, userPlayer, compPlayer, maxBet, potTotal, roundNum, compBluff);
	        return computerDecision;
	}
	
}

int userDecision_1_1(int* userDecision, struct player* userPlayer, struct player* compPlayer, int* potTotal, int* compDecision, int maxBet, int roundNum, int compBluff){ //if computer chooses to raise
	printf("\n");
	printOptions_1();
	fflush(stdout);
	scanf("%d", userDecision);
	if(*userDecision == 1){
		printf("\nUser chose to call Computer's bet");
		userPlayer->chips -= *compDecision;
		*potTotal += *compDecision;
		return 0;
	} else if(*userDecision == 2){
		printf("\nUser chose to raise");
		printf("\nPlease enter how much you would like to raise computer's call: ");
		fflush(stdout);
		scanf("%d", userDecision);
		*userDecision += *compDecision;
		printf("\nUser bet %d", *userDecision);
		userPlayer->chips -= *userDecision;
		*potTotal += *userDecision;
		return compDecision_1_1(userDecision, userPlayer, compPlayer, maxBet, potTotal, roundNum, compBluff);
	} else if(*userDecision == 3){
		printf("\nUser chose to fold");
		printf("\n\nComputer wins the pot");
		compPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	} else if(*userDecision == 4){
		printf("\nUser chose to leave game");
		return 2;
	} else {
		printf("\nUser chose to call Computer's bet");
		userPlayer->chips -= *compDecision;
		*potTotal += *compDecision;
		return 0;
	}
}

//Helper Functions for determinePoints() function

void swap(struct card* card_1, struct card* card_2){
	struct card tempCard = *card_1;
	*card_1 = *card_2;
	*card_2 = tempCard;
}


void bubbleSort(struct player* player_1, int n){
	int i, j;
	int swapped;
	for(i = 0; i < n - 1; i++){
		swapped = 0;
		for(j = 0; j < n - i - 1; j++){
			if(player_1->playerDeck[j].value > player_1->playerDeck[j+1].value){
				swap(&player_1->playerDeck[j], &player_1->playerDeck[j+1]);
				swapped = 1;
			}
		}
		if(swapped == 0){
			break;
		}
	}
}

//determines if cards are a flush or not (five cards have same suit)
//if a flush returns one if not a flush returns zero
int determineFlush(struct player* player_1){
	int diamondsTotal = 0;
	int spadesTotal = 0;
	int clubsTotal = 0;
	int heartsTotal = 0;

	//using strcmp() to determine if strings are equal (same suit), will return zero if equal
	for(int i = 0; i < 7; i++){
		if(strcmp(player_1->playerDeck[i].suit, "diamonds") == 0){
			diamondsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "spades") == 0){
			spadesTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "clubs") == 0){
			clubsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "hearts") == 0){
			heartsTotal++;
		} else {
			printf("Something is not working with the determineFlush function");
		}
	}

	//checking if any are above suit totals are above five
	if(diamondsTotal >= 5){
		return 1;
	} else if(spadesTotal >= 5){
		return 1;
	} else if(clubsTotal >= 5){
		return 1;
	} else if(heartsTotal >= 5){
		return 1;
	} else {
		return 0;
	}
}

//determine if cards are a straight or not, will return a one if a straight and will return zero if not
int determineStraight(struct player* player_1){
	int cardPoints = 0;
	int thisCardValue = 0;
	int nextCardValue = 0;
	
	for(int i = 0; i < 6; i++){
		//To check if straight has been achieved
		if(cardPoints >= 4){
			return 1;
			break;
		}
		thisCardValue = player_1->playerDeck[i].value;
		nextCardValue = player_1->playerDeck[i+1].value;
		if(thisCardValue == nextCardValue - 1){
			cardPoints++;
		} else if(thisCardValue == nextCardValue){
			continue;
		} else {
			cardPoints = 0;
		}
	}

	if(cardPoints >= 4){
		return 1;
	} else {
		return 0;
	}

}

//return one if royal flush and zero if not
int determineRoyalFlush(struct player* player_1){
	int tenOfSameSuit = 0;
	int jokerOfSameSuit = 0;
	int queenOfSameSuit = 0;
	int kingOfSameSuit = 0;
	int aceOfSameSuit = 0;
	char sameSuit[9];

	for(int i = 6; i >= 0; i--){
		strcpy(sameSuit, player_1->playerDeck[i].suit);
		tenOfSameSuit = 0;
		jokerOfSameSuit = 0;
		queenOfSameSuit = 0;
		kingOfSameSuit = 0;
		for(int j = 0; j < 7; j++){
			if(player_1->playerDeck[j].value == 10){ //checking for ten of same suit
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					tenOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 11){ //checking for joker of the same suit
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					jokerOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 12){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					queenOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 13){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					kingOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 14){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					aceOfSameSuit = 1;
				}
			}
		}

		if(tenOfSameSuit == 1){
			if(jokerOfSameSuit == 1){
				if(queenOfSameSuit == 1){
					if(kingOfSameSuit == 1){
						if(aceOfSameSuit == 1){
							return 1;
							break;
						}
					}
				}
			}
		}

	}

	return 0;
}

//returns one if straight flush and returns zero if not
int determineStraightFlush(struct player* player_1){

	int cardPoints = 0;
	int thisCardValue = 0;
	int nextCardValue = 0;
	char thisCardSuit[9];
	char nextCardSuit[9];
	
	for(int i = 0; i < 6; i++){
		//To check if straight has been achieved
		if(cardPoints >= 4){
			return 1;
			break;
		}
		thisCardValue = player_1->playerDeck[i].value;
		nextCardValue = player_1->playerDeck[i+1].value;
		strcpy(thisCardSuit, player_1->playerDeck[i].suit);
		strcpy(nextCardSuit, player_1->playerDeck[i+1].suit);
		if(thisCardValue == nextCardValue - 1){
			if(strcmp(thisCardSuit, nextCardSuit) == 0){
				cardPoints++;
			}
		} else if(thisCardValue == nextCardValue){
			continue;
		} else {
			cardPoints = 0;
		}
	}

	if(cardPoints >= 4){
		return 1;
	} else {
		return 0;
	}
}

//returns one if four of a kind and a zero if not
int determineFourOfAKind(struct player* player_1){
	int samesies;
	int thisCardValue;
	for(int i = 0; i < 7; i++){
		thisCardValue = player_1->playerDeck[i].value;
		samesies = 0;
		for(int j = 0; j < 7; j++){
			if(thisCardValue == player_1->playerDeck[j].value){
				samesies++;
			}
		}
		if(samesies >= 4){
			return 1;
			break;
		}
	}
	return 0;

}

//return one if a fullhouse and zero if not
int determineFullHouse(struct player* player_1){
	int threePete = 0; //will equal one if we have three matching cards
	int twoPete = 0; //will equal one if we have two matching cards
	int numOfMatches;
	int valueToMatch;
	for(int i = 0; i < 7; i++){
		numOfMatches = 0;
		valueToMatch = player_1->playerDeck[i].value;
		for(int j = 0; j < 7; j++){
			if(valueToMatch == player_1->playerDeck[j].value){
				numOfMatches++;
			}
		}
		if(numOfMatches == 2){
			twoPete = 1;
		}
		if(numOfMatches == 3){
			threePete = 1;
		}
	}
	if(threePete == 1 && twoPete == 1){
		return 1;
	} else {
		return 0;
	}
}

//return one if a three of a kind and zero if not
int determineThreeOfAKind(struct player* player_1){
	int numOfMatches;
	int valueToMatch;
	for(int i = 0; i < 7; i++){
		numOfMatches = 0;
		valueToMatch = player_1->playerDeck[i].value;
		for(int j = 0; j < 7; j++){
			if(valueToMatch == player_1->playerDeck[j].value){
				numOfMatches++;
			}
		}
		if(numOfMatches == 3){
			return 1;
			break;
		}
	}
	return 0;
}

//return one if a two pair and a zero if not
int determineTwoPair(struct player* player_1){
	int numOfMatches = 0;
	for(int i = 0; i < 6; i++){
		if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
			numOfMatches++;
		}
		if(numOfMatches == 2){
			return 1;
			break;
		}
	}
	return 0;
}

//return one if a pair and a zero if not
int determinePair(struct player* player_1){
	for(int i = 0; i < 6; i++){
		if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
			return 1;
		}
	}
	return 0;
}

//beginning of determinePoints() function
//Going to return points based on the hand the player posseses
int determinePoints(struct player* player_1){ //Determines which hand a player has and returns the score of his hand

	//if statement to determine which hand player has, will then return score based on hand
	//going to have to have to create a function for each of the ten hands
	//a royal flush returns ten and a single highcard returns a one
	
	//Sorting
	
	int size = 7;
	bubbleSort(player_1, size);
	printf("\nSorted deck: ");
	for(int i = 0; i < size; i++){
		printf("%d ", player_1->playerDeck[i].value);
	}

	//going to determine what hand
	if(determineRoyalFlush(player_1) == 1){
		printf("\nplayer has a royal flush!");
		return 10;
	} else if(determineStraightFlush(player_1) == 1){
		printf("\nplayer has a straight flush!");
		return 9;
	} else if(determineFourOfAKind(player_1) == 1){
		printf("\nPlayer has four of a kind!");
		return 8;
	} else if(determineFullHouse(player_1) == 1){
		printf("\nPlayer has a full house!");
		return 7;
	} else if(determineFlush(player_1) == 1){
		printf("\nPlayer has flush");
		return 6;
	} else if(determineStraight(player_1) == 1){
		printf("\nPlayer has a straight");
		return 5;
	} else if(determineThreeOfAKind(player_1) == 1){
		printf("\nPlayer has a three of a kind");
		return 4;
	} else if(determineTwoPair(player_1) == 1){
		printf("\nPlayer has a two pair");
		return 3;
	} else if(determinePair(player_1) == 1){
		printf("\nPlayer has a pair");
		return 2;
	} else {
		printf("\nPlayer only has a high card");
		return 1;
	}
	


}

//beginning of computer choice making for better informed ai FIXME

//determines if cards are a flush or not (five cards have same suit)
//if a flush returns one if not a flush returns zero
int determineFlushCompChoice(struct player* player_1, int numCheck){
	int diamondsTotal = 0;
	int spadesTotal = 0;
	int clubsTotal = 0;
	int heartsTotal = 0;

	//using strcmp() to determine if strings are equal (same suit), will return zero if equal
	for(int i = 0; i < numCheck; i++){
		if(strcmp(player_1->playerDeck[i].suit, "diamonds") == 0){
			diamondsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "spades") == 0){
			spadesTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "clubs") == 0){
			clubsTotal++;
		} else if (strcmp(player_1->playerDeck[i].suit, "hearts") == 0){
			heartsTotal++;
		} else {
			printf("Something is not working with the determineFlush function");
		}
	}

	//checking if any are above suit totals are above five
	if(diamondsTotal >= 5){
		return 1;
	} else if(spadesTotal >= 5){
		return 1;
	} else if(clubsTotal >= 5){
		return 1;
	} else if(heartsTotal >= 5){
		return 1;
	} else {
		return 0;
	}
}

//determine if cards are a straight or not, will return a one if a straight and will return zero if not
int determineStraightCompChoice(struct player* player_1, int numCheck){
	int cardPoints = 0;
	int thisCardValue = 0;
	int nextCardValue = 0;
	
	for(int i = 0; i < (numCheck - 1); i++){
		//To check if straight has been achieved
		if(cardPoints >= 4){
			return 1;
			break;
		}
		thisCardValue = player_1->playerDeck[i].value;
		nextCardValue = player_1->playerDeck[i+1].value;
		if(thisCardValue == nextCardValue - 1){
			cardPoints++;
		} else if(thisCardValue == nextCardValue){
			continue;
		} else {
			cardPoints = 0;
		}
	}

	if(cardPoints >= 4){
		return 1;
	} else {
		return 0;
	}

}

//return one if royal flush and zero if not
int determineRoyalFlushCompChoice(struct player* player_1, int numCheck){
	int tenOfSameSuit = 0;
	int jokerOfSameSuit = 0;
	int queenOfSameSuit = 0;
	int kingOfSameSuit = 0;
	int aceOfSameSuit = 0;
	char sameSuit[9];

	for(int i = (numCheck - 1); i >= 0; i--){
		strcpy(sameSuit, player_1->playerDeck[i].suit);
		tenOfSameSuit = 0;
		jokerOfSameSuit = 0;
		queenOfSameSuit = 0;
		kingOfSameSuit = 0;
		for(int j = 0; j < numCheck; j++){
			if(player_1->playerDeck[j].value == 10){ //checking for ten of same suit
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					tenOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 11){ //checking for joker of the same suit
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					jokerOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 12){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					queenOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 13){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					kingOfSameSuit = 1;
				}
			}
			if(player_1->playerDeck[j].value == 14){
				if(strcmp(player_1->playerDeck[j].suit, sameSuit) == 0){
					aceOfSameSuit = 1;
				}
			}
		}

		if(tenOfSameSuit == 1){
			if(jokerOfSameSuit == 1){
				if(queenOfSameSuit == 1){
					if(kingOfSameSuit == 1){
						if(aceOfSameSuit == 1){
							return 1;
							break;
						}
					}
				}
			}
		}

	}

	return 0;
}

//returns one if straight flush and returns zero if not
int determineStraightFlushCompChoice(struct player* player_1, int numCheck){

	int cardPoints = 0;
	int thisCardValue = 0;
	int nextCardValue = 0;
	char thisCardSuit[9];
	char nextCardSuit[9];
	
	for(int i = 0; i < (numCheck - 1); i++){
		//To check if straight has been achieved
		if(cardPoints >= 4){
			return 1;
			break;
		}
		thisCardValue = player_1->playerDeck[i].value;
		nextCardValue = player_1->playerDeck[i+1].value;
		strcpy(thisCardSuit, player_1->playerDeck[i].suit);
		strcpy(nextCardSuit, player_1->playerDeck[i+1].suit);
		if(thisCardValue == nextCardValue - 1){
			if(strcmp(thisCardSuit, nextCardSuit) == 0){
				cardPoints++;
			}
		} else if(thisCardValue == nextCardValue){
			continue;
		} else {
			cardPoints = 0;
		}
	}

	if(cardPoints >= 4){
		return 1;
	} else {
		return 0;
	}
}

//returns one if four of a kind and a zero if not
int determineFourOfAKindCompChoice(struct player* player_1, int numCheck){
	int samesies;
	int thisCardValue;
	for(int i = 0; i < numCheck; i++){
		thisCardValue = player_1->playerDeck[i].value;
		samesies = 0;
		for(int j = 0; j < numCheck; j++){
			if(thisCardValue == player_1->playerDeck[j].value){
				samesies++;
			}
		}
		if(samesies >= 4){
			return 1;
			break;
		}
	}
	return 0;

}

//return one if a fullhouse and zero if not
int determineFullHouseCompChoice(struct player* player_1, int numCheck){
	int threePete = 0; //will equal one if we have three matching cards
	int twoPete = 0; //will equal one if we have two matching cards
	int numOfMatches;
	int valueToMatch;
	for(int i = 0; i < numCheck; i++){
		numOfMatches = 0;
		valueToMatch = player_1->playerDeck[i].value;
		for(int j = 0; j < numCheck; j++){
			if(valueToMatch == player_1->playerDeck[j].value){
				numOfMatches++;
			}
		}
		if(numOfMatches == 2){
			twoPete = 1;
		}
		if(numOfMatches == 3){
			threePete = 1;
		}
	}
	if(threePete == 1 && twoPete == 1){
		return 1;
	} else {
		return 0;
	}
}

//return one if a three of a kind and zero if not
int determineThreeOfAKindCompChoice(struct player* player_1, int numCheck){
	int numOfMatches;
	int valueToMatch;
	for(int i = 0; i < numCheck; i++){
		numOfMatches = 0;
		valueToMatch = player_1->playerDeck[i].value;
		for(int j = 0; j < numCheck; j++){
			if(valueToMatch == player_1->playerDeck[j].value){
				numOfMatches++;
			}
		}
		if(numOfMatches == 3){
			return 1;
			break;
		}
	}
	return 0;
}

//return one if a two pair and a zero if not
int determineTwoPairCompChoice(struct player* player_1, int numCheck){
	int numOfMatches = 0;
	for(int i = 0; i < (numCheck - 1); i++){
		if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
			numOfMatches++;
		}
		if(numOfMatches == 2){
			return 1;
			break;
		}
	}
	return 0;
}

//return one if a pair and a zero if not
int determinePairCompChoice(struct player* player_1, int numCheck){
	for(int i = 0; i < (numCheck - 1); i++){
		if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
			return 1;
		}
	}
	return 0;
}

int determinePointsCompChoice(struct player* player_1, int roundNum){ //Determines which hand a player has and returns the score of his hand

	//if statement to determine which hand player has, will then return score based on hand
	//going to have to have to create a function for each of the ten hands
	//a royal flush returns ten and a single highcard returns a one
	
	//Sorting
	int size;
	if(roundNum == 1){
		size = 2;
	}else{
		size = (roundNum + 3);
	}
	bubbleSort(player_1, size);

	//for debugging purposes
	printf("\nSorted deck: ");
	for(int i = 0; i < size; i++){
		printf("%d ", player_1->playerDeck[i].value);
	}

	//going to determine what hand (passing size for how many cards to check for)
	if(determineRoyalFlushCompChoice(player_1, size) == 1){
		printf("\nplayer has a royal flush!");
		return 10;
	} else if(determineStraightFlushCompChoice(player_1, size) == 1){
		printf("\nplayer has a straight flush!");
		return 9;
	} else if(determineFourOfAKindCompChoice(player_1, size) == 1){
		printf("\nPlayer has four of a kind!");
		return 8;
	} else if(determineFullHouseCompChoice(player_1, size) == 1){
		printf("\nPlayer has a full house!");
		return 7;
	} else if(determineFlushCompChoice(player_1, size) == 1){
		printf("\nPlayer has flush");
		return 6;
	} else if(determineStraightCompChoice(player_1, size) == 1){
		printf("\nPlayer has a straight");
		return 5;
	} else if(determineThreeOfAKindCompChoice(player_1, size) == 1){
		printf("\nPlayer has a three of a kind");
		return 4;
	} else if(determineTwoPairCompChoice(player_1, size) == 1){
		printf("\nPlayer has a two pair");
		return 3;
	} else if(determinePairCompChoice(player_1, size) == 1){
		printf("\nPlayer has a pair");
		return 2;
	} else {
		printf("\nPlayer only has a high card");
		return 1;
	}
	


}

//end of informed ai section


void determineWinner(int playerOne, int playerTwo, int* potTotal, struct player* player_1, struct player* player_2, struct card userDeck[], struct card compDeck[]){
	if(playerOne > playerTwo){
		printf("\nWinner is player one");
		printf("\nYou won %d chips", *potTotal);
		player_1->chips += *potTotal;
		*potTotal = 0;
	} else if(playerOne < playerTwo){
		printf("\nWinner is player two");
		printf("\nPlayer Two stole %d chips", *potTotal);
		player_2->chips += *potTotal;
		*potTotal = 0;
	} else {

		if(playerOne == 1){ //if both players only have a high card
			int playerOneHighCard = 0;
			int playerTwoHighCard = 0;
			for(int i = 0; i < 7; i++){
				if(player_1->playerDeck[i].value > playerOneHighCard){
					playerOneHighCard = player_1->playerDeck[i].value;
				}
				if(player_2->playerDeck[i].value > playerTwoHighCard){
					playerTwoHighCard = player_2->playerDeck[i].value;
				}
			}
			if(playerOneHighCard > playerTwoHighCard){
				printf("\nWinner is player one with a high card of %d", playerOneHighCard);
				printf("\nYou won %d chips", *potTotal);
				player_1->chips += *potTotal;
				*potTotal = 0;
			} else if (playerOneHighCard < playerTwoHighCard){
				printf("\nWinner is player two with a high card of %d", playerTwoHighCard);
				printf("\nPlayer two stole %d chips", *potTotal);
				player_2->chips+= *potTotal;
				*potTotal = 0;
			} else{ //determine by kicker
				int playerOneKicker = 0;
				int playerTwoKicker = 0;
				for(int i = 0; i < 2; i++){
					if(userDeck[i].value > playerOneKicker){
						playerOneKicker = userDeck[i].value;
					}
					if(compDeck[i].value > playerTwoKicker){
						playerTwoKicker = compDeck[i].value;
					}
				}
				if(playerOneKicker > playerTwoKicker){
					printf("\nPlayer one is the winner");
					printf("\nYou won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneKicker < playerTwoKicker){
					printf("\nPlayer two is the winner");
					printf("\nPlayer two has stolen %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else{
					for(int i = 0; i < 2; i++){
						if(playerOneKicker != userDeck[i].value){
							playerOneKicker = userDeck[i].value;
						}
						if(playerTwoKicker != userDeck[i].value){
							playerTwoKicker = userDeck[i].value;
						}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
				}
			}
		} else if(playerOne == 2 || playerOne == 4){ //if both player have a pair or a three of a kind
				int player1PairValue = 0;
				int player2PairValue = 0;
				for(int i = 0; i < 6; i++){
					if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
						player1PairValue = player_1->playerDeck[i].value;
					}
					if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value){
						player2PairValue = player_2->playerDeck[i].value;
					}
				}
				if(player1PairValue > player2PairValue){
					printf("\nWinner is player one");
					printf("\nYou won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(player1PairValue < player2PairValue){
					printf("\nWinner is player two");
					printf("\nPlayer two stole %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else {
					//determine kicker
					int playerOneKicker = 0;
					int playerTwoKicker = 0;
					for(int i = 0; i < 2; i++){
						if(userDeck[i].value != player1PairValue & userDeck[i].value > playerOneKicker){
							playerOneKicker = userDeck[i].value;
						}
						if(compDeck[i].value != player2PairValue && compDeck[i].value > playerTwoKicker){
							playerTwoKicker = compDeck[i].value;
						}
					}
					if(playerOneKicker > playerTwoKicker){
						printf("\nWinner is player one by a kicker");
						printf("\nYou won %d chips", *potTotal);
						player_1->chips += *potTotal;
						*potTotal = 0;
					} else if(playerOneKicker < playerTwoKicker){
						printf("\nWinner is player two by a kicker");
						printf("\nPlayer two stole %d chips", *potTotal);
						player_2->chips += *potTotal;
						*potTotal = 0;
					} else {
						for(int i = 0; i < 2; i++){
							if(playerOneKicker != userDeck[i].value){
								playerOneKicker = userDeck[i].value;
							}
							if(playerTwoKicker != userDeck[i].value){
								playerTwoKicker = userDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
					}
				}
		} else if(playerOne == 3){//If both players have a two pair
				int playerOneHighestPair = 0;
				int playerTwoHighestPair = 0;
				for(int i = 0; i < 6; i++){
					if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
						if(player_1->playerDeck[i].value > playerOneHighestPair){
							playerOneHighestPair = player_1->playerDeck[i].value;
						}
					}
					if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value){
						if(player_2->playerDeck[i].value > playerTwoHighestPair){
							playerTwoHighestPair = player_2->playerDeck[i].value;
						}
					}
				}
				if(playerOneHighestPair > playerTwoHighestPair){
					printf("\nWinner is player one with a pair of %d's", playerOneHighestPair);
					printf("\nYou won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneHighestPair < playerTwoHighestPair){
					printf("\nWinner is player two with a pair of %d's", playerTwoHighestPair);
					printf("\nPlayer two stole %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else { //determine by kicker
					int playerOneKicker = 0;
					int playerTwoKicker = 0;
					for(int i = 0; i < 2; i++){
						if(userDeck[i].value > playerOneKicker){
							playerOneKicker = userDeck[i].value;
						}
						if(compDeck[i].value > playerTwoKicker){
							playerTwoKicker = compDeck[i].value;
						}
					}
					if(playerOneKicker > playerTwoKicker){
						printf("\nWinner is player one with a kicker");
						printf("\nYou won %d chips", *potTotal);
						player_1->chips += *potTotal;
						*potTotal = 0;
					} else if(playerOneKicker < playerTwoKicker){
						printf("\nWinner is player two with a kicker");
						printf("\nPlayer two stole %d chips", *potTotal);
						player_2->chips += *potTotal;
						*potTotal = 0;
					} else {
						for(int i = 0; i < 2; i++){
							if(playerOneKicker != userDeck[i].value){
								playerOneKicker = userDeck[i].value;
							}
							if(playerTwoKicker != userDeck[i].value){
								playerTwoKicker = userDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
					}
				}
		} else if(playerOne == 5 || playerOne == 9){//Players have a straight
				int playerOneHighCard = 0;
				int playerTwoHighCard = 0;
				for(int i = 0; i < 5; i++){
					if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value - 1 && player_1->playerDeck[i].value == player_1->playerDeck[i+2].value - 2){
						playerOneHighCard = player_1->playerDeck[i].value;
					}
					if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value - 1 && player_2->playerDeck[i].value == player_2->playerDeck[i+2].value - 2){
						playerTwoHighCard = player_2->playerDeck[i].value;
					}
				}
				if(playerOneHighCard > playerTwoHighCard){
					printf("\nWinner is player one");
					printf("\nYou won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneHighCard < playerTwoHighCard){
					printf("\nWinner is player two");
					printf("\nPlayer two stole %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else { //determine by kicker
					int playerOneKicker = 0;
					int playerTwoKicker = 0;
					for(int i = 0; i < 2; i++){
						if(userDeck[i].value > playerOneKicker){
							playerOneKicker = userDeck[i].value;
						}
						if(compDeck[i].value > playerTwoKicker){
							playerTwoKicker = compDeck[i].value;
						}
					}
					if(playerOneKicker > playerTwoKicker){
						printf("\nWinner is player one by a kicker");
						printf("\nYou won %d chips", *potTotal);
						player_1->chips += *potTotal;
						*potTotal = 0;
					} else if(playerOneKicker < playerTwoKicker){
						printf("\nWinner is player two by a kicker");
						printf("\nPlayer two stole %d chips", *potTotal);
						player_2->chips += *potTotal;
						*potTotal = 0;
					} else {
						for(int i = 0; i < 2; i++){
							if(playerOneKicker != userDeck[i].value){
								playerOneKicker = userDeck[i].value;
							}
							if(playerTwoKicker != userDeck[i].value){
								playerTwoKicker = userDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
					}
				}

		} else if(playerOne == 6){ //players have a flush
			char playerOneFlushSuit[9];
			char playerTwoFlushSuit[9];
			int playerOneHighest = 0;
			int playerTwoHighest = 0;
			int playerOneHighestSuitCount = 0;
			int playerTwoHighestSuitCount = 0;
			int playerOneDiamondsPoints = 0;
			int playerOneSpadesPoints = 0;
			int playerOneClubsPoints = 0;
			int playerOneHeartsPoints = 0;
			int playerTwoDiamondsPoints = 0;
			int playerTwoSpadesPoints = 0;
			int playerTwoClubsPoints = 0;
			int playerTwoHeartsPoints = 0;
			for(int i = 0; i < 7; i++){
				if(strcmp(player_1->playerDeck[i].suit, "diamonds") == 0){
					playerOneDiamondsPoints++;
				} else if(strcmp(player_1->playerDeck[i].suit, "spades") == 0){
					playerOneSpadesPoints++;
				} else if(strcmp(player_1->playerDeck[i].suit, "clubs") == 0){
					playerOneClubsPoints++;
				} else if(strcmp(player_1->playerDeck[i].suit, "hearts") == 0){
					playerOneHeartsPoints++;
				} else {
					printf("\nSomething is wrong with the flush tie comparison in determine winner function");
				}

				if(strcmp(player_2->playerDeck[i].suit, "diamonds") == 0){
					playerTwoDiamondsPoints++;
				} else if(strcmp(player_2->playerDeck[i].suit, "spades") == 0){
					playerTwoSpadesPoints++;
				} else if(strcmp(player_2->playerDeck[i].suit, "clubs") == 0){
					playerTwoClubsPoints++;
				} else if(strcmp(player_2->playerDeck[i].suit, "hearts") == 0){
					playerTwoHeartsPoints++;
				} else {
					printf("\nSomething is wrong with the flush tie comparison in determine to wins function");
				}

			}
			if(playerOneDiamondsPoints > playerOneHighestSuitCount){
				playerOneHighestSuitCount = playerOneDiamondsPoints;
				strcpy(playerOneFlushSuit, "diamonds");
			}
			if(playerOneSpadesPoints > playerOneHighestSuitCount){
				playerOneHighestSuitCount = playerOneSpadesPoints;
				strcpy(playerOneFlushSuit, "spades");
			}
			if(playerOneClubsPoints > playerOneHighestSuitCount){
				playerOneHighestSuitCount = playerOneClubsPoints;
				strcpy(playerOneFlushSuit, "clubs");
			}
			if(playerOneHeartsPoints > playerOneHighestSuitCount){
				playerOneHighestSuitCount = playerOneHeartsPoints;
				strcpy(playerOneFlushSuit, "hearts");
			}
			if(playerTwoDiamondsPoints > playerTwoHighestSuitCount){
				playerTwoHighestSuitCount = playerTwoDiamondsPoints;
				strcpy(playerTwoFlushSuit, "diamonds");
			}
			if(playerTwoSpadesPoints > playerTwoHighestSuitCount){
				playerTwoHighestSuitCount = playerTwoSpadesPoints;
				strcpy(playerTwoFlushSuit, "spades");
			}
			if(playerTwoClubsPoints > playerTwoHighestSuitCount){
				playerTwoHighestSuitCount = playerTwoClubsPoints;
				strcpy(playerTwoFlushSuit, "clubs");
			}
			if(playerTwoHeartsPoints > playerTwoHighestSuitCount){
				playerTwoHighestSuitCount = playerTwoHeartsPoints;
				strcpy(playerTwoFlushSuit, "hearts");
			}

			for(int i = 0; i < 7; i++){
				if(strcmp(player_1->playerDeck[i].suit, playerOneFlushSuit) == 0){
					if(player_1->playerDeck[i].value > playerOneHighest){
						playerOneHighest = player_1->playerDeck[i].value;
					}
				}
				if(strcmp(player_2->playerDeck[i].suit, playerTwoFlushSuit) == 0){
					if(player_2->playerDeck[i].value > playerTwoHighest){
						playerTwoHighest = player_2->playerDeck[i].value;
					}
				}
			}
			if(playerOneHighest > playerTwoHighest){
				printf("\nPlayer one has won");
				printf("\nYou won %d chips", *potTotal);
				player_1->chips += *potTotal;
				*potTotal = 0;
			} else if(playerOneHighest < playerTwoHighest){
				printf("\nPlayer two has won");
				printf("\nPlayer two stole %d chips", *potTotal);
				player_2->chips += *potTotal;
				*potTotal = 0;
			} else { //will determine by kicker
				int playerOneKicker = 0;
				int playerTwoKicker = 0;
				for(int i = 0; i < 2; i++){
					if(playerOneKicker < userDeck[i].value){
						playerOneKicker = userDeck[i].value;
					}
					if(playerTwoKicker < compDeck[i].value){
						playerTwoKicker = compDeck[i].value;
					}
				}
				if(playerOneKicker > playerTwoKicker){
					printf("\nPlayer one is winner by a kicker");
					printf("\nYou have won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneKicker < playerTwoKicker){
					printf("\nPlayer two is winner by a kicker");
					printf("\nPlayer two has stole %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else {
					for(int i = 0; i < 2; i++){
						if(playerOneKicker != userDeck[i].value){
							playerOneKicker = userDeck[i].value;
						}
						if(playerTwoKicker != userDeck[i].value){
							playerTwoKicker = userDeck[i].value;
						}
						}

						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
				}
			}

		} else if(playerOne == 7){//players have a full house
				int playerOneThreePeatValue = 0;
				int playerTwoThreePeatValue = 0;
				for(int i = 0; i < 5; i++){
					if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
						if(player_1->playerDeck[i+1].value == player_1->playerDeck[i+2].value){
							playerOneThreePeatValue = player_1->playerDeck[i].value;
						}
					}
					if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value){
						if(player_2->playerDeck[i+1].value == player_2->playerDeck[i+2].value){
							playerTwoThreePeatValue = player_2->playerDeck[i].value;
						}
					}
				}
				if(playerOneThreePeatValue > playerTwoThreePeatValue){
					printf("\nWinner is player one");
					printf("\nYou have won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneThreePeatValue < playerTwoThreePeatValue){
					printf("\nWinner is player two");
					printf("\nPlayer two stole %d chips", *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else { //determine winner from pair
					int playerOneTwoPeatValue = 0;
					int playerTwoTwoPeatValue = 0;
					for(int i = 0; i < 6; i++){
						if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
							if(player_1->playerDeck[i].value != playerOneThreePeatValue){
								playerOneTwoPeatValue = player_1->playerDeck[i].value;
							}
						}
						if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value){
							if(player_2->playerDeck[i].value != playerTwoThreePeatValue){
								playerTwoTwoPeatValue = player_2->playerDeck[i].value;
							}
						}
					}
					if(playerOneTwoPeatValue > playerTwoTwoPeatValue){
						printf("\nWinner is player one");
						printf("\nYou have won %d chips", *potTotal);
						player_1->chips += *potTotal;
						*potTotal = 0;
					} else if(playerOneTwoPeatValue < playerTwoTwoPeatValue){
						printf("\nWinner is player two");
						printf("\nPlayer two stole %d chips", *potTotal);
						player_2->chips += *potTotal;
						*potTotal = 0;
					} else { //determine by kicker
						int playerOneKicker = 0;
						int playerTwoKicker = 0;
						for(int i = 0; i < 2; i++){
							if(playerOneKicker < userDeck[i].value){
								playerOneKicker = userDeck[i].value;
							}
							if(playerTwoKicker < compDeck[i].value){
								playerTwoKicker = compDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nWinner is player one by kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nWinner is player two by a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							for(int i = 0; i < 2; i++){
							    if(playerOneKicker != userDeck[i].value){
								    playerOneKicker = userDeck[i].value;
							}
							    if(playerTwoKicker != userDeck[i].value){
								    playerTwoKicker = userDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
							player_2->chips += *potTotal;
						}

						}
					}

				}

		} else if(playerOne == 8){ //players have a four of a kind
				int playerOneFourPeatValue = 0;
				int playerTwoFourPeatValue = 0;
				for(int i = 0; i < 4; i++){
					if(player_1->playerDeck[i].value == player_1->playerDeck[i+1].value){
						if(player_1->playerDeck[i+1].value == player_1->playerDeck[i+2].value){
							if(player_1->playerDeck[i+2].value == player_1->playerDeck[i+3].value){
								playerOneFourPeatValue = player_1->playerDeck[i].value;
							}
						}
					}
					if(player_2->playerDeck[i].value == player_2->playerDeck[i+1].value){
						if(player_2->playerDeck[i+1].value == player_2->playerDeck[i+2].value){
							if(player_2->playerDeck[i+2].value == player_2->playerDeck[i+3].value){
								playerTwoFourPeatValue = player_1->playerDeck[i].value;
							}
						}
					}
				}
				if(playerOneFourPeatValue > playerTwoFourPeatValue){
					printf("\nWinner is player one");
					printf("\nYou won %d chips", *potTotal);
					player_1->chips += *potTotal;
					*potTotal = 0;
				} else if(playerOneFourPeatValue < playerTwoFourPeatValue){
					printf("\nWinner is player two");
					printf("\nPlayer two stole %d chips" , *potTotal);
					player_2->chips += *potTotal;
					*potTotal = 0;
				} else { //Determine by a kicker
					int playerOneKicker = 0;
					int playerTwoKicker = 0;
					for(int i = 0; i < 2; i++){
						if(playerOneKicker < userDeck[i].value){
							playerOneKicker = userDeck[i].value;
						}
						if(playerTwoKicker < compDeck[i].value){
							playerTwoKicker = compDeck[i].value;
						}
					}
					if(playerOneKicker > playerTwoKicker){
						printf("\nWinner is player one with a kicker");
						printf("\nYou won %d chips", *potTotal);
						player_1->chips += *potTotal;
						*potTotal = 0;
					} else if(playerOneKicker < playerTwoKicker){
						printf("\nWinner is player two with a kicker");
						printf("\nPlayer two stole %d chips");
						player_2->chips += *potTotal;
						*potTotal = 0;
					} else {
						for(int i = 0; i < 2; i++){
							if(playerOneKicker != userDeck[i].value){
								playerOneKicker = userDeck[i].value;
							}
							if(playerTwoKicker != userDeck[i].value){
								playerTwoKicker = userDeck[i].value;
							}
						}
						if(playerOneKicker > playerTwoKicker){
							printf("\nPlayer one won this hand with a kicker");
							printf("\nYou won %d chips", *potTotal);
							player_1->chips += *potTotal;
							*potTotal = 0;
						} else if(playerOneKicker < playerTwoKicker){
							printf("\nPlayer two won this hand with a kicker");
							printf("\nPlayer two stole %d chips", *potTotal);
							player_2->chips += *potTotal;
							*potTotal = 0;
						} else {
							printf("\nHand is a draw and the pot is split");
						        player_1->chips += *potTotal;
						}       player_2->chips += *potTotal;
					}
				}

		} else {
			printf("\nNo fucking way! Both Players have a royal flush and the pot will be split");
			player_1->chips += *potTotal / 2;
			player_2->chips += *potTotal / 2;
		}


	} //end of to determine tie


	}


//Comp player functions

int compDecision_1(int* userDecision, struct player* userPlayer, struct player* compPlayer, int maxBet, int* smallBlind, int* bigBlind, int* potTotal, int roundNum, int compBluff){ //if player calls first
	srand(time(NULL)); //if when function gets called throws an error might be because we seeded before
	int compDecision = rand() % 100 + 1; //generates a random number between one and one hundred
	//int compBluff = rand() % 2;
	
	//will now initiate comp decision
	int score = determinePointsCompChoice(compPlayer, roundNum);
	printf("\nscore is %d", score);

	//round 1 options for comp choice
	if(compBluff == 0){ //comp is not bluffing
		if(score == 1){ //comp has a high card
			if(compDecision <= 97){ //comp chose to call
				printf("\nComputer chose to call");
				return 0;
			}else{ //comp chose to fold
				printf("\nComputer chose to fold");
				printf("\nPot goes to user");
				userPlayer->chips += *potTotal;
				*potTotal = 0;
				return 1;
			}
		}else{ //comp has a pair 
		       if(compDecision <= 30){ //comp chose to call
				printf("\nComputer chose to call");
				return 0;
		       }else{
			       printf("\nComputer chose to raise"); //comp chose to raise
			       compDecision = rand() % maxBet + 1;
			       compPlayer->chips -= compDecision;
			       printf("\n\nComputer chose to raise %d", compDecision);
			       *potTotal += compDecision;
			       return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
		      }
		}
	}else{
		if(score == 1){ //comp has a high card
			if(compDecision <= 35){ //comp chose to call
				printf("\nComputer chose to call");
				return 0;
			}else{ //comp chose to raise
				printf("\nComputer chose to raise");
				compDecision = rand() % maxBet + 1;
				compPlayer->chips -= compDecision;
				printf("\n\nComputer chose to raise %d", compDecision);
				*potTotal += compDecision;
				return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
			}
		}else{ //comp has a pair 
		       if(compDecision <= 70){ //comp chose to call
				printf("\nComputer chose to call");
				return 0;
		       }else{
			       printf("\nComputer chose to raise"); //comp chose to raise
			       compDecision = rand() % maxBet + 1;
			       compPlayer->chips -= compDecision;
			       printf("\n\nComputer chose to raise %d", compDecision);
			       *potTotal += compDecision;
			       return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
		      }
		}

	}

	/*if(compDecision <= 75){ //comp chose to call
		printf("\nComputer chose to call");
		return 0;
	} else if(compDecision < 95){ //comp chose to raise
		printf("\nComputer chose to raise");
		compDecision = rand() % maxBet + 1;
		compPlayer->chips -= compDecision;
		printf("\n\nComputer chose to raise %d", compDecision);
		*potTotal += compDecision;
		return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum);
	} else {
		printf("\nComputer chose to fold"); //Computer chooses to fold (will use continue keyword after displaying winner of the round)
		printf("\nPot goes to user");
		userPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	}*/

	
}

int compDecision_2(int* userDecision, struct player* userPlayer, struct player* compPlayer, int maxBet, int* potTotal, int roundNum, int compBluff){ //if player checks first

	int compDecision = rand() % 100 + 1;

	//will now initiate comp decision
	int score = determinePointsCompChoice(compPlayer, roundNum);
	printf("\nscore is %d", score);

	if(compBluff == 0){ //no bluff
		if(roundNum == 2){
			if(score == 1){ //no bluff, round 2, and a highcard
				if(compDecision <= 80){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to fold");
					printf("\nPot goes to user");
					userPlayer->chips += *potTotal;
					*potTotal = 0;
					return 1;
				}
			}else if(score == 2){ //no bluff, round 2, and a pair
				if(compDecision <= 70){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 95){ //no bluff, round 2, and something better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}
		}else if(roundNum == 3){
			if(score == 1){ //no bluff, round 3, and a highcard
				if(compDecision <= 70){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to fold");
					printf("\nPot goes to user");
					userPlayer->chips += *potTotal;
					*potTotal = 0;
					return 1;
				}
			}else if(score == 2){ //no bluff, round 3, and a pair
				if(compDecision <= 60){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 95){ //no bluff, round 3, better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}
			
		}else{ //round 4
			if(score == 1){ //no bluff, round 4, and a highcard
				if(compDecision <= 45){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to fold");
					printf("\nPot goes to user");
					userPlayer->chips += *potTotal;
					*potTotal = 0;
					return 1;
				}
			}else if(score == 2){ //no bluff, round 4, and a pair
				if(compDecision <= 50){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 95){ //no bluff, round 3, better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}

		}
	}else{ //we bluffing with this one
		if(roundNum == 2){
			if(score == 1){ //bluff, round 2, and a highcard
				if(compDecision <= 50){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}
			}else if(score == 2){ //bluff, round 2, and a pair
				if(compDecision <= 30){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 5){ //bluff, round 2, and something better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}
		}else if(roundNum == 3){
			if(score == 1){ //bluff, round 3, and a highcard
				if(compDecision <= 40){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}
			}else if(score == 2){ //bluff, round 3, and a pair
				if(compDecision <= 20){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 5){ //bluff, round 3, better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}
			
		}else{ //round 4
			if(score == 1){ //bluff, round 4, and a highcard
				if(compDecision <= 30){ 
					printf("\nComputer chose to check");
					return 0;
				}else{
					printf("\nComputer chose to bet");
					compDecision = (rand() % maxBet) + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision; 
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}
			}else if(score == 2){ //bluff, round 4, and a pair
				if(compDecision <= 30){
					printf("\nComputer chose to bet");
					compDecision = rand() % maxBet + 1;
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}else{
				if(compDecision <= 5){ //bluff, round 3, better than a pair
					printf("\nComputer chose to bet");
					compDecision = (rand() % (maxBet / 2)) + ((maxBet / 2) + 1);
					printf("\nComputer bet %d", compDecision);
					compPlayer->chips -= compDecision;
					*potTotal += compDecision;
					return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
				}else{
					printf("\nComputer chose to check");
					return 0;
				}
			}

		}

	}
	

	/*if(compDecision <= 66){ //computer chooses to check 
		printf("\nComputer chose to check");
		return 0;
	} else if(compDecision <= 90){ //computer chooses to bet
		printf("\nComputer chose to bet");
		compDecision = rand() % maxBet + 1;
		printf("\nComputer bet %d", compDecision);
		compPlayer->chips -= compDecision;
		*potTotal += compDecision;
		return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum);
	} else { //computer chooses to fold (announce winner of hand and move on to next round)
		printf("\nComputer chose to fold"); //will use the continue keyword after displaying winner of round
	        printf("\nPot goes to user");
		userPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	}*/

}

int compDecision_1_1(int* userDecision, struct player* userPlayer, struct player* compPlayer, int maxBet, int* potTotal, int roundNum, int compBluff){ //if player going first and decides to bet
	int compDecision = rand() % 100 + 1;
	int score = determinePointsCompChoice(compPlayer, roundNum);
	printf("\nscore is %d", score);

	if(compBluff == 0){
		if(roundNum == 1){
			if(score == 1){
				if(*userDecision <= 100){ //no bluff, round 1, highcard, bet under 101
					if(compDecision <= 85){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}else if(*userDecision <= 250){ //no bluff, round 1, highcard, bet under 251
					if(compDecision <= 75){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}else{ //no bluff, round 1, highcard, bet over 250
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 1;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}
			}else if(score ==2){
				if(*userDecision <= 100){
					if(compDecision <= 60){ //no bluff, round 1, pair, bet under 101
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);

					}
				}else if(*userDecision <= 250){ //no bluff, round 1, pair, bet under 251
					if(compDecision <= 70){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else{ //no bluff, round 1, pair, bet over 250
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}
			} //end of score 2
		}else if(roundNum == 2){
			if(score == 1){
				if(*userDecision <= 100){ //no bluff, round 2, highcard, bet under 101
					if(compDecision <= 60){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}else if(*userDecision <= 250){ //no bluff, round 2, highcard, bet under 251
					if(compDecision <= 35){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}else{ //no bluff, round 2, highcard, bet over 250
					if(compDecision <= 20){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}
			}else if(score == 2){ //no bluff, round 2, pair, bet under 101
				if(*userDecision <= 100){
					if(compDecision <= 70){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
					
				}else if(*userDecision <= 250){ //no bluff, round 2, pair, bet under 251
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}else{ //no bluff, round 2, pair, bet over 250
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else if(compDecision < 90){
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}
			}else{ //no bluff, round 2, anything better than a pair, bet of any kind
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

			}
		}else if(roundNum == 3){
			if(score == 1){
				if(*userDecision <= 100){ //no bluff, round 3, highcard, bet under 101
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}else if(*userDecision <= 250){ //no bluff, round 3, highcard, bet under 251
					if(compDecision <= 25){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}


				}else{ //no bluff, round 3, highcard, bet over 250
					if(compDecision <= 15){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}

				}
			}else if(score == 2){
				if(*userDecision <= 100){ //no bluff, round 3, pair, bet under 101
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else if(*userDecision <= 250){ //no bluff, round 3, pair, bet under 251
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}	
				}else{ //no bluff, round 3, pair, bet over 250
					if(compDecision <= 75){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else if(compDecision < 90){
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}
			}else{ //no bluff, round 3, anything better than a pair, any bet
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
			}
		}else{ //round 4
			if(score == 1){
				if(*userDecision <= 100){ //no bluff, round 4, highcard, bet under 101
					if(compDecision <= 20){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}else if(*userDecision <= 250){ //no bluff, round 4, highcard, bet under 251
					if(compDecision <= 10){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}else{ //no bluff, round 4, highcard, bet over 250 
					if(compDecision <= 5){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}
			}else if(score == 2){
				if(*userDecision <= 100){ //no bluff, round 4, pair, bet under 101
					if(compDecision <= 85){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}else if(*userDecision <= 250){ //no bluff, round 4, pair, bet under 251
					if(compDecision <= 95){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}	
				}else{ //no bluff, round 4, pair, bet over 250
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else if(compDecision < 90){
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}else{
						printf("\nComputer chose to fold");
						printf("\nPot goes to user");
						userPlayer->chips += *potTotal;
						return 1;
					}
				}
			}else{ //no bluff, round 4, anything better than a pair, any bet
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

			}
		} //end of round 4
	}else if(compBluff == 1){
		if(roundNum == 1){
			if(score == 1){
				if(*userDecision <= 100){ //bluff, round 1, highcard, bet under 101
					if(compDecision <= 70){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else if(*userDecision <= 250){ //bluff, round 1, highcard, bet under 251
					if(compDecision <= 60){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else{ //bluff, round 1, highcard, bet over 250
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 1;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}
				}
			}else if(score == 2){
				if(*userDecision <= 100){
					if(compDecision <= 50){ //bluff, round 1, pair, bet under 101
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else if(*userDecision <= 250){ //bluff, round 1, pair, bet under 251
					if(compDecision <= 60){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else{ //bluff, round 1, pair, bet over 250
					if(compDecision <= 70){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}
			}else{
				printf("something wrong with scoring for comp check compDecision_1_1");
			}
		}else if(roundNum == 2){
			if(score == 1){
				if(*userDecision <= 100){ //bluff, round 2, highcard, bet under 101
					if(compDecision <= 70){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}else if(*userDecision <= 250){ //bluff, round 2, highcard, bet under 251
					if(compDecision <= 75){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}else{ //bluff, round 2, highcard, bet over 250
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}
			}else if(score == 2){ //bluff, round 2, pair, bet under 101
				if(*userDecision <= 100){
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
					
				}else if(*userDecision <= 250){ //bluff, round 2, pair, bet under 251
					if(compDecision <= 85){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}else{ //bluff, round 2, pair, bet over 250
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

				}
			}else{ //bluff, round 2, anything better than a pair, bet of any kind
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}

			}

		}else if(roundNum == 3){
			if(score == 1){
				if(*userDecision <= 100){ //bluff, round 3, highcard, bet under 101
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}else if(*userDecision <= 250){ //bluff, round 3, highcard, bet under 251
					if(compDecision <= 75){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}


				}else{ //bluff, round 3, highcard, bet over 250
					if(compDecision <= 85){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}
			}else if(score == 2){
				if(*userDecision <= 100){ //bluff, round 3, pair, bet under 101
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else if(*userDecision <= 250){ //bluff, round 3, pair, bet under 251
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}	
				}else{ //bluff, round 3, pair, bet over 250
					if(compDecision <= 95){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}
			}else{ //bluff, round 3, anything better than a pair, any bet
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
			}
			
		}else if(roundNum == 4){
			if(score == 1){
				if(*userDecision <= 100){ //bluff, round 4, highcard, bet under 101
					if(compDecision <= 50){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}else if(*userDecision <= 250){ //bluff, round 4, highcard, bet under 251
					if(compDecision <= 75){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}


				}else{ //bluff, round 4, highcard, bet over 250
					if(compDecision <= 85){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);	
					}

				}
			}else if(score == 2){
				if(*userDecision <= 100){ //bluff, round 4, pair, bet under 101
					if(compDecision <= 80){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}else if(*userDecision <= 250){ //bluff, round 3, pair, bet under 251
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}	
				}else{ //bluff, round 4, pair, bet over 250
					if(compDecision <= 95){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
				}
			}else{ //bluff, round 4, anything better than a pair, any bet
					if(compDecision <= 90){
						printf("\nComputer chose to call players bet");
						*potTotal += *userDecision;
						compPlayer->chips -= *userDecision;
						return 0;
					}else{
						printf("\nMax bet: %d", maxBet);
						compDecision = rand() % maxBet + *userDecision;
						printf("\nComputer chose to raise %d chips", compDecision);
						compPlayer->chips -= compDecision;
						*potTotal += compDecision;
						return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
					}
			}

		}

	}


	/*
	if(compDecision < 70){ //computers calls players raise
		printf("\nComputer chose to call players bet");
		*potTotal += *userDecision;
		compPlayer->chips -= *userDecision;
		return 0;
	} else if(compDecision < 95){ //User must then decide to call computer bet or fold
		printf("\nMax bet: %d", maxBet);
		compDecision = rand() % maxBet + *userDecision;
		printf("\nComputer chose to raise %d chips", compDecision);
		compPlayer->chips -= compDecision;
		*potTotal += compDecision;
		return userDecision_1_1(userDecision, userPlayer, compPlayer, potTotal, &compDecision, maxBet, roundNum, compBluff);
	} else {
		printf("\nComputer chose to fold");
		printf("\nUser wins pot");
		userPlayer->chips += *potTotal;
		*potTotal = 0;
		return 1;
	}*/
}


//Print Functions

void printIntro(void){
	printf("\n\n***Texas Hold'em Poker 2023***\n\n");
}

void printTableDeck(struct tableDeck* deck){
	for(int i = 0; i < 52; i++){
		printf("%s %d\n", deck->deck[i].suit, deck->deck[i].value);
	}
}

void printPlayerUI_1(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);
}

void printOptions_1() {
	printf("\nPlease enter your next move:\n");
	printf("1.) Call\n");
	printf("2.) Raise\n");
	printf("3.) Fold\n");
	printf("4.) Leave\n");
	printf("\nEnter here: ");
}


void printPlayerUI_2(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);

	//printing table deck
	
	printf("\nTable deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[2].value, userPlayer->playerDeck[2].suit);
	printf("[%d %s] ", userPlayer->playerDeck[3].value, userPlayer->playerDeck[3].suit);
	printf("[%d %s] ", userPlayer->playerDeck[4].value, userPlayer->playerDeck[4].suit);
}

void printOptions_2() {
	printf("\nPlease enter your next move:\n");
	printf("1.) Check\n");
	printf("2.) Bet\n");
	printf("3.) Fold\n");
	printf("4.) Leave\n");
	printf("\nEnter here: ");
}


void printPlayerUI_3(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);

	//printing table deck
	
	printf("\nTable deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[2].value, userPlayer->playerDeck[2].suit);
	printf("[%d %s] ", userPlayer->playerDeck[3].value, userPlayer->playerDeck[3].suit);
	printf("[%d %s] ", userPlayer->playerDeck[4].value, userPlayer->playerDeck[4].suit);
	printf("[%d %s] ", userPlayer->playerDeck[5].value, userPlayer->playerDeck[5].suit);
}


void printPlayerUI_4(struct player* userPlayer, int* totalPot){
	printf("\nPot: %d\n", *totalPot);
	printf("\nPlayer Chips: %d\n", userPlayer->chips);
	
	//printing player's cards 
	
	printf("\nYour deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[0].value, userPlayer->playerDeck[0].suit);
	printf("[%d %s]\n", userPlayer->playerDeck[1].value, userPlayer->playerDeck[1].suit);

	//printing table deck
	
	printf("\nTable deck: ");
	printf("[%d %s] ", userPlayer->playerDeck[2].value, userPlayer->playerDeck[2].suit);
	printf("[%d %s] ", userPlayer->playerDeck[3].value, userPlayer->playerDeck[3].suit);
	printf("[%d %s] ", userPlayer->playerDeck[4].value, userPlayer->playerDeck[4].suit);
	printf("[%d %s] ", userPlayer->playerDeck[5].value, userPlayer->playerDeck[5].suit);
	printf("[%d %s] ", userPlayer->playerDeck[6].value, userPlayer->playerDeck[6].suit);
}


void printEndOfHand(struct player* player_1, struct player* player_2, int* potTotal){
	printf("\n\nEnd of Hand\n");
	printf("\nPot Total: %d\n\n", *potTotal);
	printf("User Cards: [%d %s] [%d %s]  ", player_1->playerDeck[0].value, player_1->playerDeck[0].suit, player_1->playerDeck[1].value, player_1->playerDeck[1].suit);
	printf("|  |  Computer Cards: [%d %s] [%d %s]", player_2->playerDeck[0].value, player_2->playerDeck[0].suit, player_2->playerDeck[1].value, player_2->playerDeck[1].suit);

	//printing table deck
	
	printf("\n\nTable deck: ");
	printf("[%d %s] ", player_1->playerDeck[2].value, player_1->playerDeck[2].suit);
	printf("[%d %s] ", player_1->playerDeck[3].value, player_1->playerDeck[3].suit);
	printf("[%d %s] ", player_1->playerDeck[4].value, player_1->playerDeck[4].suit);
	printf("[%d %s] ", player_1->playerDeck[5].value, player_1->playerDeck[5].suit);
	printf("[%d %s] ", player_1->playerDeck[6].value, player_1->playerDeck[6].suit);
}

void printToNextHand(){
	printf("\n\n\n--Next Hand Shuffle in Progress--\n\n");
}

void printToNextRound(){
	printf("\n\n--On to next round--\n\n");
}


int main() {

	//printing the intro

	printIntro();

	//initializing card structures and tableDeck structure
	struct tableDeck table_deck;

	for(int i = 0; i < 13; i++){
		table_deck.deck[i] = (struct card){"diamonds", i + 2};
	}

	for(int i = 13; i < 26; i++){
		table_deck.deck[i] = (struct card){"spades", i - 11};
	}

	for(int i = 26; i < 39; i++){
		table_deck.deck[i] = (struct card){"hearts", i - 24};
	}

	for(int i = 39; i < 52; i++){
		table_deck.deck[i] = (struct card){"clubs", i - 37};
	}

	//printTableDeck(&table_deck);

	//shuffleDeck(&table_deck);


	//Cards are now initialized using compound literals, and are in the array table_deck.deck, going to handout cards and initialize players now
	
	struct player userPlayer;
	struct player computerPlayer;
	int chipCount = 5000;
	const int maxBet = 500;
	int potTotal = 0;
	int smallBlind = 10;
	int bigBlind = 20;
	int userDecision;
	int computerDecision;
	int determineNextMove; //if equal to zero nothing happens, if equal to one we continue and go to next hand, and if two we break out of loop
        int roundNum;


	userPlayer.chips = chipCount;
	computerPlayer.chips = chipCount;

	//beginning of game (card handout)
	
	//beginning of while loop
	
	while(userPlayer.chips >= 0){
		shuffleDeck(&table_deck);
	
	        userPlayer.playerDeck[0] = table_deck.deck[0];
	        userPlayer.playerDeck[1] = table_deck.deck[1];

	        computerPlayer.playerDeck[0] = table_deck.deck[2];
	        computerPlayer.playerDeck[1] = table_deck.deck[3];

	        //will now input input the five table deck cards in the player's player deck, although they will not be aware, we will simulate it being on the
	        //table by keeping it hidden during gameplay, only the first two cards will be shown to the player. This will make the program more efficient
	
	        userPlayer.playerDeck[2] = table_deck.deck[4];
	        userPlayer.playerDeck[3] = table_deck.deck[5];
	        userPlayer.playerDeck[4] = table_deck.deck[6];
	        userPlayer.playerDeck[5] = table_deck.deck[7];
	        userPlayer.playerDeck[6] = table_deck.deck[8];

	        computerPlayer.playerDeck[2] = table_deck.deck[4];
	        computerPlayer.playerDeck[3] = table_deck.deck[5];
	        computerPlayer.playerDeck[4] = table_deck.deck[6];
	        computerPlayer.playerDeck[5] = table_deck.deck[7];
          	computerPlayer.playerDeck[6] = table_deck.deck[8];


	        //player deck and table deck have been initialized, chips have given to their players and a max bet has been put in place
 	        //will now being initial bets and decisions
	
	        potTotal += smallBlind + bigBlind;
	        userPlayer.chips -= smallBlind;
	        computerPlayer.chips -= bigBlind;

		//determines whether computer is going to bluff or not this hand
		int compBluff = (rand() % 100) + 1;
		printf("compBluff: %d", compBluff);
		if(compBluff <= 80){ //comp will not bluff
			compBluff = 0;
		}else{ //comp will bluff
			compBluff = 1;
		}

	        //initial bets have been placed into the pot, for the first round of poker the users can either choose to: (one) call the big blind,
	        //(two) fold and end the round, (three) raise and give a number for how much you would like to
	
	        //beginning of ui
	
          	printPlayerUI_1(&userPlayer, &potTotal);
        	printOptions_1();
		roundNum = 1;
         	determineNextMove = userDecision_1(&userDecision, &userPlayer, &computerPlayer, maxBet, &smallBlind, &bigBlind, &potTotal, roundNum, compBluff);
		if(determineNextMove == 1){
			printf("\n\nMoving on to next hand");
			printToNextHand();
			continue;
		}
		if(determineNextMove == 2){
			printf("\n\nGame Over");
			break;
		}
        	//compDecision_1(&computerPlayer, &maxBet, &potTotal);

	        //beginning of 2nd round

		printToNextRound();
        	printPlayerUI_2(&userPlayer, &potTotal);
        	printOptions_2();
		roundNum = 2;
         	determineNextMove = userDecision_2(&userDecision, &userPlayer, &computerPlayer, &potTotal, maxBet, roundNum, compBluff);
		if(determineNextMove == 1){
			printf("\n\nMove on to the next hand");
			printToNextHand();
			continue;
		}
		if(determineNextMove == 2){
			printf("\n\nGame Over");
			break;
		}
        	//compDecision_2(&computerPlayer, &maxBet, &potTotal);

         	//beginning of 3rd round

		printToNextRound();
         	printPlayerUI_3(&userPlayer, &potTotal);
          	printOptions_2();
		roundNum = 3;
         	determineNextMove = userDecision_2(&userDecision, &userPlayer, &computerPlayer, &potTotal, maxBet, roundNum, compBluff);
		if(determineNextMove == 1){
			printf("\n\nMoving on to the next hand");
			printToNextHand();
			continue;
		}
		if(determineNextMove == 2){
			printf("\n\nGame Over");
			break;
		}
         	//compDecision_2(&computerPlayer, &maxBet, &potTotal);

         	//beginning of 4th and final round

		printToNextRound();
         	printPlayerUI_4(&userPlayer, &potTotal);
         	printOptions_2();
		roundNum = 4;
         	determineNextMove = userDecision_2(&userDecision, &userPlayer, &computerPlayer, &potTotal, maxBet, roundNum, compBluff);
		if(determineNextMove == 1){
			printf("\n\nMoving on to the next hand");
			printToNextHand();
			continue;
		}
		if(determineNextMove == 2){
			printf("\n\nGame Over)");
			break;
		}
         	//compDecision_2(&computerPlayer, &maxBet, &potTotal);

         	//determining winner
	
         	printEndOfHand(&userPlayer, &computerPlayer, &potTotal);
		printf("\n");
         	//need to take player decks to determine a kicker, will input into determine to determine kicker if necessary
         	//need to do before array is sorted in the players struct's
         	struct card userDeck[2] = {userPlayer.playerDeck[0], userPlayer.playerDeck[1]};
        	struct card compDeck[2] = {computerPlayer.playerDeck[0], computerPlayer.playerDeck[1]};
         	int userPoints = determinePoints(&userPlayer);
		printf("\n");
         	int compPoints = determinePoints(&computerPlayer);
		printf("\n");
         	determineWinner(userPoints, compPoints, &potTotal, &userPlayer, &computerPlayer, userDeck, compDeck);
		printToNextHand();

	} //End of while loop


}
