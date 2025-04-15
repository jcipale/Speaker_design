/mnt/stor1/Develop/cplus/projects/Speaker_Easy/subwoofer-template.oregano
*----------------------------------------------
*	GNUCAP - NETLIST
.options OUT=120 
*------------- Voltage ------------------------
V_V1 1 0 dc 1.0 ac 1.0 
*sin(0.0 1.0 1.0 0 0)
*------------- Circuit Description-------------
*L_L1 1 2 15.9m
L_L1 1 2 0.0127324
*C_C1 2 0 248.7n 
C_C1 2 0 3.16629e-07

*------------- Zobel Filter -------------------
R_Rz 4 5 6.2
C_Cz 5 0 15.6n 

*------------- Speaker Model ------------------
L_Le 2 3 0.42m
R_Re 3 4 6.2
R_Rl 4 0 8

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
*.op
.end
