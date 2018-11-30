// Algorithms races.
// Igor Lobanov. 2018
//
// This is a source file.

#include "algorithmsRaces.h"

void Graphics::myCleardevice( unsigned  bWidth,
                              unsigned  bStep,
                              size_t size,
                              unsigned  shiftX,
                              unsigned  shiftY,
                              bool isFalling ){

  setfillstyle( SOLID_FILL, 0 );
  setcolor( 0 );

  int shiftXpix = shiftX * ( size * bStep + bWidth );
  for( unsigned i = 0; i < size; ++i ){

    bar( 0 + i * bStep    + shiftXpix, shiftY,
       bWidth +i * bStep  + shiftXpix, shiftY + ( ( isFalling ) ? size : -size ) );
  }
}



void Graphics::ddelay( unsigned cycles ){

  for( unsigned t = 0 ; t < cycles; ++t );
}



void Graphics::setStyleColor( int pattern, int fill ){

  setfillstyle( pattern, fill );
  setcolor( fill );
}



void Graphics::graphicsInitialization( const unsigned ARR_SIZE_ ){


}



std::string RawData::createRawDataArrayFile( const unsigned  ARR_SIZE_a,
                                             RawArrayState rawArrayState_a,
                                             const unsigned ARR_MAX_ELEMENT_a ){

  std::string rawArrType;
  std::string txtSuffix = "_elements.txt";

  switch ( rawArrayState_a ){
    case RAW_ARRAY_RANDOM      : rawArrType = "RAW_ARRAY_RANDOM_";      break;
    case RAW_ARRAY_MAX_TO_MIN  : rawArrType = "RAW_ARRAY_MAX_TO_MIN_";  break;
    case RAW_ARRAY_MIN_TO_MAX  : rawArrType = "RAW_ARRAY_MIN_TO_MAX_";  break;
    case RAW_ARRAY_MAX_MIN_MAX : rawArrType = "RAW_ARRAY_MAX_MIN_MAX_"; break;
    case RAW_ARRAY_MIN_MAX_MIN : rawArrType = "RAW_ARRAY_MIN_MAX_MIN_"; break;
  }

  std::ostringstream sstream;
  std::string varAsString;

  sstream << rawArrType.c_str() << ARR_SIZE_a << txtSuffix.c_str();
  varAsString = sstream.str();

  // Prepare random data array ONCE to use for all sorts the same data collection.
  std::ifstream arrFileExists ( varAsString.c_str() );

  if( !arrFileExists ){

    unsigned* arr0 = new unsigned[ARR_SIZE_a];

    fillArr<unsigned>( rawArrayState_a, arr0, ARR_SIZE_a, 0, ARR_MAX_ELEMENT_a, 0 );
    std::ofstream arrFile ( varAsString.c_str(), std::ios::binary );
    arrFile.write( reinterpret_cast<char*>( arr0 ), ARR_SIZE_a * sizeof(unsigned) );

    delete [] arr0;

    if( !arrFile )
      throw Error::IosError("No array file was created.", varAsString);
  }

  return varAsString;
}



void RawData::readRawDataArrayFromFile ( const unsigned  ARR_SIZE_a,
                                         unsigned* arr_a,
                                         const std::string& varAsString_a ){

  std::ifstream arrFile2 ( varAsString_a.c_str(), std::ios::binary );

  if( !arrFile2 )
    throw Error::IosError("Array file doesn't exist. New file is being created...", varAsString_a);

  arrFile2.read( reinterpret_cast<char*>( arr_a ), ARR_SIZE_a * sizeof( unsigned ) );
}



void Graphics::showElapsedTime( const time_t t_a,
                                 const time_t tt_a,
                                 const unsigned  ARR_SIZE_a ){

  std::string str;
  std::ostringstream sstream2;
  sstream2 << ARR_SIZE_a << " el. for " << ( ( tt_a - t_a ) / 1000.0 );
  str = sstream2.str();
  str.append( " sec." );
  outtextxy( 0, 20, const_cast<char*>( str.c_str() ) ) ;
}



void Graphics::showRawDataType( RawArrayState rawArrayState_a ){

  std::string rawArrType;

  switch ( rawArrayState_a ){
    case RAW_ARRAY_RANDOM      : rawArrType = "Random";      break;
    case RAW_ARRAY_MAX_TO_MIN  : rawArrType = "Max-Min";     break;
    case RAW_ARRAY_MIN_TO_MAX  : rawArrType = "Min-Max";     break;
    case RAW_ARRAY_MAX_MIN_MAX : rawArrType = "Max-Min-Max"; break;
    case RAW_ARRAY_MIN_MAX_MIN : rawArrType = "Min-Max-Min"; break;
  }

  outtextxy( 0, 40, const_cast<char*>( rawArrType.c_str() ) ) ;
}



void Algoritms::sortArr( time_t& t_a,
                         time_t& tt_a,
                         const unsigned MAX_X_a,
                         const unsigned MAX_Y_a,
                         const unsigned ALGORITHM_NUM_a,
                         const unsigned ARR_MAX_ELEMENT_SHIFT_a,
                         const unsigned BETWEEN_WINDOWS_a,
                         const unsigned B_WIDTH_a,
                         const unsigned B_STEP_a,
                         unsigned* arr_a,
                         const unsigned ARR_SIZE_a,
                         const unsigned SHIFT_X_a,
                         const unsigned SHIFT_Y_a,
                         const unsigned COLOR_a,
                         const bool ISFALLING_a,
                         const unsigned WINDOW_COORD_X_a,
                         const unsigned WINDOW_COORD_Y_a ){

  using  qSortSpace::myHoareQuickSort;

  // Declare pointer to a sort function.
  void (* sort)( const unsigned ,
                 const unsigned,
                 unsigned*,
                 const size_t,
                 const unsigned,
                 const unsigned,
                 const unsigned char,
                 const bool );

  // Initialize pointer and define sort function name.
  std::string algType;
  switch ( ALGORITHM_NUM_a ){
    case 1 : algType = "Bubble Sort. O(pow(n,2))";          sort = myBubbleSort2;         break;
    case 2 : algType = "Bubble Sort Improved. O(pow(n,2))"; sort = myBubbleSortImproved2; break;
    case 3 : algType = "Shell Sort. O(pow(n,1.5))";         sort = myShellSort2;          break;
    case 4 : algType = "Selection Sort. O(n*log(n))";       sort = myEasyChoiceSort2;     break;
    case 5 : algType = "Quick Sort O(n*log(n))";            sort = myHoareQuickSort;      break;
    case 6 : algType = "Heap Sort O(n*log(n))";             sort = heapSort;              break;
  }

  // Set window size and coordinates.
  initwindow( MAX_X_a,
              MAX_Y_a,
              algType.c_str(),
              WINDOW_COORD_X_a * ARR_MAX_ELEMENT_SHIFT_a +
              WINDOW_COORD_X_a * BETWEEN_WINDOWS_a,
              WINDOW_COORD_Y_a * ( MAX_Y_a + BETWEEN_WINDOWS_a + 20),
              0,
              true );

  // Sort with time estimation.
  t_a = clock();
  (* sort)( B_WIDTH_a,
            B_STEP_a,
            arr_a,
            ARR_SIZE_a,
            SHIFT_X_a,
            SHIFT_Y_a,
            COLOR_a,
            ISFALLING_a );
  tt_a = clock();
}



RawData::RawArrayState RawData::getRawArrayState ( const unsigned RAW_ARRAY_NUM_a ){

  switch ( RAW_ARRAY_NUM_a ){
    case 1 : return RawData::RAW_ARRAY_RANDOM;
    case 2 : return RawData::RAW_ARRAY_MAX_TO_MIN;
    case 3 : return RawData::RAW_ARRAY_MIN_TO_MAX;
    case 4 : return RawData::RAW_ARRAY_MAX_MIN_MAX;
    case 5 : return RawData::RAW_ARRAY_MIN_MAX_MIN;
  }
}



void User::startAlgorithmRace( char* argv1_a,
                               char* argv2_a,
                               long long uBoundary_a,
                               char* argv4_a,
                               char* argv5_a ){

  using RawData::getRawArrayState;
  using RawData::RawArrayState;
  using RawData::createRawDataArrayFile;
  using RawData::readRawDataArrayFromFile;

  if( llabs( uBoundary_a ) > static_cast<long long>( UINT_MAX ) )
    throw Error::UserError("\nExcessive raw data array upper boundary.\n", uBoundary_a );

  // Algorithm type.
  const unsigned ALGORITHM_NUM  = atoi( argv1_a );

  // Raw data array state.
  const unsigned RAW_ARRAY_NUM  = atoi( argv2_a );
  RawArrayState rawArrayState = getRawArrayState ( RAW_ARRAY_NUM );

  // Raw data array size.
  const unsigned ARR_SIZE = static_cast<unsigned>( llabs( uBoundary_a ) );

#ifdef SHOW_GRAPHICS
  // Separate windows constants. Window width.
  const unsigned  MAX_X = Graphics::B_STEP * ARR_SIZE <= Graphics::SCREEN_X ?
    Graphics::B_STEP * ARR_SIZE : Graphics::SCREEN_X;

  // Raw data array max integer element size (to provide the most sutable graphics presentation).
  const unsigned  ARR_MAX_ELEMENT = ARR_SIZE * Graphics::B_STEP <= Graphics::SCREEN_Y ?
    ARR_SIZE * Graphics::B_STEP : Graphics::SCREEN_Y;

  // Separate windows constants. Horizontal shift between windows.
  const unsigned  ARR_MAX_ELEMENT_SHIFT = ARR_MAX_ELEMENT;

  // Separate windows constants. Window height.
  const unsigned  MAX_Y = ARR_MAX_ELEMENT;
#else
  const unsigned  ARR_MAX_ELEMENT = ARR_SIZE;
  const unsigned  MAX_X = 240U;
  const unsigned  ARR_MAX_ELEMENT_SHIFT = MAX_X;
  const unsigned  MAX_Y = 80U;
#endif

  // Create raw data array, if doesn't exist as a file.txt
  //std::string varAsString = createRawDataArrayFile( ARR_SIZE, rawArrayState, ARR_MAX_ELEMENT );

  //  Read previously prepared data collection.
  unsigned* arr = new unsigned [ARR_SIZE];

  // Fill raw data array.
  RawData::fillArr<unsigned>( rawArrayState, arr, ARR_SIZE, 0U, ARR_MAX_ELEMENT, false );

  //readRawDataArrayFromFile ( ARR_SIZE, arr, varAsString );

  time_t t;
  time_t tt;

  // Sort array.
  Algoritms::sortArr(  t,
                       tt,
                       MAX_X,
                       MAX_Y,
                       ALGORITHM_NUM,
                       ARR_MAX_ELEMENT_SHIFT,
                       Graphics::BETWEEN_WINDOWS,
                       Graphics::B_WIDTH,
                       Graphics::B_STEP,
                       arr,
                       ARR_SIZE,
                       0U,
                       ARR_MAX_ELEMENT,
                       15U, // WHITE
                       false,
                       atoi( argv4_a ),
                       atoi( argv5_a ) );

  Graphics::showElapsedTime ( t, tt, ARR_SIZE );

  Graphics::showRawDataType( rawArrayState );

  delete [] arr;

  getch();

  closegraph();
}



void User::warnUser( const char* WARN1_a,
                const long long arg1_a,
                const char* WARN2_a,
                const long long arg2_a,
                const char* WARN3_a,
                const long long arg3_a ){

  std::cerr << WARN1_a;
  -1LL != arg1_a ? std::cerr << arg1_a : std::cerr << "" ;
  std::cerr << WARN2_a;
  -1LL != arg2_a ? std::cerr << arg2_a : std::cerr << "" ;
  std::cerr << WARN3_a;
  -1LL != arg3_a ? std::cerr << arg3_a : std::cerr << "" ;
}
