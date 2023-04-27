#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

// 关键字
string key[6] = {"main", "int", "if", "else", "while", "do"};
// 关键字的种别码
int keyNum[6] = {1, 2, 3, 4, 5, 6};
// 运算符和界符
string symbol[17] = {"<", ">", "!=", ">=", "<=", "==", ",", ";", "(", ")", "{", "}", "+", "-", "*", "/", "="};
// char symbol[12]={'<','>','!=','>=','<=','==',',',';','(',')','{','}'};
// 运算符和界符的种别码
int symbolNum[17] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
// 存放文件取出的字符
string letter[1000];
// 将字符转换为单词
// string  words[1000];
char words[1000] = {' '};
int length; // 保存程序中字符的数目
int num;

int isSymbol(string s)
{ // 判断运算符和界符
    int i;
    for (i = 0; i < 17; i++)
    {
        if (s == symbol[i])
            return symbolNum[i];
    }
    return 0;
}

// 判断是否为数字
bool isNum(string s)
{
    if (s >= "0" && s <= "9")
        return true;
    return false;
}

// 判断是否为字母
bool isLetter(string s)
{
    if (s >= "a" && s <= "z")
        return true;
    return false;
}

// 判断是否为关键字,是返回种别码
int isKeyWord(string s)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        if (s == key[i])
            return keyNum[i];
    }
    return 0;
}

// 返回单个字符的类型
int typeword(string str)
{
    if (str >= "a" && str <= "z") //   字母
        return 1;

    if (str >= "0" && str <= "9") // 数字
        return 2;

    if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" || str == "{" || str == "}" || str == "+" || str == "-" || str == "*" || str == "/") // 判断运算符和界符
        return 3;
    if (str == " ")
    {
        //    	cout<<"空格"<<endl;
        return 4;
    }
}

string identifier(string s, int n)
{ // 字符连接 ，n是s字符在letter中下标 ,获得返回的字符串
    int j = n + 1;
    int flag = 1;
    while (flag)
    {
        if (isNum(letter[j]) || isLetter(letter[j]))
        {                                // 提取位置n的下个字符，并使用函数isNum和isLetter分别进行判断是数字或字母
            s = (s + letter[j]).c_str(); // 是数字或字母时 进行字符连接，c_str是String类中的一个函数，它返回当前字符串的首字符地址。
            // 连接以后直接判断是否是关键字，是否有问题
            j++;
        }
        else
        {
            flag = 0;
        }
    }
    num = j; // 下一个字符位置
    return s;
}

string symbolStr(string s, int n)
{
    int j = n + 1;
    string str = letter[j];
    if (str == ">" || str == "=" || str == "<" || str == "!")
    { // 双目运算符
        s = (s + letter[j]).c_str();
    }
    num = j;
    return s;
}

string Number(string s, int n)
{
    int j = n + 1;
    int flag = 1;

    while (flag)
    {
        if (isNum(letter[j]))
        {
            s = (s + letter[j]).c_str();
            j++;
        }
        else
        {
            flag = 0;
        }
    }

    num = j;
    return s;
}

void print(string s, int n)
{
    cout << "(" << s << "," << n << ")" << endl;
}

void TakeWord()
{ // 取单词
    int k;
    for (num = 0; num < length;)
    {
        string str1, str;
        str = letter[num]; // 提取num位置的字符

        k = typeword(str);
        switch (k)
        {
        case 1: // 如果是字母
        {
            str1 = identifier(str, num);
            int val = isKeyWord(str1);
            cout << "标识符---：" << num;
            print(str1, val); // 保留字val为非零值，标识符则为0
            break;
        }
        case 2:
        {
            cout << "数字开---：" << num;
            str1 = Number(str, num);
            print(str1, 24);
            break;
        }
        case 3:
        {
            cout << "符号---：" << num;
            str1 = symbolStr(str, num);
            print(str1, isSymbol(str1));
            break;
        }
        case 4:
        {
            num++;
            break;
        }
        }
    }
}

int main()
{
    char w;
    int i, j, n;
    freopen("s.c", "r", stdin);
    n = 0;
    while ((w = cin.get()) != EOF)
    {
        words[n] = w;
        n++;
    }
    cout << "长度：" << n << endl;

    for (j = 0; j < n; j++)
    {
        if (words[j] == '\n' || (int)words[j] < 32)
        {
            words[j] = ' ';
            //			cout<<j<<"回车符"<<endl;
        }
    }
    int temp = 0;
    for (j = 0; j < n; j++)
    {
        if (words[j] == ' ')
        {
            if (words[j + 1] != ' ')
            {
                letter[temp] = words[j];
                temp++;
            }
            else
            {
                //				cout<<"连续空格"<<endl;
                continue;
            }
        }
        else
        {
            letter[temp] = words[j];
            temp++;
        }
    }
    cout << "-----" << temp << endl;
    freopen("result.txt", "w", stdout); // 从控制台输出，而不是文本输出
    length = temp;

    //    while(cin>>w){
    //        if(w!=' '){//字符串是以回车作为结束标记 ，W是一个字符类型
    //            letter[length]=w;
    //            length++;
    //        }   //去掉程序中的空格
    //    }

    //
    //    cout<<length<<endl;
    //  for(j=0;j<length;j++){
    //      cout<<j<<":"<<words[j]<<endl;
    //  }

    TakeWord();
    //  for(j=0;j<length;j++){
    //      cout<<letter[j]<<endl;
    //  }
    fclose(stdin);  // 关闭文件
    fclose(stdout); // 关闭文件
    return 0;
}
