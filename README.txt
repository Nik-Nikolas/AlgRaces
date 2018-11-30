// Algorithms races.
// Igor Lobanov. 2017
//
// Program allows to sort up to 5 types of numeric sequences using up to 6 sort
// algorithms simultaneously 
// and visualize sorting processes like in real races.
// This means that you can launch up to 5 x 6 = 30 different sorting processes at the
// same time.
//
//
// To start - launch argRacesLauncher.exe - graphics  mode ( slow ).
// or argRacesLauncherNoGraph.exe         - pure math mode ( fast ).
//
// Launcher launches up to 30 applications (user can see algorithms work in the
// separate windows to easy compare algorithms efficiency in real time).
//
// To change parameters - change start_data.txt file (must be in the folder of
// .exe files)
// This .txt file contains following numeric constants ( order numbers shown below ):
//
// FIRST LINE:  #1 - NUMERIC SEQUENCE SIZE ( elements )
//
// SECOND LINE: #2, 3, 4, 5, 6, 7 - SORTING ALGORITHMS ( algorithm number - to use certain algorithm, 0 - not to use )
//    Algorithms types and related numbers ( in order from 2 to 7 ):
//    	(1) Bubble sort,
//    	(2) Bubble sort improved,
//    	(3) Shell sort,
//    	(4) Selection sort,
//    	(5) Quick sort,
//    	(6) Heap sort
//
// THIRD LINE: #8, 9, 10, 11, 12 - NUMERIC SEQUENCES ( array type number - to use certain array type, 0 - not to use )
//    Arrays types and related numbers ( in order from 8 to 12 ):
//    	(1) Random,
//    	(2) Max to Min,
//    	(3) Min to Max,
//      (4) Max to Min to Max,
//      (5) Min to Max to Min
//
// Printing any key after algorithm is finished sorting will restart it's execution.
//
// NB! All times evaluations for graphics mode are RELATIVE because of graphics time consumption effects
// ( graphics.h library works relatively slowly, so this fact had been used as a natural DELAY function here ).
//
//
//
//
//
//
// Work with graphic library Graphics.h in Code Blocks:
//
// WinBGIm is a BGI graphical library ported by Michael Main at the University of Colorado.
// In order to connect it to the IDE Code Blocks, you must perform the following steps
// (Attention! The library is incompatible with new versions of Code Blocks, therefore I recommend downloading portable
// version from codeblocks.codecutter.org).
// 0. Unzip the archive. To work, run the file "CbLancher.exe" (NOT "codeblocks.exe"!)
// 1. Download the graphics.h and winbgim.h files and place it in the MinGW include compiler folder (for example
//    C: \ Program Files \ CodeBlocks \ MinGW \ include)
// 2. Download the libbgi.a file and place it in the lib folder (C: \ Program Files \ CodeBlocks \ MinGW \ lib)
// 3. In Code :: Blocks, open Settings >> Compiler and debugger >> Linker settings
// 4. Click Add to Link libraries and load the file libbgi.a
// 5. In the right part (Other linker options) insert the commands:
// 6. -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
// 7. Click OK.
