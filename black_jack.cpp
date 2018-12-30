#include <iostream>		// std::cout
#include <sstream>		// std::stringstream
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <array> 	// std::array
#include <map>		// std::map
#include <string> 	// string concatenation

using namespace std;

// class Card;
// class Hand;
// class Player;
// class AI;
// class House;
// class Game;

// random generator function:
int myrandom (int i) { return rand()%i;}

// Cards['1s'] => 1;
map<string, int>	CardDict = {
	    {"1s", 1},{"2s",2},{"3s", 3},{"4s", 4},{"5s", 5},{"6s", 6},{"7s", 7},{"8s", 8},{"9s", 9},{"10s", 10},{"js", 10},{"qs", 10},{"ks", 10},
	    {"1d", 1},{"2d",2},{"3d", 3},{"4d", 4},{"5d", 5},{"6d", 6},{"7d", 7},{"8d", 8},{"9d", 9},{"10d", 10},{"jd", 10},{"qd", 10},{"kd", 10},
	    {"1h", 1},{"2h",2},{"3h", 3},{"4h", 4},{"5h", 5},{"6h", 6},{"7h", 7},{"8h", 8},{"9h", 9},{"10h", 10},{"jh", 10},{"qh", 10},{"kh", 10},
	    {"1c", 1},{"2c",2},{"3c", 3},{"4c", 4},{"5c", 5},{"6c", 6},{"7c", 7},{"8c", 8},{"9c", 9},{"10c", 10},{"jc", 10},{"qc", 10},{"kc", 10}
	};
string DeckArr[] = {"1s","2s","3s","4s","5s","6s","7s","8s","9s","10s","js","qs","ks",
					"1d","2d","3d","4d","5d","6d","7d","8d","9d","10d","jd","qd","kd",
					"1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","jh","qh","kh",
					"1c","2c","3c","4c","5c","6c","7c","8c","9c","10c","jc","qc","kc"
	};
map<string, int> DecisionDict = {
	{"H", 1}, {"h", 1}, {"S", 2}, {"s", 2}, {"P", 3}, {"p", 3}, {"D", 4}, {"d", 4},
};
////////////////////////////////////////////////////////////
class Card
{
   public:
      vector<string> deck;
      int numberOfAI;
      // Member functions declaration
      Card();
      void setDeck(int num);
      void shuffleDeck(void);
      void showDeck(void);
      string drawCard();
};
Card::Card(){}
// Member functions definitions
void Card::setDeck(int num){
	int i=0, j=0;
	numberOfAI = num;
	deck.clear();
	for(i=0; i<num ; i++){
		// deck.assign(myints, myints + sizeof(myints) / sizeof(int) );
		for(j=0; j<52 ; j++){
			deck.push_back(DeckArr[j]);
		}
	}
}
void Card::shuffleDeck(void){
	// using myrandom:
	// srand(time(NULL));
	random_shuffle ( deck.begin(), deck.end(), myrandom);
}
void Card::showDeck(void){
	for(int i = 0; i<deck.size() ; i++){
		cout << ' ' << deck.at(i) << ' ';
	}
}
string Card::drawCard(){
	string str;
	str = deck.back();
	deck.pop_back();
	if( deck.size() < 1){
		setDeck(numberOfAI);
		shuffleDeck();
	}
	return str;
}
/////////////////////////////////////////////////////////////////////
class Hand
{
   public:
      int point;         // point of a deamonmoney of a dealer
      vector<string> handCard; // cards that Hand has
      int decision;	// hit or stand or doublling down or split
      string decisionString; // H = hit, S = stand, P = split, D = doubling down
      int battingMoney;
      // Member functions declaration
      Hand();
      int houseRule(void);
      void setPoint(int p);
      int getPoint(void);
      void sumPoint(void);
      int sumTwoPoints(int i, int j);
      void sumMoney(int p);
      void setCard(string p);
      string getAndEraseCard();
      string showCard(void);
      void clearCardPointBattingMoney(void);
      int isBusted();
      int isBlackJack();
};

// Member functions definitions
Hand::Hand(){}
int Hand::houseRule(void){
	int decision = 1; // 1 : hit // 2 : stand // 3: split
	if( point < 13){
		decision = 1;
	}
	else if( (point>=13) && (point<16) ){
		if(rand()%2 ){
			decision =2;
		}
	}
	else if(point >= 17){
		decision = 2;
	}
	return decision;
}

void Hand::setPoint(int p){
	point = p;
}
int Hand::getPoint(void){
	return point;
}
// sum all card's point in Hand's cards
void Hand::sumPoint(void){
	int cardPoint = 0;
	point = 0;
	for(int i=0; i<handCard.size(); i++){
		cardPoint = CardDict[handCard[i]];
		if( cardPoint == 1){
			if( point+11 < 22) point += 11;
			else point += 1;
		}else{
			point += cardPoint;
		}
	}
}

int Hand::sumTwoPoints(int point_i, int point_j){
	int cardPoint = 0;
	if( point_i != 1 && point_j != 1){
		cardPoint = point_i + point_j;
	}else if( point_i != 1 && point_j == 1){
		if( point_i+11 < 22) cardPoint = point_i + 11;
		else cardPoint = point_i + point_j;
	}else if( point_i == 1 && point_j != 1){
		if( point_j+11 < 22) cardPoint = point_j + 11;
		else cardPoint = point_i + point_j;
	}else{ // when two of them are ACE
		cardPoint = point_i + point_j;
	}
	return cardPoint;
}

void Hand::setCard(string p){
	handCard.push_back(p);
}
string Hand::getAndEraseCard(){
	string str = handCard.back();
	handCard.pop_back();
	return str;
}
string Hand::showCard(void){
	string str = " ";
	for(int i = 0; i<handCard.size() ; i++){
		str += handCard.at(i);
		if( i == handCard.size()-1){str += "     ";}
		else{str += ",     "; }
	}
	return str;
}
void Hand::clearCardPointBattingMoney(void){
	handCard.clear();
	point = 0;
	battingMoney = 0;
}
int Hand::isBusted(){
	if(point > 21) return 1;
	else return 0;
}
int Hand::isBlackJack(){
	if( (point == 21) && (handCard.size()==2) ) return 1;
	else return 0;
}

////////////////////////////////////////////////////////////////////
class Player : public Hand
{
   public:
     // int aliveFlag;
     int doubleFlag;
    	double playerPossiblePointCounts[31] = {0};
   	double totalPossiblePointCounts;
   	double possiblePointCountsBusted;
      // Member functions declaration
	Player();
	void win();
	void lose();
	void push();
	void betting();
	void doublingDown();
	void split();
	void hit();
	void stand();
	// int isAlive();
	int isDoubled();
	void computePlayerStats();
};
Player::Player() : Hand(){
	// aliveFlag = 1;
	doubleFlag = 0;
	// playerPossiblePointCounts = {0};
	totalPossiblePointCounts = 0;
	possiblePointCountsBusted = 0;
}
// Member functions definitions
void Player::win(){

}
void Player::lose(){

}
void Player::push(){

}
void Player::betting(){

}
void Player::doublingDown(){

}
void Player::split(){

}
void Player::hit(){

}
void Player::stand(){

}
int Player::isDoubled(){
	return doubleFlag;
}
void Player::computePlayerStats(){

}

class AI : public Player
{
	public:
		vector<Player> SubPlayers;
		vector<string> aiCard;
		vector<string> aiDeck;
		// vector<string> aiDeckRemained;
		double housePossiblePointCounts[31] = {0};
		double houseTotalPossiblePointCounts;
   		double housePossiblePointCountsBusted;
		int aiCardSize;
		int totalCardLength;
		int aiLevel;
		int splitFlag;
		int aliveFlag;
		int winCount;
		int money;
		// int doubleFlag;
		AI();
		void setFlags();
		int isSplited();
		int isAlive();
		// int isDoubled();
		void algo();
		void alphago();
		void putCardStack(string str);
		void setTotalCardLengthAndDeck(int i);
		void setAiLevel(int i);
		void clearAI();
		void setMoney(int i);
};
AI::AI(): Player(){
	winCount = 0;
	money = 0;
}

void AI::setFlags(){
	splitFlag = 0;
	aliveFlag = 1;
	// housePossiblePointCounts = {0};
}

int AI::isSplited(){
	return splitFlag;
}
int AI::isAlive(){
	return aliveFlag;
}

void AI::algo(){}

void AI::alphago(){}

void AI::putCardStack(string str){
	if( aiCard.size() <= aiCardSize){
		aiCard.push_back(str);
	}else{
		aiCard.erase(aiCard.begin());
		aiCard.push_back(str);
	}
}

void AI::setTotalCardLengthAndDeck(int num){
	totalCardLength = 52*num;
	// modify
	int i=0, j=0;
	aiDeck.clear();
	for(i=0; i<num ; i++){
		// aiDeck.assign(myints, myints + sizeof(myints) / sizeof(int) );
		for(j=0; j<52 ; j++){
			aiDeck.push_back(DeckArr[j]);
		}
	}
	splitFlag = 0;
	for(i=0; i<31; i++) housePossiblePointCounts[i] = 0;
	houseTotalPossiblePointCounts=0;
   	housePossiblePointCountsBusted=0;
}

void AI::setAiLevel(int i){
	aiLevel = i;
	switch(aiLevel){
		case 1: aiCardSize = 0;
			break;
		case 2: aiCardSize = totalCardLength/4 - 1;
			break;
		case 3: aiCardSize = totalCardLength/2 - 1;
			break;
		case 4: aiCardSize = totalCardLength*3/4 -1 ;
			break;
		case 5: aiCardSize = totalCardLength - 1;
			break;
		default: aiCardSize = 0;
			break;
	}
}
void AI::clearAI(){
	int i=0,j=0;
	splitFlag = 0;
	for(i=0; i<31; i++) housePossiblePointCounts[i] = 0;
	houseTotalPossiblePointCounts=0;
   	housePossiblePointCountsBusted=0;
   	aiDeck.clear();
	for(i=0; i<totalCardLength/52 ; i++){
		for(j=0; j<52 ; j++){
			aiDeck.push_back(DeckArr[j]);
		}
	}
}
void AI::setMoney(int i){
	money = i;
}
///////////////////////////////////////////////////////////////////////

class House : public Hand
{
   public:
   	// int playerPossiblePointCounts[31];
   	// int totalPossiblePointCounts;
   	// int possiblePointCountsBusted;
   	// Member functions declaration
   	House();
   	// void computeHouseStats();
};
House::House() : Hand(){
	// playerPossiblePointCounts = {0};
	// totalPossiblePointCounts = 0;
	// possiblePointCountsBusted = 0;
}
// Member functions definitions
// void House::computeHouseStats(){
// }

////////////////////////////////////////////////////////////////////////
class Game
{
   public:
	Card CardClass;
	House HouseClass;
	vector<AI> AIs;
	AI MainBoy;

	int numOfAI;
	vector<int> aiLevels;
	string startPlayFlag;
	string cardDrawed;

	int DEALER_MONEY; //10 billion
	int PLAYER_MONEY; // 1000 million
	int FIRST_BET_MONEY;
	int BET_MONEY;
	int gameCount;
	int comparePoint;
	// Member functions declaration
	Game();
	int comparePoints(int a, int b);
	void putCardStacks(string str, int i);
	void AIAlgoIter();
	void computeHouseStats(int i);
	void computeAIPlayerStats(int i, int j);
	string AIAlgo(int i, int j);
	int AIAction(int i, int j, int k);
	int mainBoyAction(int i, int j);
	void houseAlgo();
	int houseAction(int i);
	void displayResult();
	void init();
	void run();
};

// Game(const vector<string>& names){
// }
Game::Game(){
	// numOfAI = 0;
}
// Member functions definitions
int Game::comparePoints(int a, int b){
	int result=0;
	if(a>b){	result=-1;}
	else if( a == b){result = 0;}
	else{result = 1;	}
	return result;
}

void Game::putCardStacks(string str, int i){
	if( i ==1 ){
		MainBoy.putCardStack(str);
		vector<AI>::iterator pAI;
		for (pAI = AIs.begin() ; pAI != AIs.end(); ++pAI){
			if( pAI->isAlive()) pAI->putCardStack(str);
		}
	}
}

void Game::AIAlgoIter(){
	// MainBoy Turn
	int decisionFlag = 0;
	int actionEndFlag = 0;
	string decisionStr;
	int i = 0, j=0, k=0;
	if(MainBoy.isAlive()){
		for(i=0; i<MainBoy.SubPlayers.size(); ){
			while(actionEndFlag == 0){
				// cout << "Player        :"<<MainBoy.SubPlayers[i].showCard()<<" ("<<MainBoy.SubPlayers[i].getPoint()<<")"<<endl;
				cout << "Player    "<< "   ";
				for(k=0; k<MainBoy.SubPlayers.size() ; k++) cout<<"("<<MainBoy.SubPlayers[k].battingMoney<<")";
				cout << "  :  ";
				for(k=0; k<MainBoy.SubPlayers.size() ; k++) cout<<"["<<MainBoy.SubPlayers[k].showCard()<<"("<<MainBoy.SubPlayers[k].getPoint()<<")] ";
				cout << endl;
				while(1){
					if(MainBoy.SubPlayers.size() > 1) cout << "\nAction-"<<i<<"  :  ";
					else cout << "\nAction       : ";
					cin >> decisionStr;
					if( (decisionFlag = DecisionDict[decisionStr]) )
						break;
				}
				actionEndFlag = mainBoyAction(decisionFlag, i);
				i += actionEndFlag;
			}
			actionEndFlag = 0;
		}
	}

	decisionFlag = 0; actionEndFlag = 0;
	for(i=0; i<AIs.size(); i++){
		if(AIs[i].isAlive()){
			cout << "\n\nTurn of AI"<<(i+1)<<endl;
			for(j=0; j<AIs[i].SubPlayers.size(); ){
				while(actionEndFlag == 0){
					// cout << "Player        :"<<AIs[i].SubPlayers[i].showCard()<<" ("<<AIs[i].SubPlayers[i].getPoint()<<")"<<endl;
					cout << "AI    ";
					for(k=0; k<AIs[i].SubPlayers.size() ; k++) cout<<"("<<AIs[i].SubPlayers[k].battingMoney<<")";
					cout << "  :  ";
					for(k=0; k<AIs[i].SubPlayers.size() ; k++) cout<<"["<<AIs[i].SubPlayers[k].showCard()<<"("<<AIs[i].SubPlayers[k].getPoint()<<")] ";
					cout << endl;
					while(1){
						decisionStr = AIAlgo(i, j);
						if( (decisionFlag = DecisionDict[decisionStr]) ){
							if(AIs[i].SubPlayers.size() > 1) cout << "\nAction-"<<j<<"  :  " << decisionStr<<endl;
							else cout << "\nAction       : " << decisionStr<<endl;
							break;
						}
					}
					actionEndFlag = AIAction(decisionFlag, i, j);
					j += actionEndFlag;
				}
				actionEndFlag = 0;
			}
		}
	}
}

void Game::computeHouseStats(int i_ai){
	int i=0, j=0, k=0;
	int addedPoint=0, addedPointForHit=0, point_i=0, point_j =0;
	for(j=0; j<AIs[i_ai].aiDeck.size(); j++){
		point_i = CardDict[HouseClass.handCard[0]];
		point_j = CardDict[AIs[i_ai].aiDeck.at(j)];
		addedPoint = HouseClass.sumTwoPoints(point_i, point_j );
		if( addedPoint < 13 ){ // hit, plus 2 to housePossiblePointCount
			for(k=0; k<AIs[i_ai].aiDeck.size(); k++ ){
				if( k == j ) continue;
				point_j = CardDict[AIs[i_ai].aiDeck.at(k)];
				addedPointForHit = HouseClass.sumTwoPoints(addedPoint, point_j );
				AIs[i_ai].housePossiblePointCounts[addedPointForHit] += 2.0;
			}
		}else if( addedPoint>=13 && addedPoint<17 ){ // hit or stand, plus 1 to housePossiblePointCount repectively
			// for the hit case, plus 1 for each
			for(k=0; k<AIs[i_ai].aiDeck.size(); k++ ){
				if( k == j ) continue;
				point_j = CardDict[AIs[i_ai].aiDeck.at(k)];
				addedPointForHit = HouseClass.sumTwoPoints(addedPoint, point_j );
				AIs[i_ai].housePossiblePointCounts[addedPointForHit] += 1.0;
			}
			// for stand case, plus 1 for each
			AIs[i_ai].housePossiblePointCounts[addedPoint] += 1.0;
		}else if( addedPoint >= 17 ){ // when addedPoint >= 17 // stand, plus 2 to housePossiblePointCount
			AIs[i_ai].housePossiblePointCounts[addedPoint] += 2.0;
		}else{
		}
	}


	// normalize housePossiblePointCounts by 2 cause we count twice
	for(i=0; i<31; i++){
		AIs[i_ai].housePossiblePointCounts[i] /= 2;
	}
	// compute Total counts and Busted Counts
	for(k=0; k<31; k++){
		AIs[i_ai].houseTotalPossiblePointCounts += AIs[i_ai].housePossiblePointCounts[k];
		if( k > 21) AIs[i_ai].housePossiblePointCountsBusted += AIs[i_ai].housePossiblePointCounts[k];
	}
}

void Game::computeAIPlayerStats(int i_ai, int j_subplayer){
	int k=0;
	int addedPoint=0, addedPointForHit=0, point_k =0;
	// for(k=0; k<AIs[i_ai].SubPlayers[j_subplayer].handCard.size(); k++){
	// 	point_k = CardDict[AIs[i_ai].SubPlayers[j_subplayer].handCard ];
	// 	addedPoint = HouseClass.sumTwoPoints(addedPoint, point_k);
	// }
	addedPoint = AIs[i_ai].SubPlayers[j_subplayer].getPoint();
	// for stand case, plus 1 for this.
	AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[addedPoint] += 1.0;
	// for hit case, plus 1 for these.
	for(k=0; k<AIs[i_ai].aiDeck.size(); k++ ){
		point_k = CardDict[AIs[i_ai].aiDeck.at(k)];
		addedPointForHit = HouseClass.sumTwoPoints(addedPoint, point_k );
		AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[addedPointForHit] += 1.0;
	}
	// compute Total counts and Busted Counts
	for(k=0; k<31; k++){
		AIs[i_ai].SubPlayers[j_subplayer].totalPossiblePointCounts += AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[k];
		if( k > 21) AIs[i_ai].SubPlayers[j_subplayer].possiblePointCountsBusted += AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[k];
	}
}

string Game::AIAlgo(int i_ai, int j_subplayer){
	// compute unused cards in the deck
	double probHitWin=0, probStandWin=0;
	double denoTotalCounts =0, nomiHit=0, nomiStand=0;
	string decisionFromAlgo;
	vector<string>::iterator aiDeckIter;
	int i=0 ,j=0;
	if(AIs[i_ai].aiLevel == 0){
		int deci_temp = 0;
		deci_temp = AIs[i_ai].houseRule();
		if( AIs[i_ai].SubPlayers[0].getPoint() < 13){
			deci_temp = 1;
		}
		else if( (AIs[i_ai].SubPlayers[0].getPoint()>=13) && (AIs[i_ai].SubPlayers[0].getPoint()<16) ){
			if(rand()%2 ){
				deci_temp =2;
			}
		}
		else if(AIs[i_ai].SubPlayers[0].getPoint() >= 17){
			deci_temp = 2;
		}
		if( deci_temp == 1){
			decisionFromAlgo = "H";
		}else{
			decisionFromAlgo = "S";
		}
	}else{
		AIs[i].aiDeck.clear();
		for(i=0; i<AIs.size() ; i++){
			for(j=0; j<52 ; j++){
				AIs[i].aiDeck.push_back(DeckArr[j]);
			}
		}
		for(i=0; i < AIs[i_ai].aiCard.size(); i++){
			for(aiDeckIter=AIs[i_ai].aiDeck.begin(), j=0; j < AIs[i_ai].aiDeck.size(); j++){
				if(AIs[i_ai].aiCard.at(i) == AIs[i_ai].aiDeck.at(j)){
					aiDeckIter += j;
					AIs[i_ai].aiDeck.erase(aiDeckIter);
					break;
				}
			}
		}
		// score computation for House based on AIs[i_ai]'s aiDeck
		computeHouseStats(i_ai);

		// score computation for Player based on AIs[i_ai]'s aiDeck
		computeAIPlayerStats(i_ai, j_subplayer);

		// compute Probabilities for winning when both in Stand and Hit cases
		denoTotalCounts = AIs[i_ai].houseTotalPossiblePointCounts * AIs[i_ai].SubPlayers[j_subplayer].totalPossiblePointCounts;

		// winning probability when Hit
		for(i=0; i<22 ; i++){
			if(AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[i] > 0){
				for(j=0; j<i; j++){
					nomiHit += AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[i]*AIs[i_ai].housePossiblePointCounts[j];
				}
			}
		}
		for(i=22; i<31 ; i++){
			if(AIs[i_ai].housePossiblePointCounts[i] > 0){
				for(j=0; j<22; j++){
					nomiHit += AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[j]*AIs[i_ai].housePossiblePointCounts[i];
				}
			}
		}
		// nomiHit += AIs[i_ai].housePossiblePointCountsBusted;
		probHitWin = nomiHit/denoTotalCounts;

		// winning probability when Stand
		i = AIs[i_ai].SubPlayers[j_subplayer].getPoint();
		if(AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[i] > 0){
			for(j=0; j<i; j++){
				nomiStand += AIs[i_ai].SubPlayers[j_subplayer].playerPossiblePointCounts[i]*AIs[i_ai].housePossiblePointCounts[j];
			}
		}
		nomiStand += AIs[i_ai].housePossiblePointCountsBusted;
		probStandWin = nomiStand/AIs[i_ai].houseTotalPossiblePointCounts;

		// if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=17 ){
		// 	decisionFromAlgo = "S";
		// }else if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() < 17 && AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=12 ){
		// 	if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() <= 16){
		// 		if( CardDict[HouseClass.handCard[0]] <7 ){
		// 			decisionFromAlgo = "S";
		// 			return decisionFromAlgo;
		// 		}
		// 		if( CardDict[HouseClass.handCard[0]] <= 11 && CardDict[HouseClass.handCard[0]] > 7){
		// 			decisionFromAlgo = "H";
		// 			return decisionFromAlgo;
		// 		}
		// 	}
		// 	if( probHitWin >= probStandWin ){
		// 		decisionFromAlgo = "H";
		// 	}else{
		// 		decisionFromAlgo = "S";
		// 	}
		// 	// decisionFromAlgo = "H";
		// }else{
		// 	decisionFromAlgo = "H";
		// }

		if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=18 ){
			if( (probHitWin - probStandWin) > 0.1 ){
				decisionFromAlgo = "H";
			}else{
				decisionFromAlgo = "S";
			}
		}else if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() < 18 && AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=12 ){
			if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() <= 17){
				if( CardDict[HouseClass.handCard[0]] <7 ){
					if( (probHitWin - probStandWin) > 0.1 ){
						decisionFromAlgo = "H";
					}else{
						decisionFromAlgo = "S";
					}
					return decisionFromAlgo;
				}
				if( CardDict[HouseClass.handCard[0]] <= 11 && CardDict[HouseClass.handCard[0]] > 7){
					if( (probHitWin - probStandWin) < -0.1 ){
						decisionFromAlgo = "S";
					}else{
						decisionFromAlgo = "H";
					}
					return decisionFromAlgo;
				}
			}
			if( probHitWin >= probStandWin ){
				decisionFromAlgo = "H";
			}else{
				decisionFromAlgo = "S";
			}
		}else{
			if( AIs[i_ai].SubPlayers[j_subplayer].handCard.size() <=2 ){
				if( (probHitWin - probStandWin) > 0.5 ){
					if( AIs[i_ai].SubPlayers[j_subplayer].handCard[0] == AIs[i_ai].SubPlayers[j_subplayer].handCard[1] ){
						decisionFromAlgo = "P";
					}else{
						decisionFromAlgo = "D";
					}
				}else{
					decisionFromAlgo = "H";
				}
			}
			decisionFromAlgo = "H";
		}
		// if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=17 ){
		// 	if( (probHitWin - probStandWin) > 0.1 ){
		// 		decisionFromAlgo = "H";
		// 	}else{
		// 		decisionFromAlgo = "S";
		// 	}
		// }else if( AIs[i_ai].SubPlayers[j_subplayer].getPoint() < 17 && AIs[i_ai].SubPlayers[j_subplayer].getPoint() >=12 ){
		// 	if( probHitWin >= probStandWin ){
		// 		decisionFromAlgo = "H";
		// 	}else{
		// 		decisionFromAlgo = "S";
		// 	}
		// }else{
		// 	decisionFromAlgo = "H";
		// }


		// if( probHitWin >= probStandWin ){
		// 	decisionFromAlgo = "H";
		// }else{
		// 	decisionFromAlgo = "S";
		// }

		// if( probHitWin > probStandWin ){
		// 	decisionFromAlgo = "H";
		// }else{
		// 	decisionFromAlgo = "S";
		// }

	}

	return decisionFromAlgo;
}

int Game::AIAction(int decisionFlag, int i , int j){
	int standFlag =0, k=0;
	string str, cardDrawed;
	vector<Player>::iterator it = AIs[i].SubPlayers.begin();
	if( AIs[i].SubPlayers[j].doubleFlag ){  // when double flag is on...
		if(decisionFlag == 1){ // 1 // hit
				// compute point
				// cout << "Action       : " << "H" << endl;
				cardDrawed = CardClass.drawCard();
				if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
				AIs[i].SubPlayers[j].setCard(cardDrawed);
				AIs[i].SubPlayers[j].sumPoint();
				// bust check
				if( AIs[i].SubPlayers[j].isBusted() == 1){
					if(AIs[i].SubPlayers.size() > 1) cout << "\nAI"<<i+1<<"-"<<j<<"  Bust!!!!!!!\n";
					else cout << "\nAI"<<i+1<<" Bust!!!!!!!\n";
				}
				return 1;
		}else if(decisionFlag == 2){
			return 1;
		}
		else{
			cout << "\nUndefined Actions.. Please type among those (H, S, P, D)"<< endl;
		}
	}else{  // when double flag is down..
		if( AIs[i].isSplited() ){
			if(decisionFlag == 1){ // 1 // hit when splitted..
				// compute point
				// cout << "\nBets one more time : "<< BET_MONEY << endl;
				// AIs[i].SubPlayers[j].battingMoney += BET_MONEY;
				cardDrawed = CardClass.drawCard();
				if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
				AIs[i].SubPlayers[j].setCard(cardDrawed);
				AIs[i].SubPlayers[j].sumPoint();
				// bust check
				if( AIs[i].SubPlayers[j].isBusted() == 1){
					if(AIs[i].SubPlayers.size() > 1) cout << "\nAI"<<i+1<<"-"<<j<<"  Bust!!!!!!!\n";
					else cout << "\nAI"<<i+1<<" Bust!!!!!!!\n";
					return 1;
				}
			}
		}else{
			if(decisionFlag == 1){ // 1 // hit when not splitted..
				// compute point
				cardDrawed = CardClass.drawCard();
				if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
				AIs[i].SubPlayers[j].setCard(cardDrawed);
				AIs[i].SubPlayers[j].sumPoint();
				// bust check
				if( AIs[i].SubPlayers[j].isBusted() == 1){
					if(AIs[i].SubPlayers.size() > 1) cout << "\nAI"<<i+1<<"-"<<j<<"  Bust!!!!!!!\n";
					else cout << "\nAI"<<i+1<<" Bust!!!!!!!\n";
					return 1;
				}
			}
		}
		if( decisionFlag == 2){ // 2// stand
			return 1;
		}else if( decisionFlag == 3){ // 3 // split
			cout << "\nBets one more time : "<< BET_MONEY << endl;
			it += j;
			AIs[i].SubPlayers.insert(it+1, Player());
			AIs[i].SubPlayers[j+1].clearCardPointBattingMoney();
			str = AIs[i].SubPlayers[i].getAndEraseCard();
			AIs[i].SubPlayers[j+1].setCard(str);
			AIs[i].SubPlayers[j+1].battingMoney += BET_MONEY;
			AIs[i].splitFlag = 1;
			cout << "Player    "<< "   ";
			// display status
			for(k=0; k<AIs[i].SubPlayers.size() ; k++) cout<<"("<<AIs[i].SubPlayers[k].battingMoney<<")";
			cout << "  :  ";
			for(k=0; k<AIs[i].SubPlayers.size() ; k++) cout<<"["<<AIs[i].SubPlayers[k].showCard()<<"("<<AIs[i].SubPlayers[k].getPoint()<<")] ";
			cout << endl;
			// hit one more card
			for(k=0; k<AIs[i].SubPlayers.size() ; k++){
				// AIs[i].SubPlayers[k].battingMoney += BET_MONEY;
	    			cardDrawed = CardClass.drawCard();
	    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
	    			AIs[i].SubPlayers[k].setCard(cardDrawed);
	    			AIs[i].SubPlayers[k].sumPoint();
				}
		}else if(decisionFlag == 4 ){ // 4 // Doubling down
			AIs[i].SubPlayers[j].doubleFlag = 1;
			AIs[i].SubPlayers[j].battingMoney *= 2;
		}else{
			cout << "\nUndefined Actions.. Please type among those (H, S, P, D)"<< endl;
		}
	}
	return 0;
}

int Game::mainBoyAction(int decisionFlag, int i){
	int standFlag =0, k=0;
	string str, cardDrawed;
	vector<Player>::iterator it = MainBoy.SubPlayers.begin();
	if( MainBoy.SubPlayers[i].isDoubled() ){ // when Double flag is on
		if(decisionFlag == 1){ // 1 // hit when not splitted
			// compute point
			cardDrawed = CardClass.drawCard();
			if( CardClass.deck.size() == CardClass.numberOfAI*52){
				for(i=0; i<AIs.size(); i++){
					AIs[i].aiCard.clear();
				}
				MainBoy.aiCard.clear();
			}
			else putCardStacks(cardDrawed,1);
			MainBoy.SubPlayers[i].setCard(cardDrawed);
			MainBoy.SubPlayers[i].sumPoint();
			// bust check
			if( MainBoy.SubPlayers[i].isBusted() == 1)
				return 1;
			return 1;
		}else if( decisionFlag == 2){ // 2// stand
			return 1;
		}
		else{
			cout << "\nUndefined Actions.. Please type among those (H, S, P, D)"<< endl;
		}
	}else{  // when double flag is down
		if( MainBoy.isSplited() ){
			if(decisionFlag == 1){ // 1 // hit when splitted
				// compute point
				// cout << "\nBets one more time : "<< BET_MONEY << endl;
				// MainBoy.SubPlayers[i].battingMoney += BET_MONEY;
				cardDrawed = CardClass.drawCard();
				if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
				MainBoy.SubPlayers[i].setCard(cardDrawed);
				MainBoy.SubPlayers[i].sumPoint();
				// bust check
				if( MainBoy.SubPlayers[i].isBusted() == 1){
					if(MainBoy.SubPlayers.size() > 1) cout << "\nPlayer's Action-"<<i<<"  :  Bust!!!!!!!";
					else cout << "\nPlayer   !!!!!!!!";
					return 1;
				}
			}
		}else{
			if(decisionFlag == 1){ // 1 // hit when not splitted
				// compute point
				cardDrawed = CardClass.drawCard();
				if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
				MainBoy.SubPlayers[i].setCard(cardDrawed);
				MainBoy.SubPlayers[i].sumPoint();
				// bust check
				if( MainBoy.SubPlayers[i].isBusted() == 1)
					return 1;
			}
		}
		if( decisionFlag == 2){ // 2// stand
			return 1;
		}else if( decisionFlag == 3){ // 3 // split
			cout << "\nBets one more time : "<< BET_MONEY << endl;
			it += i;
			MainBoy.SubPlayers.insert(it+1, Player());
			MainBoy.SubPlayers[i+1].clearCardPointBattingMoney();
			str = MainBoy.SubPlayers[i].getAndEraseCard();
			MainBoy.SubPlayers[i+1].setCard(str);
			MainBoy.SubPlayers[i+1].battingMoney += BET_MONEY;
			MainBoy.SubPlayers[i+1].sumPoint();
			MainBoy.splitFlag = 1;
			cout << "Player    "<< "   ";
			// display status
			for(k=0; k<MainBoy.SubPlayers.size() ; k++) cout<<"("<<MainBoy.SubPlayers[k].battingMoney<<")";
			cout << "  :  ";
			for(k=0; k<MainBoy.SubPlayers.size() ; k++) cout<<"["<<MainBoy.SubPlayers[k].showCard()<<"("<<MainBoy.SubPlayers[k].getPoint()<<")] ";
			cout << endl;
			// hit one more card
			for(k=0; k<MainBoy.SubPlayers.size() ; k++){
				// MainBoy.SubPlayers[k].battingMoney += BET_MONEY;
	    			cardDrawed = CardClass.drawCard();
	    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
					for(int i_card=0; i_card<AIs.size(); i_card++){
						AIs[i_card].aiCard.clear();
					}
					MainBoy.aiCard.clear();
				}
				else putCardStacks(cardDrawed,1);
	    			MainBoy.SubPlayers[k].setCard(cardDrawed);
	    			MainBoy.SubPlayers[k].sumPoint();
				}
		}else if( decisionFlag == 4){ // 4 // Doubling down
			MainBoy.SubPlayers[i].doubleFlag = 1;
			MainBoy.SubPlayers[i].battingMoney *= 2;
		}else{
			// cout << "\nUndefined Actions.. Please type among those (H, S, P, D)"<< endl;
		}
	}
	return 0;
}

void Game::houseAlgo(){
	string pause;
	int decisionFlag = 0;
	int actionEndFlag = 0;
	HouseClass.sumPoint();
	putCardStacks(HouseClass.handCard[1] ,1);
	while(actionEndFlag == 0){
		cout << "House    : "<<HouseClass.showCard()<<" ("<<HouseClass.getPoint()<<")"<<endl;
		decisionFlag = HouseClass.houseRule();
		actionEndFlag = houseAction(decisionFlag);
	}
}

int Game::houseAction(int decisionFlag){
	int standFlag =0;
	int i=0;
	if(decisionFlag == 1){ // 1 // hit
		// display
		cout << "Action       : " << "H" << endl;
		// compute point
		cardDrawed = CardClass.drawCard();
		if( CardClass.deck.size() == CardClass.numberOfAI*52){
			for(i=0; i<AIs.size(); i++){
				AIs[i].aiCard.clear();
			}
			MainBoy.aiCard.clear();
		}
		else putCardStacks(cardDrawed,1);
		HouseClass.setCard(cardDrawed);
		HouseClass.sumPoint();
		// bust check
		if( HouseClass.isBusted() == 1)
			return 1;
	}else if( decisionFlag == 2){ // 2 // stand
		// display
		cout << "Action       : " << "S" << endl;
		return 1;
	}
	return 0;
}
void Game::displayResult(){
	int i=0, j=0;
	if( MainBoy.isAlive()){
		for(j=0; j<MainBoy.SubPlayers.size() ; j++) {
			if( HouseClass.isBusted() ){ // when House busted
				if( MainBoy.SubPlayers[j].isBusted() ){ // busted lose
					MainBoy.money -= MainBoy.SubPlayers[j].battingMoney;
					cout << "Player-"<<j<<" : Lose!!!!"<<endl;
				}else{ // win
					if( MainBoy.SubPlayers[j].isBlackJack() ){
						MainBoy.money += 3*MainBoy.SubPlayers[j].battingMoney/2;
					}else{
						MainBoy.money += MainBoy.SubPlayers[j].battingMoney;
					}
					MainBoy.winCount += 1;
					cout << "Player-"<<j<<" : Win!!!!"<<endl;
				}
			}else if( HouseClass.isBlackJack() == 0 ){ // when House is not blackjack
				if( MainBoy.SubPlayers[j].isBusted() ){ // busted lose
					MainBoy.money -= MainBoy.SubPlayers[j].battingMoney;
					cout << "Player-"<<j<<" : Lose!!!!"<<endl;
				}else{ // not busted
					if( MainBoy.SubPlayers[j].isBlackJack() ){
						MainBoy.money += 3*MainBoy.SubPlayers[j].battingMoney/2;
						MainBoy.winCount += 1;
						cout << "Player-"<<j<<" : Win!!!!"<<endl;
					}else if( MainBoy.SubPlayers[j].getPoint() > HouseClass.getPoint() ){ // win
						MainBoy.money += MainBoy.SubPlayers[j].battingMoney;
						MainBoy.winCount += 1;
						cout << "Player-"<<j<<" : Win!!!!"<<endl;
					}else{ // lose
						MainBoy.money -= MainBoy.SubPlayers[j].battingMoney;
						cout << "Player-"<<j<<" : Lose!!!!"<<endl;
					}
				}
			}else{ // when house is blackjack
				if( MainBoy.SubPlayers[j].isBlackJack() ){ // equal point - push
					cout << "Player-"<<j<<" : Push!!!!"<<endl;
				}else{
					MainBoy.money -= MainBoy.SubPlayers[j].battingMoney;
					cout << "Player-"<<j<<" : Lose!!!!"<<endl;
				}
			}
		}
	}
	for(i=0; i<AIs.size() ; i++){
		if( AIs[i].isAlive() ){
			for(j=0; j<AIs[i].SubPlayers.size() ; j++) {
				if( HouseClass.isBusted() ){ // when House busted
					if( AIs[i].SubPlayers[j].isBusted() ){ // busted lose
						AIs[i].money -= AIs[i].SubPlayers[j].battingMoney;
						cout << "AI"<<i<<"-"<<j<<" : Lose!!!!"<<endl;
					}else{ // win
						if( AIs[i].SubPlayers[j].isBlackJack() ){
							AIs[i].money += 3*AIs[i].SubPlayers[j].battingMoney/2;
						}else{
							AIs[i].money += AIs[i].SubPlayers[j].battingMoney;
						}
						AIs[i].winCount += 1;
						cout << "AI"<<i<<"-"<<j<<" : Win!!!!"<<endl;
					}
				}else if( HouseClass.isBlackJack() == 0 ){ // when House is not blackjack
					if( AIs[i].SubPlayers[j].isBusted() ){ // busted lose
						AIs[i].money -= AIs[i].SubPlayers[j].battingMoney;
						cout << "AI"<<i<<"-"<<j<<" : Lose!!!!"<<endl;
					}else{ // not busted
						if( AIs[i].SubPlayers[j].isBlackJack() ){
							AIs[i].money += 3*AIs[i].SubPlayers[j].battingMoney/2;
							AIs[i].winCount += 1;
							cout << "AI"<<i<<"-"<<j<<" : Win!!!!"<<endl;
						}else if( AIs[i].SubPlayers[j].getPoint() > HouseClass.getPoint() ){ // win
							AIs[i].money += AIs[i].SubPlayers[j].battingMoney;
							AIs[i].winCount += 1;
							cout << "AI"<<i<<"-"<<j<<" : Win!!!!"<<endl;
						}else{ // lose
							AIs[i].money -= AIs[i].SubPlayers[j].battingMoney;
							cout << "AI"<<i<<"-"<<j<<" : Lose!!!!"<<endl;
						}
					}
				}else{ // when house is blackjack
					if( AIs[i].SubPlayers[j].isBlackJack() ){ // equal point - push
						cout << "AI"<<i<<"-"<<j<<" : Push!!!!"<<endl;
					}else{
						AIs[i].money -= AIs[i].SubPlayers[j].battingMoney;
						cout << "AI"<<i<<"-"<<j<<" : Lose!!!!"<<endl;
					}
				}
			}
		}
	}
}

void Game::init(){
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%						     	%" << endl;
	cout << "%						     	%" << endl;
	cout << "%						     	%" << endl;
	cout << "%		B L A C K      J A C K	     			 %" << endl;
	cout << "%						     	%" << endl;
	cout << "%						     	%" << endl;
	cout << "%						     	%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

	cout << "\nWelcome to the Black Jack world!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	while(1){
		cout << "\n\nNumber of AI (0 ~ 3) : ";
		cin >> numOfAI;
		if( (numOfAI>=0) && (numOfAI <= 3))
			break;
	}
	cout << "\n--------------------------" << endl;
	cout << "Level of AI" << endl << endl;
	cout << "Dummy	: 1" << endl;
	cout << "Low	     : 2" << endl;
	cout << "Mid	     : 3" << endl;
	cout << "High	: 4" << endl;
	cout << "Master	: 5" << endl;
	cout << "--------------------------" << endl;
	cout << "Choose AI level" << endl;
	int levTemp = 0;
	int i =0;
	if( numOfAI == 0){

	}else{
		for(i=0; i<numOfAI ; ){
			// if(numOfAI==0) break;
			cout << "\nLevel of AI" << i+1 << " : ";
			cin >> levTemp;
			if( (levTemp>=1) && (levTemp<=5) ){
				aiLevels.push_back(levTemp);
				i += 1;
			}else{ cout << "\nWrong AI level, please type again(1 ~ 5 )"; }
		}
	}
	cout << "\n--------------------------" << endl << endl;

	// string player
	DEALER_MONEY = 10000000; //10 billion
	PLAYER_MONEY = 500000; // 1000 million
	FIRST_BET_MONEY = 500;
	BET_MONEY = 500;
	gameCount = 0;
	comparePoint = 0;

	// initialize dealer's state
	HouseClass.clearCardPointBattingMoney();

	MainBoy = (AI());
	MainBoy.setTotalCardLengthAndDeck(numOfAI+2);
	MainBoy.setMoney(PLAYER_MONEY);
	MainBoy.setAiLevel(0);
	MainBoy.setFlags();
	MainBoy.aliveFlag = 1;
	MainBoy.SubPlayers.push_back(Player());
	MainBoy.SubPlayers[0].clearCardPointBattingMoney();
	if(numOfAI ==0 ){
		AIs.push_back(AI());
		AIs[0].setTotalCardLengthAndDeck(numOfAI+2);
		AIs[0].setMoney(PLAYER_MONEY);
		AIs[0].setFlags();
		AIs[0].aliveFlag = 0;
		AIs[0].setAiLevel(0);
		AIs[0].SubPlayers.push_back(Player());
		AIs[0].SubPlayers[0].clearCardPointBattingMoney();
	}else{
		for(i=0; i<numOfAI ; i++){
			AIs.push_back(AI());
			AIs[i].setTotalCardLengthAndDeck(numOfAI+2);
			AIs[i].setMoney(PLAYER_MONEY);
			AIs[i].setFlags();
			AIs[i].setAiLevel(aiLevels[i]);
			AIs[i].SubPlayers.push_back(Player());
			AIs[i].SubPlayers[0].clearCardPointBattingMoney();
		}
	}
	// initialize Card deck
	srand(time(NULL));
	CardClass.setDeck(numOfAI+1);
	CardClass.shuffleDeck();
}

void Game::run(){
	double accuracy[AIs.size()] ={0};
	while(1){
		int i = 0, j = 0;
		// int tempBattingMoney=0, pushFlag =0;
		gameCount += 1;
		cout << "Bats: " << FIRST_BET_MONEY << endl;
		vector<AI>::iterator pAI;
		// initialize points before new game

		if( gameCount > 1){
			HouseClass.clearCardPointBattingMoney();
			// with leaving AiCard stack and Total money
			// we can erase point, cards, batting money
			MainBoy.SubPlayers.clear();
			// then re-initiate subplayers
			MainBoy.SubPlayers.push_back(Player());
			// tempBattingMoney = MainBoy.SubPlayers[0].battingMoney;
			MainBoy.SubPlayers[0].clearCardPointBattingMoney();
			MainBoy.clearAI();
			for (pAI = AIs.begin() ; pAI != AIs.end(); ++pAI){
		    		if( pAI->isAlive()){
		    			pAI->SubPlayers.clear();
		    			pAI->SubPlayers.push_back(Player());
		    			// tempBattingMoney = pAI->SubPlayers[0].battingMoney;
		    			pAI->SubPlayers[0].clearCardPointBattingMoney();
		   //  			if(push == 1){
					// 	MainBoy.SubPlayers[0].battingMoney = tempBattingMoney;
					// }
		    			pAI->clearAI();
		    		}
		    	}
			CardClass.shuffleDeck();
			for(i=0; i<CardClass.deck.size(); i++){
				cout << " "<< CardClass.deck.at(i)<< " ";
			}

			for(i=0; i<AIs.size(); i++){
				for(j=0; j<AIs[i].aiCard.size(); j++){
					cout << " "<< AIs[i].aiCard.at(j)<< " ";
				}
			}
		}
		// AIs get cards and open them
		if( MainBoy.isAlive()){
    			// MainBoy.sumMoney(-FIRST_BET_MONEY);
			MainBoy.SubPlayers[0].battingMoney += BET_MONEY;
    			cardDrawed = CardClass.drawCard();
    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
    				for(i=0; i<AIs.size(); i++){
    					AIs[i].aiCard.clear();
    				}
    				MainBoy.aiCard.clear();
    			}else putCardStacks(cardDrawed,1);
    			MainBoy.SubPlayers[0].setCard(cardDrawed);
    			cardDrawed = CardClass.drawCard();
    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
    				for(i=0; i<AIs.size(); i++){
    					AIs[i].aiCard.clear();
    				}
    				MainBoy.aiCard.clear();
    			} else putCardStacks(cardDrawed,1);
    			MainBoy.SubPlayers[0].setCard(cardDrawed);
    			MainBoy.SubPlayers[0].sumPoint();
    		}
		for (pAI = AIs.begin() ; pAI != AIs.end(); ++pAI){
	    		if( pAI->isAlive()){
	    			// pAI->sumMoney(-FIRST_BET_MONEY);
	    			pAI->SubPlayers[0].battingMoney += BET_MONEY;
	    			cardDrawed = CardClass.drawCard();
	    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
	    				for(i=0; i<AIs.size(); i++){
	    					AIs[i].aiCard.clear();
	    				}
	    				MainBoy.aiCard.clear();
	    			}
	    			else putCardStacks(cardDrawed,1);
	    			pAI->SubPlayers[0].setCard(cardDrawed);
	    			cardDrawed = CardClass.drawCard();
	    			if( CardClass.deck.size() == CardClass.numberOfAI*52){
	    				for(i=0; i<AIs.size(); i++){
	    					AIs[i].aiCard.clear();
	    				}
	    				MainBoy.aiCard.clear();
	    			}
	    			else putCardStacks(cardDrawed,1);
	    			pAI->SubPlayers[0].setCard(cardDrawed);
	    			pAI->SubPlayers[0].sumPoint();
	    		}
		}

		// House get cards and open 1 card
		cardDrawed = CardClass.drawCard();
		if( CardClass.deck.size() == CardClass.numberOfAI*52){
			for(i=0; i<AIs.size(); i++){
				AIs[i].aiCard.clear();
			}
			MainBoy.aiCard.clear();
		}
		else putCardStacks(cardDrawed,1);
		HouseClass.setCard(cardDrawed);
		HouseClass.sumPoint();
		// do not put card in AiCard
		cardDrawed = CardClass.drawCard();
		if( CardClass.deck.size() == CardClass.numberOfAI*52){
			for(i=0; i<AIs.size(); i++){
				AIs[i].aiCard.clear();
			}
			MainBoy.aiCard.clear();
		}
		else putCardStacks(cardDrawed,0);
		HouseClass.setCard(cardDrawed);

		// status screen
		cout << "House		: " << HouseClass.handCard.at(0) << ",	X 	( >" << HouseClass.getPoint()<< " )"<<endl;
		if( MainBoy.isAlive() ){
			cout << "Player    "<<"   ("<<MainBoy.SubPlayers[0].battingMoney<<")     : "<<MainBoy.SubPlayers[0].showCard()<<" ("<<MainBoy.SubPlayers[0].getPoint()<<")"<<endl;
		}
		for(i=0; i<AIs.size() ; i++){
			if( AIs[i].isAlive() ){
				cout << "AI"<< i+1 <<"   ("<<AIs[i].SubPlayers[0].battingMoney<<")     : "<<AIs[i].SubPlayers[0].showCard()<<" ("<<AIs[i].SubPlayers[0].getPoint()<<")"<<endl;
			}
		}

		cout << "\nTurn of Player  --- Choose your action: Hit(H), Stand(S), Split(P)" << endl;
		AIAlgoIter();
		cout << "\n-------------------------------" << endl;
		cout << "\nOpen the house card\n"<<endl;
		houseAlgo();

		cout << "\nResult"<<endl;
		cout << "House    : "<<HouseClass.showCard()<<" ("<<HouseClass.getPoint()<<")"<<endl;
		cout << "Player"<<"   ";
		for(j=0; j<MainBoy.SubPlayers.size() ; j++) cout<<"("<<MainBoy.SubPlayers[j].battingMoney<<")";
		cout << "  :  ";
		for(j=0; j<MainBoy.SubPlayers.size() ; j++) cout<<"["<<MainBoy.SubPlayers[j].showCard()<<"("<<MainBoy.SubPlayers[j].getPoint()<<")] ";
		cout << endl;
		for(i=0; i<AIs.size() ; i++){
			if( AIs[i].isAlive() ){
				cout << "AI"<< i+1 <<"   ";
				for(j=0; j<AIs[i].SubPlayers.size() ; j++) cout<<"("<<AIs[i].SubPlayers[j].battingMoney<<")";
				cout << "  :  ";
				for(j=0; j<AIs[i].SubPlayers.size() ; j++) cout<<"["<<AIs[i].SubPlayers[j].showCard()<<"("<<AIs[i].SubPlayers[j].getPoint()<<")] ";
				cout << endl;
			}
		}

		displayResult();

		cout << "\n\nDo you wanna play BlackJack? [yes : no] " << endl;
		cin >> startPlayFlag;
		if( startPlayFlag == "no"){break;}
	}
}

//////////////////////////////////////////////////////////////
int main(int argc, char *argv[] ){

	Game blackjack;
	blackjack.init();
	blackjack.run();

	return 0;
}