#ifndef PLAYING_CARD_H
#define PLAYING_CARD_H

#include "card_types.h"
#include <string>

class PlayingCard
{
private:
    bool target; // 0 for player that possesses this card, 1 for the enemy
    int value;

public:
    enum Type cardType;

    PlayingCard();

    PlayingCard(bool target, enum Type cardType, int value);

    bool operator==(PlayingCard &other);

    int getValue();

    bool getTarget();

    std::string toString();
};
#endif
