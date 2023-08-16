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
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
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
#undef extern

using namespace std;
using std::cin;
using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------*/
/*                               Global Vars and Constants                                    */
/*--------------------------------------------------------------------------------------------*/
string drvr_dba = "";
string drvr_lgth = "";
string plot_data = "";
string gnu_plot = "gnu_script.gp";

/*--------------------------------------------------------------------------------------------*/
/*                               Functions and Procedures                                     */
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr)
/*--------------------------------------------------------------------------------------------*/
/* The build() function builds the list of available parts that the user can select from to   */
/* design/build/simualte a speaker design with. The user is prompted to enter various part    */
/* values at the CLI prompts. The information is stored in an FIFO linked list.               */
/* Input: Struct Speaker - passed by reference                                                */
/*                         Adds multiple links if needed by user.                             */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *temp, *ptr;

	temp=(struct Speaker *)malloc(sizeof(struct Speaker));

	if(temp == NULL) {
		cout << "Out of Memory Space:" << endl;
		return;
	}

	cout << "+-----------------------------------------------------------+" << endl;
	cout << "| Enter the speaker values as instructed below:             |" << endl;
	cout << "+-----------------------------------------------------------+" << endl;
	cout << "	Part Number            : ";
	cin >> temp->Part_num;
	cout << "	Vas (m^3)             : ";
	cin >> temp->Vas;
	cout << "	Compliance             : ";
	cin >> temp->Cms;
	cout << "	BL (Force Factor)      : ";
	cin >> temp->Bl;
	cout << "	Qts (Total Q factor)   : ";
	cin >> temp->Qts;
	cout << "	Qes (Electric Q factor): ";
	cin >> temp->Qes;
	cout << "	Qms (Mech Q factor)    : ";
	cin >> temp->Qms;
	cout << "	Fs                     : ";
	cin >> temp->Fs;
	cout << "	Re (ohms)              : ";
	cin >> temp->Re;
	cout << "	RMS (kg*s)             : ";
	cin >> temp->Rms;
	cout << "	Z_nom (Nom Impedance)  : ";
	cin >> temp->Z_nom;
	cout << "	Z_min (Min Impedance)  : ";
	cin >> temp->Z_min;
	cout << "	Z_max (Max Impedance)  : ";
	cin >> temp->Z_max;
	cout << "	Le (mH)                : ";
	cin >> temp->Le;
	cout << "	Xmax (mm)              : ";
	cin >> temp->Xmax;
	cout << "	Diam (mm)              : ";
	cin >> temp->Diam;
	cout << "	Nom_Pwr (W)            : ";
	cin >> temp->Nom_Pwr;
	cout << "	Max_Pwr (W)            : ";
	cin >> temp->Max_Pwr;
	cout << "	Freq_Low (Hz)          : ";
	cin >> temp->Freq_Low;
	cout << "	Freq_Hi (Hz)           : ";
	cin >> temp->Freq_Hi;
	cout << "	Sensitivity (db 1w/1m) : ";
	cin >> temp->Sensitivity;
	cout << "	Vol_seal (m^3)         : ";
	cin >> temp->Vol_seal;
	cout << "	Vol_vented (m^3)       : ";
	cin >> temp->Vol_vent;
	cout << "	f3_sealed (3db rolloff): ";
	cin >> temp->f3_sealed;
	cout << "	f3_vent (3db rolloff)  : ";
	cin >> temp->f3_vent;
	temp->next = NULL;

	drvr = temp;
	ptr=drvr;
}
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr)
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
	struct Speaker *tail;

	cout << "List the available speakers..." << endl;
	cout << "+-----------------------------" << endl;

	sleep(3);

	if (drvr == NULL) {
		cout << "Speaker Parts List is empty..." << endl;
		
		sleep(2);
		return;
	} else {
		cout << "	Avalable Speaker Parts:... " << endl;
		ptr = drvr;  //Set the temporary pointer to the head of the list

		while (ptr != NULL) {
			cout << "Part Number: " << ptr->Part_num << endl;
			cout << "Vas        : " << ptr->Vas << endl;
			cout << "Cms        : " << ptr->Cms << endl;
			cout << "Bl         : " << ptr->Bl  << endl;
			cout << "Qts        : " << ptr->Qts << endl;
			cout << "Qes        : " << ptr->Qes << endl;
			cout << "Qms        : " << ptr->Qms << endl;
			cout << "Fs         : " << ptr->Fs << endl;
			cout << "Re         : " << ptr->Re << endl;
			cout << "Rms        : " << ptr->Rms << endl;
			cout << "Z_nom      : " << ptr->Z_nom << endl;
			cout << "Z_min      : " << ptr->Z_min << endl;
			cout << "Z_max      : " << ptr->Z_max << endl;
			cout << "Le         : " << ptr->Le << endl;
			cout << "Xmax       : " << ptr->Xmax << endl;
			cout << "Diam       : " << ptr->Diam << endl;
			cout << "Nom_Pwr    : " << ptr->Nom_Pwr << endl;
			cout << "Max_Pwr    : " << ptr->Max_Pwr << endl;
			cout << "Freq_Low   : " << ptr->Freq_Low << endl;
			cout << "Freq_Hi    : " << ptr->Freq_Hi << endl;
			cout << "Sensitivity: " << ptr->Sensitivity << endl;
			cout << "Vol Sealed : " << ptr->Vol_seal << endl;
			cout << "Vol Vented : " << ptr->Vol_vent << endl;
			cout << "f3_sealed  : " << ptr->f3_sealed << endl;
			cout << "f3_vent    : " << ptr->f3_vent << endl;
			ptr = ptr->next;
			cout << "+-----------------------------" << endl;
			
			sleep(2);
		}
	}
}
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr) 
/*--------------------------------------------------------------------------------------------*/
/* closed_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     freq_params()                                                                          */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *ptr;

	char l_cmd[8];
	char d_cmd[8];

	int flag;                      // Initial pass of cabinet design flag = 0
	int vol_flg;                   // Initially set to '0', but one the user makes a first pass
	                               // through the design process, then the flag will be toggled 
								   // to '1'. The flag will be reset to '0' upon exit.
	/*
	float alpha;                   // ratio of Driver compliance vs enclosure volume (Vol_vent)
	float Fsb;                     // Driver resonance freq mounted in enclosure
	float Fb;                      // Enclosure resonance requency - not to be confused with Fsb
	float Fn;                      // Normalized frequency ratio - f(req)/Fsb
	float Vd;                      // Volume of air displacement
	float Vb_v;                    // Volume of cabinet - meter^3
	float Vb_i, Vb_u;              // Internal cabinet volumes - user supplied
	float Rh;                      // Ripple response (in db)
	float R;                       // decibel value for a given frequency(f)
	float Par, Per;                // Displacement limited power ratings
	float Dv, Lv, L_prime;         // Vent diameter, length in mm
	float A, B, C, D;              // Intermediate place-holders
	float a, b, c, d, e, f;        // value holders for frequency response measurement
	float tmp_1, tmp_2, tmp_3;
	float D_v{}, L_prm{}, l_v{};   // Values needed for Vent design
	int i;                         // frequency increment
	*/

	ptr = drvr;
	system("clear");
	cout << "Design a closed box speaker..." << endl;

	while (!flag) {
		//closed_freq_params(drvr);

		//----------------------------
		// Compute freq response here
		//----------------------------

		//closed_freq_response(drvr);

		cout << "Accept results (Y/y)? :" << endl;
		cin >> l_cmd;

		if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
			cout << "Speaker Design completed..." << endl;
			flag = 1;
			vol_flg = 0;
		} else {
			cout << "Specify new Enclosure Internal Volume - " << endl;
			cout << "Enter value in cu meters: ";
			cin >> ptr->Vol_vent;
			cout << "Enter new Vent diameter (mm) > 50(mm) - default is 50 mm: ";
		}

		sleep(5);
	}
}
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr)
/*--------------------------------------------------------------------------------------------*/
/* vented_box_design will take the stored Small/Thiele parameters, compute the necessary data */
/* points then plot the resulting frequency plot. This function calls the functions:          */
/*     freq_params()                                                                          */
/*     freq_response()                                                                        */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *ptr;

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
	float Vb_v;                    // Volume of cabinet - meter^3
	float Vb_i, Vb_u;              // Internal cabinet volumes - user supplied
	float Rh;                      // Ripple response (in db)
	float R;                       // decibel value for a given frequency(f)
	float Par, Per;                // Displacement limited power ratings
	float Dv, Lv, L_prime;         // Vent diameter, length in mm
	float A, B, C, D;              // Intermediate place-holders
	float a, b, c, d, e, f;        // value holders for frequency response measurement
	float tmp_1, tmp_2, tmp_3;
	float D_v{}, L_prm{}, l_v{};   // Values needed for Vent design
	int i;                         // frequency increment

	ptr = drvr;
	flag  = 0;
	vol_flg = 0;
	D_v = 50.0; // Set Vent diameter to 50mm by default;

	system("clear");
	cout << "Design a vented box speaker..." << endl;
	sleep(3);
	
	while (!flag) {
		vented_freq_params(drvr, Vb_v, Fsb, Fb, Fn, Vd, Rh, Par, Per, Dv, Lv, L_prm, l_v, D_v, a, b, c, d, alpha);

		//----------------------------
		// Compute freq response here
		//----------------------------

		vented_freq_response(drvr, Fsb, Fb, Fn, alpha);

		cout << "Accept results (Y/y)? :" << endl;
		cin >> l_cmd;

		if ((strcmp(l_cmd, "Y") == 0) || (strcmp(l_cmd, "y") == 0)) {
			cout << "Speaker Design completed..." << endl;
			flag = 1;
			vol_flg = 0;
		} else {
			cout << "Specify new Enclosure Internal Volume - " << endl;
			cout << "Enter value in cu meters: ";
			cin >> ptr->Vol_vent;
			cout << "Enter new Vent diameter (mm) > 50(mm) - default is 50 mm: ";
			cin >> D_v;
		}

		sleep(5);
	}
}
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, float& Vb_v, float& Fsb, float& Fb, float& Fn, float& Vd, float& Rh, float& Par, float& Per, float& Dv, float& Lv, float& L_prm, float& l_v, float& D_v, float& a, float& b, float& c, float& d, float& alpha)
/*--------------------------------------------------------------------------------------------*/
/* vented_freq_params() used to compute intermediate Thiel/Small values ised for vented box   */
/* loudspeaker design. Ideally, the user could pass a single flag that would toggle between   */
/* vented- and closed-speaker design.                                                         */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *ptr;
	ptr = drvr;

	Vb_v = 20 * ptr->Vas * pow(ptr->Qts, 3.3);

	// Cabinet resonance frequency
	Fb = 1.5 * ptr->f3_vent * pow(ptr->Qts, 0.44);

	// Driver resonance frequency - mounted
	Fsb = ptr->f3_vent/(0.28 * pow(ptr->Qts, -1.4));

	// Speaker displacement - cu meter
	Vd = (M_PI * pow((ptr->Diam/2), 2) * ptr->Xmax/1000.00);

	// 3db ripple ripple
	Rh = 20 * log ((Fb * ptr->Qts)/(0.4 * ptr->Fs));
	Rh = abs(Rh);

	// Vent design
	L_prm = 2350/(pow(Fb, 2) * (ptr->f3_vent));

	l_v = L_prm * pow(D_v, 2) - (0.73 * D_v);
	a = pow(0.85, 2);
	b = 4 * L_prm * l_v;
	c = a + b;

	d = pow(c, 0.5);

	Dv = (0.85 + pow((a + b), 0.5))/(2 * L_prm);

	alpha = ptr->Vas/ptr->Vol_vent;

	// Displacement limited power ratings
	Par = (pow(ptr->f3_vent, 4)*pow(Vd, 2))/3e8;
	Per = (1.2e6 * Par * ptr->Qts)/(pow(ptr->Fs, 3) * ptr->Vas);

	cout << "Vented Box design values - flat alignment" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << " Driver name               :    " << ptr->Part_num << endl;
	cout << " Driver Resonance freq (Hz):    " << ptr->Fs  << endl;
	cout << " Total Mechanical Q        :    " << ptr->Qts << endl;
	cout << " Equivalent cabinet volume :    " << ptr->Vas << endl;
	cout << " Enclosure Internal volume :    " << ptr->Vol_vent << endl;
	cout << " Volume - air displacement :    " << Vd << endl;
	cout << " -3db frequency rolloff    :    " << ptr->f3_vent << endl;
	cout << " Enclosure resonance freq  :    " << Fb << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << " Ripple (in decibels)      :    " << Rh << endl;
	cout << " Frequency range           :    " << ptr->Freq_Low << " - " << ptr->Freq_Hi << endl;
	cout << " Minimum vent diameter     :    " << D_v << endl;
	cout << " Vent length               :    " << l_v << endl;
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

	plot_data = plot_data + ".dat";

	ofstream outfile(plot_data);

	//----------------------------
	// Compute freq response here
	//----------------------------

	A = pow((Fb/Fsb), 2);
	B = (A/ptr->Qts) + (Fb/(7 * Fsb));
	C = 1 + A + alpha + Fb/(7 * Fsb * ptr->Qts);
	D = (1/ptr->Qts) + Fsb/(7 * Fsb);

	outfile << "Frequency (Hz), Amplitude (dB)" << endl;
	cout << "\tfreq\t\tdecibels" << endl;
	cout << "-------------------------------------" << endl;

	for (i = ptr->Freq_Low; i <= ptr->Freq_Hi; i = i + 10) {

		Fn = i/Fsb;

		a = pow(Fn, 4);
		b = pow(Fn, 2);

		c = (a - (C * b) + A);
		d = b * pow((D * b - B), 2);

		R = 20 * log(a/(pow((c + d), 0.5)));
		R = abs(R);

		if (i <= 100) {
			cout << "\t " << i << "\t\t\t" << R << endl;
			outfile << i << "," << R << endl;
		} else {
			cout << "\t " << i << "\t\t" << R << endl;
			outfile << i << "," << R << endl;
		}
	}
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
void save_speaker_data(Speaker* drvr)
/*--------------------------------------------------------------------------------------------*/
/* save_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by value                                                    */
/*                         Writes the complete list of driver elements.                       */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *ptr;

	system("clear");

	cout << "Specify speaker data file: ";
	cin >> drvr_dba;

	drvr_dba = drvr_dba + ".sdb";

	ofstream outfile(drvr_dba);

	if (ptr == NULL) {
		cout << "Speaker Parts List is empty..." << endl;
		return;
	}
	else {
		ptr = drvr;  //Set the temporary pointer to the head of the list

		while (ptr != NULL) {
			outfile << ptr->Part_num << ";";
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
			outfile << ptr->Vol_seal << ";";
			outfile << ptr->Vol_vent << ";";
			outfile << ptr->f3_sealed << ";";
			outfile << ptr->f3_vent << ";";
			ptr = ptr->next;
			
			sleep(3);
		}
	}
}
/*--------------------------------------------------------------------------------------------*/
void read_speaker_data(Speaker*& drvr)
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
{
	struct Speaker *temp, *ptr;

	char line[64];
	char *token;
	
	ifstream infile;
	ifstream input;

	int i, j, k;

	string cmd_str;

	float num;
	
	drvr = NULL;;
	system("clear");
	cout << "List the available speakers..." << endl;
	cout << "+-----------------------------" << endl;

	// This is a linux/unix derived command used for all *nix based systems
	//system("ls | grep sdb | more > file_size.txt");
	system("ls | grep sdb");
	//system("awk '{print $5, $9}' file_size.txt");

	sleep(4);

	cout << "select a file from the list above..." << endl;
	cin >> drvr_dba;
	
	cmd_str = "cat " + drvr_dba + "| wc -l > drvr_lgth.txt";

	system(cmd_str.c_str());

	infile.open("drvr_lgth.txt", ios::in);

	input.open(drvr_dba, ios::in);

	temp=(struct Speaker *)malloc(sizeof(struct Speaker));

	if (temp == NULL) {
		cout << "Out of Memory Space:" << endl;
		return;
	}

	while (input >> line) {
		cout << "Data: " << line << endl;
		token = strtok(line, ";");
		strcpy(temp->Part_num, token);
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
		temp->Vol_seal = atof(token);
		token = strtok(NULL, ";");
		temp->Vol_vent = atof(token);
		token = strtok(NULL, ";");
		temp->f3_sealed = atof(token);
		token = strtok(NULL, ";");
		temp->f3_vent = atof(token);
		temp->next = NULL;
		
		sleep(2);

		drvr = temp;
		ptr=drvr;
	}
}
/*--------------------------------------------------------------------------------------------*/
