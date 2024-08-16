#include "gameloop.h"

Game::Game(Player p1, Player p2){
    Game::p1 = p1;
    Game::p2 = p2;
    Game::turn = 1;
}

void Game::nextTurn(){

    // get the input
    PlayingCard card = PlayingCard(); 
    if(turn == 1){
        card = p1.selectCard(1);
    } else {
        card = p2.selectCard(1);
    }
    
    // ======== OUTPUT ============
    std::cout << "Card:" + card.toString() + "\n";

    // apply effect
    switch(card.cardType){
        case 0: 
            damageEffect(card);
            break;
    }

    // ======== OUTPUT ============    
    std::cout << "Player 1:" + p1.toString() + "\n";
    std::cout << "Player 2:" + p2.toString() + "\n";

    // switch turns
    if(Game::turn == 1) {
        Game::turn = 2;
    } else {
        Game::turn = 1;
    }
}

bool Game::isGameOver(){
    if(p1.getHitPoints() <= 0 || p2.getHitPoints() <= 0 || (p1.getHand().size() == 0 && p2.getHand().size() == 0)){
        return true;
    }
    return false;
}

void Game::damageEffect(PlayingCard &card){
    if(turn == 1){
        if(card.getTarget() == 0){
            Game::p1.damage(card.getValue());
        } else {
            Game::p2.damage(card.getValue());  
        }
    }
    else{
        if(card.getTarget() == 0){
            Game::p2.damage(card.getValue());
        } else {
            Game::p1.damage(card.getValue());  
        }
    }    
}


void start(){
    Player p1 = Player(100, 100, generateHand(7));
    Player p2 = Player(100, 100, generateHand(12));

    Game game = Game(p1, p2);

    while(!game.isGameOver()){
        game.nextTurn();
    }
}

std::vector<PlayingCard> generateHand(int numCards){
    std::vector<PlayingCard> hand;
    for(int i = 0; i < numCards; i++){
        PlayingCard card = PlayingCard(1, (enum Type) 0, 10);
        hand.push_back(card);
    }
    return hand;
}
