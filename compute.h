/*--------------------------------------------------------------------------------------------*/
/* compute.h - misclleaneous header file used to manage miscellaneous number manipulations    */
/* and string parsing/padding/manipulation.                                                   */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 12/19/2023:                                                                                */
/* Began code development of classes, methods and objects                                     */
/* Begin development of field_pad() functions.                                                */
/*--------------------------------------------------------------------------------------------*/
void data_field(Speaker* drvr, std::string& data_display);
/*--------------------------------------------------------------------------------------------*/
double compute_efficiency(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void cabinet_design(Speaker* drvr, Cabinet* box, std::string cab_type, std::string speaker_type);
/*--------------------------------------------------------------------------------------------*/
