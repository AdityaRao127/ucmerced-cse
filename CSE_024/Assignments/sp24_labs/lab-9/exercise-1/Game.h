#ifndef GAME_H
#define GAME_H

#include "Square.h"
#include <iostream>
#include "Button.h"

class Game {
    Square **board;
    bool playerX;
    bool AI;
    Button up;
    Button right; 
    Button left;
    Button x;
    Button header; 
    Button AIThree; 
    Button AIFour; 
    Button AIFive; 
    Button HumanThree; 
    Button HumanFour; 
    Button HumanFive; 
    bool clickedBoard; 
    int count; 
    bool cleared; 
    bool xWin, oWin, aiWin, tie, reset; 
    bool newGame, endScreen;
    bool moved;
           bool horizontalWin;
        bool verticalWin;
            bool diag1Win;
    bool diag2Win;


    bool aiThree, aiFour, aiFive, humanThree, humanFour, humanFive; 

    void init(){
        board = new Square*[count];
        for (int i = 0; i < count; i++){
            board[i] = new Square[count];
        }

        float x = -0.9;
        float y = 0.9;

        float size = 1.8/count; 
        // Initialize your state variables
        for (int i = 0; i < count; i++){
            x = -0.9;
            for (int j = 0; j < count; j++){
                board[i][j] = Square(x, y, size);
                x += size;
            }
            y -= size;
        }
    }


    void AIMove() {
        if (!playerX) {
            moved=false;
            for (int i = 0; i < count && !moved; i++) {
                for(int j=0; j<count && !moved; j++){
                    if (board[i][j].isEmpty()) {
                        board[i][j].playO();
                        moved = true; 
                        break;
                    }
                }
            }
            if(moved){
            playerX = !playerX;
                          if (isBoardFull()) {
                        tie = true;
                        std::cout << "Draw" << std::endl;
                    }
            if(checkWin()){
                aiWin = true; 
                std::cout<<"ai win" << std::endl;
            }
   
            }
        }
    }



public:
    Game() {
        playerX = true;
        AI = false;

        aiThree = false; 
        aiFour = false; 
        aiFive = false; 
        humanThree = false; 
        humanFour = false; 
        humanFive = false; 
        cleared = false; 
        clickedBoard = false;
        xWin = false; 
        oWin = false; 
        aiWin = false; 
        tie = false;
        reset = false; 
        newGame = false;
        moved = false;
        endScreen = false;  
        horizontalWin = false;
        verticalWin = false;
        diag1Win = false;
        diag2Win = false;
        up = Button("Player X wins (1)!", -0.15, 1);
        right = Button("Click to Play Again!", 0, 0.5);
        left = Button("Exit Game", -0.9, 0.5);
        init(); 
    }
/* welcome page stuff */ 

    void welcome(){
        header = Button("Start Game", -0.2, 1);
        AIThree = Button ("3 X 3: Play Against AI",-0.5, 0.7);
        HumanThree = Button("3 X 3: Play Against Human", -0.6, 0.45);
        AIFour = Button("4 X 4: Play Against AI", -0.5, 0.2); 
        HumanFour = Button("4 X 4: Play Against Human", -0.6, -0.05);
        AIFive = Button("5 X 5: Play Against AI", -0.5, -0.3); 
        HumanFive = Button("5 X 5: Play Against Human", -0.6, -0.55);

    }

    void deselectAll(){
        // what
    }

    void AIOn() {
        AIMove();
    }

    void AIOff() {
        AI = false;
    }

    void playerXFirst() {
        playerX = true;
    }

    void playerOFirst() {
        playerX = false;
    }

    void start() {
        if (AI) {
            AIMove();
        }
    }

    void handleMouseClick(float x, float y) {
   
        if(!clickedBoard){
        if(AIThree.contains(x, y)){
            std::cout<<"Ai 3 selected"<<std::endl;
            clickedBoard=true;
            aiThree = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 3; 
            init();
            AI = true; 
            start();
        }
        else if(AIFour.contains(x,y)){
            std::cout<<"Ai 4 selected"<<std::endl;
                        clickedBoard=true;
            aiFour = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 4; 
            AI = true; 
            init();
                        start();
        }
        else if(AIFive.contains(x,y)){
            std::cout<<"Ai 5 selected"<<std::endl;
                        clickedBoard=true;
            aiFive = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 5; 
            AI = true; 
            init();
                        start();
        }
        else if(HumanThree.contains(x,y)){
            std::cout<<"Human 3 selected"<<std::endl;
                        clickedBoard=true;
            humanThree = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 3; 
            AI = false; 
            init();
                        start();
        }
        else if(HumanFour.contains(x,y)){
            std::cout<<"Human 4 selected"<<std::endl;
                        clickedBoard=true;
            humanFour = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 4;
            AI = false;  
            init();
                        start();
        }
        else if(HumanFive.contains(x,y)){
            std::cout<<"Human 5 selected"<<std::endl;
                        clickedBoard=true;
            humanFive = true; 
            for (int i = 0; i < count; i++){
                delete[] board[i];
            }
            delete[] board;
            count = 5; 
            AI = false; 
            init();
                        start();
        }

        }
                // draw selecitons

        
        if(cleared){
        for (int i = 0; i < count; i++) {
            for(int j =0; j<count; j++){
                if (board[i][j].contains(x, y) && board[i][j].isEmpty()){
  
                        if (playerX) {
                            board[i][j].playX();
                            if(checkWin()){
                            xWin = true; 
                            std::cout<<"x win" << std::endl;
                            return;
                            }

                            else if(isBoardFull()) {
                            tie = true;
                            std::cout << "Draw" << std::endl;
                            break;
                            }
                        
 
                        } else {
                            board[i][j].playO();
                                                    if(checkWin()){
                            oWin = true; 
                            std::cout<<" o win" << std::endl;
                            break;
                            
                        }

                                                                  if (isBoardFull()) {
                        tie = true;
                        std::cout << "Draw" << std::endl;
                        break;
                    }

                                                           



                        }
                        playerX = !playerX;
                    // Check for a draw after each move


                        break;
                    }
                }
            }
        }
        
        

        if (AI) {
            AIMove();
        }
        if(endScreen){
        if(left.contains(x,y)){
            exit(0);
        }
        else if(right.contains(x,y)){
            reset = true; 
        }
        }
    }

    void draw() {
    header.draw(); 
    if (aiThree || aiFour || aiFive || humanThree || humanFour || humanFive || newGame) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cleared = true; 

        for (int i = 0; i < count; i++){
            for(int j = 0; j < count; j++){
                board[i][j].draw();
            }
        }

        
    } else {
        AIThree.draw(); 
        AIFour.draw(); 
        AIFive.draw(); 
        HumanThree.draw(); 
        HumanFour.draw(); 
        HumanFive.draw(); 
    }

    if(xWin){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                up = Button("Player 1 wins (X)!", -0.15, 1);
        up.draw(); 
        right.draw(); 
        left.draw();
        endScreen = true; 
    }

    else if(oWin){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        up = Button("Player 2 wins (O)!", -0.15, 1);
        up.draw(); 
        right.draw(); 
        left.draw();
        endScreen = true; 
    }

    else if(aiWin){
              glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        up = Button("AI wins!", -0.15, 1);
        up.draw(); 
        right.draw(); 
        left.draw();  
        endScreen = true; 
    }
    else if(tie){
                      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        up = Button("Tie!!", -0.15, 1);
        up.draw(); 
        right.draw(); 
        left.draw(); 
        endScreen = true;
    }

    if(reset){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        header.draw();
        AIThree.draw(); 
        AIFour.draw(); 
        AIFive.draw(); 
        HumanThree.draw(); 
        HumanFour.draw(); 
        HumanFive.draw(); 
        //newGame = true; 
        //clickedBoard = false; 
        //endScreen = false;
        
        // defaults
        playerX = true;
        AI = false;

        aiThree = false; 
        aiFour = false; 
        aiFive = false; 
        humanThree = false; 
        humanFour = false; 
        humanFive = false; 
        cleared = false; 
        clickedBoard = false;
        xWin = false; 
        oWin = false; 
        aiWin = false; 
        tie = false;
        reset = false; 
        newGame = false;
        moved = false;
        endScreen = false;  
        horizontalWin = false;
        verticalWin = false;
        diag1Win = false;
        diag2Win = false;
    }
    }

bool checkWin() {


    // Check horizontal and vertical lines
    for (int i = 0; i < count; i++) {
       horizontalWin = true;
        verticalWin = true;
        SquareState firstHorizontal = board[i][0].getState();
        SquareState firstVertical = board[0][i].getState();

        for (int j = 1; j < count; j++) {
            if (board[i][j].getState() != firstHorizontal || firstHorizontal == EMPTY)
                horizontalWin = false;
            if (board[j][i].getState() != firstVertical || firstVertical == EMPTY)
                verticalWin = false;
        }

        if (horizontalWin || verticalWin)
            return true;
    }

    // Check diagonal lines
   diag1Win = true;
    diag2Win = true;
    SquareState firstDiag1 = board[0][0].getState();
    SquareState firstDiag2 = board[0][count-1].getState();

    for (int i = 1; i < count; i++) {
        if (board[i][i].getState() != firstDiag1 || firstDiag1 == EMPTY)
            diag1Win = false;
        if (board[i][count-i-1].getState() != firstDiag2 || firstDiag2 == EMPTY)
            diag2Win = false;
    }

    if (diag1Win || diag2Win)
        return true;

    // No win found
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (board[i][j].isEmpty()) {
                return false; // If any square is empty, return false
            }
        }
    }
    return true; // All squares are filled
}

        
        

        

};

#endif