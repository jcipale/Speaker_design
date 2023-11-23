/*--------------------------------------------------------------------------------------------*/
/* menus.cpp - menu and splash screen file used by Speaker_Easy program                       */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/16/2023:                                                                                */
/* Begin initial header and code development                                                  */
/*--------------------------------------------------------------------------------------------*/
/* 05/30/2023:                                                                                */
/* Finished implementing/testing/clean-up of menus, splash scren and exit screen.             */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define extern
#include "speaker_easy.h"
#undef extern

using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------*/
void splash_screen()
{

    system("clear");

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);

    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    | SSSSSS                                           EEEEEE                 |" << endl;
    cout << "    | S                       k                        E                      |" << endl;
    cout << "    | S                       k                        E                      |" << endl;
    cout << "    | S                       k   k                    E                      |" << endl;
    cout << "    | SSSSSS  ppp  eee  aaa   k  k    eee  r rr  ===   EEEE   aaa   sss  y  y |" << endl;
    cout << "    |      S  p  p e  e   a   k k     e  e rr  r       E        a   s     y y |" << endl;
    cout << "    |      S  p  p eee    a   k k     exe  rr  r       E        a   s     y y |" << endl;
    cout << "    |      S  pp   e    a a   k   k   e    r           E      a a     s    y  |" << endl;
    cout << "    | SSSSSS  p    eee  aaaa  k    k  eee  r           EEEEEE aaaa  sss  y    |" << endl;
    cout << "    |         p                                                               |" << endl;
    cout << "    |         p                                                               |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}; /* end splash_screen*/
/*--------------------------------------------------------------------------------------------*/
void exit_screen()
{
    system("clear");

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);
    
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                 Thank you! For using Speak-Easy!                        |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void menu_screen()
{
    system("clear");

    cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |               Program Menu               |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) Speaker Parameters                   |" << endl;
    cout << "    |  2) List Speaker Parts                   |" << endl;
    cout << "    |  3) Closed Box Design                    |" << endl;
    cout << "    |  4) Vented Box Design                    |" << endl;
    cout << "    |  5) Xover Design                         |" << endl;
    cout << "    |  6) Graph Performance                    |" << endl;
    cout << "    |  7) Write Speaker Data                   |" << endl;
    cout << "    |  8) Read Speaker Data                    |" << endl;
    cout << "    |  9) Write Design Parameters              |" << endl;
    cout << "    |  0) Quit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void crossover_screen()
{
    system("clear");
    cout << "    +------------------------------------------+" << endl;
	cout << "    |          Crossover Design Menu           |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) Two-way speaker                      |" << endl;
    cout << "    |  2) tHree-way speaker                    |" << endl;
    cout << "    |  3) Active Filter Design                 |" << endl;
    cout << "    |  4) Passive Filter Design                |" << endl;
    cout << "    |  5) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
}
