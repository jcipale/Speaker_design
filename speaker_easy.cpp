/*--------------------------------------------------------------------------------------------*/
/* speaker_easy.cpp - Primary code file than manages classes, methods and functions.          */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/21/2023:                                                                                */
/* Began code development of classes, methods and objects.                                    */
/*                                                                                            */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
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

/*--------------------------------------------------------------------------------------------*/
/*                               Functions and Procedures                                     */
/*--------------------------------------------------------------------------------------------*/
/* The build() function builds the list of available parts that the user can select from to   */
/* design/build/simualte a speaker design with. The user is prompted to enter various part    */
/* values at the CLI prompts. The information is stored in an FIFO linked list.               */
/* Input: Struct Speaker - passed by reference                                                */
/*                         Adds multiple links if needed by user.                             */
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr) {
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
	scanf("%s",&temp->Part_num);
	cout << "	Vas (ft^3)             : ";
	scanf("%f",&temp->Vas);
	cout << "	Compliance             : ";
	scanf("%f",&temp->Cms);
	cout << "	BL (Force Factor)      : ";
	scanf("%f",&temp->Bl);
	cout << "	Qts (Total Q factor)   : ";
	scanf("%f",&temp->Qts);
	cout << "	Qes (Electric Q factor): ";
	scanf("%f",&temp->Qes);
	cout << "	Qms (Mech Q factor)    : ";
	scanf("%f",&temp->Qms);
	cout << "	Freq_s                 : ";
	scanf("%f",&temp->Freq_s);
	cout << "	Re (ohms)              : ";
	scanf("%f",&temp->Re);
	cout << "	RMS (kg/s)             : ";
	scanf("%f",&temp->Rms);
	cout << "	Z_nom (Nom Impedance)  : ";
	scanf("%f",&temp->Z_nom);
	cout << "	Z_min (Min Impedance)  : ";
	scanf("%f",&temp->Z_min);
	cout << "	Z_max (Max Impedance)  : ";
	scanf("%f",&temp->Z_max);
	cout << "	Le (mH)                : ";
	scanf("%f",&temp->Le);
	cout << "	Xmax (mm)              : ";
	scanf("%f",&temp->Xmax);
	cout << "	Diam (in)              : ";
	scanf("%f",&temp->Diam);
	cout << "	Nom_Pwr (W)            : ";
	scanf("%f",&temp->Nom_Pwr);
	cout << "	Max_Pwr (W)            : ";
	scanf("%f",&temp->Max_Pwr);
	cout << "	Freq_Low (Hz)          : ";
	scanf("%f",&temp->Freq_Low);
	cout << "	Freq_Hi (Hz)           : ";
	scanf("%f",&temp->Freq_Hi);
	cout << "	Sensitivity (db 1w/1m) : ";
	scanf("%f",&temp->Sensitivity);
	cout << "	Vol_seal (m^3)         : ";
	scanf("%f",&temp->Vol_seal);
	cout << "	Vol_vented (m^3)       : ";
	scanf("%f",&temp->Vol_vent);
	cout << "	F3_sealed (3db rolloff): ";
	scanf("%f",&temp->F3_sealed);
	cout << "	F3_vent (3db rolloff)  : ";
	scanf("%f",&temp->F3_vent);
	temp->next = NULL;

	drvr = temp;
	ptr=drvr;
}
/*--------------------------------------------------------------------------------------------*/
/* The parts_list function simply traverse the current list in a one-way direction. The user  */
/* has the option of saving changes to the list or closing out the application with no changes*/
/* made to the parts list. The user can chose the speaker from the available parts listing and*/
/* perform a simulation given the parameters of the selected speaker.                         */
/* Input: Struct Speaker - passed by value                                                    */
/*                         Prints the complete list of driver elements.                       */
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr) {

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
			cout << "Freq_s     : " << ptr->Freq_s << endl;
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
			cout << "F3_sealed  : " << ptr->F3_sealed << endl;
			cout << "F3_vent    : " << ptr->F3_vent << endl;
			ptr = ptr->next;
			cout << "+-----------------------------" << endl;
			
			sleep(2);
		}
	}
}
/*--------------------------------------------------------------------------------------------*/
void closed_box_design() {
	system("clear");
	cout << "Design a closed box speaker..." << endl;
}
/*--------------------------------------------------------------------------------------------*/
void vented_box_design() {
	struct Speaker *ptr;

	float Vb, Fb, Fh;

	system("clear");
	cout << "Design a vented box speaker..." << endl;
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
/* save_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by value                                                    */
/*                         Writes the complete list of driver elements.                       */
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr) {

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
			outfile << ptr->Freq_s << ";";
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
			outfile << ptr->F3_sealed << ";";
			outfile << ptr->F3_vent << ";";
			ptr = ptr->next;
			
			sleep(3);
		}
	}
}
/*--------------------------------------------------------------------------------------------*/
/* read_speaker_data is used to write the contents of the speaker list to a file on locally or*/
/* on the network drive.                                                                      */
/* Input: Struct Speaker - passed by reference                                                */
/*                         reads the complete list of driver elements.                        */
/*--------------------------------------------------------------------------------------------*/
void read_speaker_data(Speaker*& drvr) {

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
		//cout << "DBG: Part_num    : " << temp->Part_num << endl;
		token = strtok(NULL, ";");
		temp->Vas = atof(token);
		//cout << "DBG: Vas         : " << temp->Vas << endl;
		token = strtok(NULL, ";");
		temp->Cms = atof(token);
		//cout << "DBG: Cms         : " << temp->Cms << endl;
		token = strtok(NULL, ";");
		temp->Bl = atof(token);
		//cout << "DBG: Bl         : " << temp->Bl << endl;
		token = strtok(NULL, ";");
		temp->Qts = atof(token);
		//cout << "DBG: Qts         : " << temp->Qts << endl;
		token = strtok(NULL, ";");
		temp->Qes = atof(token);
		//cout << "DBG: Qes         : " << temp->Qes << endl;
		token = strtok(NULL, ";");
		temp->Qms = atof(token);
		//cout << "DBG: Qms         : " << temp->Qms << endl;
		token = strtok(NULL, ";");
		temp->Freq_s = atof(token);
		//cout << "DBG: Freq_s      : " << temp->Freq_s << endl;
		token = strtok(NULL, ";");
		temp->Re = atof(token);
		//cout << "DBG: Re          : " << temp->Re << endl;
		token = strtok(NULL, ";");
		temp->Rms = atof(token);
		//cout << "DBG: Rms          : " << temp->Rms << endl;
		token = strtok(NULL, ";");
		temp->Z_nom = atof(token);
		//cout << "DBG: Z_nom          : " << temp->Z_nom << endl;
		token = strtok(NULL, ";");
		temp->Z_min = atof(token);
		//cout << "DBG: Z_min          : " << temp->Z_min << endl;
		token = strtok(NULL, ";");
		temp->Z_max = atof(token);
		//cout << "DBG: Z_max          : " << temp->Z_max << endl;
		token = strtok(NULL, ";");
		temp->Le = atof(token);
		//cout << "DBG: Le          : " << temp->Le << endl;
		token = strtok(NULL, ";");
		temp->Xmax = atof(token);
		//cout << "DBG: Xmax        : " << temp->Xmax << endl;
		token = strtok(NULL, ";");
		temp->Diam = atof(token);
		//cout << "DBG: Diam        : " << temp->Diam << endl;
		token = strtok(NULL, ";");
		temp->Nom_Pwr = atof(token);
		//cout << "DBG: Nom_Pwr     : " << temp->Nom_Pwr << endl;
		token = strtok(NULL, ";");
		temp->Max_Pwr = atof(token);
		//cout << "DBG: Max_Pwr     : " << temp->Max_Pwr << endl;
		token = strtok(NULL, ";");
		temp->Freq_Low = atof(token);
		//cout << "DBG: Freq_Low    : " << temp->Freq_Low << endl;
		token = strtok(NULL, ";");
		temp->Freq_Hi = atof(token);
		//cout << "DBG: Freq_Low    : " << temp->Freq_Low << endl;
		token = strtok(NULL, ";");
		temp->Sensitivity = atof(token);
		//cout << "DBG: Sensitivity : " << temp->Sensitivity << endl;
		token = strtok(NULL, ";");
		temp->Vol_seal = atof(token);
		token = strtok(NULL, ";");
		temp->Vol_vent = atof(token);
		token = strtok(NULL, ";");
		temp->F3_sealed = atof(token);
		token = strtok(NULL, ";");
		temp->F3_vent = atof(token);
		temp->next = NULL;
		
		sleep(2);

		drvr = temp;
		ptr=drvr;
	}
}
/*--------------------------------------------------------------------------------------------*/
