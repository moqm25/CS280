//
//  lex.cpp
//  PA 1
//
//  Created by Moiez Qamar on 10/21/22.
//

#include "lex.h"

map<Token,string> tokenPrint = {
        {PROGRAM, "PROGRAM"},
        {PRINT, "PRINT"},
        {INT, "INT"},
        { END, "END" },
        { FLOAT, "FLOAT"},
        { BOOL, "BOOL" },
        
        { ELSE, "ELSE" },
        { IF, "IF" },
        
        {THEN, "THEN"},
        { TRUE, "TRUE" },
        { FALSE, "FALSE" },
        
        { IDENT, "IDENT" },

        { ICONST, "ICONST" },
        { RCONST, "RCONST" },
        { SCONST, "SCONST" },
        { BCONST, "BCONST" },
        
        { PLUS, "PLUS" },
        { MINUS, "MINUS" },
        { MULT, "MULT" },
        { DIV, "DIV" },
        { ASSOP, "ASSOP" },
        { EQUAL, "EQUAL" },
        { GTHAN, "GTHAN" },
        { LTHAN, "LTHAN" },
        { AND, "AND" },
        { OR, "OR" },
        { NOT, "NOT" },
            
        { COMMA, "COMMA" },
        { LPAREN, "LPAREN" },
        { RPAREN, "RPAREN" },
        
        
        { SEMICOL, "SEMICOL" },
        
        { ERR, "ERR" },

        { DONE, "DONE" },
    };


ostream& operator<<(ostream& out, const LexItem& tok){
    if(tok==IDENT || tok==SCONST || tok==ERR || tok==RCONST || tok==ICONST || tok==BCONST){
        out<< (tokenPrint.find(tok.GetToken())->second) <<"("<<tok.GetLexeme()<<")";
    }else{
        out<<(tokenPrint.find(tok.GetToken())->second);
    }
    return out;
}
LexItem id_or_kw(const string& lexeme, int linenum);

LexItem getNextToken(istream& in, int& linenum){
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
    enum TokState {START, INID, INSTRING, ININT, INREAL, INCOMMENT} lexstate = START;
    char letter;
    string lexeme;
    while (in.get(letter)){
        //cout << "--Letter: _" << letter <<"_"<< endl;
        if(letter == '\n'){
            //cout<<"next line"<<endl;
            linenum++;
            //cout<<"====== LINES BEEN INCREASED - 1"<<endl;
            continue;
        }
        //lexeme+=letter;
        switch(lexstate){
            case START:
                if (isalnum(letter) || letter=='_'){
                    //cout<<"**is alnum"<<endl;
                    if(isalpha(letter) || letter=='_'){
                        //cout<<"**is alpha"<<endl;
                        lexeme+=letter;
                        lexstate=INID;
                        break;
                    }else if(isdigit(letter)){
                        //cout<<"**is number"<<endl;
                        lexeme+=letter;
                        lexstate=ININT;
                        break;
                    }else{
                        //cout<<"--isalnum"<<endl;
                        return (LexItem(ERR,lexeme,linenum));
                    }
                }else if (ispunct(letter)){
                    //cout<<"**is punct: "<<letter<<endl;
                    if(letter=='/' and in.peek()=='*'){
                        in.get(letter);
                        //cout<<"**comment started"<<endl;
                        lexstate=INCOMMENT;
                    }else if(letter==','){
                        return (LexItem(COMMA, ",", linenum));
                    }else if(letter=='.'){
                        if(isdigit(in.peek())){
                            lexeme+=letter;
                            //in.get(letter);
                            //lexeme+=letter;
                            string s = lexeme;
                            lexeme="";
                            return (LexItem(ERR, s, linenum));
                        }
                    }else if(letter=='-'){
                        return (LexItem(MINUS, "-", linenum));
                    }else if(letter=='+'){
                        return (LexItem(PLUS, "+", linenum));
                    }else if(letter=='/'){
                        return (LexItem(DIV, "/", linenum));
                    }else if(letter==';'){
                        return (LexItem(SEMICOL, ";", linenum));
                    }else if(letter=='('){
                        return (LexItem(LPAREN, "(", linenum));
                    }else if(letter==')'){
                        return (LexItem(RPAREN, ")", linenum));
                    }else if(letter=='*'){
                        return (LexItem(MULT, ")", linenum));
                    }else if(letter=='<'){
                        return (LexItem(LTHAN, "<", linenum));
                    }else if(letter=='>'){
                        return (LexItem(GTHAN, ">", linenum));
                    }else if(letter== '&'){
                        if(in.peek()=='&'){
                            return (LexItem(AND, "&&", linenum));
                        }
                    }else if(letter== '|'){
                        if(in.peek()=='|'){
                            return (LexItem(OR, "||", linenum));
                        }
                    }else if(letter=='!'){
                        return (LexItem(NOT, "!", linenum));
                    }else if(letter=='='){
                        if(in.peek()=='='){
                            in.get(letter);
                            return (LexItem(EQUAL, "==", linenum));
                        }else{
                            return (LexItem(ASSOP, "=", linenum));
                        }
                    }else if (letter=='\"'){
                        //lexeme+=letter;
                        lexstate=INSTRING;
                    }else{
                        string s ="";
                        s=letter;
                        //cout<<"--ispunct"<<endl;
                        return (LexItem(ERR,s,linenum));
                    }
                }
                break;
            case INID:
                //cout<<"**INID"<<endl;
                if(isalnum(letter) or letter == '_' or letter == '@'){
                    lexeme+=letter;
                    //cout<<"=========_"<< lexeme<<"_" <<endl;
                    if(in.peek() == '\n'){
                        in.get(letter);
                        int x=linenum;
                        linenum++;
                        //cout<<"====== LINES BEEN INCREASED - 2"<<endl;

                        string lexemeUppercase="";
                        for(int i = 0; i<lexeme.length();i++){
                            lexemeUppercase+=toupper(lexeme[i]);
                        }
                        auto kIt = kwmap.find(lexemeUppercase);
                        if( kIt != kwmap.end() ){
                            Token tt = kIt->second;
                            //cout << "KEYWORD: " << lexeme << " at Line # " << x<<endl;
                            //string s = lexeme;
                            lexeme="";
                            //cout<<"--kwmap2"<<endl;
                            //cout << "1----------"<<in.peek()<<endl;
                            if(lexemeUppercase=="TRUE" or lexemeUppercase=="FALSE"){
                                return LexItem(BCONST,lexemeUppercase,x);
                            }
                            return LexItem(tt,lexemeUppercase,x);
                        }else{
                            //cout << "IDENT: " << lexeme << " at Line # " << x<<endl;
                            //string s = lexeme;
                            lexeme="";
                            
                            //cout<<"--ident2"<<endl;
                            //cout << "2----------"<<in.peek()<<endl;
                            if(lexemeUppercase=="TRUE" or lexemeUppercase=="FALSE"){
                                return LexItem(BCONST,lexemeUppercase,x);
                            }
                            return LexItem(IDENT,lexemeUppercase,x);
                        }
                    }
                }else{
                    in.putback(letter);
                    lexstate=START;
                    string lexemeUppercase="";
                    for(int i = 0; i<lexeme.length();i++){
                        lexemeUppercase+=toupper(lexeme[i]);
                    }
                    auto kIt = kwmap.find(lexemeUppercase);
                    if( kIt != kwmap.end() ){
                        Token tt = kIt->second;
                        //cout << tt << lexeme << " at Line # " << linenum<<endl;
                        //string s = lexeme;
                        lexeme="";
                        //cout<<"--kwmap"<<endl;
                        //cout << "3----------"<<in.peek()<<endl;
                        if(lexemeUppercase=="TRUE" or lexemeUppercase=="FALSE"){
                            return LexItem(BCONST,lexemeUppercase,linenum);
                        }
                        return LexItem(tt,lexemeUppercase,linenum);
                    }else{
                        //cout << "IDENT: " << lexeme << " at Line # " << linenum<<endl;
                        //string s = lexeme;
                        lexeme="";
                        //cout<<"--ident"<<endl;
                        //cout << "4----------"<<in.peek()<<endl;
                        if(lexemeUppercase=="TRUE" or lexemeUppercase=="FALSE"){
                            return LexItem(BCONST,lexemeUppercase,linenum);
                        }
                        return LexItem(IDENT,lexemeUppercase,linenum);
                    }
                }
                break;
            case INSTRING:
                if(letter!='\"' and letter!='\n'){
                    lexeme+=letter;
                    if (in.peek()=='\n'){
                        string s = "\""+lexeme;
                        lexeme="";
                        //s+=" ";
                        return LexItem(ERR,s,linenum);
                    }
                }else if(letter=='\"'){
                    return LexItem(SCONST,lexeme,linenum);
                }
                break;
            case ININT:
                if(isdigit(letter)){
                    lexeme+=letter;
                    if(in.peek()=='\n'){
                        string s = lexeme;
                        lexeme="";
                        return LexItem(ICONST,s,linenum);
                    }
                }else if(letter=='.' ){
                    if(isdigit(in.peek())){
                        lexeme+=letter;
                        in.get(letter);
                        lexeme+=letter;
                        lexstate=INREAL;
                        break;
                    }else{
                        //in.get(letter);
                        lexeme+=letter;
                        string s = lexeme;
                        
                        return LexItem(ERR,s,linenum);
                    }
                }else{
                    in.putback(letter);
                    string s = lexeme;
                    lexeme="";
                    return LexItem(ICONST,s,linenum);
                }
                break;
            case INREAL:
                if(letter=='.'){
                    //in.putback(letter);
                    lexeme+=letter;
                    string s = lexeme;
                    lexeme="";
                    return LexItem(ERR,s,linenum);
                }else if(isdigit(letter)){
                    lexeme+=letter;
                    if(in.peek()=='\n'){
                        string s = lexeme;
                        lexeme="";
                        return LexItem(RCONST,s,linenum);
                    }
                }else{
                    in.putback(letter);
                    string s = lexeme;
                    lexeme="";
                    return LexItem(RCONST,s,linenum);
                }
                break;
            case INCOMMENT:
                if(letter=='\n'){
                //    cout<<"linecount increase"<<endl;
                    linenum++;
                    //cout<<"====== LINES BEEN INCREASED - 3"<<endl;
                }else if(letter=='*' and in.peek()=='/'){
                    //cout<<"**comment ended"<<endl;
                    in.get(letter);
                    lexstate=START;
                    break;
                }
                else if (in.eof()){
                    string s = lexeme;
                    lexeme="";
                    cout<<"\nMissing a comment end delimiters '*/' at line "<<linenum-1<<endl;

                    return(LexItem(ERR,s,linenum));
                    
                }
                break;
        }
    }
    if (in.eof())
    {
        if(lexstate==INCOMMENT){
            cout<<"\nMissing a comment end delimiters '*/' at line "<<linenum-1<<endl;

        }
        return LexItem(DONE, lexeme, linenum);
    }
    //cout<<"--ends"<<endl;
    return LexItem();
}

