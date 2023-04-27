#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
char stSymbol[100];   // 定义栈，用来存储终结符
char stSemantic[100]; // 语义栈
int top = -1;         // 初始栈顶指针
int i = 0;
static int count = 75; // 新建的符号的小标
int table[10][10] = {
    // +   -   *   /   ^   (   i  )  #
    {1, 1, -1, -1, -1, -1, -1, 1, 1},   //+
    {1, 1, -1, -1, -1, -1, -1, 1, 1},   //-
    {1, 1, 1, 1, -1, -1, -1, 1, 1},     //*
    {1, 1, 1, 1, -1, -1, -1, 1, 1},     // /
    {1, 1, 1, 1, -1, -1, -1, 1, 1},     //^
    {1, 1, 1, 1, 1, 2, 2, 1, 1},        //  (
    {-1, -1, -1, -1, -1, -1, -1, 0, 1}, // i
    {1, 1, 1, 1, 1, 2, 2, 1, 1},        //  )
    {-1, -1, -1, -1, -1, -1, -1, 2, 0}  //  #
};
// 1表示优先，-1表示落后，0表示同等，2表示不具可比性
//  判断是否为终结符
int IsVT(char str)
{
    if (str == '+' || str == '-' || str == '*' || str == '/' || str == '^' || str == '(' || str == 'i' || str == ')' || str == '#')
        return 1;
    return 0;
}
// 操作符判断
int IsOpe(char str)
{
    if (str == '+' || str == '-' || str == '*' || str == '/' || str == '^')
        return 1;
    return 0;
}
// 有字符判断该字符在table数组中的位置
int Index(char str)
{
    switch (str)
    {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '^':
        return 4;
    case 'i':
        return 5;
    case '(':
        return 6;
    case ')':
        return 7;
    case '#':
        return 8;
    }
    return 0;
}
int Compare(char top, char input)
{
    int i = Index(top);
    int j = Index(input);
    //	cout<<"table:"<<i<<","<<j<<endl;
    return table[i][j];
}
// 动作分析
string Action(char vt, char &s1, char &s2, int i, string &s3)
{
    string str;
    switch (vt)
    {
    case 'i':
        s1 = 'F';
        s2 = stSemantic[i];
        s3 = "1";
        return "";
    case '+':
        s1 = 'E';
        s2 = (char)count++;
        s3 = "2";
        str = "(+,";
        str += stSemantic[i - 1];
        str += ",";
        str += stSemantic[i + 1];
        str += ",";
        str += s2;
        str += ")";
        return str;
    case '-':
        s1 = 'E';
        s2 = (char)count++;
        s3 = "3";
        str = "(-,";
        str += stSemantic[i - 1];
        str += ",";
        str += stSemantic[i + 1];
        str += ",";
        str += s2;
        str += ")";
        return str;
    case '*':
        s1 = 'T';
        s3 = "4";
        s2 = count++;
        str = "(*,";
        str += stSemantic[i - 1];
        str += ",";
        str += stSemantic[i + 1];
        str += ",";
        str += s2;
        str += ")";
        return str;
    case '/':
        s1 = 'T';
        s2 = (char)count++;
        s3 = "5";
        str = "(/,";
        str += stSemantic[i - 1];
        str += ",";
        str += stSemantic[i + 1];
        str += ",";
        str += s2;
        str += ")";
        return str;
    case '^':
        s1 = 'F';
        s2 = (char)count++;
        s3 = "6";
        str = "(^,";
        str += stSemantic[i - 1];
        str += ",";
        str += stSemantic[i + 1];
        str += ",";
        str += s2;
        str += ")";
        return str;
    case ')':
        s1 = stSymbol[top - 1];
        s2 = stSemantic[i - 1];
        s3 = "7";
        return "";
    case '#':
        return "";
    }
    return "";
}
void Fenxi(char *input)
{
    cout << input << endl;
    input = input++;
    cout << input << endl;
    cout << "************************生成四元式的过程************************" << endl;
    cout << "输入串\t\t  符号栈\t  语义栈\t  生成四元式\t" << endl;
    char ch;
    char subInput;
    do
    {
        string sbSym = "", sbSem = "", sbTag3 = "";
        char sbTag1, sbTag2;
        if (IsVT(stSymbol[top]) == 1) // 栈顶符号1为终结符 9个符号:+-*/^i()#
            i = top;
        else
            i = top - 1; // 栈中相连的必有一个非终结符

        if (*input == '#')
        { // 取最后1个符号#，分析结束
            ch = *input;
        }
        else
        {
            subInput = input[0];      // 输入符的首字符
            if (IsOpe(subInput) == 0) // 不是操作符返回0，设置ch=‘i’
                ch = 'i';
            else
            {
                ch = subInput; // 操作符操作符+-* / ^ ，ch为操作符的1个
                subInput = '_';
            }
        }
        // 初始化栈	A+B*C-D/E#
        //		cout<<"优先级："<< Compare(stSymbol[i], ch)<<","<<stSymbol[i]<<","<<ch<<"top:"<<top<<endl;
        if (Compare(stSymbol[i], ch) == 0 || Compare(stSymbol[i], ch) == -1)
        {
            // i位置是终结符的下标，ch为 i ， 栈顶终结符低于或等于输入符号终结符时 ,入栈
            for (int j = 0; j <= top; j++)
            {
                sbSym += stSymbol[j];
                sbSem += stSemantic[j];
                //				cout<<"top:"<<top<<sbSym<<","<<sbSem<<endl;
            }
            if (ch != '#')
            {
                cout << setw(10) << input << setw(12) << sbSym << setw(16) << sbSem << endl;
                stSymbol[++top] = ch;
                stSemantic[top] = subInput;
                //				cout<<"input:"<<input<<endl;
                //				input=input++;
                input = input + 1;
                //				cout<<"input:"<<input<<endl;
                //				cout<<input<<","<<stSymbol<<","<<stSemantic<<endl;
                continue;
            }
            else
            { // 只剩下'#'时
                cout << setw(10) << input << setw(12) << sbSym << setw(16) << sbSem << endl;
                return;
            }
        }
        else if (Compare(stSymbol[i], ch) == 2)
        {
            //			cout<<stSymbol[i]<<","<<ch<<endl;
            cout << "非法语句!!" << endl;
            return;
        }

        if (Compare(stSymbol[i], ch) == 1)
        {
            char com;
            int t = i;
            do
            { // 找出最左素短语
                com = stSymbol[t];
                if (IsVT(stSymbol[t - 1]) == 1)
                    t = t - 1;
                else
                    t = t - 2;
            } while (Compare(stSymbol[t], com) == 0);

            for (int j = 0; j <= top; j++)
            {
                sbSym += stSymbol[j]; // 栈中内容
                sbSem += stSemantic[j];
            }
            string temp;
            temp = Action(stSymbol[i], sbTag1, sbTag2, i, sbTag3);
            cout << setw(10) << input << setw(12) << sbSym << setw(16) << sbSem << setw(16) << temp << endl;
            top = t + 1;
            stSymbol[top] = sbTag1;   // 规约入栈
            stSemantic[top] = sbTag2; // 语义入栈
        }
    } while (ch != '#' || top > 0);
}
int main()
{
    // 初始化栈	A+B*C-D/E#
    stSymbol[++top] = '#';
    stSemantic[top] = '_';

    char input[30];
    //	char input[30]={"A+B*C-D/E#"};
    cout << "************************请输入要检验的输入串(以#结束):*************************" << endl;
    cout << "************************此程序仅限于输入不含'(',')'的输入串:*******************" << endl;
    //	cin>>input;
    //	input=input++;

    Fenxi(input);
    return 1;
}