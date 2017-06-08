#pragma once

// The content of this file was copied from
// https://github.com/WeAreROLI/JUCE/blob/4.3.1/extras/Projucer/Source/Utility/jucer_CodeHelpers.h

// clang-format off

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

// clang-format on
