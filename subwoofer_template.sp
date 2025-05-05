<subwoofer_title_here>
*----------------------------------------------
*	GNUCAP - NETLIST
* Each line that begins with a "*" is commented out. To comment out strings
* inline, use the ";" character. For moreinformation on what users can do with
* SPICE, there are several turorials, youtube videos and chatGPT.

.options OUT=120 
*------------- Models -------------------------
* Each Lpad has its own .param value. This allows the user to adjust 
* each Lpad in a 'real world' simulation

*------------- Power Supply -------------------
V_V1 1 0 dc 1.0 ac 1.0 sin(0 1 1000)

*------------- Circuit Description-------------
L_L1 1 2 Lxx

C_C1 2 0 Cxx

R_Sp_B 4 0 Rxx

* For a pot or Lpad, the coonections are R_Lp <pos_node> <low_node> <adjust arm>
* in this instance node(s) [5/7] go to the high or signal node, node(s) [6/8] connect
* to the pos side of the mid/tweeter speakers and node(s) [0] connect to the ground. 8 is
* the value of the lpad or potentiometer

*--- Loudspeaker Model based on T/S params ----
L_LeB 2 3 Lexx
R_ReB 3 4 Rexx

*-- Zobel Filter Values (optional based on Le --
C_Cz 4 5 0.0224994
R_Rz 5 0 6.7

*---------------- Analysis --------------------
.ac dec 100 20 50000
*.tran 0.1ms 100ms
*----------------------------------------------
*.print v(4) v(9)

.plot ac db(4)
.plot ac db(7)

*.print ac v(4)
*.print ac v(7)

*.tran 0.01ms 10ms
*.plot tran v(4)
*.plot tran v(7)

.end
