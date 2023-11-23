# Speaker_design
This is a project I am implementing to revisit data structures as well as other features of the CPP language.

This project will allow a 'user' or home speaker builder to design either a closed or vented box speaker using
data that is created from a speaker data sheet. Typically the user will use the 'build()' menu entry and fill
in the data as requested by the prompts. The user can then save the data in a S(peaker)D(esign)B(uild) or sbd
file. This is a flat-txt file in semi-colon delimited format. The user can create this file via the SpeakEasy 
application or through a spreadsheet program (excel, google sheets, etc). One speaker data sheet per file. 

When the user looks to design a loudspeaker enclosure, the use selects the speaker from the available list of 
files and read the data in. They can then choose to build either a vented or closed box design. The key parameters
that are stored/read in are Qts, Vas, Cabinet_volume (sealed/vented), f3 down point, Fs (driver resonance), 
minimum/suffested vent diameter/length.

If any of the key small/thiele values are missing (speaker volume, 3db down point or vent length/diameter), the
tool will be able to determine approximate values based on other values that are contained within the sdb file.
If the approx values do not meet with the needs of the designer, it is suggested that a more accurate data sheet be
used. For example: Accuton SS220 data sheets can be found at Accuton.com, Millerspeakers.com and 
Loudspeakerdatabase.com
