#include <iostream>
using namespace std;

int geti(int k,int n){
    return k/n;
}

int getj(int k,int n){
    return k%n;
}

int getk(int i,int j,int n){
    return i*n+j;
}

void disp2d(float A[], int m, int n){
    cout << (char)218 << "\t";
    for (int j = 0; j < n; j++)
    {
        cout << "\t";
    }
    cout << (char)191 << endl;
    for (int i = 0; i < m; i++)
    {
        cout << (char)179 << "\t";
        for (int j = 0; j < n; j++)
        {
            cout << A[getk(i,j,n)] << "\t";
        }
        cout << (char)179;
        cout << endl;
    }
    cout << (char)192 << "\t";
    for (int j = 0; j < n; j++)
    {
        cout << "\t";
    }
    cout << (char)217 << endl;
    cout << endl;
}

void setCopy(float A[],float B[], int m,int n){
    for (int i = 0; i < m*n; i++)
    {
        B[i] = A[i];
    }
}

void setPattern(float A[], int m,int n){
    for (int i = 0; i < m*n; i++)
    {
        A[i] = i+1;
    }
}

void setNull(float A[], int m,int n){
    for (int i = 0; i < m*n; i++)
    {
        A[i] = 0;
    }
}

void setIdentity(float A[], int n){
    setNull(A,n,n);
    for (int i = 0; i < n; i++)
    {
        A[getk(i,i,n)] = 1;
    }
}

void augment(float A[],float B[],float C[], int mA, int nA){
    for (int i = 0; i < mA; i++)
    {
        for (int j = 0; j < nA; j++)
        {
            C[getk(i,j,nA+1)] = A[getk(i,j,nA)];
        }
    }
    for (int j = 0; j < mA; j++)
    {
        C[getk(j,nA,nA+1)] = B[j];
    }
    // disp2d(C,mA,nA+1);
}

void unaugment(float A[],float B[], int mA, int nA){
    for (int j = 0; j < mA; j++)
    {
        B[j] = A[getk(j,3,nA+1)] ;
    }
    // disp2d(B,mA,1);
}

float multRC(float A[],int mA, int nA, float B[],int mB, int nB, int rA, int cB){
    float sum = 0;
    if(nA!=mB){cout << "Not possible"; return 0;}
    for (int i = 0; i < nA; i++)
    {
        sum += A[getk(rA,i,nA)]*B[getk(i,cB,nB)];
    }
    return sum;
}

void matMult(float A[],int mA, int nA, float B[],int mB, int nB,float C[],int mC, int nC){
    if(!(nA==mB && mC==mA && nC==nB)){
        cout << "Not possible";
        return;
    }
    for (int i = 0; i < mC; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            C[getk(i,j,nC)] = multRC(A,mA,nA,B,mB,nB,i,j);
        }
    }
}

void eopExch(float A[],int mA, int nA,int r1,int r2){
    float e[mA*mA];
    float C[mA*nA];
    setNull(e,mA,mA);
    for (int i = 0; i < mA; i++)
    {
        if (i!=r1 && i!=r2)
        {
            e[getk(i,i,mA)] = 1;
        }        
    }
    e[getk(r1,r2,mA)] = 1;
    e[getk(r2,r1,mA)] = 1;
    // disp2d(e,mA,mA);
    matMult(e,mA,mA,A,mA,nA,C,mA,nA);
    setCopy(C,A,mA,nA);
}

void eopAdd(float A[],int mA, int nA,float c1,int r1,float c2,int r2){
    float e[mA*mA];
    float C[mA*nA];
    setNull(e,mA,mA);
    if (c1==0)
    {
        cout << "c1 != 0";
        return;
    }
    for (int i = 0; i < mA; i++)
    {
        if (i!=r1)
        {
            e[getk(i,i,mA)] = 1;
        }        
    }
    e[getk(r1,r2,mA)] = c2;
    e[getk(r1,r1,mA)] = c1;
    // disp2d(e,mA,mA);
    matMult(e,mA,mA,A,mA,nA,C,mA,nA);
    setCopy(C,A,mA,nA);
}

int getLZeroes(float A[],int mA, int nA,int r){
    int l=0;
    while(A[getk(r,l,nA)]==0 && l<nA){l++;}
    return l;
}

float getPivot(float A[],int mA, int nA,int r){
    int l=0;
    while(A[getk(r,l,nA)]==0 && l<nA-1){l++;}
    return A[getk(r,l,nA)];
}

void sortByLZeroes(float A[],int mA,int nA){
    for (int i = 0; i < mA-1; i++)
    {
        for (int j = 0; j < mA-1-i; j++)
        {
            if (getLZeroes(A,mA,nA,j)>getLZeroes(A,mA,nA,j+1))
            {
                eopExch(A,mA,nA,j,j+1);
            }
        }
    }
}

void swapEle(float A[],int mA,int nA,int i1,int j1, int i2, int j2){
    float t = A[getk(i1,j1,nA)];
    A[getk(i1,j1,nA)] = A[getk(i2,j2,nA)];
    A[getk(i2,j2,nA)] = t;
}

void transpose(float A[],float B[], int m,int n){
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[getk(j,i,m)] = A[getk(i,j,n)];
            // disp2d(B,n,m);
        }
    }
    

}

void RRE(float A[],int mA, int nA){
    for (int i = 0; i < mA; i++)
    {
        sortByLZeroes(A,mA,nA);
        float p1 = getPivot(A,mA,nA,i);
        if(p1==0){break;}
        eopAdd(A,mA,nA,1.0/p1,i,0,0);
        // disp2d(A,mA,nA);
        for (int j = 0; j < mA; j++)
        {
            int lz = getLZeroes(A,mA,nA,i);
            if (j!=i && lz!=nA)
            {
                float p2 = A[getk(j,lz,nA)];
                eopAdd(A,mA,nA,1,j,-p2,i);
            }
            // disp2d(A,mA,nA);  
            
        }
        
    }
    
}

int rankMat(float A[],int mA, int nA){
    float temp1[mA*nA];
    setCopy(A,temp1,mA,nA);
    RRE(temp1,mA,nA);
    int r1 = mA-1;
    while (getPivot(temp1,mA,nA,r1)==0)
    {
        r1--;
    }
    
    float temp2[mA*nA];
    transpose(A,temp2,mA,nA);
    RRE(temp2,nA,mA);
    int r2 = nA-1;
    while (getPivot(temp2,nA,mA,r2)==0)
    {
        r2--;
    }

    if(mA>nA){
        return r2+1;
    }else{
        return r1+1;
    }
}

int main(){
    int mA=3,nA=3;
    float A[mA*nA];
    int mB=3,nB=3;
    float B[mB*nB];
    int mC=3,nC=3;
    float C[mC*nC];
    setPattern(A,mA,nA);
    setCopy(A,B,mA,nA);
    setNull(C,mC,nC);
    cout << "A:\n";
    disp2d(A,mA,nA);
    cout << "B:\n";
    disp2d(B,mB,nB);
    cout << "C:\n";
    disp2d(C,mC,nC);
    // cout << multRC(A,mA,nA,B,mB,nB,1,0);
    matMult(A,mA,nA,B,mB,nB,C,mC,nC);
    cout << "C = AB:\n";
    disp2d(C,mC,nC);
    eopExch(B,mB,nB,0,2);
    cout << "B:\n";
    disp2d(B,mB,nB);
    eopAdd(B,mB,nB,1,0,1,2);
    cout << "B:\n";
    disp2d(B,mB,nB);
    float D[100];
    setIdentity(D,10);
    // disp2d(D,10,10);
    eopExch(D,10,10,0,9);eopExch(D,10,10,1,8);eopExch(D,10,10,4,5);eopExch(D,10,10,2,7);eopExch(D,10,10,3,6);
    // disp2d(D,10,10);
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << getLZeroes(D,10,10,i) << " ";
    // }
    // cout << endl;
    sortByLZeroes(D,10,10);
    // disp2d(D,10,10);
    RRE(B,3,3);
    disp2d(B,3,3);
    float E[12] = {2,0,-6,-8,0,1,2,3,3,6,-2,-4};
    disp2d(E,3,4);
    RRE(E,3,4);
    disp2d(E,3,4);
    float F[12] = {0, 1, 5, -4, 1, 4, 3, -2, 2, 7, 1, -2};
    disp2d(F,3,4);
    RRE(F,3,4);
    disp2d(F,3,4);
    float FT[12] = {};
    transpose(F,FT,3,4);
    disp2d(FT,4,3);
    // disp2d(C,3,3);
    RRE(C,3,3);
    // disp2d(C,3,3);
    // cout << "rank" << rankMat(F,3,4);
    disp2d(E,3,4);
    float ET[12] = {};
    transpose(E,ET,3,4);
    disp2d(ET,4,3);
    // cout << "rank" << rankMat(FT,4,3);
    float P[9] = {2,5,2,3,-2,4,-6,1,-7};
    cout << "P:\n";
    disp2d(P,3,3);
    float Y[3] = {-38,17,-12};
    cout << "Y:\n";
    disp2d(Y,3,1);
    float PY[12] = {};
    augment(P,Y,PY,3,3);
    cout << "PaugY:\n";
    disp2d(PY,3,4);
    RRE(PY,3,4);
    cout << "PaugY(RRE):\n";
    disp2d(PY,3,4);
    float X[3] = {};
    unaugment(PY,X,3,3);
    cout << "X:\n";
    disp2d(X,3,1);
    
}