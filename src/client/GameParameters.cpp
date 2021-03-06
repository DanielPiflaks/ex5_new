/**************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex5
**************/

#include <fstream>
#include "Board.h"
#include "Player.h"
#include "GameParameters.h"
#include "HumanPlayer.h"
#include "RemotePlayer.h"
#include "StandartGameLogic.h"
#include "MiniMaxSimulator.h"
#include "AIPlayer.h"
#include "HumanPlayerSender.h"

GameParameters::GameParameters(PlayerOptions player1Type, char player1Symbol, PlayerOptions player2Type,
                               char player2Symbol, int numRows, int numColumns, GuiDisplay *displayOption,
                               StartFirstOptions startFirst, GameLogicOptions gameLogicOption)
        : gameBoard(gameBoard), startFirst(startFirst) {
    //Create new game board.
    gameBoard = new Board(numRows, numColumns);
    display = displayOption;
    //Create game logic by input.
    switch (gameLogicOption) {
        case StandartGame: {
            gameLogic = new StandartGameLogic(gameBoard);
            break;
        }
    }

    string gameName;
    //If one of players defined as remote player.
    if ((player1Type == RemotePlayerOp) || (player2Type == RemotePlayerOp)) {
        //Set file name.
        const char *fileName = "ClientConnectionSettings.txt";
        //Create new client.
        client = new Client(fileName, display);
        //Connect and receive from server a number(1 or 2) that represent his turn (1st or 2nd).
        client->connectToServer();
        //if connection succeeded then print for user.
        display->printMessage("Connected to server");

        gameName = client->receiveOptionFromClient();

        //Receive message from server, will be player number for new game.
        string receivedMessage = client->receive();

        int startFirstParam;
        //Convert string to int.
        sscanf(receivedMessage.c_str(), "%d", &startFirstParam);

        //If received 1 from server.
        if (startFirstParam == 1) {
            //Set players type- first human, second remote.
            player1Type = HumanPlayerSenderOp;
            player2Type = RemotePlayerOp;

            //Notify player that server waiting to 2nd player.
            display->printMessage("Waiting for other player to join...");
            //Wait for another massage from server, it will be receive only after both players connected.
            string message = client->receive();
            int startGameNotification;
            //Convert string to int.
            sscanf(message.c_str(), "%d", &startGameNotification);
            if (startGameNotification != 1) {
                throw "Not valid start game notification";
            }
        }
        //If received 2 from server.
        if (startFirstParam == 2) {
            //set opposite players type.
            player2Type = HumanPlayerSenderOp;
            player1Type = RemotePlayerOp;
        }

    }

    //Create 2 simulator in case that one of players is computer.
    MiniMaxSimulator *simulatorPlayer1 = new MiniMaxSimulator(gameLogic);
    MiniMaxSimulator *simulatorPlayer2 = new MiniMaxSimulator(gameLogic);

    //Create player 1 by it's symbol and type.
    switch (player1Type) {
        case HumanPlayerOp: {
            player1 = new HumanPlayer(player1Symbol, gameBoard, gameLogic, display);
            break;
        }
        case AIPlayerOp: {
            player1 = new AIPlayer(player1Symbol, gameBoard, gameLogic, simulatorPlayer1, display);
            break;
        }
        case RemotePlayerOp: {
            player1 = new RemotePlayer(player1Symbol, gameBoard, gameLogic, display, client, gameName);
            break;
        }
        case HumanPlayerSenderOp: {
            player1 = new HumanPlayerSender(player1Symbol, gameBoard, gameLogic, display, client, gameName);
            break;
        }
        default:
            break;
    }

    //Create player 2 by it's symbol and type.
    switch (player2Type) {
        case HumanPlayerOp: {
            player2 = new HumanPlayer(player2Symbol, gameBoard, gameLogic, display);
            break;
        }
        case AIPlayerOp: {
            player2 = new AIPlayer(player2Symbol, gameBoard, gameLogic, simulatorPlayer2, display);
            break;
        }
        case RemotePlayerOp: {
            player2 = new RemotePlayer(player2Symbol, gameBoard, gameLogic, display, client, gameName);
            break;
        }
        case HumanPlayerSenderOp: {
            player2 = new HumanPlayerSender(player2Symbol, gameBoard, gameLogic, display, client, gameName);
            break;
        }
        default:
            break;
    }

    //Check if first player is computer player
    if (player1Type == AIPlayerOp) {
        //Set players for simulators.
        simulatorPlayer1->setOpponent(player2);
        simulatorPlayer1->setComputerPlayer(player1);
    } else {
        //If not, delete the simulator.
        delete simulatorPlayer1;
    }
    //Check if second player is computer player
    if (player2Type == AIPlayerOp) {
        //Set players for simulators.
        simulatorPlayer2->setOpponent(player1);
        simulatorPlayer2->setComputerPlayer(player2);
    } else {
        //If not, delete the simulator.
        delete simulatorPlayer2;
    }

}

GuiDisplay *GameParameters::getGuiDisplay() const {
    return display;
}


Board *GameParameters::getGameBoard() {
    return gameBoard;
}


Player *GameParameters::getPlayer2() const {
    return player2;
}

GameParameters::StartFirstOptions GameParameters::getStartFirst() const {
    return startFirst;
}

Player *GameParameters::getPlayer1() const {
    return player1;
}

GameParameters::~GameParameters() {
    delete gameBoard;
    delete gameLogic;
    delete player1;
    delete player2;
    delete client;
    delete display;
}