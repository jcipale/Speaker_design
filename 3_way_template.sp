<3_way_title_here>
*----------------------------------------------
*	GNUCAP - NETLIST
.options OUT=120 
*------------- Models -------------------------
* Each Lpad has its own .param value. This allows the user to adjust 
* each Lpad in a 'real world' simulation
.param R_pot_M=8
.param position_M=0.5

.param R_pot_T=8
.param position_T=0.9

*------------- Power Supply -------------------
V_V1 1 0 dc 1.0 ac 1.0 sin(0 1 1000)

*------------- Circuit Description-------------
*R_Rb 4 0 X  ;Load resistors to smooth out freq response
*R_Rm 6 0 X  ;Load resistors to smooth out freq response
*R_Rt 6 0 X  ;Load resistors to smooth out freq response


L_L1 1 2 0.001
L_L2 1 5 0.001
L_L3 6 0 1e-06
L_L4 10 0 1e-06

C_C1 2 0 7.40111e-06
C_C2 5 0 7.40111e-06
C_C3 5 6 0.000727673
C_C4 1 10 0.000727673

* For a pot or Lpad, the coonections are R_Lp <pos_node> <low_node> <adjust arm>
* in this instance node(s) [5/7] go to the high or signal node, node(s) [6/8] connect
* to the pos side of the mid/tweeter speakers and node(s) [0] connect to the ground. 8 is
* the value of the lpad or potentiometer

* Lpad connection template

*----- Lpad circuitry used for Mid/Tweet ------
R_Lp_M1_top 6 7 {R_pot_M * position_M}
R_Lp_M1_bottom 7 0 {R_pot_M * (1 - position_M)}

R_Lp_T1_top 10 11 {R_pot_T * position_T}
R_Lp_T1_bottom 11 0 {R_pot_T * (1 - position_T)}

*--- Loudspeaker Model based on T/S params ----
L_LeB 2 3 0.42
R_ReB 3 4 6.7

L_LeM 7 8 0.11
R_ReM 8 9 6.2

L_LeT 11 12 0.11
R_ReT 12 13 6.2

R_Sp_B1 4 0 8
R_Sp_M1 9 0 8
R_Sp_T1 13 0 8

*---------------- Analysis --------------------
.ac dec 100 20 50000
*.tran 0.1ms 100ms
*----------------------------------------------
*.op
*.print v(2) v(6) v(8)
.plot ac vm(4)
*.plot ac vm(6)
*.plot ac vm(8)

.plot ac db(4)
.plot ac db(9)
.plot ac db(13)

*.print ac v(2)
*.print ac v(6)
*.print ac v(8)
*.plot ac db(v(2) v(4) v(5))

*.tran 0.01ms 10ms
*.plot tran v(4)
*.plot tran v(6)
*.plot tran v(8)

.end
