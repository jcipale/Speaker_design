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
double compute_efficiency(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    
	ptr = drvr;

	double efficency;

	efficency = (pow((2 * M_PI)*(ptr->Fs),3)) * ((ptr->Vas)/1000)/(pow(C,3) * ptr->Qes);

	return(efficency);
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
	
    double vol;
    double spkr_diam;
    double spkr_depth;
    double spkr_height;
    double vent_length;
    double vent_diam;
    double Depth;
    double Front;
    double Height;

    int done;

    /* The 3rd argument determines what speaker type is being built (sealed vs vented) */
    if (cab_type == "sealed") {
        vol = ptr->Vbs;
    } else {
        vol = ptr->Vbv;
    }

    cout << "Use Metric (M) or Imperial (I) units of measure? (Metric is default): ";
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
            if (cab_type == "vented") {
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
        Depth = spkr_depth + (spkr_depth/2.0);
        Front = spkr_diam + (spkr_diam/8);
        Height = vol/(Front * Depth);

		cout << "+--------------------------+" << endl;
		cout << "|   Speaker measurements   |" << endl;
		cout << "+--------------------------+" << endl;
		cout << "| Width  : " << Front << endl;
		cout << "| Depth  : " << Depth << endl;
		cout << "| Height : " << Height << endl;
		cout << "+---------------------------+" << endl;
        cout << "Accept dimensions? (Y/N): " << endl;
        cin >> flag;

        if ((strcmp(flag, "Y") == 0) || (strcmp(flag, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            done = 1;
        } else {
            cout << "compute closed box design..." << endl;
			//done = 0;
        }
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

	box = cptr;

    sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
void tweeter_cabinet_design(Speaker* drvr, Cabinet* box)
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    struct Cabinet *cptr;

    ptr = drvr;
    cptr = box;
   
    char flag[4];
    char type[4];
    char unit[4];
	
    double vol;
    double spkr_diam;
    double spkr_depth;
    double spkr_height;
    double vent_length;
    double vent_diam;
    double Depth;
    double Front;
    double Height;

    int done;

    /* The 3rd argument determines what speaker type is being built (sealed vs vented) */
    vol = ptr->Vbs;

    cout << "Use Metric (M) or Imperial (I) units of measure? (Metric is default): ";
    cin >> unit;
	
    if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0)) {
        vol = vol * liter_to_cubicInch;
	    spkr_diam = ptr->b_diam * mm_to_inch;
	    spkr_depth = ptr->depth * mm_to_inch;
	    spkr_height = ptr->b_height * mm_to_inch;
    } else {
        vol = vol;
	    spkr_diam = ptr->b_diam;
	    spkr_depth = ptr->depth;
	    spkr_height = ptr->b_height;
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
            cout <<" Cabinet volume: " << vol << " in^3" << endl;
            cout << " Speaker diameter: " << spkr_diam << " inches " << endl;
            cout << " Speaker depth: " << spkr_depth << " inches " << endl;
            cout << " Speaker height: " << spkr_height << " inches " << endl;

		} 

        /* Compute baffle width */
		/* Since the tweeter doesnt need a large cabinet space, the height/width are identical */
        Depth = spkr_depth + (spkr_depth/2.0);
        Height = Depth;
        Front = spkr_diam + (spkr_diam/8);

		cout << "+--------------------------+" << endl;
		cout << "|   Speaker measurements   |" << endl;
		cout << "+--------------------------+" << endl;
		cout << "| Width  : " << Front << endl;
		cout << "| Depth  : " << Depth << endl;
		cout << "| Height : " << Height << endl;
		cout << "+---------------------------+" << endl;
        cout << "Accept dimensions? (Y/N): " << endl;
        cin >> flag;

        if ((strcmp(flag, "Y") == 0) || (strcmp(flag, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            done = 1;
        } else {
            cout << "compute closed box design..." << endl;
			//done = 0;
        }
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

	box = cptr;

    sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
void center_field(char *field_data)
/*--------------------------------------------------------------------------------------------*/
/* This procedure centers the data to display the contents of the driver fields into a        */
/* cleaner display to make readability of the output cleaner.                                 */
/*--------------------------------------------------------------------------------------------*/
{
	char dest[FIELD_LGTH] = "";

	int src_len = strlen(field_data);
	int dest_len = sizeof(dest) - 1;

    // Calculate starting index for centering
    int start_index = (dest_len - src_len) / 2;


    // Fill dest with spaces
    memset(dest, ' ', dest_len);
    dest[dest_len] = '\0';            // Null-terminate dest

	// Copy src into dest starting at start_index to center it
    memcpy(&dest[start_index], field_data, src_len);

	// Copy dest back to src (datum.Part_num)
    strcpy(field_data, dest);

	sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
double compute_qt(double Qes, double Qms)
/*--------------------------------------------------------------------------------------------*/
{
    double Q;

    Q = (Qes * Qms)/(Qms + Qes);

    return(Q);
}
