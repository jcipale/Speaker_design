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
#include "compute.h"
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
void cabinet_initialize(Speaker* drvr, Speaker* pasv, double coeff, double& Area, int bdesign)
/*--------------------------------------------------------------------------------------------*/
/* This function will determine the cabinet volume and the tuning frequency of the bass       */
/* cabinet/subwoofer.                                                                         */
/*--------------------------------------------------------------------------------------------*/
{
    char val[4];
    char sys[4];
    char pdm[4];

    double ap;                    // Aspect ratio of slotted port
    double Ap;                    // Area of circular port
    double Alp, Bet;              // alpha value for passive radiator design
    double var1, var2, var3;      // Temp values used to determine Vb and Fb

    double cab_val;               // cabinet val input

    double kappa;                 // Scaling factor for Extended base Shelf designs 
	                              // - default is 2.125
	double length;                // port length
    double scalar;                // Scale factor for cabinet alignment - slotted design only 
	                              // - default is 15
	double Mma;                   // Mass to add for passive radiator to tune to target frequency
	double Mttl;                  // Total mass of the passive radiator determined by the Fb value
    double Qtc;                   // Total system Q - approx 0.37 for stanfard vented design
    double Vbv;                   // non-normlaized volume

    int flag;                     // Decision flag
	int option;                   // used by switch statment

    flag = 0;
    Vbv = drvr->Vbv * 1000.00;

    if (bdesign == 1) {
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
		cout << " * Choose a new cabinet value? (Y/N) : ";
		cin >>sys;

        if ((strcmp(sys, "Y") == 0) || (strcmp(sys, "y") == 0)) {
		    cout << "Specify new cabinet volume: " << endl;
			cout << " 1) Keep default value " << Vbv << endl;
			cout << " 2) Specify based on mulitiplier of " << coeff << " * Vas " << endl;
			cout << " 3) User specified value " << endl;
			cin >> option;

			switch(option) {
                case 1:
				    cout << "Default value is " << Vbv << endl;
					drvr->Vbv = Vbv/1000.00;

					break;
                case 2:
				    cout << "Coefficient value is " << coeff << endl;
					drvr->Vbv = (coeff * drvr->Vas);
					
					break;
                case 3:
				    cout << "Enter desired cabinet size: ";
					cin >> drvr->Vbv;
					drvr->Vbv = drvr->Vbv/1000.00;
					
					break;
				default:
				    cout << "Invalid selection..." << endl;

					break;
		    }
		}

		// Enter and normalize diameter/slot size to m^3
        cout << "+-----------------------------------+" << endl;
        cout << "| Specify the port area in mm^2:    |" << endl;
        cout << "| 1 cm <==> 10 mm                   |" << endl;
        cout << "+-----------------------------------+" << endl;
        cin >> drvr->v_diam;
        drvr->v_diam = drvr->v_diam/1000.0;

	    diffusion_menu(kappa);

		// Solve for port area opening
		Area = M_PI * pow((drvr->v_diam/2), 2);

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = Area/drvr->Vbv;

		length = var1 * var2;
		
		drvr->v_length = length - (kappa * drvr->v_diam);

    } else if (bdesign == 2 ) {
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
		cout << " * Choose a new cabinet value? (Y/N) : ";
		cin >>sys;

        if ((strcmp(sys, "Y") == 0) || (strcmp(sys, "y") == 0)) {
		    cout << "Specify new cabinet volume: " << endl;
			cout << " 1) Keep default value " << Vbv << endl;
			cout << " 2) Specify based on mulitiplier of " << coeff << " * Vas " << endl;
			cout << " 3) User specified value " << endl;
			cin >> option;

			switch(option) {
                case 1:
				    cout << "Default value is " << Vbv << endl;
					drvr->Vbv = Vbv/1000.00;

					break;
                case 2:
				    cout << "Coefficient value is " << coeff << endl;
					drvr->Vbv = (coeff * drvr->Vas);
					
					break;
                case 3:
				    cout << "Enter desired cabinet size: ";
					cin >> drvr->Vbv;
					drvr->Vbv = drvr->Vbv/1000.00;
					
					break;
				default:
				    cout << "Invalid selection..." << endl;

					break;
		    }
		}

		// Enter and normalize diameter/slot size to m^3
        cout << "+-----------------------------------+" << endl;
        cout << "| Specify the port area in mm^2:    |" << endl;
        cout << "| 1 cm <==> 10 mm                   |" << endl;
        cout << "+-----------------------------------+" << endl;
        cin >> drvr->v_diam;
        drvr->v_diam = drvr->v_diam/1000.0;

	    diffusion_menu(kappa);

		// Solve for port area opening
		Area = M_PI * pow((drvr->v_diam/2), 2);

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = Area/drvr->Vbv;

		length = var1 * var2;
		
		drvr->v_length = length - (kappa * drvr->v_diam);

    } else if (bdesign == 3) {
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
		cout << " * Choose a new cabinet value? (Y/N) : ";
		cin >> sys;

        if ((strcmp(sys, "Y") == 0) || (strcmp(sys, "y") == 0)) {
		    cout << "Specify new cabinet volume: " << endl;
			cout << " 1) Keep default value " << Vbv << endl;
			cout << " 2) Specify based on mulitiplier of " << 3.0 << " * Vas " << endl;
			cout << " 3) Specify based on mulitiplier of " << 3.5 << " * Vas " << endl;
			cout << " 4) User specified value " << endl;
			cin >> option;

			switch(option) {
                case 1:
				    cout << "Default value is " << Vbv << endl;
					drvr->Vbv = Vbv/1000.00;

					break;
                case 2:
				    cout << "Coefficient value is 3.0" << endl;
					drvr->Vbv = (3.0 * drvr->Vas);
					
					break;
                case 3:
				    cout << "Coefficient value is 3.5 (deeper bass)" << endl;
					drvr->Vbv = (3.5 * drvr->Vas);
					
					break;
                case 4:
				    cout << "Enter desired cabinet size: ";
					cin >> drvr->Vbv;
					drvr->Vbv = drvr->Vbv/1000.00;
					
					break;
				default:
				    cout << "Invalid selection..." << endl;

					break;
		    }
		}

		// Solve for port area opening
		Area = drvr->Sd * 0.05;
		Ap = Area * 1e6;
        cout << "+--------------------------------------+" << endl;
		cout << "| Recommended slot area is: " << Ap << " mm^2 |" << endl;
        cout << "| Specify the slot area in mm^2: (Y/N) |" << endl;
        cout << "| 1 cm <==> 10 mm                      |" << endl;
        cout << "+--------------------------------------+" << endl;
		cin >> sys;

		if (( strcmp(sys, "Y") == 0 )||(strcmp(sys, "y") == 0 )) {
            //cin >> drvr->v_diam;
            //drvr->v_diam = drvr->v_diam/1000.0;
            cin >> Area;
            Area = Area/1000.0;
		}

		// user selected value for kappa and aspect ratio of slotted port
		aspect_kappa(ap, kappa);

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		// Solve for slot dimensions
		drvr->v_height = sqrt(Area/ap);
		drvr->v_width = ap * drvr->v_height;

		// solve for port length
		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = Area/drvr->Vbv;

		length = var1 * var2;

		drvr->v_length = length - (kappa * Area);
		
    } else if (bdesign == 4) {
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
        cout << "Specify a new value based on Thiel/Small Specifications? (Y/N) " << endl;
        cin >> val;

        if ((strcmp(val, "Y") == 0) || (strcmp(val, "y") == 0)) {
            cin >> drvr->Vbv;
		    drvr->Vbv = coeff *drvr->Vbv/1000.00;
		}

        // Solve for total mass of Passive Radiator
		var1 = 1.42e5 * pasv->Sd;
		var2 = pow((2 * M_PI * drvr->Fb), 2) * drvr->Vbv;

		Mttl = var1/var2;

		var3 = pasv->Mms;

		pasv->Mms = Mttl - var3;
    }

    cout << "-----------------------------------------" << endl;
    cout << " Cabinet Volume m^3 - " << drvr->Vbv << endl;
    cout << " Tuned frequency    - " << drvr->Fb << endl;
    //cout << " Vas/Vb ratio       - " << alpha << endl;
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
        //drvr->Vbv = 20 * drvr->Vas * pow(drvr->Qts, 3.3);
        drvr->Fb = 0.42 * drvr->Fs;
    } else if (val == 2) {
        // Moderately aggressive bass response
        drvr->Fb = 0.38 * drvr->Fs;
    } else if (val == 3 ) {
        // Aggressive bass response
        drvr->Fb = 0.33 * drvr->Fs;
    } else if (val == 4 ) {
        // assume Fb == Fs
        drvr->Fb = drvr->Fs;
    }
}
/*--------------------------------------------------------------------------------------------*/
void port_tuning_pr(Speaker* drvr, Speaker* pasv_cpy, Cabinet* box)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will compute the tuning frequency (Fb) for a given cabient and then         */
/* design/define the port length of the port vent.                                            */
/*--------------------------------------------------------------------------------------------*/
{
	char ans[4];                       // Y/N to change Fb
	double diff, split;                // Difference between PR Fs vs Woof Fs
	double Fb;                         // New target tuning frequency
	double Mms;                        // Required mass to meet Fb requirments of Passive Radiator
	double ms_df;                      // Amount of mass that needs to be added to the 
	                                   // passive readiator to meet the design goals
	double Va;                         // used to calculate the value of k(appa)

	double var1, var2, var3;           // values used for determining port tuning

	int flag;                          // flag used to determine Fb for design

	flag = 0;

	drvr->Fb = drvr->Fs;

	cout << "Debug Resoance Frequency comparison for Mms computation..." << endl;
	cout << "Bass Fs - " << drvr->Fs << " Passive Fs - " << pasv_cpy->Fs << endl;

	while (!flag) {
	    cout << "Recommended Fb is " << drvr->Fb << " Hz. Keep or specify a new Fb value? (Y/N)" << endl;
		cin >> ans;

		if ((strcmp(ans, "Y") == 0) || (strcmp(ans, "y") == 0)) {
		     cout << "Enter target Fb for cabinet: ";
			 cin >> drvr->Fb;
		}

		flag = 1;
	}

	// Set the PR space to the same frequency tuning
	box->Fb = drvr->Fb;
	
	box->Mms = SolveMass(drvr->Sd, pasv_cpy->Sd, drvr->Fb, drvr->Vbv);

	//ms_df = Mms - pasv_cpy->Mms;
	ms_df = box->Mms - pasv_cpy->Mms;

	cout << "Passive Radiator Mass is = " << pasv_cpy->Mms << endl;
	cout << "Total Mass to adjust Passive Radiator to new Fb = " << ms_df << endl;
	cout << "Total adjusted mass of PR " << box->Mms;
	cout << "Mass delta = " << ms_df << endl;

	var1 = (1/2 * M_PI);
	box->Cms = pasv_cpy->Cms;
	var2 = sqrt(1/(box->Mms * box->Cms));
	box->Fb = var1 * var2;

	cout << "DEBUG " << endl;
	cout << "-------------------------------------" << endl;
	cout << "Passive Fb    : " << pasv_cpy->Fb << endl;
	cout << "Bass Fb       : " << drvr->Fb << endl;
	cout << "PassRad Mass  : " << pasv_cpy->Mms << endl;
	cout << "Pass init mass: " << drvr->Mms << endl;
	cout << "PassRad Cms   : " << pasv_cpy->Cms << endl;
}
/*--------------------------------------------------------------------------------------------*/
void port_length(Speaker* drvr, double ap, double &kappa, int type)
/*--------------------------------------------------------------------------------------------*/
/* port_length() is used to determine the effective port length for the specifed cabinet      */
/* volume, tuning frequnecy and port correction factor (kappa) for units in mm.               */
/* L(total) = L(eff) - L(correction) where:                                                   */
/* L(eff) = (scale * (Dp)^2)/(Fb * Vb)                                                        */
/* L(correct) =  -1.0 * (kappa * Dp)                                                          */
/*--------------------------------------------------------------------------------------------*/
{
    double Ap;                    // Port area computation A = PI * (Dp/2)^2
    double ar;                    // Port aspect ratio

    //double scale = 0.023562;        // constant value 0.023562 in mm
    double scale = 23562;        // constant value 0.023562 in mm
    double length;                // port length calculation
    

    double var1, var2, var3;      // temporary storage values

    if ((type == 1) || (type == 2) || (type == 3)) {
        // Standard port design
        Ap = M_PI * pow((drvr->Pd/2), 2);
        var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
        var2 = drvr->Vbv/Ap;
        var3 = kappa * (drvr->Pd/2);

        drvr->v_length = var1 * var2 - var3;

        cout << "D E B U G : diameter = " << drvr->v_diam << endl;
        cout << "D E B U G : length = " << drvr->v_length << endl;
    } else {
        // Slotted Port design
        aspect_kappa(ar, kappa);

        //drvr->Pd = drvr->Sd/3;
        drvr->Pd = 0.05 * drvr->Vbv;

        drvr->v_height = sqrt(drvr->Pd/ar);
        drvr->v_width = ar * drvr->v_height;
        cout << "D E B U G : height = " << drvr->v_height << endl;
        cout << "D E B U G : width  = " << drvr->v_width << endl;
        cout << "D E B U G : length = " << drvr->v_length << endl;
    }

}
/*--------------------------------------------------------------------------------------------*/
void port_length_slot(Speaker* drvr, double ap, double kappa)
/*--------------------------------------------------------------------------------------------*/
/* This procedure is used to determine the port length for a rectangular port on a speaker    */
/*--------------------------------------------------------------------------------------------*/
{
    double Ap;                    // Port area calculation

	double d, var1, var2;         // intermediate values used for port length calculation
	double k_cor;                 // Correction value 
	double Ht;                    // Port height 


	// Compute height and width of port via driver surface area
	Ap = drvr->Sd * 0.10;

	// Compute slot area based on 3:1 ratio of height vs width
	Ap = sqrt(Ap/3);
	drvr->v_height = sqrt(Ap/3);
	drvr->v_width = ap * drvr->v_height;

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
	cout << " port width  : "<< drvr->v_width << endl;
	cout << " port height : "<< drvr->v_height << endl;
}
/*--------------------------------------------------------------------------------------------*/
void port_dynamics(Speaker* drvr, int type, double& PAR, double& PER)
/*--------------------------------------------------------------------------------------------*/
/* This procedure is used to determine the PAR and PER for various vented configurations.     */
/* This procedure is not executed for the passive radiator design option.                     */
/*--------------------------------------------------------------------------------------------*/
{
	double Dp;                // Port diameter
	double Sv;                // Area of the vent
	double Vpm;               // Air velocity (max) at the port
	double Vdm;               // Air velocity (max) at the diaphragm

    cout << "Compute PAR/PER values for vented designs..." << endl;

	if (type == 0) {
	    cout << "compute PAR based on ported design..." << endl;

		// Solve port velocity based on a cylindrical port
		Dp = 2 * sqrt(drvr->Sd/M_PI);

		// Solve for cross sectional area od vent
		Sv = (M_PI * pow(drvr->v_diam, 2))/4;

		// Solve for air velocity max @ the port
		Vpm = (drvr->Xmax * drvr->Sd)/Sv;

		// Solve for air velocity max @ the diaphragm
		Vdm = drvr->Xmax * drvr->Sd;

		// compute PAR
		PAR = Vpm/Vdm;

	    // Compute Peak Excursion Ratio
	    PER = drvr->Xmax * (drvr->Fb/drvr->Fs);
    } else if (type == 1) {
	    cout << "compute PAR based on slotted design..." << endl;

		// Solve port velocity based on a cylindrical port
		Dp = 2 * sqrt(drvr->Sd/M_PI);

		// Solve for cross sectional area od vent
		Sv = (M_PI * pow(drvr->v_diam, 2))/4;

		// Solve for air velocity max @ the port
		Vpm = (drvr->Xmax * drvr->Sd)/Sv;

		// Solve for air velocity max @ the diaphragm
		Vdm = drvr->Xmax * drvr->Sd;

		// compute PAR
		PAR = Vpm/Vdm;

	    // Compute Peak Excursion Ratio
	    PER = drvr->Xmax * (drvr->Fb/drvr->Fs);
    } else {
		// PAR does not exist for a passive radiator
		PAR = 0;

	    // compute Peak Excustion Ratio
	    PER = drvr->Xmax * (drvr->Fb/drvr->Fs);
	}
}
/*--------------------------------------------------------------------------------------------*/
void cabinet_ripple(Speaker* drvr, Speaker* pasv_cpy, int i)
/*--------------------------------------------------------------------------------------------*/
/* This function calculate the -3db ripple for all of the vented cabinet designs.             */
/*--------------------------------------------------------------------------------------------*/
{
	double Mair;          // Mass of air in the cabinet

    // Determine the proper expresion got -3db ripple
	if (i == 1) {
	    drvr->f3_vent = drvr->Fb * sqrt(1 - (1/(4 * pow(drvr->Qts, 2))));
	} else {
		// Compute the Total Q for a Passive Radiator
	    pasv_cpy->Qts = drvr->Qts/(sqrt(1 + (1.8 * drvr->Vbv/pasv_cpy->Mms)));
		
	    drvr->f3_vent = drvr->Fb * sqrt(1 - (1/(4 * pow(drvr->Qts, 2))));
	}    
}
/*--------------------------------------------------------------------------------------------*/
double SolveMass(double drvr, double pr, double Fb, double Vb)
/*--------------------------------------------------------------------------------------------*/
/* This function solves the necessary mass of the passive rafiator to meet the needed Fb value*/
/* for a given cabinet size, speaker area and passive radiator area.                          */
/*--------------------------------------------------------------------------------------------*/
{
    double var1, var2, var3;           // Temporary values used for computation

	var1 = (pow(C, 2) * drvr);

	var2 = pow((2 * M_PI * Fb), 2);

	var3 = pr/Vb;

	return(var1/(var2 * var3));
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
