#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Queen{
    public:
        bool Find(int n, int row, int col);
        bool Apply(int n, int row, int col);
        void Print(int n);
    private:
        vector <string> loc;
};

bool Queen::Apply(int n, int row, int col){
    /*Check Col*/
    for(int j = 0; j<n; j++){
        if(j==row) continue;
        if(loc[j*n+col]=="Q") return false;
    }
    /*Check Right Diagnol*/
    for(int i = row*n+col; i>0; i-=(n-1)){
        if(loc[i]=="Q") return false;
        if(i%n==n-1) break;
    }
    /*Check Left Diagnol*/
    for(int j = row*n+col; j>=0; j-=(n+1)){
        if(loc[j]=="Q") return false;
        if(j%n==0) break;
    }
    return true;
}

bool Queen::Find(int n, int row, int col){
    loc.resize(n*n,"-");
    //printf("row: %d, col: %d\n", row, col);
    //Print(n);
    /*Base Case*/
    if(row == n){
        if(count(loc.begin(), loc.end(), "Q")==n) return true;
        else{
            return false;
        }
    }

    if(col == n){
        if(count(loc.begin(), loc.end(), "Q")==n) return true;
        else{
            return false;
        }
    }

    /*Check the Queen's Position*/
    if(Apply(n, row, col)){
        loc[row*n+col] = "Q";
    }
    else{
        if(Find(n, row, col+1)){
            /*Check Status*/
            if(count(loc.begin(), loc.end(), "Q")==n) return true;
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }

    if(Find(n, row+1, 0)){
        return true;
    }
    else{
        loc[row*n+col] = "-";
        if(Find(n, row, col+1)){
            /*Do Nothing*/
        }
        else{
            return false;
        }
    }
    return true;
}

void Queen::Print(int n){
    cout<<" ";
    for(int i = 0; i<n; i++){
        cout<<"  "<<char(97+i);
    }
    cout<<endl;
    for(int i = 0; i<n; i++){
        cout<<n-i;
        for(int j = 0; j < n; j++){
            cout<<"  "<<loc[i*n+j];
        }
        cout<<endl;
    }
}

int main(){
    srand((unsigned int)time(NULL));
    Queen q;
    int n;
    
    cout<<"What is the size(n) of the board (n*n)? ";
    cin>>n;
    
    q.Find(n,0,rand()%n);
    q.Print(n);
    return 0;
}