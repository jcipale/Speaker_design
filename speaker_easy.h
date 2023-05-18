/*--------------------------------------------------------------------------------------------*/
/* speaker_easy.h - Primary header file used to manages data structures and global variables. */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/15/2023:                                                                                */
/* Began code development of classes, methods and objects
/*--------------------------------------------------------------------------------------------*/

struct driver {
	char Part_num[20];
	float Vol_box;
	float Vas;
	float Qts;
	float Qes;
	float Qms;
	float Freq_s;
	float Re;
	float Le;
	float Xmax;
	float Diam;
	float Nom_Imp;
	float Nom_Pwr;
	float Max_Pwr;
	float Freq_Low;
	float Freq_Hi;
	float Sensitivuty;
	struct driver *nxt_driver;
};
/*--------------------------------------------------------------------------------------------*/
/*                                 end of speaker_easy.h                                      */
/*--------------------------------------------------------------------------------------------*/
