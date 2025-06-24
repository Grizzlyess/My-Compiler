#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>

using namespace std;

// Tabela de variáveis simples (nome -> valor)
extern map<string, string> variables;

// Classe base para todos os nós
class ASTNode
{
public:
    virtual void execute() = 0;
    virtual ~ASTNode() {}
};

// ======================= EXPRESSÕES =========================

class ASTExpr : public ASTNode
{
public:
    virtual string evaluate() = 0; // retorna valor como string
    void execute() override {}
};

// Número inteiro
class ASTInt : public ASTExpr
{
    int value;

public:
    ASTInt(int v) : value(v) {}
    string evaluate() override
    {
        return to_string(value);
    }
};

// Número float
class ASTFloat : public ASTExpr
{
    float value;

public:
    ASTFloat(float v) : value(v) {}
    string evaluate() override
    {
        return to_string(value);
    }
};

// String
class ASTString : public ASTExpr
{
    string value;

public:
    ASTString(const string &v) : value(v) {}
    string evaluate() override
    {
        return value;
    }
};

// Variável
class ASTVariable : public ASTExpr
{
    string name;

public:
    ASTVariable(const string &n) : name(n) {}
    string evaluate() override
    {
        return variables[name];
    }
};

// Operação binária (ex: +, -, ==, etc.)
class ASTBinary : public ASTExpr
{
    std::string op; // Corrigido: era char
    ASTExpr *left, *right;

public:
    ASTBinary(const std::string &o, ASTExpr *l, ASTExpr *r)
        : op(o), left(l), right(r) {}

    string evaluate() override
    {
        string l = left->evaluate();
        string r = right->evaluate();

        auto format = [](float v)
        {
            ostringstream out;
            out << fixed << setprecision(2) << v;
            return out.str();
        };

        if (op == "+")
            return format(stof(l) + stof(r));
        if (op == "-")
            return format(stof(l) - stof(r));
        if (op == "*")
            return format(stof(l) * stof(r));
        if (op == "/")
            return format(stof(l) / stof(r));
        if (op == "==")
            return (l == r) ? "1" : "0";
        if (op == "!=")
            return (l != r) ? "1" : "0";
        if (op == "<")
            return (stof(l) < stof(r)) ? "1" : "0";
        if (op == "<=")
            return (stof(l) <= stof(r)) ? "1" : "0";
        if (op == ">")
            return (stof(l) > stof(r)) ? "1" : "0";
        if (op == ">=")
            return (stof(l) >= stof(r)) ? "1" : "0";
        if (op == "and")
            return (stoi(l) && stoi(r)) ? "1" : "0";
        if (op == "or")
            return (stoi(l) || stoi(r)) ? "1" : "0";
        return "0";
    }

    ~ASTBinary()
    {
        delete left;
        delete right;
    }
};

// Operação unária (ex: -expr)
class ASTUnary : public ASTExpr
{
    std::string op;
    ASTExpr *expr;

public:
    ASTUnary(const std::string &o, ASTExpr *e)
        : op(o), expr(e) {}

    string evaluate() override
    {
        string val = expr->evaluate();
        if (op == "-")
            return to_string(-stof(val));
        return val;
    }

    ~ASTUnary()
    {
        delete expr;
    }
};

// ======================= COMANDOS =========================

// Declaração de variável
class ASTDeclaration : public ASTNode
{
    string type;
    string name;

public:
    ASTDeclaration(const string &t, const string &n)
        : type(t), name(n)
    {
        variables[name] = "0"; // valor inicial padrão
    }

    void execute() override {}
};

// Atribuição de variável
class ASTAssignment : public ASTNode
{
    string name;
    ASTExpr *expr;

public:
    ASTAssignment(const string &n, ASTExpr *e)
        : name(n), expr(e) {}

    void execute() override
    {
        variables[name] = expr->evaluate();
    }

    ~ASTAssignment()
    {
        delete expr;
    }
};

// Comando de leitura
class ASTRead : public ASTNode
{
    string name;

public:
    ASTRead(const string &n) : name(n) {}

    void execute() override
    {
        string val;
        cout << "Digite " << name << ": ";
        getline(cin, val);
        variables[name] = val;
    }
};

// Comando de escrita
class ASTWrite : public ASTNode
{
    ASTExpr *expr;

public:
    ASTWrite(ASTExpr *e) : expr(e) {}

    void execute() override
    {
        cout << expr->evaluate() << endl;
    }

    ~ASTWrite()
    {
        delete expr;
    }
};

// Condicional if/else
class ASTIf : public ASTNode
{
    ASTExpr *cond;
    ASTNode *thenBranch;
    ASTNode *elseBranch;

public:
    ASTIf(ASTExpr *c, ASTNode *t, ASTNode *e = nullptr)
        : cond(c), thenBranch(t), elseBranch(e) {}

    void execute() override
    {
        if (cond->evaluate() != "0")
            thenBranch->execute();
        else if (elseBranch)
            elseBranch->execute();
    }

    ~ASTIf()
    {
        delete cond;
        delete thenBranch;
        if (elseBranch)
            delete elseBranch;
    }
};

// Laço while
class ASTWhile : public ASTNode
{
    ASTExpr *cond;
    ASTNode *body;

public:
    ASTWhile(ASTExpr *c, ASTNode *b)
        : cond(c), body(b) {}

    void execute() override
    {
        while (cond->evaluate() != "0")
        {
            body->execute();
        }
    }

    ~ASTWhile()
    {
        delete cond;
        delete body;
    }
};

// Sequência de comandos (bloco)
class ASTSequence : public ASTNode
{
    ASTNode *first;
    ASTNode *second;

public:
    ASTSequence(ASTNode *f, ASTNode *s)
        : first(f), second(s) {}

    void execute() override
    {
        if (first)
            first->execute();
        if (second)
            second->execute();
    }

    ~ASTSequence()
    {
        delete first;
        delete second;
    }
};

#endif
