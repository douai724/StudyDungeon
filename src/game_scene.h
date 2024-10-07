/**
 * @file game_scene.h
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "gameloop.h"
#include "menu.h"
#include "player.h"
#include "util.h"
#include <conio.h>

/** initial deck size for the user */
const int user_deck_size{60};
/** initial deck size for the bot*/
const int bot_deck_size{60};
/** initial hand size limit for the user */
const int user_hand_size{5};
/** initial hand size limit for the bot */
const int bot_hand_size{5};

/**
 * @brief Scene for the card duel game
 *
 */
class GameScene : public ConsoleUI::Scene
{
private:
    /** reference to the UI manager */
    ConsoleUI::UIManager &m_uiManager;
    /** does the scene need to be redrawn on update */
    bool m_needsRedraw = true;
    /** index for the selected card */
    int m_selectedIndex = 0;
    /** reference to the back button */
    std::function<void()> m_goBack;
    /** the game object */
    Game game;
    /** the cards as they are played */
    std::vector<PlayingCard> playlist;
    /** does the scene need to be reprinted */
    bool m_staticDrawn = false;

public:
    /**
     * @brief Construct a new Game Scene object
     *
     * @param uiManager the UI Manager
     * @param goBack the back button for the previous scene
     */
    GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);

    /**
     * @brief update the scene
     *
     */
    void update() override;

    /**
     * @brief initialise the scene
     *
     */
    void init() override;

    /**
     * @brief render the scene
     *
     * @param window the console window for the scene
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief handle the input for the scene
     *
     */
    void handleInput() override;

    /**
     * @brief Set the Static Drawn object
     *
     * @param staticDrawn
     */
    void setStaticDrawn(bool staticDrawn) override;
};

#endif
