/**
 * @file settings_scene.h
 * @author Green Alligators
 * @brief The menu and settings for the over all game
 * @version 0.2
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


class StudySettings
{
public:
    StudySettings();
    StudySettings(const int &n_cards, const int &mins);
    int getFlashCardLimit();
    int getStudyDurationMin();
    void setFlashCardLimit(const int &n_cards);
    void setStudyDurationMin(const int &mins);
    void incStudyDuration();
    void decStudyDuration();
    void incFCLimit();
    void decFCLimit();
    void reset();
    void startSession();
    boolean sessionUnderway();
    void endSession();
    std::chrono::steady_clock::time_point getSessionStart();
    std::filesystem::path getDeckDir();


private:
    int m_flashcard_limit;
    int m_study_duration_mins;
    std::chrono::steady_clock::time_point m_session_start = std::chrono::steady_clock::now();
    boolean m_session_underway{false};
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
    void init();
    void incrementCards();
    void decrementCards();
    void incrementStudyMins();
    void decrementStudyMins();
    void resetDefault();
    void handleInput() override;

    void setStaticDrawn(bool staticDrawn) override
    {
        m_staticDrawn = staticDrawn;
    }

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    StudySettings &m_settings;         ///< Reference to the study settings
    std::function<void()> m_goBack;    ///< function to return to the previous scene
    bool m_staticDrawn = false;
};

#endif // SETTINGS_SCENE_H
