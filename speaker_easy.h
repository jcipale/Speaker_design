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
/*                           Classes, Objects and Methods                                     */
/*--------------------------------------------------------------------------------------------*/
/* struct Speaker is the pointer for the Speaker Driver list.                                 */
/*--------------------------------------------------------------------------------------------*/
extern struct Speaker
{
    char Part_num[40];       // Product part number
    char Type[8];            // Speaker type. One of Woof, Twet or Midr
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
    float Z_min;             // Minimum Impedance
    float Z_max;             // Maximum Impedance 
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
    Speaker *next;
};
/*--------------------------------------------------------------------------------------------*/
extern typedef struct Cabinet
/*--------------------------------------------------------------------------------------------*/
/* struct Cabinet is used to store and display the final cabinet values for the speaker design*/
/*--------------------------------------------------------------------------------------------*/
{
	char Part_num[40];
    float vent_diam;
    float vent_length;
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
} box;
/*--------------------------------------------------------------------------------------------*/
extern typedef struct Filter
/*--------------------------------------------------------------------------------------------*/
/* struct crossover is used to store and display the components needes for crossover design.  */
/*--------------------------------------------------------------------------------------------*/
{
    float R1, R2, R3;
    float L1, L2, L3;
    float C1, C2, C3;
} crossover;
/*--------------------------------------------------------------------------------------------*/
/*    Constants                                                                               */
/*--------------------------------------------------------------------------------------------*/
const float QTC = 0.707;
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void closed_box_design(Speaker*& drvr, Cabinet& box);
/*--------------------------------------------------------------------------------------------*/
void closed_box_param_set(Speaker* drvr, int& bdesign, float& Vbs, float& alpha, float& gamma, float Qa, float& Fsb, float& Vab, float& L, float& Qtc, float& Qtcp, float& fc, float& A1, float& f3, float& peak, float& Par, float& Per);
/*--------------------------------------------------------------------------------------------*/
void vented_box_design(Speaker*& drvr, Cabinet& box);
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
void save_speaker_data(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void read_speaker_data(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
void write_design_data(Speaker* drvr, Cabinet box, Filter crossover);
/*--------------------------------------------------------------------------------------------*/
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
