#include "ftptcpclient.h"
#include<iostream>
#include <string.h>
#include <cstring>
#include <fstream>
FtpTcpClient::FtpTcpClient():TcpClient()
{}
string FtpTcpClient::user(const string& message)
{
    char newCmd[256];
    string b;
    sprintf(newCmd,"user %s\r\n",message.c_str());

    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    b=buffer[0];
    return b;
}
string FtpTcpClient::pass(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"pass %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    string b;
    b=buffer[0];
    return b;
}
string FtpTcpClient::login(const string& username,const string& pass)
{
    string rq;
    string rq1;
    this->user(username);
    rq=this->pass(pass);
    if(rq=="2")
    {
        rq1= "Dang nhap thanh cong.";

    }
    else
    {
        rq1="Dang nhap that bai!";
    }
    return rq1;

}
string FtpTcpClient::pwd()
{
    string abc ="pwd\r\n";
    this->sendStringRequest(abc); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    char *a;
    char req[50];
    if(buffer[0]=='2')
    {
        a=strtok(buffer,"\"");
        if(a)
        {
            a=strtok(NULL,"\"");
        }

        sprintf(req,"Thu muc hien hanh: %s",a);
    }

    return req;
}
string FtpTcpClient::cwd(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"cwd %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }

    return buffer;
}
string FtpTcpClient::cwd()
{
    string newCmd="cwd\r\n";

    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    return buffer;
}
string FtpTcpClient::rnfr(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"rnfr %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    string b;
    b=buffer[0];
    return b;
}
string FtpTcpClient::rnto(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"rnto %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    string b;
    b=buffer[0];
    return b;
}
string FtpTcpClient::rename(const string& from,const string& to)
{
    string rq;
    string rq1;
    rq=this->rnfr(from);
    if(rq=="3")
    {
        rq=this->rnto(to);
        if(rq=="2")
        {
            rq1="Doi ten thanh cong.";
        }
        else
        {
            rq1="Doi ten khong thanh cong!";
        }
    }
    else
    {
        rq1="Khong tim thay thu muc hoac tep!";
    }
    return rq1;
}
int FtpTcpClient::epsv()
{
    string newCmd="epsv\r\n";

    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    char *a;
    a=strtok(buffer,"|||");
    if(a)
    {
        a=strtok(NULL,"|");
    }
    int c;
    c=atoi(a);
    return c;
}
int FtpTcpClient::SIZE(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"size %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    char *a;
    a=strtok(buffer," ");
    if(a)
    {
        a=strtok(NULL," ");
    }
    int c;
    c=atoi(a);
    return c;
}
void FtpTcpClient::List()
{
    int port;
    char buffer[256];
    port= this->epsv();
    if(client1.isConnected())
        client1.close();
    bool o=client1.open(this->server,port);

    this->sendStringRequest("list\r\n");
    this->recvDataBuffer(buffer,255);
    this->recvDataBuffer(buffer,255);
    if(o)
    {

        int bytes;
        bytes = client1.recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
        if(bytes==255)
        {
            while (bytes>0)
            {
                buffer[bytes]=0;
                cout<<buffer;
                bytes = client1.recvDataBuffer(buffer, 255);
            }
        }

        else
        {
            if(bytes>0)
            {
                buffer[bytes]=0;
            }
            else
            {
                *buffer=0;
            }
            cout<<buffer<<endl;
            //new


        }


    }
}
string FtpTcpClient::mkd(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"mkd %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    return buffer;
}
string FtpTcpClient::rmd(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"rmd %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    return buffer;
}
string FtpTcpClient::dele(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"dele %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    return buffer;
}
void FtpTcpClient::retr(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"retr %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes;
    for(int i=0; i<2; i++)
    {
        bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
        if(bytes>0)
        {
            buffer[bytes]=0;
        }
        else
        {
            *buffer=0;
        }
        cout<<buffer;

    }
}
void FtpTcpClient::dowload(const string& msg)
{
    int port;
    int s;
    char buffer[255];
    char newCmd[256];
    this->sendStringRequest("TYPE I\r\n");
    this->recvDataBuffer(buffer,255);
    s=this->SIZE(msg);
    port= this->epsv();
    if(client1.isConnected())
        client1.close();
    bool o=client1.open(this->server,port);

    sprintf(newCmd,"retr %s\r\n",msg.c_str());
    this->sendStringRequest(newCmd);
    this->recvDataBuffer(buffer,255);
    if(buffer[0]=='1')
    {

        if(o)
        {


            char dowload[50];
            sprintf(dowload,"C:/Users/Admin/Desktop/FTP/dowload/%s",msg.c_str());//dowload tệp từ server về thư mục này
            ofstream f(dowload,ios::binary);
            char buffer1[s];
            client1.recvDataBuffer(buffer1, s); // nhận bản tin phản hồi
            f.write(buffer1,s);
            f.close();
        }
        this->recvDataBuffer(buffer,255);
        if(buffer[0]=='2')
            cout<<"tai tep ve thanh cong"<<endl;
        client1.close();
    }
    else if(buffer[0]=='5')
    {
        cout<<"khong tim thay ten tep!"<<endl;
    }
    else
        cout<<"That bai."<<endl;
}
void FtpTcpClient::stor(const string& message)
{
    char newCmd[256];
    sprintf(newCmd,"stor %s\r\n",message.c_str());
    this->sendStringRequest(newCmd); // gửi bản tin
    char buffer[256];
    int bytes;
    bytes = this->recvDataBuffer(buffer, 255); // nhận bản tin phản hồi
    if(bytes>0)
    {
        buffer[bytes]=0;
    }
    else
    {
        *buffer=0;
    }
    cout<<buffer;



}
void FtpTcpClient::upload(const string& msg)
{
    char upload[50];
    sprintf(upload,"C:/Users/Admin/Desktop/FTP/upload/%s",msg.c_str());//tải tệp từ thư mục này lên server

    ifstream file(upload,ios::binary);
    if(file.good())
    {
        char newCmd[256];
        char buffer[256];
        this->sendStringRequest("TYPE I\r\n");
        this->recvDataBuffer(buffer,255);
        int port;
        port= this->epsv();
        if(client1.isConnected())
            client1.close();
        client1.open(this->server,port);


        sprintf(newCmd,"stor %s\r\n",msg.c_str());
        this->sendStringRequest(newCmd);
        this->recvDataBuffer(buffer,255);

        if(buffer[0]=='1')
        {
            char buffer1[1024];
            // mo file


            while(!file.eof())
            {
                file.read(buffer1,1024);
                if(file.good())
                {
                    client1.sendDataBuffer(buffer1, 1024);
                }
                else
                    client1.sendDataBuffer(buffer1,file.gcount());
            }

        }

        client1.close();
        file.close();
        this->recvDataBuffer(buffer,255);
        if(buffer[0]=='2')
            cout<<"Tai tep len thanh cong"<<endl;
        else
            cout<<"Tai tep len that bai"<<endl;

    }
    else
        cout<<"Khong tim thay ten tep!"<<endl;
}

