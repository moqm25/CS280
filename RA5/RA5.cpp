#include "lex.h"
#include <iostream>
#include <map>
using namespace std;

ostream& operator<<(ostream& out, const LexItem& tok){
    string x = tok.GetLexeme();
    switch (tok.GetToken()){
        case IDENT:
            if(x=="PROGRAM" || x=="PRINT" || x=="INT" || x=="END" || x=="FLOAT" || x=="ELSE" || x=="IF" || x=="THEN" || x=="BOOL"){
                out << "KEYWORD: "<< tok.GetLexeme() << " at Line "<<tok.GetLinenum()<<endl;
            }else{
                out << "IDENT: "<< tok.GetLexeme() << " at Line "<<tok.GetLinenum()<<endl;
            }
            break;
        case ERR:  
            out << "Error: : \""<< tok.GetLexeme() << "\" at Line "<<tok.GetLinenum()<<endl;
            break;
        case COMMA:
            out << "COMMA: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case SEMICOL:
            out << "SEMICOL: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case PLUS:
            out << "PLUS: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case MINUS:
            out << "MINUS: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case MULT:
            out << "MULT: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case DIV:
            out << "DIV: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case ASSOP:
            out << "ASSOP: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case LPAREN:
            out << "LPAREN: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case RPAREN:
            out << "RPAREN: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case EQUAL:
            out << "ASSOP: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case GTHAN:
            out << "ASSOP: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case LTHAN:
            out << "ASSOP: \'"<< tok.GetLexeme() << "\' at Line "<<tok.GetLinenum()<<endl;
            break;
        case ICONST:
            out << "ICONST: ("<< tok.GetLexeme() << ") at Line "<<tok.GetLinenum()<<endl;
            break;
        case RCONST:
            out << "RCONST: ("<< tok.GetLexeme() << ") at Line "<<tok.GetLinenum()<<endl;
            break;
        case BCONST:
            out << "BCONST: ("<< tok.GetLexeme() << ") at Line "<<tok.GetLinenum()<<endl;
            break;
        case SCONST:
            out << "SCONST: \""<< tok.GetLexeme() << "\" at Line "<<tok.GetLinenum()<<endl;
            break;
        default:
            out << "KEYWORD: " << tok.GetLexeme() << " at Line "<<tok.GetLinenum()<<endl;
            break;
    }
    return out;
}

LexItem id_or_kw(const string& lexeme, int linenum){
	map<string,Token> kwmap = {
		{ "PROGRAM", PROGRAM},
		{ "PRINT", PRINT},
		{ "INT", INT},
		{ "END", END },
		{ "FLOAT", FLOAT},
		{ "ELSE", ELSE },
		{ "IF", IF },
		{ "THEN", THEN},
		{ "TRUE", TRUE},
		{ "FALSE", FALSE},
		{ "BOOL", BOOL }
    };  	

    auto kIt = kwmap.find(lexeme);
    if( kIt != kwmap.end() ){
        return LexItem(kIt->second,lexeme,linenum);
    }
    else{
        return LexItem(IDENT, lexeme,linenum);
    }
}