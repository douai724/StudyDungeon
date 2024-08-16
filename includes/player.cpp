#include "player.h"

Player::Player(){}

Player::Player(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand)
{
    Player::hitPoints = hitPoints;
    Player::maxHitPoints = maxHitPoints;
    Player::hand = hand;
}

PlayingCard Player::selectCard(int cardNum){
    PlayingCard selected = Player::hand[cardNum];
    removeCard(selected);
    return selected;
}

int Player::getHitPoints(){
    return Player::hitPoints;
}

void Player::setHitPoints(int value){
    Player::hitPoints = value;
}

int Player::getMaxHitPoints(){
    return Player::maxHitPoints;
}

void Player::setMaxHitPoints(int value){
    Player::maxHitPoints = value;
}

std::vector<PlayingCard> Player::getHand(){
    return Player::hand;
}

void Player::setHand(std::vector<PlayingCard> playerHand){
    Player::hand = playerHand;
}

void Player::removeCard(PlayingCard &card){
    std::vector< PlayingCard>::iterator iterator = hand.begin();
    for(PlayingCard c: hand){
        if(c == card){
            hand.erase(iterator);
            break;
        }
        iterator++;
    }
}

void Player::addCard(PlayingCard &card){
    Player::hand.push_back(card);
}

void Player::damage(int amount){
    Player::hitPoints -= amount;
}

void Player::heal(int amount){
    if(Player::hitPoints + amount >= Player::maxHitPoints){
        Player::hitPoints = Player::maxHitPoints;
    } else{
        Player::hitPoints += amount;
    }
}

std::string Player::toString(){
    return std::to_string(Player::hitPoints) + "/" + std::to_string(Player::maxHitPoints) + "// " + std::to_string(hand.size());
}