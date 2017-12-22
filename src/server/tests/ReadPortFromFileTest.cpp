//
// Created by danielpiflaks on 11/12/17.
//

#include <gtest/gtest.h>
#include "../Server.h"

TEST(ReadPortFromFileTest, checkPort){
    const char *fileName = "ServerConnectionSettings.txt";
    const int port = 5555;
    Server server(fileName);
    EXPECT_EQ(server.getPort(), port);
}