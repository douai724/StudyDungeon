/**
 * @file settings_scene.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "settings_scene.h"
#include <string>


StudySettings::StudySettings() : m_flashcard_limit(15), m_study_duration_mins(25)
{
}

void StudySettings::reset()
{
    m_flashcard_limit = 15;
    m_study_duration_mins = 25;
}


void StudySettings::incFCLimit()
{
    if (m_flashcard_limit < 100)
    {
        m_flashcard_limit++;
    }
}


void StudySettings::decFCLimit()
{
    if (m_flashcard_limit > 1)
    {
        m_flashcard_limit--;
    }
}

void StudySettings::incStudyDuration()
{
    if (m_study_duration_mins < 60)
    {
        m_study_duration_mins++;
    }
}

void StudySettings::decStudyDuration()
{
    if (m_study_duration_mins > 1)
    {
        m_study_duration_mins--;
    }
}


int StudySettings::getFlashCardLimit()
{
    return m_flashcard_limit;
}

int StudySettings::getStudyDurationMin()
{
    return m_study_duration_mins;
}

void StudySettings::setFlashCardLimit(const int &n_cards)
{
    m_flashcard_limit = n_cards;
}

void StudySettings::setStudyDurationMin(const int &mins)
{
    m_study_duration_mins = mins;
}


void StudySettings::startSession()
{
    m_session_start = std::chrono::steady_clock::now();
}


SettingsScene::SettingsScene(ConsoleUI::UIManager &uiManager,
                             std::function<void()> goBack,
                             StudySettings &studySettings)

    : m_uiManager(uiManager), m_goBack(goBack), m_settings(studySettings)
{
    auto &menu = m_uiManager.createMenu("settings", true); // Horizontal menu
    menu.addButton("Increment Cards", [this]() { incrementCards(); });
    menu.addButton("Decrement Cards", [this]() { decrementCards(); });
    menu.addButton("Increment Time", [this]() { incrementStudyMins(); });
    menu.addButton("Decrement Time", [this]() { decrementStudyMins(); });
    menu.addButton("Defaults", [this]() { resetDefault(); });
    menu.addButton("Back", [this]() { m_goBack(); });
}

void SettingsScene::init()
{
    // No need for init
}

void SettingsScene::update()
{
    // No continuous updates needed for this scene
}


void SettingsScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Settings", 2);
    window->drawCenteredText("Number of Cards per Round: " + std::to_string(m_settings.getFlashCardLimit()), 5);
    window->drawCenteredText("Study time (mins): " + std::to_string(m_settings.getStudyDurationMin()), 6);


    // window->drawCenteredText("Playing the Game", window->getSize().Y / 2 - 2);


    // Draw the menu at the bottom center of the screen
    auto windowSize = window->getSize();
    m_uiManager.getMenu("settings")
        .draw((windowSize.X - 30) / 2, windowSize.Y - 4); // Adjust 30 based on your menu width
}

void SettingsScene::handleInput()
{
    m_uiManager.getMenu("settings").handleInput();
}

// increment card limit up to max of 1000
void SettingsScene::incrementCards()
{
    m_settings.incFCLimit();
}

// decrement hand limit to no less than 1
void SettingsScene::decrementCards()
{
    m_settings.decFCLimit();
}

// increment to a maximum of 1 hour
void SettingsScene::incrementStudyMins()
{
    m_settings.incStudyDuration();
}

// decrement time to a minimum of 1 min
void SettingsScene::decrementStudyMins()
{
    m_settings.decStudyDuration();
}

void SettingsScene::resetDefault()
{
    m_settings.reset();
}
