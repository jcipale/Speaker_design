/*--------------------------------------------------------------------------------------------*/
/* menus.cpp - menu and splash screen file used by Speaker_Easy program                       */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/16/2023:                                                                                */
/* Begin initial header and code development                                                  */
/*--------------------------------------------------------------------------------------------*/

#include <iostream>
#include <unistd.h>
#include "menus.h"

//using namespace std;
/*--------------------------------------------------------------------------------------------*/
extern void splash_screen()
{
	using std::cout;
	using std::endl;

	// This is used to define the wait time to display the splash screen
	unsigned int sleep(unsigned int seconds);

    cout << "+-------------------------------------------------------------------------+" << endl;
	cout << "|                                                                         |" << endl;
	cout << "| SSSSSS                                           EEEEEE                 |" << endl;
	cout << "| S                       k                        E                      |" << endl;
	cout << "| S                       k                        E                      |" << endl;
	cout << "| S                       k   k                    E                      |" << endl;
	cout << "| SSSSSS  ppp  eee  aaa   k  k    eee  r rr  ===   EEEE   aaa   sss  y  y |" << endl;
	cout << "|      S  p  p e  e   a   k k     e  e rr  r       E        a   s     y y |" << endl;
	cout << "|      S  p  p eee    a   k k     exe  rr  r       E        a   s     y y |" << endl;
	cout << "|      S  pp   e    a a   k   k   e    r           E      a a     s    y  |" << endl;
	cout << "| SSSSSS  p    eee  aaaa  k    k  eee  r           EEEEEE aaaa  sss  y    |" << endl;
	cout << "|         p                                                               |" << endl;
	cout << "|         p                                                               |" << endl;
	cout << "|                                                                         |" << endl;
	cout << "+-------------------------------------------------------------------------+" << endl;
} /* end splash_screen
/*--------------------------------------------------------------------------------------------*/
