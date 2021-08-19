/* infixToPostfix.cpp
 * ------------------
 * CSCI 255
 * Lab #4:  STL: List, Stack, Queue (infix to postfix)
 * Authors: Darwin Jacob Groskleg, Man Lin
 * Date:    Tuesday, October 1st, 2019
 *
 * QUESTION: Make a few cases for infix expressions and verify the postfix
 *          expressions generated are correct. Submit the cases that you tested.
 *
 * PROGRAM OUTPUT
 * -----------------------------------------------------------------------------
 * Infix Expression :: A*(B+C)/D
 * Postfix Expression :: ABC+ * D/ 
 * 
 * Infix Expression   :: 367+151/563	 = 367
 * Postfix Expression :: 367 151 563 / + 	 = 367
 * CORRECT: postfix expression evaluates to expected result
 * 
 * Infix Expression   :: 2 * (3+1)/2	 = 4
 * Postfix Expression :: 2 3 1 + * 2 / 	 = 4
 * CORRECT: postfix expression evaluates to expected result
 * 
 * Infix Expression   :: 51*(61+107)/461	 = 18
 * Postfix Expression :: 51 61 107 + * 461 / 	 = 18
 * CORRECT: postfix expression evaluates to expected result
 * 
 * Infix Expression   :: ((15/(7-(1+1)))*3)-(2+(1+1))	 = 5
 * Postfix Expression :: 15 7 1 1 + - / 3 * 2 1 1 + + - 	 = 5
 * CORRECT: postfix expression evaluates to expected result
 * 
 * Infix Expression   :: 7/7/(7+2)	 = 0
 * Postfix Expression :: 7 7 / 7 2 + / 	 = 0
 * CORRECT: postfix expression evaluates to expected result
 * -----------------------------------------------------------------------------
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include <cctype>   // for isdigit
#include <cstring>  // for strncopy

using namespace std;

int getWeight(char ch);
void infix2postfix(char infix[], char postfix[], size_t size);

double evalPostfix(string postfix_expression);
string infix2postfix(string infix);
int ctoi(char c) { return c - '0'; }
struct InfixEquation { string expression; int result; };

// Infix to postfix conversion in C++
// Input Postfix expression must be in a desired format.
// Operands and operator, both must be single character.
// Only '+'  ,  '-'  , '*', '/'  operators are expected.
int main() {
    {
        char infix[] = "A*(B+C)/D";
        size_t size = strlen(infix);
        char *postfix;
        postfix = new char[size+1];
        infix2postfix(infix, postfix, size);
        cout << "Infix Expression :: " << infix;
        cout << "\nPostfix Expression :: " << postfix;
        cout << endl;
        delete postfix;
    }

    vector<InfixEquation> infix_expr_cases{
        {"367+151/563",                  367 + (151/563) },
        {"2 * (3+1)/2",                  2*(3+1)/2 },
        {"51*(61+107)/461",              51*(61+107)/461 },
        {"((15/(7-(1+1)))*3)-(2+(1+1))", ((15/(7-(1+1)))*3)-(2+(1+1))},
        {"7/7/(7+2)",                    7/7/(7+2)}
    };

    for (auto &eq : infix_expr_cases) {
        cout << "\nInfix Expression   :: " << eq.expression
             << "\t = " << eq.result;

        string postfix_expr = infix2postfix(eq.expression);
        auto postfix_result = evalPostfix(postfix_expr);
        cout << "\nPostfix Expression :: " << postfix_expr
             << "\t = " << postfix_result;

        if (postfix_result == eq.result)
            cout << "\nCORRECT: postfix expression evaluates to expected "
            << "result\n";
        else
            cout << "\nINCORRECT: postfix expression fails to evaluate to "
            << "expected result\n";
    }

    return 0;
}

// Calculate the result of the expression.
// Postfix has no need to use parentheses since there is no ambiguity.
//  O(n)
// CONSTRAINTS:
//  - does not handle floating point numbers in expressions
//  - does not handle negative numbers in expressions
double evalPostfix(string postfix_expression) {
    stack<int> operand_stack;
    int number = 0;
    int num_width = 0;
    for (auto &c : postfix_expression) {
        // parse each operand (numbers) then push it to the stack
        if (isdigit(c)) {
            number = number * 10 + ctoi(c);
            num_width++;
        } else if (num_width > 0) {
            // We know the last char was a digit.
            operand_stack.push(number);

            // ASSUMPTION: expression will ALWAYS end in an operator, so the
            // number (operand) will always get pushed to the stack.
            number = num_width = 0;
        }

        // handle operators
        //  1. pop 2 operands off the stack,
        //  2. perform operation,
        //  3. place result on the stack.
        if (getWeight(c) > 0) {
            int left, right;
            right = operand_stack.top(); operand_stack.pop();
            left  = operand_stack.top(); operand_stack.pop();

            switch (c) {
                case '/': operand_stack.push(left / right); break;
                case '*': operand_stack.push(left * right); break;
                case '+': operand_stack.push(left + right); break;
                case '-': operand_stack.push(left - right); break;
            }
        }

        // ignore any other characters
    }
    return operand_stack.top();
}

// Wrapper around its namesake for using string instead of cstring.
// Also does not mutate the infix expression argument.
string infix2postfix(string infix) {
    size_t infix_size = infix.size();
    // Add extra length for spaces to pad each number.
    size_t pofix_size = infix_size * 2;

    // need a mutable strings
    char* c_infix = new char[infix_size+1];
    strncpy(c_infix, infix.c_str(), infix_size);
    char* c_pofix = new char[pofix_size+1];

    infix2postfix(c_infix, c_pofix, infix_size);
    string postfix{c_pofix, strlen(c_pofix)};

    delete [] c_infix;
    delete [] c_pofix;
    return postfix;
}

// convert infix expression to postfix using a stack
// ADDED: spaces after end of numbers (whenever an operator is encountered
// SIZES: size of postfix must be at least 2 times greater than infix_size.
void infix2postfix(char infix[], char postfix[], size_t infix_size) {
    stack<char> s;
    int weight;
    size_t i = 0;
    size_t k = 0;
    char ch;
    // iterate over the infix expression
    while (i < infix_size) {
        ch = infix[i];
        // strip spaces from infix expression
        if (isspace(ch)) {
            i++;
            continue;
        }
        if (ch == '(') {
            // simply push the opening parenthesis
            s.push(ch);
            i++;
            continue;
        }
        if (ch == ')') {
            // Last number before ) needs padding
            if (isdigit(postfix[k-1])) postfix[k++] = ' ';

            // if we see a closing parenthesis,
            // pop of all the elements and append it to
            // the postfix expression till we encounter
            // a opening parenthesis
            while (!s.empty() && s.top() != '(') {
                postfix[k++] = s.top();
                s.pop();
                postfix[k++] = ' ';
            }
            // pop off the opening parenthesis also
            if (!s.empty()) {
                s.pop();
            }
            i++;
            continue;
        }
        weight = getWeight(ch);
        if (weight == 0) {
            // we saw an operand
            // simply append it to postfix expression
            postfix[k++] = ch;
            // if last digit in expression, need to append a space
            if (i >= infix_size-1 && isdigit(ch)) postfix[k++] = ' ';
        } else {
            // we saw an operator
            // Pad the end of preceding number with a whitespace.
            if (isdigit(postfix[k-1])) postfix[k++] = ' ';
            if (s.empty()) {
                // simply push the operator onto stack if
                // stack is empty
                s.push(ch);
            } else {
                // pop of all the operators from the stack and
                // append it to the postfix expression till we
                // see an operator with a lower precedence that
                // the current operator
                while (!s.empty() && s.top() != '(' &&
                       weight <= getWeight(s.top()))
                {
                    postfix[k++] = s.top();
                    s.pop();
                    postfix[k++] = ' ';
                }
                // push the current operator onto stack
                s.push(ch);
            }
        }
        i++;
    }
    // pop of the remaining operators present in the stack
    // and append it to postfix expression
    while (!s.empty()) {
        postfix[k++] = s.top();
        s.pop();
        postfix[k++] = ' ';
    }
    postfix[k] = 0; // null terminate the postfix expression
}

// get weight of operators as per precedence
// higher weight given to operators with higher precedence
// for non operators, return 0
int getWeight(char ch) {
    // Missing case returns fall-through to the next case.
    switch (ch) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}

