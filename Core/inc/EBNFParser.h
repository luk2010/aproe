////////////////////////////////////////////////////////////
/** @file EBNFParser.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 08/11/2014 - 05/02/2015
 *
 *  @brief
 *  Defines the EBNFParser class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
////////////////////////////////////////////////////////////
#ifndef APRO_EBNFPARSER_H
#define APRO_EBNFPARSER_H

#include "Platform.h"

#include "Array.h"
#include "SString.h"

#include "TokenScanner.h"

namespace APro
{
    namespace EBNF
    {
        // EBNF is organized like :
        //
        // sentence = " rname ::= rules_list "
        // rname = A complex rule.
        // rules_list = " rule | rule | rule "
        // rule = " element , (element)* "
        // element = rule | statment
        //
        // Examples :
        //
        // . I want to look at the verb 'look' in this sentence.
        // verblook ::= "look"
        // . I want to look at the chain 'look at' in this sentence, or the 'sentence' keyword.
        // verblook2 ::= "look at" | "sentence"
        // . I want to take everything from 'from' to the end point of this sentence.
        // letters ::= ?:[a-z|A-Z]:?
        // takese ::= "from" , {letters} , "."
        //
        // Common symbols used in EBNF :
        //
        // ::= assignment operator
        // | OR operator, define a new rule.
        // , AND operator, concatenation
        // () Grouping, treated as unit and can be found.
        // [] Option, can be one or zero times.
        // {} Repetition, can be zero or more times.
        // (* *) Comments
        // ? ? Special symbols.
        // ; Termination symbol, optional
        // "" Ascii String
        // '' Ascii String
        // - Exception
        //
        // Special symbols used in EBNF in AProE :
        //
        // ?: :? Is the symbol for special AProE commands.
        // [] Range command, with '-' as 'to' command, like a-A, separated with '|'
        // -> Letter is 'a' to 'z' or 'A' to 'Z' : letters ::= ?:[a-z|A-Z]:?
        //
        // #x10FFFF : UTF8 Character CodePoint. Described as #x then the CodePoint value, maximum
        // is 10FFFF. This function is valueable in every EBNF scripts.
        //      Max   : #x10FFFF
        //      Min   : #x000000
        //      Notes : Values can have from 1 to 6 figures.
        //
        // Space between elements is note counted. Space is allowed in Strings ('' or "").
        // In each sentence, only Ascii characters are allowed. You are greatly encouraged to used
        // the form #x123456 (with max value #x10FFFF).
        //
        
        class Element
        {
        public:
            
            virtual ~Element() {
                while (!mchilds.isEmpty()) {
                    delete mchilds[0];
                    mchilds.erase(mchilds.begin());
                }
            }
            
            enum Type
            {
                ETUnknown        = 0x00,
                ETString         = 0x01,
                ETNumeric        = 0x02,
                ETRule           = 0x03,
                ETConcatening    = 0x04,
                ETRepetition     = 0x05,
                ETOption         = 0x06,
                ETGroup          = 0x07,
                ETSentence       = 0x08,
                
                /* These are specific type for EBNF in AProE engine. */
                ETSpecial               = 0xD0,
                ETSpecialRange          = 0xD1,
                ETSpecialRangeFromTo    = 0xD2,
                ETSpecialUTF8CodePoint  = 0xD3
            };
            
            virtual const char* name() const = 0;
            virtual const Type type() const = 0;
            
            Array<Element*> mchilds;
            String          mcontent;
            
        };
        
        class ElementUnknown : public Element
        {
        public:
            
            ~ElementUnknown() {}
            
            const char* name() const { return "EBNF::Unknown"; }
            const Type type() const { return ETUnknown; }
        };
        
        class ElementString : public Element
        {
        public:
            
            ~ElementString() {}
            
            const char* name() const { return "EBNF::String"; }
            const Type type() const { return ETString; }
            
            String content;
        };
        
        class ElementNumeric : public Element
        {
        public:
            
            ~ElementNumeric() {}
            
            union Data
            {
                u32   i;
                float f;
            };
            
            Data n;
            
            const char* name() const { return "EBNF::Numeric"; }
            const Type type() const { return ETNumeric; }
        };
        
        class ElementRule : public Element
        {
        public:
            ~ElementRule() {}
            
            const char* name() const { return "EBNF::Rule"; }
            const Type type() const { return ETRule; }
            
            
        };
        
        class ElementConcatening : public Element
        {
        public:
            
            ~ElementConcatening() {}
            
            const char* name() const { return "EBNF::Concatening"; }
            const Type type() const { return ETConcatening; }
            
            Element* rhs; // Right hand side element
            Element* lhs; // Left hand side element
        };
        
        class ElementRepetition : public Element
        {
        public:
            
            ~ElementRepetition() {}
            
            const char* name() const { return "EBNF::Repetition"; }
            const Type type() const { return ETRepetition; }
        };
        
        class ElementOption : public Element
        {
        public:
            
            ~ElementOption() {}
            
            const char* name() const { return "EBNF::Option"; }
            const Type type() const { return ETOption; }
        };
        
        class ElementGroup : public Element
        {
        public:
            
            ~ElementGroup() {}
            
            const char* name() const { return "EBNF::Group"; }
            const Type type() const { return ETGroup; }
        };
        
        class ElementSentence : public Element
        {
        public:
            
            ~ElementSentence() {}
            
            /// @brief Change elements contents to given one.
            bool parse(const String& str);
            
            const char* name() const { return "EBNF::Sentence"; }
            const Type type() const { return ETSentence; }
            String mname;
        };
        
        /*
         
            When parsing a simple sentence :
         letter ::= ?:[a-z|A-Z]:?
         word   ::= letter, {letter},' '
         string ::= {' '}, (word), {[' '], {(word)}}
         
         
         Structure Organization                             Content of the structure
         
         string -> Sentence
            new Rule                                            {' '}, (word), {[' '], {(word)}}
                new Element -> Concataining
                    lhs -> new Element -> Bracket               {' '}
                        new Element -> String                   ' '
                    rhs -> new Element -> Concataining          (word), {[' '], {(word)}}
                        lhs -> new Element -> Group             (word)
                            new Element -> Sentence             word
                        rhs -> new Element -> Bracket           {[' '], {(word)}}
                            new Element -> Concataining
                                lhs -> new Element -> Option    [' ']
                                    new Element -> String       ' '
                                rhs -> new Element -> Bracket   {(word)}
                                    new Element -> Group        (word)
                                        new Element -> Sentence word
         
         For every Sentences (word) ;
         
         word -> Sentence
            new Rule                                            letter, {letter},' '
                new Element -> Concataining             
                    lhs -> new Element -> Sentence              letter
                    rhs -> new Element -> Concataining          
                        lhs -> new Element -> Bracket           {letter}
                            new Element -> Sentence             letter
                        rhs -> new Element -> String            ' '
         
         For every Sentences (letter) ;
         
         letter -> Sentence
            new Rule                                            ?:[a-z|A-Z]:?
                new Element -> SpecialEngine                    ?:[a-z|A-Z]:?
                    new Element -> Range                        [a-z|A-Z]
                        new Element -> FromTo                   a-z
                        new Element -> FromTo                   A-Z
                The SpecialEngineRange command will be translated into :
                new Element -> Rule
                    new Element -> String                       'a' 
                new Element -> Rule 
                    new Element -> String                       'b'
                [...]
                new Element -> Rule                             'Z'
         
        */
        
        /////////////////////////////////////////////////////////////
        /** @class EBNFScanner
         *  @brief A specialized TokenScanner for EBNF.
         **/
        /////////////////////////////////////////////////////////////
        class EBNFScanner : public TokenScanner
        {
        public:
            
            enum TokType
            {
                TokIdentifier = 1,
                TokLiteral    = 2,
                TokComment    = 3,
                TokOperator   = 4
            };
            
            /////////////////////////////////////////////////////////////
            /** @brief Start the scanning of the next token.
             **/
            /////////////////////////////////////////////////////////////
            void nextToken();
            
            /////////////////////////////////////////////////////////////
            /** @brief Returns the content's token without the Quotes.
             *  @note This function works on Literal Token types only, or
             *  returns the full token content.
            **/
            /////////////////////////////////////////////////////////////
            static String GetUnquotedLiteral(const Token& literal);
            
        protected:
            
            /////////////////////////////////////////////////////////////
            /** @brief Scans an Identifier.
             **/
            /////////////////////////////////////////////////////////////
            Token scanIdentifier();
            
            /////////////////////////////////////////////////////////////
            /** @brief Scans a Literal.
             **/
            /////////////////////////////////////////////////////////////
            Token scanLiteral();
            
            /////////////////////////////////////////////////////////////
            /** @brief Scans an Operator.
             **/
            /////////////////////////////////////////////////////////////
            Token scanOperator();
            
            /////////////////////////////////////////////////////////////
            /** @brief Scans a Comment.
             **/
            /////////////////////////////////////////////////////////////
            Token scanComment();
            
        };
        
    }

/*
    class EBNFParser
    {
    public:
        

        bool addSentence(const char* ebnfs);
        
        bool parse(const UTF8String& sentence);
        
    private:
        
        Array<ElementSentence*> sentences;
    };
*/
}

#endif // APRO_EBNFPARSER_H
