/**
 * @file util.h
 * @author your name (you@domain.com)
 * @brief Contains useful helper functions
 * @version 0.1
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>


#ifndef UTIL_H_
#define UTIL_H_


/**
 * @brief Get the app path
 *
 * @return std::filesystem::path
 */
std::filesystem::path get_app_path();
#endif
