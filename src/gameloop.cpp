/**
 * @file gameloop.cpp
 * @author Green Alligators
 * @brief Defines the gameplay and game loop of the card duel game
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "gameloop.h"

Game::Game(Player p1, Player p2) : p1(p1), p2(p2), turn(1)
{
}

Game::Game() : p1(Player()), p2(Player()), turn(1)
{
    // Game::p1 = Player(100, 100, 5, std::vector<PlayingCard>());
    // Game::p2 = Player(100, 100, 5, std::vector<PlayingCard>());
    // Game::turn = 1;
}

void Game::nextTurn(PlayingCard &nextCard)
{

    // have current player draw card
    drawCard();

    // play the card effect
    playEffect(nextCard);

    // swap turns
    switchTurn();
}

void Game::playEffect(PlayingCard &card)
{
    switch ((int)card.getType())
    {
    case 0:
        damageEffect(card);
        break;
    case 1:
        healEffect(card);
        break;
    case 2:
        swapHandEffect();
        break;
    default:
        throw -1;
    }
}

void Game::drawCard()
{
    if (turn == 1)
    {
        p1.drawCard();
    }
    else if (turn == 2)
    {
        p2.drawCard();
    }
    else
    {
        return;
    }
}

void Game::switchTurn()
{
    if (Game::turn == 1)
    {
        Game::turn = 2;
    }
    else if (Game::turn == 2)
    {
        Game::turn = 1;
    }
    else
    {
        return;
    }
}

bool Game::isGameOver()
{
    if (p1.getHitPoints() <= 0 || p2.getHitPoints() <= 0)
    {
        return true;
    }
    if (p1.getDeck().size() == 0 || p2.getDeck().size() == 0)
    {
        return true;
    }
    return false;
}

short Game::getWinner()
{
    if (p1.getHitPoints() <= 0 || p1.getDeck().size() == 0)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

void Game::swapHandEffect()
{
    std::vector<PlayingCard> temp = Game::p1.getHand();
    p1.setHand(p2.getHand());
    p2.setHand(temp);
}

void Game::healEffect(PlayingCard &card)
{
    if (turn == 1)
    {
        Game::p1.heal(card.getValue());
    }
    else
    {
        Game::p2.heal(card.getValue());
    }
}

void Game::damageEffect(PlayingCard &card)
{
    if (turn == 1)
    {
        Game::p2.damage(card.getValue());
    }
    else
    {
        Game::p1.damage(card.getValue());
    }
}


std::vector<PlayingCard> generateDeck(int numCards)
{
    // compute the sum of all possibilities by looping over the cards
    // place them on a normal distribution
    // seed the random number generator with the current time
    std::srand(std::time(NULL));
    float sum = 0.0;
    float currentDist = 0.0;
    std::vector<float> distribution = {};
    std::_Tree_const_iterator it = cardPossibilities.begin();
    do
    {
        sum += it->second;
        ++it;
    } while (it != cardPossibilities.end());

    it = cardPossibilities.begin();
    do
    {
        currentDist += it->second / sum;
        distribution.push_back(currentDist);
        ++it;
    } while (it != cardPossibilities.end());

    std::vector<PlayingCard> hand;
    for (int i = 0; i < numCards; i++)
    {

        float type = std::rand() / (float)RAND_MAX;
        int index = -1;
        for (int j = 0; j < distribution.size(); j++)
        {
            if (type <= distribution[j])
            {
                index = j;
                break;
            }
        } // add error handling here for -1
        int value = (int)(std::rand() / (double)RAND_MAX * 30);
        PlayingCard card = PlayingCard((enum Type)index, value);
        hand.push_back(card);
    }
    return hand;
}
