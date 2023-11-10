/*--------------------------------------------------------------------------------------------*/
/* SpeakerEasy - a command-line driven program to compute and plot speaker response data from */
/*               user-input daya or from stored speaker data contained within a soeaker data  */
/*               base file stored co-located with the applicatin itself.                      */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/13/2023:                                                                                */
/* Begin initial cide development.                                                            */
/*--------------------------------------------------------------------------------------------*/
/* 05/20/2023:                                                                                */
/* Cleanup use of namespace with std::cout and std::endl.                                     */
/* Begin coding main menu body and pointer initilization method.                              */
/*--------------------------------------------------------------------------------------------*/
/* 05/28/2023:                                                                                */
/* Completed declaration of structure/linked list.                                            */
/* Implemented first pass version of main menu.                                               */
/* revised and corrected library calls across all files.                                      */
/*--------------------------------------------------------------------------------------------*/
/* 07/06/2023:                                                                                */
/* Revised data input command. Repalced fgets90 with cin(). Removed 'carriage return' from    */
/* if-then-else menu construct.                                                               */
/*--------------------------------------------------------------------------------------------*/
/* 11/07/2023:                                                                                */
/* Globally - clean up debug and print statements to track intermediate data values. Need to  */
/* upload finished closed_box() to github for code checkin.                                   */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
     
#define extern
#include "speaker_easy.h"
#undef extern

#include "menus.h"
 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;

/*   Global Variables   */
char t_cmd[8];

/*---------------------------------------------------------*/
int main()     
{
    /* The code below avoids the potentially messy "using namespace std" declaration */

	splash_screen();

	sleep(3);

	Speaker *drvr = NULL;

    while (strcmp(t_cmd, "E\n") != 0) {

		menu_screen();

		cout << "SpeakEasy: ";
		
		cin >> t_cmd;

        if ((strcmp(t_cmd, "S") == 0) || (strcmp(t_cmd, "s") == 0) || (strcmp(t_cmd, "1") == 0)) {
			cout << "test menu 1 - Speaker Parameters..." << endl;
			build(drvr);
		}

		if ((strcmp(t_cmd, "L") == 0) || (strcmp(t_cmd, "l") == 0) || (strcmp(t_cmd, "2") == 0)) {
			cout << "test menu 2 - Avaialble Parts List..." << endl;
			parts_list(drvr);
		}

		if ((strcmp(t_cmd, "C") == 0) || (strcmp(t_cmd, "c") == 0) || (strcmp(t_cmd, "3") == 0)) {
			cout << "test menu 3 - Closed Box Design..." << endl;
			closed_box_design(drvr);
		}

		if ((strcmp(t_cmd, "V") == 0) || (strcmp(t_cmd, "v") == 0) || (strcmp(t_cmd, "4") == 0)) {
			cout << "test menu 4. - Vented Box Design.." << endl;
			vented_box_design(drvr);
		}

		if ((strcmp(t_cmd, "X") == 0) || (strcmp(t_cmd, "x") == 0) || (strcmp(t_cmd, "5") == 0)) {
			cout << "test menu 5 - Xover Design..." << endl;
			crossover_design();
		}

		if ((strcmp(t_cmd, "G") == 0) || (strcmp(t_cmd, "g") == 0) || (strcmp(t_cmd, "6") == 0)) {
			cout << "test menu 6 - Graph Performance.." << endl;
			graph_performance();
		}

		if ((strcmp(t_cmd, "W") == 0) || (strcmp(t_cmd, "w") == 0) || (strcmp(t_cmd, "7") == 0)) {
			cout << "test menu 7 - Write Speaker Data..." << endl;
			save_speaker_data(drvr);
		}

		if ((strcmp(t_cmd, "R") == 0) || (strcmp(t_cmd, "r") == 0) || (strcmp(t_cmd, "8") == 0)) {
			cout << "test menu 8 - Read Speaker Data..." << endl;
			read_speaker_data(drvr);
		}

		if ((strcmp(t_cmd, "E") == 0) || (strcmp(t_cmd, "e") == 0) || (strcmp(t_cmd, "9") == 0)) {
			cout << "test menu 9 - Exit program..." << endl;
			strcpy(t_cmd, "E\n");
		}
	}

	exit_screen();

	return 0;
}
