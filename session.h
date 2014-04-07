//
//  session.h
//  3
//
//  Created by adore on 14-4-7.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef _____session__
#define _____session__

#include <iostream>
#include <boost/asio.hpp>
#include <string>
using namespace boost::asio;
class Session
{
private:
    io_service& io;
    std::string buf;
public:
    Session(io_service& io);
    ip::tcp::socket sock;
    void start();
    void do_read(char* a,int len);
    void sendto(std::string acce,std::string content);
    void readback(ip::tcp::socket* socksend);
};


#endif /* defined(_____session__) */
