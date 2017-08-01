#include <iostream>
#include <stack>
#include <sstream>

using namespace std;
string postfix_to_prefix(const string & postfix);

int main()
{
    cout << postfix_to_prefix(string("3 4 +")) << endl;
    cout << postfix_to_prefix(string("10 5 / 4 +")) << endl;
    cout << postfix_to_prefix(string("10 5 / 2 3 * +")) << endl;
    cout << postfix_to_prefix(string("3 10 5 / + 2 3 * -")) << endl;
    cout << postfix_to_prefix(string("2 3 * 10 2 / + 7 * 6 3 + 6 3 * * 2 + -")) << endl;

    return 0;
}

    string postfix_to_prefix(const string & postfix)
    {
        istringstream is(postfix);
        string token;
        string current;
        string ans;
        int whole_nums = 0;

        stack<string> s;

        while (is >> token)
        {
            stack<string> garb;
            switch(token[0])
            {
                case '+':
                case '-':
                case '/':
                case '*':
                    //check whole number count
                    if (whole_nums == 2)
                    {
                        //add to beginning of stack
                        //delete excess w's
                        while(!s.empty())
                        {
                            garb.push(s.top());
                            s.pop();
                        }
                        s.push(token);
                        while(!garb.empty())
                        {
                            if (garb.top() != " ")
                            s.push(garb.top());
                            garb.pop();
                        }
                        s.push(" ");
                        --whole_nums;


                    }
                    else if (whole_nums > 2)
                    {
                        int wholes_passed = 0;
                        while (wholes_passed < 3)
                        {
                            if (wholes_passed == 2 && s.top() == " ")
                            {
                                ++wholes_passed;
                            }
                            else
                            {
                                if (s.top() == " ")
                                ++wholes_passed;

                                garb.push(s.top());
                                s.pop();
                            }
                        }
                        garb.push(token);
                        while(!garb.empty())
                        {
                            if (garb.top() != " ")
                                s.push(garb.top());

                            garb.pop();
                        }
                        s.push(" ");

                        --whole_nums;

                        //go two wholes back and add to stack
                        //delete the wholes that you just traversed
                    }
                    break;
                case ' ':
                    break;
                default:
                    s.push(token);
                    s.push(" ");
                    ++whole_nums;

            }


        }
        stack<string> copy;
        s.pop();
        while(!s.empty())
        {
            copy.push(s.top());
            s.pop();
        }
        while(!copy.empty())
        {
            ans += copy.top();
            ans += " ";
            copy.pop();
        }
        return ans;

    }
