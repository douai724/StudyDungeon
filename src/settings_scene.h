/**
 * @file settings_scene.h
 * @author Green Alligators
 * @brief The menu and settings for the over all game
 * @version @PROJECT_VERSION@
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include "menu.h"
#include "util.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Object for the settings relating to the study sessions component
 *
 */
class StudySettings
{
public:
    /**
     * @brief Construct a new Study Settings object
     *
     */
    StudySettings();
    /**
     * @brief Construct a new Study Settings object
     *
     * @param n_cards max number of cards per round
     * @param mins duration of the study session
     */
    StudySettings(const int &n_cards, const int &mins);

    /**
     * @brief Get the round limit for flashcards
     *
     * @return int
     */
    int getFlashCardLimit();

    /**
     * @brief Get the Study Duration
     *
     * @return int
     */
    int getStudyDurationMin();

    /**
     * @brief Set the maximum number of flashcards per round
     *
     * @param n_cards number of cards
     */
    void setFlashCardLimit(const int &n_cards);

    /**
     * @brief Set the Study Duration
     *
     * @param mins number of minutes
     */
    void setStudyDurationMin(const int &mins);

    /**
     * @brief increment the study duration by 1 minute
     *
     */
    void incStudyDuration();

    /**
     * @brief decrement the study duration by 1 minute
     *
     */
    void decStudyDuration();

    /**
     * @brief increment the flashcard card round limit by 1
     *
     */
    void incFCLimit();

    /**
     * @brief decrement the flashcard card round limit by 1
     *
     */
    void decFCLimit();

    /**
     * @brief Reset the settings back to the defaults
     *
     */
    void reset();

    /**
     * @brief Set the start time for the study session
     *
     */
    void startSession();

    /**
     * @brief Determines if the study session is underway
     *
     * @return boolean
     */
    boolean sessionUnderway();

    /**
     * @brief sets the end of the session
     *
     */
    void endSession();

    /**
     * @brief Get the Session Start time point
     *
     * @return std::chrono::steady_clock::time_point
     */
    std::chrono::steady_clock::time_point getSessionStart();

    /**
     * @brief Get the directory the Deck files are stored in
     *
     * @return std::filesystem::path
     */
    std::filesystem::path getDeckDir();


private:
    /**maximum number of flashcards to study per round */
    int m_flashcard_limit;
    /** study session length */
    int m_study_duration_mins;
    /** timepoint the study session started at */
    std::chrono::steady_clock::time_point m_session_start = std::chrono::steady_clock::now();
    /** is the study session currently underway */
    boolean m_session_underway{false};
    /** the path to the Deck files */
    std::filesystem::path m_deck_dir = getAppPath().append("Decks/");
};


/**
 * @brief Class for a scene to show the program instructions.
 *
 *
 */
class SettingsScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new HowTo Scene object
     *
     * @param uiManager reference to the current UI mananger object
     * @param goBack a function to go back a scene
     */
    SettingsScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack, StudySettings &studySettings);

    /**
     * @brief function for continuous updates to the program state seperate from rendering and input handling
     *
     */
    void update() override;
    /**
     * @brief renders the scene on the console window
     * @param window shared pointer to the console window that is rendered on
     *
     * draws the title of the scene, sets up a counter for the current number of the fib sequence and draws the buttons:
     * reset, update and back.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Initialise the scene
     *
     */
    void init();

    /**
     * @brief Increment flashcard card limit by 1
     *
     */
    void incrementCards();

    /**
     * @brief Decrement flashcard card limit by 1
     *
     */
    void decrementCards();

    /**
     * @brief Increment study duration by 1 miunute
     *
     */
    void incrementStudyMins();

    /**
     * @brief Decrement study duration by 1 minute
     *
     */
    void decrementStudyMins();

    /**
     * @brief Reset to default settings
     *
     */
    void resetDefault();

    /**
     * @brief Handle user input for the scene
     *
     */
    void handleInput() override;

    /**
     * @brief Set the staticDrawn flag to determine if object needs to be redrawn
     *
     * @param staticDrawn
     */
    void setStaticDrawn(bool staticDrawn) override
    {
        m_staticDrawn = staticDrawn;
    }

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    StudySettings &m_settings;         ///< Reference to the study settings
    std::function<void()> m_goBack;    ///< function to return to the previous scene
    bool m_staticDrawn = false;        ///< Should the object be redrawn
};

#endif // SETTINGS_SCENE_H
