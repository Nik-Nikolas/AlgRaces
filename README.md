 Algorithms races.
 Igor Lobanov. 2017

 ![](https://github.com/Nik-Nikolas/AlgRaces/blob/master/prtSc1.jpg)
![](https://github.com/Nik-Nikolas/AlgRaces/blob/master/prtSc2.jpg)


 This app allows to sort up to 5 types of numeric sequences using up to 6 sort
 algorithms simultaneously and visualize sorting processes like in real races.
 You will see algorithms work in the separate windows to easy compare 
 algorithms efficiency in real time.

 This means that you can launch up to 5 x 6 = 30 different sorting processes 
 at the same time. Each process is independent. Printing any key for active 
 window after algorithm is finished sorting will restart it's execution.

 To start - launch argRacesLauncher.exe - graphics  mode ( slow ).
 or argRacesLauncherNoGraph.exe         - pure math mode ( fast ).

 To change parameters - change start_data.txt file (must be in the folder of
 .exe files)

 start_data.txt file contains following numeric constants 
 ( order numbers shown below ):

 FIRST LINE:  NUMERIC SEQUENCE SIZE ( elements amount )

 SECOND LINE: SORTING ALGORITHMS ( algorithm number - to use certain algorithm, 
                                   0 - not to use )
    Algorithms types and related numbers:
    	(1) Bubble sort,
    	(2) Bubble sort improved,
    	(3) Shell sort,
    	(4) Selection sort,
    	(5) Quick sort,
    	(6) Heap sort

	EXAMPLE 1: "1 2 3 4 5 6" - all 6 alg.types sortings will be used.
	EXAMPLE 2: "0 6 0 0 5 0" - only Quick and Heap sortings will be used.
	

 THIRD LINE: NUMERIC SEQUENCES ( num.sequence number - to use certain num.sequence, 
                                 0 - not to use )
    Numeric sequence and related numbers:
    	(1) Random,
    	(2) Max to Min,
    	(3) Min to Max,
        (4) Max to Min to Max,
        (5) Min to Max to Min

	EXAMPLE 1: "1 2 3 4 5" - all 5 num.sequences will be used.
	EXAMPLE 2: "1 0 0 0 5" - only Random and Min to Max to Min 
                                 num.sequences will be used.

 NB! All times evaluations for graphics mode are RELATIVE because of graphics 
 time consumption effects ( graphics.h library works relatively slowly, so this 
 fact had been used as a natural DELAY function here ).



-------------------------------------------------------------------------------


 Work with graphic library Graphics.h in Code Blocks:

 WinBGIm is a BGI graphical library ported by Michael Main at the University of 
 Colorado.
 In order to connect it to the IDE Code Blocks, you must perform the following steps
 (Attention! The library is incompatible with new versions of Code Blocks, therefore 
 I recommend downloading portable
 version from codeblocks.codecutter.org).
 0. Unzip the archive. To work, run the file "CbLancher.exe" (NOT "codeblocks.exe"!)
 1. Download the graphics.h and winbgim.h files and place it in the MinGW include 
 compiler folder (for example
    C: \ Program Files \ CodeBlocks \ MinGW \ include)
 2. Download the libbgi.a file and place it in the lib folder 
 (C: \ Program Files \ CodeBlocks \ MinGW \ lib)
 3. In Code :: Blocks, open Settings >> Compiler and debugger >> Linker settings
 4. Click Add to Link libraries and load the file libbgi.a
 5. In the right part (Other linker options) insert the commands:
 6. -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
 7. Click OK.
