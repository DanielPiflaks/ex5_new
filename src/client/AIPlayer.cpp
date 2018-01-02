/******************************************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
******************************************/
#include "BoardCoordinates.h"
#include "AIPlayer.h"

map<BoardCoordinates, vector<BoardCoordinates> > AIPlayer::playOneTurn() {
    bool firstTime = true;
    //Get map of all possible moves.
    map<BoardCoordinates, vector<BoardCoordinates> > possibleMoves = gameLogic->getPossibleGameMoves(playerMoves,
                                                                                                     symbol);
    //Initialize move to default.
    BoardCoordinates wantedMove(0, 0);
    //Set max to be zero.
    int min = 0;
    for (map<BoardCoordinates, vector<BoardCoordinates> >::iterator moves = possibleMoves.begin();
         moves != possibleMoves.end(); ++moves) {
        //Check on each possible move.
        for (int i = 0; i < moves->second.size(); i++) {
            //Get single move.
            BoardCoordinates singleMove = moves->second[i];
            //Get delta of moves.
            int delta = simulator->getScoreByMove(possibleMoves, singleMove);
            if (firstTime) {
                wantedMove = singleMove;
                min = delta;
                firstTime = false;
            }

            //Check if delta is smaller then min.
            if (delta < min) {
                //Set wanted move to be with smallest point.
                wantedMove = singleMove;
                //Set min to be the new min.
                min = delta;
            }
        }
    }
    BoardCoordinates playerChosenMove = wantedMove;
    //Initialize vector of flipped symbols.
    vector<BoardCoordinates> flippedSymbols;
    map<BoardCoordinates, vector<BoardCoordinates> > playerMove;
    //Check if wanted move is on board(maybe we don't have wanted move at all).
    if (board->isOnBoard(wantedMove.getRow(), wantedMove.getColumn())) {
        //Get flipped symbols vector.
        flippedSymbols = gameLogic->flipSymbols(possibleMoves,
                                                wantedMove, getSymbol());
        //Print computer player last move.
        display->printOtherPlayerMove(getSymbol(), wantedMove);

        //Return all flipped symbols.
        playerMove.insert(pair<BoardCoordinates, vector<BoardCoordinates> >(playerChosenMove, flippedSymbols));
        return playerMove;
    } else {
        display->printMessage("No possible moves.");
        //Return empty vector.
        return playerMove;
    }
}

AIPlayer::~AIPlayer() {
    delete simulator;
}

void AIPlayer::endGameFunction() {

}