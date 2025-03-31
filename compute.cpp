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
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstring>
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
double compute_efficiency(Speaker* drvr, double type)
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    
	ptr = drvr;

	double efficency;

	efficency = (pow((2 * M_PI)*(ptr->Fs),3)) * (ptr->Vas)/(pow(C,3) * (ptr->Qes/type));

	return(efficency);
}
/*--------------------------------------------------------------------------------------------*/
void cabinet_design(Speaker* drvr, Cabinet*& box, std::string cab_type)
/*--------------------------------------------------------------------------------------------*/
{
    //struct Speaker *ptr;
    //struct Cabinet *cptr;

    //ptr = drvr;
    //cptr = box;
   
    char flag[4];
    char unit[4];
	
    double width;

	double met_to_in;
	double cubm_to_cubin;
	double sqm_to_sqi;
	/*
    double vol;
    double spkr_diam;
    double spkr_depth;
    double spkr_height;
    double port_length;
    double port_diam;
	*/

    int done;

    cout << "Use Metric (M) or Imperial (I) units of measure? (Metric is default): ";
    cin >> unit;

    // Embedded logic to ignore the vent width value if this is NOT a ported loudspeaker design
    if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0)) {
	    met_to_in = 39.37;
	    cubm_to_cubin = 61020.00;
	    sqm_to_sqi = 1550;
    } else {
	    met_to_in = 1;
	    cubm_to_cubin = 1;
	    sqm_to_sqi = 1;
	}

	// Copy over data from speaker to cabinet strcuture
	box->cab_volume = drvr->Vbs * cubm_to_cubin;
    box->gross_volume = box->gross_volume * cubm_to_cubin;
	box->port_volume = box->port_volume * cubm_to_cubin;
    box->diam = box->diam * met_to_in;
    box->height = box->height * met_to_in;
    box->depth = box->depth * met_to_in;
    box->port_area = box->port_area * sqm_to_sqi;
    box->port_diam = box->port_diam * met_to_in;
    box->port_width = box->port_width * met_to_in;
    box->port_length = box->port_length * met_to_in;

    sleep(5);

	done = 0;

	// Compute baffle width

    while (!done) {
        // Loop to determine box dimensions
        cout << "Driver dimensions: " << endl;
        cout <<" Part Number       : " << box->Part_num << endl;
        cout <<" Nominal impedance : " << box->imp_Nom << endl;
        cout <<" Frequency - low   : " << box->freq_lo << endl;
        cout <<" Frequency - high  : " << box->freq_hi << endl;
        cout <<" Frequency rolloff : " << box->rolloff << endl;
        cout <<" Resonant frequency: " << box->res_freq << endl;

        if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0 )) {
            cout <<" Cabinet volume: " << box->cab_volume << " in^3" << endl;
            cout <<" Total volume  : " << box->gross_volume << " in^3" << endl;

            if ((cab_type == "vented") || (cab_type == "slotted")) {
                cout <<" Vent area     : " << box->port_area << " in^2 " << endl;
                cout <<" Vent ht/diam  : " << box->port_diam << " inches " << endl;
                if (box->port_width > 0) {
                    cout <<" Vent width    : " << box->port_width << " inches " << endl;
                }
                cout <<" Vent length   : " << box->port_length << " inches " << endl;
            }
            cout << " Driver diameter  : " << box->diam << " inches " << endl;
            cout << " Driver depth     : " << box->depth << " inches " << endl;
            cout << " Driver height    : " << box->height << " inches " << endl;
        } else {
            cout <<" Cabinet volume: " << box->cab_volume << " m^3" << endl;
            cout <<" Total volume: " << box->gross_volume << " m^3" << endl;

            if ((cab_type == "vented") || (cab_type == "slotted")) {
                cout <<" Vent area     : " << box->port_area << " m^2 " << endl;
                cout <<" Vent ht/diam  : " << box->port_diam << " meters " << endl;
                if (box->port_width > 0) {
                    cout <<" Vent width    : " << box->port_width << " meters " << endl;
                }
                cout <<" Vent length   : " << box->port_length << " meters " << endl;
            }
            cout << " Speaker diameter : " << box->diam << " meters " << endl;
            cout << " Speaker depth    : " << box->depth << " meters " << endl;
            cout << " Speaker height   : " << box->height << " meters " << endl;
        }

        // Compute baffle width
        if ((cab_type == "slotted") || (cab_type == "vented")) {
            width = pow((box->gross_volume/0.96), 0.333);
            box->Width = width;
            box->Depth = 0.6 * width;
            box->Height = 1.6 * width;
        /*} else if (strcmp(box->Type, "cone") == 0) {*/
        } else if (cab_type == "sealed") {
            //width = pow((box->cab_volume/0.96), 0.333);
            sleep(5);
            width = pow((box->gross_volume/1.12), 0.333);
            box->Width = width;
            box->Depth = 0.8 * width;
            box->Height = 1.4 * width;
        } else {
            cout << "Electrostatic/Ribbon speaker..." << endl;
            box->Height = box->Height * met_to_in;
            box->Width = box->Width * met_to_in;
            box->Depth = box->Depth * met_to_in;
        }

        cout << "+--------------------------+" << endl;
        cout << "|   Cabinet measurements   |" << endl;
        cout << "+--------------------------+" << endl;
        if ((strcmp(unit, "I") == 0) || (strcmp(unit, "i") == 0 )) {
            cout << "| Width         : " << box->Width << " in" << endl;
            cout << "| Depth         : " << box->Depth << " in" << endl;
            cout << "| Height        : " << box->Height << " in" << endl;
            if (cab_type == "vented") {
                cout << "| Vent diameter : " << box->port_diam << " in " << endl;
                cout << "| Vent length   : " << box->port_length << " in " << endl;
            } else if (cab_type == "slotted") {
                cout << "| Vent ht/width : " << box->port_width << " in " << endl;
                cout << "| Vent length   : " << box->port_length << " in " << endl;
                cout << "| Vent diameter : " << box->port_diam << " in " << endl;
            }
        } else {
            cout << "| Width         : " << box->Width << " m " << endl;
            cout << "| Depth         : " << box->Depth << " m " << endl;
            cout << "| Height        : " << box->Height << " m " << endl;
            if (cab_type == "vented") {
                cout << "| Vent diameter : " << box->port_diam << " m  " << endl;
                cout << "| Vent length   : " << box->port_length << " m  " << endl;
            } else if (cab_type == "slotted") {
                cout << "| Vent ht/width : " << box->port_width << " m  " << endl;
                cout << "| Vent length   : " << box->port_length << " m  " << endl;
                cout << "| Vent diameter : " << box->port_diam << " m  " << endl;
            }
        }

        cout << "+---------------------------+" << endl;
        cout << "Accept dimensions? (Y/N): " << endl;
        cin >> flag;

        if ((strcmp(flag, "Y") == 0) || (strcmp(flag, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            done = 1;
        } else {
            cout << "compute box design..." << endl;
            return;
        }
    }

    cout << "--------------------------------------------" << endl;
    cout << "            Speaker Dimensions              " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  Width:  " << box->Width << endl;
    cout << "  Depth:  " << box->Depth << endl;
    cout << "  Height: " << box->Height << endl;
    cout << "--------------------------------------------" << endl;

    //box = cptr;

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
	    spkr_diam = ptr->b_diam * m_to_inch;
	    spkr_depth = ptr->depth * m_to_inch;
	    spkr_height = ptr->b_height * m_to_inch;
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
/* the conversion value. (i.e. to convert from m  to meters, the conversion value would be    */
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
void vented_cabinet_initialize(Speaker* drvr, Speaker* pasv, double coeff, int bdesign)
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
	double Vd;                    // Volume of the speaker 'sylinder' itself (pi * r^2 * h))
    double Vbv;                   // non-normlaized volume

    int flag;                     // Decision flag
	int option;                   // used by switch statment

    flag = 0;
    //Vbv = drvr->Vbv;
    Vbv = drvr->Vbv * 1000.00;

    if (bdesign == 1) {
		cout << "Bass Reflex design" << endl;
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
		cout << " * Choose a new cabinet value? (Y/N) : ";
		cin >> sys;

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
        cout << "| Specify the port diam in m :      |" << endl;
        cout << "| 1 cm <==> 10 m                    |" << endl;
        cout << "+-----------------------------------+" << endl;
        cin >> drvr->v_diam;
        drvr->v_diam = drvr->v_diam/1000.0;

		// Since diameter is already normalized, we dont need 
		// to repeat the process
		drvr->w_height = drvr->v_diam;
		drvr->w_width = drvr->v_diam;

	    diffusion_menu(kappa);

		// Solve for port area opening
		drvr->Area = M_PI * pow((drvr->v_diam/2), 2);

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = drvr->Area/drvr->Vbv;

		length = var1 * var2;

		drvr->p_length = length - (kappa * drvr->v_diam);

		// Compute the gross cabinet volume
		drvr->Volume = drvr->Area * drvr->p_length;
		
		drvr->Vd = M_PI * (pow((drvr->b_diam/2), 2) * drvr->depth);
		//Spkr_Vol = M_PI * (pow((drvr->b_diam/2), 2) * drvr->depth);

		// Gross Volume DOES NOT include the value for bracing. 
		// That will be added in after the fact and will require
		// a slight recalculation of the cabinet size.
		drvr->Vol_gross = drvr->Vbv + drvr->Volume + drvr->Vd;

    } else if (bdesign == 2 ) {
		cout << "Extended Bass design" << endl;
        cout << "Recommended cabinet size is " << Vbv << " Liters. " << endl;
		cout << " * Choose a new cabinet value? (Y/N) : ";
		cin >> sys;

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
        cout << "| Specify the port area in m ^2:    |" << endl;
        cout << "| 1 cm <==> 10 m                    |" << endl;
        cout << "+-----------------------------------+" << endl;
        cin >> drvr->v_diam;
        drvr->v_diam = drvr->v_diam/1000.0;

		// Since diameter is already normalized, we dont need 
		// to repeat the process
		drvr->w_height = drvr->v_diam;
		drvr->w_width = drvr->v_diam;

	    diffusion_menu(kappa);

		// Solve for port area opening
		drvr->Area = M_PI * pow((drvr->v_diam/2), 2);

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = drvr->Area/drvr->Vbv;

		length = var1 * var2;
		
		drvr->p_length = length - (kappa * drvr->v_diam);

		// Compute the gross cabinet volume
		drvr->Volume = drvr->Area * drvr->p_length;
		
		drvr->Vd = M_PI * (pow((drvr->b_diam/2), 2) * drvr->depth);

		// Gross Volume DOES NOT include the value for bracing. 
		// That will be added in after the fact and will require
		// a slight recalculation of the cabinet size.
		drvr->Vol_gross = drvr->Vbv + drvr->Volume + drvr->Vd;

    } else if (bdesign == 3) {
		cout << "Slotted Port design" << endl;
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
				    cout << "Default value is " << drvr->Vbv << endl;
					//drvr->Vbv = Vbv/1000.00;

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
		drvr->Area = drvr->Sd * 0.05;
		
        cout << "+----------------------------------------+" << endl;
		cout << "| Recommended slot area is: " << drvr->Area << " m ^2 |" << endl;
        cout << "| 1 cm <==> 10 m                         |" << endl;
        cout << "+----------------------------------------+" << endl;

        cin >> drvr->Area;
        drvr->Area = drvr->Area/1e6;

		// user selected value for kappa and aspect ratio of slotted port
		aspect_kappa(ap, kappa);

		// Solve for slot dimensions
		drvr->w_height = sqrt(drvr->Area/ap);
		drvr->w_width = ap * drvr->w_height;

		drvr->Fb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);

		// solve for port length
		var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
		var2 = drvr->Area/drvr->Vbv;

		length = var1 * var2;

		drvr->p_length = length - (kappa * drvr->Area);

		// Compute the gross cabinet volume
		// Gross Volume DOES NOT include the value for bracing. 
		// That will be added in after the fact and will require
		// a slight recalculation of the cabinet size.

		// Compute the speaker driver volume
		drvr->Volume = drvr->Area * drvr->p_length;
		
		drvr->Vd = M_PI * (pow((drvr->b_diam/2), 2) * drvr->depth);

		drvr->Vol_gross = drvr->Vbv + drvr->Volume + drvr->Vd;
		
    } else if (bdesign == 4) {
		cout << "Passive Radiator design" << endl;
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

		// For Passive Radiator design, Fb is approx to Fs...
		drvr->Fb = drvr->Fs;

        // Solve for total mass of Passive Radiator
		var1 = 1.42e5 * pow(pasv->Sd, 2);
		var2 = pow((2 * M_PI * drvr->Fb), 2) * drvr->Vbv;

		Mttl = var1/var2;

		var3 = pasv->Mms;

		pasv->Mas = Mttl - var3;

		if (pasv->Mas < 0) {
		    cout << "The required mass for this design is too low. " << endl;
			cout << "Select a differnt Passive Radiator with a driver mass (Mms)." << endl;

			// since we can not arrive at a workable solution, we escape the procedure
			return;
		}

		// Compute the gross cabinet volume
		// For the passive radiator, the speaker 'cylinder' need to be 
		// included in the gross volume computations.
		pasv->Vd = pasv->Sd * pasv->Xmax;
		
		drvr->Vd = M_PI * (pow((drvr->b_diam/2), 2) * drvr->depth);

		// Gross Volume DOES NOT include the value for bracing. 
		// That will be added in after the fact and will require
		// a slight recalculation of the cabinet size.
		pasv->Area = pow((pasv->b_diam/2), 2) * M_PI;
		pasv->Vd = (pasv->Area * pasv->depth)/1e9;

		cout << "Cabinet : " << drvr->Vbv << endl;
		cout << "Drv Vol : " << drvr->Vd << endl;
		cout << "Pass Vol: " << pasv->Vd << endl;
		drvr->Vol_gross = drvr->Vbv + drvr->Vd + pasv->Vd;
		cout << "Total Volume : " << drvr->Vol_gross << endl;
		
    }
}
/*--------------------------------------------------------------------------------------------*/
void power_dynamics(Speaker* drvr, int type)
/*--------------------------------------------------------------------------------------------*/
/* This function computes the power dynamics for a given vented driver/cabinet                */
/*--------------------------------------------------------------------------------------------*/
{
	double Fsb;                    // Air displacement Xmx * Sd (piston area)
	double Qtc;
	double D;
	double Q;                     // Used to solve Per based on type of cabinet (sealed or vented)
	double F;                     // Frequency dependent on cabinet type - sealed or vented.
	double v1, v2, v3, v4;        // Temp vars for Par/Per calcs

	double PE, Pe, PA, Pa;

	double n;                     // A constant factor to determine the limited power-displacement


	if (type == 1) {
	    F = drvr->f3_vent;
		Q = drvr->Qts;
		D = 3e8;
		Fsb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbv);
	    n = (pow(Fsb, 3) * drvr->Vas)/drvr->Qts;
		Qtc = drvr->Qts * sqrt(drvr->Vas/drvr->Vbv);
		v1 = pow(F, 4) * pow(drvr->Vd, 2);

		drvr->Par = v1/3e8;
		drvr->Per = (drvr->Per * 1.2e6)/n;

		drvr->Rh = abs(20 * log((drvr->Fb * drvr->Qts)/(0.4 * Fsb)));
    } else {
	    F = drvr->f3_seal;
		Q = drvr->Qts;
		D = 1.2e9;
		Fsb = drvr->Fs * sqrt(drvr->Vas/drvr->Vbs);
	    n = (pow(Fsb, 3) * drvr->Vas)/drvr->Qts;
		Qtc = drvr->Qts * sqrt(drvr->Vas/drvr->Vbs);
		v1 = pow(F, 4) * pow(drvr->Vd, 2);

		drvr->Par = v1/1.2e9;
		drvr->Per = drvr->Per/(n * 1e3);

		drvr->Rh = abs(20 * log((Qtc)/(0.4)));
	}

	sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void frequency_response_sealed(Speaker* drvr, double Qtc, std::string plot)
/*--------------------------------------------------------------------------------------------*/
/* This procedure writes the frequency repsonse of the specific vented loudspeaker            */
/*--------------------------------------------------------------------------------------------*/
{
    /* The following values are used as temporary storage vars for calculating the freq response */
    double Fn;             // Normalization of frequency

    double A;              // temporary variable to hold data
	double Fr;             // Intermediate frequency
	double R;              // Value of transfer function H(f) at f

	//double Qtc;            // System Q

	double a, b, c, d;     // vars used to store data frm transfer fucntion H(f)

	int freq;              // Loop variable used for H(f)

	ofstream datafile;
    datafile.open(plot);

	if (drvr->Vas > 0) {
	    Qtc = sqrt(pow(drvr->Qts, 2) + (drvr->Vas/drvr->Vbs));
	}

	A = (1/pow(Qtc, 2)) - 2;

    cout << " Frequeny Response H(f) for " << drvr->Part_num << endl;
    datafile << " Frequeny Response H(f) for " << drvr->Part_num << endl;
    cout << " -------|---------------" << endl;
    cout << "  Freq  : H(f) " << endl;
    datafile << "Freq ; H(f)" << endl;
    cout << " -------|---------------" << endl;

    for (freq = drvr->Freq_Low; freq <= (drvr->Freq_Hi + 50) ; freq += 50) {

        Fn = freq/drvr->Fc;
        
		Fr = 10 * log(pow(Fn, 4)/(pow(Fn, 4) + A*(pow(Fn, 2)) + 1));

		R = abs(Fr);

		cout << "  " << freq << " | " << R << endl;
        datafile << "  " << freq << " ; " << R << endl;
		}
    cout << " -------|---------------" << endl;

    datafile.close();
}
/*--------------------------------------------------------------------------------------------*/
void high_frequency_sealed(Speaker* drvr, double Qtc, std::string plot)
/*--------------------------------------------------------------------------------------------*/
/* This procedure writes the frequency repsonse of the specific high_frequency loudspeaker    */
/* This is used by both midranges and tweeter speakers to determine the freq response overall.*/
/*--------------------------------------------------------------------------------------------*/
{
    double omega;     // the values for omega* are used to compute the transfer function for
	double omega_c;   // the driver without using Vas since the cabinet is typically too small

	double num, denom;// Used to compute resultant value of H(f) for a fiven frequency (f)

	double R;         // result of transfer function, H(f)

	int freq;         // loop counter used for H(f) calculations

	ofstream datafile;
    datafile.open(plot);

	cout << " Frequeny Response H(f) for " << drvr->Part_num << endl;
    datafile << " Frequeny Response H(f) for " << drvr->Part_num << endl;
    cout << " -------|---------------" << endl;
    cout << "  Freq  : H(f) " << endl;
    datafile << "Freq ; H(f)" << endl;
    cout << " -------|---------------" << endl;
	sleep(5);

    for (freq = drvr->Freq_Low; freq <= (drvr->Freq_Hi + 50); freq += 50) {
	    omega = pow((2 * M_PI * freq), 2);
	    omega_c = pow((2 * M_PI * drvr->Fc), 2);

		complex<double> num = pow(omega, 2);
		complex<double> denom = pow(omega, 2) + complex<double>(0, (omega * omega_c)/Qtc) + pow(omega_c, 2);

		complex<double> R = 20 * log10(abs(num/denom));

		cout << "  " << freq << " | " << R << endl;
        datafile << "  " << freq << " ; " << R << endl;

	}
	cout << " -------|---------------" << endl;

    datafile.close();
}
/*--------------------------------------------------------------------------------------------*/
void frequency_response_vented(Speaker* drvr, std::string plot)
/*--------------------------------------------------------------------------------------------*/
/* This procedure writes the frequency repsonse of the specific vented loudspeaker            */
/*--------------------------------------------------------------------------------------------*/
{
	/* The following values are used as temporary storage vars for calculating the freq response */
	double Fn;             // Normalization of frequency
	double A, B, C, D, e;  // Intermediate variables used to simplify calculations
	double a, b, c, d;     
	double Fsb;            // System Resonance Frequency

	double Fr;             // Interim frequency response
	double R;

	int freq;              // frequency loop iteration counter.

	
	ofstream datafile;
	datafile.open(plot);


	Fsb = drvr->Fs/(sqrt(1 + drvr->Vas/drvr->Vbv));

	e = (drvr->Fb/(7 * Fsb));

	A = pow(drvr->Fb/Fsb, 2);
	B = (A/drvr->Qts) + e;
	C = (1 - A + drvr->Vas/drvr->Vbv + (e * 1/drvr->Qts));
	D = (1/drvr->Qts) + e;
	
	cout << " Frequeny Response H(f) for " << drvr->Part_num << endl;
	datafile << " Frequeny Response H(f) for " << drvr->Part_num << endl;
	cout << " -------|---------------" << endl;
	cout << "  Freq  : H(f) " << endl;
	datafile << "Freq ; H(f)" << endl;
	cout << " -------|---------------" << endl;
	for (freq = drvr->Freq_Low; freq <= (drvr->Freq_Hi + 50) ; freq += 50) {

	    Fn = freq/Fsb;
		a = C * pow(Fn, 2);
		b = D * pow(Fn, 2);
		c = pow((D * pow(Fn, 2) - B), 2);

		Fr = (pow(Fn, 4)/sqrt(pow((pow(Fn, 4) - a + A), 2) + (pow(Fn, 2) * c)));

		R = abs(20 * log (Fr));
		
		cout << "  " << freq << " | " << R << endl;
		datafile << "  " << freq << " ; " << R << endl;
	}
	cout << " -------|---------------" << endl;

	datafile.close();
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
/* volume, tuning frequnecy and port correction factor (kappa) for units in m .               */
/* L(total) = L(eff) - L(correction) where:                                                   */
/* L(eff) = (scale * (Dp)^2)/(Fb * Vb)                                                        */
/* L(correct) =  -1.0 * (kappa * Dp)                                                          */
/*--------------------------------------------------------------------------------------------*/
{
    double Ap;                    // Port area computation A = PI * (Dp/2)^2
    double ar;                    // Port aspect ratio

    //double scale = 0.023562;        // constant value 0.023562 in m 
    double scale = 23562;        // constant value 0.023562 in m 
    double length;                // port length calculation
    

    double var1, var2, var3;      // temporary storage values

    if ((type == 1) || (type == 2) || (type == 3)) {
        // Standard port design
        Ap = M_PI * pow((drvr->Pd/2), 2);
        var1 = pow(C, 2)/(4 * pow(M_PI, 2) * pow(drvr->Fb, 2));
        var2 = drvr->Vbv/Ap;
        var3 = kappa * (drvr->Pd/2);

        drvr->p_length = var1 * var2 - var3;
    } else {
        // Slotted Port design
        aspect_kappa(ar, kappa);

        //drvr->Pd = drvr->Sd/3;
        drvr->Pd = 0.05 * drvr->Vbv;

        drvr->w_height = sqrt(drvr->Pd/ar);
        drvr->w_width = ar * drvr->w_height;
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
	drvr->w_height = sqrt(Ap/3);
	drvr->w_width = ap * drvr->w_height;

	d = 2 * M_PI * drvr->Fb;

	k_cor = kappa * sqrt(Ap);
	
	var1 = pow((C/d), 2);

	var2 = (var1 * drvr->Vbv)/Ap;

	drvr->p_length = var2 - k_cor;

	cout << "---------- DEBUG -------- " << endl;
	cout << " kappa       : "<< kappa << endl;
	cout << " Sd          : "<< drvr->Sd << endl;
	cout << " Fb (tune)   : "<< drvr->Fb << endl;
	cout << " Vbv (vol)   : "<< drvr->Vbv << endl;
	cout << " Port area   : "<< Ap << endl;
	cout << " port length : "<< drvr->p_length << endl;
	cout << " port width  : "<< drvr->w_width << endl;
	cout << " port height : "<< drvr->w_height << endl;
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
void speaker_to_cabinet(Speaker* drvr, Cabinet*& box, int bdesign)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will copy over some of the contents from the driver to the cabinet structure*/
/* to be used for determining the cabinet physical dimensions.                                */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;     
    ptr = drvr;

	struct Cabinet *temp, *temp_2, *bptr, *patr;
	bptr = box;
    //patr = pass;

	if (box == NULL) {
	    temp = (struct Cabinet *)malloc(sizeof(struct Cabinet));
	    bptr = box;
    }

	/*
	if (bdesign == 3) {
	    strcpy(box->Enclosure, "Slotted_Port");
	} else if (bdesign = 4) {
	    strcpy(box->Enclosure, "Passive_Radiator");
	} else if ((bdesign == 1) || (bdesign == 2)) { 
	    strcpy(box->Enclosure, "Ducted_Port");
	} else {
	    strcpy(box->Enclosure, "Sealed");
	}
	*/

	strcpy(box->Part_num, drvr->Part_num);
    strcpy(box->Build, drvr->Build);
    strcpy(box->Type, drvr->Type);
    box->cab_volume = drvr->Vbv;
    box->port_volume = drvr->Volume;
    box->gross_volume = drvr->Vol_gross;
    box->port_diam = drvr->w_height;
    box->port_width = drvr->w_width;
    box->port_area = drvr->Area;
    box->port_length = drvr->p_length;
    box->diam = drvr->b_height;
    box->height = drvr->b_height;
    box->depth = drvr->depth;
    box->freq_lo = drvr->Freq_Low;
    box->freq_hi = drvr->Freq_Hi;
    box->imp_Nom = drvr->Z_nom;
    box->Sensitivity = drvr->Sensitivity;
    box->res_freq = drvr->Fs;
    box->Fb = drvr->Fb;
	box->PAR = drvr->Par;
	box->PER = drvr->Par;
	box->Rh = drvr->Rh;
	box->next = NULL;

	//bptr = temp;
	sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
