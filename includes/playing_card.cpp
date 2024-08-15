#include "playing_card.h"

PlayingCard::PlayingCard(bool target, enum Type cardType, int value){
    PlayingCard::target = target;
    PlayingCard::cardType = cardType; 
    PlayingCard::value = value;
}

PlayingCard::PlayingCard(){}

bool PlayingCard::getTarget(){
    return PlayingCard::target;
}

int PlayingCard::getValue(){
    return PlayingCard::value;
}

std::string PlayingCard::toString(){
    std::string type;
    switch(PlayingCard::cardType){
        case 0:
            type = "damage";
            break;
    }

    return type + " " + std::to_string(value);
}