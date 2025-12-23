#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <dirent.h>    // 用于目录遍历

using namespace std;

// Token类别
enum TokenCategory {
    KEYWORD,        // 关键字
    IDENTIFIER,     // 标识符
    OPERATOR,       // 运算符
    DELIMITER,      // 界符
    CONSTANT,       // 常量
    UNKNOWN         // 未知类型
};

// Token具体类型
struct TokenType {
    string name;           // token名称
    TokenCategory category;// token类别
    
    // 添加默认构造函数
    TokenType() : name(""), category(UNKNOWN) {}
    
    // 保持原有的构造函数
    TokenType(string n, TokenCategory c) : name(n), category(c) {}
};

// Token结构
struct Token {
    string lexeme;        // 词素
    TokenType type;       // token类型
    int line;            // 行号
    
    // 添加默认构造函数
    Token() : lexeme(""), type(TokenType("", UNKNOWN)), line(0) {}
    
    // 保持原有的构造函数
    Token(string l, TokenType t, int ln) : lexeme(l), type(t), line(ln) {}
};

class Lexer {
private:
    string input;
    int position;
    int lineNo;
    char currentChar;
    
    // 关键字表
    vector<string> keywords = {
        "int", "if", "else", "while", "for", "return", "void", "main", "print"
    };
    
    // 运算符表
    vector<string> operators = {
        "+", "-", "*", "/", "%", "^",
        "=", "==", "!=", ">", "<", ">=", "<=",
        "&&", "||", "!"
    };
    
    // 界符表
    vector<string> delimiters = {
        "(", ")", "{", "}", "[", "]", ";", ",", "."
    };

public:
    Lexer(string text) : input(text), position(0), lineNo(1) {
        currentChar = position < input.length() ? input[position] : '\0';
    }
    
    void advance() {
        position++;
        if (currentChar == '\n') lineNo++;
        currentChar = position < input.length() ? input[position] : '\0';
    }
    
    void skipWhitespace() {
        while (currentChar != '\0' && isspace(currentChar)) {
            advance();
        }
    }
    
    // 判断是否是关键字
    bool isKeyword(const string& str) {
        for(const auto& keyword : keywords) {
            if(keyword == str) return true;
        }
        return false;
    }
    
    // 判断是否是运算符
    bool isOperator(const string& str) {
        for(const auto& op : operators) {
            if(op == str) return true;
        }
        return false;
    }
    
    // 判断是否是界符
    bool isDelimiter(const string& str) {
        for(const auto& delim : delimiters) {
            if(delim == str) return true;
        }
        return false;
    }

    Token getNextToken() {
        while (currentChar != '\0') {
            // 跳过空白字符
            if (isspace(currentChar)) {
                skipWhitespace();
                continue;
            }

            // 处理注释
            if (currentChar == '/') {
                advance();
                if (currentChar == '/') {  // 单行注释
                    while (currentChar != '\0' && currentChar != '\n') {
                        advance();
                    }
                    continue;
                } else if (currentChar == '*') {  // 多行注释
                    advance();
                    while (currentChar != '\0') {
                        if (currentChar == '*') {
                            advance();
                            if (currentChar == '/') {
                                advance();
                                break;
                            }
                        } else {
                            advance();
                        }
                    }
                    continue;
                } else {
                    // 如果不是注释，那就是除法运算符
                    return Token("/", TokenType("OPERATOR", OPERATOR), lineNo);
                }
            }

            // 识别数字常量
            if (isdigit(currentChar)) {
                string num;
                while (currentChar != '\0' && isdigit(currentChar)) {
                    num += currentChar;
                    advance();
                }
                return Token(num, TokenType("CONSTANT", CONSTANT), lineNo);
            }

            // 识别标识符和关键字
            if (isalpha(currentChar) || currentChar == '_') {
                string identifier;
                while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
                    identifier += currentChar;
                    advance();
                }
                
                if (isKeyword(identifier)) {
                    return Token(identifier, TokenType("KEYWORD", KEYWORD), lineNo);
                }
                return Token(identifier, TokenType("IDENTIFIER", IDENTIFIER), lineNo);
            }

            // 识别运算符和界符
            string op;
            op += currentChar;
            advance();
            
            // 处理双字符运算符
            if ((op == "=" || op == "!" || op == ">" || op == "<") && currentChar == '=') {
                op += currentChar;
                advance();
            } else if ((op == "&" && currentChar == '&') || (op == "|" && currentChar == '|')) {
                op += currentChar;
                advance();
            }
            
            if (isOperator(op)) {
                return Token(op, TokenType("OPERATOR", OPERATOR), lineNo);
            }
            if (isDelimiter(op)) {
                return Token(op, TokenType("DELIMITER", DELIMITER), lineNo);
            }

            // 如果遇到未知字符
            string errorMsg = "未知字符: " + op;
            throw runtime_error(errorMsg);
        }

        return Token("EOF", TokenType("EOF", UNKNOWN), lineNo);
    }
};

// 打印Token信息的辅助函数
string getCategoryName(TokenCategory cat) {
    switch(cat) {
        case KEYWORD: return "关键字";
        case IDENTIFIER: return "标识符";
        case OPERATOR: return "运算符";
        case DELIMITER: return "界符";
        case CONSTANT: return "常量";
        default: return "未知类型";
    }
}

// 抽象语法树节点类型
enum class ASTNodeType {
    PROGRAM,        // 程序
    FUNCTION_DECL,  // 函数声明
    VAR_DECL,       // 变量声明
    COMPOUND_STMT,  // 复合语句
    ASSIGN_STMT,    // 赋值语句
    IF_STMT,        // if语句
    WHILE_STMT,     // while语句
    RETURN_STMT,    // return语句
    BINARY_EXPR,    // 二元表达式
    UNARY_EXPR,     // 一元表达式
    IDENTIFIER,     // 标识符
    CONSTANT,       // 常量
    EMPTY          // 空语句
};

// 四元式结构
struct Quadruple {
    string op;      // 操作符
    string arg1;    // 第一个操作数
    string arg2;    // 第二个操作数
    string result;  // 结果
    
    Quadruple(string o, string a1, string a2, string r) 
        : op(o), arg1(a1), arg2(a2), result(r) {}
        
    // 用于打印四元式
    string toString() const {
        return "(" + op + ", " + arg1 + ", " + arg2 + ", " + result + ")";
    }
};

// 抽象语法树节点
class ASTNode {
private:
    static int tempVarCount;  // 用于生成临时变量名
    static int labelCount;    // 用于生成标签

public:
    ASTNodeType type;
    string value;
    vector<ASTNode*> children;
    
    ASTNode(ASTNodeType t, string v = "") : type(t), value(v) {}
    
    void addChild(ASTNode* child) {
        children.push_back(child);
    }
    
    // 修改 print 函数，添加一个包装函数
    void print(ostream& out = cout) {
        vector<bool> levels;
        printTree(0, out, true, levels);
    }

    // 生成新的临时变量名
    static string newTemp() {
        return "t" + to_string(tempVarCount++);
    }
    
    // 生成新的标签
    static string newLabel() {
        return "L" + to_string(labelCount++);
    }
    
    // 生成四元式的方法
    virtual vector<Quadruple> generateCode() {
        vector<Quadruple> code;
        
        switch(type) {
            case ASTNodeType::PROGRAM:
                for (auto child : children) {
                    auto childCode = child->generateCode();
                    code.insert(code.end(), childCode.begin(), childCode.end());
                }
                break;
                
            case ASTNodeType::FUNCTION_DECL: {
                string funcName = children[0]->value;  // 第一个子节点是函数名
                code.push_back(Quadruple("FUNC_BEGIN", funcName, "", ""));
                
                // 处理函数体（第二个子节点是复合语句）
                for (size_t i = 1; i < children.size(); i++) {
                    auto childCode = children[i]->generateCode();
                    code.insert(code.end(), childCode.begin(), childCode.end());
                }
                
                code.push_back(Quadruple("FUNC_END", funcName, "", ""));
                break;
            }
                
            case ASTNodeType::VAR_DECL: {
                string varName = children[0]->value;  // 变量名
                if (children.size() > 1) {  // 有初始化值
                    auto initCode = children[1]->generateCode();
                    code.insert(code.end(), initCode.begin(), initCode.end());
                    code.push_back(Quadruple("=", children[1]->result, "", varName));
                }
                break;
            }
                
            case ASTNodeType::ASSIGN_STMT: {
                string varName = children[0]->value;
                auto exprCode = children[1]->generateCode();
                code.insert(code.end(), exprCode.begin(), exprCode.end());
                code.push_back(Quadruple("=", children[1]->result, "", varName));
                break;
            }
                
            case ASTNodeType::IF_STMT: {
                string labelElse = newLabel();
                string labelEnd = newLabel();
                
                // 条件表达式的代码
                auto condCode = children[0]->generateCode();
                code.insert(code.end(), condCode.begin(), condCode.end());
                
                // 条件跳转
                code.push_back(Quadruple("JZ", children[0]->result, "", labelElse));
                
                // if 分支的代码
                auto ifCode = children[1]->generateCode();
                code.insert(code.end(), ifCode.begin(), ifCode.end());
                
                if (children.size() > 2) {  // 有 else 分支
                    code.push_back(Quadruple("JMP", "", "", labelEnd));
                    code.push_back(Quadruple("LABEL", "", "", labelElse));
                    auto elseCode = children[2]->generateCode();
                    code.insert(code.end(), elseCode.begin(), elseCode.end());
                    code.push_back(Quadruple("LABEL", "", "", labelEnd));
                } else {
                    code.push_back(Quadruple("LABEL", "", "", labelElse));
                }
                break;
            }
                
            case ASTNodeType::WHILE_STMT: {
                string labelStart = newLabel();
                string labelEnd = newLabel();
                
                code.push_back(Quadruple("LABEL", "", "", labelStart));
                
                // 条件表达式的代码
                auto condCode = children[0]->generateCode();
                code.insert(code.end(), condCode.begin(), condCode.end());
                
                // 条件跳转
                code.push_back(Quadruple("JZ", children[0]->result, "", labelEnd));
                
                // 循环体的代码
                auto bodyCode = children[1]->generateCode();
                code.insert(code.end(), bodyCode.begin(), bodyCode.end());
                
                code.push_back(Quadruple("JMP", "", "", labelStart));
                code.push_back(Quadruple("LABEL", "", "", labelEnd));
                break;
            }
                
            case ASTNodeType::BINARY_EXPR: {
                auto leftCode = children[0]->generateCode();
                auto rightCode = children[1]->generateCode();
                
                code.insert(code.end(), leftCode.begin(), leftCode.end());
                code.insert(code.end(), rightCode.begin(), rightCode.end());
                
                result = newTemp();
                code.push_back(Quadruple(value, children[0]->result, children[1]->result, result));
                break;
            }
                
            case ASTNodeType::UNARY_EXPR: {
                auto exprCode = children[0]->generateCode();
                code.insert(code.end(), exprCode.begin(), exprCode.end());
                
                result = newTemp();
                code.push_back(Quadruple(value, children[0]->result, "", result));
                break;
            }
                
            case ASTNodeType::IDENTIFIER:
                result = value;
                break;
                
            case ASTNodeType::CONSTANT:
                result = value;
                break;
                
            case ASTNodeType::RETURN_STMT: {
                if (!children.empty()) {
                    // 有返回值
                    auto exprCode = children[0]->generateCode();
                    code.insert(code.end(), exprCode.begin(), exprCode.end());
                    code.push_back(Quadruple("return", children[0]->result, "", ""));
                } else {
                    // 无返回值
                    code.push_back(Quadruple("return", "", "", ""));
                }
                break;
            }
                
            case ASTNodeType::COMPOUND_STMT: {
                // 处理复合语句中的所有子语句
                for (auto child : children) {
                    auto childCode = child->generateCode();
                    code.insert(code.end(), childCode.begin(), childCode.end());
                }
                break;
            }
        }
        
        return code;
    }
    
    string result;  // 存储表达式的结果（临时变量名或常量值）

private:
    
    void printTree(int level, ostream& out, bool isLast, vector<bool>& levels) {
        // 打印前导的连接线
        for (int i = 0; i < level - 1; i++) {
            out << (levels[i] ? "    " : "│   ");
        }
        
        // 打印当前节点的连接线
        if (level > 0) {
            out << (isLast ? "└── " : "├── ");
        }
        
        // 打印节点内容
        out << getNodeTypeName();
        if (!value.empty()) {
            out << " " << value;
        }
        out << endl;
        
        // 记录当前层级的状态
        if (level >= levels.size()) {
            levels.push_back(!isLast);
        } else {
            levels[level] = !isLast;
        }
        
        // 递归打印子节点
        for (size_t i = 0; i < children.size(); i++) {
            children[i]->printTree(level + 1, out, i == children.size() - 1, levels);
        }
        
        // 恢复当前层级的状态
        if (level < levels.size()) {
            levels[level] = false;
        }
    }
    
    string getNodeTypeName() {
        switch(type) {
            case ASTNodeType::PROGRAM: return "程序";
            case ASTNodeType::FUNCTION_DECL: return "函数声明";
            case ASTNodeType::VAR_DECL: return "变量声明";
            case ASTNodeType::COMPOUND_STMT: return "复合语句";
            case ASTNodeType::ASSIGN_STMT: return "赋值语句";
            case ASTNodeType::IF_STMT: return "if语句";
            case ASTNodeType::WHILE_STMT: return "while语句";
            case ASTNodeType::RETURN_STMT: return "return语句";
            case ASTNodeType::BINARY_EXPR: return "二元表达式";
            case ASTNodeType::UNARY_EXPR: return "一元表达式";
            case ASTNodeType::IDENTIFIER: return "标识符";
            case ASTNodeType::CONSTANT: return "常量";
            case ASTNodeType::EMPTY: return "空语句";
            default: return "未知类型";
        }
    }
};

// 初始化静态成员
int ASTNode::tempVarCount = 0;
int ASTNode::labelCount = 0;

// 语法分析器
class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    
    void advance() {
        currentToken = lexer.getNextToken();
    }
    
    void eat(TokenCategory category) {
        if (currentToken.type.category == category) {
            advance();
        } else {
            string error = "语法错误：期望 " + getCategoryName(category) + 
                         "，但得到 " + getCategoryName(currentToken.type.category) +
                         "，词素为：" + currentToken.lexeme;  // 添加词素信息以便调试
            throw runtime_error(error);
        }
    }

public:
    Parser(Lexer& lex) : lexer(lex) {
        advance();  // 获取第一个token
    }
    
    // 解析程序
    ASTNode* parse() {
        return program();
    }
    
    // 程序 -> 函数声明列表
    ASTNode* program() {
        ASTNode* node = new ASTNode(ASTNodeType::PROGRAM);
        while (currentToken.type.name != "EOF") {
            node->addChild(functionDecl());
        }
        return node;
    }
    
    // 函数声明 -> 类型 标识符 '(' 参数列表? ')' 复合语句
    ASTNode* functionDecl() {
        ASTNode* node = new ASTNode(ASTNodeType::FUNCTION_DECL);
        
        // 解析返回类型
        if (currentToken.type.category == KEYWORD) {
            node->value = currentToken.lexeme;  // 保存返回类型
            advance();
        } else {
            throw runtime_error("期望函数返回类型");
        }
        
        // 解析函数名
        if (currentToken.type.category == IDENTIFIER || 
            (currentToken.type.category == KEYWORD && currentToken.lexeme == "main")) {  // 特殊处理main
            ASTNode* funcName = new ASTNode(ASTNodeType::IDENTIFIER, currentToken.lexeme);
            node->addChild(funcName);
            advance();
        } else {
            throw runtime_error("期望函数名");
        }
        
        // 解析参数列表
        if (currentToken.lexeme != "(") {
            throw runtime_error("期望'('");
        }
        advance();  // 吃掉 '('
        
        // TODO: 解析参数列表
        
        if (currentToken.lexeme != ")") {
            throw runtime_error("期望')'");
        }
        advance();  // 吃掉 ')'
        
        // 解析函数体
        node->addChild(compoundStmt());
        
        return node;
    }
    
    // 复合语句 -> '{' 语句列表 '}'
    ASTNode* compoundStmt() {
        ASTNode* node = new ASTNode(ASTNodeType::COMPOUND_STMT);
        
        eat(DELIMITER);  // 吃掉 '{'
        
        // 解析语句列表
        while (currentToken.lexeme != "}") {
            node->addChild(statement());
        }
        
        eat(DELIMITER);  // 吃掉 '}'
        
        return node;
    }
    
    // 语句
    ASTNode* statement() {
        switch (currentToken.type.category) {
            case KEYWORD:
                if (currentToken.lexeme == "if") return ifStmt();
                if (currentToken.lexeme == "while") return whileStmt();
                if (currentToken.lexeme == "return") return returnStmt();
                if (currentToken.lexeme == "int") return varDecl();
                break;
            case IDENTIFIER:
                return assignStmt();
            default:
                return empty();
        }
        throw runtime_error("未知的语句类型");
    }
    
    // 变量声明 -> 类型 标识符 ('=' 表达式)? ';'
    ASTNode* varDecl() {
        ASTNode* node = new ASTNode(ASTNodeType::VAR_DECL);
        
        // 保存类型
        node->value = currentToken.lexeme;  // int
        advance();
        
        // 保存变量名
        if (currentToken.type.category == IDENTIFIER) {
            ASTNode* varName = new ASTNode(ASTNodeType::IDENTIFIER, currentToken.lexeme);
            node->addChild(varName);
            advance();
        }
        
        // 如果有初始化
        if (currentToken.lexeme == "=") {
            advance();  // 吃掉 =
            node->addChild(expression());
        }
        
        eat(DELIMITER);  // 吃掉 ;
        return node;
    }
    
    // 赋值语句 -> 标识符 '=' 表达式 ';'
    ASTNode* assignStmt() {
        ASTNode* node = new ASTNode(ASTNodeType::ASSIGN_STMT);
        
        // 保存变量名
        ASTNode* varName = new ASTNode(ASTNodeType::IDENTIFIER, currentToken.lexeme);
        node->addChild(varName);
        advance();
        
        eat(OPERATOR);  // 吃掉 =
        node->addChild(expression());
        eat(DELIMITER);  // 吃掉 ;
        
        return node;
    }
    
    // if语句 -> 'if' '(' 表达式 ')' 复合语句 ('else' 复合语句)?
    ASTNode* ifStmt() {
        ASTNode* node = new ASTNode(ASTNodeType::IF_STMT);
        
        advance();  // 吃掉 if
        eat(DELIMITER);  // 吃掉 (
        node->addChild(expression());  // 条件表达式
        eat(DELIMITER);  // 吃掉 )
        
        node->addChild(compoundStmt());  // if 分支
        
        // 处理 else 分支
        if (currentToken.lexeme == "else") {
            advance();  // 吃掉 else
            node->addChild(compoundStmt());
        }
        
        return node;
    }
    
    // while语句 -> 'while' '(' 表达式 ')' 复合语句
    ASTNode* whileStmt() {
        ASTNode* node = new ASTNode(ASTNodeType::WHILE_STMT);
        
        advance();  // 吃掉 while
        eat(DELIMITER);  // 吃掉 (
        node->addChild(expression());  // 条件表达式
        eat(DELIMITER);  // 吃掉 )
        
        node->addChild(compoundStmt());  // 循环体
        
        return node;
    }
    
    // return语句 -> 'return' 表达式? ';'
    ASTNode* returnStmt() {
        ASTNode* node = new ASTNode(ASTNodeType::RETURN_STMT);
        
        advance();  // 吃掉 return
        
        // 如果不是分号，说明有返回值
        if (currentToken.lexeme != ";") {
            node->addChild(expression());
        }
        
        eat(DELIMITER);  // 吃掉 ;
        return node;
    }
    
    // 表达式
    ASTNode* expression() {
        return logicalOr();  // 从最低优先级的运算开始
    }
    
    // 逻辑或表达式
    ASTNode* logicalOr() {
        ASTNode* node = logicalAnd();
        
        while (currentToken.lexeme == "||") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(logicalAnd());
            node = newNode;
        }
        
        return node;
    }
    
    // 逻辑与表达式
    ASTNode* logicalAnd() {
        ASTNode* node = equality();
        
        while (currentToken.lexeme == "&&") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(equality());
            node = newNode;
        }
        
        return node;
    }
    
    // 相等性表达式
    ASTNode* equality() {
        ASTNode* node = relational();
        
        while (currentToken.lexeme == "==" || currentToken.lexeme == "!=") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(relational());
            node = newNode;
        }
        
        return node;
    }
    
    // 关系表达式
    ASTNode* relational() {
        ASTNode* node = additive();
        
        while (currentToken.lexeme == "<" || currentToken.lexeme == ">" ||
               currentToken.lexeme == "<=" || currentToken.lexeme == ">=") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(additive());
            node = newNode;
        }
        
        return node;
    }
    
    // 加法表达式
    ASTNode* additive() {
        ASTNode* node = multiplicative();
        
        while (currentToken.lexeme == "+" || currentToken.lexeme == "-") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(multiplicative());
            node = newNode;
        }
        
        return node;
    }
    
    // 乘法表达式
    ASTNode* multiplicative() {
        ASTNode* node = unary();
        
        while (currentToken.lexeme == "*" || currentToken.lexeme == "/" || 
               currentToken.lexeme == "%") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* newNode = new ASTNode(ASTNodeType::BINARY_EXPR, op);
            newNode->addChild(node);
            newNode->addChild(unary());
            node = newNode;
        }
        
        return node;
    }
    
    // 一元表达式
    ASTNode* unary() {
        if (currentToken.lexeme == "+" || currentToken.lexeme == "-" || 
            currentToken.lexeme == "!") {
            string op = currentToken.lexeme;
            advance();  // 吃掉运算符
            
            ASTNode* node = new ASTNode(ASTNodeType::UNARY_EXPR, op);
            node->addChild(unary());
            return node;
        }
        
        return primary();
    }
    
    // 基本表达式
    ASTNode* primary() {
        Token token = currentToken;
        if (token.type.category == CONSTANT) {
            advance();
            return new ASTNode(ASTNodeType::CONSTANT, token.lexeme);
        }
        
        if (token.type.category == IDENTIFIER) {
            advance();
            return new ASTNode(ASTNodeType::IDENTIFIER, token.lexeme);
        }
        
        if (token.lexeme == "(") {
            advance();  // 吃掉 (
            ASTNode* node = expression();
            eat(DELIMITER);  // 吃掉 )
            return node;
        }
        
        throw runtime_error("意外的token: " + token.lexeme);
    }
    
    // 空语句
    ASTNode* empty() {
        return new ASTNode(ASTNodeType::EMPTY);
    }
};

// 在 Quadruple 结构体后添加优化器类
class CodeOptimizer {
private:
    vector<Quadruple>& code;
    
    // 判断是否是数字
    bool isNumber(const string& str) {
        return !str.empty() && 
               find_if(str.begin(), str.end(), 
                      [](char c) { return !isdigit(c) && c != '-'; }) == str.end();
    }
    
    // 计算常量表达式
    string evaluateConstant(const string& op, const string& arg1, const string& arg2) {
        if (!isNumber(arg1) || !isNumber(arg2)) return "";
        
        int num1 = stoi(arg1);
        int num2 = stoi(arg2);
        int result = 0;
        
        if (op == "+") result = num1 + num2;
        else if (op == "-") result = num1 - num2;
        else if (op == "*") result = num1 * num2;
        else if (op == "/") result = num2 != 0 ? num1 / num2 : 0;
        else if (op == "%") result = num2 != 0 ? num1 % num2 : 0;
        else if (op == "<") result = num1 < num2;
        else if (op == ">") result = num1 > num2;
        else if (op == "<=") result = num1 <= num2;
        else if (op == ">=") result = num1 >= num2;
        else if (op == "==") result = num1 == num2;
        else if (op == "!=") result = num1 != num2;
        else return "";
        
        return to_string(result);
    }
    
    // 检查变量是否在后续被使用
    bool isVariableUsed(const string& var, size_t start) {
        // 检查变量名是否是临时变量
        if (var[0] == 't') {
            for (size_t i = start + 1; i < code.size(); i++) {
                if (code[i].arg1 == var || code[i].arg2 == var) return true;
            }
        } else {
            // 非临时变量（如 a, b, c）应该保留
            return true;
        }
        return false;
    }
    
    // 获取变量的当前值
    string getCurrentValue(const string& var, size_t pos) {
        for (int i = pos - 1; i >= 0; i--) {
            if (code[i].result == var && code[i].op == "=") {
                return code[i].arg1;
            }
        }
        return "";
    }

public:
    CodeOptimizer(vector<Quadruple>& intermediateCode) : code(intermediateCode) {}
    
    // 执行所有优化
    void optimize() {
        bool changed;
        do {
            changed = false;
            changed |= constantFolding();
            changed |= deadCodeElimination();
            changed |= commonSubexpressionElimination();
            changed |= copyPropagation();
        } while (changed);
    }
    
    // 常量折叠
    bool constantFolding() {
        bool changed = false;
        map<string, string> constants;  // 存储已知的常量值
        
        // 第一遍：收集所有常量赋值
        for (const auto& quad : code) {
            if (quad.op == "=" && isNumber(quad.arg1)) {
                constants[quad.result] = quad.arg1;
            }
        }
        
        // 第二遍：进行常量折叠
        for (size_t i = 0; i < code.size(); i++) {
            // 跳过控制流相关的指令
            if (code[i].op == "FUNC_BEGIN" || code[i].op == "FUNC_END" || 
                code[i].op == "LABEL" || code[i].op == "JMP" || code[i].op == "JZ" ||
                code[i].op == "return") {
                continue;
            }
            
            // 对于比较运算，不进行常量折叠
            if (code[i].op == "<" || code[i].op == ">" || code[i].op == "<=" || 
                code[i].op == ">=" || code[i].op == "==" || code[i].op == "!=") {
                continue;
            }
            
            string arg1 = code[i].arg1;
            string arg2 = code[i].arg2;
            
            // 替换已知常量
            if (constants.find(arg1) != constants.end()) {
                arg1 = constants[arg1];
            }
            if (constants.find(arg2) != constants.end()) {
                arg2 = constants[arg2];
            }
            
            // 尝试计算结果
            if (isNumber(arg1) && (arg2.empty() || isNumber(arg2))) {
                string result = evaluateConstant(code[i].op, arg1, arg2);
                if (!result.empty()) {
                    code[i].op = "=";
                    code[i].arg1 = result;
                    code[i].arg2 = "";
                    constants[code[i].result] = result;
                    changed = true;
                }
            }
        }
        return changed;
    }
    
    // 死代码消除
    bool deadCodeElimination() {
        bool changed = false;
        vector<Quadruple> newCode;
        
        for (size_t i = 0; i < code.size(); i++) {
            // 保留所有标签、跳转和函数相关的四元式
            if (code[i].op == "LABEL" || code[i].op == "JMP" || code[i].op == "JZ" ||
                code[i].op == "FUNC_BEGIN" || code[i].op == "FUNC_END" || 
                code[i].op == "return") {
                newCode.push_back(code[i]);
                continue;
            }
            
            // 检查结果是否被使用
            if (!code[i].result.empty() && !isVariableUsed(code[i].result, i)) {
                changed = true;
                continue;
            }
            
            newCode.push_back(code[i]);
        }
        
        if (changed) {
            code = newCode;
        }
        return changed;
    }
    
    // 公共子表达式消除
    bool commonSubexpressionElimination() {
        bool changed = false;
        map<string, string> expressions;
        
        for (size_t i = 0; i < code.size(); i++) {
            if (code[i].op != "=" && code[i].op != "LABEL" && code[i].op != "JMP" && 
                code[i].op != "JZ" && code[i].op != "FUNC_BEGIN" && code[i].op != "FUNC_END") {
                string expr = code[i].op + "," + code[i].arg1 + "," + code[i].arg2;
                
                if (expressions.find(expr) != expressions.end()) {
                    // 找到公共子表达式
                    code[i].op = "=";
                    code[i].arg1 = expressions[expr];
                    code[i].arg2 = "";
                    changed = true;
                } else {
                    expressions[expr] = code[i].result;
                }
            }
        }
        return changed;
    }
    
    // 复制传播
    bool copyPropagation() {
        bool changed = false;
        map<string, pair<string, string>> copies;  // 变量 -> (操作符, 操作数)
        
        for (size_t i = 0; i < code.size(); i++) {
            // 跳过控制流相关的指令
            if (code[i].op == "LABEL" || code[i].op == "JMP" || code[i].op == "JZ") {
                continue;
            }
            
            // 记录赋值
            if (code[i].op == "=") {
                copies[code[i].result] = make_pair("=", code[i].arg1);
            } else {
                copies[code[i].result] = make_pair(code[i].op, code[i].arg1 + "," + code[i].arg2);
            }
            
            // 替换操作数（只替换临时变量）
            if (code[i].arg1[0] == 't') {
                auto it = copies.find(code[i].arg1);
                if (it != copies.end() && it->second.first == "=") {
                    code[i].arg1 = it->second.second;
                    changed = true;
                }
            }
            if (!code[i].arg2.empty() && code[i].arg2[0] == 't') {
                auto it = copies.find(code[i].arg2);
                if (it != copies.end() && it->second.first == "=") {
                    code[i].arg2 = it->second.second;
                    changed = true;
                }
            }
        }
        return changed;
    }
};

// 在 ASTNodeType 枚举后添加类型系统相关定义
enum class DataType {
    INT,
    VOID,
    UNKNOWN
};

// 符号表项
struct SymbolEntry {
    string name;
    DataType type;
    bool isFunction;
    vector<DataType> paramTypes;  // 如果是函数，存储参数类型
    
    // 添加默认构造函数
    SymbolEntry() : name(""), type(DataType::UNKNOWN), isFunction(false) {}
    
    // 保持原有的构造函数
    SymbolEntry(string n, DataType t, bool isFunc = false) 
        : name(n), type(t), isFunction(isFunc) {}
};

// 类型检查器
class TypeChecker {
private:
    map<string, SymbolEntry> symbolTable;
    vector<string> errors;
    
    // 获取表达式的类型
    DataType getExprType(ASTNode* node) {
        switch (node->type) {
            case ASTNodeType::CONSTANT:
                return DataType::INT;  // 目前所有常量都是整数
                
            case ASTNodeType::IDENTIFIER: {
                auto it = symbolTable.find(node->value);
                if (it != symbolTable.end()) {
                    return it->second.type;
                }
                errors.push_back("未声明的变量: " + node->value);
                return DataType::UNKNOWN;
            }
                
            case ASTNodeType::BINARY_EXPR: {
                DataType leftType = getExprType(node->children[0]);
                DataType rightType = getExprType(node->children[1]);
                
                if (leftType == DataType::UNKNOWN || rightType == DataType::UNKNOWN) {
                    return DataType::UNKNOWN;
                }
                
                if (leftType != rightType) {
                    errors.push_back("类型不匹配: " + node->value);
                    return DataType::UNKNOWN;
                }
                
                return leftType;
            }
                
            case ASTNodeType::UNARY_EXPR: {
                return getExprType(node->children[0]);
            }
                
            default:
                return DataType::UNKNOWN;
        }
    }

public:
    // 检查整个程序
    bool checkProgram(ASTNode* root) {
        if (root->type != ASTNodeType::PROGRAM) {
            errors.push_back("根节点必须是程序节点");
            return false;
        }
        
        // 检查每个函数声明
        for (auto child : root->children) {
            checkFunctionDecl(child);
        }
        
        return errors.empty();
    }
    
    // 检查函数声明
    void checkFunctionDecl(ASTNode* node) {
        if (node->type != ASTNodeType::FUNCTION_DECL) return;
        
        string funcName = node->children[0]->value;
        DataType returnType = node->value == "int" ? DataType::INT : DataType::VOID;
        
        // 添加函数到符号表
        symbolTable[funcName] = SymbolEntry(funcName, returnType, true);
        
        // 检查函数体
        checkCompoundStmt(node->children[1], returnType);
    }
    
    // 检查复合语句
    void checkCompoundStmt(ASTNode* node, DataType currentFuncType) {
        if (node->type != ASTNodeType::COMPOUND_STMT) return;
        
        // 检查每个语句
        for (auto stmt : node->children) {
            checkStatement(stmt, currentFuncType);
        }
    }
    
    // 检查单个语句
    void checkStatement(ASTNode* node, DataType currentFuncType) {
        switch (node->type) {
            case ASTNodeType::VAR_DECL: {
                string varName = node->children[0]->value;
                DataType varType = node->value == "int" ? DataType::INT : DataType::VOID;
                
                // 检查变量重定义
                if (symbolTable.find(varName) != symbolTable.end()) {
                    errors.push_back("变量重定义: " + varName);
                    return;
                }
                
                // 添加到符号表
                symbolTable[varName] = SymbolEntry(varName, varType);
                
                // 如果有初始化表达式，检查类型匹配
                if (node->children.size() > 1) {
                    DataType initType = getExprType(node->children[1]);
                    if (initType != varType && initType != DataType::UNKNOWN) {
                        errors.push_back("初始化类型不匹配: " + varName);
                    }
                }
                break;
            }
                
            case ASTNodeType::ASSIGN_STMT: {
                string varName = node->children[0]->value;
                auto it = symbolTable.find(varName);
                if (it == symbolTable.end()) {
                    errors.push_back("使用未声明的变量: " + varName);
                    return;
                }
                
                DataType exprType = getExprType(node->children[1]);
                if (exprType != it->second.type && exprType != DataType::UNKNOWN) {
                    errors.push_back("赋值类型不匹配: " + varName);
                }
                break;
            }
                
            case ASTNodeType::IF_STMT: {
                // 检查条件表达式
                DataType condType = getExprType(node->children[0]);
                if (condType != DataType::INT && condType != DataType::UNKNOWN) {
                    errors.push_back("if条件必须是整数类型");
                }
                
                // 检查分支
                checkCompoundStmt(node->children[1], currentFuncType);
                if (node->children.size() > 2) {
                    checkCompoundStmt(node->children[2], currentFuncType);
                }
                break;
            }
                
            case ASTNodeType::WHILE_STMT: {
                // 检查条件表达式
                DataType condType = getExprType(node->children[0]);
                if (condType != DataType::INT && condType != DataType::UNKNOWN) {
                    errors.push_back("while条件必须是整数类型");
                }
                
                // 检查循环体
                checkCompoundStmt(node->children[1], currentFuncType);
                break;
            }
                
            case ASTNodeType::RETURN_STMT: {
                if (node->children.empty()) {
                    if (currentFuncType != DataType::VOID) {
                        errors.push_back("返回值类型不匹配：期望int，得到void");
                    }
                } else {
                    DataType returnType = getExprType(node->children[0]);
                    if (returnType != currentFuncType && returnType != DataType::UNKNOWN) {
                        errors.push_back("返回值类型不匹配");
                    }
                }
                break;
            }
        }
    }
    
    // 获取错误信息
    vector<string> getErrors() const {
        return errors;
    }
};

// 在 TypeChecker 类后添加代码生成器
class CodeGenerator {
private:
    vector<string> assembly;
    map<string, string> varMap;  // 变量到内存位置的映射
    int stackOffset = 0;         // 当前栈偏移
    int labelCount = 0;          // 标签计数器
    
    // 生成新的标签
    string newLabel() {
        return "L" + to_string(labelCount++);
    }
    
    // 分配栈空间
    string allocateVar(const string& var) {
        if (varMap.find(var) == varMap.end()) {
            stackOffset += 4;  // 为变量分配4字节
            varMap[var] = "[ebp-" + to_string(stackOffset) + "]";
        }
        return varMap[var];
    }
    
    // 生成数据段
    void generateDataSection() {
        assembly.push_back("section .data");
        // 添加常量和字符串
    }
    
    // 生成代码段
    void generateTextSection() {
        assembly.push_back("section .text");
        assembly.push_back("global main");
        assembly.push_back("");
    }

public:
    // 从四元式生成汇编代码
    vector<string> generate(const vector<Quadruple>& code) {
        generateDataSection();
        generateTextSection();
        
        for (const auto& quad : code) {
            if (quad.op == "FUNC_BEGIN") {
                if (quad.arg1 == "main") {
                    assembly.push_back("main:");
                    assembly.push_back("    push ebp");
                    assembly.push_back("    mov ebp, esp");
                    assembly.push_back("    sub esp, 64");  // 预留栈空间
                }
            }
            else if (quad.op == "FUNC_END") {
                if (quad.arg1 == "main") {
                    assembly.push_back("    mov esp, ebp");
                    assembly.push_back("    pop ebp");
                    assembly.push_back("    ret");
                }
            }
            else if (quad.op == "=") {
                string dest = allocateVar(quad.result);
                if (isdigit(quad.arg1[0]) || quad.arg1[0] == '-') {
                    // 常量赋值
                    assembly.push_back("    mov dword " + dest + ", " + quad.arg1);
                } else {
                    // 变量赋值
                    string src = allocateVar(quad.arg1);
                    assembly.push_back("    mov eax, " + src);
                    assembly.push_back("    mov " + dest + ", eax");
                }
            }
            else if (quad.op == "+") {
                string src1 = allocateVar(quad.arg1);
                string src2 = allocateVar(quad.arg2);
                string dest = allocateVar(quad.result);
                assembly.push_back("    mov eax, " + src1);
                assembly.push_back("    add eax, " + src2);
                assembly.push_back("    mov " + dest + ", eax");
            }
            else if (quad.op == "-") {
                string src1 = allocateVar(quad.arg1);
                string src2 = allocateVar(quad.arg2);
                string dest = allocateVar(quad.result);
                assembly.push_back("    mov eax, " + src1);
                assembly.push_back("    sub eax, " + src2);
                assembly.push_back("    mov " + dest + ", eax");
            }
            else if (quad.op == "*") {
                string src1 = allocateVar(quad.arg1);
                string src2 = allocateVar(quad.arg2);
                string dest = allocateVar(quad.result);
                assembly.push_back("    mov eax, " + src1);
                assembly.push_back("    imul dword " + src2);
                assembly.push_back("    mov " + dest + ", eax");
            }
            else if (quad.op == "/") {
                string src1 = allocateVar(quad.arg1);
                string src2 = allocateVar(quad.arg2);
                string dest = allocateVar(quad.result);
                assembly.push_back("    mov eax, " + src1);
                assembly.push_back("    cdq");  // 扩展 eax 到 edx:eax
                assembly.push_back("    idiv " + src2);
                assembly.push_back("    mov " + dest + ", eax");
            }
            else if (quad.op == "JMP") {
                assembly.push_back("    jmp " + quad.result);
            }
            else if (quad.op == "JZ") {
                if (isdigit(quad.arg1[0]) || quad.arg1[0] == '-') {
                    // 常量条件
                    int value = stoi(quad.arg1);
                    if (value == 0) {
                        assembly.push_back("    jmp " + quad.result);
                    }
                } else {
                    // 变量条件
                    string src = allocateVar(quad.arg1);
                    assembly.push_back("    mov eax, " + src);
                    assembly.push_back("    test eax, eax");  // 测试是否为0
                    assembly.push_back("    jz " + quad.result);
                }
            }
            else if (quad.op == "LABEL") {
                assembly.push_back(quad.result + ":");
            }
            else if (quad.op == "return") {
                if (!quad.arg1.empty()) {
                    if (isdigit(quad.arg1[0]) || quad.arg1[0] == '-') {
                        assembly.push_back("    mov eax, " + quad.arg1);
                    } else {
                        string src = allocateVar(quad.arg1);
                        assembly.push_back("    mov eax, " + src);
                    }
                }
            }
            else if (quad.op == ">") {
                string src1 = allocateVar(quad.arg1);
                string src2;
                if (isdigit(quad.arg2[0]) || quad.arg2[0] == '-') {
                    // 如果是常量
                    assembly.push_back("    mov eax, " + src1);
                    assembly.push_back("    cmp eax, " + quad.arg2);
                } else {
                    // 如果是变量
                    src2 = allocateVar(quad.arg2);
                    assembly.push_back("    mov eax, " + src1);
                    assembly.push_back("    cmp eax, dword " + src2);
                }
                string dest = allocateVar(quad.result);
                assembly.push_back("    setg al");
                assembly.push_back("    movzx eax, al");
                assembly.push_back("    mov " + dest + ", eax");
            }
            else if (quad.op == "<") {
                string src1 = allocateVar(quad.arg1);
                string src2;
                if (isdigit(quad.arg2[0]) || quad.arg2[0] == '-') {
                    // 如果是常量
                    assembly.push_back("    mov eax, " + src1);
                    assembly.push_back("    cmp eax, " + quad.arg2);
                } else {
                    // 如果是变量
                    src2 = allocateVar(quad.arg2);
                    assembly.push_back("    mov eax, " + src1);
                    assembly.push_back("    cmp eax, dword " + src2);
                }
                string dest = allocateVar(quad.result);
                assembly.push_back("    setl al");
                assembly.push_back("    movzx eax, al");
                assembly.push_back("    mov " + dest + ", eax");
            }
        }
        
        return assembly;
    }
};

int main() {
    string filename;
    cout << "请输入要分析的文件名（无需输入.txt后缀）：";
    cin >> filename;
    
    // 自动添加.txt后缀
    filename += ".txt";
    
    // 从文件读取源代码
    ifstream inFile(filename);
    if (!inFile) {
        cout << "错误：无法打开文件 " << filename << endl;
        return 1;
    }

    // 读取文件内容
    stringstream buffer;
    buffer << inFile.rdbuf();
    string sourceCode = buffer.str();
    inFile.close();
    
    // 创建词法分析器实例
    Lexer lexer(sourceCode);
    
    // 创建语法分析器实例
    Parser parser(lexer);
    
    // 创建输出文件名（在原文件名后添加_output.txt）
    string outFilename = filename.substr(0, filename.length() - 4) + "_output.txt";
    ofstream outFile(outFilename);
    
    if (!outFile) {
        cout << "错误：无法创建输出文件 " << outFilename << endl;
        return 1;
    }
    
    try {
        // 先进行词法分析
        cout << "\n词法分析结果：\n";
        cout << setw(5) << "行号" << setw(15) << "类别" << setw(20) << "词素" << endl;
        cout << string(40, '-') << endl;
        
        outFile << "\n词法分析结果：\n";
        outFile << setw(5) << "行号" << setw(15) << "类别" << setw(20) << "词素" << endl;
        outFile << string(40, '-') << endl;
        
        // 保存源代码的副本用于词法分析
        string sourceCodeCopy = sourceCode;
        Lexer lexerForTokens(sourceCodeCopy);
        Token token;
        do {
            token = lexerForTokens.getNextToken();
            if (token.type.name != "EOF") {
                // 输出到控制台
                cout << setw(5) << token.line 
                     << setw(15) << getCategoryName(token.type.category)
                     << setw(20) << token.lexeme << endl;
                
                // 输出到文件
                outFile << setw(5) << token.line 
                       << setw(15) << getCategoryName(token.type.category)
                       << setw(20) << token.lexeme << endl;
            }
        } while (token.type.name != "EOF");
        
        // 进行语法分析
        cout << "\n语法分析结果：\n";
        cout << "语法树：\n";
        outFile << "\n语法分析结果：\n";
        outFile << "语法树：\n";
        
        // 创建新的词法分析器和语法分析器
        Lexer lexer(sourceCode);
        Parser parser(lexer);
        ASTNode* root = parser.parse();
        
        // 打印语法树（只打印一次）
        root->print(cout);  // 打印到控制台
        
        // 将语法树保存到文件
        outFile << "\n";
        root->print(outFile);  // 打印到文件
        
        // 生成四元式
        cout << "\n中间代码（四元式）：\n";
        outFile << "\n中间代码（四元式）：\n";

        vector<Quadruple> intermediateCode = root->generateCode();
        for (size_t i = 0; i < intermediateCode.size(); i++) {
            cout << i << ": " << intermediateCode[i].toString() << endl;
            outFile << i << ": " << intermediateCode[i].toString() << endl;
        }
        
        // 原始中间代码
        cout << "\n原始中间代码：\n";
        outFile << "\n原始中间代码：\n";
        for (size_t i = 0; i < intermediateCode.size(); i++) {
            cout << i << ": " << intermediateCode[i].toString() << endl;
            outFile << i << ": " << intermediateCode[i].toString() << endl;
        }

        // 执行代码优化
        CodeOptimizer optimizer(intermediateCode);
        optimizer.optimize();

        // 优化后的中间代码
        cout << "\n优化后的中间代码：\n";
        outFile << "\n优化后的中间代码：\n";
        for (size_t i = 0; i < intermediateCode.size(); i++) {
            cout << i << ": " << intermediateCode[i].toString() << endl;
            outFile << i << ": " << intermediateCode[i].toString() << endl;
        }
        
        // 类型检查
        cout << "\n类型检查：\n";
        outFile << "\n类型检查：\n";

        TypeChecker typeChecker;
        if (!typeChecker.checkProgram(root)) {
            cout << "发现类型错误：\n";
            outFile << "发现类型错误：\n";
            for (const auto& error : typeChecker.getErrors()) {
                cout << "- " << error << endl;
                outFile << "- " << error << endl;
            }
        } else {
            cout << "类型检查通过\n";
            outFile << "类型检查通过\n";
        }
        
        // 在优化后的代码后面添加
        cout << "\n目标代码（x86汇编）：\n";
        outFile << "\n目标代码（x86汇编）：\n";

        CodeGenerator generator;
        vector<string> assemblyCode = generator.generate(intermediateCode);

        // 输出汇编代码
        for (const auto& line : assemblyCode) {
            cout << line << endl;
            outFile << line << endl;
        }

        // 保存汇编代码到文件
        string asmFilename = filename.substr(0, filename.length() - 4) + ".asm";
        ofstream asmFile(asmFilename);
        if (asmFile) {
            for (const auto& line : assemblyCode) {
                asmFile << line << endl;
            }
            asmFile.close();
            cout << "\n汇编代码已保存到: " << asmFilename << endl;
        }
        
        // 清理内存
        // TODO: 实现析构函数清理语法树
        
    } catch (const runtime_error& e) {
        cout << "错误: " << e.what() << endl;
        outFile << "错误: " << e.what() << endl;
    }
    
    outFile.close();
    cout << "\n分析结果已保存到: " << outFilename << endl;
    
	return 0;
}

