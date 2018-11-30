// Algorithms races.
// Igor Lobanov. 2017
//
// This is a header file.

#ifndef ALGORITHMS_RACE
#define ALGORITHMS_RACE

#include <fstream>
#include <graphics.h>
#include <iostream>
#include <locale>       // srand()
#include <limits.h>     // UINT_MAX
#include <math.h>       // log()

// Sets graphics mode ON.
// Comment this line to compile in pure math mode.
#define SHOW_GRAPHICS

namespace RawData{

  // Integer numbers array different sequences:
  // random,
  // already sorted from max to min,
  // already sorted from min to max,
  // max - min - max,
  // min - max - min.
  enum RawArrayState { RAW_ARRAY_RANDOM = 1,
                       RAW_ARRAY_MAX_TO_MIN,
                       RAW_ARRAY_MIN_TO_MAX,
                       RAW_ARRAY_MAX_MIN_MAX,
                       RAW_ARRAY_MIN_MAX_MIN };

  // Prepare fill data array
  template<class T>
  void fillArr ( RawArrayState rawArrayState_a,
                 T* t_a,
                 size_t size_a,
                 unsigned lowerB_a,
                 unsigned upperB_a,
                 bool isSrand_a ){

    switch ( rawArrayState_a ){

      default :
      case ( RAW_ARRAY_RANDOM ) :
        if ( isSrand_a )
          srand( time( NULL ) );

        for( unsigned i = 0; i < size_a; ++i )
          t_a[i] = rand() % ( upperB_a - lowerB_a );

        break;
      case ( RAW_ARRAY_MAX_TO_MIN ) :
        for( unsigned i = 0; i < size_a; ++i )
          t_a[i] = upperB_a - i;

        break;
      case ( RAW_ARRAY_MIN_TO_MAX ) :
        for( unsigned i = 0; i < size_a; ++i )
          t_a[i] = lowerB_a + i;

        break;
      case ( RAW_ARRAY_MAX_MIN_MAX ) :
        for( unsigned i = 0; i <= size_a / 2; ++i )
          t_a[i] = upperB_a - i * 2;

        for( unsigned i = 1; i <  size_a / 2; ++i )
          t_a[i + size_a / 2] = lowerB_a + i * 2;

        break;
      case ( RAW_ARRAY_MIN_MAX_MIN ) :
        for( unsigned i = 0; i <= size_a / 2; ++i )
          t_a[i] = lowerB_a + i * 2;

        for( unsigned i = 1; i <  size_a / 2; ++i )
          t_a[i + size_a / 2] = upperB_a - i * 2;

        break;
    }
  }

  std::string createRawDataArrayFile( const unsigned  ARR_SIZE_a,
                                      RawArrayState rawArrayState_a,
                                      const unsigned ARR_MAX_ELEMENT_a );

  void readRawDataArrayFromFile ( const unsigned  ARR_SIZE_a,
                                  unsigned * arr_a,
                                  const std::string& varAsString_a );

  RawArrayState getRawArrayState ( const unsigned RAW_ARRAY_NUM_a );
}

namespace Graphics{

  using namespace RawData;

#ifdef SHOW_GRAPHICS
  const bool IS_GRAPHICS_MODE     = true;
#else
  const bool IS_GRAPHICS_MODE     = false;
#endif

  // Graphics constants. Bar chart bar width.
  const unsigned  B_WIDTH         = 1;

  // Graphics constants. Space between bars. +0 means no free space between bars.
  const unsigned  B_STEP          = B_WIDTH + 0;

  // Separate windows constants. Space between windows.
  const unsigned  BETWEEN_WINDOWS = 5;

  // Separate windows constants. Monitor screen resolution.
  const unsigned  SCREEN_X_MAX    = 640;
  const unsigned  SCREEN_Y_MAX    = 480;

  void myCleardevice( unsigned bWidth,
                      unsigned bStep,
                      size_t size,
                      unsigned shiftX,
                      unsigned shiftY,
                      bool isFalling = false );

  void setStyleColor( int pattern, int fill );

  template<class T>
  void showArr( const unsigned leftBorder,
                const unsigned rightBorder,
                const unsigned bWidth,
                const unsigned bStep,
                const T* t,
                const size_t size,
                const unsigned shiftX,
                const unsigned shiftY,
                const unsigned int color,
                const bool isFalling = false ){

    int shiftXpix = shiftX * ( size * bStep + bWidth );

    for( unsigned i = 0; i < size; ++i ){
      if( i == leftBorder || i == rightBorder ){
        setStyleColor( SOLID_FILL, RED );
      }
      else{
        setStyleColor( SOLID_FILL, color );
      }

      bar(          i * bStep  + shiftXpix, shiftY,
           bWidth + i * bStep  + shiftXpix, shiftY +
           ( ( isFalling ) ? t[i] : -t[i] ) );
    }
  }

  void showElapsedTime( const time_t t_a, const time_t tt_a,
                        const unsigned  ARR_SIZE_a );

  void showRawDataType( RawArrayState rawArrayState_a );
}

namespace Algorithms{

  enum AlgorithmType { BUBBLE_SORT      = 1,
                       BUBBLE_IMPR_SORT = 2,
                       SHELL_SORT       = 3,
                       SELECTION_SORT   = 4,
                       QUICK_SORT       = 5,
                       HEAP_SORT        = 6 };

  using namespace Graphics;

  // Bubble Sort.
  template<class T>
  void myBubbleSort2( const unsigned bWidth,
                      const unsigned bStep,
                      T* t,
                      const size_t size,
                      const unsigned shiftX,
                      const unsigned shiftY,
                      const unsigned char color,
                      const bool isFalling = false ) {

    T temp;

    for( size_t i = 0; i < size - 1; ++i ){
      for( size_t j = i + 1; j < size; ++j ){
        if ( t[i] > t[j] ){
          temp = t[i];
          t[i] = t[j];
          t[j] = temp;

#ifdef SHOW_GRAPHICS
          cleardevice();
          showArr<T>( i, j, bWidth, bStep, t, size, shiftX, shiftY, color,
                      isFalling );
#endif
        }
      }
    }

#ifdef SHOW_GRAPHICS
    showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                false );
    setStyleColor( SOLID_FILL, WHITE );
    outtextxy( 0, 0, "Bubble Sort. O(pow(n,2))" );
#endif
  }

  // Bubble Sort Improved.
  template<class T>
  void myBubbleSortImproved2( const unsigned bWidth,
                              const unsigned bStep,
                              T* t,
                              const size_t size,
                              const unsigned shiftX,
                              const unsigned shiftY,
                              const unsigned char color,
                              const bool isFalling = false ) {

    unsigned ixLastChange = 0;
    unsigned i = 1;
    T copy = 0;

    while ( ixLastChange < size ){

      ixLastChange = size;
      for( unsigned j = size - 1; j >= i; --j ){

        if( t[j] < t[j - 1] ){
          copy = t[j];
          t[j] = t[j - 1];
          t[j - 1] = copy;
          ixLastChange = j;

#ifdef SHOW_GRAPHICS
          cleardevice();
          showArr<T>( j, j - 1, bWidth, bStep, t, size, shiftX, shiftY, color,
                      isFalling );
#endif
        }
      }

      i = ixLastChange + 1;
    }

#ifdef SHOW_GRAPHICS
    showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                isFalling );
    setStyleColor( SOLID_FILL, WHITE );
    outtextxy( 0, 0, "Bubble Sort Improved. O(pow(n,2))" );
#endif
  }

  // Selection Sort.
  template<class T>
  void myEasyChoiceSort2( const unsigned bWidth,
                          const unsigned bStep,
                          T* t,
                          const size_t size,
                          const unsigned shiftX,
                          const unsigned shiftY,
                          const unsigned char color,
                          const bool isFalling = false ){
    T min;
    int ixMin = 0;
    for( unsigned i = 0; i < size - 1; ++i ) {
      min   = t[i];
      ixMin = i;

      for( unsigned j = i + 1; j < size; ++j ){
        if ( t[j] < min ){
          min = t[j];
          ixMin = j;

#ifdef SHOW_GRAPHICS
          cleardevice();
          showArr<T>( i, j, bWidth, bStep, t, size, shiftX, shiftY, color,
                      isFalling );
#endif
        }
      }

      t[ixMin] = t[i];
      t[i] = min;
    }

#ifdef SHOW_GRAPHICS
    showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                isFalling );
    setStyleColor( SOLID_FILL, WHITE );
    outtextxy( 0, 0, "Selection Sort. O(n*log(n))" );
#endif
  }

  // Shell Sort.
  template<class T>
  void myShellSort2( const unsigned bWidth,
                     const unsigned bStep,
                     T* t,
                     const size_t size,
                     const unsigned shiftX,
                     const unsigned shiftY,
                     const unsigned char color,
                     const bool isFalling = false ){

    int distance = size / 2;
    int j = 0;
    T x;
    while ( distance > 0 ){

      for( unsigned i = distance; i < size; ++i ) {

        x = t[i];
        j = i - distance;

        while ( j >= 0 && x < t[j] ){
          t[j + distance] = t[j];
          j -= distance;

#ifdef SHOW_GRAPHICS
          cleardevice();
          showArr<T>( i, j, bWidth, bStep, t, size, shiftX, shiftY, color,
                      isFalling );
#endif
        }

        t[j + distance] = x;
      }
      distance /= 2;
    }

#ifdef SHOW_GRAPHICS
    showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                isFalling );
    setStyleColor( SOLID_FILL, WHITE );
    outtextxy( 0, 0, "Shell Sort. O(pow(n,1.5))" );
#endif
  }

  namespace qSortSpace{

    class QuickSortStack{

      struct StackItem{
        int left_;
        int right_;
      };

    public:
      QuickSortStack( int _size ): body_ ( new StackItem [_size] ),
                                   size_ ( _size ),
                                   top_ (-1)
      {}

      ~QuickSortStack()
      {
        delete [] body_;
      }

      void push( int left_, int right_ ){
        if( ( right_ - left_ ) >= 1 )
        {
          ++top_;
          body_[top_].left_  = left_;
          body_[top_].right_ = right_;
        }
      }

      void pop( int& left_, int& right_ ){
         left_  = body_[top_].left_;
         right_ = body_[top_].right_;
         --top_;
      }

      int isEmpty(){
        return top_ == -1;
      }

    private:
      StackItem* body_;

      int size_;
      int top_;
    };

    // Hoare Quick Sort.
    template<class T>
    void myHoareQuickSort( const unsigned bWidth,
                           const unsigned bStep,
                           T* t,
                           const size_t size,
                           const unsigned shiftX,
                           const unsigned shiftY,
                           const unsigned char color,
                           const bool isFalling = false ){

      int left;
      int right;
      int ixleft;
      int ixright;

      int copy;
      int x;

      int stackSize = log10( static_cast<double>( size ) ) / log10 ( 2.0 ) + 1;

      QuickSortStack stack ( stackSize );

      srand( static_cast<unsigned>( time( NULL ) ) );

      stack.push( 0, size - 1 );

      while ( !stack.isEmpty() ){

        stack.pop( left, right );

        while ( left < right ){
          x = t[left + rand() % ( right - left )];

          ixleft  = left;
          ixright = right;

          while ( ixleft <= ixright ){
              while ( t[ixleft]  < x ) ++ixleft;
              while ( t[ixright] > x ) --ixright;

              if( ixleft <= ixright ){
                copy       = t[ixleft];
                t[ixleft]  = t[ixright];
                t[ixright] = copy;

                ++ixleft;
                --ixright;

#ifdef SHOW_GRAPHICS
                cleardevice();
                showArr<T>( ixleft, ixright, bWidth, bStep, t, size, shiftX,
                            shiftY, color, isFalling );
#endif
              }
          }

          if( ixright - left < right - ixleft ){
            stack.push( ixleft, right );
            right = ixright;
          }
          else{
            stack.push( left, ixright );
            left = ixleft;
          }
        }
      }

#ifdef SHOW_GRAPHICS
      showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                  false );
      setStyleColor( SOLID_FILL, WHITE );
      outtextxy( 0, 0, "Quick Sort. O(n*log(n))" );
#endif
    }
  }

  // Heap Sort.
  template<class T>
  void sift( T* a,
      int root,
      int last ){

    int hole = root; // hole is at a root place.
    T x = a[hole - 1]; // last element.
    int left;
    int right;
    int pretender;

    while ( true ){
      left  = 2 * hole; // root of left sub-tree.
      right = left + 1; // root of right sub-tree.

      if( left > last )
        break; // if leaf appears - stop sift.

      // choose pretendent.
      if( left == last )
        pretender = left;
      else{
        if( a[left - 1] < a[right - 1] )
          pretender = right;
        else
          pretender = left;
      }

      // if pretender is not better than x - stop sift.
      if( a[pretender - 1] <= x )
        break;
      //making new hole.
      a[hole - 1] = a[pretender - 1];

      hole = pretender;
    }

    //fill the hole.
    a[hole - 1] = x;
    }

    template<class T>
    void heapSort(  const unsigned  bWidth,
                    const unsigned  bStep,
                    T* t,
                    const size_t size,
                    const unsigned  shiftX,
                    const unsigned  shiftY,
                    const unsigned char color,
                    const bool isFalling = false ){
    int root;
    int last;

    // preliminary pyramid preparation.
    for( root = size / 2; root > 0; --root )
      sift( t, root, size );

    // sorting cycle.
    for( last = size; last > 1; --last ){
      T copy = t[0];
      t[0] = t[last - 1];
      t[last - 1] = copy;

#ifdef SHOW_GRAPHICS
      cleardevice();
      showArr<T>( 0, last - 1, bWidth, bStep, t, size, shiftX, shiftY, color,
                  isFalling );
#endif

      // sift.
      sift( t, 1, last - 1 );
    }

#ifdef SHOW_GRAPHICS
    showArr<T>( 0xffff, 0xffff, bWidth, bStep, t, size, shiftX, shiftY, GREEN,
                isFalling );
    setStyleColor( SOLID_FILL, WHITE );
    outtextxy( 0, 0, "Heap Sort. O(n*log(n))" );
#endif
  }

  void sortArr( time_t& t_a,
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
                const unsigned WINDOW_COORD_Y_a );
}

namespace User{
  // Primary function to provide sort process.
  void startAlgorithmRace( char* argv1_, char* argv2_, long long uBoundary_,
                           char* argv4_, char* argv5_ );
  // Console IO to warn user about typical problems (memory, files access etc.)
  void warnUser( const char* WARN1,
                 const long long arg1  = -1LL,
                 const char* WARN2     = "",
                 const long long arg2  = -1LL,
                 const char* WARN3     = "",
                 const long long arg3  = -1LL );
}

// Exceptions classes.
namespace Error {
  class BaseError{
  public:

    std::string name_;

    BaseError( std::string name ) : name_( name) {}
  };

  class UserError {
    public:

      std::string name_;
      long long upperBoundary_;

      UserError( std::string name, long long  upperBoundary = 0LL ) :
        name_( name ), upperBoundary_( upperBoundary ) {}
    };

  class IosError {
    public:

      std::string name_;
      std::string path_;

      IosError( std::string name, std::string path = "" ) : name_( name ),
                                                            path_( path ) {}
    };
}

template <typename T>
class Array{

public:
  Array( const size_t size_a,
         RawData::RawArrayState rawArrayState_a,
         Algorithms::AlgorithmType algorithmType_a ) : size_( size_a ),
                                                       array_( new T [size_] ),
                                            rawArrayState_( rawArrayState_a ),
                                            algorithmType_( algorithmType_a ) {}

  ~Array() {
    delete [] array_;
  }

  void fillArr ( unsigned lowerB_a,
                 unsigned upperB_a,
                 bool isSrand_a ){

    using namespace RawData;

    switch ( rawArrayState_ ){

      default :
      case ( RAW_ARRAY_RANDOM ) :
        if ( isSrand_a )
          srand( time( NULL ) );

        for( unsigned i = 0; i < size_; ++i )
          array_[i] = ( rand() ) % ( upperB_a - lowerB_a );

        break;
      case ( RAW_ARRAY_MAX_TO_MIN ) :
        for( unsigned i = 0; i < size_; ++i )
          array_[i] = upperB_a - i;

        break;
      case ( RAW_ARRAY_MIN_TO_MAX ) :
        for( unsigned i = 0; i < size_; ++i )
          array_[i] = lowerB_a + i;

        break;
      case ( RAW_ARRAY_MAX_MIN_MAX ) :
        for( unsigned i = 0; i <= size_ / 2; ++i )
          array_[i] = upperB_a - i * 2;

        for( unsigned i = 1; i <  size_ / 2; ++i )
          array_[i + size_ / 2] = lowerB_a + i * 2;

        break;
      case ( RAW_ARRAY_MIN_MAX_MIN ) :
        for( unsigned i = 0; i <= size_ / 2; ++i )
          array_[i] = lowerB_a + i * 2;

        for( unsigned i = 1; i <  size_ / 2; ++i )
          array_[i + size_ / 2] = upperB_a - i * 2;

        break;
    }
  }

  // Bubble Sort.
  void bubbleSort( const unsigned      BWIDTH_a,
                   const unsigned      BSTEP_a,
                   const unsigned      SHIFTX_a,
                   const unsigned      SHIFTY_a,
                   const unsigned char COLOR_a,
                   const bool          ISFALLING_a = false ) {

    T temp;

    for( size_t i = 0; i < size_ - 1; ++i ){
      for( size_t j = i + 1; j < size_; ++j ){
        if ( array_[i] > array_[j] ){
          temp = array_[i];
          array_[i] = array_[j];
          array_[j] = temp;

#ifdef SHOW_GRAPHICS
          cleardevice();
          Graphics::showArr<T>( i, j, BWIDTH_a, BSTEP_a, array_, size_,
                                SHIFTX_a, SHIFTY_a, COLOR_a, ISFALLING_a );

          Graphics::showRawDataType( rawArrayState_ );
#endif
        }
      }
    }
  }

private:
  size_t size_;
  T* array_;
  RawData::RawArrayState rawArrayState_;
  Algorithms::AlgorithmType algorithmType_;
};
#endif
