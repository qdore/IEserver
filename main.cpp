//
//  main.cpp
//  3
//
//  Created by adore on 14-4-6.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include <iostream>
#include "server.h"
using namespace std;
using namespace boost::asio;
int main(int argc, const char * argv[])
try
{
    io_service io;
    Server s(io, 8888);
    io.run();
}
catch (std::exception& er)
{
    cout << er.what() << endl;
}

