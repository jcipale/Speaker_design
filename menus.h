/*--------------------------------------------------------------------------------------------*/
/* menus.h - menu and splash screen file used by Speaker_Easy program                         */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 05/16/2023:                                                                                */
/* Begin initial header and code development                                                  */
/*--------------------------------------------------------------------------------------------*/
void splash_screen();
/*--------------------------------------------------------------------------------------------*/
void menu_screen();
/*--------------------------------------------------------------------------------------------*/
void cabinet_screen();
/*--------------------------------------------------------------------------------------------*/
void midrange_cabinet_screen();
/*--------------------------------------------------------------------------------------------*/
void crossover_screen();
/*--------------------------------------------------------------------------------------------*/
void driver_selection_screen();
/*--------------------------------------------------------------------------------------------*/
void cabinet_design_screen();
/*--------------------------------------------------------------------------------------------*/
void closed_design_menu();
/*--------------------------------------------------------------------------------------------*/
void Qtc_design_menu();
/*--------------------------------------------------------------------------------------------*/
void midrange_Qdesign_menu();
/*--------------------------------------------------------------------------------------------*/
void ribbon_design();
/*--------------------------------------------------------------------------------------------*/
void diffusion_menu(double &kappa);
/*--------------------------------------------------------------------------------------------*/
double design_constant_bass_reflex(double &kappa);
/*--------------------------------------------------------------------------------------------*/
double butterworth_constant(double &kappa);
/*--------------------------------------------------------------------------------------------*/
double butterworth_cabinet_mulitplier(double &Se);
/*--------------------------------------------------------------------------------------------*/
void bass_shelf_multiplier(int &ESB);
/*--------------------------------------------------------------------------------------------*/
void confirm_screen();
/*--------------------------------------------------------------------------------------------*/
void passive_screen();
/*--------------------------------------------------------------------------------------------*/
void kappa_screen();
/*--------------------------------------------------------------------------------------------*/
void aspect_kappa(double &ar, double &kappa);
/*--------------------------------------------------------------------------------------------*/
void scalar_screen();
/*--------------------------------------------------------------------------------------------*/
void frequency_limit_screen();
/*--------------------------------------------------------------------------------------------*/
void freq_crossover_screen();
/*--------------------------------------------------------------------------------------------*/
void inductor_selection();
/*--------------------------------------------------------------------------------------------*/
void lpad_msg(Speaker* drvr, Filter crossover, char* type);
/*--------------------------------------------------------------------------------------------*/
double gain_value();
/*--------------------------------------------------------------------------------------------*/
void exit_screen();
/*--------------------------------------------------------------------------------------------*/
