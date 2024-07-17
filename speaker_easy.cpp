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
#include <algorithm>
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
void build(Speaker*& drvr, Speaker*& mid, Speaker*& tweet)
/*--------------------------------------------------------------------------------------------*/
/* The build() function builds the list of available parts that the user can select from to   */
/* design/build/simualte a speaker design with. The user is prompted to enter various part    */
/* values at the CLI prompts. The information is stored in an FIFO linked list.               */
/* Input: Struct Speaker - passed by reference                                                */
/*                         Adds multiple links if needed by user.                             */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *temp, *bass, *bandp, *high;

    temp=(struct Speaker *)malloc(sizeof(struct Speaker));

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "| Enter the speaker values as instructed below:             |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "    Part Number            : ";
    cin >> temp->Part_num;
    cout << "    Type (Woof/Twet/Midr)  : ";
    cin >> temp->Type;
    cout << "    Vas (dm^3) (aka liters): ";
    cin >> temp->Vas;
    cout << "    Compliance             : ";
    cin >> temp->Cms;
    cout << "    BL (Force Factor)      : ";
    cin >> temp->Bl;
    cout << "    Qts (Total Q factor)   : ";
    cin >> temp->Qts;
    cout << "    Qes (Electric Q factor): ";
    cin >> temp->Qes;
    cout << "    Qms (Mech Q factor)    : ";
    cin >> temp->Qms;
    cout << "    Fs                     : ";
    cin >> temp->Fs;
    cout << "    Re (ohms)              : ";
    cin >> temp->Re;
    cout << "    RMS (kg*s)             : ";
    cin >> temp->Rms;
    cout << "    Z_nom (Nom Impedance)  : ";
    cin >> temp->Z_nom;
    cout << "    Z_min (Min Impedance)  : ";
    cin >> temp->Z_min;
    cout << "    Z_max (Max Impedance)  : ";
    cin >> temp->Z_max;
    cout << "    Le (mH)                : ";
    cin >> temp->Le;
    cout << "    Xmax (mm)              : ";
    cin >> temp->Xmax;
    cout << "    Diam (mm)              : ";
    cin >> temp->Diam;
    cout << "    Nom_Pwr (W)            : ";
    cin >> temp->Nom_Pwr;
    cout << "    Max_Pwr (W)            : ";
    cin >> temp->Max_Pwr;
    cout << "    Freq_Low (Hz)          : ";
    cin >> temp->Freq_Low;
    cout << "    Freq_Hi (Hz)           : ";
    cin >> temp->Freq_Hi;
    cout << "    Sensitivity (db 1w/1m) : ";
    cin >> temp->Sensitivity;
    cout << "    Box volume - sealed (m^3)         : ";
    cin >> temp->Vbs;
    cout << "    Box volume - vented (m^3)       : ";
    cin >> temp->Vbv;
    cout << "    f3_seal (3db rolloff): ";
    cin >> temp->f3_seal;
    cout << "    f3_vent (3db rolloff)  : ";
    cin >> temp->f3_vent;
    cout << "    v_diam (vent diameter) : ";
    cin >> temp->v_diam;
    cout << "    v_length (vent length) : ";
    cin >> temp->v_length;
    temp->next = NULL;

    sleep(10);

    drvr = temp;

    if (strcmp(temp->Type, "Woof") == 0) {
        sleep(1);
        drvr = temp;
        // check
        cout << "Part num: " << drvr->Part_num << endl;
        sleep(1);
    }

    if (strcmp(temp->Type, "Midr") == 0) {
        sleep(1);
        mid = temp;
        // check
        cout << "Part num: " << mid->Part_num << endl;
        sleep(1);
    }

    if (strcmp(temp->Type, "Twet") == 0) {
        sleep(1);
        tweet = temp;
        // check
        cout << "Part num: " << tweet->Part_num << endl;
        sleep(1);
    }
}
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr, Speaker* mid, Speaker* tweet)
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

    for (i = 0; i< 3; i++) {
        if (i == 0 ) {
            ptr = drvr;  

            if (ptr == NULL) {
                cout << "Parts List is empty..." << endl;
                sleep(1);
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    
    
        if (i == 1) { 
            ptr = mid; 
    
            if (ptr == NULL) {
                cout << "Parts List is empty..." << endl;
                sleep(1);
            } else {
                print_part(ptr);
                sleep(1);
            }
        }    

        if (i == 2) { 
            ptr = tweet;
    
            if (ptr == NULL) {
                cout << "Parts List is empty..." << endl;
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
        cout << "Speaker Parts List is empty..." << endl;
        
        sleep(1);
        return;
    } else {
        cout << "    Avalable Speaker Parts:... " << endl;
        ptr = drvr;  //Set the temporary pointer to the head of the list

        while (ptr != NULL) {
            cout << "Part Number            : " << ptr->Part_num << endl;
            cout << "Type                   : " << ptr->Type << endl;
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
            cout << "Z_min (Ohms)           : " << ptr->Z_min << endl;
            cout << "Z_max (Ohms)           : " << ptr->Z_max << endl;
            cout << "Le (mH)                : " << ptr->Le << endl;
            cout << "Xmax (mm)              : " << ptr->Xmax << endl;
            cout << "Diam (mm)              : " << ptr->Diam << endl;
            cout << "Nom_Pwr (W)            : " << ptr->Nom_Pwr << endl;
            cout << "Max_Pwr (W)            : " << ptr->Max_Pwr << endl;
            cout << "Freq_Low (Hz)          : " << ptr->Freq_Low << endl;
            cout << "Freq_Hi (Hz)           : " << ptr->Freq_Hi << endl;
            cout << "Sensitivity            :  " << ptr->Sensitivity << endl;
            cout << "- - - - Default Data Sheet Values - - - -" << endl;
            cout << "Vol Sealed (L || dm^3) : " << ptr->Vbs << endl;
            cout << "Vol Vented (L || dm^3) : " << ptr->Vbv << endl;
            cout << "f3_seal (Hz)           : " << ptr->f3_seal << endl;
            cout << "f3_vent (Hz)           : " << ptr->f3_vent << endl;
            cout << "vent diam  (mm)        : " << ptr->v_diam << endl;
            cout << "vent length(mm)        : " << ptr->v_length << endl;
            ptr = ptr->next;
            cout << "+-----------------------------" << endl;
            
            sleep(5);
        }
    }
}
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet& box)
/*--------------------------------------------------------------------------------------------*/
/* closed_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     closed_box_param_set()                                                                 */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    struct Cabinet enclosure;
    char l_cmd[8];
    char d_cmd[8];

    char fill[4];                  // Box is filled (1) or not (0)
	char units[8];                 // used to display centimeters or inches


    float Qa;                      // These two *values* are used to determine the 'filling'
    float gamma;                   // constants for a closed-box design. Qa = 10/5 - lambda = 1/1.2

	int uom;                       // Unit of measure - metric (0) or imperial (1)
    int flag;                      // Initial pass of cabinet design flag = 0
    int vol_flg;                   // Initially set to '0', but one the user makes a first pass
                                   // through the design process, then the flag will be toggled 
                                   // to '1'. The flag will be reset to '0' upon exit.

    float alpha;                   // ratio of Driver compliance vs enclosure volume (Vol_vent)
    float A1;
    float f3;
    float Fcb;
    float Fsb;                     // Driver resonance freq mounted in enclosure
    float Fb;                      // Resonance frequency of a closed box system
    float fc;                      // Resonance frequency of a closed box system
    float Fs;
    float Fn;                      // Normal frequency value
    float L;
    float Vd;
    float Qtc, Qtcp;               // Q factor values used for closed-box measurements
    float Vab;                     // box volume derived from compliance (Vas) and alpha/gamma
    float Vbs;                     // Temporary value of box volume derived from Vol_seal
    float vol_temp;                // Hold value of converte volume

    float Par, Per;                // Displacement limited power ratings
    float peak;
    float Rh;                      // Ripple response (in db)
    float R;                       // decibel value for a given frequency(f)
    float A, B;                    // Intermediate place-holder for frequency response
    float a, b, c, d;

    int i;                         // frequency increment
    int bdesign;                   // Value entered for switch statement choosing deign flow
    int empty_val;                 // value used to checking for missing values.

    flag = 0;
    
    vol_flg = 0;
    empty_val = 0;

    system("clear");
    cout << "Design a closed box speaker..." << endl;

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

        if (ptr->Vbs <= 0) {
            sleep(2);

            empty_val = 2;
        }

        if (ptr->f3_seal <= 0) {
            sleep(2);

            empty_val = 2;
        }

        sleep(2);

        cout << "Choose design based on:" << endl;
        cout << "    1) default speaker values" << endl;
        cout << "    2) box volume" << endl;
        cout << "    3) Enter Q(tc)" << endl;
        cout << "    4) Use default value of Q(tc) = 1" << endl;

        if (empty_val = 0) {
            cin >> bdesign;
        } else {
            bdesign = empty_val;
        }
        
        switch (bdesign) {
            case 1:
                cout << "Choose design based on default values : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per);
                break;
            case 2:
                cout << "Choose design based on box volume : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per);
                break;
            case 3:
                cout << "Choose design based on user specified value of Q(tc) : " << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per);
                break;
            default:
                cout << "Choose design based on default value of Q(tc) to 1" << endl;
                closed_box_param_set(drvr, bdesign, Vbs, alpha, gamma, Qa, Fsb, Vab, L, Qtc, Qtcp, fc, A1, f3, peak, Par, Per);
                break;

        }

        cout << "+------------------------------------------+" << endl;
        cout << "| Inermediate values for sealed box design |" << endl;
        cout << "+------------------------------------------+" << endl;
        cout << " Acoustic Filling (Y/N)   : " << fill << endl;
        cout << " Driver compliance (Vas)  : " << ptr->Vas << endl;
        cout << " Box Volume (dm^3)        : " << Vbs << endl;
        cout << " Volume compliance (Vab)  : " << Vab << endl;
        cout << " Volume ratio (alpha)     : " << alpha << endl;
        cout << " Filling value (gamma)    : " << gamma << endl;
        cout << " Filling value (Qa)       : " << Qa << endl;
        cout << " Driver Q (Qtc)           : " << Qtc << endl;
        cout << " Derived Driver Q (Qtcp)  : " << Qtcp << endl;
        cout << " Resonance Frequncy Fc    : " << Fsb << endl;
        cout << " Driver resonance Fs      : " << ptr->Fs << endl;
        cout << " Driver resonance Fsb     : " << Fsb << endl;
        cout << " Q driver ratio L         : " << L << endl;
        cout << " 3db down response f3 (Hz): " << f3 << endl;
        cout << " Peak db                  : " << peak << endl;
        cout << " Acoustic Power Par       : " << Par << endl;
        cout << " Electrical Power Per     : " << Per << endl;
        cout << "--------------------------------------------" << endl;

        strcpy(box.Part_num, ptr->Part_num);
        box.cab_volume = Vbs;
        box.freq_lo = ptr->Freq_Low;
        box.freq_hi = ptr->Freq_Hi;
        box.Sensitivity = ptr->Sensitivity;
        box.res_freq = Fsb;
        box.rolloff = f3;
        box.imp_Nom = ptr->Z_nom;;
        box.vent_diam = 0;
        box.vent_length = 0;
        box.PAR = Par;
        box.PER = Per;

        sleep(5);
        // Power displacement ratings 

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

    cout << "Units are based on metric measurements. Continue with metric (cubic decimeters) or use imperial (cubic inches) (Y/N) ?" << endl;
     cout << "--------------------------------------------------------------------------------------------------------------" << endl;
     cin >> l_cmd;

     if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
         // Remain in metric units
         Vbs = liter_to_cubicInch * Vbs;

		 uom = 0;

		 strcpy(units, "cms");
		 cout << "DBG - Vbs : " << Vbs << endl;
     } else {
         // work in imperial units
         Vbs = liter_to_cubicInch * Vbs;

		 uom = 1;

		 strcpy(units, "inches");
		 cout << "DBG - Vbs : " << Vbs << endl;
     }

     // Compute box dimensions
     cout << "Determine interior box volume..." << endl;
     cout << "-----------------------------------" << endl;
     cout << endl;
     cout << "Enter box depth (D) in " << units << " : ";
     cin >> box.D;

}
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, float& Vbs, float& alpha, float& gamma, float Qa, float& Fsb, float& Vab, float& L, float& Qtc, float& Qtcp, float& fc, float& A1, float& f3, float& peak, float& Par, float& Per)
/*--------------------------------------------------------------------------------------------*/
/* closed_box_param_set() will take the settingd used to define the closed_box parameters     */
/* derived from gamma and Qa based on the choice to use fill material or no. The user defines */
/* the fill parameter progamatically.                                                         */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    char flag;                 // trigger to ignore switch stmt and fall into case statement

    float a, b, c, d;          // Intermediate placeholders to ease complex math evaluations
    float Vd;                  // Volume of air displacement;
    float alpha_p;
    float Fsb_p;
    //float Fsb;
    float Qt;                  // Total Q factor - computed

    int choice;

    flag = 1;

    Vbs = ptr->Vbs;
    Fsb = ptr->Fs;
    Qt = ptr->Qts;
    
    switch (bdesign) {
        case 1:
            cout << "Design centered around default values : " << endl;
            
            Vab = Vbs * gamma;
            alpha = ptr->Vas/ptr->Vbs;

            L = sqrt(alpha + 1);
            fc = L * Fsb;

            Qtcp = L * ptr->Qts;
            Qtc = 1/((1/Qtcp) + (1/Qa));

            A1 = (1/pow(Qtc, 2)) - 2;

            f3 = ptr->f3_seal;

            break;

        case 2:
            cout << "Enter speaker box volume in decimeters^3: ";
            cout << "Current speaker volume: " << ptr->Vbs << endl;
            cout << "Enter: ";
            cin >> Vbs;

            Vab = Vbs * gamma;
            alpha = ptr->Vas/Vbs;

            L = sqrt(alpha + 1);
            fc = L * Fsb;

            Qtcp = L * ptr->Qts;
            Qtc = 1/((1/Qtcp) + (1/Qa));

            A1 = (1/pow(Qtc, 2)) - 2;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);
            
            if (ptr->f3_seal <= 0) {
                ptr->f3_seal = f3;
            }
            
            if (ptr->Vbs <= 0) {
                ptr->Vbs = Vbs;
            }

            break;

        case 3:
            cout << "Choose design based on user specified value of Q(tc) :";
            cout << "Current value of Qtc: " << Qtc << endl;
            cout << "Enter: ";
            cin >> Qtc;

            Qtcp = 1/((1/Qtc) - (1/Qa));
            L = Qtcp/Qt;

            alpha = pow(L, 2) - 1;

            Vab = ptr->Vas/alpha;
            Vbs = Vab/gamma;

            fc = L * Fsb;

            A1 = (1/pow(Qtc, 2)) - 2;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);
            
            break;

        default:
            cout << "Choose design based on default value of Q(tc) to 1" << endl;
            Qtc = 1;

            Qtcp = 1/((1/Qtc) - (1/Qa));
            L = Qtcp/Qt;

            alpha = pow(L, 2) - 1;

            Vab = ptr->Vas/alpha;
            Vbs = Vab/gamma;

            fc = L * Fsb;

            A1 = (1/pow(Qtc, 2)) - 2;

            f3 = fc * sqrt(A1 + sqrt(pow(A1, 2) + 4)/2);

            break;

    }
    ptr->Vbs = Vbs;

    // Speaker displacement - cu meter
    Vd = (M_PI * pow((ptr->Diam/2), 2) * ptr->Xmax/1000.00);

    if (A1 >= 0) {
        peak = 0;
    } else {
        peak = 10 * log(4/(4 - pow(A1, 2)));
    }

    cout << "-------------------------------------" << endl;
    cout << " Debug - intermediate data           " << endl;
    cout << "-------------------------------------" << endl;
    cout << " Sealed box volume (Vbs) : " << ptr->Vbs << endl;
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
    cout << " Closed box resonance Fs : " << ptr->Fs << endl;
    cout << " Piston area Vd          : " << Vd << endl;
    cout << " 3db rolloff (data sheet): " << ptr->f3_seal << endl;
    cout << " 3db rolloff (calculated): " << f3 << endl;
    cout << "-------------------------------------" << endl;
    cout << " Sealed box Qa           : " << Qa << endl;
    cout << " sealed box gamma        : " << gamma << endl;
    cout << " Peak db value           : " << peak << endl;
    cout << "-------------------------------------" << endl;

    sleep(5);

    //Par = (pow(ptr->f3_seal, 4) * pow(Vd, 2))/(1.2e9);
    //Per = (pow(ptr->f3_seal, 4) * pow(Vd, 2) * ptr->Qts)/(pow(ptr->Fs, 3) * ptr->Vas * 1e3);
    Par = (pow(f3, 4) * pow(Vd, 2))/(1.2e9);
    Per = (pow(f3, 4) * pow(Vd, 2) * ptr->Qts)/(pow(ptr->Fs, 3) * ptr->Vas * 1e3);

    closed_freq_response(drvr, A1, f3, fc, Fsb);

}
/*--------------------------------------------------------------------------------------------*/
void closed_freq_response(Speaker* drvr, float A1, float f3, float fc, float Fsb)
/*--------------------------------------------------------------------------------------------*/
/* closed_freq_response() plots the frequency rsponse of a sealed box speaker for the chosen  */
/* driver.                                                                                    */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;
    
    float a, b, c, d;                     // Intermediate variables used to keep track
                                          // of computations and ease readability
    float i;
    float Fn;
    float R, Rp;

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
void vented_box_design(Speaker*& drvr, Cabinet& box)
/*--------------------------------------------------------------------------------------------*/
/* vented_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     freq_params()                                                                          */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    char l_cmd[8];
    char d_cmd[8];

    int flag;                      // Initial pass of cabinet design flag = 0
    int vol_flg;                   // Initially set to '0', but one the user makes a first pass
                                   // through the design process, then the flag will be toggled 
                                   // to '1'. The flag will be reset to '0' upon exit.
    float alpha;                   // ratio of Driver compliance vs enclosure volume (Vol_vent)
    float Fsb;                     // Driver resonance freq mounted in enclosure
    float Fb;                      // Enclosure resonance requency - not to be confused with Fsb
    float Fn;                      // Normalized frequency ratio - f(req)/Fsb
    float Vd;                      // Volume of air displacement
    float Vb;                      // Volume of cabinet - liters || dm^3
    float Vbv;                     // Computed volume of cabinet - liters || dm^3 
    float Vb_i, Vb_u;              // Internal cabinet volumes - user supplied
    float Rh;                      // Ripple response (in db)
    float R;                       // decibel value for a given frequency(f)
    float Par, Per;                // Displacement limited power ratings
    float Dv, Lv, L_prm;           // Vent diameter, length in mm
    float lv;
    float dv;
    float A, B, C, D;              // Intermediate place-holders
    float a, b, c, d, e, f;        // value holders for frequency response measurement
    float tmp_1, tmp_2, tmp_3;
    int i;                        // frequency increment

    flag  = 0;
    vol_flg = 0;

    /* Default flat values */
    Dv = 50.0; // Set Vent diameter to 50mm by default;
    Lv = 50.0;

    if (ptr->Vbv <= 0) {
        a = pow(ptr->Qts, 3.3);

        ptr->Vbv = pow(ptr->Qts, 3.3) * (ptr->Vas) * 20.0;
    }

    alpha = ptr->Vas/ptr->Vbv;
    Fsb = (ptr->f3_vent)/pow(alpha, 0.44);
    Fb = (ptr->f3_vent)/pow(alpha, 0.13);

    system("clear");
    cout << "Design a vented box speaker..." << endl;
    sleep(5);
    
    while (!flag) {
        vented_freq_params(drvr, Vbv, Fsb, Fb, Fn, Vd, Rh, Par, Per, Dv, Lv, L_prm, lv, dv, a, b, c, d, alpha);

        sleep(5);
        //----------------------------
        // Compute freq response here
        //----------------------------

        vented_freq_response(drvr, Fsb, Fb, Fn, alpha);

        cout << "Accept results (Y/y)? :" << endl;
        cin >> l_cmd;
        system("clear");

        if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
            cout << "Speaker Design completed..." << endl;
            flag = 1;
            vol_flg = 0;
        } else {
            cout << "Specify new Enclosure Internal Volume - " << endl;
            cout << "Enter value in dm^3 (aka liters): ";
            cin >> ptr->Vbv;
            cout << "Enter new Vent diameter (mm) > 50(mm) - default is " << ptr->v_diam << "mm: ";
            cin >> ptr->v_diam;
            cout << "Enter new Vent length (mm) > 50(mm) - default is " << ptr->v_length << "mm: ";
            cin >> ptr->v_length;
        }

        sleep(5);
    }

    strcpy(box.Part_num, ptr->Part_num);
    box.cab_volume = Vbv;
    box.freq_lo = ptr->Freq_Low;
    box.freq_hi = ptr->Freq_Hi;
    box.Sensitivity = ptr->Sensitivity;
    box.res_freq = Fsb;
    box.rolloff = ptr->f3_vent;
    box.imp_Nom = ptr->Z_nom;;
    box.vent_diam = ptr->v_diam;
    box.vent_length = ptr->v_length;
    box.PAR = Par;
    box.PER = Per;

}
/*--------------------------------------------------------------------------------------------*/
void closed_freq_params(Speaker* drvr, float& Qa, float& gamma, float& alpha, float& A1, float& Fsb, float& Fcb, float& Fs, float& f3, float& Fb, float& Fc, float& L, float& Vd, float& Qtc, float& Qtcp, float& Vab, float& Rh, float& R, float& Par, float& Per) 
/*--------------------------------------------------------------------------------------------*/
/* closed_freq_params - evaluates the Small/Thiele parameters for a closed box systeem in     */
/* preparation for evaluating the peak power and frequency response.                          */
/*--------------------------------------------------------------------------------------------*/
{

    struct Speaker *ptr;
    ptr = drvr;

    char fill[4];                  // Box is filled (1) or not (0)
    float a, b, c, d;              // intermediate compute buckets
        
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

    // Speaker displacement - cu meter
    Vd = (M_PI * pow((ptr->Diam/2), 2) * ptr->Xmax/1000.00);

    if (A1 < 0) {
        Rh = 10 * log (4 /(4 - pow(A1, 2)));
    } else {
        Rh = 0;
    }
        
    // Displaement limited power ratings
    Par = (pow(ptr->f3_seal, 4) * pow(Vd, 2))/1.2e9;
        
    Per = (pow(ptr->f3_seal, 4) * pow(Vd, 2) * ptr->Qts)/(pow(ptr->Fs, 3) * ptr->Vas * 1e3);

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
    cout << " Limited Acoustic Power    :    " << Par << endl;
    cout << " Limited Electrical Power  :    " << Per << endl;
    cout << "-----------------------------------------------------------" << endl;

    sleep(5);

}
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, float& Vbv, float& Fsb, float& Fb, float& Fn, float& Vd, float& Rh, float& Par, float& Per, float& Dv, float& Lv, float& L_prm, float& lv, float& dv, float& a, float& b, float& c, float& d, float& alpha)
/*--------------------------------------------------------------------------------------------*/
/* vented_freq_params() used to compute intermediate Thiel/Small values ised for vented box   */
/* loudspeaker design. Ideally, the user could pass a single flag that would toggle between   */
/* vented- and closed-speaker design.                                                         */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;
    ptr = drvr;

    float A, B, C, D;
    float Vb;

    /* If f3 down parameters are missing, compute here */
    if (ptr->f3_vent <= 0) {
        ptr->f3_vent = 0.28 * ptr->Fs * pow(ptr->Qts, -1.4);
    }

    Fb = 1.5 * ptr->f3_vent * pow(ptr->Qts, 0.44);

    // Driver resonance frequency - mounted
    Fsb = ptr->f3_vent/(0.28 * pow(ptr->Qts, -1.4));

    // Speaker displacement - decimeter^3
    A = M_PI * pow(ptr->Diam/2, 2);
    Vd = (A * ptr->Xmax)/1000.00;

    /* Vent design                                                   */
    /* If vent parameters are missing or null, define minimal values */
    if (ptr->v_diam <= 0) {
        ptr->v_diam = (20 * sqrt(Vd))/(pow(ptr->Fs, 0.25));
    }

    if (ptr->v_length <= 0) {
        L_prm = 2350/(pow(Fb, 2) * (ptr->f3_vent));

        ptr->v_length = L_prm * pow(ptr->v_diam, 2) - (0.73 * ptr->v_diam);
    }

    sleep(5);

    A = pow(0.85, 2);
    B = 4 * L_prm * ptr->v_length;
    C = a + b;

    D = pow(c, 0.5);

    alpha = ptr->Vas/ptr->Vbv;

    // Displacement limited power ratings
    Par = (pow(ptr->f3_vent, 4) * pow(Vd, 2))/3e8;
    Per = (1.2e6 * Par * ptr->Qts)/(pow(ptr->Fs, 3) * ptr->Vas);

    // 3db ripple ripple
    Rh = 20 * log ((Fb * ptr->Qts)/(0.4 * ptr->Fs));
    Rh = abs(Rh);

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
    cout << " Ripple (in decibels)             : " << Rh << endl;
    cout << " Frequency range                  : " << ptr->Freq_Low << " - " << ptr->Freq_Hi << endl;
    cout << " Minimum vent diameter            : " << ptr->v_diam << endl;
    cout << " Vent length                      : " << ptr->v_length << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "              Displacement Power Ratings                   " << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << " Limited Acoustic Power    :    " << Par << endl;
    cout << " Limited Electrical Power  :    " << Per << endl;
    cout << "-----------------------------------------------------------" << endl;
        
    sleep(5);
}
/*--------------------------------------------------------------------------------------------*/
void vented_freq_response(Speaker* drvr, float Fsb, float Fb, float Fn, float alpha) 
/*--------------------------------------------------------------------------------------------*/
/* vented_freq_response() is used to write the results of the frequency calculation to a CSV  */
/* format text file. The file will be read by the GNUplot graphing utility and displayed.     */
/*--------------------------------------------------------------------------------------------*/
{

    struct Speaker *ptr;
    ptr = drvr;

    float A, B, C, D;                            // Intermediate placeholders variables
    float a, b, c, d;                            // Intermediate placeholders
    
    float R;                                     // Decibel value for plotting

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
void save_speaker_data(Speaker* drvr, Speaker* mid, Speaker* tweet)
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

    int i;

    low = drvr;
    bpass = mid;
    high = tweet;

    system("clear");

    /*--------------------------------------------------*/
    /* Once code is validated, indent to clean up code block */
    /*--------------------------------------------------*/
    
    if (low == NULL) {
         cout << "Bass pointer is null..." << endl;
         sleep(2);
    } else {
         save_data_ptr(low);
    }
    
    if (bpass == NULL) {
         cout << "Midrange pointer is null..." << endl;
         sleep(2);
    } else {
         save_data_ptr(bpass);
    }
    
    if (high == NULL) {
         cout << "Tweeter pointer is null..." << endl;
         sleep(2);
    } else {
         save_data_ptr(high);
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

    /*
    cout << "In save_data_ptr() call..." << endl;
    cout << drvr->Part_num << endl;
    cout << drvr->Type << endl;
    sleep(2);
    */

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
            outfile << ptr->Z_min << ";"; 
            outfile << ptr->Z_max << ";"; 
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
            ptr = drvr->next;
            
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
    struct Speaker *ptr, *temp;

    char line[64];
    char *token;
    
    int i, j, k;

    float num;

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

    //system("cat drvr_dba");
    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
        //cout << "Data: " << line << endl;
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
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
        temp->Z_min = atof(token);
        token = strtok(NULL, ";");
        temp->Z_max = atof(token);
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

    char line[64];
    char *token;
    
    int i, j, k;

    float num;

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
        //cout << "Data: " << line << endl;
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
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
        temp->Z_min = atof(token);
        token = strtok(NULL, ";");
        temp->Z_max = atof(token);
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

    char line[64];
    char *token;
    
    int i, j, k;

    float num;

    string cmd_str;
    string filesdb = "";

    ifstream infile;
    ifstream input;

    tweet = NULL;
    drvr_dba = "";

    system("clear");

    cout << "-------------------------------" << endl;
    sleep(2);
    cmd_str = "./driver.csh Twet";

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

    //system("cat drvr_dba");
    temp = (struct Speaker *)malloc(sizeof(struct Speaker));

    while (input >> line) {
        //cout << "Data: " << line << endl;
        token = strtok(line, ";");
        strcpy(temp->Part_num, token);
        token = strtok(NULL, ";");
        strcpy(temp->Type, token);
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
        temp->Z_min = atof(token);
        token = strtok(NULL, ";");
        temp->Z_max = atof(token);
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
        temp->next = NULL;
    
        sleep(2);
        tweet = temp;
        ptr = tweet;
    }

    //sleep(3);
}
/*--------------------------------------------------------------------------------------------*/
void write_design_data(Speaker* drvr, Cabinet box, Filter lowpass, Filter bandpass, Filter highpass)
/*--------------------------------------------------------------------------------------------*/
/* This function will print the resulting speaker parameters and crossover information to a   */
/* simple text file that the user can then print out.                                         */
/*--------------------------------------------------------------------------------------------*/
{
    struct Speaker *ptr;

    system("clear");

    cout << "Specify speaker data file: ";
    cin >> dsgn_data;

    dsgn_data = dsgn_data + ".ddf";

    ofstream outfile(dsgn_data);
    /*-------------------------------------------------------*/
    outfile << "+--------------------------------------------+" << endl;
    outfile << " Cabinet Design Values" << endl;
    outfile << "+--------------------------------------------+" << endl;
    outfile << " Part Number              : " << box.Part_num << endl;
    outfile << " Cabinet Volume(dm^3)     : " << box.cab_volume << endl;
    outfile << " Vent Diameter (mm)       : " << box.vent_diam << endl;
    outfile << " Vent Length (mm)         : " << box.vent_length << endl;
    outfile << " Low Frequency (Hz)       : " << box.freq_lo << endl;
    outfile << " High Frequency (Hz)      : " << box.freq_hi << endl;
    outfile << " Nominal Impedance (ohms) : " << box.imp_Nom << endl;
    outfile << " Resonant Frequency (Hz)  : " << box.res_freq << endl;
    outfile << " Frequency Rolloff (Hz)   : " << box.rolloff << endl;
    outfile << " Sensitivity (SPL)        : " << box.Sensitivity << endl;
    outfile << " Acoustic Power (W)       : " << box.PAR << endl;
    outfile << " Electrical Power (W)     : " << box.PER << endl;
    outfile << "+--------------------------------------------+" << endl;
    outfile << endl;
    outfile << "+--------------------------------------------+" << endl;
    outfile << " Crossover Design Values" << endl;
    outfile << "+--------------------------------------------+" << endl;
    outfile << " Filter Type                : " << lowpass.xover_type << endl;
    outfile << " Filter Order               : " << lowpass.stages << endl;
    outfile << " Low-Pass Frequency (Hz)    : " << lowpass.xover1 << endl;
    outfile << " Low-Pass gain (< 1)        : " << lowpass.gain << endl;
    outfile << " Low-Pass 3db freq  (Hz)    : " << lowpass.f3db1<< endl;
    outfile << " Low-Pass Capacitance/C1    : " << lowpass.C1 << endl;
    outfile << " Low-Pass Resistance/R1     : " << lowpass.R1 << endl;
    outfile << " Band-Pass Frequency(Hz)    : " << bandpass.xover1 << endl;
    outfile << " Band-Pass gain (< 1)       : " << bandpass.gain << endl;
    outfile << " Band-Pass 3db(l) freq (Hz) : " << bandpass.f3db1<< endl;
    outfile << " Band-Pass 3db(h) freq (Hz) : " << bandpass.f3db2<< endl;
    outfile << " Band-Pass Capacitance/C1   : " << bandpass.C1 << endl;
    outfile << " Band-Pass Capacitance/C2   : " << bandpass.C2 << endl;
    outfile << " Band-Pass Resistance/R1    : " << bandpass.R1 << endl;
    outfile << " Band-Pass Resistance/R2    : " << bandpass.R2 << endl;

    if (lowpass.xover_type == "Active") {
        outfile << " Feedback Resistance - R1: " << lowpass.FB_R1 << endl;
        outfile << " Feedback Resistance - R2: " << lowpass.FB_R2 << endl;
    }

    outfile << " High-Pass gain (< 1)    : " << highpass.gain << endl;
    outfile << " High-Pass Frequency     : " << highpass.xover1 << endl;
    outfile << " High-Pass 3db freq      : " << highpass.f3db1<< endl;
    outfile << " High-Pass Capacitance   : " << highpass.C1 << endl;
    outfile << " High-Pass Resistance    : " << highpass.R1 << endl;
    outfile << "-----------------------------------------" << endl;

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

    float res_freq;   /* resonant frequency of the bandpass filter */
    float gain;       /* Gain at cut-off frequency for filter.  */
    float xover;      /* Cross-ver or frequency cut-off for filter(s)  - high/low pass */
    float f3db1;      /* -3db cut-off frequency for 2-way speaker. */

    float C1, C2;     /* User defined value for capacitance for filter cut-off */
    float R1, R2;     /* Computed resistance for given capacitance and crossover frequency. */
    int i;            /* Counter value for storing the values in the number of cascading stages. */
    int stages;       /* Number of stages used to determine the order of the filter. */
                      /* Default is 1 (1st order Butterworth Filter). */

    string low_parse = "";    /* The following strings are used to store the parsed data from    */
    string high_parse = "";   /* the speaker node passed in to display the part and frequency    */
                              /* band-width.                                                     */
                              
    cout << "This is a Butterworth passive crossover for 2 driver speaker. " << endl;
    lowpass.xover_type = "Passive";

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

    float res_freq;           /* resonant frequency of the bandpass filter */

    float gain;               /* Gain at cut-off frequency for filter. */
    float xover;              /* Cross-ver or frequency cut-off for filter(s) - high/low pass */
    float f3db1, f3bd_2;      /* -3db cut-off frequency for 3-way speaker. */

    float C1, C2, C3; /* User defined value for capacitance for filter cut-off */
    float R1, R2, R3; /* Computed resistance for given capacitance and crossover frequency. */

    int co_1, co_2;   /* crossover point. */
    int i;            /* Counter value for storing the values in the number of N-order stages.*/
    int stages;       /* Number of stages used to determine the order of the filter. */
                      /* Default is 1 (1st order Butterworth Filter). */

                              
    cout << "This is a 1st order crossover for 3 driver speaker. " << endl;
    lowpass.xover_type = "Passive";

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

    float res_freq;   /* resonant frequency of the bandpass filter */
    float gain;       /* Gain at cut-off frequency for filter. */
    float xover;      /* Cross-ver or frequency cut-off for filter(s)  - high/low pass */
    float f3db1;      /* -3db cut-off frequency for 2-way speaker. */

    float C1, C2;     /* User defined value for capacitance for filter cut-off */
    float R1, R2;     /* Computed resistance for given capacitance and crossover frequency. */
    float R3, R4;

    int i;            /* Counter value for storing the values in the number of cascading stages. */
    int stages;       /* Number of stages used to determine the order of the filter.             */
                      /* Default is 1 (1st order Butterworth Filter).                            */

    string low_parse = "";    /* The following strings are used to store the parsed data from    */
    string high_parse = "";   /* the speaker node passed in to display the part and frequency    */
                              /* band-width.                                                     */
                              
    cout << "This is a Butterworth passive crossover for 2 driver speaker. " << endl;
    lowpass.xover_type = "Active";

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

    float res_freq;           /* resonant frequency of the bandpass filter */

    float gain;               /* Gain at cut-off frequency for filter. */
    float xover;              /* Cross-ver or frequency cut-off for filter(s) - high/low pass */
    float f3db1, f3bd_2;      /* -3db cut-off frequency for 3-way speaker. */

    float C1, C2, C3; /* User defined value for capacitance for filter cut-off                */
    float R1, R2, R3; /* Computed resistance for given capacitance and crossover frequency.   */

    int co_1, co_2;   /* crossover point. */
    int i;            /* Counter value for storing the values in the number of N-order stages.*/
    int stages;       /* Number of stages used to determine the order of the filter.          */
                      /* Default is 1 (1st order Butterworth Filter).                         */

                              
    cout << "This is a 1st order crossover for 3 driver speaker. " << endl;
    lowpass.xover_type = "Active";

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
