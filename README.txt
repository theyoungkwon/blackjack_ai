## Statistical Blackjack AI

#### Description
Implemented an blackjack game and AI by statistically modeling Hit and Stand probability.
The implementation is based on C++.


In blackjack game, you can play with a total of 0 ~ 3 AI agents.


The source code consists of one file and it has 6 classes as follows: 
1) Cards, 2) Hand, 3) Player, 4) House, 5) Game, 6) AI.


Here are inheritance relations.
1. Player inherits Hand
2. AI inherits Player
3. House inherits Player


#### How to run the code
Here is the way to run the code.

- go to a working directory
- compile the code
- $g++ -std=c++11 black_jack black_jack.cpp

- execute
- $./black_jack

