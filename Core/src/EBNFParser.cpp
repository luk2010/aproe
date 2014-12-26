////////////////////////////////////////////////////////////
/** @file EBNFParser.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 13/11/2014 - 29/11/2014
 *
 *  Implements the EBNFParser class.
 *
 **/
////////////////////////////////////////////////////////////
#include "EBNFParser.h"

namespace APro
{
    namespace EBNF
    {
        void EBNFScanner::nextToken()
        {
            if(currentToken > -1 && currentToken < tokens.size() - 1)
            {
                currentToken++;
                return;
            }
            
            while (hasNextCharacter())
            {
                nextCharacter();
                
                // Scan the Identifier type. [a-zA-Z\-_]
                if(TokenScannerHelper::isAlpha(currentCharacter))
                {
                    Token tok = scanIdentifier();
                    tokens.append(stdmove(tok));
                    currentToken++;
                    return;
                }
                
                // Scan a literal
                else if (TokenScannerHelper::isQuote(currentCharacter))
                {
                    Token tok = scanLiteral();
                    tokens.append(stdmove(tok));
                    currentToken++;
                    return;
                }
                
                // Scan an operator Token.
                else if (TokenScannerHelper::isOperator(currentCharacter))
                {
                    if (currentCharacter == '(' && peekCharacter() == '*') {
                        Token tok = scanComment();
                        tokens.append(stdmove(tok));
                        currentToken++;
                        return;
                    }
                    else {
                        Token tok = scanOperator();
                        tokens.append(stdmove(tok));
                        currentToken++;
                        return;
                    }
                }
                
                else if (TokenScannerHelper::isWhiteSpace(currentCharacter))
                {
                    // Ignore white spaces.
                }
                
                else
                {
                    raiseError (String("Invalid Character."));
                }
                
                checkNewLine();
            }
            
            tokens.append(Token(Token::TypeEof, String(""), createPosition()));
            currentToken++;
        }
        
        Token EBNFScanner::scanIdentifier()
        {
            TokPosition pos = createPosition();
            String content  = String(&currentCharacter, 1);
            CharArray _equals; _equals << '-' << '_';
            
            while (hasNextCharacter())
            {
                nextCharacter();
                
                // Ensure this character is in identifier.
                if(TokenScannerHelper::isAlphaNum(currentCharacter) ||
                   TokenScannerHelper::isEquals(currentCharacter, _equals) )
                {
                    content.append(currentCharacter);
                }
                else
                {
                    backupCharacter();
                    break;
                }
            }
            
            return Token (TokIdentifier, content, pos);
        }
        
        Token EBNFScanner::scanLiteral()
        {
            TokPosition pos = createPosition();
            char _start = getCurrentCharacter();
            String content(&_start, 1);
            
            while (hasNextCharacter())
            {
                nextCharacter();
                content.append(currentCharacter);
                
                // Ensure begin and end of literal.
                if(TokenScannerHelper::isQuote(currentCharacter) && currentCharacter == _start) {
                    break;
                }
            }
            
            return Token (TokLiteral, content, pos);
        }
        
        Token EBNFScanner::scanComment()
        {
            TokPosition pos = createPosition();
            String content  = String(&currentCharacter, 1);
            
            while (hasNextCharacter())
            {
                nextCharacter();
                content.append(currentCharacter);
                
                if(currentCharacter == '*' && peekCharacter() == ')')
                {
                    nextCharacter();
                    content.append(currentCharacter);
                    break;
                }
                
                checkNewLine();
            }
            
            return Token (TokComment, content, pos);
        }
        
        Token EBNFScanner::scanOperator()
        {
            TokPosition pos = createPosition();
            String content  = String(&currentCharacter, 1);
            char peak       = peekCharacter();
            
            if(currentCharacter == ':' && peak == ':')
            {
                nextCharacter();
                content.append(currentCharacter);
                nextCharacter();
                
                if(currentCharacter != '=') {
                    raiseError (String("Expecting '=' but got '") + currentCharacter + "' instead.");
                    content.append(currentCharacter);
                    return Token (Token::TypeInvalid, content, pos);
                }
                
                content.append(currentCharacter);
            }
            
            return Token (TokOperator, content, pos);
        }
        
        String EBNFScanner::GetUnquotedLiteral(const Token& literal)
        {
            if(literal.getType() == TokLiteral) {
                String result = literal;
                result.interpretastext();
                return result;
            }
            return literal.getContent();
        }
    }
    
    using namespace EBNF;
    
    bool EBNFParser::addSentence (const char* ebnfs)
    {
        if(!ebnfs)
            return false;
        
        int sz = String::Size(ebnfs);
        if(!sz)
            return false;
        
        String ebnfstr (ebnfs);
        
        // Okay here we have to get a new Sentence. Let it parse our string.
        ElementSentence* newsentence = AProNew (ElementSentence);
        if(!newsentence->parse(ebnfstr)) {
            AProDelete (newsentence);
            aprodebug("Can't parse sentence ('") << ebnfs << "').\n";
            return false;
        }
        
        // Just add it to the parser context.
        sentences.append(newsentence);
        
        aprodebug("Parsed new Sentence ('") << newsentence->mname << "').\n";
        return true;
    }
    
    
}