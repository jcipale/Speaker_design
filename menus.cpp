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
/* 12/10/2023:                                                                                */
/* Completed testing/debugging of driver selection (read) menu.                               */
/* Completed testing/debugging of Crossover Desgin menu.                                      */
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

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);

}; /* end splash_screen*/
/*--------------------------------------------------------------------------------------------*/
void menu_screen()
{
    system("clear");
    cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |               Program Menu               |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (B)uild Parameters                   |" << endl;
    cout << "    |  2) (L)ist Speaker Parts                 |" << endl;
    cout << "    |  3) (C)abinet Design                     |" << endl;
    cout << "    |  4) (X)over Design                       |" << endl;
    cout << "    |  5) (G)raph Performance                  |" << endl;
    cout << "    |  6) (S)ave Speaker Data                  |" << endl;
    cout << "    |  7) (R)ead Speaker Data                  |" << endl;
    cout << "    |  8) (W)rite Design Parameters            |" << endl;
    cout << "    |  9) (Q)uit                               |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void crossover_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |          Crossover Design Menu           |" << endl;
    cout << "    |      (Use numerical selection only)      |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) 2-way - passive speaker              |" << endl;
    cout << "    |  2) 2-way - active speaker               |" << endl;
    cout << "    |  3) 3-way - passive speaker              |" << endl;
    cout << "    |  4) 3-way - active speaker               |" << endl;
    cout << "    |  5) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void driver_selection_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |          Driver Selection Menu           |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (B)ass Driver                        |" << endl;
    cout << "    |  2) (M)id-range Driver                   |" << endl;
    cout << "    |  3) (T)weeter Driver                     |" << endl;
    cout << "    |  4) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void cabinet_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |           Cabinet Design Menu            |" << endl;
    cout << "    +------------------------------------------+" << endl;
	cout << "    |  1) (S)ub-woofer Design                  |" << endl;
	cout << "    |  2) (2)-way Speaker Design               |" << endl;
	cout << "    |  3) (3)-way Speaker Design               |" << endl;
    cout << "    |  4) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";

}
/*--------------------------------------------------------------------------------------------*/
void cabinet_design_screen()
{
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (S)ealed Cabinet                     |" << endl;
    cout << "    |  2) (V)ented Cabinet                     |" << endl;
    cout << "    |  3) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void exit_screen()
{
	cout << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                 Thank you! For using Speak-Easy!                        |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);
    
    system("clear");
}
/*--------------------------------------------------------------------------------------------*/
