/**
 * @file player.cpp
 * @author Green Alligators
 * @brief Definitiona for the player class that is used in the card duel game
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "player.h"

Player::Player() : hitPoints(100), maxHitPoints(100), handSize(5), deck(std::vector<PlayingCard>{})
{
    // Player::hitPoints = 100;
    // Player::maxHitPoints = 100;
    // Player::handSize = 5;
    // Player::deck = std::vector<PlayingCard>{};
}

Player::Player(int hitPoints, int maxHitPoints, size_t handSize, const std::vector<PlayingCard> &deck)
    : hitPoints(hitPoints), maxHitPoints(maxHitPoints), handSize(handSize), deck(deck)
{
    for (int i = 0; i < Player::handSize; i++)
    {
        Player::drawCard();
    }
}

void Player::drawCard()
{
    if ((int)Player::deck.size() != 0)
    {
        PlayingCard first = Player::deck.front();
        Player::deck.erase(Player::deck.begin());
        Player::hand.push_back(first);
    }
}

int Player::getHitPoints()
{
    return Player::hitPoints;
}

void Player::setHitPoints(int value)
{
    Player::hitPoints = value;
}

int Player::getMaxHitPoints()
{
    return Player::maxHitPoints;
}

void Player::setMaxHitPoints(int value)
{
    if (value <= 0)
        return;
    Player::maxHitPoints = value;
}

std::vector<PlayingCard> Player::getHand()
{
    return Player::hand;
}

void Player::setHand(const std::vector<PlayingCard> &playerHand)
{
    Player::hand = playerHand;
}

size_t Player::getHandSize()
{
    return Player::handSize;
}

void Player::setHandSize(size_t handSize)
{
    Player::handSize = handSize;
}

std::vector<PlayingCard> Player::getDeck()
{
    return Player::deck;
}

void Player::setDeck(const std::vector<PlayingCard> &deck)
{
    Player::deck = deck;
}

void Player::removeCard(PlayingCard &card)
{
    std::vector<PlayingCard>::iterator it = hand.begin();
    for (PlayingCard c : hand)
    {
        if (c == card)
        {
            hand.erase(it);
            break;
        }
        ++it;
    }
}

void Player::addCard(PlayingCard &card)
{
    Player::hand.push_back(card);
}

PlayingCard Player::getCard(int index)
{
    if (index < 0 || index > (int)Player::hand.size() - 1)
        throw -1;
    return Player::hand[index];
}

void Player::damage(int amount)
{
    if (amount >= 0)
    {
        Player::hitPoints -= amount;
    }
}

void Player::heal(int amount)
{
    if (amount <= 0)
        return;
    if (Player::hitPoints + amount >= Player::maxHitPoints)
    {
        Player::hitPoints = Player::maxHitPoints;
    }
    else
    {
        Player::hitPoints += amount;
    }
}

std::string Player::toString()
{
    return std::to_string(Player::hitPoints) + "/" + std::to_string(Player::maxHitPoints) + "// " +
           std::to_string(hand.size());
}

void Player::printHand()
{
    std::string output = "";
    for (PlayingCard c : hand)
    {
        std::string add = "Card:" + c.toString() + "\n";
        output += add;
    }
    std::cout << output << std::endl;
}
