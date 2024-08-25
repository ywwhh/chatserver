/*
muduo网络库给用户提供了两个主要的类
TcpServer : 用于编写服务器程序的
TcPClient : 用于编写客户端程序的

epoll + 线程池
好处：能够把网络I/O的代码和业务代码区分开
                        用户的连接和断开 用户的可读写事件

*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <string>
#include <iostream>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;


/*基于muduo网络库开发服务器程序
1.组合TcpServer对象

*/

class ChatServer
{
public:
    ChatServer(EventLoop* loop,  //事件循环
                const InetAddress &listenAddr,   // IP + Port
                const string &nameArg)  //服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
        {
            // 给服务器注册用户连接的创建和断开回调
            _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

            // 给服务器注册用户读写事件回调
            _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

            //设置服务器端的线程数量
            _server.setThreadNum(4); 
        }

        //开启事件循环
        void start()
        {
            _server.start();
        }

private:
    //专门处理用户的连接    epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn) 
    {
        if (conn->connected())
        {
            cout << conn -> peerAddress().toIpPort() << " -> " << conn -> localAddress().toIpPort() << "state:online" << endl;
        }
         else
        {
            cout << conn -> peerAddress().toIpPort() << " -> " << conn -> localAddress().toIpPort() << endl;
            conn ->shutdown();
            //_loop->quit(); 
        }
        
    }
   

    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,
                    Buffer *buffer,
                    Timestamp  time)
    {
        string buf = buffer -> retrieveAllAsString();
        cout << "recv data:" << buf << "time: " << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server;
    EventLoop *_loop;
};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop(); //epoll_wait

    return 0;
}