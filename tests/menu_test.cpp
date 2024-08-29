#include <catch2/catch_test_macros.hpp>
#include "menu.h"
#include "util.h"
#include <Windows.h>

extern bool isTestMode;


TEST_CASE("GridMenu", "[menu]")
{
    isTestMode = true;
    SECTION("Add grid item with action")
    {
        auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
        bool actionCalled = false;
        gridMenu->addGridItem("Item 1", [&actionCalled]() { actionCalled = true; }, 0, 0, 1, 1);
        
        REQUIRE(gridMenu->getGridItems().size() == 1);
        REQUIRE(gridMenu->getGridItems()[0].item.label == "Item 1");
        
        gridMenu->getGridItems()[0].item.action();
        REQUIRE(actionCalled);
    }
    
    SECTION("Add grid item with submenu")
    {
        auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
        auto subMenu = std::make_shared<GridMenu>("Submenu", 2, 2);
        gridMenu->addGridItem("Item 2", subMenu, 1, 1, 2, 2);
        
        REQUIRE(gridMenu->getGridItems().size() == 1);
        REQUIRE(gridMenu->getGridItems()[0].item.label == "Item 2");
        REQUIRE(gridMenu->getGridItems()[0].item.subMenu == subMenu);
    }
    
    SECTION("Navigation")
    {
        auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
        gridMenu->addGridItem("Item 1", []() {}, 0, 0, 1, 1);
        gridMenu->addGridItem("Item 2", []() {}, 0, 1, 1, 1);
        
        gridMenu->setSelectedRow(0);
        gridMenu->setSelectedCol(0);
        
        gridMenu->handleNavigation(1); // Down
        REQUIRE(gridMenu->getSelectedRow() == 0);
        REQUIRE(gridMenu->getSelectedCol() == 0);
        
        gridMenu->handleNavigation(5); // Right
        REQUIRE(gridMenu->getSelectedRow() == 0);
        REQUIRE(gridMenu->getSelectedCol() == 1);
        
        gridMenu->handleNavigation(-1); // Up
        REQUIRE(gridMenu->getSelectedRow() == 0);
        REQUIRE(gridMenu->getSelectedCol() == 1);
        
        gridMenu->handleNavigation(4); // Left
        REQUIRE(gridMenu->getSelectedRow() == 0);
        REQUIRE(gridMenu->getSelectedCol() == 0);
    }
    

    // SECTION("Delete selected item")
    // {
    //     auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
    //     gridMenu->addGridItem("Item 1", []() {}, 0, 0, 1, 1);
    //     gridMenu->addGridItem("Item 2", []() {}, 1, 1, 1, 1);
        
    //     gridMenu->setSelectedRow(0);
    //     gridMenu->setSelectedCol(0);
        
    //     gridMenu->deleteSelectedItem();

    //     REQUIRE(gridMenu->getGridItems().size() == 1);
    //     REQUIRE(gridMenu->getGridItems()[0].item.label == "Item 2");

    // }

    SECTION("Find next valid item")
    {
        auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
        gridMenu->addGridItem("Item 1", []() {}, 0, 0, 1, 1);
        gridMenu->addGridItem("Item 2", []() {}, 0, 1, 1, 1);
        
        auto nextItem = gridMenu->findNextValidItem(0, 0, 0, 1);
        REQUIRE(nextItem.first == 0);
        REQUIRE(nextItem.second == 1);
        
        nextItem = gridMenu->findNextValidItem(0, 1, 0, -1);
        REQUIRE(nextItem.first == 0);
        REQUIRE(nextItem.second == 0);
    }
    
    SECTION("Execute selected item")
    {
        auto gridMenu = std::make_shared<GridMenu>("Test Menu", 3, 3);
        bool actionCalled = false;
        gridMenu->addGridItem("Item 1", [&actionCalled]() { actionCalled = true; }, 0, 0, 1, 1);
        
        gridMenu->setSelectedRow(0);
        gridMenu->setSelectedCol(0);
        
        gridMenu->executeSelectedItem();
        REQUIRE(actionCalled);
    }
}