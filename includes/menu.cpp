#include "menu.h"
#include <algorithm>
#include <iomanip>


/**
 * @brief Construct a new Menu Item:: Menu Item object that has an action
 * 
 * @param label is the text label of the menu item
 * @param action is the function to be executed when the menu item is selected
 */
MenuItem::MenuItem(const std::string &label, std::function<void()> action)
    : label(label), action(action), subMenu(nullptr)
{
}

/**
 * @brief Construct a new Menu Item:: Menu Item object that has a submenu
 *
 * @param label is the text label of the menu item
 * @param subMenu is the submenu to be displayed when the menu item is selected
 */
MenuItem::MenuItem(const std::string &label, std::shared_ptr<Menu> subMenu)
    : label(label), action(nullptr), subMenu(subMenu)
{
}

/**
 * @brief Construct a new Menu:: Menu object that has a title.
 *
 * @param title is the text title of the menu
 */
Menu::Menu(const std::string &title) : title(title), selectedIndex(0)
{
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

/**
 * @brief Add a new menu item to the menu
 *
 * @param label is the text label of the menu item
 * @param action is the function to be executed when the menu item is selected
 */
void Menu::addItem(const std::string &label, std::function<void()> action)
{
    items.emplace_back(label, action);
}

/**
 * @brief Add a new menu item to the menu
 * 
 *
 * @param label is the text label of the menu item
 * @param subMenu is the submenu to be displayed when the menu item is selected
 */
void Menu::addItem(const std::string &label, std::shared_ptr<Menu> subMenu)
{
    items.emplace_back(label, subMenu);
}

/**
 * @brief Set the color of the text in the console
 *
 * @param foreground is the color of the text
 * @param background is the color of the background
 */
void Menu::setColor(WORD foreground, WORD background)
{
    SetConsoleTextAttribute(consoleHandle, foreground | (background << 4));
}

/**
 * @brief Move the cursor to a specific position in the console
 *
 * @param x is the x-coordinate of the cursor
 * @param y is the y-coordinate of the cursor
 */
void Menu::moveCursor(SHORT x, SHORT y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(consoleHandle, coord);
}

/**
 * @brief Get the navigation input from the user
 * 
 * @return int is the navigation input
 */
int Menu::getArrowKeyNavigation() {
    int ch = _getch();
    if (ch == 0 || ch == 224) { // Arrow key pressed
        switch (_getch()) {
            case 72: return -1; // Up arrow
            case 80: return 1;  // Down arrow
            case 75: return 4;  // Left arrow
            case 77: return 5;  // Right arrow
        }
    }
    else if (ch == 13)
    { // Enter key
        return 2;
    }
    else if (ch == 27)
    { // Esc key
        return 3;
    }
    return 0;
}

/**
 * @brief Construct a new Grid Menu:: Grid Menu object that has a title, width, and height
 *
 * @param title is the text title of the menu
 * @param width is the width of the grid
 * @param height is the height of the grid
 */
GridMenu::GridMenu(const std::string &title, int width, int height)
    : Menu(title), gridWidth(width), gridHeight(height), selectedRow(0), selectedCol(0)
{
}

/**
 * @brief add a new grid item to the grid menu
 *
 * @param label is the text label of the menu item
 * @param action is the function to be executed when the menu item is selected
 * @param row is the row of the grid item
 * @param col is the column of the grid item
 * @param width is the width of the grid item
 * @param height is the height of the grid item
 */
void GridMenu::addGridItem(const std::string &label,
                           std::function<void()> action,
                           int row,
                           int col,
                           int width,
                           int height)
{
    gridItems.emplace_back(MenuItem(label, action), row, col, width, height);
}

/**
 * @brief add a new grid item to the grid menu
 *
 * @param label is the text label of the menu item
 * @param subMenu is the submenu to be displayed when the menu item is selected
 * @param row is the row of the grid item
 * @param col is the column of the grid item
 * @param width is the width of the grid item
 * @param height is the height of the grid item
 */
void GridMenu::addGridItem(const std::string &label,
                           std::shared_ptr<Menu> subMenu,
                           int row,
                           int col,
                           int width,
                           int height)
{
    gridItems.emplace_back(MenuItem(label, subMenu), row, col, width, height);
}

/**
 * @brief Display the grid menu.
 *
 * steps:
 * 1. Get the console screen buffer info
 * 2. Calculate the console width and height
 * 3. Clear the console
 * 4. Draw the border
 * 5. Move the cursor to the center of the title
 * 6. Display the title
 * 7. Calculate the cell width and height
 * 8. Loop through the grid items
 * 9. Calculate the start x and y position of the grid item
 * 10. Calculate the item width and height
 * 11. Draw the grid items
 */
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

/**
 * @brief Run the grid menu
 *
 * steps:
 * 1. Display the grid menu
 * 2. Get the navigation input
 * 3. Handle the navigation
 * 4. If the navigation is 3 (Esc), clear the console and exit the menu
 */
void GridMenu::run()
{
    while (true)
    {
        display();
        int navigation = getArrowKeyNavigation();
        handleNavigation(navigation);
        if (navigation == 3)
        { // Esc
            system("cls");
            break; // Exit the menu
        }
    }
}

/**
 * @brief Draw the border of the grid menu
 *
 * steps:
 * 1. Move the cursor to the top-left corner
 * 2. Draw the top border
 * 3. Loop through the height of the grid menu
 * 4. Move the cursor to the left and right border
 * 5. Draw the left and right border
 * 6. Move the cursor to the bottom-left corner
 * 7. Draw the bottom border
 *
 *
 * @param width is the width of the grid menu
 * @param height is the height of the grid menu
 */
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

/**
 * @brief Draw the grid item
 *
 * steps:
 * 1. Check if the item is selected
 * 2. Set the color of the text and background
 * 3. Loop through the height of the grid item
 * 4. Move the cursor to the start x and y position
 * 5. If the height is in the middle, calculate the padding
 * 6. Display the label
 * 7. If the height is not in the middle, display an empty string
 * 8. Reset the color to the default
 *
 * @param item is the grid item
 * @param startX is the start x position of the grid item
 * @param startY is the start y position of the grid item
 * @param width is the width of the grid item
 * @param height is the height of the grid item
 */
void GridMenu::drawGridItem(const GridItem &item, int startX, int startY, int width, int height)
{
    bool isSelected = (item.row == selectedRow && item.col == selectedCol);

    if (isSelected)
    {
        setColor(0, 15); // Black text on white background
    }
    else
    {
        setColor(15, 0); // White text on black background
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

    setColor(15, 0); // Reset to default colors
}

/**
 * @brief Check if the grid item is valid by checking if the row and column are within the grid item
 *
 * @param row is the row of the grid item
 * @param col is the column of the grid item
 * @return true if the grid item is valid
 * @return false if the grid item is not valid
 */
bool GridMenu::isValidGridItem(int row, int col) const
{
    return std::any_of(gridItems.begin(), gridItems.end(), [row, col](const GridItem &item) {
        return row >= item.row && row < item.row + item.height && col >= item.col && col < item.col + item.width;
    });
}

/**
 * @brief Find the next valid item in the grid menu by checking the row and column delta.
 *
 * steps:
 * 1. Loop through the grid menu
 * 2. Calculate the next row and column
 * 3. Check if the grid item is valid
 * 4. Find the top-left corner of the button
 * 5. Return the row and column of the next valid item
 *
 * a next valid item is a grid item that is within the grid menu and not empty.
 *
 * @param startRow is the starting row
 * @param startCol is the starting column
 * @param rowDelta is the change in row
 * @param colDelta is the change in column
 * @return std::pair<int, int> is the row and column of the next valid item
 */
std::pair<int, int> GridMenu::findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const
{
    int row = startRow;
    int col = startCol;
    
    // Find the current item
    auto currentItem = std::find_if(gridItems.begin(), gridItems.end(),
        [row, col](const GridItem& item) {
            return row >= item.row && row < item.row + item.height &&
                   col >= item.col && col < item.col + item.width;
        });

    if (currentItem != gridItems.end()) {
        // Adjust starting position based on the current item's size
        if (colDelta > 0) col = currentItem->col + currentItem->width - 1;
        else if (colDelta < 0) col = currentItem->col;
        if (rowDelta > 0) row = currentItem->row + currentItem->height - 1;
        else if (rowDelta < 0) row = currentItem->row;
    }

    do {
        // Move to the next cell in the specified direction
        row = (row + rowDelta + gridHeight) % gridHeight;
        col = (col + colDelta + gridWidth) % gridWidth;

        // Check if the current cell is valid
        if (isValidGridItem(row, col)) {
            auto it = std::find_if(gridItems.begin(), gridItems.end(),
                [row, col](const GridItem& item) {
                    return row >= item.row && row < item.row + item.height &&
                           col >= item.col && col < item.col + item.width;
                });
            if (it != gridItems.end()) {
                return {it->row, it->col};
            }
        }

        // If we've made a complete loop and haven't found a valid item, break
        if (row == startRow && col == startCol) {
            break;
        }

    } while (true);

    // If no valid item is found, return the starting position
    return {startRow, startCol};
}

/**
 * @brief Handle the navigation input
 *
 * steps:
 * 1. Find the next valid item
 * 2. If the new row and column are different from the selected row and column, update the selected row and column
 * 3. If the navigation is 2 (Enter), execute the selected item
 *
 * if the navigation is -1 (Up arrow), find the next valid item by decrementing the row.
 * if the navigation is 1 (Down arrow), find the next valid item by incrementing the row.
 * if the navigation is 4 (Left arrow), find the next valid item by decrementing the column.
 * if the navigation is 5 (Right arrow), find the next valid item by incrementing the column.
 *
 * if the navigation tries to go out of bounds, the next valid item will loop back to the other side of the grid menu.
 *
 * @param navigation is the navigation input
 */
void GridMenu::handleNavigation(int navigation)
{
    int newRow = selectedRow;
    int newCol = selectedCol;

    switch (navigation)
    {
    case -1: // Up arrow
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, -1, 0);
        break;
    case 1: // Down arrow
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 1, 0);
        break;
    case 4: // Left arrow
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 0, -1);
        break;
    case 5: // Right arrow
        std::tie(newRow, newCol) = findNextValidItem(selectedRow, selectedCol, 0, 1);
        break;
    case 2: // Enter
        executeSelectedItem();
        return;
    }
    if (newRow != selectedRow || newCol != selectedCol)
    {
        selectedRow = newRow;
        selectedCol = newCol;
    }
}

/**
 * @brief Execute the selected item
 *
 * steps:
 * 1. Find the grid item that contains the selected row and column
 * 2. If the item is a submenu, run the submenu
 * 3. If the item is an action, execute the action
 */
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


