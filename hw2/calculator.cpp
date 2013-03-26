#include "calculator.h"
#include "calc_exception.h"
#include <sstream>

std::ostream& operator<<(std::ostream& output, const Calculator::symbol_t& t) {
    std::stringstream ss;
    ss << t.val;
    std::string s;
    ss >> s;
    output << "(" << t.name << ", " << (t.writen?s:"UNINITIALIZED") << ")";
    return output;
}
std::ostream& operator<<(std::ostream& output, const std::vector<Calculator::symbol_t>& vec) {
    output << "Symbol Table {";
    for(Calculator::symbol_t t : vec){
        output << t;
    }
    output << "}";
    return output;
}

Calculator::Calculator(Scanner& source) : symbol_table(), scan_stream(source)
{
    //ctor
}

bool Calculator::run(std::ostream& output, std::ostream& err)
{
    std::cerr << "---- ---- ---- Starting Line " << scan_stream.line() << " ---- ---- ----" << std::endl;
    depth = 0;
    int save_depth = depth;
    try{
        Token t = line();
        if(t.type() == Token::END){
            output<<"Good bye!"<<std::endl;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << symbol_table << std::endl;
            return false;
        }
        if(t.type() == Token::EXPR){
            Fraction res = t.value().f;

            if(res.is_integer()){
                output<<(int)res<<std::endl;
            } else {
                output<<res<<std::endl;
            }
        }
    } catch (calc_exception& e) {
        depth = save_depth;
        err << e << std::endl;
    }
    Token clr;
    while((clr=scan_stream.getNextToken()).type()!=Token::EOL){
            for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "Destroying: " << clr << std::endl;
    }
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << symbol_table << std::endl;
    return true;
}


Token Calculator::line()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "line{" << std::endl;
    depth++;
    Token t;
    t = scan_stream.getNextToken();
    if(t.type() == Token::END){
        return t;
    }
    scan_stream.unget(t);
    t = expr();
    if(t.valid()){
        Token next = scan_stream.getNextToken();
        if(next.type() == Token::EOL || (next.type() == Token::CHAR && next.value().s == '#')){
            scan_stream.unget(next);
            depth--;
            for(int i = 0; i < depth; ++i) std::cerr << "\t";
            std::cerr << "}" << std::endl;
            return t;
        }
        scan_stream.unget(next);
        throw calc_exception("Additional input after expression", scan_stream.col(), scan_stream.line());
    }
    scan_stream.unget(t);
    throw calc_exception("Bad expression", scan_stream.col(), scan_stream.line());
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::expr()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "expr{" << std::endl;
    depth++;
    Token res(Token::EXPR, 0, 0);
    Token t = scan_stream.getNextToken();
    if(t.type() != Token::EXPR){
        scan_stream.unget(t);
        t = var();
    }
    if(t.valid() && t.type() == Token::LVAR){
        Token a = scan_stream.getNextToken();
        if(!a.valid()||a.type()!= Token::ASSIGN){
            scan_stream.unget(a);
            throw calc_exception("Declaring new variables requires ASSIGN operator '='", scan_stream.col(), scan_stream.line());
        }
        Token e = expr();
        if(!e.valid()){
            throw calc_exception("Declaring new variables requires value", scan_stream.col(), scan_stream.line());
        }
        for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "Setting value of " << symbol_table[(int)t.value().f].name << " to " << e.value().f << std::endl;
        symbol_table[(int)t.value().f].val = e.value().f;
        symbol_table[(int)t.value().f].writen = true;
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return e;
    }
    scan_stream.unget(t);
    t = term();
    if(t.valid()){
        Token a = addop();
        res = t.value().f;
        res.len(t.len());
        while(a.valid()){
            t = term();
            if(!t.valid()){
                throw calc_exception("Expecting TERM", scan_stream.col(), scan_stream.line());
            }
            switch(a.value().s){
            case '+':
                res = res.value().f + t.value().f;
                break;
            case '-':
                res = res.value().f - t.value().f;
                break;
            default:
                throw calc_exception("Invalid ADDOP type", scan_stream.col(), scan_stream.line());
            }
            res.len(t.len()+a.len());
            a = addop();
        }
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return res;
    }
    throw calc_exception("Expecting TERM or LVAR", scan_stream.col(), scan_stream.line());
}
Token Calculator::term()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "term{" << std::endl;
    depth++;
    Token res(Token::TERM, 0, 0);
    Token f = scan_stream.getNextToken();
    if(f.type() != Token::TERM){
        scan_stream.unget(f);
        f = factor();
    }
    if(f.valid()){
        Token m = mulop();
        res = f.value().f;
        res.len(f.len());
        while(m.valid()){
            f = factor();
            if(!f.valid()){
                throw calc_exception("Expecting FACTOR", scan_stream.col(), scan_stream.line());
            }
            switch(m.value().s){
            case '*':
                res = res.value().f * f.value().f;
                break;
            case '/':
                res = res.value().f / f.value().f;
                break;
            default:
                throw calc_exception("Invalid MULTOP type", scan_stream.col(), scan_stream.line());
            }
            res.len(f.len()+m.len());
            m = mulop();
        }
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return res;
    }
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::factor()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "factor{" << std::endl;
    depth++;
    Token res(Token::FACTOR, 0, 0);
    Token num = number();
    if(num.valid()){
        res.len(num.len());
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return res = num.value().f;
    }
    Token par = scan_stream.getNextToken();
    if(par.type()==Token::LPAR){
        Token exp;
        try{
             exp = expr();
        } catch (calc_exception& e) {
            throw calc_exception("Expecting EXPRESSION", scan_stream.col(), scan_stream.line());
        }
        Token par2 = scan_stream.getNextToken();
        if(par2.type()==Token::RPAR){
            res.len(par.len()+exp.len()+par2.len());
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
            return res = exp.value().f;
        }
        scan_stream.unget(par2);
        throw calc_exception("Expecting ')'", scan_stream.col(), scan_stream.line());
    }
    scan_stream.unget(par);
    throw calc_exception("No Valid FACTOR", scan_stream.col(), scan_stream.line());
}
Token Calculator::addop()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "addop{" << std::endl;
    depth++;
    Token a = scan_stream.getNextToken();
    if(a.type() == Token::ADDOP){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return a;
    }
    scan_stream.unget(a);
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::mulop()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "mulop{" << std::endl;
    depth++;
    Token m = scan_stream.getNextToken();
    if(m.type() == Token::MULTOP){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return m;
    }
    scan_stream.unget(m);
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::number()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "number{" << std::endl;
    depth++;
    Token n = scan_stream.getNextToken();
    if(n.type() == Token::NUMBER){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return n;
    }
    scan_stream.unget(n);
    n = fraction();
    if(n.valid()){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return n;
    }
    n = var();
    if(n.valid() && n.type() == Token::RVAR){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return n;
    }
    scan_stream.unget(n);
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::fraction()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "fraction{" << std::endl;
    depth++;
    Token f = scan_stream.getNextToken();
    int col;
    if(f.type() == Token::CHAR && f.value().s == 'F'){
        Token par = scan_stream.getNextToken();
        if(par.type() == Token::LPAR){
            Token n1;
            try{
                n1 = factor();
            } catch (calc_exception& e) {
                throw calc_exception("Fraction format requires FACTOR", scan_stream.col(), scan_stream.line());
            }
            Token div = scan_stream.getNextToken();
            if(div.type() == Token::MULTOP && div.value().s == '/'){
                Token n2;
                try{
                    n2 = factor();
                } catch (calc_exception& e) {
                    throw calc_exception("Fraction format requires FACTOR", scan_stream.col(), scan_stream.line());
                }
                    Token par2 = scan_stream.getNextToken();
                    if(par2.type() == Token::RPAR){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
                        return Token(Token::NUMBER, n1.value().f/n2.value().f, f.len()+par.len()+n1.len()+div.len()+n2.len()+par2.len());
                    }
                    scan_stream.unget(par2);
                    col = scan_stream.col();
                    scan_stream.unget(n2);
                    throw calc_exception("Fraction format requires ')'", col, scan_stream.line());
            }
            scan_stream.unget(div);
            col = scan_stream.col();
            scan_stream.unget(n1);
            throw calc_exception("Fraction format requires '/'", col, scan_stream.line());
        }
        col = scan_stream.col();
        scan_stream.unget(par);
        throw calc_exception("Fraction format requires '('", col, scan_stream.line());
    }
    scan_stream.unget(f);
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token();
}
Token Calculator::var()
{
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "var{" << std::endl;
    depth++;
    Token m = scan_stream.getNextToken();
    if(m.type() == Token::LVAR || m.type() == Token::RVAR){
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return m;
    }
    if(m.type() != Token::CHAR || m.value().s < 'a' || m.value().s > 'z'){
        scan_stream.unget(m);
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
        return Token();
    }
    int len = m.len();
    std::stringstream s;
    s << m.value().s;
    m = scan_stream.getNextToken();
    while (m.type() == Token::CHAR && m.value().s >= 'a' && m.value().s <= 'z' && m.len() == 1){
        s << m.value().s;
        len++;
        m = scan_stream.getNextToken();
    }
    Token::token_t expect;
    if(m.type() == Token::ASSIGN){
        expect = Token::LVAR;
    } else {
        expect = Token::RVAR;
    }
    scan_stream.unget(m);
    symbol_t sym;
    s >> sym.name;
    unsigned int i;
    for(i = 0; i < symbol_table.size(); ++i){
        if(symbol_table[i].name == sym.name){
            if(!symbol_table[i].writen) break;// then it is still an LVAR
            for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "Variable " << sym.name << " at pos " << i << " already exists" << std::endl;
            if(expect == Token::LVAR){
                scan_stream.unget(Token(Token::RVAR, symbol_table[i].val, len));
                throw calc_exception("Multiple definition of variable " + sym.name, scan_stream.col(), scan_stream.line());
            }
            depth--;
            for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
            return Token(Token::RVAR, symbol_table[i].val, len);
        }
    }
    if(i == symbol_table.size()){
        symbol_table.push_back(sym);
        for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "Defining variable " << sym.name << " at pos " << i << std::endl;
    }
    if(expect == Token::RVAR){
        scan_stream.unget(Token(Token::LVAR, (int)i, len));
        throw calc_exception("Use of uninitialised variable " + sym.name, scan_stream.col(), scan_stream.line());
    }
    depth--;
    for(int i = 0; i < depth; ++i) std::cerr << "\t"; std::cerr << "}" << std::endl;
    return Token(Token::LVAR, (int)i, len);
}
