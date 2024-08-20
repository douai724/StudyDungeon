[![pre-commit](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml/badge.svg?branch=cmake_dev)](https://github.com/douai724/StudyDungeon/actions/workflows/pre-commit.yml)
[![Documentation](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml/badge.svg?branch=cmake_dev)](https://github.com/douai724/StudyDungeon/actions/workflows/documentation.yml)
[![MSBuild](https://github.com/douai724/StudyDungeon/actions/workflows/msbuild.yml/badge.svg?branch=cmake_dev)](https://github.com/douai724/StudyDungeon/actions/workflows/msbuild.yml)
[![Windows CI Test](https://github.com/douai724/StudyDungeon/actions/workflows/windows.yml/badge.svg?branch=cmake_dev)](https://github.com/douai724/StudyDungeon/actions/workflows/windows.yml)

## VScode config

extensions:
- franneck94.vscode-c-cpp-dev-extension-pack
- github.vscode-github-actions
- Gruntfuggly.todo-tree


## Building

Open vscode using the "Developer Command Prompt"
```
cd <path to StudyDungeon>
code .
```

In VScode to build:
<kbd>ctrl</kbd> + <kbd>shift</kbd> + <kbd>B</kbd>


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
