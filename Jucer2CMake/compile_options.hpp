// Copyright (c) 2017 Alain Martin, Matthieu Talbot
//
// This file is part of JUCE.cmake.
//
// JUCE.cmake is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JUCE.cmake is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JUCE.cmake.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <string>


inline std::string getGCCOptimization(const int optimizationLevel)
{
  switch (optimizationLevel)
  {
  case 1:
    return "-O0";
  case 4:
    return "-O1";
  case 5:
    return "-O2";
  case 3:
    return "-O3";
  case 2:
    return "-Os";
  case 6:
    return "-Ofast";
  }
  return "";
}


inline std::string getMSVCOptimization(const int optimizationLevel)
{
  switch (optimizationLevel)
  {
  case 1:
    return "/Od";
  case 2:
    return "/O1";
  case 3:
    return "/O2";
  }

  return "";
}
