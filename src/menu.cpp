#include "menu.h"
#include <algorithm>
#include <iomanip>

MenuItem::MenuItem(const std::string &label, std::function<void()> action)
    : label(label), action(action), subMenu(nullptr)
{
}

MenuItem::MenuItem(const std::string &label, std::shared_ptr<Menu> subMenu)
    : label(label), action(nullptr), subMenu(subMenu)
{
}

Menu::Menu(const std::string &title) : title(title), selectedIndex(0)
{
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::addItem(const std::string &label, std::function<void()> action)
{
    items.emplace_back(label, action);
}

void Menu::addItem(const std::string &label, std::shared_ptr<Menu> subMenu)
{
    items.emplace_back(label, subMenu);
}

void Menu::setColor(WORD foreground, WORD background)
{
    SetConsoleTextAttribute(consoleHandle, foreground | (background << 4));
}

void Menu::moveCursor(SHORT x, SHORT y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(consoleHandle, coord);
}

int Menu::getArrowKeyNavigation()
{
    int ch = _getch();
    if (ch == 0 || ch == 224)
    {
        switch (_getch())
        {
        case 72:
            return -1;
        case 80:
            return 1;
        case 75:
            return 4;
        case 77:
            return 5;
        }
    }
    else if (ch == 13)
    {
        return 2;
    }
    else if (ch == 27)
    {
        return 3;
    }
    return 0;
}

GridMenu::GridMenu(const std::string &title, int width, int height)
    : Menu(title), gridWidth(width), gridHeight(height), selectedRow(0), selectedCol(0)
{
}

void GridMenu::addGridItem(const std::string &label,
                           std::function<void()> action,
                           int row,
                           int col,
                           int width,
                           int height)
{
    gridItems.emplace_back(MenuItem(label, action), row, col, width, height);
}

void GridMenu::addGridItem(const std::string &label,
                           std::shared_ptr<Menu> subMenu,
                           int row,
                           int col,
                           int width,
                           int height)
{
    gridItems.emplace_back(MenuItem(label, subMenu), row, col, width, height);
}

void GridMenu::display()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    system("cls");
    drawBorder(consoleWidth, consoleHeight);

    moveCursor(static_cast<SHORT>((consoleWidth - title.length()) / 2), 1);
    std::cout << title;

    int cellWidth = (consoleWidth - 2) / gridWidth;
    int cellHeight = (consoleHeight - 4) / gridHeight;

    for (const auto &gridItem : gridItems)
    {
        int startX = 1 + gridItem.col * cellWidth;
        int startY = 3 + gridItem.row * cellHeight;
        int itemWidth = gridItem.width * cellWidth;
        int itemHeight = gridItem.height * cellHeight;

        drawGridItem(gridItem, startX, startY, itemWidth, itemHeight);
    }
}

void GridMenu::run()
{
    while (true)
    {
        display();
        int navigation = getArrowKeyNavigation();
        handleNavigation(navigation);
        if (navigation == 3)
        {
            system("cls");
            break;
        }
    }
}

void GridMenu::drawBorder(int width, int height)
{
    moveCursor(0, 0);
    std::cout << static_cast<char>(218) << std::string(width - 2, static_cast<char>(196)) << static_cast<char>(191);

    for (int i = 1; i < height - 1; ++i)
    {
        moveCursor(0, static_cast<SHORT>(i));
        std::cout << static_cast<char>(179);
        moveCursor(static_cast<SHORT>(width - 1), static_cast<SHORT>(i));
        std::cout << static_cast<char>(179);
    }

    moveCursor(0, static_cast<SHORT>(height - 1));
    std::cout << static_cast<char>(192) << std::string(width - 2, static_cast<char>(196)) << static_cast<char>(217);
}

void GridMenu::drawGridItem(const GridItem &item, int startX, int startY, int width, int height)
{
    bool isSelected = (item.row == selectedRow && item.col == selectedCol);

    if (isSelected)
    {
        setColor(0, 15);
    }
    else
    {
        setColor(15, 0);
    }

    for (int i = 0; i < height; ++i)
    {
        moveCursor(static_cast<SHORT>(startX), static_cast<SHORT>(startY + i));
        if (i == height / 2)
        {
            int labelLength = static_cast<int>(item.item.label.length());
            int padding = (width - labelLength) / 2;
            std::cout << std::setw(padding) << "" << item.item.label << std::setw(width - padding - labelLength) << "";
        }
        else
        {
            std::cout << std::string(width, ' ');
        }
    }

    setColor(15, 0);
}

bool GridMenu::isValidGridItem(int row, int col) const
{
    return std::any_of(gridItems.begin(), gridItems.end(), [row, col](const GridItem &item) {
        return row >= item.row && row < item.row + item.height && col >= item.col && col < item.col + item.width;
    });
}

std::pair<int, int> GridMenu::findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const
{
    int row = startRow;
    int col = startCol;

    auto currentItem = std::find_if(gridItems.begin(), gridItems.end(), [row, col](const GridItem &item) {
        return row >= item.row && row < item.row + item.height && col >= item.col && col < item.col + item.width;
    });

    if (currentItem != gridItems.end())
    {
        if (colDelta > 0)
            col = currentItem->col + currentItem->width - 1;
        else if (colDelta < 0)
            col = currentItem->col;
        if (rowDelta > 0)
            row = currentItem->row + currentItem->height - 1;
        else if (rowDelta < 0)
            row = currentItem->row;
    }

    do
    {
        row = (row + rowDelta + gridHeight) % gridHeight;
        col = (col + colDelta + gridWidth) % gridWidth;

        if (isValidGridItem(row, col))
        {
            auto it = std::find_if(gridItems.begin(), gridItems.end(), [row, col](const GridItem &item) {
                return row >= item.row && row < item.row + item.height && col >= item.col &&
                       col < item.col + item.width;
            });
            if (it != gridItems.end())
            {
                return std::make_pair(it->row, it->col);
            }
        }

        if (row == startRow && col == startCol)
        {
            break;
        }

    } while (true);

    return std::make_pair(startRow, startCol);
}

void GridMenu::handleNavigation(int navigation)
{
    int newRow = selectedRow;
    int newCol = selectedCol;

    switch (navigation)
    {
    case -1:
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, -1, 0);
        break;
    case 1:
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 1, 0);
        break;
    case 4:
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 0, -1);
        break;
    case 5:
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 0, 1);
        break;
    case 2:
        executeSelectedItem();
        return;
    }
    if (newRow != selectedRow || newCol != selectedCol)
    {
        selectedRow = newRow;
        selectedCol = newCol;
    }
}

void GridMenu::executeSelectedItem()
{
    auto it = std::find_if(gridItems.begin(), gridItems.end(), [this](const GridItem &item) {
        return selectedRow >= item.row && selectedRow < item.row + item.height && selectedCol >= item.col &&
               selectedCol < item.col + item.width;
    });
    if (it != gridItems.end())
    {
        if (it->item.isSubMenu())
        {
            it->item.subMenu->run();
        }
        else if (it->item.action)
        {
            it->item.action();
        }
    }
}

int GridMenu::getGridWidth() const
{
    return gridWidth;
}

int GridMenu::getGridHeight() const
{
    return gridHeight;
}

void GridMenu::setGridWidth(int width)
{
    gridWidth = width;
}

void GridMenu::setGridHeight(int height)
{
    gridHeight = height;
}