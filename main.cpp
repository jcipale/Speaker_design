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
/* 12/16/2023:                                                                                */
/* Completed revising script to allow user to read in up to 3 different speakers:             */
/*     + Bass                                                                                 */
/*     + Midrange                                                                             */
/*     + Tweeter                                                                              */
/*--------------------------------------------------------------------------------------------*/
/* Created new menu selection to read in speaker type individually.                           */
/*--------------------------------------------------------------------------------------------*/
/* Revised program to name sdb file based on Part_num value and define pointer type of        */
/* (woofer, midrange or tweeter) entered speaker.                                             */
/*--------------------------------------------------------------------------------------------*/
/* Added in new structure type to report/write values of cabinet parameters and cabinet       */
/* dimensions for construction.                                                               */
/*--------------------------------------------------------------------------------------------*/
/* Added in new structure to store crossover part values per frequency response of seelcted   */
/* drivers.                                                                                   */
/*--------------------------------------------------------------------------------------------*/
/* 01/21/2024:                                                                                */
/* Final code cleanup. Reduce/remove extraneous sleep times. Commit code to github under      */
/* Ver_1.0                                                                                    */
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
//#include "compute.h"
#undef extern

#include "menus.h"
 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;

/*   Global Variables   */
char t_cmd[8];                // These are all menu place holders to allow the user
char x_cmd[8];                // to choose a given item in the main or sub-menus.
char s_cmd[8];

int sptype;                   // This int is used to determine what type of 
                              // speaker is being read from the file system

string speaker = "";

/*---------------------------------------------------------*/
int main()     
{
    /* The code below avoids the potentially messy "using namespace std" declaration */

    splash_screen();

    sleep(3);

    Speaker *drvr = NULL;
	Speaker *mid = NULL;
	Speaker *tweet = NULL;
    

	Cabinet box;
	Filter crossover;
	Filter lowpass;
	Filter bandpass;
	Filter highpass;

	//Cabinet *box;

    while (strcmp(t_cmd, "Q\n") != 0) {

        menu_screen();

        cin >> t_cmd;

        if ((strcmp(t_cmd, "P") == 0) || (strcmp(t_cmd, "p") == 0) || (strcmp(t_cmd, "1") == 0)) {
            cout << "test menu 1 - Parameters..." << endl;
            build(drvr, mid, tweet);
        }

        if ((strcmp(t_cmd, "L") == 0) || (strcmp(t_cmd, "l") == 0) || (strcmp(t_cmd, "2") == 0)) {
            cout << "test menu 2 - Avaialble Parts List..." << endl;
            parts_list(drvr, mid, tweet);
        }

        if ((strcmp(t_cmd, "C") == 0) || (strcmp(t_cmd, "c") == 0) || (strcmp(t_cmd, "3") == 0)) {
            cout << "test menu 3 - Closed Box Design..." << endl;
            closed_box_design(drvr, box);
        }

        if ((strcmp(t_cmd, "V") == 0) || (strcmp(t_cmd, "v") == 0) || (strcmp(t_cmd, "4") == 0)) {
            cout << "test menu 4. - Vented Box Design.." << endl;
            vented_box_design(drvr, box);
        }

        if ((strcmp(t_cmd, "X") == 0) || (strcmp(t_cmd, "x") == 0) || (strcmp(t_cmd, "5") == 0)) {
            cout << "test menu 5 - Xover Design..." << endl;
            
			strcpy(x_cmd, "");
            while (strcmp(x_cmd, "E\n") != 0) {
                crossover_screen();

			    cin >> x_cmd;

                if (strcmp(x_cmd, "1") == 0) {
                    cout << "Passive xover design - Two-way Speaker..." << endl;
					passive_two_way(drvr, tweet, lowpass, highpass);
					sleep(2);
                }

                if (strcmp(x_cmd, "2") == 0) {
                    cout << "Active xover design - Two-way Speaker..." << endl;
					active_two_way(drvr, tweet, lowpass, highpass);
					sleep(2);
                }

                if (strcmp(x_cmd, "3") == 0) {
                    cout << "Passive xover design - Three-way Speaker..." << endl;
					passive_three_way(drvr, mid, tweet, lowpass, bandpass, highpass);
					sleep(2);
                }

                if (strcmp(x_cmd, "4") == 0) {
                    cout << "Active xover design - Three-way Speaker..." << endl;
					active_three_way(drvr, mid, tweet, lowpass, bandpass, highpass);
					sleep(2);
                }

                if (strcmp(x_cmd, "5") == 0) {
                    cout << "Compute Speaker Volume..." << endl;
					cout << "Dummy routine - compute volume basedon cubic inches because the developer cant use the metric system" << endl;
					sleep(2);
                }

                if ((strcmp(x_cmd, "E") == 0) || (strcmp(x_cmd, "e") == 0) || (strcmp(x_cmd, "6") == 0)) {
                    cout << "xover menu - Exit sub-menu..." << endl;
					sleep(2);
                    strcpy(x_cmd, "E\n");
                }
            }
        }

        if ((strcmp(t_cmd, "G") == 0) || (strcmp(t_cmd, "g") == 0) || (strcmp(t_cmd, "6") == 0)) {
            cout << "test menu 6 - Graph Performance.." << endl;
            graph_performance();
        }

        if ((strcmp(t_cmd, "W") == 0) || (strcmp(t_cmd, "w") == 0) || (strcmp(t_cmd, "7") == 0)) {
            cout << "test menu 7 - Write Speaker Data..." << endl;
            save_speaker_data(drvr, mid, tweet);
        }

        if ((strcmp(t_cmd, "R") == 0) || (strcmp(t_cmd, "r") == 0) || (strcmp(t_cmd, "8") == 0)) {
            cout << "test menu 8 - Read Speaker Data..." << endl;
            
			strcpy(s_cmd, "");
            while (strcmp(s_cmd, "E\n") != 0) {
                driver_selection_screen();

			    cin >> s_cmd;

                if ((strcmp(s_cmd, "B") == 0) || (strcmp(s_cmd, "b") == 0) || (strcmp(s_cmd, "1") == 0)) {
                    cout << "Bass selection menu 1..." << endl;
			        sptype = 1;
					read_bass_driver(drvr);
					sleep(2);
                }

                if ((strcmp(s_cmd, "M") == 0) || (strcmp(s_cmd, "m") == 0) || (strcmp(s_cmd, "2") == 0)) {
                    cout << "Midrange selection menu 2..." << endl;
			        sptype = 2;
					read_midrange_driver(mid);
					sleep(2);
                }

                if ((strcmp(s_cmd, "T") == 0) || (strcmp(s_cmd, "t") == 0) || (strcmp(s_cmd, "3") == 0)) {
                    cout << "Tweeter selection menu 3..." << endl;
			        sptype = 3;
					read_tweet_driver(tweet);
					sleep(2);
                }

                if ((strcmp(s_cmd, "E") == 0) || (strcmp(s_cmd, "e") == 0) || (strcmp(s_cmd, "4") == 0)) {
                    cout << "Parts menu - Exit sub-menu..." << endl;
					sleep(2);
                    strcpy(s_cmd, "E\n");
                }
            }
        }

        if ((strcmp(t_cmd, "D") == 0) || (strcmp(t_cmd, "d") == 0) || (strcmp(t_cmd, "9") == 0)) {
            cout << "test menu 9 - Save design parameters..." << endl;
			write_design_data(drvr, box, lowpass, bandpass, highpass);
        }

        if ((strcmp(t_cmd, "Q") == 0) || (strcmp(t_cmd, "q") == 0) || (strcmp(t_cmd, "0") == 0)) {
            cout << "test menu 0 - Quit program..." << endl;
            strcpy(t_cmd, "Q\n");
        }
    }

    exit_screen();

    return 0;
}
