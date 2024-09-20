/**
 * @file gameloop.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "gameloop.h"

Game::Game(Player p1, Player p2)
{
    Game::p1 = p1;
    Game::p2 = p2;
    Game::turn = 1;
}

Game::Game()
{
}

void Game::nextTurn(PlayingCard nextCard)
{

    // draw a card
    if (turn == 1)
    {
        p1.drawCard();
    }
    else
    {
        p2.drawCard();
    }

    // apply effect
    switch ((int)nextCard.getType())
    {
    case 0:
        damageEffect(nextCard);
        break;
    case 1:
        healEffect(nextCard);
        break;
    case 2:
        swapHandEffect();
        break;
    default:
        throw -1;
    }

    // switch turns
    if (Game::turn == 1)
    {
        Game::turn = 2;
    }
    else
    {
        Game::turn = 1;
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

bool Game::isWinner()
{
    if (turn == 1)
    {
        if (p1.getHitPoints() <= 0 || p1.getDeck().size() == 0)
        {
            return false;
        }
        else if (p2.getHitPoints() <= 0 || p2.getDeck().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (turn == 2)
    {
        if (p2.getHitPoints() <= 0 || p2.getDeck().size() == 0)
        {
            return false;
        }
        else if (p1.getHitPoints() <= 0 || p1.getDeck().size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
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

Game setUp(Player p1, Player p2)
{
    return Game(p1, p2);
}

std::vector<PlayingCard> generateDeck(int numCards)
{
    std::vector<PlayingCard> hand;
    for (int i = 0; i < numCards; i++)
    {
        int type = (int)(std::rand() / (double)RAND_MAX * 3);
        int value = (int)(std::rand() / (double)RAND_MAX * 10);
        PlayingCard card = PlayingCard((enum Type)type, value);
        hand.push_back(card);
    }
    return hand;
}
