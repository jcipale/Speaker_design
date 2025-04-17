/*--------------------------------------------------------------------------------------------*/
/* speaker_easy.cpp - Primary code file that contains classes, methods and functions.         */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/21/2023:                                                                                */
/* Began code development of classes, methods and objects.                                    */
/*--------------------------------------------------------------------------------------------*/
/* 06/10/2023:                                                                                */
/* Finished build() function to allow user to enter speaker parameters from the data sheet.   */
/*--------------------------------------------------------------------------------------------*/
/* 06/15/2023:                                                                                */
/* Finished parts_list() function to display readout of pointer structure.                    */
/*--------------------------------------------------------------------------------------------*/
/* 06/17/2023:                                                                                */
/* Completed save_speaker() function to write speaker structure to the file system.           */
/*--------------------------------------------------------------------------------------------*/
/* 06/20/2023:                                                                                */
/* Completed read_speaker() function to retrieve data from the file system.                   */
/*--------------------------------------------------------------------------------------------*/
/* 06/20/2023:                                                                                */
/* Began work on vented_box_design() feature.                                                 */
/*--------------------------------------------------------------------------------------------*/
/* 07/06/2023:                                                                                */
/* Revise data entry - use cin() in place of scanf().                                         */
/*--------------------------------------------------------------------------------------------*/
/* 08/15/2023:                                                                                */
/* Completed first pass of gnuplot testing. Work on plotting/displaying data from gnuplot     */
/* data file created by program.                                                              */
/*--------------------------------------------------------------------------------------------*/
/* 10/21/2023:                                                                                */
/* revised/cleaned up vented_box cabinet design. Confirmed computed data values fall in line  */
/* with default/data sheet values.                                                            */
/*--------------------------------------------------------------------------------------------*/
/* 11/07/2023:                                                                                */
/* cleaned up basic closed_box scenarios for speaker design. Determine performance when key   */
/* parameters are missing from the input file. Begin work on determining crossover points.    */
/*--------------------------------------------------------------------------------------------*/
/* 11/16/2023:                                                                                */
/* Implement parameter display for final approved cabinbet design.                            */
/* Implement structures for crossover design.                                                 */
/* Implement functions to design crossover based on 2,3,4 way speaker                         */
/*--------------------------------------------------------------------------------------------*/
/* 12/16/2023:                                                                                */
/* Completed coding/testing on the following functions:                                       */
/*    build()                                                                                 */
/*    save_speaker_data()                                                                     */
/*    parts_list()                                                                            */
/*    read_bass_driver()/read_midrange_driver()/read_tweeter_driver()                         */
/*--------------------------------------------------------------------------------------------*/
/* 06/20/2024:                                                                                */
/* Begin work on revising closed_box_design() function to  derive box internal measurements   */
/* for cabinet construction.                                                                  */
/*--------------------------------------------------------------------------------------------*/
/* 09/27/2024:                                                                                */
/*    Revised loudspeaker design procedures for closed/vented box designs.                    */
/*    Fixed segmaentaion fault by increasing size of string buffer on reading in line from    */
/*    *.sdb file.                                                                             */
/*    Incorporated passive radiator spkr struct and cabinet design.                           */
/*    Created extra field to distinguish between ribbon and cone for tweeter cabinet design.  */
/*    Refactored closed/vented box designs to make better use of tweeter design requirements. */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <string>
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
#include "compute.h"
#include "menus.h"
#undef extern


using namespace std;
using std::cin;
using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------*/
/*                               Global Vars and Constants                                    */
/*--------------------------------------------------------------------------------------------*/
string drvr_dba = "";
string dsgn_data = "";
string drvr_lgth = "";
string plot_data = "";
string plot_name = "";
string pad_string = "";

/*--------------------------------------------------------------------------------------------*/
/*                               Functions and Procedures                                     */
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr, Speaker*& mid, Speaker*& tweet, Speaker*& pass)
/*--------------------------------------------------------------------------------------------*/
/* The build() function builds the list of available parts that the user can select from to   */
/* design/build/simualte a speaker design with. The user is prompted to enter various part    */
/* values at the CLI prompts. The information is stored in an FIFO linked list.               */
/* Input: Struct Speaker - passed by reference                                                */
/*                         Adds multiple links if needed by user.                             */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *temp;

    temp=(struct Speaker *)malloc(sizeof(struct Speaker));

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "| Enter the speaker values as instructed below:             |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "    Part Number                      : ";
    cin >> temp->Part_num;
    cout << "    Type (Woof/Tweet/Midr/Pass)      : ";
    cin >> temp->Type;
    cout << "    Build (cone/ribbon/electrostatic): ";
    cin >> temp->Build;
    cout << "    Vas (dm^3) (aka liters)          : ";
    cin >> temp->Vas;
    cout << "    Compliance                       : ";
    cin >> temp->Cms;
    cout << "    Driver Mass                      : ";
    cin >> temp->Mms;
    cout << "    BL (Force Factor)                : ";
    cin >> temp->Bl;
    cout << "    Qts (Total Q factor)             : ";
    cin >> temp->Qts;
    cout << "    Qes (Electric Q factor)          : ";
    cin >> temp->Qes;
    cout << "    Qms (Mech Q factor)              : ";
    cin >> temp->Qms;
    cout << "    Sd (Effective piston area cm^2)  : ";
    cin >> temp->Sd;
    cout << "    Fs                               : ";
    cin >> temp->Fs;
    cout << "    Re (ohms)                        : ";
    cin >> temp->Re;
    cout << "    RMS (kg*s)                       : ";
    cin >> temp->Rms;
    cout << "    Z_nom (Nom Impedance)            : ";
    cin >> temp->Z_nom;
    cout << "    Le (mH)                          : ";
    cin >> temp->Le;
    cout << "    Xmax (m)                         : ";
    cin >> temp->Xmax;
    cout << "    Diam (m)                         : ";
    cin >> temp->Diam;
    cout << "    Nom_Pwr (W)                      : ";
    cin >> temp->Nom_Pwr;
    cout << "    Max_Pwr (W)                      : ";
    cin >> temp->Max_Pwr;
    cout << "    Freq_Low (Hz)                    : ";
    cin >> temp->Freq_Low;
    cout << "    Freq_Hi (Hz)                     : ";
    cin >> temp->Freq_Hi;
    cout << "    Sensitivity (db 1w/1m)           : ";
    cin >> temp->Sensitivity;
    cout << "    Box volume - sealed (liters)     : ";
    cin >> temp->Vbs;
    cout << "    Box volume - vented (liters)     : ";
    cin >> temp->Vbv;
    cout << "    f3_seal (3db rolloff)            : ";
    cin >> temp->f3_seal;
    cout << "    f3_vent (3db rolloff)            : ";
    cin >> temp->f3_vent;
    cout << "    v_diam (vent diameter)           : ";
    cin >> temp->v_diam;
    cout << "    p_length (vent length)           : ";
    cin >> temp->p_length;
    cout << "    b_diam (speaker diameter)        : ";
    cin >> temp->b_diam;
    cout << "    b_height (speaker height)        : ";
    cin >> temp->b_height;
    cout << "    depth (speaker depth)            : ";
    cin >> temp->depth;
    temp->next = NULL;

    sleep(10);

    drvr = temp;

    if (strcmp(temp->Type, "Woof") == 0) {
        sleep(1);
        drvr = temp;
        sleep(1);
    }

    if (strcmp(temp->Type, "Midr") == 0) {
        sleep(1);
        mid = temp;
        sleep(1);
    }

    if (strcmp(temp->Type, "Tweet") == 0) {
        sleep(1);
        tweet = temp;
        sleep(1);
    }

    if (strcmp(temp->Type, "Pass") == 0) {
        sleep(1);
        pass = temp;
        sleep(1);
    }

}
/*--------------------------------------------------------------------------------------------*/
void mem_copy(Speaker*& drvr, Speaker*& clone)
/*--------------------------------------------------------------------------------------------*/
/* mem_copy() will copy data upon read in and normaliaze the measurements to meters.          */
/*--------------------------------------------------------------------------------------------*/
{
	clone=(struct Speaker *)malloc(sizeof(struct Speaker));

	cout << "Cloning the data for normalization" << endl;

	if (drvr == NULL) {
        sleep(1);
		return;
    } else {
	    strcpy(clone->Part_num, drvr->Part_num);
	    strcpy(clone->Type, drvr->Type);
	    strcpy(clone->Build, drvr->Build);
		clone->Vas = drvr->Vas/1000.00;
		clone->Cms = drvr->Cms;
		clone->Mms = drvr->Mms/1000.00;
		clone->Bl = drvr->Bl;
		clone->Qts = drvr->Qts;
		clone->Qes = drvr->Qes;
		clone->Qms = drvr->Qms;
		clone->Sd = drvr->Sd/10000.00;
		clone->Fs = drvr->Fs;
		clone->Re = drvr->Re;
		clone->Rms = drvr->Rms;
		clone->Z_nom = drvr->Z_nom;
		clone->Le = drvr->Le;
		clone->Xmax = drvr->Xmax/1000.00;
		clone->Diam = drvr->Diam/1000.00;
		clone->Nom_Pwr = drvr->Nom_Pwr;
		clone->Max_Pwr = drvr->Max_Pwr;
		clone->Freq_Low = drvr->Freq_Low;
		clone->Freq_Hi = drvr->Freq_Hi;
		clone->Sensitivity = drvr->Sensitivity;
		clone->Vbs = drvr->Vbs/1000.0;
		clone->Vbv = drvr->Vbv/1000.0;
		clone->f3_seal = drvr->f3_seal;
		clone->f3_vent = drvr->f3_vent;
		clone->v_diam = drvr->v_diam/1000.00;
		clone->p_length = drvr->p_length/1000.00;
		clone->b_diam = drvr->b_diam/1000.00;
		clone->b_height = drvr->b_height/1000.00;
		clone->depth = drvr->depth/1000.00;
		clone->next = NULL;
	}
}
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass)
/*--------------------------------------------------------------------------------------------*/
/* The parts_list function simply traverse the current list in a one-way direction. The user  */
/* has the option of saving changes to the list or closing out the application with no changes*/
/* made to the parts list. The user can chose the speaker from the available parts listing and*/
/* perform a simulation given the parameters of the selected speaker.                         */
/* Input: Struct Speaker - passed by value                                                    */
/*                         Prints the complete list of driver elements.                       */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;

    int i;

    cout << "Display current speakers..." << endl;
    cout << "+-----------------------------" << endl;

    sleep(5);

    for (i = 0; i< 4; i++) {
        if (i == 0 ) {
            ptr = drvr;  

            if (ptr == nullptr) {
                sleep(1);
				continue;
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    
    
        if (i == 1) { 
            ptr = mid; 
    
            if (ptr == nullptr) {
                sleep(1);
				continue;
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    

        if (i == 2) { 
            ptr = tweet;
    
            if (ptr == nullptr) {
                sleep(1);
				continue;
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    

        if (i == 3) { 
            ptr = pass;
    
            if (ptr == nullptr) {
                sleep(1);
				continue;
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    
    }
}
/*--------------------------------------------------------------------------------------------*/
void print_part(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
/* print_part() will display basic characteristics to the user. All values will be shown.     */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;

    if (drvr == NULL) {
        sleep(1);
        return;
    } else {
        cout << "       Avalable Speaker Parts:...     " << endl;
		cout << " (Measurements normalized to meters)  " << endl;
        ptr = drvr;  //Set the temporary pointer to the head of the list

        while (ptr != NULL) {
            cout << "Part Number            : " << ptr->Part_num << endl;
            cout << "Type                   : " << ptr->Type << endl;
            cout << "Build                  : " << ptr->Build << endl;
            cout << "Vas (L || dm^3)        : " << ptr->Vas << endl;
            cout << "Cms                    : " << ptr->Cms << endl;
            cout << "Mms                    : " << ptr->Mms << endl;
            cout << "Bl                     : " << ptr->Bl  << endl;
            cout << "Qts                    : " << ptr->Qts << endl;
            cout << "Qes                    : " << ptr->Qes << endl;
            cout << "Qms                    : " << ptr->Qms << endl;
            cout << "Sd                     : " << ptr->Sd << endl;
            cout << "Fs (Hz)                : " << ptr->Fs << endl;
            cout << "Re (Ohms)              : " << ptr->Re << endl;
            cout << "Rms                    : " << ptr->Rms << endl;
            cout << "Z_nom (Ohms)           : " << ptr->Z_nom << endl;
            cout << "Le (mH)                : " << ptr->Le << endl;
            cout << "Xmax (m)               : " << ptr->Xmax << endl;
            cout << "Diam (m)               : " << ptr->Diam << endl;
            cout << "Nom_Pwr (W)            : " << ptr->Nom_Pwr << endl;
            cout << "Max_Pwr (W)            : " << ptr->Max_Pwr << endl;
            cout << "Freq_Low (Hz)          : " << ptr->Freq_Low << endl;
            cout << "Freq_Hi (Hz)           : " << ptr->Freq_Hi << endl;
            cout << "Sensitivity            : " << ptr->Sensitivity << endl;
            cout << "- - - - Default Data Sheet Values - - - -" << endl;
            cout << "Vol Sealed (L || dm^3) : " << ptr->Vbs << endl;
            cout << "Vol Vented (L || dm^3) : " << ptr->Vbv << endl;
            cout << "f3_seal (Hz)           : " << ptr->f3_seal << endl;
            cout << "f3_vent (Hz)           : " << ptr->f3_vent << endl;
            cout << "vent diam  (m)         : " << ptr->v_diam << endl;
            cout << "vent length (m)        : " << ptr->p_length << endl;
            cout << "speaker diam (m)       : " << ptr->b_diam << endl;
            cout << "speaker ht/length (m)  : " << ptr->b_height << endl;
            cout << "speaker depth (m)      : " << ptr->depth << endl;
            ptr = ptr->next;
            cout << "+-----------------------------" << endl;
            
            sleep(5);
        }
    }
}
/*--------------------------------------------------------------------------------------------*/
void print_speaker(Field_Pad* speaker, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* print_speaker() will display basic Thile/Small characterstics used to design the cabinet.  */
/*--------------------------------------------------------------------------------------------*/
{

    if (speaker == NULL) {
        sleep(1);
        return;
    } else {
	    while (speaker != NULL) {
            outfile << "+--------+-----------------------+" << endl;
            outfile << "| Attrs  | " << speaker->Part_num << "|" << endl;
            outfile << "+--------+-----------------------+" << endl;
            outfile << "| Type   | " << speaker->Type << "|" << endl;
            outfile << "| Build  | " << speaker->Build << "|" << endl;
            outfile << "| Fs     | " << speaker->Fs << "|" << endl;
            outfile << "| Qts    | " << speaker->Qts << "|" << endl;
            outfile << "| Qes    | " << speaker->Qes << "|" << endl;
            outfile << "| Qms    | " << speaker->Qms << "|" << endl;
            outfile << "| Vas    | " << speaker->Vas << "|" << endl;
            outfile << "| SPL    | " << speaker->Sensitivity << "|" << endl;
            outfile << "| Diam   | " << speaker->Diam << "|" << endl;
            outfile << "| Xmax   | " << speaker->Xmax << "|" << endl;
            outfile << "| Re     | " << speaker->Re << "|" << endl;
            outfile << "| Cms    | " << speaker->Cms << "|" << endl;
            outfile << "| Mms    | " << speaker->Mms << "|" << endl;
            outfile << "| Bl     | " << speaker->Bl << "|" << endl;
            outfile << "+--------+-----------------------+" << endl;
			outfile << endl;

			return;
        }
	}
}
/*--------------------------------------------------------------------------------------------*/
void print_cabinet(Cabinet* cptr, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* print_speaker() will display basic characteristics to the user. All values will be shown.  */
/*--------------------------------------------------------------------------------------------*/
{

    if (cptr == NULL) {
        sleep(1);
        return;
    } else {
	    while (cptr != NULL) {
            outfile << "+------------+-----------------------+" << endl;
            outfile << "| Attrs      | " << cptr->Part_num << endl;
            outfile << "+------------+-----------------------+" << endl;
            outfile << "| Build      | " << cptr->Build << " |" << endl;
            outfile << "| Enclosure  | " << cptr->Enclosure << " |" << endl;
			if (strcmp(cptr->Enclosure, "Vented") == 0) {
			    outfile << "| Vent Diam | " << cptr->port_diam << " |" << endl;
			    outfile << "| Vent Lgth | " << cptr->port_length << " |" << endl;
			}
            outfile << "| Diam       | " << cptr->diam << " |" << endl;
            outfile << "| Depth      | " << cptr->depth << " |" << endl;
            outfile << "| Height     | " << cptr->height << " |" << endl;
            outfile << "| Volume     | " << cptr->cab_volume << " |" << endl;
            outfile << "| Low Freq   | " << cptr->freq_lo << " |" << endl;
            outfile << "| High Freq  | " << cptr->freq_hi << " |" << endl;
            outfile << "| Impedance  | " << cptr->imp_Nom << " |" << endl;
            outfile << "| Res Freq   | " << cptr->res_freq << "|" << endl;
            outfile << "| DC Resist  | " << cptr->DC_resist << "|" << endl;
            outfile << "| 3db rollof | " << cptr->rolloff << " |" << endl;
            outfile << "| Xover Low  | " << cptr->crossover_lo << " |" << endl;
            outfile << "| Xover High | " << cptr->crossover_hi << " |" << endl;
            outfile << "| PAR        | " << cptr->PAR << " |" << endl;
            outfile << "| PER        | " << cptr->PER << " |" << endl;
            outfile << "| Ripple     | " << cptr->Rh <<  "|" << endl;
            outfile << "| Cab Width  | " << cptr->Width << " |" << endl;
            outfile << "| Cab Height | " << cptr->Height << " |" << endl;
            outfile << "| Cab Depth  | " << cptr->Depth << " |" << endl;
            outfile << "+------------+ -----------------------+" << endl;
			outfile << endl;

			return;
        }
	}
}
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet*& cptr)
/*--------------------------------------------------------------------------------------------*/
/* closed_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     power_dynamics()                                                                       */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    struct Cabinet *temp;

    temp=(struct Cabinet *)malloc(sizeof(struct Cabinet));

	char fill[4];
	char l_cmd[8];
	
	double A1;
	double gamma;                   // constants for a closed-box design. Qa = 10/5 - lambda = 1/1.2
	double peak;

	//double Qa;                    // See note on acoustic modeling below
	double Qt;                      // Computed Q-factor
	double Qtc;                     // Value of system Q-factor

    /* temporary variables used to ease computations */
	double v1, v2, v3, v4;

	int bdesign;                    // Switch input value
	int flag;                       // toggle switch

	std::string plot_name;          // Name of the file passed to print the freq response
    std::string cab_type;           // Type of cabinet being built - vented or sealed.
	                                // Passive radiator defaults to sealed.

    system("clear");

	sleep(2);

	cout << " Design a Bass cabinet.. " << endl;
	flag = 0;
	sleep(1);

	// Determine speaker displacement
    drvr->Vd = (M_PI * pow((drvr->Diam/2), 2) * drvr->Xmax);

	// determine system Qt
	Qt = compute_qt(ptr->Qes, ptr->Qms);

    while (!flag) {
        cout << "Use acoustic filling - Y/N? :";
        cin >> fill;

		/* This is used as a method to mark/denote acoustic damping. The code serves */
		/* no set purpose other than to set the damping factor value. There is no    */
		/* modeling/computation to takes place at this time, but the prompt will     */
		/* remain intact for now, pending future work on this feature.               */

        if ((strcmp(fill, "Y") == 0) || (strcmp(fill, "y") == 0)) {
            gamma = 1.0;
            //Qa = 10.0;
        } else {
            gamma = 1.2;
            //Qa = 5.0;
        }

        // used to set the plot name based on driver part number
        std::string str(drvr->Part_num);

        closed_design_menu();

        cin >> bdesign;
        switch (bdesign) {
            case 1:

				if (A1 >= 0) {
                    peak = 0;
                } else {
                    peak = 10 * log(4/(4 - pow(A1, 2)));
                }

				Qtc = drvr->Qts * sqrt((drvr->Vas/drvr->Vbs) + 1.0);

				v1 = pow(Qtc, 2);
				v2 = pow(v1, 2);
				v3 = 1 - 2 * v1 + sqrt(1 + 4 * v2);
				drvr->f3_seal = drvr->Fs * sqrt(v1/v3);

				drvr->Vab = drvr->Vbs * gamma;

				drvr->Fc = ptr->Fs * sqrt(1 + drvr->Vas/drvr->Vbs);

				drvr->f3_seal = drvr->Fc * sqrt((1/pow(Qtc, 2)) - 1);

				drvr->Vol_gross = drvr->Vbs + drvr->Vd;

                cout << "Design based on default values : " << endl;
				cout << "+---------------------------------------" << endl;
				cout << "| Total Q-factor           - " << drvr->Qts << endl;
				cout << "| System Qtc               - " << Qtc << endl;
				cout << "| Total system Qt          - " << Qt << endl;
				cout << "| Driver displacemnt Vd    - " << drvr->Vd << " m^3 " << endl;
				cout << "| Default cabinet value    - " << drvr->Vbs << " m^3 " << endl;
				cout << "| Gross cabinet value      - " << drvr->Vol_gross << " m^3 " << endl;
				cout << "| Default compliance value - " << drvr->Vab << " m^3 " << endl;
				cout << "| Default resonance freq   - " << drvr->Fc << " Hz" << endl;
				cout << "| -3db freq rolloff        - " << drvr->f3_seal << " Hz" << endl;
				cout << "| Peak db value            - " << peak << endl;
				cout << "+---------------------------------------" << endl;

				plot_name = str + "Default_design.plt";

                break;
            case 2:
				cout << "Specify cabinet volume. Default is " << drvr->Vbs*1000.00 << " Liters. " << endl;
				cin >> drvr->Vbs;
				drvr->Vbs = drvr->Vbs/1000.00;

				Qtc = drvr->Qts * sqrt((drvr->Vas/drvr->Vbs) + 1.0);

				A1 = (1/pow(Qtc, 2)) - 2;

				if (A1 >= 0) {
                    peak = 0;
                } else {
                    peak = 10 * log(4/(4 - pow(A1, 2)));
                }

				v1 = pow(Qtc, 2);
				v2 = pow(v1, 2);
				v3 = 1 - 2 * v1 + sqrt(1 + 4 * v2);
				drvr->f3_seal = drvr->Fs * sqrt(v1/v3);

				drvr->Vab = drvr->Vbs * gamma;

				drvr->Fc = ptr->Fs * sqrt(1 + drvr->Vas/drvr->Vbs);

				drvr->f3_seal = drvr->Fc * sqrt((1/pow(Qtc, 2)) - 1);

				drvr->Vol_gross = drvr->Vbs + drvr->Vd;

				cout << "+----------------------------------------------+" << endl;
                cout << "|         Design based on box volume :         |" << endl;
				cout << "+----------------------------------------------+" << endl;
				cout << "| Total Q-factor           - " << drvr->Qts << endl;
				cout << "| System Qtc               - " << Qtc << endl;
				cout << "| Total system Qt          - " << Qt << endl;
				cout << "| Driver displacemnt Vd    - " << drvr->Vd << " m^3 " << endl;
				cout << "| Cabinet value            - " << drvr->Vbs << " m^3 " << endl;
				cout << "| Revised compliance value - " << drvr->Vab << " m^3 " << endl;
				cout << "| Gross cabinet value      - " << drvr->Vol_gross << " m^3 " << endl;
				cout << "| Revised resonance freq   - " << drvr->Fc << " Hz" << endl;
				cout << "| Revised -3db rolloff     - " << drvr->f3_seal << " Hz" << endl;
				cout << "| Peak db value            - " << peak << endl;
				cout << "+----------------------------------------------+" << endl;

				plot_name = str + "custom_cabinet.plt";

                break;
            default:
				Qtc_design_menu();
				cin >> Qtc;

				A1 = (1/pow(Qtc, 2)) - 2;

				if (A1 >= 0) {
                    peak = 0;
                } else {
                    peak = 10 * log(4/(4 - pow(A1, 2)));
                }

				v4 = Qtc/drvr->Qts;
				drvr->Vbs = drvr->Vas/(pow(v4, 2) - 1.0);

				v1 = pow(Qtc, 2);
				v2 = pow(v1, 2);
				v3 = 1 - 2 * v1 + sqrt(1 + 4 * v2);
				drvr->f3_seal = drvr->Fs * sqrt(v1/v3);

				drvr->Vab = drvr->Vbs * gamma;

				drvr->Fc = ptr->Fs * sqrt(1 + drvr->Vas/drvr->Vbs);

				drvr->f3_seal = drvr->Fc * sqrt((1/pow(Qtc, 2)) - 1);

				drvr->Vol_gross = drvr->Vbs + drvr->Vd;

				cout << "+----------------------------------------------+" << endl;
                cout << "|  Design based on specified value of Q(tc) :  |" << endl;
				cout << "+----------------------------------------------+" << endl;
				cout << "| Total Q-factor           - " << drvr->Qts << endl;
				cout << "| System Qtc               - " << Qtc << endl;
				cout << "| Total system Qt          - " << Qt << endl;
				cout << "| Driver displacemnt Vd    - " << drvr->Vd << " m^3 " << endl;
				cout << "| Cabinet value            - " << drvr->Vbs << " m^3 " << endl;
				cout << "| Gross cabinet value      - " << drvr->Vol_gross << " m^3 " << endl;
				cout << "| Revised compliance value - " << drvr->Vab << " m^3 " << endl;
				cout << "| Revised resonance freq   - " << drvr->Fc << " Hz" << endl;
				cout << "| Revised -3db rolloff     - " << drvr->f3_seal << " Hz" << endl;
				cout << "| Peak db value            - " << peak << endl;
				cout << "+----------------------------------------------+" << endl;

				plot_name = str + "custom_Q-factor.plt";

                break;
		 }

		 cout << "Are the values correct (Y/N)?" << endl;
		 cin >> l_cmd;

		 if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
             cout << "Speaker Design completed..." << endl;
             flag = 1;
         } else {
             cout << "Revise closed box design..." << endl;
		     flag = 0;
         }

    }

	// reuse the flag value and reset to 0
    flag = 0;

	power_dynamics(drvr, 2);

    cout << "+-------------------------------------------+" << endl;
    cout << "| Intermediate values for sealed box design |" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << " Part Number                   : " << drvr->Part_num << endl;
    cout << " Driver compliance (Vas)       : " << drvr->Vas << endl;
    cout << " free-air resonance Fs         : " << drvr->Fs << endl;
    cout << " 3db down response f3 (Hz)     : " << drvr->f3_seal  << endl;
	cout << " Low Freq                      : " << drvr->Freq_Low << endl;
	cout << " High Freq                     : " << drvr->Freq_Hi << endl;
	cout << " Nominal Impedance             : " << drvr->Z_nom << endl;
    cout << " Power Efficiency              : " << drvr->Per << " % " << endl;
    cout << " Electrical Power              : " << drvr->Par << " W " << endl;
	cout << " Speaker Height                : " << drvr->b_height << endl;
	cout << " Speaker Width                 : " << drvr->b_diam << endl;
	cout << " Speaker Depth                 : " << drvr->depth << endl;
    cout << "--------------------------------------------" << endl;

	// Copy over data to cabinet structure
	strcpy(temp->Part_num, ptr->Part_num);
    strcpy(temp->Build, ptr->Build);
    strcpy(temp->Enclosure, "Sealed");
    temp->cab_volume = drvr->Vbs;
	temp->gross_volume = drvr->Vol_gross;
    temp->freq_lo = drvr->Freq_Low;
    temp->freq_hi = drvr->Freq_Hi;
    temp->Sensitivity = drvr->Sensitivity;
    temp->res_freq = drvr->Fc;
    temp->rolloff = drvr->f3_seal;
    temp->imp_Nom = ptr->Z_nom;
    temp->diam = drvr->b_diam;
    temp->height = drvr->b_height;
    temp->depth = drvr->depth;
    temp->port_diam = 0;
    temp->port_length = 0;
    temp->PER = drvr->Per;
    temp->PAR = drvr->Par;
    temp->Rh = drvr->Rh;
    temp->port_area = 0.0;
    temp->port_diam = 0.0;
    temp->port_width = 0.0;
    temp->port_length = 0.0;
    temp->next = NULL;

    cptr = temp;
	
    cab_type = "sealed";

    cabinet_design(drvr, cptr, cab_type);
	
	frequency_response_sealed(drvr, Qtc, plot_name);

}
/*--------------------------------------------------------------------------------------------*/
void closed_midrange_design(Speaker*& drvr, Cabinet*& cptr, double baffle)
/*--------------------------------------------------------------------------------------------*/
/* Procedure used to design/define the midrange and tweeter cabinet space since the designs   */
/* are very similar in approach and philosophy (small cabinets, no standing waves, etc)       */
/*--------------------------------------------------------------------------------------------*/
{
    //struct Speaker *ptr;
    //ptr = drvr;

    //struct Cabinet *midr;
	//midr = cptr;

    struct Cabinet *temp;

    temp = (struct Cabinet *)malloc(sizeof(struct Cabinet));

	//double Depth = 100.0;  // Depth is by default 100 mm.
	double H, W, D;
	double Qtc;            // System Q
	double type;

	int ratio;

	std::string cab_type;
	std::string driver;
	std::string plot_name;

	if (cptr != NULL) {
	    temp = cptr;
	}

    cab_type = "sealed";

	Qtc = 0.707;

    midrange_Qdesign_menu();
	cin >> Qtc;

	if (strcmp(drvr->Type, "Tweet") == 0) {
	    drvr->Vbs = 0.0;
	    drvr->Fc = drvr->Fs;
		driver = "Tweeter";
	} else {
	    type = 1;
	    drvr->Vbs = drvr->Vas/(pow(Qtc/drvr->Qts, 2) - 1);
	    drvr->Fc = drvr->Fs * sqrt((drvr->Vas/drvr->Vbs) + 1);
		driver = "Midrange";
    }

	std::string str(drvr->Part_num);

	if ((strcmp(drvr->Build, "ribbon") == 0) || (strcmp(drvr->Build, "planar") == 0) || (strcmp(drvr->Build, "electrostatic") == 0)) {
		ribbon_design();

		cin >> type;

		cab_type = "ribbon";

		// for ribbon/electrostatic tweeter against the overall baffle size of the cabinet
		drvr->f3_seal = C/(2 * M_PI * baffle);
		//temp->sw_freq = 0;
		
		drvr->Vd = drvr->Sd * drvr->Xmax;

		/* Use pythagorean theorem to solve the lgs of a triangle. The values found below   */
		/* form the 'legs' of a right triangle which will be used to create/form the        */
		/* enclosure for the ribbon/planar midrange/tweeter. The 'cabinet' or housing may   */
		/* require a small 'aperture' at the back of the housing so the design will mimic   */
		/* that of a slotted cabient design.                                                */

		if (drvr->depth >= drvr->b_diam) {
			// If the depth of the speaker is greater/equal the width of
			// the driver, then the enclosure needs to be deeper/wider.
		    W = 3 * drvr->b_diam;
			D = 2 * drvr->depth;
			H = drvr->b_height;

	        temp->Height = H;
	        temp->Width = W;
	        temp->Depth = D;

		    drvr->Vbs = (W * D)/2 * H;
		    drvr->Vol_gross = drvr->Vd + drvr->Vbs;
	        temp->cab_volume = drvr->Vol_gross;

		} else if (drvr->depth <= drvr->b_diam) {
			// If the depth of the speaker is less than the width of
			// the driver, then the enclosure needs to be shallower.
		    W = 2 * drvr->b_diam;
			D = 2 * drvr->depth;
			H = drvr->b_height;

	        temp->Height = H;
	        temp->Width = W;
	        temp->Depth = D;

		    drvr->Vbs = (W * D)/2 * H;
		    drvr->Vol_gross = drvr->Vd + drvr->Vbs;
	        temp->cab_volume = drvr->Vol_gross;
		}

		plot_name = str + "_" + driver + "_" + "ribbon.plt";
	} 

        if (strcmp(drvr->Build, "cone") == 0) {
		cab_type = "sealed";

		temp->sw_freq = C/(2 * temp->Depth);

                //W = temp->b_diam * 0.1587;
                //H = temp->b_height * 0.1597;
                //D = temp->depth * 0.1597

                if (drvr->Vbs <= 0) {
                    drvr->Vbs = SolveVbs(drvr);
                }
		//drvr->Vbs = drvr->Vas * 0.2;

		drvr->Fc = drvr->Fs * (sqrt((drvr->Vas/drvr->Vbs) + 1));

		//freq1 = 115/drvr->b_diam;
		
		drvr->f3_seal = drvr->Fs * sqrt(1 + 2 * pow(Qtc, 2));

		drvr->Vd = M_PI * pow((drvr->b_diam/2), 2) * drvr->Xmax;
	    
		midrange_cabinet_screen();
	    cin >> ratio;

		// Solve the cabinet volume based on the ratio to control standing waves
		switch (ratio) {
	        case 1: 
	            H = pow((drvr->Vbs/2), 0.33);
                W = H * 1.25;
		        D = H * 1.6;
        
	            temp->Height = H;
	            temp->Width = W;
	            temp->Depth = D;
		        drvr->Vbs = W * D * H;
		        drvr->Vol_gross = drvr->Vd + drvr->Vbs;
	            temp->cab_volume = drvr->Vol_gross;

			    break;
	        case 2:
	            H = pow((drvr->Vbs/2.8), 0.33);
                W = H * 1.4;
		        D = H * 2.0;

			    // Allocated memory for the cabinet structure!!!

	            temp->Height = H;
	            temp->Width = W;
	            temp->Depth = D;
		        drvr->Vbs = W * D * H;
		        drvr->Vol_gross = drvr->Vd + drvr->Vbs;
	            temp->cab_volume = drvr->Vol_gross;

			    break;
	        default:
	            H = pow((drvr->Vbs/4.16), 0.33);
                W = H * 1.6;
		        D = H * 2.6;

	            temp->Height = H;
	            temp->Width = W;
	            temp->Depth = D;
		        drvr->Vbs = W * D * H;
		        drvr->Vol_gross = drvr->Vd + drvr->Vbs;
	            temp->cab_volume = drvr->Vol_gross;
    
		        break;
	    }

		plot_name = str + "_" + driver + "_" + "dome.plt";
	}

	// Electrical/Acoustigal measurements
	power_dynamics(drvr, 2);

	// compute Baffle Step Frequency
	temp->bfl_freq = C/(M_PI * baffle);

    cout << "+-------------------------------------------+" << endl;
    cout << "| Intermediate values for sealed box design |" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << " Part Number                   : " << drvr->Part_num << endl;
    cout << " Driver compliance (Vas)       : " << drvr->Vas << endl;
    cout << " free-air resonance Fs         : " << drvr->Fs << endl;
    cout << " 3db down response f3 (Hz)     : " << drvr->f3_seal  << endl;
	cout << " Low Freq                      : " << drvr->Freq_Low << endl;
	cout << " High Freq                     : " << drvr->Freq_Hi << endl;
	cout << " Nominal Impedance             : " << drvr->Z_nom << endl;
    cout << " Power Efficiency              : " << drvr->Per << " % " << endl;
    cout << " Electrical Power              : " << drvr->Par << " W " << endl;
	cout << " Driver Height                 : " << drvr->b_height << endl;
	cout << " Driver Width                  : " << drvr->b_diam << endl;
	cout << " Driver Depth                  : " << drvr->depth << endl;
	cout << " Cabinet volume Vbs            : " << drvr->Vbs << endl;
	cout << " Gross cabinet volume          : " << drvr->Vol_gross << endl;
    cout << "--------------------------------------------" << endl;


	strcpy(temp->Part_num, drvr->Part_num);
	strcpy(temp->Type, drvr->Type);
	strcpy(temp->Build, drvr->Build);
	strcpy(temp->Enclosure, "sealed");
	temp->Sensitivity = drvr->Sensitivity;
	temp->gross_volume = drvr->Vol_gross;
	temp->diam = drvr->v_diam;
	temp->height = drvr->w_height;
	temp->depth = drvr->depth;
	temp->rolloff = drvr->f3_seal;
	temp->freq_lo = drvr->Freq_Low;
	temp->freq_hi = drvr->Freq_Hi;
	temp->Cms = drvr->Cms;
	temp->Mms = drvr->Mms;
	temp->diam = drvr->b_diam;
	temp->imp_Nom = drvr->Z_nom;
	temp->res_freq = drvr->Fs;
	temp->DC_resist = drvr->Re;
	temp->Fc = drvr->Fc;
	temp->Qt = drvr->Qts;
	temp->PER = drvr->Per;
    temp->PAR = drvr->Par;
    temp->Rh = drvr->Rh;

	
	// Set other fields to '0'
	temp->port_area = 0;
	temp->port_diam = 0;
	temp->port_width = 0;
	temp->crossover_lo = 0;
	temp->crossover_hi = 0;
	temp->Ma = 0;

	cptr = temp;

    speaker_to_cabinet(drvr, cptr, 1);

    cabinet_design(drvr, cptr, cab_type);

	// Calculate frequency response
	frequency_response_sealed(drvr, Qtc, plot_name);
	cout << "-------------------------------" << endl;
	//plot_name = "freq_resp_curve2.plt";
	//high_frequency_sealed(drvr, Qtc, plot_name);
}
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Speaker*& pasv, Speaker*& pasv_cpy, Cabinet*& bass, Cabinet*& pass)
/*--------------------------------------------------------------------------------------------*/
/* this procedure will design a vented box system, and refactors code pulled in from the      */
/* closed_box_design() procedure call. This procedure works on the bass and midr speaker      */
/* drivers.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr, *temp;
    //struct Speaker *pptr;
    //struct Speaker *pasv_copy;
	ptr = drvr;
	//pptr = pasv;
	//pasv_copy = pasv_cpy;

	temp = (struct Speaker *)malloc(sizeof(struct Speaker));

	struct Cabinet *tmp1, *tmp2;
	//struct Cabinet *bcab;
	//struct Cabinet *pcab;
	//bcab = bass;
	//pcab = pass;
	
	// Bass cabinet (if needed)
	tmp1=(struct Cabinet *)malloc(sizeof(struct Cabinet));

	// Passive cabinet (if needed)
	tmp2=(struct Cabinet *)malloc(sizeof(struct Cabinet));

    std::string design_file;
	std::string cab_type;
    std::string plot_name;


    char l_cmd[8];

	double Vbv;              // Copy of the base-state of the cabinet default volume

	int bdesign;             // switch-stmt control value

    int flag, pflag;         // exit flags to exit switch and while loops.
                             // '0' state means loop is active in loop scope
    flag = 0;
    pflag = 0;

	Vbv = drvr->Vbv;

	// Need to trick the applicatin for now
	strcpy(tmp1->Part_num, drvr->Part_num);
	bass = tmp1;

    while (!flag) {

        cout << "Choose design based on:" << endl;
        cout << "    1) Standard Bass Reflex - Balanced system response" << endl;
        cout << "    2) Extended Bass Shelf - " << endl;
        cout << "    3) Slotted Port Design " << endl;
        cout << "    4) Passive Radiator Design " << endl;
        cout << "-------------------------------------" << endl;
        cin >> bdesign;

		// used to set the plot name based on driver part number
		std::string str(drvr->Part_num);

        switch(bdesign) {
            case 1:
                cout << "Bass Reflex design..." << endl;

                cab_type = "vented";
                pflag = 0;

                vented_cabinet_initialize(ptr, temp, 3.0, bdesign);

                power_dynamics(drvr, 1);

                plot_name = str + "Bass-Reflex.plt";

                speaker_to_cabinet(drvr, bass, bdesign);

                cabinet_design(drvr, bass, cab_type);

                break;
            case 2:
                cout << "Extended-Bass Shelf design..." << endl;

				// Need to trick the applicatin for now
				//strcpy(tmp1->Part_num, drvr->Part_num);
				//bass = tmp1;

                cab_type = "vented";
                pflag = 0;

                vented_cabinet_initialize(ptr, temp, 3.5, bdesign);

                power_dynamics(drvr, 1);

                plot_name = str + "Extended-Shelf.plt";

                speaker_to_cabinet(drvr, bass, bdesign);

                cabinet_design(drvr, bass, cab_type);

                break;
            case 3:
                cout << "Slotted Port design..." << endl;

				// Need to trick the applicatin for now
				//strcpy(tmp1->Part_num, drvr->Part_num);
				//bass = tmp1;

                cab_type = "slotted";

                pflag = 0;
				vented_cabinet_initialize(drvr, temp, 0, bdesign);

                power_dynamics(drvr, 1);

                plot_name = str + "Slotted-Port.plt";

                speaker_to_cabinet(drvr, bass, bdesign);

                cabinet_design(drvr, bass, cab_type);

                break;
            case 4:
                cout << "Passive Radiator design..." << endl;

				// Need to trick the applicatin for now
				//strcpy(tmp1->Part_num, drvr->Part_num);
				//bass = tmp1;

                // If a passive radiator hasnt been loaded into memeory,
                // prompt the user to select one of the available drivers.
                if (pasv == NULL) {
                    read_driver(pasv, pasv_cpy, "Pass", 0, 0);

                    mem_copy(pasv, pasv_cpy);
					
				    // Need to trick the applicatin for now
				    strcpy(tmp2->Part_num, pasv->Part_num);
				    pass = tmp2;

                }

                pflag = 1;

				//pptr = pasv_cpy;
				vented_cabinet_initialize(drvr, pasv_cpy, 0, bdesign);

				power_dynamics(drvr, 1);

                plot_name = str + "Passive-Radiator.plt";

                speaker_to_cabinet(drvr, bass, bdesign);

                cab_type = "passive";

				strcpy(tmp2->Part_num, drvr->Part_num);
				pass = tmp2;

                speaker_to_cabinet(drvr, pass, bdesign);

                cabinet_design(drvr, pass, cab_type);

                break;
            default :
                cout << "Invalid selection. Please choose from one of the above options." << endl;
                break;
        }
        /*-----------------------------*/
        /* Confirm results are correct */
        /*-----------------------------*/
        if (!pflag) {
            if ((drvr->p_length <= 0.0) || (drvr->p_length >= 0.5)) {
                confirm_screen();

                /* exit the procedure to choose a new driver and    */
                /* discontinue further processing  with this driver */
                return;
            }
        } 

		if (pflag) {
            passive_screen();

            /* exit the procedure to choose a new driver and    */
            /* discontinue further processing  with this driver */
            return;
        }

        cout << "Accept results? (Y/N) " << endl;
        cin >> l_cmd;

        if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
            flag = 1;
        } else {
            // Reset compute values to 0
            flag = 0;
            drvr->Fb = 0;
            drvr->Vbv = Vbv;
            drvr->v_diam = 0;
            drvr->f3_vent = 0;
            drvr->w_height = 0;
            drvr->w_width = 0;
            drvr->p_length = 0;
        }
    }

    // Copy over data to cabinet structure
    //strcpy(tmp1->Part_num, drvr->Part_num);
    strcpy(bass->Build, drvr->Build);
    strcpy(bass->Enclosure, "Sealed");
    bass->cab_volume = drvr->Vbs;
    bass->gross_volume = drvr->Vol_gross;
    bass->freq_lo = drvr->Freq_Low;
    bass->freq_hi = drvr->Freq_Hi;
    bass->Sensitivity = drvr->Sensitivity;
    bass->res_freq = drvr->Fc;
    bass->rolloff = drvr->f3_seal;
    bass->imp_Nom = ptr->Z_nom;
    bass->diam = drvr->b_diam;
    bass->height = drvr->b_height;
    bass->depth = drvr->depth;
    bass->port_diam = 0;
    bass->port_length = 0;
    bass->PER = drvr->Per;
    bass->PAR = drvr->Par;
    bass->Rh = drvr->Rh;

    bass->port_area = 0.0;
    bass->port_diam = 0.0;
    bass->port_width = 0.0;
    bass->port_length = 0.0;
    bass->next = NULL;

    frequency_response_vented(drvr, plot_name);
}
/*--------------------------------------------------------------------------------------------*/
void crossover_design() 
/*--------------------------------------------------------------------------------------------*/
{
    system("clear");
    cout << "Design the crossover..." << endl;
}
/*--------------------------------------------------------------------------------------------*/
void graph_performance() 
/*--------------------------------------------------------------------------------------------*/
{
    system("clear");
    cout << "Display graphical performance..." << endl;
}
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass)
/*--------------------------------------------------------------------------------------------*/
/* save_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by value                                                    */
/*                         Writes the complete list of driver elements.                       */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *low;
    struct Speaker *bpass;
    struct Speaker *high;
    struct Speaker *passive;

    //int i;

    low = drvr;
    bpass = mid;
    high = tweet;
	passive = pass;

    system("clear");

    /*--------------------------------------------------*/
    /* Once code is validated, indent to clean up code block */
    /*--------------------------------------------------*/
    
    if (low == NULL) {
         sleep(2);
    } else {
         save_data_ptr(low);
    }
    
    if (bpass == NULL) {
         sleep(2);
    } else {
         save_data_ptr(bpass);
    }
    
    if (high == NULL) {
         sleep(2);
    } else {
         save_data_ptr(high);
    }
    
    if (passive == NULL) {
         sleep(2);
    } else {
         save_data_ptr(passive);
    }
}
/*--------------------------------------------------------------------------------------------*/
void save_data_ptr(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
/* This function is used to write data to the file system if the pointer in the calling       */
/* contains data.                                                                             */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;

    drvr_dba = drvr->Part_num;

    drvr_dba = drvr_dba + ".sdb";

    ofstream outfile(drvr_dba);

    if (drvr == NULL) {
        return;
    }
    else {
        ptr = drvr;  //Set the temporary pointer to the head of the list

        while (ptr != NULL) {
            outfile << ptr->Part_num << ";";
            outfile << ptr->Type << ";";
            outfile << ptr->Build << ";";
            outfile << ptr->Vas << ";";
            outfile << ptr->Cms << ";";
            outfile << ptr->Mms << ";";
            outfile << ptr->Bl << ";";
            outfile << ptr->Qts << ";";
            outfile << ptr->Qes << ";";
            outfile << ptr->Qms << ";";
            outfile << ptr->Sd << ";";
            outfile << ptr->Fs << ";";
            outfile << ptr->Re << ";";
            outfile << ptr->Rms << ";";
            outfile << ptr->Z_nom << ";"; 
            outfile << ptr->Le << ";"; 
            outfile << ptr->Xmax << ";";
            outfile << ptr->Diam << ";";
            outfile << ptr->Nom_Pwr << ";";
            outfile << ptr->Max_Pwr << ";";
            outfile << ptr->Freq_Low << ";";
            outfile << ptr->Freq_Hi << ";";
            outfile << ptr->Sensitivity << ";";
            outfile << ptr->Vbs << ";";
            outfile << ptr->Vbv << ";";
            outfile << ptr->f3_seal << ";";
            outfile << ptr->f3_vent << ";";
            outfile << ptr->v_diam << ";";
            outfile << ptr->p_length << ";";
            outfile << ptr->b_diam << ";";
            outfile << ptr->b_height << ";";
            outfile << ptr->depth << ";";
            ptr = ptr->next;
            
            sleep(3);
        }
    }
}
/*--------------------------------------------------------------------------------------------*/
void read_bass_driver(Speaker*& drvr)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *temp;
    //struct Speaker *ptr;

    char line[256];
    char *token;
    
    string cmd_str;
    string filesdb = "";

    ifstream infile;
    ifstream input;

    drvr = NULL;
    drvr_dba = "";

    system("clear");

    cout << "-------------------------------" << endl;
    sleep(3);
    cmd_str = "./driver.csh Woof";

    cout << "Select a speaker from the list below..." << endl;
    cout << "+-----------------------------" << endl;

    system(cmd_str.c_str());

    sleep(2);

    cout << endl;
    cout << "Bass Speaker... : ";
    cin >> drvr_dba;

    drvr_dba = drvr_dba + ".sdb";
    
    sleep(2);
    
    input.open(drvr_dba, ios::in);

    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
	    sleep(2);
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
        token = strtok(NULL, ";");
        strcpy(temp->Build, token);
        token = strtok(NULL, ";");
        temp->Vas = atof(token);
        token = strtok(NULL, ";");
        temp->Cms = atof(token);
        token = strtok(NULL, ";");
        temp->Mms = atof(token);
        token = strtok(NULL, ";");
        temp->Bl = atof(token);
        token = strtok(NULL, ";");
        temp->Qts = atof(token);
        token = strtok(NULL, ";");
        temp->Qes = atof(token);
        token = strtok(NULL, ";");
        temp->Qms = atof(token);
        token = strtok(NULL, ";");
        temp->Sd = atof(token);
        token = strtok(NULL, ";");
        temp->Fs = atof(token);
        token = strtok(NULL, ";");
        temp->Re = atof(token);
        token = strtok(NULL, ";");
        temp->Rms = atof(token);
        token = strtok(NULL, ";");
        temp->Z_nom = atof(token);
        token = strtok(NULL, ";");
        temp->Le = atof(token);
        token = strtok(NULL, ";");
        temp->Xmax = atof(token);
        token = strtok(NULL, ";");
        temp->Diam = atof(token);
        token = strtok(NULL, ";");
        temp->Nom_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Max_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Low = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Hi = atof(token);
        token = strtok(NULL, ";");
        temp->Sensitivity = atof(token);
        token = strtok(NULL, ";");
        temp->Vbs = atof(token);
        token = strtok(NULL, ";");
        temp->Vbv = atof(token);
        token = strtok(NULL, ";");
        temp->f3_seal = atof(token);
        token = strtok(NULL, ";");
        temp->f3_vent = atof(token);
        token = strtok(NULL, ";");
        temp->v_diam = atof(token);
        token = strtok(NULL, ";");
        temp->p_length = atof(token);
        token = strtok(NULL, ";");
        temp->b_diam = atof(token);
        token = strtok(NULL, ";");
        temp->b_height = atof(token);
        token = strtok(NULL, ";");
        temp->depth = atof(token);
        token = strtok(NULL, ";");
        temp->next = NULL;
    
        sleep(2);
        drvr = temp;
        //ptr = drvr;
    }

    //sleep(3);
}
/*--------------------------------------------------------------------------------------------*/
void read_midrange_driver(Speaker*& midr)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    //struct Speaker *ptr;
    struct Speaker *temp;

    char line[256];
    char *token;
    
    string cmd_str;
    string filesdb = "";

    ifstream infile;
    ifstream input;

    midr = NULL;
    system("clear");
    drvr_dba = "";

    cout << "-------------------------------" << endl;
    sleep(3);
    cmd_str = "./driver.csh Midr";

    cout << "Select a speaker from the list below..." << endl;
    cout << "+-----------------------------" << endl;

    system(cmd_str.c_str());

    sleep(2);

    cout << endl;
    cout << "Mid-range Speaker... : ";
    cin >> drvr_dba;

    drvr_dba = drvr_dba + ".sdb";
    
    sleep(2);
    
    input.open(drvr_dba, ios::in);

    //system("cat drvr_dba");
    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
        token = strtok(NULL, ";");
        strcpy(temp->Build, token);
        token = strtok(NULL, ";");
        temp->Vas = atof(token);
        token = strtok(NULL, ";");
        temp->Cms = atof(token);
        token = strtok(NULL, ";");
        temp->Bl = atof(token);
        token = strtok(NULL, ";");
        temp->Qts = atof(token);
        token = strtok(NULL, ";");
        temp->Qes = atof(token);
        token = strtok(NULL, ";");
        temp->Qms = atof(token);
        token = strtok(NULL, ";");
        temp->Sd = atof(token);
        token = strtok(NULL, ";");
        temp->Fs = atof(token);
        token = strtok(NULL, ";");
        temp->Re = atof(token);
        token = strtok(NULL, ";");
        temp->Rms = atof(token);
        token = strtok(NULL, ";");
        temp->Z_nom = atof(token);
        token = strtok(NULL, ";");
        temp->Le = atof(token);
        token = strtok(NULL, ";");
        temp->Xmax = atof(token);
        token = strtok(NULL, ";");
        temp->Diam = atof(token);
        token = strtok(NULL, ";");
        temp->Nom_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Max_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Low = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Hi = atof(token);
        token = strtok(NULL, ";");
        temp->Sensitivity = atof(token);
        token = strtok(NULL, ";");
        temp->Vbs = atof(token);
        token = strtok(NULL, ";");
        temp->Vbv = atof(token);
        token = strtok(NULL, ";");
        temp->f3_seal = atof(token);
        token = strtok(NULL, ";");
        temp->f3_vent = atof(token);
        token = strtok(NULL, ";");
        temp->v_diam = atof(token);
        token = strtok(NULL, ";");
        temp->p_length = atof(token);
        token = strtok(NULL, ";");
        temp->b_diam = atof(token);
        token = strtok(NULL, ";");
        temp->b_height = atof(token);
        token = strtok(NULL, ";");
        temp->depth = atof(token);
        token = strtok(NULL, ";");
        temp->next = NULL;
    
        sleep(2);
        midr = temp;
        //ptr = midr;
    }

    //sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
void read_tweet_driver(Speaker*& tweet)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    //struct Speaker *ptr;
    struct Speaker *temp;

    char line[256];
    char *token;
    
    //int i, j, k;

    //double num;

    string cmd_str;
    string filesdb = "";

    ifstream infile;
    ifstream input;

    tweet = NULL;
    drvr_dba = "";

    system("clear");

    cout << "-------------------------------" << endl;
    sleep(2);
    cmd_str = "cat *.sdb | grep Tweet";
    cmd_str = "./driver.csh Tweet";

    cout << "Select a speaker from the list below..." << endl;
    cout << "+-----------------------------" << endl;

    system(cmd_str.c_str());

    sleep(2);

    cout << endl;
    cout << "Tweeter Speaker... : ";
    cin >> drvr_dba;

    drvr_dba = drvr_dba + ".sdb";
    
    sleep(2);
    
    input.open(drvr_dba, ios::in);

    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
        token = strtok(NULL, ";");
        strcpy(temp->Build, token);
        token = strtok(NULL, ";");
        temp->Vas = atof(token);
        token = strtok(NULL, ";");
        temp->Cms = atof(token);
        token = strtok(NULL, ";");
        temp->Bl = atof(token);
        token = strtok(NULL, ";");
        temp->Qts = atof(token);
        token = strtok(NULL, ";");
        temp->Qes = atof(token);
        token = strtok(NULL, ";");
        temp->Qms = atof(token);
        token = strtok(NULL, ";");
        temp->Sd = atof(token);
        token = strtok(NULL, ";");
        temp->Fs = atof(token);
        token = strtok(NULL, ";");
        temp->Re = atof(token);
        token = strtok(NULL, ";");
        temp->Rms = atof(token);
        token = strtok(NULL, ";");
        temp->Z_nom = atof(token);
        token = strtok(NULL, ";");
        temp->Le = atof(token);
        token = strtok(NULL, ";");
        temp->Xmax = atof(token);
        token = strtok(NULL, ";");
        temp->Diam = atof(token);
        token = strtok(NULL, ";");
        temp->Nom_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Max_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Low = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Hi = atof(token);
        token = strtok(NULL, ";");
        temp->Sensitivity = atof(token);
        token = strtok(NULL, ";");
        temp->Vbs = atof(token);
        token = strtok(NULL, ";");
        temp->Vbv = atof(token);
        token = strtok(NULL, ";");
        temp->f3_seal = atof(token);
        token = strtok(NULL, ";");
        temp->f3_vent = atof(token);
        token = strtok(NULL, ";");
        temp->v_diam = atof(token);
        token = strtok(NULL, ";");
        temp->p_length = atof(token);
        token = strtok(NULL, ";");
        temp->b_diam = atof(token);
        token = strtok(NULL, ";");
        temp->b_height = atof(token);
        token = strtok(NULL, ";");
        temp->depth = atof(token);
        token = strtok(NULL, ";");
        temp->next = NULL;
    
        sleep(2);
        tweet = temp;
        //ptr = tweet;
    }

    //sleep(3);
}
/*--------------------------------------------------------------------------------------------*/
void read_driver(Speaker*& drvr, Speaker*& drvr_cpy, std::string drv_type, int flag, double Sd)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *temp;
    //struct Speaker *ptr;

    char line[256];
    char *token;
    
	int field_index;                     // pass the field ID into the python script
    string cmd_str;
    string filesdb = "";

	string driver_filter;       // the tyoe of driver to search for

    ifstream infile;
    ifstream input;

    drvr = NULL;

    system("clear");
    drvr_dba = "";

    cout << "-------------------------------" << endl;

    sleep(3);

	// Old system call to be replaced with python support script throughout
	
	if (flag == 1) {
	   cout << "Check for driver area..." << endl;
	   field_index = 10;                // Search for the 10th field - surface area of driver
	   // Look for the passive driver with a specific Sd against the main bass driver

       cmd_str = "/usr/bin/python3 driver_area.py " + drv_type + " " + to_string(field_index);
    } else {
	   field_index = 0;                // Just search for passive radiator files

       cmd_str = "/usr/bin/python3 driver_area.py " + drv_type + " " + to_string(field_index);
    }

    cout << "Select a speaker from the list below..." << endl;
    cout << "+-----------------------------" << endl;

    system(cmd_str.c_str());

    sleep(2);

    cout << endl;
    cout << "Choose Speaker... : ";
    cin >> drvr_dba;

    
    sleep(2);
    
    input.open(drvr_dba, ios::in);

    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
        token = strtok(NULL, ";");
        strcpy(temp->Build, token);
        token = strtok(NULL, ";");
        temp->Vas = atof(token);
        token = strtok(NULL, ";");
        temp->Cms = atof(token);
        token = strtok(NULL, ";");
        temp->Mms = atof(token);
        token = strtok(NULL, ";");
        temp->Bl = atof(token);
        token = strtok(NULL, ";");
        temp->Qts = atof(token);
        token = strtok(NULL, ";");
        temp->Qes = atof(token);
        token = strtok(NULL, ";");
        temp->Qms = atof(token);
        token = strtok(NULL, ";");
        temp->Sd = atof(token);
        token = strtok(NULL, ";");
        temp->Fs = atof(token);
        token = strtok(NULL, ";");
        temp->Re = atof(token);
        token = strtok(NULL, ";");
        temp->Rms = atof(token);
        token = strtok(NULL, ";");
        temp->Z_nom = atof(token);
        token = strtok(NULL, ";");
        temp->Le = atof(token);
        token = strtok(NULL, ";");
        temp->Xmax = atof(token);
        token = strtok(NULL, ";");
        temp->Diam = atof(token);
        token = strtok(NULL, ";");
        temp->Nom_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Max_Pwr = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Low = atof(token);
        token = strtok(NULL, ";");
        temp->Freq_Hi = atof(token);
        token = strtok(NULL, ";");
        temp->Sensitivity = atof(token);
        token = strtok(NULL, ";");
        temp->Vbs = atof(token);
        token = strtok(NULL, ";");
        temp->Vbv = atof(token);
        token = strtok(NULL, ";");
        temp->f3_seal = atof(token);
        token = strtok(NULL, ";");
        temp->f3_vent = atof(token);
        token = strtok(NULL, ";");
        temp->v_diam = atof(token);
        token = strtok(NULL, ";");
        temp->p_length = atof(token);
        token = strtok(NULL, ";");
        temp->b_diam = atof(token);
        token = strtok(NULL, ";");
        temp->b_height = atof(token);
        token = strtok(NULL, ";");
        temp->depth = atof(token);
        token = strtok(NULL, ";");
        temp->next = NULL;
    
        sleep(2);
        //pasv = temp;
        //ptr = pasv;
        drvr = temp;
        //ptr = drvr;
    }
}
/*--------------------------------------------------------------------------------------------*/
void create_data_fields(Speaker* ptr, Field_Pad*& datum, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure exrtacts the data from the Speaker structure and builds the string formated */
/* data with the Field_Pad data structure to be used in the write_design_data() procedure.    */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *temp;
	struct Field_Pad *parse;

	//double tmp_value;

	string tmp_str;

	temp = ptr;

    parse = (struct Field_Pad *)malloc(sizeof(struct Field_Pad));

    if (temp == NULL) {
	    return;
    } else {
	    // Extract data and create field strings

		outfile << "+--------+-----------------------+" << endl;
		strcpy(parse->Part_num, temp->Part_num);
		center_field(parse->Part_num);
		outfile << "| Attrs  | " << parse->Part_num << "|" << endl;
		outfile << "+--------+-----------------------+" << endl;
		strcpy(parse->Type, temp->Type);
		center_field(parse->Type);
		outfile << "| Type   | " << parse->Type << "|" << endl;
		strcpy(parse->Build, temp->Build);
		center_field(parse->Build);
		outfile << "| Build  | " << parse->Build << "|" << endl;
		tmp_str = to_string(temp->Vas);
		strcpy(parse->Vas, tmp_str.c_str());
		center_field(parse->Vas);
		outfile << "| Vas    | " << parse->Vas << "|" << endl;
		tmp_str = to_string(temp->Cms);
		strcpy(parse->Cms, tmp_str.c_str());
		center_field(parse->Cms);
		outfile << "| Cms    | " << parse->Cms << "|" << endl;
		tmp_str = to_string(temp->Bl);
		strcpy(parse->Bl, tmp_str.c_str());
		center_field(parse->Bl);
		outfile << "| Bl     | " << parse->Bl << "|" << endl;
		tmp_str = to_string(temp->Qts);
		strcpy(parse->Qts, tmp_str.c_str());
		center_field(parse->Qts);
		outfile << "| Qts    | " << parse->Qts << "|" << endl;
		tmp_str = to_string(temp->Qes);
		strcpy(parse->Qes, tmp_str.c_str());
		center_field(parse->Qes);
		outfile << "| Qes    | " << parse->Qes << "|" << endl;
		tmp_str = to_string(temp->Qms);
		strcpy(parse->Qms, tmp_str.c_str());
		center_field(parse->Qms);
		outfile << "| Qms    | " << parse->Qms << "|" << endl;
		tmp_str = to_string(temp->Fs);
		strcpy(parse->Fs, tmp_str.c_str());
		center_field(parse->Fs);
		outfile << "| Fs     | " << parse->Fs << "|" << endl;
		tmp_str = to_string(temp->Re);
		strcpy(parse->Re, tmp_str.c_str());
		center_field(parse->Re);
		outfile << "| Re     | " << parse->Re << "|" << endl;
		tmp_str = to_string(temp->Sensitivity);
		strcpy(parse->Sensitivity, tmp_str.c_str());
		center_field(parse->Sensitivity);
		outfile << "| SPL    | " << parse->Sensitivity << "|" << endl;
		tmp_str = to_string(temp->Rms);
		strcpy(parse->Rms, tmp_str.c_str());
		center_field(parse->Rms);
		tmp_str = to_string(temp->Z_nom);
		strcpy(parse->Z_nom, tmp_str.c_str());
		center_field(parse->Z_nom);
		tmp_str = to_string(temp->Le);
		strcpy(parse->Le, tmp_str.c_str());
		center_field(parse->Le);
		tmp_str = to_string(temp->Xmax);
		strcpy(parse->Xmax, tmp_str.c_str());
		center_field(parse->Xmax);
		outfile << "| Xmax   | " << parse->Xmax << "|" << endl;
		tmp_str = to_string(temp->Diam);
		strcpy(parse->Diam, tmp_str.c_str());
		center_field(parse->Diam);
		outfile << "| Diam   | " << parse->Diam << "|" << endl;
		tmp_str = to_string(temp->Nom_Pwr);
		strcpy(parse->Nom_Pwr, tmp_str.c_str());
		center_field(parse->Nom_Pwr);
		tmp_str = to_string(temp->Max_Pwr);
		strcpy(parse->Max_Pwr, tmp_str.c_str());
		center_field(parse->Max_Pwr);
		tmp_str = to_string(temp->Freq_Low);
		strcpy(parse->Freq_Low, tmp_str.c_str());
		center_field(parse->Freq_Low);
		tmp_str = to_string(temp->Freq_Hi);
		strcpy(parse->Freq_Hi, tmp_str.c_str());
		center_field(parse->Freq_Hi);
		tmp_str = to_string(temp->Sensitivity);
		strcpy(parse->Sensitivity, tmp_str.c_str());
		center_field(parse->Sensitivity);
		tmp_str = to_string(temp->Vbs);
		strcpy(parse->Vbs, tmp_str.c_str());
		center_field(parse->Vbs);
		tmp_str = to_string(temp->Vbv);
		strcpy(parse->Vbv, tmp_str.c_str());
		center_field(parse->Vbv);
		tmp_str = to_string(temp->f3_seal);
		strcpy(parse->f3_seal, tmp_str.c_str());
		center_field(parse->f3_seal);
		tmp_str = to_string(temp->f3_vent);
		strcpy(parse->f3_vent, tmp_str.c_str());
		center_field(parse->f3_vent);
		tmp_str = to_string(temp->v_diam);
		strcpy(parse->v_diam, tmp_str.c_str());
		center_field(parse->v_diam);
		tmp_str = to_string(temp->p_length);
		strcpy(parse->p_length, tmp_str.c_str());
		center_field(parse->p_length);
		tmp_str = to_string(temp->b_diam);
		strcpy(parse->b_diam, tmp_str.c_str());
		center_field(parse->b_diam);
		tmp_str = to_string(temp->b_height);
		strcpy(parse->b_height, tmp_str.c_str());
		center_field(parse->b_height);
		tmp_str = to_string(temp->depth);
		strcpy(parse->depth, tmp_str.c_str());
		center_field(parse->depth);
		parse->next = NULL;
		datum = parse;
		outfile << "+--------+-----------------------+" << endl;
		outfile << endl;
	}
}
/*--------------------------------------------------------------------------------------------*/
void create_cab_fields(Cabinet* cptr, Cab_Pad*& cdatum, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure exrtacts the data from the Speaker structure and builds the string formated */
/* data with the Field_Pad data structure to be used in the write_design_data() procedure.    */
/*--------------------------------------------------------------------------------------------*/
{
    struct Cabinet *temp;
	struct Cab_Pad *cparse;

	//double tmp_value;

	string tmp_str;

	temp = cptr;

    cparse = (struct Cab_Pad *)malloc(sizeof(struct Cab_Pad));

    if (temp == NULL) {
	    return;
    } else {
	    // Extract data and create field strings

		outfile << "+------------+-----------------------+" << endl;
		strcpy(cparse->Part_num, temp->Part_num);
		center_field(cparse->Part_num);
		outfile << "| Attrs      | " << cparse->Part_num << "|" <<  endl;
		outfile << "+------------+-----------------------+" << endl;
		strcpy(cparse->Build, temp->Build);
		center_field(cparse->Build);
		outfile << "| Build      | " << cparse->Build << "|" << endl;
		strcpy(cparse->Enclosure, temp->Enclosure);
		center_field(cparse->Enclosure);
		outfile << "| Enclosure  | " << cparse->Enclosure << "|" << endl;
		tmp_str = to_string(temp->port_diam);
		strcpy(cparse->port_diam, tmp_str.c_str());
		center_field(cparse->port_diam);
		tmp_str = to_string(temp->port_length);
		strcpy(cparse->port_length, tmp_str.c_str());
		center_field(cparse->port_length);
		if (strcmp(cparse->Enclosure, "Vented") == 0) {
		    outfile << "| Vent Diam | " << cparse->port_diam << "|" << endl;
            outfile << "| Vent Lgth | " << cparse->port_length << "|" << endl;
		}
		tmp_str = to_string(temp->diam);
		strcpy(cparse->diam, tmp_str.c_str());
		center_field(cparse->diam);
		outfile << "| Diam       | " << cparse->diam << "|" << endl;
		tmp_str = to_string(temp->depth);
		strcpy(cparse->depth, tmp_str.c_str());
		center_field(cparse->depth);
		outfile << "| Depth      | " << cparse->depth << "|" << endl;
		tmp_str = to_string(temp->height);
		strcpy(cparse->height, tmp_str.c_str());
		center_field(cparse->height);
		outfile << "| Height     | " << cparse->height << "|" << endl;
		tmp_str = to_string(temp->cab_volume);
		strcpy(cparse->cab_volume, tmp_str.c_str());
		center_field(cparse->cab_volume);
		outfile << "| Volume     | " << cparse->cab_volume << "|" << endl;
		tmp_str = to_string(temp->freq_lo);
		strcpy(cparse->freq_lo, tmp_str.c_str());
		center_field(cparse->freq_lo);
		outfile << "| Low Freq   | " << cparse->freq_lo << "|" << endl;
		tmp_str = to_string(temp->freq_hi);
		strcpy(cparse->freq_hi, tmp_str.c_str());
		center_field(cparse->freq_hi);
		outfile << "| High Freq  | " << cparse->freq_hi << "|" << endl;
		tmp_str = to_string(temp->imp_Nom);
		strcpy(cparse->imp_Nom, tmp_str.c_str());
		center_field(cparse->imp_Nom);
		outfile << "| Impedance  | " << cparse->imp_Nom << "|" << endl;
		tmp_str = to_string(temp->res_freq);
		strcpy(cparse->res_freq, tmp_str.c_str());
		center_field(cparse->res_freq);
		outfile << "| Res Freq   | " << cparse->res_freq << "|" << endl;
		tmp_str = to_string(temp->DC_resist);
		strcpy(cparse->DC_resist, tmp_str.c_str());
		center_field(cparse->DC_resist);
		outfile << "| DC Resist  | " << cparse->DC_resist << "|" << endl;
		tmp_str = to_string(temp->Sensitivity);
		strcpy(cparse->Sensitivity, tmp_str.c_str());
		center_field(cparse->Sensitivity);
		outfile << "| Sensitivity| " << cparse->Sensitivity << "|" << endl;
		tmp_str = to_string(temp->rolloff);
		strcpy(cparse->rolloff, tmp_str.c_str());
		center_field(cparse->rolloff);
		outfile << "| 3db rollof | " << cparse->rolloff << "|" << endl;
		tmp_str = to_string(temp->crossover_lo);
		strcpy(cparse->crossover_lo, tmp_str.c_str());
		center_field(cparse->crossover_lo);
		outfile << "| Xover Low  | " << cparse->crossover_lo << "|" << endl;
		tmp_str = to_string(temp->crossover_hi);
		strcpy(cparse->crossover_hi, tmp_str.c_str());
		center_field(cparse->crossover_hi);
		outfile << "| Xover High | " << cparse->crossover_hi << "|" << endl;
		tmp_str = to_string(temp->PAR);
		strcpy(cparse->PAR, tmp_str.c_str());
		center_field(cparse->PAR);
		outfile << "| PAR        | " << cparse->PAR << "|" << endl;
		tmp_str = to_string(temp->PER);
		strcpy(cparse->PER, tmp_str.c_str());
		center_field(cparse->PER);
		outfile << "| PER        | " << cparse->PER << "|" << endl;
		tmp_str = to_string(temp->Rh);
		strcpy(cparse->Rh, tmp_str.c_str());
		center_field(cparse->Rh);
		outfile << "| Ripple     | " << cparse->Rh <<  "|" << endl;
		tmp_str = to_string(temp->Height);
		strcpy(cparse->Height, tmp_str.c_str());
		center_field(cparse->Height);
		outfile << "| Cab Height | " << cparse->Height << "|" << endl;
		tmp_str = to_string(temp->Width);
		strcpy(cparse->Width, tmp_str.c_str());
		center_field(cparse->Width);
		outfile << "| Cab Width  | " << cparse->Width << "|" << endl;
		tmp_str = to_string(temp->Depth);
		strcpy(cparse->Depth, tmp_str.c_str());
		center_field(cparse->Depth);
		outfile << "| Cab Depth  | " << cparse->Depth << "|" << endl;
		cparse->next = NULL;
		cdatum = cparse;
		outfile << "+------------+-----------------------+" << endl;

		sleep(2);
	}
}
/*--------------------------------------------------------------------------------------------*/
void passive_two_way(Speaker* drvr, Speaker* tweet, Filter& zobel, Filter& lowpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (capcitance) and the desired crossover    */
/* point for the speaker. The function will then compute the values of a 1st order crossover. */
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/*--------------------------------------------------------------------------------------------*/
{
    char type[12];     /* type of speaker requiring Lpad in the crossover branch */

    string low_parse = "";    /* The following strings are used to store the parsed data from    */
    string high_parse = "";   /* the speaker node passed in to display the part and frequency    */
                              /* band-width.                                                     */
                              
	// Check to insure that speaker drivers are loaded to prevent a seg fault of the applicaiton
	if (drvr == nullptr) {
	    cout << "No bass drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
    }
                              
	if (!tweet) {
	    cout << "No tweeter drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
	}

    cout << "This is a Butterworth passive crossover for 2 driver speaker. " << endl;

    lowpass.xover_type = "Bass";
    highpass.xover_type = "Tweeter";

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */


	// Counter values used to loop through filter vars
	lowpass.i = 1;
	lowpass.j = 1;
	highpass.i = 1;
	highpass.j = 1;

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

	if (drvr->Le <= 1.0 ) {
	    cout << "Loudspeaker inductance is low. A zobel filter ss not needed to smooth any impedance bump..." << endl;
	    zobel.Rz = 0;
		zobel.Cz = 0;
		zobel.Lz = drvr->Le;
		sleep(3);
	} else {
	    zobel.Rz = 1.25 * drvr->Re;    // zobel resistance is the same value as the driver DC Resistance
		zobel.Cz = drvr->Le/(pow(zobel.Rz, 2));
		zobel.Lz = drvr->Le;

	    sleep(3);
	}

	lowpass.order = 2;      // LC cross-over filters are 2-stage by default
	highpass.order = 2;     // LC cross-over filters are 2-stage by default


	freq_crossover_screen();
    lowpass.xover[0] =  tweet->Freq_Low + (drvr->Freq_Hi - tweet->Freq_Low)/2;

    cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Tweet: " << lowpass.xover[0] << endl;
    cout << "+---------------------------+" << endl;

    highpass.xover[0] = lowpass.xover[0];
    cout << "High-pass Crossover frequency: " << highpass.xover[0] << endl;
   
	/*------------------------------------------------*/
	/* Compute/assign inductance/capacitance network  */
	/*------------------------------------------------*/
	lowpass.filt_l[0] = solve_inductance(drvr, lowpass.xover[0]);
	lowpass.filt_c[0] = solve_capacitance(drvr, lowpass.xover[0]);
	highpass.filt_l[0] = lowpass.filt_l[0];
	highpass.filt_c[0] = lowpass.filt_c[0];

    lowpass.gain = (pow(1/(sqrt(2)), lowpass.order));
    highpass.gain = (pow(1/(sqrt(2)), highpass.order));

    lowpass.f3db[0] = lowpass.xover[0] * 0.644; //sqrt( -1 + sqrt(2));
    highpass.f3db[0] = highpass.xover[0] * 1.533; //sqrt( 1 + sqrt(2));

	/*------------------------------------------------*/
	/* compare driver outputs to design L-pad network */
	/*------------------------------------------------*/

	lowpass.Z_nom = drvr->Z_nom;
	highpass.Z_nom = tweet->Z_nom;

	lowpass.Sensitivity = drvr->Sensitivity;
	highpass.Sensitivity = tweet->Sensitivity;

	cout << "+---------------------------------------+" << endl;
	cout << "       Bass/Tweeter measurables          " << endl;
	cout << "+---------------------------------------+" << endl;
	cout << " Woofer            Tweeter               " << endl;
	cout << "+---------------------------------------+" << endl;
	cout << " " << lowpass.Z_nom << " Nom Resistance "  << lowpass.Z_nom << endl;
	cout << " " << lowpass.Sensitivity << "       SPL      "  << lowpass.Sensitivity << endl;
	cout << "+---------------------------------------+" << endl;

	// Set the value of the woofer Lpad to "0" since Lpads are only for high-frequency drivers
	strcpy(lowpass.lpad, "N/A");

	if (drvr->Z_nom <= 4) {
	    strcpy(highpass.lpad, "50");
		strcpy(type, "Tweeter");
	} else if ((drvr->Z_nom > 4) || (drvr->Z_nom <= 6)) {
	    strcpy(highpass.lpad, "75");
		strcpy(type, "Tweeter");
	} else {
	    strcpy(highpass.lpad, "100");
		strcpy(type, "Tweeter");
	}

	lpad_msg(drvr, highpass, type);

    /* Review design values here */

    cout << "-----------------------------------------" << endl;
    cout << " Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Lpad Potentiometer       : " << highpass.lpad << endl;
    cout << " Filter Low Pass Order    : " << lowpass.order << endl;
    cout << " Filter High PassOrder    : " << highpass.order << endl;
    cout << " Low-Pass Frequency (Hz)  : " << lowpass.xover[0] << endl;
    cout << " High-Pass Frequency (Hz) : " << highpass.xover[0] << endl;
    cout << " Low-Pass gain (< 1)      : " << lowpass.gain << endl;
    cout << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    cout << " Low-Pass 3db freq  (Hz)  : " << lowpass.f3db[0]<< endl;
    cout << " High-Pass 3db freq  (Hz) : " << highpass.f3db[0]<< endl;
	cout << " Low-Pass Sensitivity     : " << lowpass.Sensitivity << endl;
	cout << " Low-pass Load            : " << lowpass.Z_nom << endl;
    cout << " Low-Pass Capacitance     : " << lowpass.filt_c[0] << endl;
    cout << " Low-Pass Inductance      : " << lowpass.filt_l[0] << endl;
	cout << " High-pass Load           : " << highpass.Z_nom << endl;
	cout << " High-Pass Sensitivity    : " << lowpass.Sensitivity << endl;
    cout << " High-Pass Capacitance    : " << highpass.filt_c[0] << endl;
    cout << " High-Pass Inductance     : " << highpass.filt_l[0] << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);

	//highpass.enabled = 1;
}
/*--------------------------------------------------------------------------------------------*/
void passive_three_way(Speaker* drvr, Speaker* mid, Speaker* tweet, Filter& zobel, Filter& lowpass, Filter& bandpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (resistance) and the desired crossover    */
/* points for the speaker. The function will then compute the values of a 1st order crossover.*/
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/*--------------------------------------------------------------------------------------------*/
{
    char type[12];     /* type of speaker requiring Lpad in the crossover branch */

	// Check to insure that speaker drivers are loaded to prevent a seg fault of the applicaiton
	if (drvr == nullptr) {
	    cout << "No bass drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
    }
                              
	// Check to insure that speaker drivers are loaded to prevent a seg fault of the applicaiton
	if (mid == nullptr) {
	    cout << "No bass drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
    }
                              
	// Check to insure that speaker drivers are loaded to prevent a seg fault of the applicaiton
	if (tweet == nullptr) {
	    cout << "No bass drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
    }

    lowpass.xover_type = "Bass";
    bandpass.xover_type = "Midrange";
    highpass.xover_type = "Tweeter";

    string low_parse = "";    /* The following strings are used to store the parsed data from */
    string mid_parse = "";    /* the speaker node passed in to display the part and frequency */
    string high_parse = "";   /* band-width.                                                  */
    

	// counter vars used for looping constructs
	lowpass.i = 2;
	lowpass.j = 2;
	bandpass.i = 2;
	bandpass.j = 2;
	highpass.i = 2;
	highpass.j = 2;

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(mid, mid_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

    if (drvr->Le <= 1.0 ) {
        cout << "Loudspeaker inductance is low. A zobel filter ss not needed to smooth any impedance bump..." << endl;
        zobel.Rz = 0;
        zobel.Cz = 0;
		zobel.Lz = drvr->Le;
        sleep(3);
    } else {
        zobel.Rz = 1.25 * drvr->Re;    // zobel resistance is the same value as the driver DC Resistance
        zobel.Cz = drvr->Le/(pow(zobel.Rz, 2));
		zobel.Lz = drvr->Le;

        sleep(3);
    }

    freq_crossover_screen();
    lowpass.xover[0] = drvr->Freq_Low + (mid->Freq_Hi - drvr->Freq_Low)/2;
    bandpass.xover[0] = lowpass.xover[0];
	bandpass.xover[1] = mid->Freq_Low + (mid->Freq_Hi - tweet->Freq_Low)/2;
    highpass.xover[0] = bandpass.xover[1];

	cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Midrange : " << bandpass.xover[0] << endl;
    cout << "  Midrange/Tweet: " << bandpass.xover[1] << endl;
    cout << "+---------------------------+" << endl;

	lowpass.order = 2;      // LC cross-over filters are 2-stage by default
	bandpass.order = 4;     // LC cross-over network for band-pass is a special case
    highpass.order = 2;     // LC cross-over filters are 2-stage by default

	/*------------------------------------------------*/
	/* Compute/assign inductance/capacitance network  */
	/* Solve for the bandpass network LC values[0,1]  */
	/*------------------------------------------------*/

	/* Band Pass network  - 4-stage network */
	bandpass.filt_l[0] = solve_inductance(drvr, bandpass.xover[0]);
	bandpass.filt_c[0] = solve_capacitance(drvr, bandpass.xover[0]);

	bandpass.filt_l[1] = solve_inductance(drvr, bandpass.xover[1]);
	bandpass.filt_c[1] = solve_capacitance(drvr, bandpass.xover[1]);

	/* Populate the remaining LC values for bass/tweeter */
	lowpass.filt_l[0] = bandpass.filt_l[0];
	lowpass.filt_c[0] = bandpass.filt_c[0];

	highpass.filt_l[0] = bandpass.filt_l[1];
	highpass.filt_c[0] = bandpass.filt_c[1];

	/* Determine stage gain values per crossover stage */
    lowpass.gain = (pow(1/(sqrt(2)), lowpass.order));
    bandpass.gain = (pow(1/(sqrt(2)), bandpass.order));
    highpass.gain = (pow(1/(sqrt(2)), highpass.order));

	/* determine bandpass attenuation */
    lowpass.f3db[0] = lowpass.xover[0] * sqrt((pow(2, 1/lowpass.order)) - 1);

    bandpass.f3db[0] = bandpass.xover[0] * sqrt((pow(2, 1/bandpass.order)) - 1);
    bandpass.f3db[1] = bandpass.xover[1] * sqrt((pow(2, 1/bandpass.order)) - 1);

    highpass.f3db[0] = highpass.xover[0] * sqrt((pow(2, 1/highpass.order)) - 1);

	/*------------------------------------------------*/
    /* compare driver outputs to design L-pad network */
    /*------------------------------------------------*/
	lowpass.Z_nom = drvr->Z_nom;
	bandpass.Z_nom = mid->Z_nom;
	highpass.Z_nom = tweet->Z_nom;

	lowpass.Sensitivity = drvr->Sensitivity;
	bandpass.Sensitivity = mid->Sensitivity;
	highpass.Sensitivity = tweet->Sensitivity;

    cout << "+-------------------------------------------------------------+" << endl;
    cout << "             Bass/Midrange/Tweeter measurables                 " << endl;
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "                Woofer       Midrange      Tweeter " << endl;
    cout << "+---------------------------------------+" << endl;
    cout << " Impedance " << lowpass.Z_nom << " " <<  bandpass.Z_nom << " " << highpass.Z_nom << endl;
    cout << " SPL       " << lowpass.Sensitivity << " " << bandpass.Sensitivity << " " << highpass.Sensitivity << endl;
    cout << "+-------------------------------------------------------------+" << endl;

	// Set the value of the woofer Lpad to "0" since Lpads are only for high-frequency drivers
	strcpy(lowpass.lpad, "N/A");

	if (drvr->Z_nom <= 4) {
        strcpy(bandpass.lpad, "50");
        strcpy(type, "Midrange");
    } else if ((drvr->Z_nom > 4) || (drvr->Z_nom <= 6)) {
        strcpy(bandpass.lpad, "75");
        strcpy(type, "Midrange");
    } else {
        strcpy(bandpass.lpad, "100");
        strcpy(type, "Midrange");
    }

	if (mid->Z_nom <= 4) {
        strcpy(highpass.lpad, "50");
        strcpy(type, "Tweeter");
    } else if ((mid->Z_nom > 4) || (mid->Z_nom <= 6)) {
        strcpy(highpass.lpad, "75");
        strcpy(type, "Tweeter");
    } else {
        strcpy(highpass.lpad, "100");
        strcpy(type, "Tweeter");
    }

    cout << " Band-pass Load           : " << bandpass.Z_nom << endl;
    cout << " Band-Pass Capacitance C1 : " << bandpass.filt_c[0] << endl;
    cout << " Band-Pass Inductance  L1 : " << bandpass.filt_l[0] << endl;
    cout << " Band-Pass Capacitance C2 : " << bandpass.filt_c[1] << endl;
    cout << " Band-Pass Inductance  L2 : " << bandpass.filt_l[1] << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Lpad Mid Potentiometer   : " << bandpass.lpad << endl;
    cout << " Lpad Tweet Potentiometer : " << highpass.lpad << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Low Pass Order    : " << lowpass.order << endl;
    cout << " Filter Band Pass Order   : " << bandpass.order << endl;
    cout << " Filter High PassOrder    : " << highpass.order << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Low-Pass Frequency (Hz)  : " << lowpass.xover[0] << endl;
    cout << " Bann-Pass Frequency(1)   : " << highpass.xover[0] << endl;
    cout << " Band-Pass Frequency(2)   : " << highpass.xover[0] << endl;
    cout << " High-Pass Frequency (Hz) : " << highpass.xover[0] << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Low-Pass gain (< 1)      : " << lowpass.gain << endl;
    cout << " Band-Pass gain (< 1)     : " << highpass.gain << endl;
    cout << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Low-Pass 3db freq  (Hz)  : " << lowpass.f3db[0]<< endl;
    cout << " Band-Pass 3db freq  (Hz) : " << lowpass.f3db[0]<< endl;
    cout << " Band-Pass 3db freq  (Hz) : " << lowpass.f3db[0]<< endl;
    cout << " High-Pass 3db freq  (Hz) : " << highpass.f3db[0]<< endl;
    cout << "-----------------------------------------" << endl;
    cout << " Low-Pass Sensitivity     : " << lowpass.Sensitivity << endl;
    cout << " Low-pass Load            : " << lowpass.Z_nom << endl;
    cout << " Low-Pass Capacitance     : " << lowpass.filt_c[0] << endl;
    cout << " Low-Pass Inductance      : " << lowpass.filt_l[0] << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Band-pass Load           : " << bandpass.Z_nom << endl;
    cout << " Band-Pass Sensitivity    : " << bandpass.Sensitivity << endl;
    cout << " Band-Pass Capacitance C1 : " << bandpass.filt_c[0] << endl;
    cout << " Band-Pass Inductance  L1 : " << bandpass.filt_l[0] << endl;
    cout << " Band-Pass Capacitance C2 : " << bandpass.filt_c[1] << endl;
    cout << " Band-Pass Inductance  L2 : " << bandpass.filt_l[1] << endl;
    cout << "-----------------------------------------" << endl;
    cout << " High-pass Load           : " << highpass.Z_nom << endl;
    cout << " High-Pass Sensitivity    : " << lowpass.Sensitivity << endl;
    cout << " High-Pass Capacitance    : " << highpass.filt_c[0] << endl;
    cout << " High-Pass Inductance     : " << highpass.filt_l[0] << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);

	//zobel.enabled = 0;
	//lowpass.enabled = 0;
	//highpass.enabled = 0;
	//bandpass.enabled = 1;

}
/*--------------------------------------------------------------------------------------------*/
void subwoofer_passive(Speaker* drvr, Filter& lowpass, Filter& zobel)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will create a low-pass filter and zobel shunt for a subwoofer depending on  */
/* the inductance value of the woofer. There should be a way to optimize code so that the     */
/* zobel filter is called without creating or repeating code for each element of the          */
/* network(s).                                                                                */
/*--------------------------------------------------------------------------------------------*/
{
	int i;
	int input;                  // Selection answer for frequency cut-off

	int f_delta;

	int f_lo, f_hi;             // Frequency bandwidth for filter adjustment

	// Check to insure that speaker drivers are loaded to prevent a seg fault of the applicaiton
	if (drvr == nullptr) {
	    cout << "No bass drivers have been loaded into the application." << endl;
		cout << "A valid bass driver must be loaded into the application " << endl;
		cout << "before a crossover network can be designed.             " << endl;

		return;
    }
                              
	zobel.order = 2;
	zobel.xover_type = "Subwoofer";

	if (drvr->Le <= 1.0 ) {
	    cout << "Loudspeaker inductance is low. A zobel filter is not needed to smooth any impedance bump..." << endl;
	    zobel.Rz = 0;
		zobel.Lz = drvr->Le;
	    zobel.Cz = 0;
		sleep(3);
	} else {
	    zobel.Rz = drvr->Re;    // zobel resistance is the same value as the driver DC Resistance
		zobel.Cz = drvr->Le/(pow(zobel.Rz, 2));
		zobel.Lz = drvr->Le;

	    sleep(3);
	}
	
	frequency_limit_screen();
	cin >> input;

	switch (input) {
	    case 1:
			zobel.enabled = 1;

			i = 0;
	        zobel.i = 1;
	        zobel.j = 1;

			cout << "Specify the cut-off frequency F: ";
			cin >> zobel.xover[i];

			zobel.filt_l[i] = solve_inductance(drvr, zobel.xover[i]);
			zobel.filt_c[i] = solve_capacitance(drvr, zobel.xover[i]);

			cout << "+-----------------------------------------------" << endl;
			cout << "|   Freq       Capacitance      Inductance " << endl;
			cout << "+-----------------------------------------------" << endl;
			cout << "| " << zobel.xover[i] << " | " << zobel.filt_c[i] << " | " << zobel.filt_l[i] << endl;
			cout << "+-----------------------------------------------" << endl;
			
			sleep(5);
	        break;

        case 2:
			zobel.enabled = 2;

	        zobel.i = 1;

			while (true) {
			    cout << "Specify the number of freq breaks (2 - 4): ";
			    cin >> zobel.j;
			    
				if (cin.fail()){
				    cin.clear();      // Clear the error flag
					cin.ignore(1000, '\n'); // Discard invalid input

                    cout << "Invalid input. Please enter a number between 2 and 4.\n";
                    continue;
				}

				// Check if input is within range
                if (input >= 2 && input <= 4) {
                    break; // Valid input, exit loop
                }

				std::cout << "Out of range. Try again.\n";
            }

			/*------------------------------------------------------------------*/
			cout << "Specify frequency range: " << endl;
	        while (true) { // Loop until the correct values are entered

	            cout << "Enter the bandwidth for the effective filter width (freq_lo/freq_hi): ";
	   
	            if (cin >> f_lo >> f_hi)  {
	                break;
	            }

	            cerr << "Invalid values submitted, please enter the min/max freq range." << endl;

	            cin.clear();
	            cin.ignore(10000, '\n');
	        }

			f_delta = (f_hi - f_lo)/input;

			// Setup freq limit to start computation loop
			zobel.freq[0] = f_lo;

			cout << "+-----------------------------------------------" << endl;
			cout << "|   Freq       Capacitance      Inductance       Freq " << endl;
			cout << "+-----------------------------------------------" << endl;
			
			for (i = 0; i < zobel.j; i++ ) {
				zobel.freq[i] = f_lo + (i * f_delta);
				
				zobel.filt_c[i] = solve_capacitance(drvr, zobel.freq[i]);

			    zobel.filt_l[i] = solve_inductance(drvr, zobel.freq[i]);

		    }

			cout << "+-----------------------------------------------" << endl;

			sleep(5);
	        break;

        default:
			zobel.enabled = 3;

	        zobel.i = 1;
	        zobel.j = 2;

			cout << "Specify frequency range: " << endl;
	        while (true) { // Loop until the correct values are entered

	            cout << "Enter the bandwidth for the effective filter width (freq_lo/freq_hi): ";
	   
	            if (cin >> f_lo >> f_hi)  {
	                break;
	            }

	            cerr << "Invalid values submitted, please enter the min/max freq range." << endl;

	            cin.clear();
	            cin.ignore(10000, '\n');
	        }

			// Setup freq limit to start computation loop
			zobel.freq[0] = f_lo;
			zobel.freq[1] = f_hi;

			cout << "+-----------------------------------------------" << endl;
			cout << "|   Freq       Capacitance      Inductance " << endl;
			cout << "+-----------------------------------------------" << endl;

			zobel.xover_pts = 2;
			for (i = 0; i < zobel.j; i++ ) {
				// Fixed capacitor value is solved for the initial freq value.
				// while the inductance is adjustable for the range of frequency
				if (i == 0) {
				    zobel.filt_c[i] = solve_capacitance(drvr, zobel.freq[i]);
				} else {
				    zobel.filt_c[i] = zobel.filt_c[i - 1];
				}

			    zobel.filt_l[i] = solve_inductance(drvr, zobel.freq[i]);

	        }

			sleep(5);
			break;
    }
}
/*--------------------------------------------------------------------------------------------*/
void passive_check(Speaker* drvr, Speaker*& pasv, Speaker*& pasv_cpy)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will check to see if a passive radiator file has been loaded up to perform  */
/* a design verification/simulation for a passive radirator loaded cabinet.                   */
/*--------------------------------------------------------------------------------------------*/
{

    if (pasv == NULL)  {
	    cout << "No passive radiator is loaded into the applicatin. Please select from the following drivers..." << endl;
		read_driver(pasv, pasv_cpy, "Pass", 1, drvr->Sd);
		//read_passive_driver(pasv, pasv_cpy, 1, drvr->Sd);
        mem_copy(pasv, pasv_cpy);

		sleep(5);
    }
}
/*--------------------------------------------------------------------------------------------*/
void write_design_data(Field_Pad* P0, Field_Pad* P1, Field_Pad* P2, Field_Pad* P3, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This function will print the resulting speaker parameters contained with the formatted     */
/* Field_Pad structure ad write out to a simple text file that the user can then print out.   */
/*--------------------------------------------------------------------------------------------*/
{
	struct Field_Pad *ptr;

    int i;

    cout << "Display current speakers..." << endl;
    cout << "+-----------------------------" << endl;

    sleep(5);
	for (i = 0; i < 4; i++) {
        if (i == 0 ) {
            ptr = P0;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_speaker(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 1) {
            ptr = P1;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_speaker(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 2) {
            ptr = P2;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_speaker(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 3) {
            ptr = P3;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_speaker(ptr, outfile);
                sleep(1);
            }
        }
    }


	sleep(1);
}
/*--------------------------------------------------------------------------------------------*/
void write_cabinet_data(Cabinet* pass, Cabinet* bass, Cabinet* midr, Cabinet* treb, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This function will print the resulting cabinet design parameters and crossover information */
/* to a simple text file that the user can then print out.                                    */
/*--------------------------------------------------------------------------------------------*/
{
	struct Cabinet *ptr;

    int i;

    cout << "Display cabinet parameters..." << endl;
    cout << "+-----------------------------" << endl;

    sleep(5);


    for (i = 0; i < 4; i++) {
        if (i == 0 ) {
            ptr = pass;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_cabinet(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 1) {
            ptr = bass;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_cabinet(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 2) {
            ptr = midr;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_cabinet(ptr, outfile);
                sleep(1);
            }
        }

        if (i == 3) {
            ptr = treb;

            if (ptr == NULL) {
                sleep(1);
            } else {
                print_cabinet(ptr, outfile);
                sleep(1);
            }
        }
    }

	sleep(1);
}
/*--------------------------------------------------------------------------------------------*/
void write_filter_data(Filter zobel, Filter lowpass, Filter bandpass, Filter highpass, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document. It uses */
/* the <filter>.enabled flag on which to print data out.                                      */
/* Since a zobel filter is used in the event of high-inductance bass drivers, it may or may   */
/* not need to be displayed. It certainly will be displayed if a subwoofer network is being   */
/* writen out to a file.                                                                      */
/*--------------------------------------------------------------------------------------------*/
{
	if (zobel.enabled >= 1) {
	     print_zobel(zobel, outfile);
		 return;
	}

	if (highpass.enabled >= 1) {
	     print_twoway_crossover(zobel, lowpass, highpass, outfile);
		 return;
	}

	if (bandpass.enabled >= 1) {
	     print_threeway_crossover(zobel, lowpass, bandpass, highpass, outfile);
		 return;
	}
}
/*--------------------------------------------------------------------------------------------*/
void print_zobel(Filter zobel, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document.         */
/*--------------------------------------------------------------------------------------------*/
{
	int i, j;          // counters for looping constructs

	cout << " " << zobel.xover_type << " values determined by SpeakEasy: " << endl;
	outfile << " " << zobel.xover_type << " values determined by SpeakEasy: " << endl;

	if (zobel.enabled == 1) {
		j = zobel.j;
		outfile << "-----------------------------------------------" << endl;
        outfile << "              Zobel Filter Values              " << endl;
		outfile << "-----------------------------------------------" << endl;
        outfile << " Filter Order = " << zobel.order << endl;
		outfile << "           Rz = " << zobel.Rz << endl;
        outfile << "           Cz = " << zobel.Cz << endl;
        outfile << "           Lz = " << zobel.Lz << endl;
        
		outfile << "-----------------------------------------------" << endl;
        outfile << "  Freq   Capacitance  Inductance" << endl;
        outfile << "-----------------------------------------------" << endl;

		for (i = 1; i < j; i++) {
		    outfile << "| " << zobel.freq[i] << " | " << zobel.filt_c[0] << " | " << zobel.filt_l[i] << endl;
		}
        outfile << "+-----------------------------------------------" << endl;

		return;
	}

	if (zobel.enabled == 2) {
		j = zobel.j;
		outfile << "-----------------------------------------------" << endl;
        outfile << "              Zobel Filter Values              " << endl;
		outfile << "-----------------------------------------------" << endl;
        outfile << " Filter Order = " << zobel.order << endl;
		outfile << "           Rz = " << zobel.Rz << endl;
        outfile << "           Cz = " << zobel.Cz << endl;
        outfile << "           Lz = " << zobel.Lz << endl;
        
		outfile << "-----------------------------------------------" << endl;
		outfile << "            Component LRC Values               " << endl;
		outfile << "-----------------------------------------------" << endl;
        outfile << "  Freq   Capacitance  Inductance" << endl;
		outfile << "-----------------------------------------------" << endl;

		for (i = 0; i < j; i++) {
		    outfile << "| " << zobel.freq[i] << " | " << zobel.filt_c[i] << " | " << zobel.filt_l[i] << endl;
		}
		outfile << "-----------------------------------------------" << endl;

	    return;
	}

	if (zobel.enabled == 3) {
		j = zobel.j;
		outfile << "-----------------------------------------------" << endl;
        outfile << "              Zobel Filter Values              " << endl;
		outfile << "-----------------------------------------------" << endl;
        outfile << " Filter Order = " << zobel.order << endl;
		outfile << "           Rz = " << zobel.Rz << endl;
        outfile << "           Cz = " << zobel.Cz << endl;
        outfile << "           Lz = " << zobel.Lz << endl;
        
		outfile << "-----------------------------------------------" << endl;
		outfile << "            Component LRC Values               " << endl;
		outfile << "-----------------------------------------------" << endl;
        outfile << "  Freq   Capacitance  Inductance" << endl;
		outfile << "-----------------------------------------------" << endl;

		for (i = 0; i < j; i++) {
		    outfile << "| " << zobel.freq[i] << " | " << zobel.filt_c[i] << " | " << zobel.filt_l[i] << endl;
		}
		outfile << "-----------------------------------------------" << endl;
	    return;
	}
    
}
/*--------------------------------------------------------------------------------------------*/
void print_twoway_crossover(Filter zobel, Filter lowpass, Filter highpass, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document.         */
/*--------------------------------------------------------------------------------------------*/
{

    outfile << "+-----------------------------+" << endl;
    outfile << "| Suggested Cross Over Points |" << endl;
    outfile << "+-----------------------------+" << endl;
    outfile << "  Bass/Tweet: " << lowpass.xover[0] << endl;
    outfile << "+---------------------------+" << endl;

	outfile << "-----------------------------------------" << endl;
	outfile << " Zobel filter values " << endl;
	outfile << "-----------------------------------------" << endl;
	outfile << " Rz : " << zobel.Rz << endl;
	outfile << " Lz : " << zobel.Lz << endl;
	outfile << " Cz : " << zobel.Cz << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Filter Values " << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Lpad Potentiometer       : " << highpass.lpad << endl;
    outfile << " Filter Order             : " << lowpass.order << endl;
    outfile << " Low-Pass Frequency (Hz)  : " << lowpass.xover[0] << endl;
    outfile << " High-Pass Frequency (Hz) : " << highpass.xover[0] << endl;
    outfile << " Low-Pass gain (< 1)      : " << lowpass.gain << endl;
    outfile << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    outfile << " Low-Pass 3db freq  (Hz)  : " << lowpass.f3db[0]<< endl;
    outfile << " High-Pass 3db freq  (Hz) : " << highpass.f3db[0]<< endl;
	outfile << " Low-pass Load            : " << lowpass.Z_nom << endl;
	outfile << " Low-Pass Sensitivity     : " << lowpass.Sensitivity << endl;
    outfile << " Low-Pass Capacitance     : " << lowpass.filt_c[0] << endl;
    outfile << " Low-Pass Inductance      : " << lowpass.filt_l[0] << endl;
	outfile << " High-pass Load           : " << highpass.Z_nom << endl;
	outfile << " High-Pass Sensitivity    : " << lowpass.Sensitivity << endl;
    outfile << " High-Pass Capacitance    : " << highpass.filt_c[0] << endl;
    outfile << " High-Pass Inductance     : " << highpass.filt_l[0] << endl;
    outfile << "-----------------------------------------" << endl;

}
/*--------------------------------------------------------------------------------------------*/
void print_threeway_crossover(Filter zobel, Filter lowpass, Filter highpass, Filter bandpass, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document.         */
/*--------------------------------------------------------------------------------------------*/
{

	outfile << "+-----------------------------+" << endl;
    outfile << "| Suggested Cross Over Points |" << endl;
    outfile << "+-----------------------------+" << endl;
    outfile << "  Bass/Midrange : " << bandpass.xover[0] << endl;
    outfile << "  Midrange/Tweet: " << bandpass.xover[1] << endl;
    outfile << "+---------------------------+" << endl;

	outfile << "-----------------------------------------" << endl;
	outfile << " Zobel filter values " << endl;
	outfile << "-----------------------------------------" << endl;
	outfile << " Rz : " << zobel.Rz << endl;
	outfile << " Lz : " << zobel.Lz << endl;
	outfile << " Cz : " << zobel.Cz << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Filter Values " << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Lpad Potentiometer       : " << highpass.lpad << endl;
    outfile << " Filter Low Pass Order    : " << lowpass.order << endl;
    outfile << " Filter Band Pass Order   : " << bandpass.order << endl;
    outfile << " Filter High PassOrder    : " << highpass.order << endl;
    outfile << " Low-Pass Frequency (Hz)  : " << lowpass.xover[0] << endl;
    outfile << " Bann-Pass Frequency(1)   : " << highpass.xover[0] << endl;
    outfile << " Band-Pass Frequency(2)   : " << highpass.xover[0] << endl;
    outfile << " High-Pass Frequency (Hz) : " << highpass.xover[0] << endl;
    outfile << " Low-Pass gain (< 1)      : " << lowpass.gain << endl;
    outfile << " Band-Pass gain (< 1)     : " << highpass.gain << endl;
    outfile << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    outfile << " Low-Pass 3db freq  (Hz)  : " << lowpass.f3db[0]<< endl;
    outfile << " Band-Pass 3db freq  (Hz) : " << lowpass.f3db[0]<< endl;
    outfile << " Band-Pass 3db freq  (Hz) : " << lowpass.f3db[0]<< endl;
    outfile << " High-Pass 3db freq  (Hz) : " << highpass.f3db[0]<< endl;
    outfile << " Band-pass Load           : " << bandpass.Z_nom << endl;
    outfile << " High-pass Load           : " << highpass.Z_nom << endl;
    outfile << " Low-Pass Sensitivity     : " << lowpass.Sensitivity << endl;
    outfile << " Band-Pass Sensitivity    : " << bandpass.Sensitivity << endl;
    outfile << " High-Pass Sensitivity    : " << highpass.Sensitivity << endl;
    outfile << " Low-pass Load            : " << lowpass.Z_nom << endl;
    outfile << " Low-Pass Capacitance     : " << lowpass.filt_c[0] << endl;
    outfile << " Low-Pass Inductance      : " << lowpass.filt_l[0] << endl;
    outfile << " Band-pass Load           : " << bandpass.Z_nom << endl;
    outfile << " Band-Pass Capacitance C1 : " << bandpass.filt_c[0] << endl;
    outfile << " Band-Pass Inductance  L1 : " << bandpass.filt_l[0] << endl;
    outfile << " Band-Pass Capacitance C2 : " << bandpass.filt_c[1] << endl;
    outfile << " Band-Pass Inductance  L2 : " << bandpass.filt_l[1] << endl;
    outfile << " High-pass Load           : " << highpass.Z_nom << endl;
    outfile << " High-Pass Sensitivity    : " << lowpass.Sensitivity << endl;
    outfile << " High-Pass Capacitance    : " << highpass.filt_c[0] << endl;
    outfile << " High-Pass Inductance     : " << highpass.filt_l[0] << endl;
    outfile << "-----------------------------------------" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void purge_data(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will simply reset/point all current pointers to NULL and allow the design   */
/* to start from the beginning.                                                               */
/*--------------------------------------------------------------------------------------------*/
{
	cout << "delete record..." << endl;

    if (drvr != NULL) {
        delete drvr;        // Delete the node (frees memory)
        drvr = nullptr;     // Set the pointer to null
	    cout << "Record deleted..." << endl;
    } else {
		return;
	}

	sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
void clear_formatting(Field_Pad* datum)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will simply reset/point all current pointers to NULL and allow the design   */
/* to start from the beginning.                                                               */
/*--------------------------------------------------------------------------------------------*/
{
	cout << "delete record..." << endl;

    if (datum != NULL) {
        delete datum;        // Delete the node (frees memory)
        datum = nullptr;     // Set the pointer to null
	    cout << "Record deleted..." << endl;
    } else {
		return;
	}

	sleep(2);
}
/*--------------------------------------------------------------------------------------------*/
void display_vented_data(Speaker* drvr, Cabinet* box)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print out the speaker/cabinet data for the user to review and/or write */
/* to file.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
{
        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " |                      Cabinet Build Values                       |" << endl;
        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " |     Driver name : " << drvr->Part_num << endl;
        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " | Type         : " << drvr->Type << endl;
        cout << " | Vbv          : " << drvr->Vbv * 1000.0 << endl;
        cout << " | Vas          : " << drvr->Vas * 1000.0 << endl;
        cout << " | Fb           : " << drvr->Fb << endl;
        cout << " | 3db freq     : " << drvr->f3_vent << endl;
        cout << " | Fs           : " << drvr->Fs << endl;
        cout << " | Sd           : " << drvr->Sd * 1000.0 << endl;
        cout << " | Nominal Ohms : " << drvr->Z_nom << endl;
        cout << " | Nominal Power: " << drvr->Nom_Pwr << endl;
        cout << " | Max Power    : " << drvr->Max_Pwr << endl;
        cout << " | Low Freq     : " << drvr->Freq_Low << endl;
        cout << " | High Freq    : " << drvr->Freq_Hi << endl;
        cout << " | Sensitivity  : " << drvr->Sensitivity << endl;
        cout << " | Height       : " << drvr->w_height << endl;
        cout << " | Width        : " << drvr->w_width << endl;
        cout << " | Length       : " << drvr->p_length << endl;
        cout << " | Volume Gross : " << drvr->Vol_gross * 1000.0 << endl;
        cout << " +-----------------------------------------------------------------+" << endl;

        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " |                     Box Design Values                           |" << endl;
        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " |     Driver name : " << box->Part_num << endl;
        cout << " +-----------------------------------------------------------------+" << endl;
        cout << " | Type          : " << box->Type << endl;
		cout << " | Build         : " << box->Build << endl;
        cout << " | Cabinet Volume: " << box->cab_volume << endl;
        cout << " | Port Volume   : " << box->port_volume << endl;
        cout << " | Gross Volume  : " << box->gross_volume << endl;
        cout << " | Vent Diam     : " << box->port_diam << endl;
        cout << " | Vent Width    : " << box->port_width << endl;
        cout << " | Vent Length   : " << box->port_length << endl;
        cout << " | Speaker Diam  : " << box->diam << endl;
        cout << " | Speaker Height: " << box->height << endl;
        cout << " | Speaker Depth : " << box->depth << endl;
        cout << " | Low Frequency : " << box->freq_lo << endl;
        cout << " | High Frequency: " << box->freq_hi << endl;
        cout << " | Nominal Imp   : " << box->imp_Nom << endl;
        cout << " | Sensitivity   : " << box->Sensitivity << endl;
        cout << " | Resonance Freq: " << box->res_freq << endl;
        cout << " | Tuning Freq   : " << box->Fb << endl;
        cout << " | PAR Power     : " << box->PAR << endl;
        cout << " | PER Power     : " << box->PER << endl;
        cout << " | R(h)          : " << box->Rh << endl;
        cout << " +-----------------------------------------------------------------+" << endl;
     
}
/*--------------------------------------------------------------------------------------------*/

