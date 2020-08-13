#include <iostream>
#include "ftpcli.h"
using namespace std;

int main()
{
    FtpCLI cli;
    cli.initCmd();
    cli.run();


    return 0;
}


