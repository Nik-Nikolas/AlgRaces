// Algorithms races.
// Igor Lobanov. 2017
//
// This is a main.cpp file.

#include "algorithmsRaces.h"
#define NDEBUG
#include <cassert>

int main( int argc, char** argv ){

  using User::startAlgorithmRace;
  using User::warnUser;

  assert( 6 == argc ); // 6 types of sorting.

  long long uBoundary = atoll( argv[3] );

  // Main cycle
  while( true ){
    try{

      startAlgorithmRace( argv[1], argv[2], uBoundary, argv[4], argv[5] );

    }
    catch( std::bad_alloc ){ // All heap memory allocation malfunctions.

      warnUser( "\nNo enougth system memory to deploy an array with size ",
                uBoundary,
                ".\nTrying to halve the array size...\n" );

      uBoundary /= 2;

      warnUser( "\nNew array size is ",
                uBoundary,
                " elements.\n" );

    }
    catch( Error::UserError err ){ // Input data errors.

      warnUser( "\n",
                err.upperBoundary_,
                " is incorrect array upper boundary!\nNew boundary ",
                Graphics::IS_GRAPHICS_MODE ? Graphics::SCREEN_Y_MAX :
                static_cast<long long>( UINT_MAX ),
                " will be assigned instead.\n" );

      uBoundary = Graphics::IS_GRAPHICS_MODE ? Graphics::SCREEN_Y_MAX :
                  static_cast<long long>( UINT_MAX );
    }
    catch( Error::IosError err ){ // File errors.

      std::string s = "\n" + err.name_ + ". File path: " + err.path_ + "\n";
      warnUser( s.c_str() );

      throw;
    }
    catch( ... ){
      throw;
    }
  }

  return 0;
}
