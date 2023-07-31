/*Voltorb Flip*/
#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <limits>
using namespace std;

void Game(int level, int coins, int collected, vector<string> display, vector<int> board, int mode);
void Assign(vector<int> &board, int level);

int main(){
    srand((unsigned int) time(NULL));
    int level = 1;
    int coins = 0;              //Coins colleted in total
    int collected = 0;          //Coins colleted in the level
    int row = 0, col = 0;       //User input row and col
    bool status = true;         //Check Game ends or not
    int mode;                   //select mode for display; 0 to not show, 1 to show
    stringstream ss;

    vector <int> board;
    vector <string> display;
    vector <int> choice;
    
    while(true){
        collected = 0;
        status = true;
        board.clear();
        display.clear();
        choice.clear();
        
        for(int b = 0; b<25; b++){
            board.push_back(1);
        }
        for(int d = 0; d<25; d++){
            display.push_back("?");
        }
        
        /*Randomly Assign*/
        Assign(board, level);
        cout<<"Ready to Play VOLTORB Flip Lv. "<<level<<"!"<<'\n'<<'\n';
        sleep(1);
        
        while(true){
            /*Display board*/
            Game(level, coins, collected, display, board, 0);

            /*User input*/
            do{
                if(!cin){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
                cout<<"Enter Row(0-4) and Column(0-4): ";
                cin>>row>>col;
            }while(!cin||row<0||row>4||col<0||col>4||display[row*5+col]!="?");
            
            cout<<'\n';
            choice.push_back(row*5+col);
            
            if(board[row*5+col]==0){
                cout<<"Oh no! You get 0 Coins!"<<'\n'<<'\n';
                sleep(1);
                status=false;
                /*Show Correct Answer*/
                Game(level, coins, collected, display, board, 1);
                cout<<'\n';
                sleep(1);
                break;
            }
            else{
                /*Change Display*/
                ss.clear();
                ss<<board[row*5+col];
                display[row*5+col].clear();
                ss>>display[row*5+col];

                /*Assign Coin*/
                if(collected==0) collected+=board[row*5+col];
                else{
                    collected*=board[row*5+col];
                }
            }
            
            /*Check whether game ends*/
            int checker = 0;//check 2s and 3s
            int match = 0;
            for(int c = 0; c < choice.size(); c++){
                if(board[choice[c]]==2||board[choice[c]]==3) checker++;
            }
            
            for(int b = 0; b < board.size(); b++){
                if(board[b]==2||board[b]==3) match++;
            }
            
            if(match==checker) break;
        }
        if(!status){
            /*User Lost*/
            int temp = level;
            if(choice.size()>level){/*Keep Level*/}
            else if(choice.size()<=level && choice.size()>2) level = choice.size()-1;
            else{
                level = 1;
            }
            if(temp>level){
                cout<<"Dropped to Game Lv. "<<level<<'\n'<<'\n';
                sleep(1);
            }
        }
        else{
            /*User Win*/
            cout<<"Game Clear! You received "<<collected<<" Coins!"<<'\n'<<'\n';
            sleep(1);
            /*Show Answer*/
            Game(level, coins, collected, display, board, 1);
            sleep(1);
            coins += collected;
            if(level<8){
                level++;
                cout<<"\nAdvanced to Game Lv. "<<level<<"!"<<'\n'<<'\n';
                sleep(1);
            }
        }
    }
    return 0;
}

/*Display board*/
void Game(int level, int coins, int collected, vector<string> display, vector<int> board, int mode){
    int sum = 0;        //Display Sum of Row or Cols
    int voltorb = 0;    //Display Number of Voltorbs
    
    cout<<"Lv. "<<level<<"  Coins: "<<coins<<"  Collected: "<<collected<<'\n'<<'\n';
    
    for(int i = 0; i < 25; i++){
        sum+=board[i];
        if(board[i]==0) voltorb++;
        
        if(mode==0) cout<<display[i]<<"   ";
        else if(mode==1) cout<<board[i]<<"   ";
        
        /*Line Change*/
        if((i+1)%5==0){
            cout<<"| "<<sum<<" ; "<<voltorb<<'\n';
            sum = 0;
            voltorb = 0;
        }
    }
    cout<<"--------------------"<<'\n';
    
    for(int j = 0; j < 5; j++){
        int temp = 0;
        for(int k = 0; k < 5; k++){
            temp += board[j+5*k];
        }
        cout<<temp<<"   ";
    }
    cout<<'\n';
    
    for(int j = 0; j < 5; j++){
        int temp_v = 0;
        for(int k = 0; k < 5; k++){
            if(board[j+5*k]==0) temp_v++;
        }
        cout<<temp_v<<"   ";
    }
    cout<<'\n';
}

/*Randomly Assign 2s,3s, and Voltorbs on the board*/
void Assign(vector<int> &board, int level){
    int temp;
    int rn = rand()%5;
    int w = 0, h = 0, o = 0; //Number of 2s, 3s, and Voltorbs
    
    if(level==1){
        if(rn == 0){
            w = 3; h = 1; o = 6;
        }
        else if(rn==1){
            w = 0; h = 3; o = 6;
        }
        else if(rn==2){
            w = 5; h = 0; o = 6;
        }
        else if(rn==3){
            w = 2; h = 2; o = 6;
        }
        else if(rn==4){
            w = 4; h = 1; o = 6;
        }
    }
    else if(level==2){
        if(rn == 0){
            w = 1; h = 3; o = 7;
        }
        else if(rn==1){
            w = 6; h = 0; o = 7;
        }
        else if(rn==2){
            w = 3; h = 2; o = 7;
        }
        else if(rn==3){
            w = 0; h = 4; o = 7;
        }
        else if(rn==4){
            w = 5; h = 1; o = 7;
        }
    }
    else if(level==3){
        if(rn==0){
            w = 2; h = 3; o = 8;
        }
        else if(rn==1){
            w = 7; h = 0; o = 8;
        }
        else if(rn==2){
            w = 4; h = 2; o = 8;
        }
        else if(rn==3){
            w = 1; h = 4; o = 8;
        }
        else if(rn==4){
            w = 6; h = 1; o = 8;
        }
    }
    else if(level==4){
        if(rn==0){
            w = 3; h = 3; o = 8;
        }
        else if(rn==1){
            w = 0; h = 5; o = 8;

        }
        else if(rn==2){
            w = 8; h = 0; o = 10;

        }
        else if(rn==3){
            w = 5; h = 2; o = 10;

        }
        else if(rn==4){
            w = 2; h = 4; o = 10;
        }
    }
    else if(level==5){
        if(rn==0){
            w = 7; h = 1; o = 10;
        }
        else if(rn==1){
            w = 4; h = 3; o = 10;
        }
        else if(rn==2){
            w = 1; h = 5; o = 10;
        }
        else if(rn==3){
            w = 9; h = 0; o = 10;
        }
        else if(rn==4){
            w = 6; h = 2; o = 10;
        }
    }
    else if(level==6){
        if(rn==0){
            w = 3; h = 4; o = 10;
        }
        else if(rn==1){
            w = 0; h = 6; o = 10;
        }
        else if(rn==2){
            w = 8; h = 1; o = 10;
        }
        else if(rn==3){
            w = 5; h = 3; o = 10;
        }
        else if(rn==4){
            w = 2; h = 5; o = 10;
        }
    }
    else if(level==7){
        if(rn==0){
            w = 7; h = 2; o = 10;
        }
        else if(rn==1){
            w = 4; h = 4; o = 10;
        }
        else if(rn==2){
            w = 1; h = 6; o = 13;
        }
        else if(rn==3){
            w = 9; h = 1; o = 13;
        }
        else if(rn==4){
            w = 6; h = 3; o = 10;
        }
    }
    else if(level==8){
        if(rn==0){
            w = 0; h = 7; o = 10;
        }
        else if(rn==1){
            w = 8; h = 2; o = 10;
        }
        else if(rn==2){
            w = 5; h = 4; o = 10;
        }
        else if(rn==3){
            w = 2; h = 6; o = 10;
        }
        else if(rn==4){
            w = 7; h = 3; o = 10;
        }
    }
    /*Assign 2s, 3s, and Voltorbs*/
    if(w>0){
        for(int i = 0; i < w; i++){
            while(true){
                temp = rand()%25;
                if(board[temp]==1){
                    board[temp]=2;
                    break;
                }
            }
        }
    }

    if(h>0){
        for(int j = 0; j < h; j++){
            while(true){
                temp = rand()%25;
                if(board[temp]==1){
                    board[temp]=3;
                    break;
                }
            }
        }
    }

    if(o>0){
        for(int k = 0; k < o; k++){
            while(true){
                temp = rand()%25;
                if(board[temp]==1){
                    board[temp]=0;
                    break;
                }
            }
        }
    }
}