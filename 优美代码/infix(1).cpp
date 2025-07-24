#include <bits/stdc++.h>
using namespace std;

const int StackSize = 10000; //栈容量
const int Error = 2e9;
int OPTR_top = -1, OPND_top = -1; //操作符栈顶、操作数栈顶
char OPTR[StackSize]; //操作符栈
int OPND[StackSize];  //操作数栈

//计算栈内操作符的优先级
int isp(char ch){
    if( ch == '#') return 0;
    else if( ch == '(') return 1;
    else if( ch == '^') return 7;
    else if( ch == '*' || ch == '/' || ch == '%') return 5;
    else if( ch == '+' || ch == '-') return 3;
    else if( ch == ')') return 8;
    else return -1;
}

//计算栈外操作符的优先级
int icp(char ch){
    if( ch == '#') return 0;
    else if( ch == '(') return 8;
    else if( ch == '^') return 6;
    else if( ch == '*' || ch == '/' || ch == '%') return 4;
    else if( ch == '+' || ch == '-') return 2;
    else if( ch == ')') return 1;
    else return -1;
}

//计算中缀算式表达式的值
int Cal(string s){
    OPTR_top = -1;
    OPND_top = -1;

    OPTR[++OPTR_top] = '#';

    int now;
    char ch;
    for( int i = 0; i < (int)s.size(); i++){
        if ( isdigit(s[i])){    //遇到一个数字，则将连着的数字转化为整数
            now = 0;
            int j;
            for ( j = i; isdigit(s[j]); j++){
                now = now * 10 + s[j] - '0';
            }
            if ( OPND_top == StackSize - 1){
                cout << "栈溢出" << endl;
                return Error;
            }
            OPND[++OPND_top] = now;
            i = j - 1;
        }
        else{
            //比较栈顶操作符和栈外操作符的优先级
            while(icp(s[i]) < isp(OPTR[OPTR_top])){  
                ch = OPTR[OPTR_top--];
                int a2 = OPND[OPND_top--];
                int a1 = OPND[OPND_top--];
                if (ch == '+') a1 += a2;
                else if (ch == '-') a1 -= a2;
                else if (ch == '*') a1 *= a2;
                else if (ch == '/'){
                    if( a2 != 0) a1 /= a2 ;
                    else {
                        cout << "除数不合法" << endl;
                        return Error;
                    }
                }
                else if (ch == '%'){
                    if( a2 != 0) a1 %= a2;
                    else{
                        cout << "模数不合法" << endl;
                        return Error;
                    } 
                }
                else if (ch == '^'){
                    if( a2 > 0){
                        int res = 1;
                        while (a2){
                            if( a2 & 1) res = res * a1;
                            a2 >>= 1;
                            a1 *= a1;
                        }
                        a1 = res;
                    }
                    else{
                        cout << "幂次不合法" << endl;
                        return Error;
                    } 
                }
                else{
                    cout << "输入不合法" << endl;
                    return Error;
                }
                OPND[++OPND_top] = a1;
            }

            if (icp(s[i]) == isp(OPTR[OPTR_top])){
                if ( OPTR[OPTR_top] == '(') OPTR_top--;
                else break; //此时为两个'#'相遇，直接退出
            } 
            else OPTR[++OPTR_top] = s[i];
        }
    }
    return OPND[OPND_top];
}

int main(){
    string s;
    //输入格式为 中缀算式表达式+'#'
    //如： 10-(2+3)*(4-1)+8/2#
    while ( getline( cin, s)){
        if(Cal(s) != Error){
            cout << Cal(s) << '\n';
        }
    }
    return 0;
}




