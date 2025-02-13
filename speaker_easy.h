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
    char Part_num[64];        // Product part number
    char Type[64];            // Speaker type. One of Woof, Pass, Twet or Midr
    char Build[64];           // Construction type: cone or ribbon/electrostatic
    double Vas;               // Equivalent Volume of cabinet dm^3
    double Cms;               // Compliance
    double Mms;               // Derived from Cms, Fs used primarily for Passive drivers
    double Bl;                // BL Product (aka Force Factor)
    double Qts;               // Total Q factor
    double Qes;               // Electrical Q factor
    double Qms;               // Mechanical Q factor
    double Sd;                // Effective piston area cm^2
    double Fs;                // Resonant Frequency
    double Fb;                // Port tuning Frequency
    double Re;                // DC Resistance
    double Rms;               // Mechanical resistance
    double Z_nom;             // Nominal impedance (aka Impedance)
    double Le;                // Voice Coil inductance (aka Lbm)
    double Xmax;              // Maximum Linear Excursion
    double Diam;              // Voice Coil Diameter
    double Vd;                // Speaker diameter (computed real-time from Sd).
    double Nom_Pwr;           // Nominal Power (aka RMS power)
    double Max_Pwr;           // Maximum Power (aka Long-term max power)
    double Freq_Low;          // Low-end of Freq Response
    double Freq_Hi;           // Upper limit of Frequency Response (F_low -- F_high)
    double Sensitivity;       // Sensitivity
    double Vbs;               // Sealed Volume (user define liters)
    double Vbv;               // Vented Volume (user define liters)
    double f3_seal;           // 3db down point (rolloff)
    double f3_vent;           // 3db down point (rolloff)
	double Pd;                // Port diameter - either a cylinder or slot
    double v_diam;            // vent diameter (from data sheet - default)
	double v_height;          // port height - used ONLY for slotted designs
	double v_width;           // port width - used ONLY for slotted designs
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
    char Part_num[64]; 
	char Build[64];               // Construction type: cone or ribbon/electrostatic 
	char Enclosure[64];           // Sealed or Ported
	double Cms;                   // Complianc value of the PR driver (passive radiator specifically)
	double Mms;                   // Total mass of driver (passive radiator specifically)
	double Fb;                    // Frequency of cabinet
    double vent_diam;             // Can be used for port height if used as a ducted port
    double vent_width;            // Can be used for port width if used as a ducted port
    double vent_length;
    double diam;                  // Overall basket diameter - used for designing physical cabinet
    double depth;                 // Overall driver depth - used for designing physical cabinet
	double height;                // overall driver height - used for designing physical cabinet
    double cab_volume;            // This includes the volume for ducted/ported designs as well
    double freq_lo;
    double freq_hi;
    double imp_Nom;
    double res_freq;
    double DC_resist;
	double Qt;                    // Total damping factor - Closed or Ported
    double Sensitivity;
    double rolloff;
    double crossover_lo;
    double crossover_hi;
	double Ma;                    // Mass to add for passive radiator in addition to the 
	                              // speaker mass
	double PAR;                   // Acostic power
	double PER;                   // Electirical efficiency
	double Rh;                    // 3db ripple
    double Height, Width, Depth;  // Cabinet INTERNAL measurements.
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
    double L1, L2, L3, L4;      // Inductors are NOT in use, but are kept in place for future use. 
    double C1, C2, C3, C4;
    double Fres;                // resonant frequency - used for bandpass filters only
    double f3db1, f3db2;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Field_Pad
/*--------------------------------------------------------------------------------------------*/
/* struct Field_Pad is used to format and display the values of char lengths for the fields   */
/* contained in the Speaker structure.                                                        */
/*--------------------------------------------------------------------------------------------*/
{
    char Part_num[64];       // Product part number
    char Type[64];           // Speaker type. One of Woof, Pass, Twet or Midr
	char Build[64];          // Construction type: cone or ribbon/electrostatic
    char Vas[23];            // Equivalent Volume of cabinet dm^3
    char Cms[23];            // Compliance
    char Mms[23];            // Moving mass of driver
    char Bl[23];             // BL Product (aka Force Factor)
    char Qts[23];            // Total Q factor
    char Qes[23];            // Electrical Q factor
    char Qms[23];            // Mechanical Q factor
    char Fs[23];             // Resonant Frequency
    char Re[23];             // DC Resistance
    char Rms[23];            // Mechanical resistance
    char Z_nom[23];          // Nominal impedance (aka Impedance)
    char Le[23];             // Voice Coil inductance (aka Lbm)
    char Xmax[23];           // Maximum Linear Excursion
    char Diam[23];           // Voice Coil Diameter
    char Nom_Pwr[23];        // Nominal Power (aka RMS power)
    char Max_Pwr[23];        // Maximum Power (aka Long-term max power)
    char Freq_Low[23];       // Low-end of Freq Response
    char Freq_Hi[23];        // Upper limit of Frequency Response (F_low -- F_high)
    char Sensitivity[23];    // Sensitivity
    char Vbs[23];            // Sealed Volume (user define dm^3)
    char Vbv[23];            // Vented Volume (user define dm^3)
    char f3_seal[23];        // 3db down point (rolloff)
    char f3_vent[23];        // 3db down point (rolloff)
    char v_diam[23];         // vent diameter (from data sheet - default)
    char v_length[23];       // vent length (from data sheet - default)
    char b_diam[23];         // Overall basket diameter or diaphragm width if 
	                         // ribbon - used for designing physical cabinet
    char b_height[23];       // driver height. Used primarily for ribbon tweeters. 
	                         // defaults to b_diam for mid/bass/cone tweeters
    char depth[23];          // Overall driver depth - used for designing physical cabinet
	Field_Pad *next;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Cab_Pad
/*--------------------------------------------------------------------------------------------*/
/* struct Cabinet is used to store and display the final cabinet values for the speaker design*/
/*--------------------------------------------------------------------------------------------*/
{
    char Part_num[64]; //*
	char Build[64]; //*           // Construction type: cone or ribbon/electrostatic 
	char Enclosure[23];           // Sealed or Ported
    char vent_diam[23];
    char vent_length[23];
    char diam[23]; //*              // Overall basket diameter - used for designing physical cabinet
    char depth[23]; //*             // Overall driver depth - used for designing physical cabinet
	char height[23]; //*            // overall driver height - used for designing physical cabinet
    char cab_volume[23]; //*
    char freq_lo[23];
    char freq_hi[23];
    char imp_Nom[23];
    char res_freq[23];
    char DC_resist[23];
    char Sensitivity[23];
    char rolloff[23];
    char crossover_lo[23];
    char crossover_hi[23];
	char PAR[23];                   // Acostic power
	char PER[23];                   // Electirical efficiency
	char Rh[23];                    // 3db ripple
    char Height[23], Width[23], Depth[23];
	Cab_Pad *next;
};
/*--------------------------------------------------------------------------------------------*/
/*                                         Constants                                          */
/*--------------------------------------------------------------------------------------------*/
const double C = 343.0;         // Speed of sound in m/s
const double QTC = 0.707;
const double liter_to_cubicInch = 61.0237;
const double met_to_decmet = 1000.0;
const double liter_to_cubic = 1000.0;
const double mm_to_inch = 0.0393701;
const double cm_to_mm = 10.0;
const double mm_to_m = 1000.0;
const double rho = 1.2;         // kg/m^3
const double R_WOOL = 30;       // Pa * s/m^3

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

const std::string HEADER =  "+--------";
const std::string TYPE = "| Type   ";
const int HEADR_LGTH = 9;

const std::string FIELD = "-----------------------";
const int FIELD_LGTH = 23;

const std::string VERSION = "Version 1.0.0";
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr, Speaker*& mid, Speaker*& tweet, Speaker*& pass);
/*--------------------------------------------------------------------------------------------*/
void mem_copy(Speaker*& drvr, Speaker*& drvr_cpy);
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass);
/*--------------------------------------------------------------------------------------------*/
void save_data_ptr(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr, Speaker* mid, Speaker* tweet, Speaker* pass);
/*--------------------------------------------------------------------------------------------*/
void print_part(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void print_speaker(Field_Pad* speaker, std::ofstream& output);
/*--------------------------------------------------------------------------------------------*/
void print_cabinet(Cabinet* speaker, std::ofstream& output);
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet*& box);
/*--------------------------------------------------------------------------------------------*/
void passive_box_design(Speaker*& drvr, Cabinet*& box, Cabinet*& pass);
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, double& Vbs, double& alpha, double& gamma, \
double Qa, double& Fsb, double& Vab, double& L, double& Qtc, double& Qtcp, double& fc, double& A1, 
double& f3, double& peak, double& Par, double& Per, double& Rh, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Speaker*& pasv, Speaker*& pasv_cpy, Cabinet*& bass, Cabinet*& pass);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, double& Vbv, double& Fsb, double& Fb, double& Fn, \
double& Vd, double& L_prm, double& alpha);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_response(Speaker* drvr, double Fsb, double Fb, double Fn, double alpha);
/*--------------------------------------------------------------------------------------------*/
void frequency_response(double Fb, double Fs, double Qts, double alpha, std::string plot_file, \
std::string cab_type);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_params(Speaker* drvr, double& Qa, double& gamma, double& alpha, double& A1, \
double& Fsb, double& Fcb, double& Fs, double& f3, double& Fb, double& Fc, double& L, double& Vd, \
double& Qtc, double& Qtcp, double& Vab, double& Rh, double& R, double& Par, double& Per);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_response(Speaker* drvr, double A1, double f3, double fc, double Fsb);
/*--------------------------------------------------------------------------------------------*/
void crossover_design();
/*--------------------------------------------------------------------------------------------*/
void graph_performance();
/*--------------------------------------------------------------------------------------------*/
void read_bass_driver(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
void read_midrange_driver(Speaker*& mid);
/*--------------------------------------------------------------------------------------------*/
void read_tweet_driver(Speaker*& tweet);
/*--------------------------------------------------------------------------------------------*/
//void read_passive_driver(Speaker*& pasv, Speaker*& pasv_cpy, int flag, double Sd);
void read_driver(Speaker*& drvr, Speaker*& drvr_cpy, std::string drv_type, int flag, double Sd);
/*--------------------------------------------------------------------------------------------*/
void create_data_fields(Speaker* drvr, Field_Pad*& datum, std::ofstream& outfile);
/*--------------------------------------------------------------------------------------------*/
void create_cab_fields(Cabinet* cptr, Cab_Pad*& cdatum, std::ofstream& outfile);
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
void design_low_vented(Speaker*& drvr, Speaker*& pasv, Speaker*& pasv_cpy, Cabinet*& bass, Cabinet*& pass, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void passive_check(Speaker* drvr, Speaker*& pasv, Speaker*& pasv_cpy);
/*--------------------------------------------------------------------------------------------*/
void design_tweeter_sealed(Speaker*& drvr, Cabinet*& cptr, double& Vd);
/*--------------------------------------------------------------------------------------------*/
void write_design_data(Field_Pad* P0, Field_Pad* P1, Field_Pad* P2, Field_Pad* P3, std::ofstream& outfile);
/*--------------------------------------------------------------------------------------------*/
void write_cabinet_data(Cabinet* P0, Cabinet* P1, Cabinet* P2, Cabinet* P3, std::ofstream& outfile);
/*--------------------------------------------------------------------------------------------*/
void write_filter_data(Filter low, Filter band, Filter high, int xover, std::ofstream& outfile);
/*--------------------------------------------------------------------------------------------*/
void print_crossover(Filter crossover, std::ofstream& outfile);
/*--------------------------------------------------------------------------------------------*/
void purge_data(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void clear_formatting(Field_Pad* datum);
/*--------------------------------------------------------------------------------------------*/
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
