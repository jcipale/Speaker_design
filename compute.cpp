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
//#include <algorithm>
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
void cabinet_design(Speaker* drvr, Cabinet* box, std::string cab_type, std::string speaker_type)
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    struct Cabinet *cptr;

    ptr = drvr;
    cptr = box;
   
    char flag[4];
    char type[4];
    char unit[4];
	
    float vol;
    float spkr_diam;
    float spkr_depth;
    float spkr_height;
    float vent_length;
    float vent_diam;
    float Depth;
    float Front;
    float Height;

    int done;


    cout << "Test function..." << endl;

    /* The 3rd argument determines what speaker type is being built (sealed vs vented) */
    //if (strcmp(cab_type, "sealed") == 0) {
    if (cab_type == "sealed") {
        vol = ptr->Vbs;
    } else {
        vol = ptr->Vbv;
    }

    cout << "Use Metric (M) or Imperial (I) units of measure? ( Metric is default)";
    cin >> unit;
	
    if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0)) {
        vol = vol * liter_to_cubicInch;
	    spkr_diam = ptr->b_diam * mm_to_inch;
	    spkr_depth = ptr->depth * mm_to_inch;
	    spkr_height = ptr->b_height * mm_to_inch;
	    vent_diam = ptr->v_diam * mm_to_inch;
	    vent_length = ptr->v_length * mm_to_inch;
    } else {
        vol = vol;
	    spkr_diam = ptr->b_diam;
	    spkr_depth = ptr->depth;
	    spkr_height = ptr->b_height;
	    vent_diam = ptr->v_diam;
	    vent_length = ptr->v_length;
    }

	done = 0;

    while (!done) {
        // Loop to determine box dimensions
        cout << "Driver dimensions: " << endl;
        cout <<" Part Number: " << cptr->Part_num << endl;
        cout <<" Nominal impedance: " << cptr->imp_Nom << endl;
        cout <<" Frequency - low: " << cptr->freq_lo << endl;
        cout <<" Frequency - high: " << cptr->freq_hi << endl;
        cout <<" Frequency rolloff: " << cptr->rolloff << endl;
        cout <<" Resonant frequncy: " << cptr->res_freq << endl;
		if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0 )) {
            if (cab_type == "sealed") {
                cout <<" Cabinet volume: " << vol << " in^3" << endl;
            } else {
                cout <<" Cabinet volume: " << vol << " in^3" << endl;
                cout <<" Vent diameter: " << vent_diam << " inches " << endl;
                cout <<" Vent length: " << vent_length << " inches " << endl;
            }
            cout << " Speaker diameter: " << spkr_diam << " inches " << endl;
            cout << " Speaker depth: " << spkr_depth << " inches " << endl;
            cout << " Speaker height: " << spkr_height << " inches " << endl;

		} else {
            if (cab_type == "sealed") {
                cout <<" Cabinet volume: " << vol << " liters" << endl;
            } else {
                cout <<" Cabinet volume: " << vol << " liters" << endl;
                cout <<" Vent diameter: " << vent_diam << " mm " << endl;
                cout <<" Vent length: " << vent_length << " mm " << endl;
            }
            cout << " Speaker diameter: " << spkr_diam << " mm " << endl;
            cout << " Speaker depth: " << spkr_depth << " mm " << endl;
            cout << " Speaker height: " << spkr_height << " mm " << endl;

		}
        // Compute baffle width
        Front = 1.5 * spkr_diam;

        // Compute cabinet depth
        Depth = 2.0 * spkr_depth;
 
        // Compute Height ht = Vas/(w * d)
        Height = vol/(Front * Depth);

        // Check with user id for correct dimensions

        cout << "Accept dimensions? (Y/N): " << endl;
        cin >> flag;

        if ((strcmp(flag, "Y") == 0) || (strcmp(flag, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            done = 1;
        } else {
            cout << "compute closed box design..." << endl;
        }

        cptr->D = Depth;
        cptr->W = Front;
        cptr->H = Height;

        cout << "--------------------------------------------" << endl;
        cout << "            Speaker Dimensions              " << endl;
        cout << "--------------------------------------------" << endl;
        cout << "  Width:  " << cptr->W << endl;
        cout << "  Depth:  " << cptr->D << endl;
        cout << "  Height: " << cptr->H << endl;
        cout << "--------------------------------------------" << endl;

        sleep(5);
    }

    sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
