#include <iostream>
#include <cstdlib>


using namespace std;

char up[3];
char down[3];
char lleft[3];
char rright[3];

typedef int X;
typedef int Y;
typedef int Z;

typedef struct node
{
    X x;
    Y y;
    Z z;
    struct node *link;

    friend ostream &operator<< (ostream &o, node &t)
    {
        return o << "(" << t.x << "," << t.y << "," << t.z << ")";
    }

} LinkNode, *SeqStack;

struct Stack
{
    node *top = nullptr;
    void push(X value, Y Value, Z valuE)
    {
        node *p = new node;
         
        p -> x = value;
        p -> y = Value;
        p -> z = valuE;

        p -> link = top;
        top = p;
    }
    void pop(X &value, Y &Value, Z &valuE)
    {
        if (top == nullptr)
        {
            cout << "satck empty!\n" ;
            exit(1);
        }
        value = top -> x;
        Value = top -> y;
        valuE = top -> z;

        node *p = top;
        top = top -> link;
        
        // delete p;
    }
    Stack()
    {
        top = nullptr;
    }
    void top1(X &value, Y &Value, Z &valuE)
    {
        if (top == nullptr)
        {
            cout <<"stack empty!\n" ;
            exit(1);
        }
        value = top -> x;
        Value = top -> y;
        valuE = top -> z;
    }


};

int maze[10][10] = {
    {1,0,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1},
};

int biaoji[10][10]={
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
};

bool pd[10][10] = {{false}};
// for (int i = 0;i<10;i++)
// {
//     for(int j =0;j<10;j++)
//     {
//         cout<< biaoji[i][j]<<' '<<endl;
//     }
// }


void shuchu()
{
    
    up[0] = 0xA1;
    up[1] = 0xFC;
    
    down[0] = 0xA1;
    down[1] = 0xFD;
    
    lleft[0] = 0xA1;
    lleft[1] = 0xFB;
    
    rright[0] = 0xA1;
    rright[1] = 0xFA;
    // cout<<up<<" "<<down<<" "<<lleft<<" "<<rright<<endl;
    cout <<"Recursion:"<<endl;

    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         cout<< biaoji[i][j] << " ";
    //     }
    //     cout << " "<<endl;
    // }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (biaoji[i][j] == -1)
            {
                cout << maze[i][j] << " ";
            }
            else
            {
                switch (biaoji[i][j])
                {
                case 0:
                    cout << up;
                    break;
                case 1:
                    cout << rright;
                    break;
                case 2:
                    cout << down;
                    break;
                case 3:
                    cout << lleft;
                }
            }

        }
        cout << " "<<endl;
    }
}
int num = 0;
bool dfs(int x, int y)
{
    // cout << x << ' ' << y << '\n';
    if (x == 8 && y == 9)
    {
        shuchu();
        num++;
        return true;
    }
    else
    {
        int xx = x + 1, yy = y;
        // cout << xx << ' ' << yy << '\n';
        if (0 <= xx &&xx < 10 && 10 > yy && yy >= 0)
        {
            if (maze[xx][yy] != 1)
            {
                if(pd[xx][yy] == false)
                {
                    
                    biaoji[x][y] = 2;
                    pd[xx][yy] = true;
                    dfs(xx, yy);
                    pd[xx][yy] = false;
                    biaoji[x][y] = -1;
                }
            }
            
        }
        xx = x - 1, yy = y;
        // cout << x << ' ' << y << ' ' << "112esds " <<  xx << ' ' << yy << '\n';
        if (0 <= xx &&xx < 10 && 10 > yy && yy >= 0)
        {
            if (maze[xx][yy] != 1)
            {
                if(pd[xx][yy] == false)
                {
                    
                    biaoji[x][y] = 0;
                    pd[xx][yy] = true;
                    dfs(xx, yy);
                    pd[xx][yy] = false;
                    biaoji[x][y] = -1;
                }
            }
            
        }
        xx = x , yy = y-1;
        // cout << xx << ' ' << yy << '\n';
        // cout << x << ' ' << y << ' ' << "112esds " <<  xx << ' ' << yy << '\n';

        if (0 <= xx &&xx < 10 && 10 > yy && yy >= 0)
        {
            if (maze[xx][yy] != 1)
            {
                if(pd[xx][yy] == false)
                {
                    
                    biaoji[x][y] = 3;
                    pd[xx][yy] = true;
                    dfs(xx, yy);
                    pd[xx][yy] = false;
                    biaoji[x][y] = -1;
                }
            }
            
        }
        xx = x, yy = y + 1;
        // cout << xx << ' ' << yy << '\n';
        if (0 <= xx &&xx < 10 && 10 > yy && yy >= 0)
        {
            if (maze[xx][yy] != 1)
            {
                if(pd[xx][yy] == false)
                {
                    
                    biaoji[x][y] = 1;
                    pd[xx][yy] = true;
                    dfs(xx, yy);
                    pd[xx][yy] = false;
                    biaoji[x][y] = -1;
                }
            }
            
        }
    }

    return false;
}

void test()
{
    Stack S;

    int xx = 0, yy = 1, zz;

    S.push(xx, yy, -1);

    pd[xx][yy] = true;
    while (S.top->x != 8 || S.top->y != 9)
    {

        S.top -> z ++;
        S.top1(xx,yy,zz);

        if (S.top -> z == 0)
        {
            if ( 1 <= xx && xx<10&& yy>=0 && yy<10)
            {

                if (maze[xx-1][yy] == 0 && pd[xx-1][yy] == false)
                {
                    xx -= 1 , yy = yy;
                    S.push(xx, yy, -1);

                    pd[xx][yy] = true;
                }
            }
        }
        if (S.top -> z == 1)
        {
            if ( 0 <= xx && xx<10&& yy>=0 && yy<9)
            {
                
                if (maze[xx][yy+1] == 0 && pd[xx][yy+1] == false)
                {
                    xx = xx , yy += 1;
                    S.push(xx, yy, -1);

                    pd[xx][yy] = true;
                }
            }
        }
        if (S.top -> z == 2)
        {
            if ( 0 <= xx && xx<9&& yy>=0 && yy<10)
            {
                if (maze[xx+1][yy] == 0 && pd[xx+1][yy] == false)
                {
                    xx += 1 , yy = yy;
                    // cout <<xx <<' '<< yy<<' ' <<endl; 
                    S.push(xx, yy, -1);
                    pd[xx][yy] = true;
                }
            }
        }
        if (S.top -> z == 3)
        {

            if ( 0 <= xx && xx<10&& yy>=1 && yy<10)
            {

                if (maze[xx][yy-1] == 0 && pd[xx][yy-1] == false)
                {
                    xx = xx , yy -= 1;
                    S.push(xx, yy, -1);

                    pd[xx][yy] = true;
                }
            }
        }
        if (S.top -> z == 4)
        {
            S.pop(xx, yy, S.top->z);
            pd[xx][yy] = true;
            // if (pd[xx-1][yy]== true )
            //     pd[xx-1][yy] = false;
            // if (pd[xx+1][yy]== true )
            //     pd[xx+1][yy] = false;
            // if (pd[xx][yy-1]== true )
            //     pd[xx][yy-1] = false;
            // if (pd[xx][yy+1]== true )
            //     pd[xx][yy+1] = false;
        }
        // cout <<xx <<' '<< yy <<" "<<S.top->z<<endl; 
        // cout <<'\n';
    }
    // cout <<'('<< S -> x << ','<< S -> y  << ',' << S -> z << ')' << endl;
    Stack S1;
    int xx1, yy1, zz1;
    while( S.top !=nullptr)
    {
        S.pop(xx1,yy1,zz1);
        S1.push(xx1,yy1,zz1);
    }
    cout << "Not Recursion:"<<endl;
    while( S1.top!=nullptr)
    {

        cout<< (*S1.top) << ',';
        S1.pop(xx1,yy1,zz1);
    }
    cout<< '\n';
}



int main()
{


    pd[0][1] = true;
    test();
    for (int i = 0;i<10;i++)
    {
        for(int j =0;j<10;j++)
        {
            pd[i][j] = false;
        }
    }
    pd[0][1] = true;
    dfs(0,1);
    // cout << num << endl;
    // shuchu();
    system("pause");
}
