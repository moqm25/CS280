#include "parseInt.h"

map<string, bool> DV;
map<string, Token> ST;
map<string, Value> TR;
queue<Value> *VQ;
/*
namespace Parser {
bool pushed_back = false;
LexItem    pushed_token;

static LexItem GetNextToken(istream& in, int& line) {
if( pushed_back ) {
pushed_back = false;
return pushed_token;
}
return getNextToken(in, line);
}

static void PushBackToken(LexItem & t) {
if( pushed_back ) {
abort();
}
pushed_back = true;
pushed_token = t;
}
}

*/
namespace Parser {
    bool pushed_back = false;
    LexItem pushed_token;

    static LexItem GetNextToken(istream &in, int &line) {
        if (pushed_back) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem &t) {
        if (pushed_back) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}
//static int error_count = 0;
static int error_count = 0;

//int ErrCount(){return error_count;}
int ErrCount() {
    return error_count;
}

void ParseError(int line, string msg) {//void ParseError(int line, string msg){
  ++error_count;//++error_count;
  cout << line << ": " << msg << endl;//cout << line << ": " << msg << endl;
}

bool DT(Token dt, Value &ValueToUse){
    if(dt==INT){//void ParseError(int line, string msg){
        if(ValueToUse.IsReal()){//void ParseError(int line, string msg){
            ValueToUse = Value((int)(ValueToUse.GetReal()));//void ParseError(int line, string msg){
        }//void ParseError(int line, string msg){
        return ValueToUse.IsInt() || ValueToUse.IsReal();//void ParseError(int line, string msg){
    }//void ParseError(int line, string msg){
    else if(dt==BOOL){//++error_count;
        return ValueToUse.IsBool();//++error_count;
    }//++error_count;
    else if(dt==FLOAT){//++error_count;
        if(ValueToUse.IsInt()){//++error_count;
            ValueToUse = Value((float)(ValueToUse.GetInt()));//cout << line << ": " << msg << endl;
        }//cout << line << ": " << msg << endl;
        bool wiuhe = ValueToUse.IsReal() || ValueToUse.IsInt();//cout << line << ": " << msg << endl;
        return wiuhe;//cout << line << ": " << msg << endl;
    }else{//cout << line << ": " << msg << endl;
        return false;//cout << line << ": " << msg << endl;
    }
}

extern bool Prog(istream &in, int &line) {
    /*
     *LexItem t = Parser::GetNextToken(in,line);
     if(t!=PROGRAM){
         ParseError(line, "program statement missing");
         return false;
     }
     */
    LexItem tokToUse;
    
    /*
     t = Parser::GetNextToken(in,line);
     if(t!=IDENT){
         ParseError(line, "program name missing");
         return false;
     }
     */
    tokToUse = Parser::GetNextToken(in, line);
    Token x = tokToUse.GetToken();
    if (x != PROGRAM) {
        ParseError(line, "Error");
        return false;
    }
    /*
     t = Parser::GetNextToken(in,line);
     while(t!=END){
         
         Parser::PushBackToken(t);
         bool ex = StmtList(in, line);
         if(!ex){
             ParseError(line, "Error in the body");
             return false;
         }
         t = Parser::GetNextToken(in,line);
         
     */
    
    tokToUse = Parser::GetNextToken(in, line);
    x = tokToUse.GetToken();
    if (x != IDENT) {
        ParseError(line, "Error");
        return false;
    }
    string y = tokToUse.GetLexeme();
    ST[y] = PROGRAM;
    /*
     if(t==END){
         t = Parser::GetNextToken(in,line);
         if(t!=PROGRAM){
             //Parser::PushBackToken(t);
             continue;
         }else{
             //Parser::PushBackToken(t);
             break;
         }
     }
 }
     */
    
    bool existence;
    existence = StmtList(in, line);
    tokToUse = Parser::GetNextToken(in, line);
    x = tokToUse.GetToken();
    if (x != PROGRAM || !existence) {
        ParseError(line, "Error");
        return false;
    }
    return existence;
    /*
     if(!((t=Parser::GetNextToken(in, line))==DONE)){
         ParseError(line, "end program missing");
         return false;
     }
      
     return true;
     */
}

extern bool StmtList(istream &in, int &line) {
    LexItem tokToUse = Parser::GetNextToken(in, line);
    Token x = tokToUse.GetToken();
    if (x == END) {
        return true;
    }
    /*
     bool ex = true;
     LexItem t=Parser::GetNextToken(in, line);
     Parser::PushBackToken(t);
     ex = Stmt(in,line);
     if(!ex){
         ParseError(line, "syntactic problem");
         return false;
     }
     t=Parser::GetNextToken(in, line);
     */
    
    Parser::PushBackToken(tokToUse);
    
    bool existence;
    existence = Stmt(in, line);
    tokToUse = Parser::GetNextToken(in, line);

    x = tokToUse.GetToken();
    if (x == PROGRAM && !existence) {
        ParseError(line, "Error");
        return false;
    } else {
        Parser::PushBackToken(tokToUse);
    }
    /*
     if(t!=SEMICOL){
         ParseError(line, "Missing semicolon at end of Statement.");
         return false;
     }else{
         return true;
     }
     */
    return existence;
}

extern bool Stmt(istream &in, int &line) {
    LexItem tokToUse;
    tokToUse = Parser::GetNextToken(in, line);
    Token x = tokToUse.GetToken();
    if (tokToUse == END) {
        return true;
    }
    /*
     LexItem t = Parser::GetNextToken(in, line);
     if(t==INT or t == FLOAT or t==BOOL){
         Parser::PushBackToken(t);
         if(!DeclStmt(in,line)){
             ParseError(line, "Incorrect Declaration statement");

             return false;
         }
         return true;
     }
     */
    
    if (tokToUse == PROGRAM) {
        Parser::PushBackToken(tokToUse);
        return false;
    }
    /*
     if(t==PRINT or t==IF or t==IDENT){
         Parser::PushBackToken(t);
         if(!ControlStmt(in,line)){
             ParseError(line, "Incorrect Control statement");
             return false;
         }
         return true;
     }
     */
    bool existence;

    if (x == INT || x == FLOAT || x == BOOL) {
        Parser::PushBackToken(tokToUse);
        existence = DeclStmt(in, line);
        if (!existence) {
            ParseError(line, "Error");
            return false;
        }
    } else if (x == IDENT || x == IF || x == PRINT) {
        Parser::PushBackToken(tokToUse);
        existence = ControlStmt(in, line);
        if (!existence) {
            ParseError(line, "Error");
            return false;
        }
    } else {
        Parser::PushBackToken(tokToUse);
        return true;
    }
    /*
     if(t==SEMICOL){
         return true;
     }
     
     //ParseError(line,"Statement problem");
     return true;
     */
    LexItem SC;
    SC = Parser::GetNextToken(in, line);
    Token s = SC.GetToken();
    if (s != SEMICOL) {
        ParseError(line, "Error");
        return false;
    } else {
        existence = Stmt(in, line);
    }
    
    return existence;
}
//DeclStmt ::= ( INT | FLOAT | BOOL ) VarList============================

extern bool DeclStmt(istream &in, int &line) {
    LexItem thing;
    thing = Parser::GetNextToken(in, line);
    /*
     LexItem t = Parser::GetNextToken(in, line);
     if(t==INT or t == FLOAT or t==BOOL){
         if(!VarList(in, line)){
             ParseError(line, "Incorrect Variable in declaration statement.");
             return false;
         }else{
             return true;
         }
     }
     return false;
     */
    return VarList(in, line, thing);
}

extern bool VarList(istream &in, int &line, LexItem &type) {
    LexItem thingToUse;
    thingToUse = Parser::GetNextToken(in, line);
    
    bool existence;
    
    existence = Var(in, line, thingToUse);
    if (!existence) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem t;
     bool ex = true;
     if(Var(in,line)){
         t=Parser::GetNextToken(in, line);
         if (defVar.find(t.GetLexeme()) == defVar.end()) {
             //not found
             defVar.insert(std::pair<string, bool>(t.GetLexeme(),true));
         }else{
             ParseError(line, "Redeclarations");
             return false;
             
         }
     }
     */
    string y =thingToUse.GetLexeme();
    ST[y] = type.GetToken();
    
    LexItem t;
    t = Parser::GetNextToken(in, line);
    Token z = t.GetToken();
    
    /*
     t=Parser::GetNextToken(in, line);
     if(t==COMMA and t!=SEMICOL){
         return VarList(in,line);
     }
     if(t==IDENT){
         Parser::PushBackToken(t);
         return true;
     }
     */
    if (z == COMMA) {
        existence = VarList(in, line, type);
    } else if (z == IDENT) {
        ParseError(line, "Error");
        return false;
    } else {
        Parser::PushBackToken(t);
        return true;
    }
    return existence;
    /*
     if(t==SEMICOL){
         Parser::PushBackToken(t);
         return true;
     }
     return ex;
     */
}

extern bool Var(istream &in, int &line, LexItem &idtok) {
    bool existence;
    if (idtok != IDENT) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem t = Parser::GetNextToken(in, line);
     if(t==IDENT){
         Parser::PushBackToken(t);
         return true;
     }
     */
    
    existence = DV.insert({idtok.GetLexeme(), true}).second;
    if (existence == false) {
        ParseError(line, "Error");
        return false;
    }
    
    return existence;
    /*
     else{
         Parser::PushBackToken(t);
         return false;
     }
     return true;
     */
}

extern bool ControlStmt(istream &in, int &line) {
    bool existence;
    LexItem thingToUse;
    thingToUse = Parser::GetNextToken(in, line);
    Token x = thingToUse.GetToken();
    /*
     bool status;
     LexItem t = Parser::GetNextToken(in, line);
     switch( t.GetToken() ) {
         case PRINT:
             if(!PrintStmt(in, line)){
                 return false;
             }
             return true;
     */
    if(x==PRINT){
        existence = PrintStmt(in, line);
    /*
     case IF:
         Parser::PushBackToken(t);
         if(!IfStmt(in, line)){
             //ParseError(line, "Incorrect control statement");
             return false;
         }
         return true;
         // break;
     */
    }else if(x==IF){
        existence = IfStmt(in, line);
    /*
     case IDENT:
         //return true;
         Parser::PushBackToken(t);
         if(!AssignStmt(in, line)){
             //ParseError(line, "Assignment problem");
             return false;
         }
         return true;
     */
    }else if(x==IDENT){
        Parser::PushBackToken(thingToUse);
        existence = AssignStmt(in, line);
        /*
         default:
             Parser::PushBackToken(t);
             return false;
         */
    }else{
        Parser::PushBackToken(thingToUse);
        return false;
    }//    return status;

    return existence;
}

extern bool AssignStmt(istream &in, int &line) {
    LexItem thingToUse;
    thingToUse = Parser::GetNextToken(in, line);
    string y = thingToUse.GetLexeme();
    if (DV.count(y) != 1) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem t = Parser::GetNextToken(in, line);
     bool ex = true;
     Parser::PushBackToken(t);
     if(Var(in,line)){
         t=Parser::GetNextToken(in, line);
         if (defVar.find(t.GetLexeme()) == defVar.end()) {
             Parser::PushBackToken(t);
             ParseError(line, "Undeclared Var");
             ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
             return false;
         }
     }
     */
    LexItem thingToUse2;
    thingToUse2 = Parser::GetNextToken(in, line);
    Token tt = thingToUse2.GetToken();
    if (tt != ASSOP) {
        ParseError(line, "Error");
        return false;
    }
    /*
     t = Parser::GetNextToken(in, line);
     if(t!=ASSOP){
         ParseError(line, "Missing Assignment Operator");
         return false;
     }
     */
    Value ValueToUse;
    bool existence;
    existence = Expr(in, line, ValueToUse);
    if(existence){
        Token dt = ST[y];
        if(ValueToUse.IsErr()){
            ParseError(line, "Error");
            return false;
        }
        /*
         ex=Expr(in, line);
         if(!ex){
             ParseError(line, "Expression missing u fool");
             return false;
         }
         return true;
         */
        if(DT(dt, ValueToUse)){
            TR[y] = ValueToUse;
        }else{
            ParseError(line, "Error");
            return false;
        }
    }
    return existence;
}

extern bool IfStmt(istream &in, int &line) {
    LexItem TokToUse;
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    x = TokToUse.GetToken();
    /*
     LexItem t = Parser::GetNextToken(in, line);
     if( t != IF ) {
         ParseError(line, "IF start statement missing");
         return false;
     }else{
     }
     */
    if (x != LPAREN) {
        ParseError(line, "Error");
        return false;
    }
    /*
     t = Parser::GetNextToken(in, line);
     if( t != LPAREN ) {
         ParseError(line, "LPAREN MISSING");
         return false;
     }else{
     }
     */
    
    Value ValueToUse;
    if (!Expr(in, line, ValueToUse)) {
        ParseError(line, "Error");
        return false;
    }
    /*
     bool ex = Expr(in, line);
     if( !ex ) {
         ParseError(line, "Missing expression in IF");
         return false;
     }else{
     }
     */
    
    TokToUse = Parser::GetNextToken(in, line);
    x = TokToUse.GetToken();
    if (x != RPAREN) {
        ParseError(line, "Error");
        return false;
    }
    /*
     t = Parser::GetNextToken(in, line);
     if(t != RPAREN ) {
         ParseError(line, "RPAREN MISSING");
         return false;
     }else{
     }
     */
    
    TokToUse = Parser::GetNextToken(in, line);
    x = TokToUse.GetToken();

    if (x != THEN) {
        return false;
    }
    /*
     t = Parser::GetNextToken(in, line);
     if(t != THEN ) {
         ParseError(line, "THEN MISSING");
         return false;
     }else{
     }
     */
    
    if(ValueToUse.IsBool()){
        if(ValueToUse.GetBool()){
            if (!StmtList(in, line)) {
                ParseError(line, "Error");
                return false;
            }
            /*ex=StmtList(in, line);
             if(!ex){
                 ParseError(line, "IF Stmtlist statement problem");
                 return false;
             }else{*/
        }else{
            x=TokToUse.GetToken();
            while(x != ELSE && x != END){
                TokToUse = Parser::GetNextToken(in, line);
                x=TokToUse.GetToken();
            }
            Parser::PushBackToken(TokToUse);
        }
        /*
         t = Parser::GetNextToken(in, line);
         while(t!=ELSE and t!=END){
             Parser::PushBackToken(t);
             ex=StmtList(in, line);
             if(!ex){
                 ParseError(line, "IF Stmtlist statement problem");
                 return false;
             }else{
             }
             t = Parser::GetNextToken(in, line);
         */
    }else{
        ParseError(line, "Error");
        return false;
        /*
         }
         Parser::PushBackToken(t);
     }
         */
    }
    
    TokToUse = Parser::GetNextToken(in, line);
    x=TokToUse.GetToken();
    if (x == ELSE) {
        if(ValueToUse.GetBool()){
            while(x != END){
                /*t = Parser::GetNextToken(in, line);
                 if(t==ELSE){
                     t = Parser::GetNextToken(in, line);
                     while(t!=END){
                         Parser::PushBackToken(t);
                         ex=StmtList(in, line);
                         if(!ex){
                             ParseError(line, "IF ELSE Stmtlist statement problem");
                             return false;
                         }else{
                         }
                         t = Parser::GetNextToken(in, line);
                     }
                     //Parser::PushBackToken(t);*/
                TokToUse = Parser::GetNextToken(in, line);
                x=TokToUse.GetToken();
            }
            /*
             }
             if(t==END){
                 t = Parser::GetNextToken(in, line);
                 if(t==IF){
                     t = Parser::GetNextToken(in, line);
                     if(t==SEMICOL){
                         Parser::PushBackToken(t);
                         return true;
                     }
                 }
             }
             */
        }else{
            if (!StmtList(in, line)) {
                ParseError(line, "Error");
                return false;
            }
        }
    } else {
        Parser::PushBackToken(TokToUse);
    }
    
    TokToUse = Parser::GetNextToken(in, line);
    x=TokToUse.GetToken();
    /*ParseError(line, "Missing ending if stuff");
     return false;
*/
    if(x == END){
        TokToUse = Parser::GetNextToken(in, line);
        x=TokToUse.GetToken();
    }
    /*
     ParseError(line, "Missing ending if stuff");
     return false;

     */
    if (x != IF) {
        ParseError(line, "Error");
        /*
         ParseError(line, "Missing ending if stuff");
         return false;

         */
        return false;
    }
    return true;
}


bool PrintStmt(istream &in, int &line) {
    LexItem TokToUse;
    
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    /*
     bool PrintStmt(istream& in, int& line) {
         LexItem t;
         t = Parser::GetNextToken(in, line);
         if( t != LPAREN ) {
             ParseError(line, "Missing Left Parenthesis");
             return false;
         }else{
         }
     */
    x = TokToUse.GetToken();
    if (x != LPAREN) {

        ParseError(line, "Error");
        return false;
    }
    /*
     bool ex = ExprList(in, line);
     if( !ex ) {
         ParseError(line, "Missing expression after PRINT");
         return false;
     }
     t = Parser::GetNextToken(in, line);
     */
    
    VQ = new queue<Value>;

    if (!ExprList(in, line)) {
        ParseError(line, "Error");
        while ((*VQ).empty() == false) {
            VQ->pop();
            /*
             if(t != RPAREN ) {
                 ParseError(line, "Missing Right Parenthesis");
                 return false;
             }else{
             */
        }
        delete VQ;
        
        return false;
    }
    /*
     t = Parser::GetNextToken(in, line);
     if(t==SEMICOL){
         Parser::PushBackToken(t);
         return true;
     }
     */
    while (!(*VQ).empty()) {
        Value nv = (*VQ).front();
        
        if(nv.IsErr()){
            ParseError(line, "Error");
            return false;
        }
        cout << nv;
        /*t = Parser::GetNextToken(in, line);
         if(t==SEMICOL){
             Parser::PushBackToken(t);
             return true;
         }*/
        
        VQ->pop();
    }
    
    cout << "\n";
    
    TokToUse = Parser::GetNextToken(in, line);
    x = TokToUse.GetToken();
    if (x != RPAREN) {
        /*t = Parser::GetNextToken(in, line);
         if(t==SEMICOL){
             Parser::PushBackToken(t);
             return true;
         }*/
        ParseError(line, "Error");
        return false;
    }
    
    return true;
}


extern bool ExprList(istream &in, int &line) {
    bool existence;
    existence = false;
    
    Value ValueToUse;
    existence = Expr(in, line, ValueToUse);
    /*
     bool status = false;
     status = LogANDExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }
     */
    if (!existence) {
        ParseError(line, "Error");
        return false;
    }
    /*
     bool status = false;
     status = LogANDExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }
     */
    
    VQ -> push(ValueToUse);
    
    LexItem TokToUse;
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    if (x == COMMA) {
        existence = ExprList(in, line);
    } else if (x == ERR) {
        /*
         LexItem tok = Parser::GetNextToken(in, line);
         if (tok == OR) {
             status = Expr(in, line);
         }else if(tok.GetToken() == ERR){
             ParseError(line, "Unrecognized Input Pattern");
             return false;
         */
        ParseError(line, "Error");
        string y = TokToUse.GetLexeme();
        cout << "(" << y << ")" << endl;
        return false;
    } else {
        /*
         }else{
             Parser::PushBackToken(tok);
             return true;
         }
         return status;
         */
        Parser::PushBackToken(TokToUse);
        return true;
    }
    return existence;
}

extern bool Expr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    Value val1, val2;
    bool t1 = LogANDExpr(in, line, val1);
    if (!t1) {
        return false;
    }
    /*bool status = false;
     status = LogANDExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }*/
    
    retVal = val1;
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == OR) {
         status = Expr(in, line);
     }else if(tok.GetToken() == ERR){
         ParseError(line, "Unrecognized Input Pattern");
         return false;
     }else{
     */
    
    while (x == OR) {
        t1 = LogANDExpr(in, line, val2);
        if (!t1) {
            ParseError(line, "Error");
            /*
             if (tok == OR) {
                 status = Expr(in, line);
             }else if(tok.GetToken() == ERR){
                 ParseError(line, "Unrecognized Input Pattern");
                 return false;
             }else{
             */
            return false;
        }
        Value t = retVal or val2;
        
        retVal = t;
        
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        /*
         Parser::PushBackToken(tok);
         return true;
     }
     return status;
         */
        
        TokToUse = Parser::GetNextToken(in, line);
        x = TokToUse.GetToken();
        
        if (x == ERR) {
            ParseError(line, "Error");
            return false;
        }
    }
    
    Parser::PushBackToken(TokToUse);
    
    return true;
}

/*
 bool LogORExpr(istream& in, int& line){
     bool status = false;
     status = LogANDExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == OR) {
         status = LogORExpr(in, line);
     }else if(tok.GetToken() == ERR){
         ParseError(line, "Unrecognized Input Pattern");
         return false;
     }else{
         Parser::PushBackToken(tok);
         return true;
     }
     return status;}
 */

bool LogANDExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    
    Value val1, val2;
    
    /*
     bool LogANDExpr(istream& in, int& line){
         bool status = false;
         status = EqualExpr(in, line);
         if(!status){
             //ParseError(line, "Missing Expression");
             return false;
         }
     */
    
    if (!EqualExpr(in, line, val1)) {
        return false;
    }
    
    retVal = val1;
    
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == AND) {
         status = LogANDExpr(in, line);
     }else if(tok.GetToken() == ERR){
      
     */
    while (x == AND) {
        
        if (!EqualExpr(in, line, val2)) {
            ParseError(line, "Error");
            return false;
        }
        Value thingy =retVal && val2;
        retVal = thingy;
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        /*
         ParseError(line, "Unrecognized Input Pattern");
         return false;
     }else{
         */
        TokToUse = Parser::GetNextToken(in, line);
        x = TokToUse.GetToken();
        if (x == ERR) {
            ParseError(line, "Error");
            return false;
        }
    }
    /*
     Parser::PushBackToken(tok);
     return true;
 }
 return status;}
     */
    Parser::PushBackToken(TokToUse);
    return true;
}

bool EqualExpr(istream &in, int &line, Value &retVal, bool ef) {
    /*
     bool status = false;
     status = RelExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == EQUAL) {
     */
    if(!RelExpr(in, line, retVal)){
        ParseError(line, "Error");
        return false;
    }
    /*
     status = RelExpr(in, line);
     if(status){
         tok=Parser::GetNextToken(in,line);
         if(tok==EQUAL){
             ParseError(line, "Illegal Equality Expression");
             return false;
         }
         Parser::PushBackToken(tok);
     }
     return true;
     */
    
    LexItem TokToUse;
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    x = TokToUse.GetToken();
    if (x == EQUAL && ef==true) {
        ParseError(line, "Error");
        return false;
    }
    /*
     }else{
         Parser::PushBackToken(tok);
         //
         return true;
     }
     return status;
     
     */
    Parser::PushBackToken(TokToUse);
    return true;
}

extern bool EqualExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    Value val1, val2;
    
    if (!RelExpr(in, line, val1)) {
        return false;
    }
    /*
     bool EqualExpr(istream& in, int& line){
         bool status = false;
         status = RelExpr(in, line);
         if(!status){
             //ParseError(line, "Missing Expression");
             return false;
         }
     */
    
    retVal = val1;
    
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    x = TokToUse.GetToken();
    
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == EQUAL) {
         status = RelExpr(in, line);
         if(status){
             tok=Parser::GetNextToken(in,line);
             if(tok==EQUAL){
                 ParseError(line, "Illegal Equality Expression");
                 return false;
             }
             Parser::PushBackToken(tok);
         }
         return true;
     */
    
    if (x == EQUAL) {
        
        if (!EqualExpr(in, line, val2, true)) {
            ParseError(line, "Error");
            return false;
        }
        
        Value thingy =retVal == val2;
        retVal =thingy;
        
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        /*
         }else{
             Parser::PushBackToken(tok);
             //
             return true;
         }
         return status;
         */
        TokToUse = Parser::GetNextToken(in, line);
        x = TokToUse.GetToken();
        if (x == ERR) {
            ParseError(line, "Error");
            return false;
        }
    }
    Parser::PushBackToken(TokToUse);
    return true;
}

bool RelExpr(istream &in, int &line, Value &retVal, bool ef) {
    if(!AddExpr(in, line, retVal)){
        ParseError(line, "Error");
        return false;
    }
    /*
     bool status = false;
     status = AddExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Expression");
         return false;
     }
     */
    
    LexItem TokToUse;
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == LTHAN or tok==GTHAN) {
         status = AddExpr(in, line);
         if(status){
             tok=Parser::GetNextToken(in,line);
             if(tok == LTHAN or tok==GTHAN){
                 ParseError(line, "Illegal Relational Expression");
                 return false;
             }
             Parser::PushBackToken(tok);
         }
         return true;
     
     }
     */
    bool tf = (x==GTHAN or x == LTHAN);
    if (tf and ef==true) {
        ParseError(line, "Error");
        return false;
    }
    /*
     else{
         Parser::PushBackToken(tok);

         return true;
     }
     return status;
     */
    Parser::PushBackToken(TokToUse);
    return true;
}

extern bool RelExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    Value val1, val2;
    
    if (!AddExpr(in, line, val1)) {
        return false;
    }
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == LTHAN or tok==GTHAN) {
         status = AddExpr(in, line);
         if(status){
             tok=Parser::GetNextToken(in,line);
             if(tok == LTHAN or tok==GTHAN){
                 ParseError(line, "Illegal Relational Expression");
                 return false;
             }
             Parser::PushBackToken(tok);
         }
         return true;
     
     }else{
     */
    retVal = val1;
    
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    x = TokToUse.GetToken();
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == LTHAN or tok==GTHAN) {
         status = AddExpr(in, line);
         if(status){
             tok=Parser::GetNextToken(in,line);
             if(tok == LTHAN or tok==GTHAN){
                 ParseError(line, "Illegal Relational Expression");
                 return false;
             }
             Parser::PushBackToken(tok);
         }
         return true;
     
     }else{
     */
    
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    
    bool tf =(x == GTHAN || x == LTHAN);
    
    if (tf) {

        if (!RelExpr(in, line, val2, true)) {
            ParseError(line, "Error");
            return false;
        }
        if(x==GTHAN){
            retVal =retVal > val2;
            /*
             Parser::PushBackToken(tok);

             return true;
         }
         return status;
             */
        }else{
            retVal = retVal < val2;
        }
        
        
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        /*
         Parser::PushBackToken(tok);

         return true;
     }
     return status;
         */
        
        TokToUse = Parser::GetNextToken(in, line);
        
        x=TokToUse.GetToken();
        
        if (x == ERR) {
            ParseError(line, "Error");
            return false;
        }
    }
    Parser::PushBackToken(TokToUse);
    return true;
}

extern bool AddExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    /*
     bool AddExpr(istream& in, int& line){
         bool status = false;
         status = MultExpr(in, line);
         if(!status){
             //ParseError(line, "Missing MultExpr Expression");
             return false;
         }
     */
    Value val1, val2;
    
    if (!MultExpr(in, line, val1)) {
        return false;
    }
    
    retVal = val1;
    TokToUse = Parser::GetNextToken(in, line);

    Token x = TokToUse.GetToken();
    
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    /*
     LexItem tok = Parser::GetNextToken(in, line);
     if (tok == PLUS || tok==MINUS) {
         status = AddExpr(in, line);
     }
     else if(tok.GetToken() == ERR){
         ParseError(line, "Unrecognized Input Pattern");
         return false;
     }else{
     */
    bool fu = (x == PLUS || x == MINUS);
    while (fu) {
        
        if (!MultExpr(in, line, val2)) {
            ParseError(line, "Error");
            return false;
        }
        /*
         LexItem tok = Parser::GetNextToken(in, line);
         if (tok == PLUS || tok==MINUS) {
             status = AddExpr(in, line);
         }
         else if(tok.GetToken() == ERR){
             ParseError(line, "Unrecognized Input Pattern");
             return false;
         }else{
         */
        
        if(x == PLUS){
            retVal = retVal+val2;
        }else{
            retVal=retVal-val2;
        }
        
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        /*
         Parser::PushBackToken(tok);
         
         return true;
     }
     return status;
         */
        
        TokToUse = Parser::GetNextToken(in, line);
        x = TokToUse.GetToken();
        if (x == ERR) {
            ParseError(line, "Error");
            return false;
        }
        fu = (x == PLUS || x == MINUS);
    }
    Parser::PushBackToken(TokToUse);
    return true;
    /*
     Parser::PushBackToken(tok);
     
     return true;
 }
 return status;
     */
}

extern bool MultExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    Value val1, val2;
    if (!UnaryExpr(in, line, val1)) {
        return false;
    }
    /*
     bool status = false;
     status = UnaryExpr(in, line);
     if(!status){
         //ParseError(line, "Missing Unary Expression");
         return false;
     }
     */
    
    retVal = val1;
    
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    
    if (x == ERR) {
        ParseError(line, "Error");
        return false;
    }
    bool fu =(x==MULT or x==DIV);
    while (fu) {
        if (!UnaryExpr(in, line, val2)) {
            ParseError(line, "Error");
            return false;
        }
        /*
         LexItem tok = Parser::GetNextToken(in, line);
         //tok = Parser::GetNextToken(in, line);

         if (tok == MULT || tok==DIV) {
             status = MultExpr(in, line);
         }
         else if(tok.GetToken() == ERR){
             ParseError(line, "Unrecognized Input Pattern");
             return false;
         }else{
         */
        bool tf= x == DIV && (val2.GetInt() == 0 || val2.GetReal() == 0);
        if(tf){
            ParseError(line, "Error");
            return false;
        }
        if(x == MULT){
            retVal=retVal*val2;
        }else{
            retVal=retVal/val2;
        }
        /*
         LexItem tok = Parser::GetNextToken(in, line);
         //tok = Parser::GetNextToken(in, line);

         if (tok == MULT || tok==DIV) {
             status = MultExpr(in, line);
         }
         else if(tok.GetToken() == ERR){
             ParseError(line, "Unrecognized Input Pattern");
             return false;
         }else{
         */
        
        if (retVal.IsErr()) {
            ParseError(line, "Error");
            return false;
        }
        
        TokToUse = Parser::GetNextToken(in, line);
        x=TokToUse.GetToken();
        if (x == ERR) {
            ParseError(line, "Error");
            /*
             Parser::PushBackToken(tok);
             

             return true;
         }
         return status;
             */
            return false;
        }
        fu =(x==MULT or x==DIV);
      
    }
    Parser::PushBackToken(TokToUse);
    /*
     Parser::PushBackToken(tok);
     

     return true;
 }
 return status;
     */
    return true;
}

extern bool UnaryExpr(istream &in, int &line, Value &retVal) {
    LexItem TokToUse;
    int existence = 0;
    /*
     bool UnaryExpr(istream& in, int& line){
         bool status = false;
         LexItem tok = Parser::GetNextToken(in, line);
     */
    TokToUse = Parser::GetNextToken(in, line);
    Token x = TokToUse.GetToken();
    if(x == MINUS){
        existence = 1;
        /*
         if(tok == MINUS || tok == PLUS ){
             status = PrimaryExpr(in, line, 1);
             return status;
         }
         */
        
    }else if (x==PLUS){
        existence = 2;
        /*
         if(tok == NOT){
             status = PrimaryExpr(in, line, 2);
             return status;

         }
         */
    }else if (x==NOT){
        existence = 3;
        
    }else{
        Parser::PushBackToken(TokToUse);
        
    }
    /*
     Parser::PushBackToken(tok);
     status = PrimaryExpr(in, line, 0);
     if(status){

         return true;
     }
     
     return status;
     */
    
    bool thingy = PrimaryExpr(in, line, existence, retVal);
    
    return thingy;
}

extern bool PrimaryExpr(istream &in, int &line, int sign, Value &retVal) {
    LexItem TokToUse;
    TokToUse = Parser::GetNextToken(in, line);
    Token x;
    x = TokToUse.GetToken();
    if(x==BCONST){
        /*
         LexItem tok = Parser::GetNextToken(in, line);
         if(sign==1){
             if((tok==ICONST or tok==RCONST)){
                 //Parser::PushBackToken(tok);
                 return true;
             }else{
                 ParseError(line, "invalid operator w/type");
                 return false;
             }
          }
         */
        string t = TokToUse.GetLexeme();
        if(t=="TRUE"){
            retVal = Value(true);
        }else{
            retVal=Value(false);
        }
    }else if (x==SCONST){
        /*
         if(sign==2){
             if((tok==BCONST)){
                 //Parser::PushBackToken(tok);
                 return true;
             }else{
                 ParseError(line, "invalid operator w/type");
                 return false;
             }
         }
         */
        string t = TokToUse.GetLexeme();
        retVal = Value(t);

    }else if (x==ICONST){
        /*
         if(sign==0){
             if(tok==IDENT){
                 if (!(defVar.find(tok.GetLexeme())->second)){
                     ParseError(line, "Using Undefined Variable");
                     return false;
                 }
                 //Parser::PushBackToken(tok);
                 return true;
             }
             if(tok==RCONST or tok==SCONST or tok==BCONST or tok==ICONST){
                 //Parser::PushBackToken(tok);
                 return true;
                 
             }
         }
         */
        string t = TokToUse.GetLexeme();
        retVal = Value(stoi(t));

    }else if (x==RCONST){
        string t = TokToUse.GetLexeme();
        retVal = Value(stof(t));
/*
 if(tok==LPAREN){
     tok=Parser::GetNextToken(in, line);
     Parser::PushBackToken(tok);
     bool ex = Expr(in, line);
     if(!ex){
         ParseError(line, "No expression");
         return false;
     }
     tok=Parser::GetNextToken(in, line);
     if(tok==RPAREN){
         return true;
     }else{
         line++;
         ParseError(line, "Missing RPAREN");
         return false;
     }
 }else if (tok==ERR){
 */
    }else if (x==IDENT){
        string t = TokToUse.GetLexeme();
        if(ST[t] == PROGRAM){
            ParseError(line, "Error");
            return false;
        }
        retVal = Value(TR[t]);
    }
    /*
     ParseError(line, "Input Pattern Unrecognizeable");
     return false;
 }else{
     ParseError(line, "Missing opperand");
     return false;
 }
 return false;
     */
    
    if (x == LPAREN) {
        Value val1;
        if (!Expr(in, line, val1)) {
            ParseError(line, "Error");
            return false;
        }
        TokToUse = Parser::GetNextToken(in, line);
        x = TokToUse.GetToken();
        if (x != RPAREN) {
            ParseError(line, "Error");
            /*
             ParseError(line, "Input Pattern Unrecognizeable");
             return false;
         }else{
             ParseError(line, "Missing opperand");
             return false;
         }
         return false;
             */
            return false;
        }
        retVal = val1;
    }
    if(sign == 1){
        bool one =retVal.IsInt();
        /*
         f(tok==LPAREN){
             tok=Parser::GetNextToken(in, line);
             Parser::PushBackToken(tok);
             bool ex = Expr(in, line);
             if(!ex){
                 ParseError(line, "No expression");
                 return false;
             }
             tok=Parser::GetNextToken(in, line);
             if(tok==RPAREN){
                 return true;
             }else{
                 line++;
                 ParseError(line, "Missing RPAREN");
                 return false;
         */
        bool two =retVal.IsReal();
        if(one){
            retVal = Value(-retVal.GetInt());
            return true;
        }else if(two){
            retVal = Value(-retVal.GetReal());
            return true;
            /*
             if(tok==IDENT){
                 if (!(defVar.find(tok.GetLexeme())->second)){
                     ParseError(line, "Using Undefined Variable");
                     return false;
                 }
                 //Parser::PushBackToken(tok);
                 return true;
             }
             if(tok==RCONST or tok==SCONST or tok==BCONST or tok==ICONST){
                 //Parser::PushBackToken(tok);
                 return true;
                 
             }
             */
        }else{
            ParseError(line, "Error");
            return false;
        }
        
    }else if(sign == 2){
        bool tg = (retVal.IsInt() or retVal.IsReal());
        if(!tg){
            ParseError(line, "Error");
            return false;
        }
        return true;
        /*
         if(sign==1){
             if((tok==ICONST or tok==RCONST)){
                 //Parser::PushBackToken(tok);
                 return true;
             }else{
                 ParseError(line, "invalid operator w/type");
                 return false;
             }
          }
         */
    }else if(sign == 3){
        bool tg = retVal.IsBool();
        if(tg){
            retVal = Value(!retVal);
            return true;
        }
        return false;
    }

    return true;
}

