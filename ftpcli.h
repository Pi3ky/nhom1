#ifndef FTPTCPCLIENT_H_INCLUDED
#define FTPTCPCLIENT_H_INCLUDED
#include "cli.h"
#include "tcpsocket.h"
#include "ftptcpclient.h"
#include <string>
class FtpCLI : public CmdLineInterface
{
private:
    FtpTcpClient client;
public:
    FtpCLI();
    virtual void initCmd();
private:


    void doOpen(char * cmd_argv[], int cmd_argc);
    void doLogin(char * cmd_argv[], int cmd_argc);
    void doPwd(char * cmd_argv[], int cmd_argc);
    void doCwd(char * cmd_argv[], int cmd_argc);
    void doRename(char * cmd_argv[], int cmd_argc);
    void doList(char * cmd_argv[], int cmd_argc);//xoa
    void doMkd(char * cmd_argv[], int cmd_argc);
    void doRmd(char * cmd_argv[], int cmd_argc);
    void doDele(char * cmd_argv[], int cmd_argc);
    void doDowload(char * cmd_argv[], int cmd_argc);
    void doUpload(char * cmd_argv[], int cmd_argc);
    void doClose(char * cmd_argv[], int cmd_argc);
    void doHelp(char * cmd_argv[], int cmd_argc);

};



#endif // FtpTcpClient_H_INCLUDED
