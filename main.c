#include <stdio.h>
#include <stdlib.h>
#include<dos.h>
#include<windows.h>  // needed for Sleep to work
#include "splash.h"
#include "login.h"
#include "menu.h"
#include<string.h>





int main(void)
{
    splash_screen(); //Calling the intro screen function

    User_Data_File();
    loginOrRegister();


    return 0;
}
