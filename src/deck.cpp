
#include "deck.h"

namespace fs = std::filesystem;


/**
 * @brief Create a flashcard and fill in the card contents
 *
 * @return FlashCard
 */
FlashCard createFlashCard(std::string question, std::string answer, CardDifficulty difficulty, int n_times_answered)
{
    FlashCard card{};
    card.question = question;
    card.answer = answer;
    card.difficulty = difficulty;
    card.n_times_answered = n_times_answered;
    return card;
};

/**
 * @brief For a given deck file, read the contents in to create all the cards
 * TODO document
 * @param deck_file
 */
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
        }

        lineCount++;
    }

    //TODO remove these debugging steps
    std::cout << "name of deck: " << deck.name << '\n';
    std::cout << "number of lines read: " << lineCount << '\n';
    deck.printDeck();

    return deck;
};


/**
 * @brief Write a deck of flashcards to disk
 * The standard location will be in Decks/ located with the executable
 * and use a suffix of ".deck"
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 */
void writeFlashCardDeck(FlashCardDeck deck, fs::path filename) {
    // check Decks/ exists
    // check for existance of
    // open file for writing
    // write name of deck to file
    // loop through each card in the deck
};


/**
 * @brief Function that will scan the deck directory and read in all the deck files found
 * TODO document
 * @param deck_path the path to look for ".deck" suffixed files
 */
std::vector<FlashCardDeck> loadFlashCardDecks(fs::path deck_path)
{
    // TODO create an array of Decks to store eacn deck in
    std::cout << deck_path << std::endl;
    std::vector<FlashCardDeck> deck_array;
    // Check the deck directory exists
    if (fs::exists(deck_path) && fs::is_directory(deck_path))
    {
        std::cout << deck_path << " is a directory" << std::endl;
        // list out the contents of the directory
        for (const auto &entry : fs::directory_iterator(deck_path))
        {
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;
            // TODO for each "<file>.deck" files, call read_deck() and add into the Deck array
            if (entry.is_regular_file())
            // TODO ensure file has .deck extension
            {
                FlashCardDeck fd{};
                fd = readFlashCardDeck(entry);
                deck_array.push_back(fd);
            }
        }
    }
    else
    {
        std::cerr << "Directory does not exist, or is not a directory";
        //TODO deal with error
    }
    // for (FlashCardDeck d : deck_array)
    // {
    //     d.printDeck();
    // }
    return deck_array;
};
