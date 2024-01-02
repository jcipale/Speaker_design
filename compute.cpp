/*--------------------------------------------------------------------------------------------*/
/* compute.cpp - misclleaneous code file used to manage miscellaneous number manipulations    */
/* and string parsing/padding/manipulation.                                                   */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 12/19/2023:                                                                                */
/* Began code development of classes, methods and objects                                     */
/* Begin development of field_pad() functions.                                                */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define extern
#include "speaker_easy.h"
#undef extern

using namespace std;
using std::cin;
using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------*/
void data_field(Speaker* drvr, std::string& data_display)
/*--------------------------------------------------------------------------------------------*/
/* This function will manipulate the data_field string and pad it to fit the desired format   */
/* to display the Part_num and frequency range of the selected speaker in order to determine  */
/* the crossover point for the speaker being designed.                                        */
/*--------------------------------------------------------------------------------------------*/
{
    //struct Speaker *ptr_1;   
	string fld = "";

	int i;
	int ttl_cnt;
	int cnt;

	fld = fld + "| ";
	ttl_cnt = fld.length();

	sleep(2);

	// the associated field below is a char array, so the operation is differnt.
	cnt = strlen(drvr->Part_num);

	// Append Part_num to the string vale fld;
	fld = fld + drvr->Part_num;

	// fld is a string object, so the object method to extract the string length is required
	ttl_cnt = fld.length();
	cnt = 43 - ttl_cnt;

	/*
	The code going forward will perform calculations to add/subtract/pad whitespace
	to the assembled string before displaying it in the form for the user to see the
	speaker badn-widths and make the appropriate component selections to determine the
	crossover network.
	*/

    for (i = 0; i < cnt; i++) {
	    fld = fld + " ";
	}

	fld = fld + "| ";
	ttl_cnt = fld.length();

	fld = fld + to_string(drvr->Freq_Low);
	ttl_cnt = fld.length();
	cnt = 61 - ttl_cnt;

	for (i = 0; i < cnt; i++) {
	    fld = fld + " ";
	}
	fld = fld + "| ";
	
	ttl_cnt = fld.length();

	fld = fld + to_string(drvr->Freq_Hi);
	ttl_cnt = fld.length();

	cnt = 81 - ttl_cnt;

	for (i = 0; i < cnt; i++) {
	    fld = fld + " ";
	}
	fld = fld + "|";
	
	data_display = fld;
	cout << fld << endl;
}
/*--------------------------------------------------------------------------------------------*/
