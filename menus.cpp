/*--------------------------------------------------------------------------------------------*/
/* menus.cpp - menu and splash screen file used by Speaker_Easy program                       */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/16/2023:                                                                                */
/* Begin initial header and code development                                                  */
/*--------------------------------------------------------------------------------------------*/
/* 05/30/2023:                                                                                */
/* Finished implementing/testing/clean-up of menus, splash scren and exit screen.             */
/*--------------------------------------------------------------------------------------------*/
/* 12/10/2023:                                                                                */
/* Completed testing/debugging of driver selection (read) menu.                               */
/* Completed testing/debugging of Crossover Desgin menu.                                      */
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <forward_list>
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

using std::cin;
using std::cout;
using std::endl;

/*--------------------------------------------------------------------------------------------*/
void splash_screen()
{

    system("clear");
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    | SSSSSS                                           EEEEEE                 |" << endl;
    cout << "    | S                       k                        E                      |" << endl;
    cout << "    | S                       k                        E                      |" << endl;
    cout << "    | S                       k   k                    E                      |" << endl;
    cout << "    | SSSSSS  ppp  eee  aaa   k  k    eee  r rr  ===   EEEE   aaa   sss  y  y |" << endl;
    cout << "    |      S  p  p e  e   a   k k     e  e rr  r       E        a   s     y y |" << endl;
    cout << "    |      S  p  p eee    a   k k     exe  rr  r       E        a   s     y y |" << endl;
    cout << "    |      S  pp   e    a a   k   k   e    r           E      a a     s    y  |" << endl;
    cout << "    | SSSSSS  p    eee  aaaa  k    k  eee  r           EEEEEE aaaa  sss  y    |" << endl;
    cout << "    |         p                                                               |" << endl;
    cout << "    |         p                                                               |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
	cout << "    |                              " << VERSION << "                              |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);

}; /* end splash_screen*/
/*--------------------------------------------------------------------------------------------*/
void menu_screen()
{
    system("clear");
    cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |               Program Menu               |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (B)uild Parameters                   |" << endl;
    cout << "    |  2) (L)ist Speaker Parts                 |" << endl;
    cout << "    |  3) (C)abinet Design                     |" << endl;
    cout << "    |  4) (X)over Design                       |" << endl;
    cout << "    |  5) (G)raph Performance                  |" << endl;
    cout << "    |  6) (S)ave Speaker Data                  |" << endl;
    cout << "    |  7) (R)ead Speaker Data                  |" << endl;
    cout << "    |  8) (W)rite Design Parameters            |" << endl;
    cout << "    |  9) (P)urge                              |" << endl;
    cout << "    |  0) (Q)uit                               |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void crossover_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |          Crossover Design Menu           |" << endl;
    cout << "    |      (Use numerical selection only)      |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) 2-way - passive speaker              |" << endl;
    cout << "    |  2) 2-way - active speaker               |" << endl;
    cout << "    |  3) 3-way - passive speaker              |" << endl;
    cout << "    |  4) 3-way - active speaker               |" << endl;
    cout << "    |  5) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void driver_selection_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |          Driver Selection Menu           |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (B)ass Driver                        |" << endl;
    cout << "    |  2) (M)id-range Driver                   |" << endl;
    cout << "    |  3) (T)weeter Driver                     |" << endl;
    cout << "    |  4) (P)assive Driver                     |" << endl;
    cout << "    |  5) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void cabinet_screen()
{
    system("clear");
	cout << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    |           Cabinet Design Menu            |" << endl;
    cout << "    +------------------------------------------+" << endl;
	cout << "    |  1) (S)ub-woofer Design                  |" << endl;
	cout << "    |  2) (2)-way Speaker Design               |" << endl;
	cout << "    |  3) (3)-way Speaker Design               |" << endl;
    cout << "    |  4) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";

}
/*--------------------------------------------------------------------------------------------*/
void cabinet_design_screen()
{
    cout << "    +------------------------------------------+" << endl;
    cout << "    |  1) (S)ealed Cabinet                     |" << endl;
    cout << "    |  2) (V)ented Cabinet                     |" << endl;
    cout << "    |  3) Exit                                 |" << endl;
    cout << "    +------------------------------------------+" << endl;
    cout << "    SpeakEasy: ";
}
/*--------------------------------------------------------------------------------------------*/
void closed_design_menu()
{
        cout << "Choose design based on:" << endl;
        cout << "    1) default speaker values" << endl;
        cout << "    2) box volume" << endl;
        cout << "    3) Enter Q(tc)" << endl;
        cout << "    4) Use default value of Q(tc) = 1" << endl;
        cout << "-------------------------------------" << endl;

}
/*--------------------------------------------------------------------------------------------*/
void diffusion_menu(double &kappa)
{
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|   Select the port diffusion value:                                      |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|   diffusion value (kappa) = 0.435 : 1 flanged and 1 unflanged port      |" << endl;
    cout << "|   diffusion value (kappa) = 0.732 : 2 flanged ports - internal/external |" << endl;
    cout << "|   diffusion value (kappa) = 0.85  : 2 unflanged ports                   |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;

    cout << " kappa: ";
    cin >> kappa;

}
/*--------------------------------------------------------------------------------------------*/
double design_constant_bass_reflex(double &kappa)
{
    cout << "+-------------------------------------------------------------------------+" << endl;
	cout << "|  Standard Bass Reflex design constant:                                  |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
	cout << "| Choose the design constant from the following range of values:          |" << endl;
	cout << "| Deep Bass  design  - Br: 0.6 - 0.7                                      |" << endl;
	cout << "| Balanced design    - Br: 0.8 - 1.0                                      |" << endl;
	cout << "| High-output design - Br: 1.1 - 1.2                                      |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;

	cout << "Beta: ";
	cin >> kappa;

	return(kappa);
}
/*--------------------------------------------------------------------------------------------*/
double butterworth_constant(double &kappa)
{
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|  Butterworth design constant:                                           |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "| Choose the design constant from 0.7 <= Bb <= 0.9 (default = 0.8)        |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;

	cout << "kappa: ";
	cin >> kappa;

	return(kappa);
}
/*--------------------------------------------------------------------------------------------*/
void butterworth_cabinet_mulitplier()
{
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|  Butterworth cabient multiplier:                                        |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
	cout << "| Chose a value from 0.5 <= Sb <= 1.0 (default = 0.8)                     |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
	
	cout << "S-mulitplier: ";
}
/*--------------------------------------------------------------------------------------------*/
void bass_shelf_multiplier(int &ESB)
{
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|  Extended Bass Shelf multiplier:                                        |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "| Chose from one of the following options:                                |" << endl;
    cout << "| 1): ESB1 - Moderate bass extension - alpha = 1,25, beta = 0.7           |" << endl;
    cout << "| 2): ESB2 - Extended bass extension - alpha = 1.5, beta = 0.6            |" << endl;
    cout << "| 3): ESB3 - Maximum bass extension  - alpha = 2.0, beta = 0.5            |" << endl;
    cout << "+-------------------------------------------------------------------------+" << endl;

    cout << "ESB: ";
    cin >> ESB;
}
/*--------------------------------------------------------------------------------------------*/
void confirm_screen()
{
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    | The effective Port Length, L(eff) is less than 0, therfore the design   |" << endl;
    cout << "    | for this cabient (Volume, tuning frequency, port diameter) is incorrect.|" << endl;
    cout << "    | Retry the design with the following changes:                            |" << endl;
    cout << "    |    - Larger port diameter                                               |" << endl;
    cout << "    |    - Lower tuning frequency Fb                                          |" << endl;
    cout << "    |    - Smaller cabient volume                                             |" << endl;
    cout << "    | If the simulation is unable to find a port length for the design, it    |" << endl;
    cout << "    | may be better to try using a slotted port or a passive radiator design. |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    | If a slotted port design is being used and the port length is longer    |" << endl;
    cout << "    | than 0.5 meter (approx 19.5 inches) consider using a passive radiator.  |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void passive_screen()
{
    cout << "    +-------------------------------------------------------------------------+" << endl;
	cout << "    | The amount of weight needed to adjust the passive radiator is negative. |" << endl;
	cout << "    | Choose feom the following solutions:                                    |" << endl;
	cout << "    |    - A different passive radiator                                       |" << endl;
	cout << "    |    - A different vented design                                          |" << endl;
	cout << "    |    - A diffent bass driver.                                             |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void kappa_screen()
{
    cout << "    +-------------------------------------------------------------------------------+" << endl;
    cout << "    | Define the scalar value for the Extended Bass Shelf design. kappa ranges from |" << endl;
    cout << "    | 1.25 through 2.5 X Vas (Equivalent Cabinet Volume).                           |" << endl;
    cout << "    +-------------------------------------------------------------------------------+" << endl;
}
/*--------------------------------------------------------------------------------------------*/
void aspect_kappa(double &ar, double &kappa)
{
    cout << "    +----------------------------------------------------------------------------+" << endl;
    cout << "    | The port aspect ratio (W/H) is used to determine the over all port         |" << endl;
    cout << "    | dimensions, port wall thickness, and kappa correction factor.              |" << endl;
    cout << "    +----------------------------------------------------------------------------+" << endl;
    cout << "    | Choose from the following specified ratios to specify the port constant:   |" << endl;
    cout << "    +---------------+------------------------------------------------------------+" << endl;
    cout << "    | Aspect Ratio  |                  Port Correction Factor                    |" << endl;
    cout << "    +---------------+------------------------------------------------------------+" << endl;
    cout << "    | W:H slot type |                 Diffusion value (kappa)                    |" << endl;
    cout << "    +---------------+------------------------------------------------------------+" << endl;
    cout << "    | 1 - 2 square  |               0.435 : flanged/unflanged port               |" << endl;
    cout << "    | 3 - 5 medium  |               0.732 : 2 flanged ports                      |" << endl;
    cout << "    | 6+ long       |               0.85  : 2 unflanged ports                    |" << endl;
    cout << "    +---------------+------------------------------------------------------------+" << endl;
    cout << "    | Aspect Raio always breaks down into a x:y ratio -                          |" << endl;
    cout << "    | where y = 1, x = value from left column such as '4'.                       |" << endl;
    cout << "    +----------------------------------------------------------------------------+" << endl;

    cout << " Choose the desired aspect ratio from the left column (i.e. 4): ";
    cin >> ar;
    cout << endl;
    cout << " Specify correction factor (kappa) from the table above " << endl;
    cout << " (i.e. for a slotted port with 2 unflanged (smooth) portrs, enter 0.85) : ";
    cin >> kappa;
}
/*--------------------------------------------------------------------------------------------*/
void scalar_screen()
{

    cout << "    +-------------------------------------------------------------------------------+" << endl;
    cout << "    | Specify choose the scaling factor desired for this design:                    |" << endl;
    cout << "    | 1) Quasi-base Alignment (exended lo-freq response) : alpha  = 20, beta = 2.87 |" << endl;
    cout << "    | 2) B4 (Maximally Flat Response)                    : alpha  = 15, beta = 2.87 |" << endl;
    cout << "    | 3) Extended Base Shelf Alignment (deep low-end)    : alpha  = 25, beta = 3.3  |" << endl;
    cout << "    +-------------------------------------------------------------------------------+" << endl;

}
/*--------------------------------------------------------------------------------------------*/
void exit_screen()
{
	cout << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                 Thank you! For using Speak-Easy!                        |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    |                                                                         |" << endl;
    cout << "    +-------------------------------------------------------------------------+" << endl;

    // This is used to define the wait time to display the splash screen
    unsigned int sleep(unsigned int seconds);
    
    system("clear");
}
/*--------------------------------------------------------------------------------------------*/
