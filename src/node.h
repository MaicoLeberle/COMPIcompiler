#include <iostream>
#include <vector>
// #include <llvm/Value.h>


class CodeGenContext;
class node {
public:
    virtual ~node() { }
   // virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

class class_decl;
class program : public node {
public:
    std::vector<class_decl*> classes;
    program(std::vector<class_decl*>& list_classes) : classes(list_classes) { }
   // virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

class field_decl;
class method_decl;
class class_decl : public node {
public:
    std::string id;
    std::vector<field_decl*>* fields;
    std::vector<method_decl*>* methods;
    class_decl(std::string ident, std::vector<field_decl*>* list_fields, std::vector<method_decl*>* list_methods) :
        id(ident), fields(list_fields), methods(list_methods) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
}; 

class identifier_decl;
class field_decl : public node {
public:
    std::string f_type;
    std::vector<identifier_decl*> ids;
    field_decl(std::string t, std::vector<identifier_decl*> list_ids) : f_type(t), ids(list_ids) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class body;
class identifier;
class method_decl : public node {
public: 
    std::string m_type;
    std::string id;
    std::vector<identifier*>* arguments;
    body* m_body;
    method_decl(std::string method_type, std::string method_id, std::vector<identifier*>* method_args, body* method_body) :
        m_type(method_type), id(method_id), arguments(method_args), m_body(method_body) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class block;
class body : public node {
public:
    bool is_extern;
    block* b_block;
    body(block* body_block) : is_extern(false), b_block(body_block) { }
    body() : is_extern(true), b_block(NULL) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class statement;
class block : public node {
public:
    std::vector<field_decl*>* field_decls;
    std::vector<statement*>* statements;
    block(std::vector<field_decl*>* block_field_decls, std::vector<statement*>* block_statements) :
        field_decls(block_field_decls), statements(block_statements) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};


class types : public node {
public:
    std::string t;
    types(std::string t_type) : t(t_type) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class statement : public node {
public:
};

class location;
class expr;
class assignment_statement : public statement {
public:
    location* loc;
    expr* e;
    assignment_statement(location* assignment_location, expr* assignment_expression) : 
        loc(assignment_location), e(assignment_expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class method_call;
class method_call_statement : public statement {
public:
    method_call* m;
    method_call_statement(method_call* method) : m(method) { }
};

class if_statement : public statement {
public:
    expr* e;
    statement* true_statement;
    statement* false_statement;
    if_statement(expr* expression, statement* t) : 
        e(expression), true_statement(t), false_statement(NULL) {}
    if_statement(expr* expression, statement* t, statement* f) :
        e(expression), true_statement(t), false_statement(f) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class for_statement : public statement {
public:
    identifier* id;
    expr* from;
    expr* to;
    statement* s;
    for_statement(identifier* ident, expr* from_expression, expr* to_expression, statement* for_body) :
        id(ident), from(from_expression), to(to_expression), s(for_body) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class while_statement : public statement {
public:
    expr* e;
    statement* s;
    while_statement(expr* while_guard, statement* while_body) : e(while_guard), s(while_body) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class return_statement : public statement {
public:
    expr* e;
    return_statement(expr* return_expression) : e(return_expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class break_statement : public statement {
public:
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class continue_statement : public statement {
public:
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class skip_statement : public statement {
public:
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class block_statement : public statement {
public:
    statement* s;
    block_statement(statement* statement_block) : s(statement_block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class assign_op {
public:
    std::string op;
    assign_op(std::string operator_symbol) : op(operator_symbol) { }
};

class method_call : public node {
public:
    std::vector<identifier*> ids;
    std::vector<expr*>* e;
    method_call(std::vector<identifier*> list_ids) : ids(list_ids) { }
    method_call(std::vector<identifier*> list_ids, std::vector<expr*>* expression) :
        ids(list_ids), e(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class location : public node {
public:
    std::vector<identifier*> ids;
    expr* e;
    location(std::vector<identifier*> location_ids) : ids(location_ids) { }
    location(std::vector<identifier*> location_ids, expr* index) :
        ids(location_ids), e(index) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class expr : public node {
};

class location_expr : public expr {
public:
    location l;
    location_expr(location loc) : l(loc) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class method_call_expr : public expr {
public:
    method_call m;
    method_call_expr(method_call m_call) : m(m_call) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class literal;
class literal_expr : public expr {
public:
    literal* l;
    literal_expr(literal* l_expression) : l(l_expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class bin_op;
class binary_operation_expr : public expr {
public:
    bin_op* op;
    expr* lhs_expr;
    expr* rhs_expr;
    binary_operation_expr(bin_op* binary_operator, expr* left_expression, expr* right_expression) :
        op(binary_operator), lhs_expr(left_expression), rhs_expr(right_expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class minus_expr : public expr {
public:
    expr e;
    minus_expr(expr expression) : e(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class negate_expr : public expr {
public:
    expr e;
    negate_expr(expr expression) : e(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class parenthesis_expr : public expr {
public:
    expr e;
    parenthesis_expr(expr expression) : e(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class bin_op {
public:
    std::string op;
    bin_op(std::string operator_symbol) : op(operator_symbol) { }
};

class arith_op {
public:
    std::string op;
    arith_op(std::string operator_symbol) : op(operator_symbol) { }
};

class rel_op {
public:
    std::string op;
    rel_op(std::string operator_symbol) : op(operator_symbol) { }
};

class eq_op {
public:
    std::string op;
    eq_op(std::string operator_symbol) : op(operator_symbol) { }
};

class cond_op {
public:
    std::string op;
    cond_op(std::string operator_symbol) : op(operator_symbol) { }
};

class literal : public node {
public:
};


class alpha {
public:
    char c;
    alpha(char character) : c(character) { }
    char get() { return c; }
    void set(char character) { c = character; }
};

class digit {
public:
    int i;
    digit(int number) : i(number) { }
    int get() { return i; }
};

class alpha_num {
public:
    alpha* a;
    digit* d;
    alpha_num(char character) { a = new alpha(character); }
    alpha_num(int i) { d = new digit(i); }
    alpha_num(alpha* character) : a(character), d(NULL) { }
    alpha_num(digit* number) : a(NULL), d(number) { }
    bool is_alpha() { return a != NULL; }
    bool is_digit() { return this->d != NULL; }
    char get_alpha() { return a->get(); }
    int get_digit() { return d->get(); }
};

class identifier {
public:
    alpha* c;
    std::vector<alpha_num*> rest;
    identifier(std::string id) {
        if (id.size() >= 1) {
            c->set(id[0]);
            for(int i = 1; i < id.size(); ++i) {
                alpha_num* extra = new alpha_num(id[i]);
                rest.push_back(extra);
            }
        } else {
            // ERROR
        }
    }
    identifier(char first_char, std::vector<alpha_num*> continuation) {
        c = new alpha(first_char);
        rest = continuation;
    }
    std::string get() {
        std::string s = "";
        s += c->get();
        for(std::vector<alpha_num*>::iterator it = rest.begin(); it != rest.end(); ++it) {
            if ((*it)->is_alpha())
                s += (*it)->get_alpha() ;
            if((*it)->is_digit())
                s += (*it)->get_digit();
        }
        return s;
    }
    void set(std::string id) {
        if (id.size() >= 1) {
            c->set(id[0]);
            for(int i = 1; i < id.size(); ++i) {
                alpha_num* extra = new alpha_num(id[i]);
                rest.push_back(extra);
            }
        } else {
            // ERROR
        }
    }
    int get_size() {
        int count = 1; // Because it is of length 1 at least.
        for(std::vector<alpha_num*>::iterator it = rest.begin(); it != rest.end(); ++it) {
            count++;
        }
        return count;
    }
};

class identifier_decl : public identifier {
public:
    int size;
    identifier_decl(std::string id) : identifier(id), size(1) { }
    identifier_decl(std::string id, int identifier_size) : identifier(id), size(identifier_size) { }
};

class int_literal : public literal { 
public:
    long long  value;
    int_literal(long long val) : value(val) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class float_literal : public literal {
public:
    double value;
    float_literal(double val) : value(val) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class bool_literal : public literal { 
public:
    bool value;
    bool_literal(bool val) : value(val) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);    
};

class string_literal : public literal { 
public:
    std::string value;
    string_literal(const std::string val) : value(val) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};