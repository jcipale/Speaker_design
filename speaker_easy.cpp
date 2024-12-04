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
    struct Speaker *temp, *bass, *bandp, *high, *passive;

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
    cout << "    BL (Force Factor)                : ";
    cin >> temp->Bl;
    cout << "    Qts (Total Q factor)             : ";
    cin >> temp->Qts;
    cout << "    Qes (Electric Q factor)          : ";
    cin >> temp->Qes;
    cout << "    Qms (Mech Q factor)              : ";
    cin >> temp->Qms;
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
    cout << "    Xmax (mm)                        : ";
    cin >> temp->Xmax;
    cout << "    Diam (mm)                        : ";
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
    cout << "    v_length (vent length)           : ";
    cin >> temp->v_length;
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

            if (ptr == NULL) {
                //cout << "Parts List is empty..." << endl;
                sleep(1);
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    
    
        if (i == 1) { 
            ptr = mid; 
    
            if (ptr == NULL) {
                //cout << "Parts List is empty..." << endl;
                sleep(1);
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    

        if (i == 2) { 
            ptr = tweet;
    
            if (ptr == NULL) {
                //cout << "Parts List is empty..." << endl;
                sleep(1);
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    

        if (i == 3) { 
            ptr = pass;
    
            if (ptr == NULL) {
                //cout << "Parts List is empty..." << endl;
                sleep(1);
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
        cout << "    Avalable Speaker Parts:... " << endl;
        ptr = drvr;  //Set the temporary pointer to the head of the list

        while (ptr != NULL) {
            cout << "Part Number            : " << ptr->Part_num << endl;
            cout << "Type                   : " << ptr->Type << endl;
            cout << "Build                  : " << ptr->Build << endl;
            cout << "Vas (L || dm^3)        : " << ptr->Vas << endl;
            cout << "Cms                    : " << ptr->Cms << endl;
            cout << "Bl                     : " << ptr->Bl  << endl;
            cout << "Qts                    : " << ptr->Qts << endl;
            cout << "Qes                    : " << ptr->Qes << endl;
            cout << "Qms                    : " << ptr->Qms << endl;
            cout << "Fs (Hz)                : " << ptr->Fs << endl;
            cout << "Re (Ohms)              : " << ptr->Re << endl;
            cout << "Rms                    : " << ptr->Rms << endl;
            cout << "Z_nom (Ohms)           : " << ptr->Z_nom << endl;
            cout << "Le (mH)                : " << ptr->Le << endl;
            cout << "Xmax (mm)              : " << ptr->Xmax << endl;
            cout << "Diam (mm)              : " << ptr->Diam << endl;
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
            cout << "vent diam  (mm)        : " << ptr->v_diam << endl;
            cout << "vent length (mm)       : " << ptr->v_length << endl;
            cout << "speaker diam (mm)      : " << ptr->b_diam << endl;
            cout << "speaker ht/length (mm) : " << ptr->b_height << endl;
            cout << "speaker depth (mm)     : " << ptr->depth << endl;
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
    struct Field_Pad *ptr;

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
    struct Cabinet *ptr;

	sleep(5);

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
			    outfile << "| Vent Diam | " << cptr->vent_diam << " |" << endl;
			    outfile << "| Vent Lgth | " << cptr->vent_length << " |" << endl;
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
            outfile << "| Cab Width  | " << cptr->W << " |" << endl;
            outfile << "| Cab Height | " << cptr->H << " |" << endl;
            outfile << "| Cab Depth  | " << cptr->D << " |" << endl;
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
/*     closed_box_param_set()                                                                 */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    //struct Cabinet *temp, *cptr, *bass, *midr, *treb;
    struct Cabinet *temp, *bass, *midr, *treb;

    //temp=(struct Cabinet *)malloc(sizeof(struct Cabinet));

    std::string cab_type;           // Type of cabinet being built - vented or sealed.
	                                // Passive radiator defaults to sealed.

    double Vd;                      // Speaker displacement volume - part of overall cabinet volume

	char fill[4];                   // Box is filled (1) or not (0)
	char units[8];                  // used to display centimeters or inches

    system("clear");

	cout << "Box Design Debug: Speaker Type: " << drvr->Type << endl;
	sleep(2);

	// Determine speaker displacement
    if (strcmp(ptr->Type, "Tweet") == 0) {
	    Vd = 0;
		cout << " Design a Tweeter space.. " << endl;
		sleep(1);
		design_tweeter_sealed(drvr, cptr, Vd);
		treb = cptr;
    } 

	if (strcmp(ptr->Type, "Woof") == 0) {
        Vd = (M_PI * pow((drvr->Diam/2), 2) * drvr->Xmax);
	cout << " Design a Bass space.. " << endl;
	sleep(1);
        design_low_sealed(drvr, cptr, Vd);
        bass = cptr;
    } 

    if (strcmp(ptr->Type, "Midr") == 0) {
        Vd = (M_PI * pow((drvr->Diam/2), 2) * drvr->Xmax);
	cout << " Design a Midrange space.. " << endl;
	sleep(1);
        design_low_sealed(drvr, cptr, Vd);
        midr = cptr;
	}

}
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, double& Vbs, double& alpha, double& gamma, double Qa, double& Fsb, double& Vab, double& L, double& Qtc, double& Qtcp, double& fc, double& A1, double& f3, double& peak, double& Par, double& Per, double& Rh, double& Vd)
/*--------------------------------------------------------------------------------------------*/
/* closed_box_param_set() will take the settingd used to define the closed_box parameters     */
/* derived from gamma and Qa based on the choice to use fill material or no. The user defines */
/* the fill parameter progamatically.                                                         */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;
	
    char flag;                 // trigger to ignore switch stmt and fall into case statement

    double a, b, c, d;          // Intermediate placeholders to ease complex math evaluations
    double alpha_p;
    double Fsb_p;
    double Qt;                  // Total Q factor - computed
	double power;
	

    int choice;

    flag = 1;

    //Vbs = ptr->Vbs;
    //Fsb = ptr->Fs;
    
	Qt = compute_qt(ptr->Qes, ptr->Qms);
    switch (bdesign) {
        case 1:
            cout << "Design centered around default values : " << endl;
            
			Vbs = ptr->Vbs;
            Vab = Vbs * gamma;
            alpha = ptr->Vas/ptr->Vbs;

            L = sqrt(alpha + 1);

			Fsb = ptr->Fs * sqrt(1 + alpha);

            fc = L * Fsb;

            //Qtc = 1/((1/Qtcp) + (1/Qa));

            A1 = (1/pow(ptr->Qts, 2)) - 2;

            f3 = ptr->f3_seal;

			cout << "------------------------------------------" << endl;
			cout << " Default sealed box values " << endl;
			cout << "------------------------------------------" << endl;
			cout << " Qa      : " << Qa << endl;
			cout << " gamma   : " << gamma << endl;
			cout << " Vab     : " << Vab << endl;
			cout << " Alpha   : " << alpha << endl;
			cout << " L       : " << L << endl;
			cout << " Fsb     : " << Fsb << endl;
			cout << " fc      : " << fc << endl;
			cout << " Qtcp    : " << Qtcp << endl;
			cout << " A1      : " << A1 << endl;
			cout << " f3      : " << f3 << endl;
			cout << "------------------------------------------" << endl;

			// Modify values of speaker struct
			ptr->Vbs = Vbs;
			ptr->Fs = Fsb;
			ptr->f3_seal = f3;

            break;

        case 2:
            cout << "Enter speaker box volume in decimeters^3: ";
            cout << "Sspeaker volume = " << ptr->Vbs << " )" << endl;
            cout << "Enter: ";
            cin >> Vbs;

            Vab = Vbs * gamma;

            alpha = ptr->Vas/Vbs;

            L = sqrt(alpha + 1);

            Qtcp = L * ptr->Qts;

            Qtc = 1/((1/Qtcp) + (1/Qa));

            A1 = (1/pow(Qtc, 2)) - 2;

			Fsb = ptr->Fs * sqrt(1 + alpha);

            fc = L * Fsb;

            Qtcp = L * ptr->Qts;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);
            
            if (ptr->f3_seal <= 0) {
                ptr->f3_seal = f3;
            }
            
			cout << "------------------------------------------" << endl;
			cout << " Modify sealed box volume " << endl;
			cout << "------------------------------------------" << endl;
			cout << " Qa      : " << Qa << endl;
			cout << " gamma   : " << gamma << endl;
			cout << " Vab     : " << Vab << endl;
			cout << " Alpha   : " << alpha << endl;
			cout << " A1      : " << A1 << endl;
			cout << " L       : " << L << endl;
			cout << " Fsb     : " << Fsb << endl;
			cout << " fc      : " << fc << endl;
			cout << " Qtcp    : " << Qtcp << endl;
			cout << " Qtc     : " << Qtc << endl;
			cout << " f3      : " << f3 << endl;
			cout << "------------------------------------------" << endl;

			// Modify values of speaker struct
			ptr->Vbs = Vbs;
			ptr->Fs = Fsb;
			ptr->f3_seal = f3;

            break;

        case 3:
            cout << "Choose design based on user specified value of Q(tc) (.5 <= Qtc <= 0.9) :";
            cout << "Enter: ";
            cin >> Qtc;

            Qtcp = 1/((1/Qtc) - (1/Qa));

            L = Qtcp/Qt;

            alpha = pow(L, 2) - 1;

            Vab = ptr->Vas/alpha;

            A1 = (1/pow(Qtc, 2)) - 2;

            Vbs = Vab/gamma;

            fc = L * Fsb;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);
            
			Fsb = ptr->Fs * sqrt(1 + alpha);
            
			cout << "------------------------------------------" << endl;
			cout << " Modify Qtc value " << endl;
			cout << "------------------------------------------" << endl;
			cout << " Qa      : " << Qa << endl;
			cout << " gamma   : " << gamma << endl;
			cout << " Vab     : " << Vab << endl;
			cout << " Vbs     : " << Vbs << endl;
			cout << " Alpha   : " << alpha << endl;
			cout << " A1      : " << A1 << endl;
			cout << " L       : " << L << endl;
			cout << " Fsb     : " << Fsb << endl;
			cout << " fc      : " << fc << endl;
			cout << " Qtcp    : " << Qtcp << endl;
			cout << " Qtc     : " << Qtc << endl;
			cout << " f3      : " << f3 << endl;
			cout << "------------------------------------------" << endl;

			// Modify values of speaker struct
			ptr->Vbs = Vbs;
			ptr->Fs = Fsb;
			ptr->f3_seal = f3;

            break;

        default:
            cout << "Choose design based on default value of Q(tc) to 1.00" << endl;
            Qtc = 1.00;

            Qtcp = 1/((1/Qtc) - (1/Qa));
            L = Qtcp/Qt;

            alpha = pow(L, 2) - 1;

            Vab = ptr->Vas/alpha;

            A1 = (1/pow(Qtc, 2)) - 2;

            Vbs = Vab/gamma;

            fc = L * Fsb;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);

			Fsb = ptr->Fs * sqrt(1 + alpha);

			cout << "------------------------------------------" << endl;
			cout << " Default value of Qtc = 1 " << endl;
			cout << "------------------------------------------" << endl;
			cout << " Qa      : " << Qa << endl;
			cout << " gamma   : " << gamma << endl;
			cout << " Vab     : " << Vab << endl;
			cout << " Vbs     : " << Vbs << endl;
			cout << " Alpha   : " << alpha << endl;
			cout << " A1      : " << A1 << endl;
			cout << " L       : " << L << endl;
			cout << " Fsb     : " << Fsb << endl;
			cout << " fc      : " << fc << endl;
			cout << " Qtcp    : " << Qtcp << endl;
			cout << " Qtc     : " << Qtc << endl;
			cout << " f3      : " << f3 << endl;
			cout << "------------------------------------------" << endl;

			// Modify values of speaker struct
			ptr->Vbs = Vbs;
			ptr->Fs = Fsb;
			ptr->f3_seal = f3;

            break;

    }
    //ptr->Vbs = Vbs;

    if (A1 >= 0) {
        peak = 0;
    } else {
        peak = 10 * log(4/(4 - pow(A1, 2)));
    }

	/*
    cout << "-------------------------------------" << endl;
    cout << " Debug - intermediate data           " << endl;
    cout << "-------------------------------------" << endl;
    cout << " Sealed box volume (Vbs) : " << ptr->Vbs << endl;
    cout << " Sealed box volume (Vbs) : " << Vbs << endl;
    cout << " Vas                     : " << ptr->Vas << endl;
    cout << " ratio of Vas/Vbs (alpha): " << alpha << endl;
    cout << "-------------------------------------" << endl;
    cout << " Intermediate value computations     " << endl;
    cout << "-------------------------------------" << endl;
    cout << " L                       : " << L << endl;
    cout << " Qtc(prime)              : " << Qtcp << endl;
    cout << " Qtc (Total closed box Q): " << Qtc << endl;
    cout << " System Q(ts)            : " << ptr->Qts << endl;
    cout << " A1 (data multiplier)    : " << A1 << endl;
    cout << " fc (closed box res freq): " << fc << endl;
    cout << " free-air resonance Fs   : " << ptr->Fs << endl;
    cout << " Closed box resonance Fs : " << Fsb << endl;
    cout << " Piston area Vd          : " << Vd << endl;
    cout << " 3db rolloff (data sheet): " << ptr->f3_seal << endl;
    cout << " 3db rolloff (calculated): " << f3 << endl;
    cout << "-------------------------------------" << endl;
    cout << " Sealed box Qa           : " << Qa << endl;
    cout << " sealed box gamma        : " << gamma << endl;
    cout << " Peak db value           : " << peak << endl;
    cout << "-------------------------------------" << endl;
	*/

    sleep(5);

	// Electrical/Acoustigal measurements
	Per = compute_efficiency(drvr) * 100.0;
	Par = 1/(compute_efficiency(drvr));

    // 3db Ripple 
	Rh = ptr->Fs * sqrt(((ptr->Vas)/(ptr->Vbs)) + 1.0);
    closed_freq_response(drvr, A1, f3, fc, Fsb);
}
/*--------------------------------------------------------------------------------------------*/
void passive_box_design(Speaker*& drvr, Cabinet*& box, Cabinet*& pass)
/*--------------------------------------------------------------------------------------------*/
/* closed_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     closed_box_param_set()                                                                 */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *ptr;
    ptr = drvr;

    cout << "TEST PROCEDURE" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void closed_freq_response(Speaker* drvr, double A1, double f3, double fc, double Fsb)
/*--------------------------------------------------------------------------------------------*/
/* closed_freq_response() plots the frequency rsponse of a sealed box speaker for the chosen  */
/* driver.                                                                                    */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;
    
    double a, b, c, d;                     // Intermediate variables used to keep track
                                          // of computations and ease readability
    double i;
    double Fn;
    double R, Rp;

    system("clear");

    cout << "Specify speaker plot file: ";
    cin >> plot_data;
    plot_name = plot_data + ".gp";

    ofstream plotfile;
    plot_data = plot_data + ".csv";
    plotfile.open(plot_data);

    //----------------------------
    // Compute freq response here
    //----------------------------

    plotfile << "Frequency (Hz), Amplitude (dB)" << endl;
    cout << "\tfreq\t\tdecibels" << endl;
    cout << "-------------------------------------" << endl;

    for ( i = ptr->Freq_Low; i <= ptr->Freq_Hi; i = i + 10) {
        Fn = i/fc;

        /* NOTE: Need to investigate/understand why values flip to negative  */
        /* for values c and d when the box volume is smaller than the default*/
        /* sealed box volume.                                                */
        a = pow(Fn, 2);
        a = abs(a);

        b = pow(Fn, 3);
        b = abs(b);

        c = a + (A1 * b) + 1;
        c = abs(c);

        d = (pow(Fn, 4)/c);
        d = abs(d);

        R =  10 * log(d);
        R = abs(R);

        if (isnan(R)) {
            R = 0.0;
        }

        if (i <= 100) {
            cout << "\t " << i << "\t\t\t" << R << endl;
            plotfile << i << ", " << R << endl;
        } else {
            cout << "\t " << i << "\t\t" << R << endl;
            plotfile << i << ", " << R << endl;
        }

    }
    /* Finish coding freq response loop here */
    plotfile.close();

    ofstream gplot;
    gplot.open(plot_name);
    gplot << "set terminal xterm" << endl;
    gplot << "set output 'loudspeaker_frequency_response.png'" << endl;
    gplot << "set title 'Loudspeaker Frequency Response'" << endl;
    gplot << "set xlabel 'Frequency (Hz)'" << endl;
    gplot << "set ylabel 'Amplitude (dB)'" << endl;
    gplot << "set xrange [" << ptr->Freq_Low << ":" << ptr->Freq_Hi << "]" << endl;
    gplot << "set yrange [-40:60]" << endl;
    gplot << "set grid" << endl;
    gplot << "set key top left" << endl;
    gplot << "plot '" << plot_data << "' using 1:2 with lines title 'Frequency Response'" << endl;
    gplot.close();
}
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Cabinet*& box)
/*--------------------------------------------------------------------------------------------*/
/* vented_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     freq_params()                                                                          */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    struct Cabinet *temp, *bass, *midr, *treb, *vptr;

    temp=(struct Cabinet *)malloc(sizeof(struct Cabinet));

	char fill[4];
	
	double a;
	double Dv;                   // Default vent diameter
	double Lv;                   // Default port length 
	double Vd;                   // Diameter of speaker cone

    std::string cab_type;
	
    /* Default flat values */
    //Dv = 50.0; // Set Vent diameter to 50mm by default;
    //Lv = 50.0;

	// Determine speaker displacement
    if (strcmp(ptr->Type, "Tweet") == 0) {
        Vd = 0;
		treb = temp;
        design_tweeter_sealed(drvr, treb, Vd);
    } else if (strcmp(ptr->Type, "Woof") == 0) {
        Vd = (M_PI * pow((drvr->Diam/2), 2) * drvr->Xmax);
        design_low_vented(drvr, bass, Vd);
        midr = temp;
    } else {
        Vd = (M_PI * pow((drvr->Diam/2), 2) * drvr->Xmax);
        design_low_sealed(drvr, midr, Vd);
        bass = temp;
    }

}
/*--------------------------------------------------------------------------------------------*/
void closed_freq_params(Speaker* drvr, double& Qa, double& gamma, double& alpha, double& A1, double& Fsb, double& Fcb, double& Fs, double& f3, double& Fb, double& Fc, double& L, double& Vd, double& Qtc, double& Qtcp, double& Vab, double& Rh, double& R, double& Par, double& Per) 
/*--------------------------------------------------------------------------------------------*/
/* closed_freq_params - evaluates the Small/Thiele parameters for a closed box systeem in     */
/* preparation for evaluating the peak power and frequency response.                          */
/*--------------------------------------------------------------------------------------------*/
{

    struct Speaker *ptr;
    ptr = drvr;

    char fill[4];                  // Box is filled (1) or not (0)
    double a, b, c, d;              // intermediate compute buckets
        
    // Box volume based on fill factor
    Vab = gamma * ptr->Vbs;

    // Compliance ration between Compliance and the value of the sealed box volume 
    alpha = ptr->Vas/Vab;
    
    // Multiplier factor
    L = sqrt(alpha + 1);

    // Qtc prime of sealed box measured at Fc
    Qtcp = L * ptr->Qts;

    // Total Qtc
    a = 1/Qa;

    b = 1/Qtcp;

    Qtc = a + b;
    c = 1/Qtc;

    Fc = L * ptr->Fs;
    A1 = (1/pow(Qtc, 2)) - 2;

    // Compute the 3db rolloff
    a = (pow(A1, 2) + 4);
    b = sqrt(a) + A1;
    c = sqrt(b/2);
    f3 = Fc * c;
    ptr->f3_seal = f3;

    if (A1 < 0) {
        Rh = 10 * log (4 /(4 - pow(A1, 2)));
    } else {
        Rh = 0;
    }
        
    // Displaement limited power ratings
	Per = compute_efficiency(drvr) * 100.0;
	Par = 1/(compute_efficiency(drvr));

	// Specify design choice beyond just "flat alignment" 
    cout << "-----------------------------------------------------------" << endl;
    cout << "Closed Box design values - flat alignment" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Driver name               :    " << ptr->Part_num << endl;
    cout << " Driver Resonance freq (Hz):    " << ptr->Fs  << endl;
    cout << " Total Mechanical Q        :    " << ptr->Qts << endl;
    cout << " Qa                        :    " << Qa  << endl;
    cout << " Qtcp                      :    " << Qtcp  << endl;
    cout << " Qtc                       :    " << Qtc  << endl;
    cout << " Equivalent cabinet volume :    " << ptr->Vas << endl;
    cout << " Enclosure Internal volume :    " << ptr->Vbs << endl;
    cout << " Volume - air displacement :    " << Vd << endl;
    cout << " -3db frequency rolloff    :    " << ptr->f3_seal << endl;
    cout << " -3db frequency computed   :    " << f3 << endl;
    cout << " Enclosure resonance freq  :    " << Fc << endl;
    cout << " gamma                     :    " << gamma << endl;
    cout << " Vab                       :    " << Vab << endl;
    cout << " alpha                     :    " << alpha << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Ripple (in decibels)      :    " << Rh << endl;
    cout << " Frequency range           :    " << ptr->Freq_Low << " - " << ptr->Freq_Hi << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "              Displacement Power Ratings                   " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Electrical Efficiency     :    " << Per << " % " << endl;
    cout << " Accoustical Power         :    " << Par << " W " << endl;
    cout << "-----------------------------------------------------------" << endl;

    sleep(5);

}
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, double& Vbv, double& Fsb, double& Fb, double& Fn, double& Vd, double& L_prm, double& alpha)
/*--------------------------------------------------------------------------------------------*/
/* vented_freq_params() used to compute intermediate Thiel/Small values ised for vented box   */
/* loudspeaker design. Ideally, the user could pass a single flag that would toggle between   */
/* vented- and closed-speaker design.                                                         */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    double A, B, C, D;
    double Vb;

	/* Revise and rewrite */
	sleep(10);

	/*
    cout << "Vented Box design values - flat alignment" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Driver name                      : " << ptr->Part_num << endl;
    cout << " Driver Resonance freq (Hz)       : " << ptr->Fs  << endl;
    cout << " Enclosure resonance freq         : " << Fb << endl;
    cout << " -3db frequency rolloff           : " << ptr->f3_vent << endl;
    cout << " Total Mechanical Q               : " << ptr->Qts << endl;
    cout << " Equivalent cabinet volume        : " << ptr->Vas << endl;
    cout << " Enclosure Internal volume        : " << ptr->Vbv << endl;
    cout << " Volume - air displacement  (m^3) : " << Vd << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Frequency range                  : " << ptr->Freq_Low << " - " << ptr->Freq_Hi << endl;
    cout << " Minimum vent diameter            : " << ptr->v_diam << endl;
    cout << " Vent length                      : " << ptr->v_length << endl;
    cout << "-----------------------------------------------------------" << endl;
	*/
        
    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void vented_freq_response(Speaker* drvr, double Fsb, double Fb, double Fn, double alpha) 
/*--------------------------------------------------------------------------------------------*/
/* vented_freq_response() is used to write the results of the frequency calculation to a CSV  */
/* format text file. The file will be read by the GNUplot graphing utility and displayed.     */
/*--------------------------------------------------------------------------------------------*/
{

    struct Speaker *ptr;
    ptr = drvr;

    double A, B, C, D;                            // Intermediate placeholders variables
    double a, b, c, d;                            // Intermediate placeholders
    
    double R;                                     // Decibel value for plotting

    int i;                                       // loop frequncy countrt

    system("clear");

    cout << "Specify speaker plot file: ";
    cin >> plot_data;
    plot_name = plot_data + ".gp";

    ofstream plotfile;
    plot_data = plot_data + ".csv";
    plotfile.open(plot_data);

    //----------------------------
    // Compute freq response here
    //----------------------------

    A = pow((Fb/Fsb), 2);
    B = (A/ptr->Qts) + (Fb/(7 * Fsb));
    C = 1 + A + alpha + Fb/(7 * Fsb * ptr->Qts);
    D = (1/ptr->Qts) + Fsb/(7 * Fsb);

    plotfile << "Frequency (Hz), Amplitude (dB)" << endl;
    cout << "\tfreq\t\tdecibels" << endl;
    cout << "-------------------------------------" << endl;

    for (i = ptr->Freq_Low; i <= ptr->Freq_Hi; i = i + 5) {

        Fn = i/Fsb;

        a = pow(Fn, 4);
        b = pow(Fn, 2);

        c = (a - (C * b) + A);
        d = b * pow((D * b - B), 2);

        R = 20 * log(a/(pow((c + d), 0.5)));
        if (isnan(R)) {
            R = 0.0;
        }

        R = abs(R);

        if (i <= 100) {
            cout << "\t " << i << "\t\t\t" << R << endl;
            plotfile << i << ", " << R << endl;
        } else {
            cout << "\t " << i << "\t\t" << R << endl;
            plotfile << i << ", " << R << endl;
        }
    }
    plotfile.close();

    ofstream gplot;
    gplot.open(plot_name);
    gplot << "set terminal xterm" << endl;
    gplot << "set output 'loudspeaker_frequency_response.png'" << endl;
    gplot << "set title 'Loudspeaker Frequency Response'" << endl;
    gplot << "set xlabel 'Frequency (Hz)'" << endl;
    gplot << "set ylabel 'Amplitude (dB)'" << endl;
    gplot << "set xrange [" << ptr->Freq_Low << ":" << ptr->Freq_Hi << "]" << endl;
    gplot << "set yrange [-40:60]" << endl;
    gplot << "set grid" << endl;
    gplot << "set key top left" << endl;
    gplot << "plot '" << plot_data << "' using 1:2 with lines title 'Frequency Response'" << endl;
    gplot.close();
}
/*--------------------------------------------------------------------------------------------*/
void crossover_design() {
    system("clear");
    cout << "Design the crossover..." << endl;
}
/*--------------------------------------------------------------------------------------------*/
void graph_performance() {
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

    int i;

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
/* contains data.  
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    char file_name[40];

    drvr_dba = drvr->Part_num;

    drvr_dba = drvr_dba + ".sdb";

    ofstream outfile(drvr_dba);

    if (drvr == NULL) {
        cout << "Speaker Parts List is empty..." << endl;
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
            outfile << ptr->Bl << ";";
            outfile << ptr->Qts << ";";
            outfile << ptr->Qes << ";";
            outfile << ptr->Qms << ";";
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
            outfile << ptr->v_length << ";";
            outfile << ptr->b_diam << ";";
            outfile << ptr->b_height << ";";
            outfile << ptr->depth << ";";
            ptr = ptr->next;
            
            sleep(3);
        }
    }
}
/*--------------------------------------------------------------------------------------------*/
//void read_bass_driver(Speaker*& drvr, std::string& speaker)
void read_bass_driver(Speaker*& drvr)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr, *temp;

    char line[256];
    char *token;
    
    int i, j, k;

    double num;

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
        temp->Bl = atof(token);
        token = strtok(NULL, ";");
        temp->Qts = atof(token);
        token = strtok(NULL, ";");
        temp->Qes = atof(token);
        token = strtok(NULL, ";");
        temp->Qms = atof(token);
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
        temp->v_length = atof(token);
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
        ptr = drvr;
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
    struct Speaker *ptr, *temp;

    char line[256];
    char *token;
    
    int i, j, k;

    double num;

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
        temp->v_length = atof(token);
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
        ptr = midr;
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
    struct Speaker *ptr, *temp;

    char line[256];
    char *token;
    
    int i, j, k;

    double num;

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
        temp->v_length = atof(token);
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
        ptr = tweet;
    }

    //sleep(3);
}
/*--------------------------------------------------------------------------------------------*/
void read_passive_driver(Speaker*& passive)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr, *temp;

    char line[256];
    char *token;
    
    int i, j, k;

    double num;

    string cmd_str;
    string filesdb = "";

    ifstream infile;
    ifstream input;

    passive = NULL;
    system("clear");
    drvr_dba = "";

    cout << "-------------------------------" << endl;
    sleep(3);
    cmd_str = "./driver.csh Pass";

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
        temp->v_length = atof(token);
        token = strtok(NULL, ";");
        temp->b_diam = atof(token);
        token = strtok(NULL, ";");
        temp->b_height = atof(token);
        token = strtok(NULL, ";");
        temp->depth = atof(token);
        token = strtok(NULL, ";");
        temp->next = NULL;
    
        sleep(2);
        passive = temp;
        ptr = passive;
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

	double tmp_value;

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
		tmp_str = to_string(temp->v_length);
		strcpy(parse->v_length, tmp_str.c_str());
		center_field(parse->v_length);
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

	double tmp_value;

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
		tmp_str = to_string(temp->vent_diam);
		strcpy(cparse->vent_diam, tmp_str.c_str());
		center_field(cparse->vent_diam);
		tmp_str = to_string(temp->vent_length);
		strcpy(cparse->vent_length, tmp_str.c_str());
		center_field(cparse->vent_length);
		if (strcmp(cparse->Enclosure, "Vented") == 0) {
		    outfile << "| Vent Diam | " << cparse->vent_diam << "|" << endl;
            outfile << "| Vent Lgth | " << cparse->vent_length << "|" << endl;
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
		tmp_str = to_string(temp->H);
		strcpy(cparse->H, tmp_str.c_str());
		center_field(cparse->H);
		outfile << "| Cab Height | " << cparse->H << "|" << endl;
		tmp_str = to_string(temp->W);
		strcpy(cparse->W, tmp_str.c_str());
		center_field(cparse->W);
		outfile << "| Cab Width  | " << cparse->W << "|" << endl;
		tmp_str = to_string(temp->D);
		strcpy(cparse->D, tmp_str.c_str());
		center_field(cparse->D);
		outfile << "| Cab Depth  | " << cparse->D << "|" << endl;
		cparse->next = NULL;
		cdatum = cparse;
		outfile << "+------------+-----------------------+" << endl;

		sleep(2);
	}
}
/*--------------------------------------------------------------------------------------------*/
void passive_two_way(Speaker* drvr, Speaker* tweet, Filter& lowpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (capcitance) and the desired crossover    */
/* point for the speaker. The function will then compute the values of a 1st order crossover. */
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/*--------------------------------------------------------------------------------------------*/
{
    char xovr[8];     /* response to modify high pass cut-off frequency. */
    char loop[8];     /* control parameter to determine correctness of solution. */

    double res_freq;   /* resonant frequency of the bandpass filter */
    double gain;       /* Gain at cut-off frequency for filter.  */
    double xover;      /* Cross-ver or frequency cut-off for filter(s)  - high/low pass */
    double f3db1;      /* -3db cut-off frequency for 2-way speaker. */

    double C1, C2;     /* User defined value for capacitance for filter cut-off */
    double R1, R2;     /* Computed resistance for given capacitance and crossover frequency. */
    int i;            /* Counter value for storing the values in the number of cascading stages. */
    int stages;       /* Number of stages used to determine the order of the filter. */
                      /* Default is 1 (1st order Butterworth Filter). */

    string low_parse = "";    /* The following strings are used to store the parsed data from    */
    string high_parse = "";   /* the speaker node passed in to display the part and frequency    */
                              /* band-width.                                                     */
                              
    cout << "This is a Butterworth passive crossover for 2 driver speaker. " << endl;
    lowpass.xover_type = "Passive";
    highpass.xover_type = "Passive";

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

    cout << "===============================================================================" << endl;
    cout << "Select crossover point based on the band-overlap of the specified drivers: " << endl;
    lowpass.xover1 =  tweet->Freq_Low + (drvr->Freq_Hi - tweet->Freq_Low)/2;

    cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Tweet: " << lowpass.xover1 << endl;
    cout << "+---------------------------+" << endl;

    highpass.xover1 = lowpass.xover1;
    cout << "High-pass Crossover frequency: " << highpass.xover1 << endl;

    cout << "Enter the order of this filter (2 = 2nd Order, 3 = 3rd order) Default is 1, Max stages is 3." << endl;
    cin >> lowpass.stages;
    
    /*------------------------------*/
    /* Compute low-pass values here */
    /*------------------------------*/
    cout << endl << "Capacitance : (F) " ;
    cin >> C1;
    C1 = C1 * 1e-09;
   
    R1 = 1 / (C1 * lowpass.xover1 * 2 * M_PI);
    
    for (i = 1; i <= lowpass.stages; i++) {
        if (i == 1) {
            lowpass.C1 = C1;
            lowpass.R1 = R1;
        }

        if (i == 2) {
            lowpass.C2 = C1;
            lowpass.R2 = R1;
        }

        if (i == 3) {
            lowpass.C3 = C1;
            lowpass.R3 = R1;
        }
    }
    
    /*-------------------------------*/
    /* Compute high-pass values here */
    /*-------------------------------*/

    /* use same capacitance value for all filter values, compute resistance */
    C2 = lowpass.C1;

    highpass.stages = lowpass.stages;
    
    R2 = 1 / (C2 * highpass.xover1 * 2 * M_PI);
    
    for (i = 1; i <= highpass.stages; i++) {
        if (i == 1) {
            highpass.C1 = C2;
            highpass.R1 = R2;
        }

        if (i == 2) {
            highpass.C2 = C2;
            highpass.R2 = R2;
        }

        if (i == 3) {
            highpass.C3 = C2;
            highpass.R3 = R2;
        }

    }
    
    lowpass.gain = (pow(1/(sqrt(2)), lowpass.stages));
    highpass.gain = (pow(1/(sqrt(2)), highpass.stages));
    
    lowpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1);
    highpass.f3db1 = highpass.xover1 * sqrt((pow(2, 1/highpass.stages)) - 1);
    
    /* Review design values here */

    cout << "-----------------------------------------" << endl;
    cout << " Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Order             : " << lowpass.stages << endl;
    cout << " Low-Pass Frequency (Hz)  : " << lowpass.xover1 << endl;
    cout << " Low-Pass gain (< 1)      : " << lowpass.gain << endl;
    cout << " Low-Pass 3db freq  (Hz)  : " << lowpass.f3db1<< endl;
    cout << " Low-Pass Capacitance     : " << lowpass.C1 << endl;
    cout << " Low-Pass Resistance      : " << lowpass.R1 << endl;
    cout << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    cout << " High-Pass Frequency (Hz) : " << highpass.xover1 << endl;
    cout << " High-Pass 3db freq  (Hz) : " << highpass.f3db1<< endl;
    cout << " High-Pass Capacitance    : " << highpass.C1 << endl;
    cout << " High-Pass Resistance     : " << highpass.R1 << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void passive_three_way(Speaker* drvr, Speaker* mid, Speaker* tweet, Filter& lowpass, Filter& bandpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (resistance) and the desired crossover    */
/* points for the speaker. The function will then compute the values of a 1st order crossover.*/
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/*--------------------------------------------------------------------------------------------*/
{
    char xovr[8];             /* response to modify high pass cut-off frequency. */
    char mdle[8];             /* response to modify band pass cut-off frequency. */
    char loop[8];             /* control parameter to determine correctness of solution.  */

    double res_freq;           /* resonant frequency of the bandpass filter */

    double gain;               /* Gain at cut-off frequency for filter. */
    double xover;              /* Cross-ver or frequency cut-off for filter(s) - high/low pass */
    double f3db1, f3bd_2;      /* -3db cut-off frequency for 3-way speaker. */

    double C1, C2, C3; /* User defined value for capacitance for filter cut-off */
    double R1, R2, R3; /* Computed resistance for given capacitance and crossover frequency. */

    int co_1, co_2;   /* crossover point. */
    int i;            /* Counter value for storing the values in the number of N-order stages.*/
    int stages;       /* Number of stages used to determine the order of the filter. */
                      /* Default is 1 (1st order Butterworth Filter). */

                              
    cout << "This is a 1st order crossover for 3 driver speaker. " << endl;
    lowpass.xover_type = "Passive";
    bandpass.xover_type = "Passive";
    highpass.xover_type = "Passive";

    string low_parse = "";    /* The following strings are used to store the parsed data from */
    string mid_parse = "";    /* the speaker node passed in to display the part and frequency */
    string high_parse = "";   /* band-width.                                                  */
    

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(mid, mid_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

    cout << "===============================================================================" << endl;
    cout << "Select crossover point based on the band-overlap of the specified drivers: " << endl;
    lowpass.xover1 = drvr->Freq_Low;
    lowpass.xover2 =  mid->Freq_Low + (drvr->Freq_Hi - mid->Freq_Low)/2;
    bandpass.xover1 = lowpass.xover2;
    bandpass.xover2 =  tweet->Freq_Low + (mid->Freq_Hi - tweet->Freq_Low)/2;
    highpass.xover1 = bandpass.xover2;
    highpass.xover2 = tweet->Freq_Hi;
    bandpass.Fres = sqrt(bandpass.xover1 * bandpass.xover2);

    cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Midrange     (Hz) : " << bandpass.xover1 << endl;
    cout << "  Midrange/Treble   (Hz) : " << bandpass.xover2 << endl;
    cout << "  Resonant Fequency (Hz) : " << bandpass.Fres << endl;
    cout << "+---------------------------+" << endl;

    cout << "Enter the order of this filter (2 = 2nd Order, 3 = 3rd order) Default is 1, Max stages is 3." << endl;
    cin >> lowpass.stages;
  
    /*------------------------------*/
    /* Compute low-pass values here */
    /*------------------------------*/
    cout << endl << "Capacitance : (F) " ;
    cin >> C1;
    lowpass.C1 = C1 * 1e-09;       /* The capcitance for the filters are identical, but the   */
    lowpass.C2 = lowpass.C1;       /* resistance will change based on the corner frequencies. */
    lowpass.xover1 = drvr->Freq_Low;
    
    // Low-Pass filter computation
    lowpass.R1 = 1/(2 * M_PI * lowpass.C1 * lowpass.xover1);
    
    /*------------------------------*/
    /* Compute Band-pass values hew */
    /*------------------------------*/
    bandpass.C1 = lowpass.C1;
    bandpass.C2 = lowpass.C1;
    bandpass.R2 = 1/(2 * M_PI * bandpass.C2 * bandpass.xover2);
    
    /*------------------------------*/
    /* Compute High-pass values hew */
    /*------------------------------*/
    highpass.C1 = bandpass.C2;
    highpass.R1 = bandpass.R2;
    
    /*------------------------------*/
    /* Gain/Bandwidth measurements  */
    /*------------------------------*/
    lowpass.gain = (pow(1/(sqrt(2)), lowpass.stages));
    bandpass.gain = (pow(1/(sqrt(2)), bandpass.stages));
    highpass.gain = (pow(1/(sqrt(2)), highpass.stages));

    lowpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    bandpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    bandpass.f3db2 = lowpass.xover2 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    highpass.f3db1 = highpass.xover1 * sqrt((pow(2, 1/highpass.stages)) - 1); 

    cout << "-----------------------------------------" << endl;
    cout << " Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Order               : " << lowpass.stages << endl;
    cout << " Low-Pass Frequency         : " << lowpass.xover1 << endl;
    cout << " Low-Pass gain (< 1)        : " << lowpass.gain << endl;
    cout << " Low-Pass 3db freq (Hz)     : " << lowpass.f3db1<< endl;
    cout << " Low-Pass Capacitance/C1    : " << lowpass.C1 << endl;
    cout << " Low-Pass Resistance/R1     : " << lowpass.R1 << endl;
    cout << " Band-Pass Frequency   (Hz) : " << bandpass.xover1 << endl;
    cout << " Band-Pass gain (< 1)       : " << bandpass.gain << endl;
    cout << " Band-Pass 3db(l) freq (Hz) : " << bandpass.f3db1<< endl;
    cout << " Band-Pass 3db(h) freq (Hz) : " << bandpass.f3db2<< endl;
    cout << " Band-Pass Capacitance/C1   : " << bandpass.C1 << endl;
    cout << " Band-Pass Capacitance/C2   : " << bandpass.C2 << endl;
    cout << " Band-Pass Resistance/R1    : " << bandpass.R1 << endl;
    cout << " Band-Pass Resistance/R2    : " << bandpass.R2 << endl;
    cout << " High-Pass gain (< 1)       : " << highpass.gain << endl;
    cout << " High-Pass Frequency   (Hz) : " << highpass.xover1 << endl;
    cout << " High-Pass 3db freq    (Hz) : " << highpass.f3db1<< endl;
    cout << " High-Pass Capacitance      : " << highpass.C1 << endl;
    cout << " High-Pass Resistance       : " << highpass.R1 << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void active_two_way(Speaker* drvr, Speaker* tweet, Filter& lowpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (capcitance) and the desired crossover    */
/* point for the speaker. The function will then compute the values of a 1st order crossover. */
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/* Because this is an active filter design, the opamp utilized will have a feedback path that */
/* is comprised of two resistive elements (R1/R2) that need to be defined such that the       */
/* overall gain is: A(gain) = 1 + (R2/R1) where R2/R1 -> 0.                                   */
/*--------------------------------------------------------------------------------------------*/
{
    char xovr[8];     /* response to modify high pass cut-off frequency. */
    char loop[8];     /* control parameter to determine correctness of solution. */

    double res_freq;   /* resonant frequency of the bandpass filter */
    double gain;       /* Gain at cut-off frequency for filter. */
    double xover;      /* Cross-ver or frequency cut-off for filter(s)  - high/low pass */
    double f3db1;      /* -3db cut-off frequency for 2-way speaker. */

    double C1, C2;     /* User defined value for capacitance for filter cut-off */
    double R1, R2;     /* Computed resistance for given capacitance and crossover frequency. */
    double R3, R4;

    int i;            /* Counter value for storing the values in the number of cascading stages. */
    int stages;       /* Number of stages used to determine the order of the filter.             */
                      /* Default is 1 (1st order Butterworth Filter).                            */

    string low_parse = "";    /* The following strings are used to store the parsed data from    */
    string high_parse = "";   /* the speaker node passed in to display the part and frequency    */
                              /* band-width.                                                     */
                              
    cout << "This is a Butterworth passive crossover for 2 driver speaker. " << endl;
    lowpass.xover_type = "Active";
    highpass.xover_type = "Active";

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

    cout << "===============================================================================" << endl;
    cout << "Select crossover point based on the band-overlap of the specified drivers: " << endl;
    lowpass.xover1 =  tweet->Freq_Low + (drvr->Freq_Hi - tweet->Freq_Low)/2;

    cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Tweet: " << lowpass.xover1 << endl;
    cout << "+---------------------------+" << endl;

    highpass.xover1 = lowpass.xover1;
    cout << "High-pass Crossover frequency: " << highpass.xover1 << endl;

    cout << "Enter the order of this filter (1 = 1st Order, 2 = 2nd Order) Default is 1, Max stages is 2." << endl;
    cin >> lowpass.stages;
  
    
    /*------------------------------*/
    /* Compute low-pass values here */
    /*------------------------------*/
    cout << endl << "Capacitance : (F) " ;
    cin >> C1;
    C1 = C1 * 1e-09;

    lowpass.gain = 1 + (feedback_1/feedback_2);
    lowpass.FB_R1 = feedback_1;
    lowpass.FB_R2 = feedback_2;
   
    R1 = 1 / (C1 * lowpass.xover1 * 2 * M_PI);
    
    for (i = 1; i <= lowpass.stages; i++) {
        if (i == 1) {
            lowpass.C1 = C1;
            lowpass.R1 = R1;
        }

        if (i == 2) {
            lowpass.C2 = C1;
            lowpass.R2 = R1;
        }

        if (i == 3) {
            lowpass.C3 = C1;
            lowpass.R3 = R1;
        }
    }

    /*-------------------------------*/
    /* Compute high-pass values here */
    /*-------------------------------*/

    /* use same capacitance value for all filter values, compute resistance */
    C2 = lowpass.C1;

    highpass.stages = lowpass.stages;
    highpass.gain = 1 + (feedback_1/feedback_2);
    highpass.FB_R1 = feedback_1;
    highpass.FB_R2 = feedback_2;
    
    R2 = 1 / (C2 * highpass.xover1 * 2 * M_PI);
    
    for (i = 1; i <= highpass.stages; i++) {
        if (i == 1) {
            highpass.C1 = C2;
            highpass.R1 = R2;
        }

        if (i == 2) {
            highpass.C2 = C2;
            highpass.R2 = R2;
        }

        if (i == 3) {
            highpass.C3 = C2;
            highpass.R3 = R2;
        }
    }
    
    lowpass.gain = (pow(1/(sqrt(2)), lowpass.stages));
    highpass.gain = (pow(1/(sqrt(2)), highpass.stages));
    
    lowpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1);
    highpass.f3db1 = highpass.xover1 * sqrt((pow(2, 1/highpass.stages)) - 1);
    
    /* Review design values here */

    cout << "-----------------------------------------" << endl;
    cout << " Active Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Order (generic)  : " << lowpass.stages << endl;
    cout << " Low-Pass gain           : " << lowpass.gain << endl;
    cout << " High-Pass gain          : " << highpass.gain << endl;

    cout << " Low-pass Feedback R1    : " << lowpass.FB_R1 << endl;
    cout << " Low-pass Feedback R2    : " << lowpass.FB_R2 << endl;
    cout << " Low-Pass Frequency  (Hz): " << lowpass.xover1 << endl;
    cout << " Low-Pass 3db freq   (Hz): " << lowpass.f3db1<< endl;
    cout << " Low-Pass Capacitance    : " << lowpass.C1 << endl;
    cout << " Low-Pass Resistance     : " << lowpass.R1 << endl;
    cout << "                           " << endl;
    cout << " High-pass Feedback R1   : " << lowpass.FB_R1 << endl;
    cout << " High-pass Feedback R2   : " << lowpass.FB_R2 << endl;
    cout << " High-Pass Frequency (Hz): " << highpass.xover1 << endl;
    cout << " High-Pass 3db freq  (Hz): " << highpass.f3db1<< endl;
    cout << " High-Pass Capacitance   : " << highpass.C1 << endl;
    cout << " High-Pass Resistance    : " << highpass.R1 << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void active_three_way(Speaker* drvr, Speaker* mid, Speaker* tweet, Filter& lowpass, Filter& bandpass, Filter& highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function prompts the user for a fixed value (capcitance) and the desired crossover    */
/* point for the speaker. The function will then compute the values of a 1st order crossover. */
/* (future feature) - a 2nd order filter design is a forth coming feature.                    */
/* Because this is an active filter design, the opamp utilized will have a feedback path that */
/* is comprised of two resistive elements (R1/R2) that need to be defined such that the       */
/* overall gain is: A(gain) = 1 + (R2/R1) where R2/R1 -> 0.                                   */
/*--------------------------------------------------------------------------------------------*/
{
    char xovr[8];             /* response to modify high pass cut-off frequency. */
    char mdle[8];             /* response to modify band pass cut-off frequency. */
    char loop[8];             /* control parameter to determine correctness of solution. */

    double res_freq;           /* resonant frequency of the bandpass filter */

    double gain;               /* Gain at cut-off frequency for filter. */
    double xover;              /* Cross-ver or frequency cut-off for filter(s) - high/low pass */
    double f3db1, f3bd_2;      /* -3db cut-off frequency for 3-way speaker. */

    double C1, C2, C3; /* User defined value for capacitance for filter cut-off                */
    double R1, R2, R3; /* Computed resistance for given capacitance and crossover frequency.   */

    int co_1, co_2;   /* crossover point. */
    int i;            /* Counter value for storing the values in the number of N-order stages.*/
    int stages;       /* Number of stages used to determine the order of the filter.          */
                      /* Default is 1 (1st order Butterworth Filter).                         */

                              
    cout << "This is a 1st order crossover for 3 driver speaker. " << endl;
    lowpass.xover_type = "Active";
    bandpass.xover_type = "Active";
    highpass.xover_type = "Active";

    string low_parse = "";    /* The following strings are used to store the parsed data from */
    string mid_parse = "";    /* the speaker node passed in to display the part and frequency */
    string high_parse = "";   /* band-width.                                                  */
    

    /* the values below are constants and are used to set the display table */
    /* used to display cnd ompare freq ranges.                              */

    cout << HDR << endl;
    cout << TOWAY << endl;
    cout << HDR << endl;
    data_field(drvr, low_parse);
    data_field(mid, mid_parse);
    data_field(tweet, high_parse);
    cout << HDR << endl;

    cout << "===============================================================================" << endl;
    cout << "Select crossover point based on the band-overlap of the specified drivers: " << endl;
    lowpass.xover1 = drvr->Freq_Low;
    lowpass.xover2 =  mid->Freq_Low + (drvr->Freq_Hi - mid->Freq_Low)/2;
    bandpass.xover1 = lowpass.xover2;
    bandpass.xover2 =  tweet->Freq_Low + (mid->Freq_Hi - tweet->Freq_Low)/2;
    highpass.xover1 = bandpass.xover2;
    highpass.xover2 = tweet->Freq_Hi;
    bandpass.Fres = sqrt(bandpass.xover1 * bandpass.xover2);

    cout << "+-----------------------------+" << endl;
    cout << "| Suggested Cross Over Points |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "  Bass/Midrange (Hz)     : " << bandpass.xover1 << endl;
    cout << "  Midrange/Treble (Hz)   : " << bandpass.xover2 << endl;
    cout << "  Resonant Fequency (Hz) : " << bandpass.Fres << endl;
    cout << "+---------------------------+" << endl;

    //cout << "Enter the order of this filter (2 = 2nd Order, 3 = 3rd order) Default is 1, Max stages is 3." << endl;
    //cin >> lowpass.stages;
    lowpass.stages = 2;
    highpass.stages = lowpass.stages;
  
    /*------------------------------*/
    /* Compute low-pass values here */
    /*------------------------------*/
    cout << endl << "Capacitance : (F) " ;
    cin >> C1;

    bandpass.gain = 1 + (feedback_1/feedback_2);
    bandpass.FB_R1 = feedback_1;
    bandpass.FB_R2 = feedback_2;
    lowpass.C1 = C1 * 1e-09;       /* The capcitance for the filters are identical, but the   */
    lowpass.C2 = lowpass.C1;       /* resistance will change based on the corner frequencies. */
    lowpass.xover1 = drvr->Freq_Low;
    
    // Low-Pass filter computation
    lowpass.R1 = 1/(2 * M_PI * lowpass.C1 * lowpass.xover1);
    
    /*------------------------------*/
    /* Compute Band-pass values hew */
    /*------------------------------*/
    bandpass.C1 = lowpass.C1;
    bandpass.C2 = lowpass.C1;
    bandpass.R1 = lowpass.R1;
    bandpass.R2 = 1/(2 * M_PI * bandpass.C2 * bandpass.xover2);
    
    /*------------------------------*/
    /* Compute High-pass values hew */
    /*------------------------------*/
    highpass.C1 = bandpass.C2;
    highpass.R1 = bandpass.R2;
    
    /*------------------------------*/
    /* Gain/Bandwidth measurements  */
    /*------------------------------*/
    lowpass.gain = (pow(1/(sqrt(2)), lowpass.stages));
    bandpass.gain = (pow(1/(sqrt(2)), bandpass.stages));
    highpass.gain = (pow(1/(sqrt(2)), highpass.stages));

    lowpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    bandpass.f3db1 = lowpass.xover1 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    bandpass.f3db2 = lowpass.xover2 * sqrt((pow(2, 1/lowpass.stages)) - 1); 
    highpass.f3db1 = highpass.xover1 * sqrt((pow(2, 1/highpass.stages)) - 1); 

    cout << "-----------------------------------------" << endl;
    cout << " Filter Values " << endl;
    cout << "-----------------------------------------" << endl;
    cout << " Filter Order            : " << lowpass.stages << endl;
    cout << " Low-Pass gain (< 1)     : " << lowpass.gain << endl;
    cout << " Band-Pass gain (< 1)    : " << bandpass.gain << endl;
    cout << " High-Pass gain (< 1)    : " << highpass.gain << endl;
    cout << "                           " << endl;
    cout << " Low-Pass Frequency      : " << lowpass.xover1 << endl;
    cout << " Low-Pass 3db freq       : " << lowpass.f3db1 << endl;
    cout << " Low-Pass Capacitance/C1 : " << lowpass.C1 << endl;
    cout << " Low-Pass Resistance/R1  : " << lowpass.R1 << endl;
    cout << "                           " << endl;
    cout << " Band-pass Feedback R1   : " << bandpass.FB_R1 << endl;
    cout << " Band-pass Feedback R2   : " << bandpass.FB_R2 << endl;
    cout << " Band-Pass Frequency     : " << bandpass.xover1 << endl;
    cout << " Band-Pass 3db(l) freq   : " << bandpass.f3db1 << endl;
    cout << " Band-Pass 3db(h) freq   : " << bandpass.f3db2 << endl;
    cout << " Band-Pass Capacitance/C1: " << bandpass.C1 << endl;
    cout << " Band-Pass Capacitance/C2: " << bandpass.C2 << endl;
    cout << " Band-Pass Resistance/R1 : " << bandpass.R1 << endl;
    cout << " Band-Pass Resistance/R2 : " << bandpass.R2 << endl;
    cout << "                           " << endl;
    cout << " High-Pass Frequency     : " << highpass.xover1 << endl;
    cout << " High-Pass 3db freq      : " << highpass.f3db1 << endl;
    cout << " High-Pass Capacitance   : " << highpass.C1 << endl;
    cout << " High-Pass Resistance    : " << highpass.R1 << endl;
    cout << "-----------------------------------------" << endl;

    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void design_low_sealed(Speaker*& drvr, Cabinet*& cptr, double& Vd)
/*--------------------------------------------------------------------------------------------*/
/* this procedure will design a closed box system, and refactors code pulled in from the      */
/* closed_box_design() procedure call. This procedure works on the bass and midr speaker      */
/* drivers.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

	//struct Cabinet *bptr, *cptr;
	struct Cabinet *bptr;

    cptr=(struct Cabinet *)malloc(sizeof(struct Cabinet));

	char fill[4];
    char l_cmd[8];
    char d_cmd[8];

    double Qa;                     // These two *values* are used to determine the 'filling'
    double gamma;                  // constants for a closed-box design. Qa = 10/5 - lambda = 1/1.2
	
	/* intermediate internal values */
    double alpha;                   // ratio of Driver compliance vs enclosure volume (Vol_vent)
    double A1;
    double f3;
    double fc;                      // Resonance frequency of a closed box system
    double Fsb;                     // Driver resonance freq mounted in enclosure
    double L;
    double peak;
    double Par, Per;                // Displacement limited power ratings
    double Qtc, Qtcp;               // Q factor values used for closed-box measurements
	double Rh;                      // 3db ripple
    double Vab;                     // box volume derived from compliance (Vas) and alpha/gamma
    double Vbs;                     // Temporary value of box volume derived from Vol_seal

    int bdesign;                    // Value entered for switch statement choosing deign flow
	int empty_val;                  // value used to checking for missing values.
	int flag;

    std::string cab_type;

	flag = 0;

    cout << "Test procedure design_low()" << endl;

	if ((ptr->f3_seal <= 0) || (ptr->Vbs <= 0)) {
        empty_val = 2;
    }

    while (!flag) {
        cout << "Use acoustic filling - Y/N? :";
        cin >> fill;

        if ((strcmp(fill, "Y") == 0) || (strcmp(fill, "y") == 0)) {
            gamma = 1.0;
            Qa = 10.0;
        } else {
            gamma = 1.2;
            Qa = 5.0;
        }

        cout << "Choose design based on:" << endl;
        cout << "    1) default speaker values" << endl;
        cout << "    2) box volume" << endl;
        cout << "    3) Enter Q(tc)" << endl;
        cout << "    4) Use default value of Q(tc) = 1" << endl;
        cout << "-------------------------------------" << endl;
        cin >> bdesign;

        switch (bdesign) {
            case 1:
                cout << "Choose design based on default values : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per, Rh, Vd);
                break;
            case 2:
                cout << "Choose design based on box volume : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per, Rh, Vd);
                break;
            case 3:
		Qtc = 0.0;
                cout << "Choose design based on user specified value of Q(tc) : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per, Rh, Vd);
                break;
            default:
                cout << "Choose design based on default value of Q(tc) to 0.707" << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per, Rh, Vd);
                break;
	    }

        cout << "+-------------------------------------------+" << endl;
        cout << "| Intermediate values for sealed box design |" << endl;
        cout << "+-------------------------------------------+" << endl;
        cout << " Acoustic Filling (Y/N)        : " << fill << endl;
	    cout << " Part Number                   : " << ptr->Part_num << endl;
        cout << " Driver compliance (Vas)       : " << ptr->Vas << endl;
        cout << " Box Volume (dm^3)             : " << Vbs << endl;
        cout << " Cabinet Volume derived (Vab)  : " << Vab << endl;
        cout << " Volume ratio (alpha)          : " << alpha << endl;
        cout << " Filling value (gamma)         : " << gamma << endl;
        cout << " Filling value (Qa)            : " << Qa << endl;
        cout << " Driver Q (Qtc)                : " << Qtc << endl;
        cout << " Derived Driver Q (Qtcp)       : " << Qtcp << endl;
        cout << " Resonance Frequncy Fc         : " << Fsb << endl;
        cout << " free-air resonance Fs         : " << ptr->Fs << endl;
        cout << " Q driver ratio L              : " << L << endl;
        cout << " 3db down response f3 (Hz)     : " << f3 << endl;
        cout << " Peak db                       : " << peak << endl;
        cout << " Power Efficiency              : " << Per << " % " << endl;
        cout << " Electrical Power              : " << Par << " W " << endl;
	    cout << " Estimated 3db ripple          : " << Rh << endl;
        cout << "--------------------------------------------" << endl;

        strcpy(cptr->Part_num, ptr->Part_num);
	    strcpy(cptr->Build, ptr->Build);
	    strcpy(cptr->Enclosure, "Sealed");
        cptr->cab_volume = Vbs;
        cptr->freq_lo = ptr->Freq_Low;
        cptr->freq_hi = ptr->Freq_Hi;
        cptr->Sensitivity = ptr->Sensitivity;
        cptr->res_freq = Fsb;
        cptr->rolloff = f3;
        cptr->imp_Nom = ptr->Z_nom;
        cptr->diam = drvr->b_diam;
        cptr->height = drvr->b_height;
        cptr->depth = drvr->depth;
        cptr->vent_diam = 0;
        cptr->vent_length = 0;
        cptr->PAR = Par;
        cptr->PER = Per;
	    cptr->Rh = Rh;
        cptr->next = NULL;

        bptr = cptr;
    
        sleep(5);

        cout << "Accept results (Y/y)? :" << endl;
        cin >> l_cmd;

        if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
                cout << "Speaker Design completed..." << endl;
                flag = 1;
        } else {
                cout << "compute closed box design..." << endl;
        }

        sleep(5);
	}

    // reuse the flag value and reset to 0
    flag = 0;

    while (!flag) {
        cout << "define cabinet dimensions..." << endl;
        cab_type = "closed";
        cabinet_design(drvr, cptr, "sealed", drvr->Type);
        // make sure to set flag to true
        flag = 1;
    }
}
/*--------------------------------------------------------------------------------------------*/
void design_low_vented(Speaker*& drvr, Cabinet*& box, double& Vd)
/*--------------------------------------------------------------------------------------------*/
/* this procedure will design a closed box system, and refactors code pulled in from the      */
/* closed_box_design() procedure call. This procedure works on the bass and midr speaker      */
/* drivers.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

	struct Cabinet *temp, *bptr;
	bptr = box;

    temp=(struct Cabinet *)malloc(sizeof(struct Cabinet));

    char l_cmd[8];
    char d_cmd[8];
	
    double Qa;                     // These two *values* are used to determine the 'filling'
    double gamma;                  // constants for a closed-box design. Qa = 10/5 - lambda = 1/1.2

    double a, b, c, d, e, f;       // value holders for frequency response measurement
    double alpha;                  // ratio of Driver compliance vs enclosure volume (Vol_vent)
    double Vba;                    // Enclosure multiplier
	double Ap;                     // Cross-sectional area of the port (mm)
    double Dv, Lv, L_prm;          // Vent diameter, length in mm
    double f3v;                    // frequency rolloff
    double Fsb;                    // Driver resonance freq mounted in enclosure
    double Fb;                     // Enclosure resonance requency - not to be confused with Fsb
    double Fn;                     // Normalized frequency ratio - f(req)/Fsb
	double Fpk;                    // Frequency peak as determined using T/S values.
    double Lp;                     // Length of the port
	double Mb, Mp;                 // Acoustic mass pf the box and port, respectively;
    double Ppt;                    // Acoustic Power radiated by the Port
	double Pttl;                   // Total Acoustic Power
    double Par, Per;               // Displacement limited power ratings
	double Pd;                     // Pressure change factor - user input from 0.15 to 0.25
	double Qb;                     // Box damping factor;
	double Rb, Re, Rp, Rd;         // Acoustic resistance Rb includes empty, port, damping msterial)
    double Rh;                     // Ripple response (in db)
    double Vbv;                    // Computed volume of cabinet - liters || dm^3
	double Vpt;                    // Peak port volume velocity
	double Apt;                    // Port cross-sectional area
	double Vpk;                    // Peak Air Velocity

    int bdesign;                   // Value entered for switch statement choosing deign flow
    int empty_val;                 // value used to checking for missing values.
    int flag;
    int vflag;                     // Initially set to '0', but one the user makes a first pass
                                   // through the design process, then the flag will be toggled
                                   // to '1'. The flag will be reset to '0' upon exit.


    /* REFACTOR PROCEDURE TO CORRECT VENTED VALUES */

    std::string cab_type;

    flag = 0;

	Vbv = ptr->Vbv;

	while (!flag) {
        cout << "Choose design based on:" << endl;
        cout << "    1) Standard Bass Reflex - Balanced  system response" << endl;
        cout << "    2) Quasi-Butterworth - Flat response/Low effeiciency" << endl;
        cout << "    3) Extended Bass Shelf - " << endl;
        cout << "-------------------------------------" << endl;
        cin >> bdesign;

		switch(bdesign) {
		    case 1:
			    cout << "Create a speaker profile using a flat alignment..." << endl;
				cout << "Flat-alignment is based on the manufacturers Thiele/Small speicifications." << endl;

				// Compute parameters here
				Vbv = 20 * (ptr->Vas)/pow(ptr->Qts, 2);

				// Compute tuning frequency (Fb)
				Fb = 0.42 * ptr->Fs/ptr->Qts;

				//--------------------------------------------------------
				// Design the box port
				a = 23562.5 * pow(ptr->v_diam, 2);
				b = Vbv * pow(Fb, 2);

				Pd = 0;
				vflag = 0;

				while (!vflag) {
				    cout << "Specify Air Pressure delta value ( 0.15 to 0.25) - " << endl;
				    cout << "Pd = ";
				    cin >> Pd;

					if ((Pd >= 0.15) && (Pd <= 0.25)) {
					     vflag = 1;
				    }
				}

				sleep(5);
				break;

		    case 2:
			    cout << "Quasi-Butterworth alignment..." << endl;
				cout << "Flatter response but lower efficiency." << endl;

				// Compute parameters here
                a = 20 * ptr->Vas * pow(ptr->Qts, 3);
                b = pow(1 + ptr->Qts, 2);
				Vbv = a/b;

                // Tuning frequency
				Fb = 0.8 * ptr->Fs;

				//--------------------------------------------------------
				// Design the box port
				a = 23562.5 * pow(ptr->v_diam, 2);
				b = Vbv * pow(Fb, 2);

				Pd = 0;
				vflag = 0;

				while (!vflag) {
				    cout << "Specify Air Pressure Delta value ( 0.15 to 0.25) - " << endl;
				    cout << "Pd = ";
				    cin >> Pd;

					if ((Pd >= 0.15) && (Pd <= 0.25)) {
					     vflag = 1;
				    }
				}

		    case 3:
			    cout << "Extended Bass Shelf" << endl;
				cout << "Maximizes low-frequency extension at the expense of flatness." << endl;

				Vba = 0;

				vflag = 0;

				while (!vflag) {
				    cout << "Specify the box-volume muliplier(Vba) [ 1.5 to 2.0] - " << endl;
				    cout << "Vba = ";
				    cin >> Vba;

					if ((Vba >= 1.5) && (Vba <= 2.0)) {
					     vflag = 1;
				    }
				}

				Vbv = Vba * ptr->Vas;

                // Tuning frequency
				Fb = 0.7 * ptr->Fs;

				//--------------------------------------------------------
				// Design the box port
				a = 23562.5 * pow(ptr->v_diam, 2);
				b = Vbv * Fb;

				Pd = 0;
				vflag = 0;

				while (!vflag) {
				    cout << "Specify Air Pressure Delta value ( 0.15 to 0.25) - " << endl;
				    cout << "Pd = ";
				    cin >> Pd;

					if ((Pd >= 0.15) && (Pd <= 0.25)) {
					     vflag = 1;
				    }
				}

			default :
				cout << "Invalid selection. Please choose from one of the 3 options." << endl;
				break;
		}

		// Compute PAR/PER here
		Ap = (Vbv * Fb)/(C * Pd);
		Dv = 2 * sqrt(Ap/M_PI);

		Lp = a/b - (0.732 * Dv);

		// Convert cm to mm as spec sheets are in mm

		Lp = Lp * cm_to_mm;

		alpha = Vbv/ptr->Vas;
		Fpk = Fb * sqrt((1 + alpha)/alpha);

		// Port Air Velocity (PAR)
		Vpt = M_PI * pow(ptr->Diam, 2) * ptr->Xmax * Fpk;
		Apt = M_PI * pow((Dv/2), 2);
		Vpk = Vpt/Apt;

		// Normalize to Speed of Sound
		Par = Vpk/C;

		// Port Efficiency Ratio (PER)
        Ppt = (rho * pow(Vpk, 2) * Apt)/2;

		a = rho * M_PI * pow(Fpk, 2);
		b = pow((ptr->Diam/2), 2);

		Pttl = a * b * pow(ptr->Xmax, 2);
		Per = Ppt/Pttl;

		// Compute frequency response here
	    //double Rb, Re, Rp, Rd;         
		// Acoustic resistance Rb includes empty, port, damping msterial)
		// Convert liters to m^3
		Me = (rho * Vbv)/pow(C, 2);
		Mp = (rho * C)/*Lp * Ap);
		Md = 
		
		// Mass of air port (vent)
		Mb = rho * (Lp/Ap);
		Mv = rho * (

		//vented_freq_params(drvr, Vbv, Fsb, Fb, Fn, Vd, L_prm, a, b, c, d, alpha);

		// Compute ripple here

		cout << "Accept results? (Y/N) " << endl;
		cin >> l_cmd;

		if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
		    flag = 1;
		}
	}
}
/*--------------------------------------------------------------------------------------------*/
void design_tweeter_sealed(Speaker*& drvr, Cabinet*& cptr, double& Vd)
/* this procedure will design a closed box system, and refactors code pulled in from the      */
/* closed_box_design() procedure call. This procedure works on the treble speaker driver only.*/
/* drivers.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;
	
	struct Cabinet *bptr;

	bptr = (struct Cabinet *)malloc(sizeof(struct Cabinet));

	double peakSPL;
	double PAR;
	double PER;

	//tptr = box;

    cout << "Test procedure design_tweeter()" << endl;
	
	/* Calculate power efficency and value ratings */
	peakSPL = (ptr->Sensitivity) + 10 * log10(ptr->Max_Pwr);
	PER = (10 * ((ptr->Sensitivity - 112)/10))/100;
	PAR = 10 * ((ptr->Sensitivity - 112)/10);

    cout << "+-------------------------------------------+" << endl;
    cout << "| Intermediate values for sealed box design |" << endl;
    cout << "+-------------------------------------------+" << endl;
    cout << " Part Number                   : " << ptr->Part_num << endl;
    cout << " Driver compliance (Vas)       : " << ptr->Vas << endl;
    cout << " free-air resonance Fs         : " << ptr->Fs << endl;
    cout << " 3db down response f3 (Hz)     : " << ptr->f3_seal  << endl;
    cout << " Peak db                       : " << peakSPL << endl;
	cout << " Low Freq                      : " << ptr->Freq_Low << endl;
	cout << " High Freq                     : " << ptr->Freq_Hi << endl;
	cout << " Nominal Impedance             : " << ptr->Z_nom << endl;
    cout << " Power Efficiency              : " << PER << " % " << endl;
    cout << " Electrical Power              : " << PAR << " W " << endl;
	cout << " Speaker Height                : " << ptr->b_height << endl;
	cout << " Speaker Width                 : " << ptr->b_diam << endl;
	cout << " Speaker Depth                 : " << ptr->depth << endl;
    cout << "--------------------------------------------" << endl;

	sleep(5);
	
	strcpy(bptr->Part_num, ptr->Part_num);
	strcpy(bptr->Build, ptr->Build);
	strcpy(bptr->Enclosure, "Sealed");
	bptr->freq_lo = ptr->Freq_Low;
    bptr->freq_hi = ptr->Freq_Hi;
    bptr->Sensitivity = ptr->Sensitivity;
    bptr->res_freq = ptr->Fs;
    bptr->rolloff = ptr->f3_seal;
    bptr->imp_Nom = ptr->Z_nom;
	bptr->diam = drvr->b_diam;
	bptr->height = ptr->b_height;
	bptr->depth = ptr->depth;
	bptr->H = ptr->b_height;
	bptr->W = ptr->b_diam;
	bptr->D = ptr->depth;
	bptr->next = NULL;

	cptr = bptr;

    cout << "+--------------------------------+" << endl;
    cout << "| Intermediate box design values |" << endl;
    cout << "+--------------------------------+" << endl;
	cout << "Debug - tweeter values " << endl;
	cout << "Part Number : " << cptr->Part_num << endl;
	cout << "Enclosure   : " << cptr->Enclosure << endl;
	cout << "Build       : " << cptr->Build << endl;
	cout << "Freq_Low    : " << cptr->freq_lo << endl;
	cout << "Freq_Hi     : " << cptr->freq_hi << endl;
	cout << "Sensitivity : " << cptr->Sensitivity << endl;
	cout << "Diameter    : " << cptr->diam << endl;
	cout << "Height      : " << cptr->height << endl;
	cout << "Depth       : " << cptr->depth << endl;
	cout << "Cab Height  : " << cptr->H << endl;
	cout << "Cab Width   : " << cptr->W << endl;
	cout << "Cab Depth   : " << cptr->D << endl;
	cout << "Cab Volume  : " << cptr->cab_volume << endl;
    cout << "+--------------------------------+" << endl;

	sleep(2);

	tweeter_cabinet_design(drvr, cptr);
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
void write_filter_data(Filter low, Filter band, Filter high, int xover, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document.         */
/*--------------------------------------------------------------------------------------------*/
{
    if (xover == 0) {
	    return;
    } else if (xover == 1) {
	    print_crossover(low, outfile);
	    print_crossover(high, outfile);
	} else if (xover == 2) {
	    print_crossover(low, outfile);
	    print_crossover(band, outfile);
	    print_crossover(high, outfile);
    }
}
/*--------------------------------------------------------------------------------------------*/
void print_crossover(Filter crossover, std::ofstream& outfile)
/*--------------------------------------------------------------------------------------------*/
/* This procedure will print the filter design criteria to the final design document.         */
/*--------------------------------------------------------------------------------------------*/
{
	outfile << " " << crossover.xover_type << " values computed by SpeakEasy: " << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Filter Values " << endl;
    outfile << "-----------------------------------------" << endl;
    outfile << " Filter Order             : " << crossover.stages << endl;
    outfile << " Low-Pass Frequency (Hz)  : " << crossover.xover1 << endl;
    outfile << " Low-Pass gain (< 1)      : " << crossover.gain << endl;
    outfile << " Low-Pass 3db freq  (Hz)  : " << crossover.f3db1<< endl;
    outfile << " Low-Pass Capacitance     : " << crossover.C1 << endl;
    outfile << " Low-Pass Resistance      : " << crossover.R1 << endl;
    //outfile << " High-Pass gain (< 1)     : " << highpass.gain << endl;
    //outfile << " High-Pass Frequency (Hz) : " << highpass.xover1 << endl;
    //outfile << " High-Pass 3db freq  (Hz) : " << highpass.f3db1<< endl;
    //outfile << " High-Pass Capacitance    : " << highpass.C1 << endl;
    //outfile << " High-Pass Resistance     : " << highpass.R1 << endl;
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
