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
//   JUCE/extras/Projucer/Source/Utility/jucer_MiscUtilities.cpp
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

#include "../jucer_Headers.h"

//==============================================================================
String createAlphaNumericUID()
{
    String uid;
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    Random r;

    uid << chars [r.nextInt (52)]; // make sure the first character is always a letter

    for (int i = 5; --i >= 0;)
    {
        r.setSeedRandomly();
        uid << chars [r.nextInt (62)];
    }

    return uid;
}

String hexString8Digits (int value)
{
    return String::toHexString (value).paddedLeft ('0', 8);
}

String createGUID (const String& seed)
{
    const String hex (MD5 ((seed + "_guidsalt").toUTF8()).toHexString().toUpperCase());

    return "{" + hex.substring (0, 8)
         + "-" + hex.substring (8, 12)
         + "-" + hex.substring (12, 16)
         + "-" + hex.substring (16, 20)
         + "-" + hex.substring (20, 32)
         + "}";
}

String escapeSpaces (const String& s)
{
    return s.replace (" ", "\\ ");
}

String addQuotesIfContainsSpaces (const String& text)
{
    return (text.containsChar (' ') && ! text.isQuotedString()) ? text.quoted() : text;
}

void setValueIfVoid (Value value, const var& defaultValue)
{
    if (value.getValue().isVoid())
        value = defaultValue;
}

//==============================================================================
StringPairArray parsePreprocessorDefs (const String& text)
{
    StringPairArray result;
    String::CharPointerType s (text.getCharPointer());

    while (! s.isEmpty())
    {
        String token, value;
        s = s.findEndOfWhitespace();

        while ((! s.isEmpty()) && *s != '=' && ! s.isWhitespace())
            token << s.getAndAdvance();

        s = s.findEndOfWhitespace();

        if (*s == '=')
        {
            ++s;

            s = s.findEndOfWhitespace();

            while ((! s.isEmpty()) && ! s.isWhitespace())
            {
                if (*s == ',')
                {
                    ++s;
                    break;
                }

                if (*s == '\\' && (s[1] == ' ' || s[1] == ','))
                    ++s;

                value << s.getAndAdvance();
            }
        }

        if (token.isNotEmpty())
            result.set (token, value);
    }

    return result;
}

StringPairArray mergePreprocessorDefs (StringPairArray inheritedDefs, const StringPairArray& overridingDefs)
{
    for (int i = 0; i < overridingDefs.size(); ++i)
        inheritedDefs.set (overridingDefs.getAllKeys()[i], overridingDefs.getAllValues()[i]);

    return inheritedDefs;
}

String createGCCPreprocessorFlags (const StringPairArray& defs)
{
    String s;

    for (int i = 0; i < defs.size(); ++i)
    {
        String def (defs.getAllKeys()[i]);
        const String value (defs.getAllValues()[i]);
        if (value.isNotEmpty())
            def << "=" << value;

        s += " -D" + def;
    }

    return s;
}

String replacePreprocessorDefs (const StringPairArray& definitions, String sourceString)
{
    for (int i = 0; i < definitions.size(); ++i)
    {
        const String key (definitions.getAllKeys()[i]);
        const String value (definitions.getAllValues()[i]);

        sourceString = sourceString.replace ("${" + key + "}", value);
    }

    return sourceString;
}

StringArray getSearchPathsFromString (const String& searchPath)
{
    StringArray s;
    s.addTokens (searchPath, ";\r\n", StringRef());
    return getCleanedStringArray (s);
}

StringArray getCommaOrWhitespaceSeparatedItems (const String& sourceString)
{
    StringArray s;
    s.addTokens (sourceString, ", \t\r\n", StringRef());
    return getCleanedStringArray (s);
}

StringArray getCleanedStringArray (StringArray s)
{
    s.trim();
    s.removeEmptyStrings();
    return s;
}

//==============================================================================
static bool keyFoundAndNotSequentialDuplicate (XmlElement* xml, const String& key)
{
    forEachXmlChildElementWithTagName (*xml, element, "key")
    {
        if (element->getAllSubText().trim().equalsIgnoreCase (key))
        {
            if (element->getNextElement() != nullptr && element->getNextElement()->hasTagName ("key"))
            {
                // found broken plist format (sequential duplicate), fix by removing
                xml->removeChildElement (element, true);
                return false;
            }

            // key found (not sequential duplicate)
            return true;
        }
    }

     // key not found
    return false;
}

static bool addKeyIfNotFound (XmlElement* xml, const String& key)
{
    if (! keyFoundAndNotSequentialDuplicate (xml, key))
    {
        xml->createNewChildElement ("key")->addTextElement (key);
        return true;
    }

    return false;
}

void addPlistDictionaryKey (XmlElement* xml, const String& key, const String& value)
{
    if (addKeyIfNotFound (xml, key))
        xml->createNewChildElement ("string")->addTextElement (value);
}

void addPlistDictionaryKeyBool (XmlElement* xml, const String& key, const bool value)
{
    if (addKeyIfNotFound (xml, key))
        xml->createNewChildElement (value ? "true" : "false");
}

void addPlistDictionaryKeyInt (XmlElement* xml, const String& key, int value)
{
    if (addKeyIfNotFound (xml, key))
        xml->createNewChildElement ("integer")->addTextElement (String (value));
}

//==============================================================================
void autoScrollForMouseEvent (const MouseEvent& e, bool scrollX, bool scrollY)
{
    if (Viewport* const viewport = e.eventComponent->findParentComponentOfClass<Viewport>())
    {
        const MouseEvent e2 (e.getEventRelativeTo (viewport));
        viewport->autoScroll (scrollX ? e2.x : 20, scrollY ? e2.y : 20, 8, 16);
    }
}

//==============================================================================
int indexOfLineStartingWith (const StringArray& lines, const String& text, int index)
{
    const int len = text.length();

    for (const String* i = lines.begin() + index, * const e = lines.end(); i < e; ++i)
    {
        if (CharacterFunctions::compareUpTo (i->getCharPointer().findEndOfWhitespace(),
                                             text.getCharPointer(), len) == 0)
            return index;

        ++index;
    }

    return -1;
}

//==============================================================================
bool fileNeedsCppSyntaxHighlighting (const File& file)
{
    if (file.hasFileExtension (sourceOrHeaderFileExtensions))
        return true;

    // This is a bit of a bodge to deal with libc++ headers with no extension..
    char fileStart[128] = { 0 };
    FileInputStream fin (file);
    fin.read (fileStart, sizeof (fileStart) - 4);

    return CharPointer_UTF8::isValidString (fileStart, sizeof (fileStart))
             && String (fileStart).trimStart().startsWith ("// -*- C++ -*-");
}
