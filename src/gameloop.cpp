#include "gameloop.h"

Game::Game(Player *p1, Player *p2)
{
    Game::p1 = p1;
    Game::p2 = p2;
    Game::turn = 1;
}

void Game::nextTurn()
{
    clearScreen();
    PlayingCard card = PlayingCard();

    if (turn == 1)
    {
        if ((int)p1->getHand().size() == 0)
        {
            Game::turn = 2;
            return;
        }
        try
        {
            card = p1->play();
        }
        catch (int e)
        {
            std::cout << "Invalid card selection, please try again." << e << std::endl;
            return;
        }
    }
    else
    {
        if ((int)p2->getHand().size() == 0)
        {
            Game::turn = 1;
            return;
        }
        try
        {
            card = p2->play();
        }
        catch (int e)
        {
            std::cout << "Invalid card selection." << e << std::endl;
            return;
        }
    }


    // apply effect
    switch (card.getType())
    {
    case 0:
        damageEffect(card);
        if (turn == 1)
        {
            std::cout << "You dealt " << card.getValue() << " damage!\n";
        }
        else
        {
            std::cout << "The enemy dealt " << card.getValue() << " damage!\n";
        }
        break;
    case 1:
        healEffect(card);
        break;
    case 2:
        swapHandEffect();
        break;
    default:
        std::cout << "Valid card does not exist." << std::endl;
    }

    std::cout << "Health: P1=" << p1->getHitPoints() << "\t\t\t\t\t\t\t P2=" << p2->getHitPoints() << std::endl;
    pause();

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
    if (p1->getHitPoints() <= 0 || p2->getHitPoints() <= 0 || (p1->getHand().size() == 0 && p2->getHand().size() == 0))
    {
        return true;
    }
    return false;
}

void Game::swapHandEffect()
{
    std::vector<PlayingCard> temp = Game::p1->getHand();
    p1->setHand(p2->getHand());
    p2->setHand(temp);
}

void Game::healEffect(PlayingCard &card)
{
    if (turn == 1)
    {
        Game::p1->heal(card.getValue());
    }
    else
    {
        Game::p2->heal(card.getValue());
    }
}

void Game::damageEffect(PlayingCard &card)
{
    if (turn == 1)
    {
        Game::p2->damage(card.getValue());
    }
    else
    {
        Game::p1->damage(card.getValue());
    }
}


void start(int numCards)
{
    std::cout << "BEGIN GAME" << std::endl;
    pause();
    User u1 = User(100, 100, generateHand(numCards));
    Bot u2 = Bot(100, 100, generateHand(12));
    Player *p1 = &u1;
    Player *p2 = &u2;

    Game game = Game(p1, p2);

    while (!game.isGameOver())
    {
        game.nextTurn();
    }
    std::cout << "The game is over!" << std::endl;
    pause();
}

std::vector<PlayingCard> generateHand(int numCards)
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
