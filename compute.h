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
void cabinet_design(Speaker* drvr, Cabinet*& box, std::string cab_type, std::string speaker_type);
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
void vented_cabinet_initialize(Speaker* drvr, Speaker* pasv, double coeff, int bdesign);
/*--------------------------------------------------------------------------------------------*/
void acoustic_compliance(Speaker* drvr, double& Ca);
/*--------------------------------------------------------------------------------------------*/
void power_dynamics(Speaker* drvr, double& PAR, double& PER, double& Rh);
/*--------------------------------------------------------------------------------------------*/
void frequency_response_vented(Speaker* drvr, std::string plot);
/*--------------------------------------------------------------------------------------------*/
void port_tuning(Speaker* drvr, int val);
/*--------------------------------------------------------------------------------------------*/
void port_tuning_pr(Speaker* drvr, Speaker* pasv_cpy, Cabinet* box);
/*--------------------------------------------------------------------------------------------*/
void port_length(Speaker* drvr, double ap, double &kappa, int type);
/*--------------------------------------------------------------------------------------------*/
void port_length_slot(Speaker* drvr, double ap, double kappa);
/*--------------------------------------------------------------------------------------------*/
void port_length_pr(Speaker* drvr, Speaker* pasv_cpy, double kappa);
/*--------------------------------------------------------------------------------------------*/
void port_dynamics(Speaker* drvr, int type, double& PAR, double& PER);
/*--------------------------------------------------------------------------------------------*/
void cabinet_ripple(Speaker* drvr, Speaker* pasv_cpy, int i);
/*--------------------------------------------------------------------------------------------*/
double SolveMass(double drvr, double pr, double Fb, double Vb);
/*--------------------------------------------------------------------------------------------*/
void data_normalize(Speaker* drvr);
/*--------------------------------------------------------------------------------------------*/
void speaker_to_cabinet(Speaker* drvr, Cabinet*& box, int bdesign, double PAR, double PER, double Rh);
/*--------------------------------------------------------------------------------------------*/
