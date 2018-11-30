// Algorithms races.
// Igor Lobanov. 2018
//
// This is a launcher main file.

#include "algRacesLauncher.h"

int main( int argc, char** argv )
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory( &si, sizeof(si) );
  si.cb = sizeof(si);
  ZeroMemory( &pi, sizeof(pi) );

  char stringi  [BUFF_SIZE] = "";
  char stringj  [BUFF_SIZE] = "";
  char stringx  [BUFF_SIZE] = "";
  char stringy  [BUFF_SIZE] = "";
  char stringArr[BUFF_SIZE] = "";

  std::string varAsString;
#ifdef SHOW_GRAPHICS
  std::string defaultPath = "algRaces.exe";

  varAsString.append( "algRacesLauncher.exe" );
  std::rename( "main.exe", const_cast<const char*>( varAsString.c_str() ) );
#else
  std::string defaultPath = "algRacesNoGraph.exe";

  varAsString.append( "algRacesNoGraphLauncher.exe" );
  std::rename( "main.exe", const_cast<const char*>( varAsString.c_str() ) );
#endif

  std::string path = defaultPath;

  // Read main settings from file.
  std::ifstream fromFile ( "start_data.txt" );

  long long arrSize   = 0LL;

  fromFile >> arrSize;

  unsigned x;
  std::vector<unsigned> algVec;
  std::vector<unsigned> arrVec;

  for( size_t i = 1; i <= ALG_AMOUNT; ++i){
    fromFile >> x;
    if( x != 0 )
      algVec.push_back( x );
  }

  for( size_t i = 1; i <= ARR_AMOUNT; ++i){
    fromFile >> x;
    if( x != 0 )
      arrVec.push_back( x );
  }

  snprintf( stringArr, BUFF_SIZE, "%d", arrSize );

  // i - algorithm type from vector.
  for( size_t i = 0; i < algVec.size(); ++i ){

    snprintf( stringi, BUFF_SIZE, "%d", algVec[i] );

    // j - raw data array type from vector.
    for( size_t j = 0; j < arrVec.size(); ++j ){

      snprintf( stringj, BUFF_SIZE, "%d", arrVec[j] );

      // Pass i, j.
      path.append(" ");
      path.append( stringi );
      path.append(" ");
      path.append( stringj );
      path.append(" ");
      path.append( stringArr );

      // Pass windows coordinates.
      snprintf( stringx, BUFF_SIZE, "%d", i );
      snprintf( stringy, BUFF_SIZE, "%d", j );
      path.append(" ");
      path.append( stringx );
      path.append(" ");
      path.append( stringy );
      path.append(" ");

      if( !CreateProcess( NULL,   // No module name (use command line).
                          const_cast<char*>( path.c_str() ),
                          NULL,   // Process handle not inheritable
                          NULL,   // Thread handle not inheritable
                          FALSE,  // Set handle inheritance to FALSE
                          0,      // No creation flags
                          NULL,   // Use parent's environment block
                          NULL,   // Use parent's starting directory
                          &si,    // Pointer to STARTUPINFO structure
                          &pi )   // Pointer to PROCESS_INFORMATION structure
                          ){
          printf( "CreateProcess failed (%d).\n", GetLastError() );
          return 1;
        }

      path = defaultPath;
    }
  }

  // Wait until child process exits.
  WaitForSingleObject( pi.hProcess, INFINITE );

  // Close process and thread handles.
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );

  return 0;
}
