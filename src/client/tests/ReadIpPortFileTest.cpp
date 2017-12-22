//
// Created by danielpiflaks on 11/12/17.
//

#include <gtest/gtest.h>
#include "../Client.h"

TEST(ReadIpPortFileTest, readFromFileTest){
    const char *fileName = "ClientConnectionSettings.txt";
    const char * ip = "127.0.0.1";
    const int port = 5555;
    Client client(fileName);
    EXPECT_EQ(client.getServerIP(), ip);
    EXPECT_EQ(client.getServerPort(), port);
}