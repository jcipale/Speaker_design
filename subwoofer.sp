subwoofer
*----------------------------------------------
*	GNUCAP - NETLIST
.options OUT=120 
*------------- Sources ------------------------
Vin 1 0 dc 1 ac 1.0
*------------- Models -------------------------

*------------- Circuit Description-------------
L1 1 2 15.9m
C1 2 0 248.7n
*----------------------------------------------
* Voice coil impedance
Le 2 3 0.42m
Re 3 4 6.7

* Load (speaker)
Rl 4 0 8

* Zobel network across driver
Rz1 4 5 6.2
Cz1 5 0 15.6n

*----------------  Analysis -------------------
.ac dec 100 20 3000
*-----------------Print/Plot ------------------
.print ac v(4)
.print ac vm(4)
.plot ac db(v(4))
*----------------------------------------------
.end
