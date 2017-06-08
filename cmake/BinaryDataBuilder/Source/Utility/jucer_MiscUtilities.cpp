// The content of this file was copied from
// https://github.com/WeAreROLI/JUCE/blob/4.3.1/extras/Projucer/Source/Utility/jucer_MiscUtilities.h

// clang-format off

#include "../jucer_Headers.h"

String hexString8Digits (int value)
{
    return String::toHexString (value).paddedLeft ('0', 8);
}

// clang-format on
