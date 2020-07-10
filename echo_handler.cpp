#include "sys/socket.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include "echo_handler.h"

EchoHandler::EchoHandler(QString ip,int port)
{
    if ( (m_echo_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "socket error " << errno << std::endl;
        exit(-1);
    }
    else
    {
        int on = 1;
        setsockopt(m_echo_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
        setsockopt(m_echo_fd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));

    }

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(port);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY); // TODO
    //seraddr.sin_addr.s_addr =inet_addr((char*)ip.data());




    int ret = bind(m_echo_fd, (struct sockaddr*)&seraddr, sizeof(seraddr));

    if(ret < 0)
    {
        std::cerr << "socket error " << errno << std::endl;
        printf("socket bind fail!\n");
    }


}


EchoHandler::~EchoHandler()
{

}

Handle EchoHandler::getHandle() const
{
    return m_echo_fd;
}

void EchoHandler::handleRead()
{

    int BUFF_LEN=1024;
    char buf[BUFF_LEN];  //接收缓冲区，1024字节
    socklen_t len;
    int count;
    struct sockaddr_in client_addr;  //clent_addr用于记录发送方的地址信息
    while(1)
    {
        memset(buf, 0, BUFF_LEN);
        len = sizeof(client_addr);
        count = recvfrom(m_echo_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&client_addr, &len);  //recvfrom是拥塞函数，没有数据就一直拥塞
        if(count == -1)
        {
            printf("recieve data fail!\n");
            return;
        }
        printf("client:%s\n",buf);  //打印client发过来的信息
        memset(buf, 0, BUFF_LEN);
        sprintf(buf, "I have recieved %d bytes data!\n", count);  //回复client
        printf("server:%s\n",buf);  //打印自己发送的信息给
        sendto(m_echo_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&client_addr, len);  //发送信息给client，注意使用了clent_addr结构体指针

    }
}
void EchoHandler::handleWrite()
{

}
void EchoHandler::handleError()
{

}

