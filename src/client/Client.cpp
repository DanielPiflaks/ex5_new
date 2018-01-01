/**************
Student name: Daniel Piflaks and Sapir Blutman
Student ID: Daniel : 311322986 Sapir : 203312905
Course Exercise Group: 05
Exercise name: Ex4
**************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <fstream>
#include <netdb.h>
#include <limits>
#include "Client.h"

Client::Client(char *serverIP, int serverPort) :
        serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
    //serverIP = new char((strlen(serverIP)) + 1);
    strcpy(serverIP, serverIP);
}

Client::Client(const char *fileName) {
    setIpAndPortFromFile(fileName);
}

Client::~Client() {
    disconnectServer();
    //delete serverIP;
}

void Client::connectToServer() {
    const char *ip = serverIP.c_str();
    //Create socket point.
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }

    // Convert the ip string to a network address
    struct in_addr address;
    memset(&address, 0, sizeof(address));
    if (!inet_aton(ip, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    memset(&server, 0, sizeof(server));
    server = gethostbyaddr((const void *) &address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }

    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, server->h_addr, (uint16_t) server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons((uint16_t) serverPort);

    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

void Client::sendMove(BoardCoordinates move) {
    //Create message of move in wanted format.
    char moveMessage[7] = "";

    //If there isn't any possible move.
    if ((move.getRow() == 0) && (move.getColumn() == 0)) {
        strcpy(moveMessage, "NoMove");
        //If there is possible move.
    } else {
        //Build a string with this pattern (x, y) from the client move.
        moveMessage[0] = (char) move.getRow();
        moveMessage[1] = ',';
        moveMessage[2] = ' ';
        moveMessage[3] = (char) move.getColumn();
    }

    //Write the move coordinate to the socket.
    long check = write(clientSocket, &moveMessage, sizeof(moveMessage));
    if (check == -1) {
        throw "Error writing row coordinate";
    }
}

BoardCoordinates Client::receiveMove() {
    char moveMessage[7];
    cout << "Waiting for other player's moves" << endl;
    //Read massage from socket.
    long readParam = read(clientSocket, &moveMessage, sizeof(moveMessage));
    //If reading failed.
    if (readParam == -1) {
        throw "Error reading result from socket";
    }
    if (moveMessage == "NoMove") {
        return BoardCoordinates(0, 0);
        //If there is any move to read.
    } else {
        //Convert massage into coordinate.
        BoardCoordinates receivedMove((int) moveMessage[0], (int) moveMessage[3]);
        //Return the move after coverting to board coordinate.
        return receivedMove;
    }
}

int Client::getStartGameNotification() {
    int startParamNotify;
    //Read massage from socket.
    long readParam = read(clientSocket, &startParamNotify, sizeof(startParamNotify));
    //If reading failed.
    if (readParam == -1) {
        throw "Error reading result from socket";
    }
    //Return massage.
    return startParamNotify;
}


void Client::setIpAndPortFromFile(const char *fileName) {
    //Set const sub string as expected.
    const string ipSubString = "IP:";
    const string portSubString = "PORT:";
    //Set const comment char symbol.
    const char commentChar = '#';
    string singleLine, stringPort;
    ifstream inFile;
    //Open file.
    inFile.open(fileName);
    //Check if file opened.
    if (inFile.is_open()) {
        //Check if file is empty.
        if (!inFile.eof()) {
            //Get next line.
            getline(inFile, singleLine);
        }
        //Get all lines until we get to end of file.
        while (!inFile.eof()) {
            //Check if line is not comment line.
            if (singleLine.find(commentChar) != 0) {
                //Check if line contains ip sub string.
                if (singleLine.find(ipSubString) == 0) {
                    serverIP = (singleLine.substr(ipSubString.length(), singleLine.length()));
                    //Check if line contains port sub string.
                } else if (singleLine.find(portSubString) == 0) {
                    stringPort = singleLine.substr(portSubString.length(), singleLine.length());
                    //Convert string to int.
                    sscanf(stringPort.c_str(), "%d", &serverPort);
                }
            }
            //Get next line.
            getline(inFile, singleLine);
        }
        //Close file when there is no more lines to read.
        inFile.close();
    } else {
        //Throw exception when we can't open file.
        throw "Can't open settings file!";
    }
}

/*void Client::sendEndGameMessage() {
    //Create message of move in wanted format.
    char endGameBuffer[7] = "End";

    //Write the massage into the socket.
    long check = write(clientSocket, &endGameBuffer, sizeof(endGameBuffer));
    //If writing failed.
    if (check == -1) {
        throw "Error writing row coordinate";
    }
}*/

/*void Client::sendNoPossibleMovesMessage() {
    //Create message of move in wanted format.
    char noMoveBuffer[7] = "NoMove";

    //Write the massage into the socket.
    long check = write(clientSocket, &noMoveBuffer, sizeof(noMoveBuffer));
    //If writing failed.
    if (check == -1) {
        throw "Error writing row coordinate";
    }
}*/

void Client::disconnectServer() {
    close(clientSocket);
}

const string &Client::getServerIP() const {
    return serverIP;
}

int Client::getServerPort() const {
    return serverPort;
}

int Client::receiveOptionFromClient() {
    bool waitingForInput = true;
    int input;
    while (waitingForInput) {
        //Print menu of options to client.
        cout << "please choose one of the following options:" << endl;
        cout << "1. start new game" << endl;
        cout << "2. get list of optional games to play" << endl;
        cout << "3. join exiting game" << endl;

        //Receive client input.
        cin >> input;

        //Ignore all other input.
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        string message;

        switch (input) {
            //If user input is 1.
            case 1: {
                //Print order to pick up name for new game.
                cout << "please choose name for new game" << endl;
                //Receive client input for new game name.
                string gameName;
                cin >> gameName;
                //Set relevant message.
                message = "start ";
                message = message + gameName;
                //Send message to server.
                send(message);

                cin.ignore();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //Change boolean variable in order to exit while loop.
                waitingForInput = false;
                //Break switch-case.
                break;
            }
            //If user input is 2.
            case 2: {
                //Set relevant message.
                message = "list_games";
                //Send message to server.
                send(message);

                cout << endl;
                //Receive from server list of waiting games.
                string receivedMessage = receive();
                //Print list of waiting games.
                cout << receivedMessage << endl;
                cout << endl;
                //Break switch-case.
                break;
            }
            //If user input is 3.
            case 3: {
                //Print order to pick up name for new game.
                cout << "please choose name for new game" << endl;
                //Receive client input for chosen game name.
                string gameName;
                cin >> gameName;
                //Set relevant message.
                message = "join ";
                message = message + gameName;
                //Send message to server.
                send(message);
                //Receive from server if game exist of games list.
                string checkMessage = receive();
                cin.ignore();
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //If server send message for invalid game.
                if (checkMessage == "Not valid game") {
                    //Print for user appropriate message.
                    cout << checkMessage << endl;
                    //If user game name is valid.
                } else {
                    //Change boolean variable in order to exit while loop.
                    waitingForInput = false;
                }
                //Break switch-case.
                break;
            }
            //If user input is invalid.
            default: {
                //Print for user appropriate message.
                cout << "Wrong input! please try again." << endl;
            }
        }
    }//End of while.
    //Receive message from server, will be player number for new game.
    string receivedMessage = receive();

    int playerNumber;
    //Convert string to int.
    sscanf(receivedMessage.c_str(), "%d", &playerNumber);

    return playerNumber;
}

void Client::send(string message) {
    //Set buffer to be empty.
    char messageBuffer[50] = {0};

    //copy message to buffer.
    strcpy(messageBuffer, message.c_str());

    //Write the message into the socket.
    long check = write(clientSocket, &messageBuffer, sizeof(messageBuffer));
    //If writing failed.
    if (check == -1) {
        throw "Error writing to server";
    }
}

string Client::receive() {
    //Set buffer to be empty.
    char message[50] = {0};

    //Read message from socket.
    long readParam = read(clientSocket, &message, sizeof(message));

    //If reading failed.
    if (readParam == -1) {
        throw "Error reading result from socket";
    }
    //Return massage.
    return message;
}