//
//  server.cpp
//  3
//
//  Created by adore on 14-4-7.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "server.h"
Server::Server(io_service& ios, int port):
            acce(ios, ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)),
            io(ios)
{
    start();
}
void Server::start()
{
    Session *s = new Session(io);
    acce.async_accept(s->sock, [s, this](boost::system::error_code er){
        if (!er)
        {
            s->start();
        }
        this->start();
    });
}