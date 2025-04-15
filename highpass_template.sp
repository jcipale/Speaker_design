/mnt/stor1/Develop/cplus/projects/Speaker_Easy/highpass_template.oregano
*----------------------------------------------
*	GNUCAP - NETLIST
.options OUT=120 
*------------- Models -------------------------
V_V1 1 0 dc 1.0 ac 1.0 
*------------- Circuit Description-------------
C_C1 1 2 4.50877e-10
L_L1 2 0 0.000480468
R_Rl 4 0 8 
L_Le 2 3 0.42m
R_Re 3 4 6.2

*----------------------------------------------

*------------- Analysis -----------------------
.ac dec 100 20 3000
*-----------------Print/Plot ------------------
.print ac v(4)
.print ac vm(4)
.plot ac db(v(4))
* .print tran  v(3)
*.tran 0 0.005 5e-05
*.print op v(nodes)
.end
