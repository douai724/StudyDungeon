#include "player.h"

Player::Player()
{
}

Player::Player(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand)
{
    Player::hitPoints = hitPoints;
    Player::maxHitPoints = maxHitPoints;
    Player::hand = hand;
}

PlayingCard Player::play()
{
    std::cout << "This is the base class." << std::endl;
    PlayingCard selected = getCard(1);
    removeCard(selected);
    return selected;
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

void Player::setHand(std::vector<PlayingCard> playerHand)
{
    Player::hand = playerHand;
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
        it++;
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

User::User(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand) : Player(hitPoints, maxHitPoints, hand)
{
}

// could change the return type to an integer so that -1 can be sent in return
// PlayingCard User::play()
// {
//     std::cout << "This is the USER class." << std::endl;

//     std::vector<PlayingCard> currentHand = Player::getHand();


//     for (int i = 0; i < (int)currentHand.size(); i++)
//     {
//         std::cout << i << ": " << currentHand[i].toString() << std::endl;
//     }
//     try
//     {
//         std::cout << "Please pick a card by entering its number:" << std::endl;
//         int input;
//         std::cin >> input;
//         PlayingCard selectedCard = getCard(input);
//         removeCard(selectedCard);
//         return selectedCard;
//     }
//     catch (int e)
//     {
//         throw e;
//     }
// }

PlayingCard User::play()
{
    std::cout << "This is the USER class." << std::endl;

    std::vector<PlayingCard> currentHand = Player::getHand();
    int handSize = (int)currentHand.size();
    PlayingCard selectedCard = PlayingCard();
    // probably need to free this up somehow
    auto cardsMenu = std::make_shared<GridMenu>("Select a card", 1, handSize);
    for (int i = 0; i < handSize; i++)
    {

        cardsMenu->addGridItem(
            currentHand[i].toString(),
            [this, i, currentHand, &selectedCard]() {
                system("cls");
                std::cout << "Helo" << std::endl;
                selectedCard = currentHand[i];
                system("pause");
                throw "continue";
            },
            i,
            0);
    }

    cardsMenu->run();
    removeCard(selectedCard);
    std::cout << "return" << std::endl;
    return selectedCard;
}


Bot::Bot(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand) : Player(hitPoints, maxHitPoints, hand)
{
}

PlayingCard Bot::play()
{
    std::cout << "This is the BOT class." << std::endl;

    try
    {
        PlayingCard selectedCard = getCard((int)getHand().size() - 1);
        removeCard(selectedCard);
        return selectedCard;
    }
    catch (int e)
    {
        throw e;
    }
}
