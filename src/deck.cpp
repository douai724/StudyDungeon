/**
 * @file deck.cpp
 * @author Green Alligators
 * @brief Functions and classes relating to flashcards
 *
 *
 * @version 0.2
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "deck.h"


CardDifficulty strToCardDifficulty(const std::string &difficultyStr)
{
    if (difficultyStr == "EASY")
    {
        return EASY;
    }
    else if (difficultyStr == "MEDIUM")
    {
        return MEDIUM;
    }
    else if (difficultyStr == "HARD")
    {
        return HARD;
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
    case (EASY):
        return "EASY";
        break;
    case (MEDIUM):
        return "MEDIUM";
        break;
    case (HARD):
        return "HARD";
        break;
    default:
        return "UNKNOWN";
        break;
    };
}

FlashCard::FlashCard() : FlashCard{"", "", UNKNOWN, 0}
{
}

FlashCard::FlashCard(std::string question, std::string answer, CardDifficulty difficulty, int n_times_answered)
    : question(question), answer(answer), difficulty(difficulty), n_times_answered(n_times_answered) {};

void FlashCard::printCard()
{
    std::cout << question << '\n';
    std::cout << answer << '\n';
    std::cout << "\n";
}

void FlashCard::printCardAsTemplate()
{
    std::cout << "Q: " << question << '\n' << "A: " << answer << '\n';
    std::cout << "D: " << cardDifficultyToStr(difficulty) << '\n' << "N: " << n_times_answered << '\n';
    std::cout << "-" << '\n';
}

std::string FlashCard::stringCardAsTemplate()
{
    std::stringstream card_contents{};
    card_contents << "Q: " << question << "\nA: " << answer << '\n';
    card_contents << "D: " << cardDifficultyToStr(difficulty);
    card_contents << "\nN: " << std::to_string(n_times_answered) << "\n";
    card_contents << "-\n";
    return card_contents.str();
}

void FlashCardDeck::printDeck()
{
    std::cout << name << std::endl;
    std::cout << "File location: " << filename << std::endl;
    std::cout << "Deck size: " << cards.size() << " cards" << std::endl;
    for (FlashCard card : cards)
    {
        card.printCard();
    }
}


void FlashCardDeck::printDeckAsTemplate()
{
    std::cout << name << std::endl;
    for (FlashCard card : cards)
    {
        card.printCardAsTemplate();
    }
}


// parses a deck file to convert it to a Flashcard deck object
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

    // Create a blank card and push it onto the deck ready to be filled
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
            }
            if (strInput.starts_with("Q: "))
            {
                size_t pos = strInput.find_first_not_of(" \t", 3);
                deck.cards.at(cardNum).question = strInput.substr(pos);
            }
            if (strInput.starts_with("A: "))
            {
                size_t pos = strInput.find_first_not_of(" \t", 3);
                deck.cards.at(cardNum).answer = strInput.substr(pos);
            }
            if (strInput.starts_with("D: "))
            {
                size_t pos = strInput.find_first_not_of(" \t", 3);
                deck.cards.at(cardNum).difficulty = strToCardDifficulty(strInput.substr(pos));
            }
            if (strInput.starts_with("N: "))
            {
                deck.cards.at(cardNum).n_times_answered = std::stoi(strInput.substr(2));
            }
        }

        lineCount++;
    }

    // TODO replace the below with a method that will remove any empty cards in the deck
    // remove the empty card that should be at the end of the deck after reading in the files
    if (deck.cards.at(cardNum).question == "" && deck.cards.at(cardNum).answer == "")
    {
        deck.cards.pop_back();
    }


    return deck;
};

bool writeFlashCardDeck(const FlashCardDeck &deck, fs::path filename)
{
    //TODO this needs a try block
    if (fs::is_directory(filename.parent_path()))
    {
        // open file
        std::ofstream outf{filename.string(), std::ios::trunc};
        // write contents to file
        outf << deck.name << std::endl;
        for (FlashCard fc : deck.cards)
        {
            outf << fc.stringCardAsTemplate();
            //outf << "-" << std::endl;
        }
        // close file
        outf.close();
        return true;
    }
    else
    {
        return false;
    }
}

// write the FlashCardDeck to a file but will first check if file exists and if so should be overwritten
bool writeFlashCardDeckWithChecks(const FlashCardDeck &deck, fs::path filename, bool force_overwrite = false)
{
    //FIXME this function is not complete and so doesn't work properly....
    // check filename ends with .deck
    if (!filename.string().ends_with(".deck"))
    {
        return false;
    }

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
            if (!force_overwrite)
            {
                std::cout << "Path " << filename << " already exists, Overwrite file? Y/N\n";
                // DOUBLE CHECK WITH USER!
                bool overwrite = yesNoPrompt();
                if (!overwrite)
                {
                    std::cout << "Choose new filename?" << std::endl;
                    bool create_new_path = yesNoPrompt();

                    if (!create_new_path)
                    {
                        return false;
                    }

                    filename = createDeckFilename(filename.parent_path());
                }
            }

            return writeFlashCardDeck(deck, filename);
        }
    }
    else
    {
        // TODO
        // ensure parent directory exists
        if (fs::is_directory(filename.parent_path()))
        {
            return writeFlashCardDeck(deck, filename);
        }
        return false;
    }
};


std::vector<FlashCardDeck> loadFlashCardDecks(fs::path deck_dir_path)
{
    //std::cout << deck_dir_path << std::endl;
    std::vector<FlashCardDeck> deck_array;
    // Check the deck directory exists
    if (fs::exists(deck_dir_path) && fs::is_directory(deck_dir_path))
    {
        //std::cout << deck_dir_path << " is a directory" << std::endl;
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

// This is used to create some eample decks if the decks directory doesn't exits
// or can be used in tests.
std::vector<FlashCardDeck> createExampleDecks()
{
    FlashCard f1 = FlashCard("question 1", "answer 1", EASY, 0);
    FlashCard f2 = FlashCard("question 2", "answer 2", MEDIUM, 1);
    FlashCardDeck d1{"Example Deck 1", "", std::vector<FlashCard>{f1, f2}};

    FlashCard f3 = FlashCard("question 3", "answer 3", HARD, 2);
    FlashCard f4 = FlashCard("question 4", "answer 4", UNKNOWN, 1);
    FlashCardDeck d2{"Example Deck 2", "", std::vector<FlashCard>{f3, f4}};

    return std::vector<FlashCardDeck>{d1, d2};
};

// given a directory, will prompt user for a deck name and ensure that it is a valid name
std::filesystem::path createDeckFilename(std::filesystem::path deck_dir)
{
    if (!fs::is_directory(deck_dir))
    {
        // TODO throw exception - path not a directory
    }
    std::string input{};
    std::cerr
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


// provides a prompt to double check updating of deck
bool updateDeckFile(FlashCardDeck &deck_to_update)
{
    //std::cout << "Save card updates?" << std::endl;

    if (yesNoPrompt())
    {
        if (writeFlashCardDeckWithChecks(deck_to_update, deck_to_update.filename, true))
        {
            return true;
        }
        else
        {
            //std::cout << "Issue in writing file. Cards were not updated." << std::endl;
        }
    }
    return false;
}
