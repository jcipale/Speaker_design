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
/* 03/18/2025:                                                                                */
/* completed revision of frequency_response_sealed() and frequency_response_vented().         */
/* Revised port_tuning for vented/slottted and passive radiators.                             */
/* Revised cabinet ripple r(h) and solved math errors.                                        */
/*--------------------------------------------------------------------------------------------*/
void data_field(Speaker* drvr, std::string& data_display);
/*--------------------------------------------------------------------------------------------*/
double compute_efficiency(Speaker* drvr, double type);
/*--------------------------------------------------------------------------------------------*/
void cabinet_design(Speaker* drvr, Cabinet*& cptr, std::string cab_type);
/*--------------------------------------------------------------------------------------------*/
void center_field(char *field_data);
/*--------------------------------------------------------------------------------------------*/
double compute_qt(double Qes, double Qms);
/*--------------------------------------------------------------------------------------------*/
double convert_units(double& target, double conversion);
/*--------------------------------------------------------------------------------------------*/
double effective_port(Speaker* drvr, double Vbv, double Dp, double Fb, double kappa);
/*--------------------------------------------------------------------------------------------*/
void vented_cabinet_initialize(Speaker* drvr, Speaker* pasv, double coeff, int bdesign);
/*--------------------------------------------------------------------------------------------*/
void power_dynamics(Speaker* drvr, int type);
/*--------------------------------------------------------------------------------------------*/
void frequency_response_sealed(Speaker* drvr, double Qtc, std::string plot);
/*--------------------------------------------------------------------------------------------*/
void high_frequency_sealed(Speaker* drvr, double Qtc, std::string plot);
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
void speaker_to_cabinet(Speaker* drvr, Cabinet*& box, std::string cab_type, int bdesign);
/*--------------------------------------------------------------------------------------------*/
double solve_inductance(Speaker* drvr, int freq);
/*--------------------------------------------------------------------------------------------*/
double solve_capacitance(Speaker* drvr, int freq);
/*--------------------------------------------------------------------------------------------*/
