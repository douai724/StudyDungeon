# StudyDungeon

A flashcard study command line application


Playing the Game

StudyDungeon is a Flashcard program to aid in study

Flashcard decks are stored in `Decks/` and are loaded in upon lauching the program.

Once inside the program, you can start a study session by selecting _Begin Study_. This will then allow you to choose your starting deck to revise flashcards from.

Alternatively, you can add, edit, or remove decks through the _Edit Decks_ menu.

A study session has 2 phases:

1. Flashcard revision
   - You will go through as many rounds of flashcard revision as you like. Each card that you answer correctly will influence the cards available to you in the study break card duel game.
2. Study Break Card Duel
   - A card duel game to play as a study break. The more cards you answer correctly from the flashcard revision, the better your playing cards will be in the card duel.


Creating Decks:

1. Go into the `Decks/` directory
2. Select `Add file` -> `Create new file`
3. Name the file ensuring it has a suffix of `.deck`
4. First line of the file is the deck name visible in the program
5. add cards using the following template:

```
Q: <question>
A: <answer>
D: UNKNOWN
N: 0
-
```

Replace `<question>` with your question text and `<answer>` with your answer text. The line with only `-` denotes the end of each card.

- `D:` is the card difficulty, options are `UNKNOWN`, `EASY`, `MEDIUM`, and `HARD`
- `N:` is the number of times the card has been answered
