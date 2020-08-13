#include <iostream>
#include "ftpcli.h"
#include <string>
#include <fstream>
using namespace std;

FtpCLI::FtpCLI():CmdLineInterface("Ftp>")
{}
void FtpCLI::initCmd()
{
    addCmd("login",CLI_CAST(&FtpCLI::doLogin));
    addCmd("pwd",CLI_CAST(&FtpCLI::doPwd));
    addCmd("cwd",CLI_CAST(&FtpCLI::doCwd));
    addCmd("rename",CLI_CAST(&FtpCLI::doRename));
    addCmd("list",CLI_CAST(&FtpCLI::doList));
    addCmd("mkd",CLI_CAST(&FtpCLI::doMkd));
    addCmd("rmd",CLI_CAST(&FtpCLI::doRmd));
    addCmd("dele",CLI_CAST(&FtpCLI::doDele));
    addCmd("dowload",CLI_CAST(&FtpCLI::doDowload));
    addCmd("upload",CLI_CAST(&FtpCLI::doUpload));
    addCmd("open",CLI_CAST(&FtpCLI::doOpen));
    addCmd("help", CLI_CAST(&FtpCLI::doHelp));
    addCmd("close", CLI_CAST(&FtpCLI::doClose));
}
void FtpCLI::doOpen(char * cmd_argv[], int cmd_argc)
{
    if(cmd_argc==3)
    {
        if(client.isConnected())
            cout << "Already connected. Close connection first" << endl;
        else
        {
            client.server=cmd_argv[1];
            bool ok = client.open(cmd_argv[1],atoi(cmd_argv[2]));//open localhost 80
            if(ok)
            {
                cout << "Connected.\n" << endl;
                char buffer[256];
                int bytes;
                bytes = client.recvDataBuffer(buffer, 255); // nhận bản tin phản hồi

                if(bytes>0)
                {
                    buffer[bytes]=0;
                }
                else
                {
                    *buffer=0;
                }
                cout<<buffer<<endl;

            }
        }
    }

    else
    {
        cerr << "Lenh khong dung tham so: open <hostname> <port>\n";
    }
    if(atoi(cmd_argv[2])!=21)
        client.close();
}
void FtpCLI::doLogin(char * cmd_argv[], int cmd_argc)
{
    string username,pass,ser;
    string response;
    if(cmd_argc == 1)
    {
        cout<<"Moi nhap username: "<<endl;
        getline(cin,username);


        cout<<"Moi nhap password: "<<endl;
        fflush(stdin);
        getline(cin,pass);

        if(!client.isConnected())
        {

            cout<<"Chua ket noi.Moi nhap server: "<<endl;
            fflush(stdin);
            getline(cin,ser);
            client.server=ser;
            client.open(ser,21);
            char buffer[256];

            client.recvDataBuffer(buffer, 255);
        }
        response=client.login(username,pass);
        cout<<response<<endl;
    }

    else
    {
        cerr << "Usage: login\n";

    }

}


void FtpCLI::doPwd(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 1)
    {
        string response = client.pwd();
        cout  << response << endl;
    }

    else
    {
        cerr << "Usage: pwd \n";
    }
}

void FtpCLI::doCwd(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 1)
    {
        string response = client.cwd();
        cout  << response << endl;
    }
    else if(cmd_argc == 2)
    {
        string response = client.cwd(cmd_argv[1]);
        cout  << response << endl;
    }
    else
    {
        cerr << "Usage: cwd [directory]\n";
    }
}
void FtpCLI::doRename(char * cmd_argv[], int cmd_argc)
{
    string response;
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 1)
    {
        string from,to;
        cout<<"From: "<<endl;
        getline(cin,from);

        cout<<"To: "<<endl;
        fflush(stdin);
        getline(cin,to);
        response = client.rename(from,to);
        cout << response << endl;

    }

    else
    {
        cerr << "Usage: rename \n";
    }
}


void FtpCLI::doMkd(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 2)
    {
        string response = client.mkd(cmd_argv[1]);
        cout  << response << endl;
    }

    else
    {
        cerr << "Usage: mkd [dir]\n";
    }
}

void FtpCLI::doRmd(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 2)
    {
        string response = client.rmd(cmd_argv[1]);
        cout  << response << endl;
    }

    else
    {
        cerr << "Usage: rmd [dir]\n";
    }
}

void FtpCLI::doDele(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 2)
    {
        string response = client.dele(cmd_argv[1]);
        cout  << response << endl;
    }

    else
    {
        cerr << "Usage: dele [filename]\n";
    }
}

void FtpCLI::doDowload(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 2)
    {
        client.dowload(cmd_argv[1]);


    }

    else
    {
        cerr << "Usage: dowload <filename>\n";
    }
}

void FtpCLI::doUpload(char * cmd_argv[], int cmd_argc)
{
    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 2)
    {
        client.upload(cmd_argv[1]);


    }

    else
    {
        cerr << "Usage: upload <filename>\n";
    }
}

void FtpCLI::doClose(char * cmd_argv[], int cmd_argc)
{
    client.close();
}
void FtpCLI::doList(char * cmd_argv[], int cmd_argc)
{

    if(!client.isConnected())
    {
        cout << "Not connected" << endl;
    }
    else if(cmd_argc == 1)
    {
        client.List();
    }

    else
    {
        cerr << "Usage: list\n";
    }

}
void FtpCLI::doHelp(char * cmd_argv[], int cmd_argc)
{
    cout << "Cac lenh duoc ho tro:" << endl;
    cout << "- open <server> <port>     Mo ket noi den Ftp server" << endl;
    cout << "- login                    Dang nhap" << endl;
    cout << "- pwd                      Hien thu muc lam viec hien thoi" << endl;
    cout << "- cwd <dir>                Chuyen thu muc hien hanh" << endl;
    cout << "- rename                   Doi ten tep/thu muc" << endl;
    cout << "- list                     In danh sach thu muc" << endl;
    cout << "- mkd <dir>                Tao thu muc" << endl;
    cout << "- rmd <dir>                Xoa thu muc" << endl;
    cout << "- dele <filename>          Xoa file" << endl;
    cout << "- dowload <filename>       Tai ve <Dowload>" << endl;
    cout << "- upload <filename>        Tai len <Upload>" << endl;
    cout << "- close                    Dong ket noi       " << endl;
    cout << "- help                     Tro giup" << endl;
}
