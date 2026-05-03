#endif
#include <iostream>
#include "GameManager.h"

using namespace std;

void GameManager::run(){
    int choice;

    do{
        board.displayBoard();

        cout<<"\n1.Answer 2.Check 3.Reset 4.Inspect 5.Exit\n";
        cin>>choice;

        if(choice==1){
            string p; int v;
            cin>>p>>v;
            board.setCell(p,v);
        }
        else if(choice==2){
            cout<<(board.checkSolved()?"Solved!\n":"Not yet!\n");
        }
        else if(choice==3){
            board.resetBoard();
        }
        else if(choice==4){
            string p; cin>>p; 
            board.inspect(p);
        }

    }while(choice!=5);

    cout<<"Exit\n";
}


