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
/*                           Classes, Objects and Methods                                     */
/*--------------------------------------------------------------------------------------------*/
/* struct Speaker is the pointer for the Speaker Driver list.                                 */
/*--------------------------------------------------------------------------------------------*/
extern struct Speaker
{
	char Part_num[40];       // Product part number
	float Vas;               // Equivalent Volume of cabinet
	float Cms;               // Compliance
	float Bl;                // BL Product (aka Force Factor)
	float Qts;               // Total Q factor
	float Qes;               // Electrical Q factor
	float Qms;               // Mechanical Q factor
	float Freq_s;            // Resonant Frequency
	float Re;                // DC Resistance
	float Rms;               // Mechanical resistance
	float Z_nom;             // Nominal impedance (aka Impedance)
	float Z_min;             // Minimum Impedance
	float Z_max;             // Maximum Impedance 
	float Le;                // Voice Coil inductance (aka Lbm)
	float Xmax;              // Maximum Linear Excursion
	float Diam;              // Voice Coil Diameter
	float Nom_Pwr;           // Nominal Power (aka RMS power)
	float Max_Pwr;           // Maximum Power (aka Long-term max power)`
	float Freq_Low;          // Low-end of Freq Response
	float Freq_Hi;           // Upper limit of Frequency Response (F_low -- F_high)
	float Sensitivity;       // Sensitivity
	float Vol_seal;          // Sealed Volume (recommended)
	float Vol_vent;          // Vented Volume (recommended)
	float F3_sealed;         // 3db down point (rolloff)
	float F3_vent;           // 3db down point (rolloff)
	Speaker *next;
};
/*--------------------------------------------------------------------------------------------*/
void build(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
void parts_list(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void closed_box_design();
/*--------------------------------------------------------------------------------------------*/
void vented_box_design();
/*--------------------------------------------------------------------------------------------*/
void crossover_design();
/*--------------------------------------------------------------------------------------------*/
void graph_performance();
/*--------------------------------------------------------------------------------------------*/
void save_speaker_data(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void read_speaker_data(Speaker*& drvr);
/*--------------------------------------------------------------------------------------------*/
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
