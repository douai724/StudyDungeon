[![pre-commit](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml)
[![Documentation](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml)
[![Windows CI Build App](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml)
[![Windows CI Test](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml)

[![codecov](https://codecov.io/gh/douai724/StudyDungeon/graph/badge.svg?token=J8X7NTCMTC)](https://codecov.io/gh/douai724/StudyDungeon)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/2908ef35da3345f295e479b0a0af2026)](https://app.codacy.com/gh/douai724/StudyDungeon/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

DEV BRANCH: [![pre-commit](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml) [![Windows CI Build App](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml)
[![Windows CI Test](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml)

Beta released

## Playing the Game

StudyDungeon is a Flashcard program to aid in study

Flashcard decks are stored in `Decks/` and are loaded in upon lauching the program.

Once inside the program, you can start a study session by selecting _Begin Study_. This will then allow you to choose your starting deck to revise flashcards from.

Alternatively, you can add, edit, or remove decks through the _Edit Decks_ menu.

A study session has 2 phases:

1. Flashcard revision
   - You will go through as many rounds of flashcard revision as you like. Each card that you answer correctly will influence the cards available to you in the study break card duel game.
2. Study Break Card Duel
   - A card duel game to play as a study break. The more cards you answer correctly from the flashcard revision, the better your playing cards will be in the card duel.

### Adding decks in github

to add/edit decks in github:

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


## VScode config

extensions:

- franneck94.vscode-c-cpp-dev-extension-pack
- github.vscode-github-actions
- Gruntfuggly.todo-tree

## Building

Open vscode using the "Developer Command Prompt"

```bash
cd <path to StudyDungeon>
code .
```

In VScode to build:

A build task for `cmake` is defined in `.vscode/tasks.json`. `CMakePresets.json` contains a list of cmake presets that will populate the CMake extension with preset build options.

<kbd>Shift</kbd> + <kbd>F7</kbd> should be the shortcut key for triggering a build. You will be prompted to select a "Target" - Choose "ALL_BUILD".

For debug building there are two main presets:

- Configure preset: "Visual Studio Community 2022 Release - x86_amd64"
- Build preset: "Debug: Visual Studio Community 2022 Release - x86_amd64"

The exe from the build process gets put into [`build/Visual Studio Community 2022 Release - x86_amd64/app/Debug/StudyDungeon.exe`](<build/Visual Studio Community 2022 Release - x86_amd64/app/Debug/StudyDungeon.exe>)

Choosing the `install` target should build the exe and then place it (plus `Deck/*`) into `bin/` at the project root.

### Manual/CLI method

```bash
mkdir -p build
cd build
```

Run the cmake generator for MSVC which will set up the workflow:

```
cmake -S ../ -B ./ -G "Visual Studio Community 2022"
```

Building:

```bash
# debug build
cmake -DCMAKE_BUILD_TYPE=Debug ../

# release build
cmake -DCMAKE_BUILD_TYPE=Release ../
```

## Pre-commit

Pre-commit checks files for conformity to various stylings.

1. install python (https://www.python.org/downloads/release/python-3125/)
    - add to your path (https://realpython.com/add-python-to-path/) plus the `Scripts` dir
2. install pip (https://www.geeksforgeeks.org/how-to-install-pip-on-windows/)
3. install pre-commit (https://pre-commit.com/)
    - `pip install pre-commit`
4. in directory configure pre-commit
    - `pre-commit install`
5. run pre-commit on all files initially
    - `pre-commit run --all-files`
6. pre-commit will then run automatically on each commit checking the commited files for styling and auto fixing where it can.

.
