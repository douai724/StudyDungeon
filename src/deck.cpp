/**
 * @file deck.cpp
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "deck.h"

namespace fs = std::filesystem;


CardDifficulty strToCardDifficulty(const std::string &difficultyStr)
{
    if (difficultyStr == "LOW")
    {
        return LOW;
    }
    else if (difficultyStr == "MEDIUM")
    {
        return MEDIUM;
    }
    else if (difficultyStr == "HIGH")
    {
        return HIGH;
    }
    else
    {
        return UNKNOWN;
    }
}

std::string cardDifficultyToStr(const CardDifficulty &difficulty)
{
    switch (difficulty)
    {
    case (LOW):
        return "LOW";
    case (MEDIUM):
        return "MEDIUM";
    case (HIGH):
        return "HIGH";
    };
    return "UNKNOWN";
}


FlashCard createFlashCard(std::string question, std::string answer, CardDifficulty difficulty, int n_times_answered)
{
    FlashCard card{};
    card.question = question;
    card.answer = answer;
    card.difficulty = difficulty;
    card.n_times_answered = n_times_answered;
    return card;
};


FlashCardDeck readFlashCardDeck(fs::path deck_file)
{

    /** The flashcard deck to store the flashcards in as read from the file */
    FlashCardDeck deck;

    // Open file for reading
    std::ifstream inf{deck_file};
    // temporary variables to use for reading data
    int lineCount{0};
    std::string strInput{};
    // keep track of current card in deck
    int cardNum{0};

    /** blank flashcard to begin filling in */
    FlashCard fc{};
    deck.cards.push_back(fc);

    // Read each line of the deck file and process to make flashcards
    while (std::getline(inf, strInput))
    {
        // First line of the file is the deck name
        if (lineCount == 0)
        {
            deck.name = strInput;
        }
        else
        {
            // parse line
            // if Q -> fc.question
            // if A -> fc.answer
            // if D -> fc.difficulty
            // if N -> fc.num_times
            // if '-' indicates the start of a new card
            if (strInput.starts_with("-"))
            {
                cardNum++;
                deck.cards.push_back(fc);
                std::cout << "NEW CARD" << '\n';
            }
            if (strInput.starts_with("Q:"))
            {
                deck.cards.at(cardNum).question = strInput;
            }
            if (strInput.starts_with("A:"))
            {
                deck.cards.at(cardNum).answer = strInput;
            }
            if (strInput.starts_with("D:"))
            {
                //deck.cards.at(cardNum).difficulty = strToCardDifficulty(strInput);
            }
        }

        lineCount++;
    }

    return deck;
};


bool writeFlashCardDeck(const FlashCardDeck &deck, fs::path filename)
{
    // check filename ends with .deck
    if (!filename.string().ends_with(".deck"))
    {
        return false;
    }

    // TODO
    if (fs::exists(filename))
    {
        if (!fs::is_regular_file(filename))
        {
            // path exists but is not a file
            //TODO throw exception
            return false;
        }
        else
        {
            std::cout << "Path " << filename << " already exists, Overwrite file? Y/N\n";
            // DOUBLE CHECK WITH USER!
            bool overwrite = yesNoInput();
            if (!overwrite)
            {
                return false;
            }


            // open file
            // write contents to file
            // close file
            return true;
        }
    }
    else
    {
        // ensure parent directory exists


        // check Decks/ exists
        // check for existance of
        // open file for writing
        // write name of deck to file
        // loop through each card in the deck
        return false;
    }
};


std::vector<FlashCardDeck> loadFlashCardDecks(fs::path deck_dir_path)
{
    std::cout << deck_dir_path << std::endl;
    std::vector<FlashCardDeck> deck_array;
    // Check the deck directory exists
    if (fs::exists(deck_dir_path) && fs::is_directory(deck_dir_path))
    {
        std::cout << deck_dir_path << " is a directory" << std::endl;
        // list out the contents of the directory
        for (const auto &entry : fs::directory_iterator(deck_dir_path))
        {
            if (entry.is_regular_file() && entry.path().string().ends_with(".deck"))
            {
                FlashCardDeck fd{};
                fd = readFlashCardDeck(entry);
                fd.filename = entry;
                deck_array.push_back(fd);
            }
        }
    }
    else
    {
        std::cerr << "Directory does not exist, or is not a directory";
        //TODO deal with error
    }

    return deck_array;
};

std::vector<FlashCardDeck> createExampleDecks()
{
    FlashCard f1 = createFlashCard("question 1", "answer 1", LOW, 0);
    FlashCard f2 = createFlashCard("question 2", "answer 2", MEDIUM, 1);
    FlashCardDeck d1{"Example Deck 1", "", std::vector<FlashCard>{f1, f2}};

    FlashCard f3 = createFlashCard("question 3", "answer 3", HIGH, 2);
    FlashCard f4 = createFlashCard("question 4", "answer 4", UNKNOWN, 1);
    FlashCardDeck d2{"Example Deck 2", "", std::vector<FlashCard>{f3, f4}};

    return std::vector<FlashCardDeck>{d1, d2};
};


std::filesystem::path createDeckFilename(std::filesystem::path deck_dir)
{
    if (!fs::is_directory(deck_dir))
    {
        // TODO throw exception - path not a directory
    }
    std::string input{};
    std::cout
        << "Please enter a name to save your deck file to. (Alphanumeric characters only and maximum of 20 characters)"
        << std::endl;
    bool invalid{true};
    do
    {
        std::getline(std::cin, input);
        invalid = isValidDeckFileName(input);
    } while (invalid);

    deck_dir.append(input).concat(".deck");

    return deck_dir;
}
