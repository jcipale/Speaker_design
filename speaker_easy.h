/*--------------------------------------------------------------------------------------------*/
/* speaker_easy.h - Primary header file used to manages data structures and global variables. */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/15/2023:                                                                                */
/* Began code development of classes, methods and objects                                     */
/*--------------------------------------------------------------------------------------------*/
/* 05/29/2023:                                                                                */
/* Completed definition of struct and method calls (stubs).                                   */
/*--------------------------------------------------------------------------------------------*/
/* 11/16/2023:                                                                                */   
/* Implement parameter display for final approved cabinbet design.                            */   
/* Implement structures for crossover design.                                                 */   
/* Implement functions to design crossover based on 2,3,4 way speaker                         */   
/*--------------------------------------------------------------------------------------------*/
/* 12/16/2023:                                                                                */
/* Added, revised and tested the following functions:                                         */
/*    build()                                                                                 */
/*    save_speaker_data()                                                                     */
/*    parts_list()                                                                            */
/*    read_bass_driver()/read_midrange_driver()/read_tweeter_driver()                         */
/*--------------------------------------------------------------------------------------------*/
/*                           Classes, Objects and Methods                                     */
/*--------------------------------------------------------------------------------------------*/
/* struct Speaker is the pointer for the Speaker Driver list.                                 */
/*--------------------------------------------------------------------------------------------*/
extern struct Speaker
{
    char Part_num[128];       // Product part number
    char Type[16];            // Speaker type. One of Woof, Pass, Twet or Midr
    char Build[16];           // Construction type: cone or ribbon/electrostatic
    double Vas;               // Equivalent Volume of cabinet dm^3
    double Cms;               // Compliance
    double Bl;                // BL Product (aka Force Factor)
    double Qts;               // Total Q factor
    double Qes;               // Electrical Q factor
    double Qms;               // Mechanical Q factor
    double Fs;                // Resonant Frequency
    double Re;                // DC Resistance
    double Rms;               // Mechanical resistance
    double Z_nom;             // Nominal impedance (aka Impedance)
    double Le;                // Voice Coil inductance (aka Lbm)
    double Xmax;              // Maximum Linear Excursion
    double Diam;              // Voice Coil Diameter
    double Nom_Pwr;           // Nominal Power (aka RMS power)
    double Max_Pwr;           // Maximum Power (aka Long-term max power)
    double Freq_Low;          // Low-end of Freq Response
    double Freq_Hi;           // Upper limit of Frequency Response (F_low -- F_high)
    double Sensitivity;       // Sensitivity
    double Vbs;               // Sealed Volume (user define dm^3)
    double Vbv;               // Vented Volume (user define dm^3)
    double f3_seal;           // 3db down point (rolloff)
    double f3_vent;           // 3db down point (rolloff)
    double v_diam;            // vent diameter (from data sheet - default)
    double v_length;          // vent length (from data sheet - default)
    double b_diam;            // Overall basket diameter or diaphragm width if 
	                      // ribbon - used for designing physical cabinet
    double b_height;          // driver height. Used primarily for ribbon tweeters. 
	                      // defaults to b_diam for mid/bass/cone tweeters
    double depth;             // Overall driver depth - used for designing physical cabinet
    Speaker *next;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Cabinet
/*--------------------------------------------------------------------------------------------*/
/* struct Cabinet is used to store and display the final cabinet values for the speaker design*/
/*--------------------------------------------------------------------------------------------*/
{
    char Part_num[128]; //*
    char Build[16]; //*           // Construction type: cone or ribbon/electrostatic 
    double vent_diam;
    double vent_length;
    double diam; //*              // Overall basket diameter - used for designing physical cabinet
    double depth; //*             // Overall driver depth - used for designing physical cabinet
    double height; //*            // overall driver height - used for designing physical cabinet
    double cab_volume; //*
    double freq_lo;
    double freq_hi;
    double imp_Nom;
    double res_freq;
    double DC_resist;
    double Sensitivity;
    double rolloff;
    double crossover_lo;
    double crossover_hi;
    double PAR;                   // Acostic power
    double PER;                   // Electirical efficiency
    double Rh;                    // 3db ripple
    double H, W, D;
    Cabinet *next;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Filter
/*--------------------------------------------------------------------------------------------*/
/* struct crossover is used to store and display the components needs for crossover design.   */
/*--------------------------------------------------------------------------------------------*/
{
    std::string xover_type;     // sets the type of crossover network: active or passive for 
	                            // the final design
    double stages;
    double gain;                // gain is computed by Vg = 1 + R2/R1 where R1 is significantly 
	                            // larger than R2 
    double xover1, xover2;
    double FB_R1, FB_R2;        // Feedback values used in active filter design Vg = 1 + R2/R1 
	                            // where R1 -> infinity 
    double R1, R2, R3, R4;
    //double L1, L2, L3, L4;    // Inductors are NOT in use, but are kept in place for future use. 
    double C1, C2, C3, C4;
    double Fres;                // resonant frequency - used for bandpass filters only
    double f3db1, f3db2;
};
/*--------------------------------------------------------------------------------------------*/
/*    Constants                                                                               */
/*--------------------------------------------------------------------------------------------*/
const double C = 343.0;         // Speed of sound in m/s
const double QTC = 0.707;
const double liter_to_cubicInch = 61.0237;
const double met_to_decmet = 1000.0;
const double liter_to_cubic_cm = 1000.0;
const double mm_to_inch = 0.0393701;

const double feedback_1 = 1000000.00;
const double feedback_2 = 100.00;

const double BUFFER = 2.54;     // Default units are in metric units (this is centimeter)

const std::string HDR = "+------------------------------------------+-----------------+-------------------+";
const std::string TOWAY = "|              Driver Name                 |    Low freq     |      High freq    |";
const std::string THDR = "+------------------------------------------+------------+------------+-----------+";

const std::string HDR2 = "    +------------------------------------------+";

const std::string SUB = "    |          Sub-woofer Design Menu          |";
const std::string DUAL = "    |            Two-way Design Menu           |";
const std::string THREE =  "    |           Three-way Design Menu          |";

/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr, Speaker*& mid, Speaker*& tweet, Speaker*& pass);
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass);
/*--------------------------------------------------------------------------------------------*/
void save_data_ptr(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass);
/*--------------------------------------------------------------------------------------------*/
void print_part(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet*& box);
/*--------------------------------------------------------------------------------------------*/
void passive_box_design(Speaker*& drvr, Cabinet*& box, Cabinet*& pass);
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, double& Vbs, double& alpha, double& gamma, double Qa, double& Fsb, double& Vab, double& L, double& Qtc, double& Qtcp, double& fc, double& A1, double& f3, double& peak, double& Par, double& Per, double& Rh, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Cabinet*& box);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, double& Vbv, double& Fsb, double& Fb, double& Fn, double& Vd, double& Rh, double& Par, double& Per, double& L_prm, double& a, double& b, double& c, double& d, double& alpha);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_response(Speaker* drvr, double Fsb, double Fb, double Fn, double alpha);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_params(Speaker* drvr, double& Qa, double& gamma, double& alpha, double& A1, double& Fsb, double& Fcb, double& Fs, double& f3, double& Fb, double& Fc, double& L, double& Vd, double& Qtc, double& Qtcp, double& Vab, double& Rh, double& R, double& Par, double& Per);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_response(Speaker* drvr, double A1, double f3, double fc, double Fsb);
/*--------------------------------------------------------------------------------------------*/
void crossover_design();
/*--------------------------------------------------------------------------------------------*/
void graph_performance();
/*--------------------------------------------------------------------------------------------*/
//void read_bass_driver(Speaker*& drvr,  std::string& speaker);
void read_bass_driver(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
void read_midrange_driver(Speaker*& mid);
/*--------------------------------------------------------------------------------------------*/
void read_tweet_driver(Speaker*& tweet);
/*--------------------------------------------------------------------------------------------*/
void read_passive_driver(Speaker*& passive);
/*--------------------------------------------------------------------------------------------*/
void write_design_data(Speaker* drvr, Cabinet* box, Filter lowpass, Filter bandpass, Filter highpass);
/*--------------------------------------------------------------------------------------------*/
void passive_two_way(Speaker* drvr, Speaker* tweet, Filter& lowpass, Filter& highpass);
/*--------------------------------------------------------------------------------------------*/
void passive_three_way(Speaker* drvr, Speaker* mid, Speaker* tweet, Filter& lowpass, Filter& bandpass, Filter& highpass);
/*--------------------------------------------------------------------------------------------*/
void active_two_way(Speaker* drvr, Speaker* tweet, Filter& lowpass, Filter& highpass);
/*--------------------------------------------------------------------------------------------*/
void active_three_way(Speaker* drvr, Speaker* mid, Speaker* tweet, Filter& lowpass, Filter& bandpass, Filter& highpass);
/*--------------------------------------------------------------------------------------------*/
void design_low_sealed(Speaker*& drvr, Cabinet*& box, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void design_low_vented(Speaker*& drvr, Cabinet*& box, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void design_tweeter_sealed(Speaker*& drvr, Cabinet*& box, double& Vd);
/*--------------------------------------------------------------------------------------------*/
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
