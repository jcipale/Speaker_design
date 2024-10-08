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
    char Part_num[128];      // Product part number
    char Type[16];           // Speaker type. One of Woof, Twet or Midr
    float Vas;               // Equivalent Volume of cabinet dm^3
    float Cms;               // Compliance
    float Bl;                // BL Product (aka Force Factor)
    float Qts;               // Total Q factor
    float Qes;               // Electrical Q factor
    float Qms;               // Mechanical Q factor
    float Fs;                // Resonant Frequency
    float Re;                // DC Resistance
    float Rms;               // Mechanical resistance
    float Z_nom;             // Nominal impedance (aka Impedance)
    float Le;                // Voice Coil inductance (aka Lbm)
    float Xmax;              // Maximum Linear Excursion
    float Diam;              // Voice Coil Diameter
    float Nom_Pwr;           // Nominal Power (aka RMS power)
    float Max_Pwr;           // Maximum Power (aka Long-term max power)
    float Freq_Low;          // Low-end of Freq Response
    float Freq_Hi;           // Upper limit of Frequency Response (F_low -- F_high)
    float Sensitivity;       // Sensitivity
    float Vbs;               // Sealed Volume (user define dm^3)
    float Vbv;               // Vented Volume (user define dm^3)
    float f3_seal;           // 3db down point (rolloff)
    float f3_vent;           // 3db down point (rolloff)
    float v_diam;            // vent diameter (from data sheet - default)
    float v_length;          // vent length (from data sheet - default)
    float b_diam;            // Overall basket diameter or diaphragm width if ribbon - used for designing physical cabinet
    float b_height;           // driver width. Used primarily for ribbon tweeters. defaults to b_diam for mid/bass/cone tweeters
    float depth;             // Overall driver depth - used for designing physical cabinet
    Speaker *next;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Cabinet
/*--------------------------------------------------------------------------------------------*/
/* struct Cabinet is used to store and display the final cabinet values for the speaker design*/
/*--------------------------------------------------------------------------------------------*/
{
    char Part_num[128];
    float vent_diam;
    float vent_length;
    float diam;              // Overall basket diameter - used for designing physical cabinet
    float depth;             // Overall driver depth - used for designing physical cabinet
	float height;            // overall driver height - used for designing physical cabinet
    float cab_volume;
    float freq_lo;
    float freq_hi;
    float imp_Nom;
    float res_freq;
    float DC_resist;
    float Sensitivity;
    float rolloff;
    float crossover_lo;
    float crossover_hi;
    float PAR;
    float PER;
    float H, W, D;
    Cabinet *next;
};
/*--------------------------------------------------------------------------------------------*/
extern struct Filter
/*--------------------------------------------------------------------------------------------*/
/* struct crossover is used to store and display the components needs for crossover design.   */
/*--------------------------------------------------------------------------------------------*/
{
    std::string xover_type;     /* sets the type of crossover network: active or passive for the final design */
    float stages;
    float gain;                 /* gain is computed by Vg = 1 + R2/R1 where R1 is significantly larger than R2 */
    float xover1, xover2;
    float FB_R1, FB_R2;         /* Feedback values used in active filter design Vg = 1 + R2/R1 where R1 -> infinity */
    float R1, R2, R3, R4;
    //float L1, L2, L3, L4;     /* Inductors are NOT in use, but are kept in place for future use. */
    float C1, C2, C3, C4;
    float Fres;                 /* resonant frequency - used for bandpass filters only */
    float f3db1, f3db2;
};
/*--------------------------------------------------------------------------------------------*/
/*    Constants                                                                               */
/*--------------------------------------------------------------------------------------------*/
const float QTC = 0.707;
const float liter_to_cubicInch = 61.0237;
const float met_to_decmet = 1000.0;
const float liter_to_cubic_cm = 1000.0;
const float mm_to_inch = 0.0393701;

const float feedback_1 = 1000000.00;
const float feedback_2 = 100.00;

const std::string HDR = "+------------------------------------------+-----------------+-------------------+";
const std::string TOWAY = "|              Driver Name                 |    Low freq     |      High freq    |";
const std::string THDR = "+------------------------------------------+------------+------------+-----------+";

const std::string HDR2 = "    +------------------------------------------+";

const std::string SUB = "    |          Sub-woofer Design Menu          |";
const std::string DUAL = "    |            Two-way Design Menu           |";
const std::string THREE =  "    |           Three-way Design Menu          |";

/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr, Speaker*& mid, Speaker*& tweet);
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr, Speaker* mid, Speaker* tweet);
/*--------------------------------------------------------------------------------------------*/
void save_data_ptr(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr, Speaker* mid, Speaker* tweet);
/*--------------------------------------------------------------------------------------------*/
void print_part(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet*& box);
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, float& Vbs, float& alpha, float& gamma, float Qa, float& Fsb, float& Vab, float& L, float& Qtc, float& Qtcp, float& fc, float& A1, float& f3, float& peak, float& Par, float& Per);
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Cabinet*& box);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_params(Speaker* drvr, float& Vbv, float& Fsb, float& Fb, float& Fn, float& Vd, float& Rh, float& Par, float& Per, float& Dv, float& Lv, float& L_prm, float& lv, float& dv, float& a, float& b, float& c, float& d, float& alpha);
/*--------------------------------------------------------------------------------------------*/
void vented_freq_response(Speaker* drvr, float Fsb, float Fb, float Fn, float alpha);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_params(Speaker* drvr, float& Qa, float& gamma, float& alpha, float& A1, float& Fsb, float& Fcb, float& Fs, float& f3, float& Fb, float& Fc, float& L, float& Vd, float& Qtc, float& Qtcp, float& Vab, float& Rh, float& R, float& Par, float& Per);
/*--------------------------------------------------------------------------------------------*/
void closed_freq_response(Speaker* drvr, float A1, float f3, float fc, float Fsb);
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
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
