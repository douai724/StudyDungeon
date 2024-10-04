/**
 * @file card_types.h
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef CARD_TYPES_H
#define CARD_TYPES_H

#include <map>

/**
 * @brief All possible effects that a playing card could have.
 *
 */
enum Type
{
    damage,
    heal,
    swapHand
};

const std::map<enum Type, float> cardPossibilities{{damage, 0.8}, {heal, 0.2}, {swapHand, 0.1}};
#endif
