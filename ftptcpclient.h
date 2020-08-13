#ifndef FtpTcpClient_H_INCLUDED
#define FtpTcpClient_H_INCLUDED
#include "tcpclient.h"
class FtpTcpClient: public TcpClient
{
private:
    TcpClient client1;
public:
    string server;
    FtpTcpClient();
    string user(const string& msg);
    string pass(const string& msg);
    string login(const string& username,const string& pass);
    string pwd();
    string cwd(const string& msg);
    string cwd();
    string rnfr(const string& msg);
    string rnto(const string& msg);
    string rename(const string& from,const string& to);
    int epsv();
    int SIZE(const string& message);
    void List();
    string mkd(const string& msg);
    string rmd(const string& msg);
    string dele(const string& msg);
    void retr(const string& msg);
    void dowload(const string& msg);
    void stor(const string& msg);
    void upload(const string& msg);
};
#endif // FtpTcpClient_H_INCLUDED
