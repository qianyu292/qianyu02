//中缀转后缀和后缀转中缀
#include<iostream>
#include<stack>
#include<string>
#include<map>
#include<cctype>
using namespace std;
//中缀转后缀
class IndixToPostfix
{
private:
	//运算符优先级
	map<char, int>precedence =
	{
		{'+',1},{'-',1},{'*',2},{'/',2},{'^',3}
	};
	bool isOperator(char c)
	{
		return precedence.count(c);
	}
	bool isOperand(char c)
	{
		return isalnum(c) || c == '.';
	}
public:
	string convert(const string& infix)
	{
		stack<char>opstack;
		string postfix;

		for (size_t i = 0; i < infix.length(); ++i)
		{
			char c = infix[i];

			if (c == ' ')continue;

			if (isOperand(c))
			{
				postfix += c;
				while (i + 1 < infix.length() && isOperand(infix[i + 1]))
				{
					postfix += infix[++i];
				}
				postfix += ' ';
			}
			else if (c == '(')
			{
				opstack.push(c);
			}
			else if (c == ')')
			{
				while (!opstack.empty() && opstack.top() != '(')
				{
					postfix += opstack.top();
					postfix += ' ';
					opstack.pop();
				}
				if (!opstack.empty())opstack.pop();
			}
			else if (isOperator(c))
			{
				while (!opstack.empty() && opstack.top() != '(' && precedence[opstack.top()] >= precedence[c])
				{
					if (c == '^' && opstack.top() == '^')break;
					postfix += opstack.top();
					postfix += ' ';
					opstack.pop();
				}
				opstack.push(c);
			}
		}
		while (!opstack.empty())
		{
			postfix += opstack.top();
			postfix += ' ';
			opstack.pop();
		}
		return postfix;
	}
};
class PostfixToInfix
{
private:
    map<char, int> precedence =
    {
        {'+',1},{'-',1},{'*',2},{'/',2},{'^',3}
    };

    bool isOperator(char c)
    {
        return precedence.count(c);
    }

    bool isOperand(char c)
    {
        return isalnum(c) || c == '.';
    }

    // 判断是否需要加括号
    bool needParentheses(const string& expr, char op, bool isLeft)
    {
        if (expr.length() <= 1) return false;

        char lastOp = expr[expr.length() - 1];
        if (!isOperator(lastOp)) return false;

        int currentPrec = precedence[op];
        int childPrec = precedence[lastOp];

        if (currentPrec > childPrec) return false;
        if (currentPrec < childPrec) return true;

        // 优先级相同
        if (op == '^') return isLeft;  // 幂运算是右结合的
        return !isLeft;  // 其他运算是左结合的
    }

public:
    string convert(const string& postfix)
    {
        stack<string> st;
        string operand;

        for (size_t i = 0; i < postfix.length(); ++i)
        {
            char c = postfix[i];

            if (c == ' ') continue;

            if (isOperand(c))
            {
                operand = c;
                while (i + 1 < postfix.length() && isOperand(postfix[i + 1]))
                {
                    operand += postfix[++i];
                }
                st.push(operand);
            }
            else if (isOperator(c))
            {
                if (st.size() < 2)
                {
                    throw runtime_error("Invalid postfix expression");
                }

                string right = st.top(); st.pop();
                string left = st.top(); st.pop();

                // 处理左操作数的括号
                if (needParentheses(left, c, true))
                {
                    left = "(" + left + ")";
                }

                // 处理右操作数的括号
                if (needParentheses(right, c, false))
                {
                    right = "(" + right + ")";
                }

                st.push(left + " " + c + " " + right);
            }
        }

        if (st.size() != 1)
        {
            throw runtime_error("Invalid postfix expression");
        }

        return st.top();
    }
};