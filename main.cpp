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
#include "compute.h"
#include "menus.h"
#undef extern

 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;

/*   Global Variables   */
char t_cmd[8];                // These are all menu place holders to allow the user
char x_cmd[8];                // to choose a given item in the main or sub-menus.
char s_cmd[8];
char c_cmd[8];
char w_cmd[8];
char tw_cmd[8];
char th_cmd[8];

std::string design_file;

int xover;                    // This int is used to determine what type of 
                              // speaker is being read from the file system

double Vd;                     // driver displacement volume. Added to overall cabinet volume;
string speaker = "";

/*---------------------------------------------------------*/
int main()     
{
    /* The code below avoids the potentially messy "using namespace std" declaration */

    splash_screen();

    sleep(3);

    Speaker *pasv = NULL;
    Speaker *drvr = NULL;
    Speaker *mid = NULL;
    Speaker *tweet = NULL;
    
    
	Cabinet *pass = NULL;
    Cabinet *bass = NULL;
    Cabinet *midr = NULL;
    Cabinet *treb = NULL;

    Field_Pad *Passive = NULL;
    Field_Pad *Bass = NULL;
    Field_Pad *Midrange = NULL;
    Field_Pad *Tweeter = NULL;

    Cab_Pad *Low = NULL;
    Cab_Pad *Mid = NULL;
    Cab_Pad *High = NULL;
    Cab_Pad *LowV = NULL;

    Filter crossover;
    Filter lowpass;
    Filter bandpass;
    Filter highpass;
	
    while (strcmp(t_cmd, "Q\n") != 0) {

        strcpy(t_cmd, "");
        menu_screen();

        cin >> t_cmd;

        if ((strcmp(t_cmd, "B") == 0) || (strcmp(t_cmd, "b") == 0) || (strcmp(t_cmd, "1") == 0)) {
            build(drvr, mid, tweet, pasv);
        }

        if ((strcmp(t_cmd, "L") == 0) || (strcmp(t_cmd, "l") == 0) || (strcmp(t_cmd, "2") == 0)) {
            parts_list(drvr, mid, tweet, pasv);
        }

        if ((strcmp(t_cmd, "C") == 0) || (strcmp(t_cmd, "c") == 0) || (strcmp(t_cmd, "3") == 0)) {
		    cout << "Cabinet Design..." << endl;
			sleep(2);
            strcpy(c_cmd, "");
			while (strcmp(c_cmd, "E\n") != 0 ) {
                strcpy(c_cmd, "");
			    cabinet_screen();
                cin >> c_cmd;

                if ((strcmp(c_cmd, "1") == 0) || (strcmp(c_cmd, "S") == 0) || (strcmp(c_cmd, "s") == 0)) {

                    strcpy(w_cmd, "");
					while (strcmp(w_cmd, "E\n") != 0) {
                        cout << endl;
					    cout << HDR2 << endl;
					    cout << SUB << endl;
					    cabinet_design_screen();
					    cin >> w_cmd;

                        if ((strcmp(w_cmd, "S") == 0) || (strcmp(w_cmd, "s") == 0) || (strcmp(w_cmd, "1") == 0)) {
							closed_box_design(drvr, bass);
						    sleep(2);
					    }

                        if ((strcmp(w_cmd, "V") == 0) || (strcmp(w_cmd, "v") == 0) || (strcmp(w_cmd, "2") == 0)) {
					        cout << "In vented design space..." << endl;
							vented_box_design(drvr, bass);
							cout << "leaving vented case" << endl;
						    sleep(2);
					    }

                        if ((strcmp(w_cmd, "P") == 0) || (strcmp(w_cmd, "p") == 0) || (strcmp(w_cmd, "3") == 0)) {
					        cout << "In passive design space..." << endl;
							cout << "This feature is not implemented at this time" << endl;
							/*
							closed_box_design(drvr, bass);
							passive_box_design(pasv, bass, pass);
							*/
						    sleep(2);
					    }

                        if ((strcmp(w_cmd, "E") == 0) || (strcmp(w_cmd, "e") == 0) || (strcmp(w_cmd, "4") == 0)) {
					        cout << "Exit subwoofer design..." << endl;
						    sleep(2);
                            strcpy(w_cmd, "E\n");
					    }
					}
                }

                if (strcmp(c_cmd, "2") == 0) {

                    strcpy(tw_cmd, "");
					while (strcmp(tw_cmd, "E\n") != 0) {
					    cout << HDR2 << endl;
					    cout << DUAL << endl;
					    cabinet_design_screen();
					    cin >> tw_cmd;

                        if ((strcmp(tw_cmd, "S") == 0) || (strcmp(tw_cmd, "s") == 0) || (strcmp(tw_cmd, "1") == 0)) {
					        cout << "In sealed design space..." << endl;
							closed_box_design(drvr, bass);
							closed_box_design(tweet, treb);
						    sleep(2);
					    }

                        if ((strcmp(tw_cmd, "V") == 0) || (strcmp(tw_cmd, "v") == 0) || (strcmp(tw_cmd, "2") == 0)) {
					        cout << "In vented design space..." << endl;
							closed_box_design(drvr, bass);
							vented_box_design(tweet, treb);
						    sleep(2);
					    }

                        if ((strcmp(w_cmd, "P") == 0) || (strcmp(w_cmd, "p") == 0) || (strcmp(w_cmd, "3") == 0)) {
					        cout << "In passive design space..." << endl;
							cout << "This feature is not implemented at this time" << endl;
							/*
							closed_box_design(drvr, bass);
							passive_box_design(pasv, bass, pass);
							vented_box_design(tweet, treb);
							*/
						    sleep(2);
					    }

                        if ((strcmp(tw_cmd, "E") == 0) || (strcmp(tw_cmd, "e") == 0) || (strcmp(tw_cmd, "4") == 0)) {
					        cout << "Exit two-way speaker design..." << endl;
						    sleep(2);
                            strcpy(tw_cmd, "E\n");
					    }
                    }
				}

                if (strcmp(c_cmd, "3") == 0) {

                    strcpy(th_cmd, "");
					while (strcmp(th_cmd, "E\n") != 0) {
					    cout << HDR2 << endl;
					    cout << THREE << endl;
					    cabinet_design_screen();
					    cin >> th_cmd;

                        if ((strcmp(th_cmd, "S") == 0) || (strcmp(th_cmd, "s") == 0) || (strcmp(th_cmd, "1") == 0)) {
					        cout << "In sealed design space..." << endl;
							closed_box_design(drvr, bass);
							closed_box_design(mid, midr);
							closed_box_design(tweet, treb);
						    sleep(2);
					    }

                        if ((strcmp(th_cmd, "V") == 0) || (strcmp(th_cmd, "v") == 0) || (strcmp(th_cmd, "2") == 0)) {
					        cout << "In vented design space..." << endl;
							vented_box_design(drvr, bass);
							closed_box_design(mid, midr);
							closed_box_design(tweet, treb);
						    sleep(2);
					    }

                        if ((strcmp(w_cmd, "P") == 0) || (strcmp(w_cmd, "p") == 0) || (strcmp(w_cmd, "3") == 0)) {
					        cout << "In passive design space..." << endl;
							cout << "This feature is not implemented at this time" << endl;
							/*
							closed_box_design(drvr, bass);
							passive_box_design(pasv, bass, pass);
							closed_box_design(mid, midr);
							vented_box_design(tweet, treb);
							*/
						    sleep(2);
					    }

                        if ((strcmp(th_cmd, "E") == 1) || (strcmp(th_cmd, "e") == 0) || (strcmp(th_cmd, "4") == 0)) {
					        cout << "Exit three-way speaker design..." << endl;
						    sleep(2);
                            strcpy(th_cmd, "E\n");
					    }
                    }
                }

                if ((strcmp(c_cmd, "4") == 0) || (strcmp(c_cmd, "E") == 0) || (strcmp(c_cmd, "e") == 0)) {
                    cout << "Exit cabinet design" << endl;
		            sleep(2);
                    strcpy(c_cmd, "E\n");
                }
			}
        }

        if ((strcmp(t_cmd, "X") == 0) || (strcmp(t_cmd, "x") == 0) || (strcmp(t_cmd, "4") == 0)) {
            
            strcpy(x_cmd, "");
            while (strcmp(x_cmd, "E\n") != 0) {
				xover = 0;               // Default value for subwoofer with or without passive speaker
                crossover_screen();
		        cin >> x_cmd;

                if (strcmp(x_cmd, "1") == 0) {
                    cout << "Passive xover design - Two-way Speaker..." << endl;
					xover = 1;
		            passive_two_way(drvr, tweet, lowpass, highpass);
		            sleep(2);
                }

                if (strcmp(x_cmd, "2") == 0) {
                    cout << "Active xover design - Two-way Speaker..." << endl;
					xover = 1;
		            active_two_way(drvr, tweet, lowpass, highpass);
		            sleep(2);
                }

                if (strcmp(x_cmd, "3") == 0) {
                    cout << "Passive xover design - Three-way Speaker..." << endl;
					xover = 2;
		            passive_three_way(drvr, mid, tweet, lowpass, bandpass, highpass);
		            sleep(2);
                }

                if (strcmp(x_cmd, "4") == 0) {
                    cout << "Active xover design - Three-way Speaker..." << endl;
					xover = 2;
		            active_three_way(drvr, mid, tweet, lowpass, bandpass, highpass);
		            sleep(2);
                }

                if ((strcmp(x_cmd, "E") == 0) || (strcmp(x_cmd, "e") == 0) || (strcmp(x_cmd, "5") == 0)) {
                    cout << "Crossover design menu - Exit sub-menu..." << endl;
		            sleep(2);
                    strcpy(x_cmd, "E\n");
                }
            }
        }

        if ((strcmp(t_cmd, "G") == 0) || (strcmp(t_cmd, "g") == 0) || (strcmp(t_cmd, "5") == 0)) {
            graph_performance();
        }

        if ((strcmp(t_cmd, "S") == 0) || (strcmp(t_cmd, "s") == 0) || (strcmp(t_cmd, "6") == 0)) {
            save_speaker_data(drvr, mid, tweet, pasv);
        }

        if ((strcmp(t_cmd, "R") == 0) || (strcmp(t_cmd, "r") == 0) || (strcmp(t_cmd, "7") == 0)) {
            
	        strcpy(s_cmd, "");
            while (strcmp(s_cmd, "E\n") != 0) {
                driver_selection_screen();

		        cin >> s_cmd;

                if ((strcmp(s_cmd, "B") == 0) || (strcmp(s_cmd, "b") == 0) || (strcmp(s_cmd, "1") == 0)) {
                    cout << "Bass selection menu 1..." << endl;
					speaker = "Woof";
		            read_bass_driver(drvr);

		            sleep(2);
                }

                if ((strcmp(s_cmd, "M") == 0) || (strcmp(s_cmd, "m") == 0) || (strcmp(s_cmd, "2") == 0)) {
                    cout << "Midrange selection menu 2..." << endl;
		            read_midrange_driver(mid);

		            sleep(2);
                }

                if ((strcmp(s_cmd, "T") == 0) || (strcmp(s_cmd, "t") == 0) || (strcmp(s_cmd, "3") == 0)) {
                    cout << "Tweeter selection menu 3..." << endl;
			        read_tweet_driver(tweet);

			        sleep(2);
                }

                if ((strcmp(s_cmd, "P") == 0) || (strcmp(s_cmd, "p") == 0) || (strcmp(s_cmd, "4") == 0)) {
                    cout << "Passive Radiator selection menu 4..." << endl;
					cout << "This feature is not implemented at this time" << endl;
					/*
			        read_passive_driver(pasv);
					*/

			        sleep(2);
                }

                if ((strcmp(s_cmd, "E") == 0) || (strcmp(s_cmd, "e") == 0) || (strcmp(s_cmd, "4") == 0)) {
                    cout << "Parts menu - Exit sub-menu..." << endl;
		            sleep(2);
                    strcpy(s_cmd, "E\n");
                }
            }
        }

        if ((strcmp(t_cmd, "W") == 0) || (strcmp(t_cmd, "w") == 0) || (strcmp(t_cmd, "8") == 0)) {
            cout << "Save design data..." << endl;
			/* this function needs to be revised to add in other driver data as well */
			cout << "Enter a destination file: : ";
			cin >> design_file;
			design_file = design_file + ".doc";

			std::ofstream outfile(design_file);

			create_data_fields(pasv, Passive, outfile);
			create_data_fields(drvr, Bass, outfile);
			create_data_fields(mid, Midrange, outfile);
			create_data_fields(tweet, Tweeter, outfile);

			create_cab_fields(pass, LowV, outfile);
			create_cab_fields(bass, Low, outfile);
			create_cab_fields(midr, Mid, outfile);
			create_cab_fields(treb, High, outfile);

	        write_design_data(Passive, Bass, Midrange, Tweeter, outfile);
			////write_cabinet_data(pass, bass, midr, treb, outfile);

			/* Need a scheme to determine what kind of filter is being used */
			write_filter_data(lowpass, bandpass, highpass, xover, outfile);
        }

        if ((strcmp(t_cmd, "P") == 0) || (strcmp(t_cmd, "p") == 0) || (strcmp(t_cmd, "9") == 0)) {
            cout << "Purge driver data and read new drivers in.." << endl;
			purge_data(drvr);
			purge_data(mid);
			purge_data(tweet);
			// purge_data(pasv);
			clear_formatting(Bass);
			clear_formatting(Midrange);
			clear_formatting(Tweeter);
			//clear_formatting(Passive);
        }

        if ((strcmp(t_cmd, "Q") == 0) || (strcmp(t_cmd, "q") == 0) || (strcmp(t_cmd, "0") == 0)) {
            cout << "Terinatating program..." << endl;
            strcpy(t_cmd, "Q\n");
        }
    }

    exit_screen();

    return 0;
}
