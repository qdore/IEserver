//
//  server.h
//  3
//
//  Created by adore on 14-4-7.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef _____server__
#define _____server__

#include <iostream>
#include "session.h"
#include <boost/asio.hpp>
class Server
{
private:
    io_service& io;
    ip::tcp::acceptor acce;
public:
    Server(io_service& ios, int port);
    void start();
    
};
#endif /* defined(_____server__) */
