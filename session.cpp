//
//  session.cpp
//  3
//
//  Created by adore on 14-4-7.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "session.h"

Session::Session(io_service& io):
    sock(io),
    io(io)
{}
void Session::start()
{
    char *a = new char[1024];
    bzero(a, 1024);
    sock.async_read_some(buffer(a, 1024), [this, a](boost::system::error_code  er, int len)
    {
        if(!er)
        {
            do_read(a, len);
            start();
        }
        else
        {
            delete this;
        }
    });
}
void Session::do_read(char* a, int len)
{
    buf = buf + a;
    delete[] a;
    while(buf.find("\r\n\r\n") != std::string::npos)
    {
        std::string tmp = buf.substr(0, buf.find("\r\n\r\n") + 4);
        std::string tmp2 = tmp.substr(tmp.find("Host:") + 6, 30);
        auto i = tmp2.find("\r\n");
        tmp2 = tmp.substr(tmp.find("Host:") + 6, i);
        buf = buf.substr(buf.find("\r\n\r\n") + 4);
        sendto(tmp2, tmp);
    }
}
void Session::sendto(std::string acce, std::string content)
{
    try
    {
        ip::tcp::socket *socksend = new ip::tcp::socket(this->io);
        ip::tcp::resolver rlv(this->io);
        ip::tcp::resolver::query qry(acce, "80");
        ip::tcp::resolver::iterator end, begin = rlv.resolve(qry);
        boost::system::error_code ec = error::host_not_found;
        for(; ec && begin != end; begin++)
        {
            socksend->close();
            socksend->connect(*begin, ec);
        }
        if(!ec)
        {
            socksend->write_some(buffer(content));
            readback(socksend);
        }
    }
    catch(...) {}
}
void Session::readback(ip::tcp::socket* socksend)
{
    char *a = new char[1024];
    bzero(a, 1024);
    socksend->async_read_some(buffer(a, 1024), [this, socksend, a](boost::system::error_code er, int len)
    {
        if(!er)
        {
            try
            {
                sock.write_some(buffer(a, len));
                delete[] a;
                readback(socksend);
            }
            catch(...) {}
        }
        else
        {
            delete[] a;
            delete socksend;
        }
    });
}










