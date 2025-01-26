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
#include "menus.h"
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
    //char type[4];
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
	    //vent_diam = cptr->vent_diam * mm_to_inch;
	    //vent_length = cptr->vent_length * mm_to_inch;
    } else {
        vol = vol;
	    spkr_diam = ptr->b_diam;
	    spkr_depth = ptr->depth;
	    spkr_height = ptr->b_height;
	    vent_diam = ptr->v_diam;
	    vent_length = ptr->v_length;
	    //vent_diam = cptr->vent_diam;
	    //vent_length = cptr->vent_length;
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

		if (cab_type == "vented") {
		    cout << "| Vent diameter : " << vent_diam << endl;
		    cout << "| vent_length   : " << vent_length << endl;
		}

		cout << "+---------------------------+" << endl;
        cout << "Accept dimensions? (Y/N): " << endl;
        cin >> flag;

        if ((strcmp(flag, "Y") == 0) || (strcmp(flag, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            done = 1;
        } else {
            cout << "compute box design..." << endl;
			done = 0;
        }
    }

    cptr->Depth = Depth;
    cptr->Width = Front;
    cptr->Height = Height;

    cout << "--------------------------------------------" << endl;
    cout << "            Speaker Dimensions              " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  Width:  " << cptr->Width << endl;
    cout << "  Depth:  " << cptr->Depth << endl;
    cout << "  Height: " << cptr->Height << endl;
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
    //char type[4];
    char unit[4];
	
    double vol;
    double spkr_diam;
    double spkr_depth;
    double spkr_height;
    //double vent_length;
    //double vent_diam;
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

    cptr->Depth = Depth;
    cptr->Width = Front;
    cptr->Height = Height;

    cout << "--------------------------------------------" << endl;
    cout << "            Speaker Dimensions              " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  Width:  " << cptr->Width << endl;
    cout << "  Depth:  " << cptr->Depth << endl;
    cout << "  Height: " << cptr->Height << endl;
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
/*--------------------------------------------------------------------------------------------*/
double convert_units(double& target, double conversion)
/*--------------------------------------------------------------------------------------------*/
/* This function converts the units of a given variable back and forth based on the factor of */
/* the conversion value. (i.e. to convert from mm to meters, the conversion value would be    */
/* 1/1000 or 0.001. to convert back it would be 1000.00.                                      */
/*--------------------------------------------------------------------------------------------*/
{
    target = target * conversion;
	return(target);
}
/*--------------------------------------------------------------------------------------------*/
double tuning_frequency(Speaker* drvr, std::string cab_type)
/*--------------------------------------------------------------------------------------------*/
/* This function calculate the tuning frequency of the port for a bass-reflex speaker         */
/*--------------------------------------------------------------------------------------------*/
{
    double F;                     // Tuning frequency based on cabinet parameters

	return(0);
}
/*--------------------------------------------------------------------------------------------*/
double effective_port(Speaker* drvr, double Vbv, double Dp, double Fb, double kappa)
/*--------------------------------------------------------------------------------------------*/
/* This function computes the effective port length for the speaker. This is used by all of   */
/* the vented speaker construction methods (bass reflex, QBR, ESS).                           */
/*--------------------------------------------------------------------------------------------*/
{
    double v1, v2, v3;                // temporary var buffers

	v1 = 2350 * pow(Dp, 2);
	v2 = Fb/Vbv;

	v3 = (v1 * v2)/Fb - kappa;
	return(v3);
}
/*--------------------------------------------------------------------------------------------*/
void cabinet_initialize(Speaker* drvr, double& alpha)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for an initial cabinet volume.                              */
/*--------------------------------------------------------------------------------------------*/
{
	char val[4];

	double cab_val;               // cabinet val input
	double Vbv;                    // non-normlaized volume

    int flag;                     // Decision flag

	flag = 0;

	Vbv = drvr->Vbv * 1000.00;
	//drvr->Vbv = 20 * drvr->Vas * pow(drvr->Qts, 3.3);

	cout << "Manufacturer recommended cabinet size is " << Vbv << ". Specify a new value? (Y) " << endl;
	cin >> val;

	if ((strcmp(val, "Y") == 0) || (strcmp(val, "y") == 0)) {
		// user specified cabinet volume
		cout << "Enter new cabinet volume (liters): ";
		cin >> Vbv;

		drvr->Vbv = Vbv/1000.00;

		alpha = drvr->Vas/drvr->Vbv;

		drvr->f3_vent = drvr->Fs * pow(alpha, 0.44);

		//drvr->Fb = drvr->f3_vent * pow(alpha, 0.31);
	}
	else {
		// Natural flat alignment based on T/S params
		drvr->f3_vent = 0.28 * drvr->Fs * pow(drvr->Qts, -1.4);

		alpha = drvr->Vbv/drvr->Vas;

	}

	cout << "-----------------------------------------" << endl;
	cout << " Cabinet Volume m^3 - " << drvr->Vbv << endl;
	cout << " Vas/Vb ratio       - " << alpha << endl;
}
/*--------------------------------------------------------------------------------------------*/
void acoustic_compliance(Speaker* drvr, double& Ca)
/*--------------------------------------------------------------------------------------------*/
/* This function computes the acoustic compliance for a given driver/cabinet                  */
/*--------------------------------------------------------------------------------------------*/
{
    double var1, var2;                            // placeholder vars
	
	Ca = drvr->Vbv/drvr->Vas;

	cout << " Acoustic compliance   - " << Ca << endl;
}
/*--------------------------------------------------------------------------------------------*/
void port_tuning(Speaker* drvr, int val)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will compute the tuning frequency (Fb) for a given cabient and then         */
/* design/define the port length of the port vent.                                            */
/*--------------------------------------------------------------------------------------------*/
{
	double k;                          // ESB scaling fctor
	double Va;                         // used to calculate the value of k(appa)


	Va = sqrt(drvr->Vas/drvr->Vbv);

	if (val == 1) {
	    // For typical Bass Reflex use k(appa) as a ratio of the sq root of Va to Box Volume
	    drvr->Fb = 0.42 * drvr->Fs;
	} else if (val == 2) {
	    // Moderately aggressive bass response
	    drvr->Fb = 0.38 * drvr->Fs;
	} else if (val == 3 ) {
	    // Aggressive bass response
	    drvr->Fb = 0.33 * drvr->Fs;
	} else {
		// assume Fb == Fs
	    drvr->Fb = drvr->Fs;
    }

}
/*--------------------------------------------------------------------------------------------*/
void port_tuning_pr(Speaker* drvr, Speaker* pasv_cpy)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will compute the tuning frequency (Fb) for a given cabient and then         */
/* design/define the port length of the port vent.                                            */
/*--------------------------------------------------------------------------------------------*/
{
	double diff;                       // Difference between PR Fs vs Woof Fs
	double k;                          // ESB scaling fctor
	double Va;                         // used to calculate the value of k(appa)

	double var1, var2, var3;           // values used for determining port tuning

	Va = sqrt(drvr->Vas/drvr->Vbv);

	diff = drvr->Fs - pasv_cpy->Fs;

	cout << "Debug Resoance Frequency comparison for Mms computation..." << endl;
	cout << diff << " Hz" << endl;

	drvr->Fb = drvr->Fs;

	var1 = pow((2 * M_PI * pasv_cpy->Fs), 2) * pasv_cpy->Cms;
	pasv_cpy->Mms = 1/var1;


	//pasv_cpy->Fs = var2 * sqrt(var3);

}
/*--------------------------------------------------------------------------------------------*/
void port_length(Speaker* drvr, double kappa)
/*--------------------------------------------------------------------------------------------*/
/* port_length() is used to determine the effective port length for the specifed cabinet      */
/* volume, tuning frequnecy and port correction factor (kappa) for units in mm.               */
/* L(total) = L(eff) - L(correction) where:                                                   */
/* L(eff) = (scale * (Dp)^2)/(Fb * Vb)                                                        */
/* L(correct) =  -1.0 * (kappa * Dp)                                                          */
/*--------------------------------------------------------------------------------------------*/
{
    double Ap;                    // Port area computation A = 2* PI * Dp/2

	double scale = 0.023562;        // constant value 0.023562 in mm
	double length;                // port length calculation

	double var1, var2, var3;      // temporary storage values

	var1 = scale * pow(drvr->b_diam, 2);
	var2 = pow(drvr->Fb, 2) * drvr->Vbv;
	var3 = kappa * drvr->b_diam;
	drvr->v_length = var1/var2 - var3;
	
}
/*--------------------------------------------------------------------------------------------*/
void port_length_slot(Speaker* drvr, double kappa, double& height, double& width)
/*--------------------------------------------------------------------------------------------*/
/* This procedure is used to determine the port length for a rectangular port on a speaker    */
/*--------------------------------------------------------------------------------------------*/
{
    double Ap;                    // Port area calculation

	double d, var1, var2;         // intermediate values used for port length calculation
	double k_cor;                 // Correction value 
	double Ht;                    // Port height 


	// Compute height and width of port vis driver surface area
	Ap = drvr->Sd * 0.10;

	// Compute slot area based on 3:1 ratio of height vs width
	width = sqrt(Ap/3);
	height = 3 * width;

	d = 2 * M_PI * drvr->Fb;

	k_cor = kappa * sqrt(Ap);
	
	var1 = pow((C/d), 2);

	var2 = (var1 * drvr->Vbv)/Ap;

	drvr->v_length = var2 - k_cor;

	cout << "---------- DEBUG -------- " << endl;
	cout << " kappa       : "<< kappa << endl;
	cout << " Sd          : "<< drvr->Sd << endl;
	cout << " Fb (tune)   : "<< drvr->Fb << endl;
	cout << " Vbv (vol)   : "<< drvr->Vbv << endl;
	cout << " Port area   : "<< Ap << endl;
	cout << " port length : "<< drvr->v_length << endl;
	cout << " port width  : "<< width << endl;
	cout << " port height : "<< height << endl;
}
/*--------------------------------------------------------------------------------------------*/
void port_length_pr(Speaker* drvr, Speaker* pasv_cpy, double kappa)
/*--------------------------------------------------------------------------------------------*/
/* This procedure is used to determine the optimum mass for a passive radiator used in place  */
/* of a slotted or circular port due to size restrictions.                                    */
/*--------------------------------------------------------------------------------------------*/
{
    cout << "dummy name" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void data_normalize(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
{
	cout << "Normalize data... " << endl;

    drvr->Vas = drvr->Vas/1000.00;
    cout << "DEBUG: Vas(normalized) - " << drvr->Vas << endl;
    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
