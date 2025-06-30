#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// Tabelas de símbolos globais
extern map<string, string> variables;
extern map<string, vector<string>> vector_variables;
extern map<string, string> variable_types;

class ASTExpr;
class ASTVectorInit;

// CONSTRUIR OS NOS
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

// EXPRESSÕES

class ASTInt : public ASTExpr
{
    int valor;

public:
    ASTInt(int v) : valor(v) {}
    string evaluate() override { return to_string(valor); }
};

class ASTFloat : public ASTExpr
{
    float valor;

public:
    ASTFloat(float v) : valor(v) {}
    string evaluate() override
    {
        ostringstream out;
        out << fixed << setprecision(2) << valor;
        return out.str();
    }
};

class ASTString : public ASTExpr
{
    string valor;

public:
    ASTString(const string &v) : valor(v) {}
    string evaluate() override { return valor; }
};

class ASTVariable : public ASTExpr
{
    string name;

public:
    ASTVariable(const string &n) : name(n) {}

    string getName() const { return name; }

    string evaluate() override
    {
        if (!variable_types.count(name))
        {
            cerr << "Erro de execucao: variavel '" << name << "' nao declarada." << endl;
            exit(1);
        }

        string type = variable_types[name];
        if (type == "string")
        {
            string reconstructed_string = "";
            for (const auto &ch : vector_variables[name])
            {
                reconstructed_string += ch;
            }
            return reconstructed_string;
        }
        else if (type.rfind("vector", 0) == 0)
        {
            return name;
        }
        else
        {
            return variables[name];
        }
    }
};

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
        return "[vector initializer]";
    }
};

class ASTVectorAccess : public ASTExpr
{
    string name;
    ASTExpr *index_expr;

public:
    ASTVectorAccess(const string &n, ASTExpr *idx) : name(n), index_expr(idx) {}
    ~ASTVectorAccess() { delete index_expr; }
    string evaluate() override
    {
        if (!vector_variables.count(name))
        {
            cerr << "Erro de execucao: variavel/vetor '" << name << "' nao declarado." << endl;
            exit(1);
        }
        int index = stoi(index_expr->evaluate());
        if (index < 0 || static_cast<size_t>(index) >= vector_variables[name].size())
        {
            cerr << "Erro de execucao: indice " << index << " fora dos limites para '" << name << "'." << endl;
            exit(1);
        }
        return vector_variables[name][index];
    }
};

class ASTVectorSize : public ASTExpr
{
    string name;

public:
    ASTVectorSize(const string &n) : name(n) {}
    string evaluate() override
    {
        if (!vector_variables.count(name))
        {
            cerr << "Erro de execucao: variavel/vetor '" << name << "' nao declarado." << endl;
            exit(1);
        }
        return to_string(vector_variables[name].size());
    }
};

class ASTBinary : public ASTExpr
{
    std::string op;
    ASTExpr *left, *right;

public:
    ASTBinary(const std::string &o, ASTExpr *l, ASTExpr *r) : op(o), left(l), right(r) {}
    ~ASTBinary()
    {
        delete left;
        delete right;
    }
    string evaluate() override
    {
        string l = left->evaluate();
        string r = right->evaluate();

        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^")
        {
            bool is_float = l.find('.') != string::npos || r.find('.') != string::npos;
            if (is_float)
            {
                ostringstream out;
                double result;
                if (op == "+")
                    result = stof(l) + stof(r);
                if (op == "-")
                    result = stof(l) - stof(r);
                if (op == "*")
                    result = stof(l) * stof(r);
                if (op == "/")
                    result = stof(l) / stof(r);
                if (op == "^")
                    result = pow(stod(l), stod(r));
                out << fixed << setprecision(2) << result;
                return out.str();
            }
            else
            {

                long long result;
                if (op == "+")
                    result = stoll(l) + stoll(r);
                if (op == "-")
                    result = stoll(l) - stoll(r);
                if (op == "*")
                    result = stoll(l) * stoll(r);
                if (op == "/")
                    result = stoll(l) / stoll(r);
                if (op == "^")
                    result = pow(stoll(l), stoll(r));
                return to_string(result);
            }
        }

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
            return (stof(l) != 0.0f && stof(r) != 0.0f) ? "1" : "0";
        if (op == "||")
            return (stof(l) != 0.0f || stof(r) != 0.0f) ? "1" : "0";

        return "0";
    }
};


class ASTUnary : public ASTExpr
{
    std::string op;
    ASTExpr *expr;
public:
    ASTUnary(const std::string &o, ASTExpr *e) : op(o), expr(e) {}
    ~ASTUnary() { delete expr; }
    string evaluate() override
    {
        string val = expr->evaluate();
        
        if (op == "!") {
            // Negação Lógica
            bool is_false = (stof(val) == 0.0f);
            return is_false ? "1" : "0";
        }
        
        if (op == "-") {
            bool is_float = val.find('.') != string::npos;
            if (is_float) {
                ostringstream out;
                out << fixed << setprecision(2) << -stof(val);
                return out.str();
            } else {
                return to_string(-stoll(val));
            }
        }

        return val; 
    }
};

// COMANDOS

class ASTDeclaration : public ASTNode
{
    string type;
    string name;

public:
    ASTDeclaration(const string &t, const string &n) : type(t), name(n) {}
    void execute() override
    {
        variable_types[name] = type;
        if (type == "string")
        {
            vector_variables[name] = vector<string>();
        }
        else if (type == "int" || type == "float")
        {
            variables[name] = "0";
        }
    }
};

class ASTVectorDeclaration : public ASTNode
{
    string type;
    string name;
    ASTVectorInit *init;

public:
    ASTVectorDeclaration(const string &t, const string &n, ASTVectorInit *i = nullptr) : type(t), name(n), init(i) {}
    ~ASTVectorDeclaration() { delete init; }
    void execute() override
    {
        variable_types[name] = type;
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

class ASTAssignment : public ASTNode
{
    string name;
    ASTExpr *expr;

public:
    ASTAssignment(const string &n, ASTExpr *e) : name(n), expr(e) {}
    ~ASTAssignment() { delete expr; }
    void execute() override
    {
        if (!variable_types.count(name))
        {
            cerr << "Erro de execucao: variavel '" << name << "' nao declarada." << endl;
            exit(1);
        }
        string type = variable_types[name];
        if (type == "string")
        {
            string value_to_assign = expr->evaluate();
            vector<string> char_vector;
            for (char c : value_to_assign)
            {
                char_vector.push_back(string(1, c));
            }
            vector_variables[name] = char_vector;
            return;
        }

        ASTVectorInit *vec_init = dynamic_cast<ASTVectorInit *>(expr);
        if (vec_init)
        {
            if (type.rfind("vector", 0) != 0)
            {
                cerr << "Erro de execucao: nao se pode atribuir uma lista a um nao-vetor '" << name << "'." << endl;
                exit(1);
            }
            vector_variables[name] = vec_init->evaluate_list();
        }
        else
        {
            if (type.rfind("vector", 0) == 0)
            {
                cerr << "Erro de execucao: nao se pode atribuir um valor escalar a um vetor '" << name << "'." << endl;
                exit(1);
            }
            variables[name] = expr->evaluate();
        }
    }
};

class ASTRead : public ASTNode
{
    string name;

public:
    ASTRead(const string &n) : name(n) {}
    void execute() override
    {
        string val;
        cout << "Digite " << name << ": ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, val);

        if (!variable_types.count(name))
        {
            cerr << "Erro de execucao: variavel '" << name << "' nao declarada para leitura." << endl;
            exit(1);
        }

        string type = variable_types[name];
        if (type == "string")
        {
            vector<string> char_vector;
            for (char c : val)
            {
                char_vector.push_back(string(1, c));
            }
            vector_variables[name] = char_vector;
        }
        else
        {
            variables[name] = val;
        }
    }
};

class ASTWrite : public ASTNode
{
    ASTExpr *expr;
public:
    ASTWrite(ASTExpr *e) : expr(e) {}
    ~ASTWrite() { delete expr; }
    void execute() override
    {
        ASTVariable *var_node = dynamic_cast<ASTVariable *>(expr);
        if (var_node) {
            string var_name = var_node->getName();
            if (variable_types.count(var_name)) {
                 string type = variable_types[var_name];
                 if (type == "string") {
                     cout << var_node->evaluate() << endl;
                     return;
                 } else if (type.rfind("vector", 0) == 0) {
                     cout << "[";
                     const auto &vec = vector_variables[var_name];
                     for (size_t i = 0; i < vec.size(); ++i) {
                         cout << vec[i];
                         if (i < vec.size() - 1)
                             cout << ", ";
                     }
                     cout << "]" << endl;
                     return;
                 }
            }
        }
        
        cout << expr->evaluate() << endl;
    }
};

class ASTPrint : public ASTNode
{
    ASTExpr *expr;
public:
    ASTPrint(ASTExpr *e) : expr(e) {}
    ~ASTPrint() { delete expr; }
    void execute() override
    {
        // A lógica é idêntica à de ASTWrite, mas usa 'cout' sem 'endl'.
        ASTVariable *var_node = dynamic_cast<ASTVariable *>(expr);
        if (var_node) {
            string var_name = var_node->getName();
            if (variable_types.count(var_name)) {
                 string type = variable_types[var_name];
                 if (type == "string") {
                     cout << var_node->evaluate(); // SEM endl
                     return;
                 } else if (type.rfind("vector", 0) == 0) {
                     cout << "[";
                     const auto &vec = vector_variables[var_name];
                     for (size_t i = 0; i < vec.size(); ++i) {
                         cout << vec[i];
                         if (i < vec.size() - 1)
                             cout << ", ";
                     }
                     cout << "]"; // SEM endl
                     return;
                 }
            }
        }
        
        cout << expr->evaluate(); // SEM endl
    }
};


class ASTPrintln : public ASTNode
{
public:
    ASTPrintln() {}
    void execute() override
    {
        cout << endl;
    }
};

class ASTIf : public ASTNode
{
    ASTExpr *cond;
    ASTNode *thenBranch;
    ASTNode *elseBranch;

public:
    ASTIf(ASTExpr *c, ASTNode *t, ASTNode *e = nullptr) : cond(c), thenBranch(t), elseBranch(e) {}
    ~ASTIf()
    {
        delete cond;
        delete thenBranch;
        if (elseBranch)
            delete elseBranch;
    }
    void execute() override
    {
        if (stof(cond->evaluate()) != 0.0f)
            thenBranch->execute();
        else if (elseBranch)
            elseBranch->execute();
    }
};

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
        while (stof(cond->evaluate()) != 0.0f)
        {
            body->execute();
        }
    }
};

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

class ASTVectorPush : public ASTNode
{
    string name;
    ASTExpr *expr;

public:
    ASTVectorPush(const string &n, ASTExpr *e) : name(n), expr(e) {}
    ~ASTVectorPush() { delete expr; }
    void execute() override
    {
        if (!vector_variables.count(name))
        {
            cerr << "Erro de execucao: variavel/vetor '" << name << "' nao declarado." << endl;
            exit(1);
        }
        vector_variables[name].push_back(expr->evaluate());
    }
};

class ASTVectorPop : public ASTNode
{
    string name;

public:
    ASTVectorPop(const string &n) : name(n) {}
    void execute() override
    {
        if (!vector_variables.count(name))
        {
            cerr << "Erro de execucao: variavel/vetor '" << name << "' nao declarado." << endl;
            exit(1);
        }
        if (vector_variables[name].empty())
        {
            cerr << "Erro de execucao: nao e possivel aplicar pop() em um vetor vazio '" << name << "'." << endl;
            exit(1);
        }
        vector_variables[name].pop_back();
    }
};

#endif
