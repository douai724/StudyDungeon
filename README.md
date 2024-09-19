[![pre-commit](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml)
[![Documentation](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml)
[![Windows CI Build App](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml)
[![Windows CI Test](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml/badge.svg)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml)

[![codecov](https://codecov.io/gh/douai724/StudyDungeon/graph/badge.svg?token=J8X7NTCMTC)](https://codecov.io/gh/douai724/StudyDungeon)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/2908ef35da3345f295e479b0a0af2026)](https://app.codacy.com/gh/douai724/StudyDungeon/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

DEV BRANCH: [![pre-commit](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml) [![Windows CI Build App](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-build.yml)
[![Windows CI Test](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml/badge.svg?branch=dev)](https://github.com/douai724/StudyDungeon/actions/workflows/windows-test.yml)

Alpha released

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
