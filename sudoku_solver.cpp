#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct Pair{int a, b;};

vector<vector<char>> givenBoard = {{'.','.','.','2','.','.','.','6','3'},{'3','.','.','.','.','5','4','.','1'},{'.','.','1','.','.','3','9','8','.'},{'.','.','.','.','.','.','.','9','.'},{'.','.','.','5','3','8','.','.','.'},{'.','3','.','.','.','.','.','.','.'},{'.','2','6','3','.','.','5','.','.'},{'5','.','3','7','.','.','.','.','8'},{'4','7','.','.','.','1','.','.','.'}};

int getPoss(bool A[9]){
    int c = 0,r;
    for(int i=0;i<9;i++){
        if(!A[i]){c++;r = i;}
        if(c==2)return -1;
    }
    return r;
}
bool rowFilled[9][9] = {};
bool colFilled[9][9] = {};
bool boxFilled[3][3][9] = {};

void printBools(bool IMP[9][9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(givenBoard[i][j]!='.'){
                cout << "         ";
            }else{
                for(int k=0;k<9;k++){
                    cout << IMP[i][j][k];
                }
            }
            cout << ' ';
        }
        cout << "- ";
        for(int j=0;j<9;j++){
            cout << rowFilled[i][j];
        }
        cout << '\n';
    }
    cout << "\n\n";
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << colFilled[i][j];
        }
        cout << ' ';
    }
    cout << "\n\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<9;k++){
                cout << boxFilled[i][j][k];
            }
            cout << ' ';
        }
        cout <<  '\n';
    }
}

void printBoard(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << givenBoard[i][j];
        }
        cout << '\n';
    }
    cout << '\n' ;
}

Pair findMinPossSq(vector<vector<char>> &board,bool IMP[9][9][9]){
    Pair min = {-1,-1};
    int minCount=10,count;
    for(int i=0;i<9 && minCount>2;i++){
        for(int j=0;j<9 && minCount>2;j++){
            if(board[i][j]=='.'){    
                count=0;
                for(int k=0;k<9;k++){
                    if(!IMP[i][j][k]) count++;
                }
            }
            if(count<minCount){
                min = {i,j};
                minCount  = count;
            }
        }
    }
    return min;
}

bool solved = false;

void solve(vector<vector<char>> &board){
    bool IMP[9][9][9] = {};
    
    int fin=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<9;k++){
                IMP[i][j][k] = false;
            }
            rowFilled[i][j] = false;
            colFilled[i][j] = false;
            boxFilled[i/3][i%3][j] = false;        
        }
    }
    queue<Pair> Q;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(board[i][j]!='.')Q.push({i,j});
        }
    }
    
    Pair curr;
    do{
        while(!Q.empty()){
            fin++;
            curr = Q.front();
            Q.pop();

            rowFilled[curr.a][board[curr.a][curr.b]-'1'] = true;
            colFilled[curr.b][board[curr.a][curr.b]-'1'] = true;
            boxFilled[curr.a/3][curr.b/3][board[curr.a][curr.b]-'1'] = true;

            for (int i = 0; i < 9; i++)
            {
                if(board[curr.a][i]=='.'){
                    IMP[curr.a][i][board[curr.a][curr.b]-'1'] = true;
                }
            }

            for (int i = 0; i < 9; i++)
            {
                if(board[i][curr.b]=='.'){
                    IMP[i][curr.b][board[curr.a][curr.b]-'1'] = true;
                }
            }

            for (int i = (curr.a/3)*3; i < (curr.a/3)*3+3; i++)
            {
                for (int j = (curr.b/3)*3; j < (curr.b/3)*3+3; j++)
                {
                    if(board[i][j]=='.'){
                        IMP[i][j][board[curr.a][curr.b]-'1'] = true;
                    }
                }
            }
                
        }
        
        bool nextLoop = false;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if(board[i][j]=='.'){
                    int r = getPoss(IMP[i][j]);
                    if(r!=-1){
                        board[i][j] = r+'1';
                        Q.push({i,j});
                        nextLoop = true;
                    }
                }
            }
        }

        for(int i=0;i<9 && !nextLoop;i++){
            for(int j=0;j<9  && !nextLoop;j++){
                if(!colFilled[i][j]){
                    int r=-1;
                    for(int k=0;k<9;k++){
                        if(board[k][i]=='.' && !IMP[k][i][j]){
                            if(r==-1)r=k;
                            else{
                                r=-1;break;
                            }
                        }
                    }
                    if(r!=-1){
                        board[r][i] = j+'1';
                        Q.push({r,i});
                        nextLoop = true;
                    }
                }
            }
        }

        for(int i=0;i<9 && !nextLoop;i++){
            for(int j=0;j<9 && !nextLoop;j++){
                if(!rowFilled[i][j]){
                    int r=-1;
                    for(int k=0;k<9;k++){
                        if(board[i][k]=='.' && !IMP[i][k][j]){
                            if(r==-1)r=k;
                            else{
                                r=-1;break;
                            }
                        }
                    }
                    if(r!=-1){
                        board[i][r] = j+'1';
                        Q.push({i,r});
                        nextLoop = true;
                    }
                }
            }
        }

        for(int i1=0;i1<3 && !nextLoop;i1++){
            for(int i2=0;i2<3 && !nextLoop;i2++){
                for(int j=0;j<9 && !nextLoop;j++){
                    if(!boxFilled[i1][i2][j]){
                        int r1=-1,r2=-1;
                        for(int k1=i1*3;k1<i1*3+3 && r2!=-2;k1++){
                            for(int k2=i2*3;k2<i2*3+3;k2++){
                                if(board[k1][k2]=='.' && !IMP[k1][k2][j]){
                                    if(r1==-1){
                                        r1=k1;
                                        r2=k2;
                                    }else{
                                        r1=-1;r2=-2;break;
                                    }
                                }
                            }
                        }
                        if(r1!=-1){
                            board[r1][r2] = j+'1';
                            Q.push({r1,r2});
                            nextLoop = true;
                        }
                    }
                }
            }
        }

    
        printBoard();
    }while(!Q.empty());

    cout << "________________________\n";
    printBoard();
    printBools(IMP);
    cout << fin << endl;

    Pair min = findMinPossSq(board,IMP);
    cout << min.a << min.b << endl;

    vector<vector <char>> currBoard = board;

    bool allFilled = true;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            allFilled = allFilled && rowFilled[i][j];
            allFilled = allFilled && colFilled[i][j];
            allFilled = allFilled && boxFilled[i/3][i%3][j];        
        }
    }
    if(fin==81 && allFilled)solved = true;
    for(int i=0;i<9 && fin<81 && !solved && min.a!=-1;i++){
        if(!IMP[min.a][min.b][i]){
            board = currBoard;
            board[min.a][min.b] = i+'1';
            solve(board);
        }
    }
    

}

int main(){
    solve(givenBoard);
    // printBoard();
}