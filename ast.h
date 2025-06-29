#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>
#include <limits> // Necessário para a correção do 'read'

using namespace std;

// Tabelas de símbolos globais
extern map<string, string> variables;
extern map<string, vector<string>> vector_variables;

// Declaração antecipada para referência cruzada
class ASTExpr;
class ASTVectorInit;

// ======================= CLASSES BASE =======================
class ASTNode
{
public:
    virtual void execute() = 0;
    virtual ~ASTNode() {}
};

class ASTExpr : public ASTNode
{
public:
    virtual string evaluate() = 0;
    void execute() override {}
};

// ======================= EXPRESSÕES =========================

// Número inteiro
class ASTInt : public ASTExpr
{
    int value;

public:
    ASTInt(int v) : value(v) {}
    string evaluate() override { return to_string(value); }
};

// Número float - CORRIGIDO para formatar com 2 casas decimais
class ASTFloat : public ASTExpr
{
    float value;

public:
    ASTFloat(float v) : value(v) {}
    string evaluate() override
    {
        ostringstream out;
        out << fixed << setprecision(2) << value;
        return out.str();
    }
};

// String
class ASTString : public ASTExpr
{
    string value;

public:
    ASTString(const string &v) : value(v) {}
    string evaluate() override { return value; }
};

// Variável
class ASTVariable : public ASTExpr
{
    string name;

public:
    ASTVariable(const string &n) : name(n) {}
    string evaluate() override
    {
        if (vector_variables.count(name))
        {
            return name;
        }
        if (variables.find(name) == variables.end())
        {
            cerr << "Erro de execucao: variavel '" << name << "' nao declarada." << endl;
            exit(1);
        }
        return variables[name];
    }
};

// Inicialização de Vetor
class ASTVectorInit : public ASTExpr
{
public:
    vector<ASTExpr *> elements;
    ASTVectorInit(vector<ASTExpr *> *elems)
    {
        if (elems)
        {
            elements = *elems;
            delete elems;
        }
    }
    ~ASTVectorInit()
    {
        for (auto expr : elements)
        {
            delete expr;
        }
    }
    vector<string> evaluate_list()
    {
        vector<string> values;
        for (auto elem : elements)
        {
            values.push_back(elem->evaluate());
        }
        return values;
    }
    string evaluate() override
    {
        stringstream ss;
        ss << "[";
        for (size_t i = 0; i < elements.size(); ++i)
        {
            ss << elements[i]->evaluate();
            if (i < elements.size() - 1)
                ss << ", ";
        }
        ss << "]";
        return ss.str();
    }
};

// Acesso a elemento de Vetor
class ASTVectorAccess : public ASTExpr
{
    string name;
    ASTExpr *index_expr;

public:
    ASTVectorAccess(const string &n, ASTExpr *idx) : name(n), index_expr(idx) {}
    ~ASTVectorAccess()
    {
        delete index_expr;
    }
    string evaluate() override
    {
        if (vector_variables.find(name) == vector_variables.end())
        {
            cerr << "Erro de execucao: vetor '" << name << "' nao declarado." << endl;
            exit(1);
        }
        int index = stoi(index_expr->evaluate());
        if (index < 0 || static_cast<size_t>(index) >= vector_variables[name].size())
        {
            cerr << "Erro de execucao: indice " << index << " fora dos limites para o vetor '" << name << "'." << endl;
            exit(1);
        }
        return vector_variables[name][index];
    }
};

// Operação Binária
class ASTBinary : public ASTExpr
{
    std::string op;
    ASTExpr *left, *right;

public:
    ASTBinary(const std::string &o, ASTExpr *l, ASTExpr *r)
        : op(o), left(l), right(r) {}
    ~ASTBinary()
    {
        delete left;
        delete right;
    }
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
        if (op == "&&")
            return (stoi(l) && stoi(r)) ? "1" : "0";
        if (op == "||")
            return (stoi(l) || stoi(r)) ? "1" : "0";
        return "0";
    }
};

// Operação Unária
class ASTUnary : public ASTExpr
{
    std::string op;
    ASTExpr *expr;

public:
    ASTUnary(const std::string &o, ASTExpr *e) : op(o), expr(e) {}
    ~ASTUnary()
    {
        delete expr;
    }
    string evaluate() override
    {
        string val = expr->evaluate();
        if (op == "-")
            return to_string(-stof(val));
        return val;
    }
};

// ======================= COMANDOS =========================

// Declaração de Variável
class ASTDeclaration : public ASTNode
{
    string type;
    string name;

public:
    ASTDeclaration(const string &t, const string &n) : type(t), name(n)
    {
        variables[name] = "0";
    }
    void execute() override {}
};

// Declaração de Vetor
class ASTVectorDeclaration : public ASTNode
{
    string type;
    string name;
    ASTVectorInit *init;

public:
    ASTVectorDeclaration(const string &t, const string &n, ASTVectorInit *i = nullptr)
        : type(t), name(n), init(i) {}
    ~ASTVectorDeclaration()
    {
        delete init;
    }
    void execute() override
    {
        if (init)
        {
            vector_variables[name] = init->evaluate_list();
        }
        else
        {
            vector_variables[name] = vector<string>();
        }
    }
};

// Atribuição
class ASTAssignment : public ASTNode
{
    string name;
    ASTExpr *expr;

public:
    ASTAssignment(const string &n, ASTExpr *e) : name(n), expr(e) {}
    ~ASTAssignment()
    {
        delete expr;
    }
    void execute() override
    {
        ASTVectorInit *vec_init = dynamic_cast<ASTVectorInit *>(expr);
        if (vec_init)
        {
            if (vector_variables.find(name) == vector_variables.end())
            {
                cerr << "Erro de execucao: vetor '" << name << "' nao declarado." << endl;
                exit(1);
            }
            vector_variables[name] = vec_init->evaluate_list();
        }
        else
        {
            if (vector_variables.count(name))
            {
                cerr << "Erro de execucao: nao se pode atribuir um valor escalar a um vetor '" << name << "'." << endl;
                exit(1);
            }
            variables[name] = expr->evaluate();
        }
    }
};

// Comando de Leitura
class ASTRead : public ASTNode
{
    string name;

public:
    ASTRead(const string &n) : name(n) {}
    void execute() override
    {
        string val;
        cout << "Digite " << name << ": ";

        // Se o próximo caractere for uma nova linha, ignora
        if (cin.peek() == '\n')
            cin.ignore();

        getline(cin, val);
        variables[name] = val;
    }
};

// Comando de Escrita
class ASTWrite : public ASTNode
{
    ASTExpr *expr;

public:
    ASTWrite(ASTExpr *e) : expr(e) {}
    ~ASTWrite()
    {
        delete expr;
    }
    void execute() override
    {
        ASTVariable *var = dynamic_cast<ASTVariable *>(expr);
        if (var)
        {
            string var_name = var->evaluate();
            if (vector_variables.count(var_name))
            {
                cout << "[";
                const auto &vec = vector_variables[var_name];
                for (size_t i = 0; i < vec.size(); ++i)
                {
                    cout << vec[i];
                    if (i < vec.size() - 1)
                        cout << ", ";
                }
                cout << "]" << endl;
                return;
            }
        }
        cout << expr->evaluate() << endl;
    }
};

// Condicional If/Else
class ASTIf : public ASTNode
{
    ASTExpr *cond;
    ASTNode *thenBranch;
    ASTNode *elseBranch;

public:
    ASTIf(ASTExpr *c, ASTNode *t, ASTNode *e = nullptr)
        : cond(c), thenBranch(t), elseBranch(e) {}
    ~ASTIf()
    {
        delete cond;
        delete thenBranch;
        if (elseBranch)
            delete elseBranch;
    }
    void execute() override
    {
        if (cond->evaluate() != "0")
            thenBranch->execute();
        else if (elseBranch)
            elseBranch->execute();
    }
};

// Laço While
class ASTWhile : public ASTNode
{
    ASTExpr *cond;
    ASTNode *body;

public:
    ASTWhile(ASTExpr *c, ASTNode *b) : cond(c), body(b) {}
    ~ASTWhile()
    {
        delete cond;
        delete body;
    }
    void execute() override
    {
        while (cond->evaluate() != "0")
        {
            body->execute();
        }
    }
};

// Sequência de Comandos
class ASTSequence : public ASTNode
{
    ASTNode *first;
    ASTNode *second;

public:
    ASTSequence(ASTNode *f, ASTNode *s) : first(f), second(s) {}
    ~ASTSequence()
    {
        delete first;
        delete second;
    }
    void execute() override
    {
        if (first)
            first->execute();
        if (second)
            second->execute();
    }
};

#endif
