/**
 * @file card_types.h
 * @author Green Aligators
 * @brief
 * @version 0.1
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef CARD_TYPES_H
#define CARD_TYPES_H

/**
 * @brief All possible effects that a playing card could have.
 *
 */
enum Type
{
    damage,
    heal,
    block,
    swapHand
};

#endif
