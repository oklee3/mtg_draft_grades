#pragma once

#include "card.h"
#include <vector>

/*
* 
*/
inline std::vector<Color> getCardColors(unsigned int colors)
{
    std::vector<Color> result;

    for (Color color : {
        Color::White,
        Color::Blue,
        Color::Black,
        Color::Red,
        Color::Green
    })
    {
        if (colors & static_cast<unsigned int>(color))
            result.push_back(color);
    }

    return result;
}