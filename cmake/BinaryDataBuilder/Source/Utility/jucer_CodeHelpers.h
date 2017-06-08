// Copyright (c) 2016 Alain Martin
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

// The content of this file was copied from
//   JUCE/extras/Projucer/Source/Utility/jucer_CodeHelpers.h
// at commit fc9937d83201331eb00303b0fbc1b77d47ae27ac (tags/4.3.1).


/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef JUCER_CODEHELPERS_H_INCLUDED
#define JUCER_CODEHELPERS_H_INCLUDED


//==============================================================================
namespace CodeHelpers
{
    String indent (const String& code, const int numSpaces, bool indentFirstLine);
    String makeValidIdentifier (String s, bool capitalise, bool removeColons, bool allowTemplates);
    String createIncludeStatement (const File& includedFile, const File& targetFile);
    String createIncludeStatement (const String& includePath);
    String makeHeaderGuardName (const File& file);
    String makeBinaryDataIdentifierName (const File& file);

    String stringLiteral (const String& text, int maxLineLength = -1);
    String floatLiteral (double value, int numDecPlaces);
    String boolLiteral (bool value);

    String colourToCode (Colour col);
    String justificationToCode (Justification);

    String alignFunctionCallParams (const String& call, const StringArray& parameters, int maxLineLength);

    void writeDataAsCppLiteral (const MemoryBlock& data, OutputStream& out,
                                bool breakAtNewLines, bool allowStringBreaks);

    void createStringMatcher (OutputStream& out, const String& utf8PointerVariable,
                              const StringArray& strings, const StringArray& codeToExecute, const int indentLevel);

    String getLeadingWhitespace (String line);
    int getBraceCount (String::CharPointerType line);
    bool getIndentForCurrentBlock (CodeDocument::Position pos, const String& tab,
                                   String& blockIndent, String& lastLineIndent);
}


#endif   // JUCER_CODEHELPERS_H_INCLUDED
