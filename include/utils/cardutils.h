#pragma once

#include "card.h"
#include <vector>

/*
* 
*/
inline std::vector<color> getCardColors(unsigned int colors)
{
    std::vector<color> result;

    for (color color : {
        color::White,
        color::Blue,
        color::Black,
        color::Red,
        color::Green
    })
    {
        if (colors & static_cast<unsigned int>(color))
            result.push_back(color);
    }

    return result;
}
