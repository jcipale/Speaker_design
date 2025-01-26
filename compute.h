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
void tweeter_cabinet_design(Speaker* drvr, Cabinet* box);
/*--------------------------------------------------------------------------------------------*/
void center_field(char *field_data);
/*--------------------------------------------------------------------------------------------*/
double compute_qt(double Qes, double Qms);
/*--------------------------------------------------------------------------------------------*/
double convert_units(double& target, double conversion);
/*--------------------------------------------------------------------------------------------*/
double tuning_frequency(Speaker* drvr, std::string cab_type);
/*--------------------------------------------------------------------------------------------*/
double effective_port(Speaker* drvr, double Vbv, double Dp, double Fb, double kappa);
/*--------------------------------------------------------------------------------------------*/
void cabinet_initialize(Speaker* drvr, double& alpha);
/*--------------------------------------------------------------------------------------------*/
void acoustic_compliance(Speaker* drvr, double& Ca);
/*--------------------------------------------------------------------------------------------*/
void port_tuning(Speaker* drvr, int val);
/*--------------------------------------------------------------------------------------------*/
void port_tuning_pr(Speaker* drvr, Speaker* pasv_cpy);
/*--------------------------------------------------------------------------------------------*/
void port_length(Speaker* drvr, double kappa);
/*--------------------------------------------------------------------------------------------*/
void port_length_slot(Speaker* drvr, double kappa, double& height, double& width);
/*--------------------------------------------------------------------------------------------*/
void port_length_pr(Speaker* drvr, Speaker* pasv_cpy, double kappa);
/*--------------------------------------------------------------------------------------------*/
void data_normalize(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
