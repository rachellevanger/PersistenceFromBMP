
#include <iostream>
#include "CDataPersistence.h"

#include <vector>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <exception>


int* mask_;
std::vector<num> mask_dimensions_;


/* main */
int main ( int argc, char * argv [] ) {

  int filestart = atoi(argv[1]); // Starting integer for bitmaps
  int fileend = atoi(argv[2]); // Ending integer for bitmaps
  char jobDir[500];
  std::strcpy(jobDir, argv[3]); // Directory containing the bitmap images.
  char jobPattern[100];
  std::strcpy(jobPattern, argv[4]); // Pattern to find the height functions relative to jobDir

  int sublevel = atoi(argv[5]); // Do sublevel sets?
  int superlevel = atoi(argv[6]); // Do superlevel sets?

  int filter = atoi(argv[7]); // Filter pixels (strictly) less than this value, 0 for no filter.

  char jobMask[500];
  mask_ = NULL;

  if ( argc == 9) {
    std::strcopy(jobMask, argv[8]); // Image mask path
    CImg<int> image( jobMask );
    int mask_size_x_ = image . width( ) ;
    int mask_size_y_ = image . height( ) ;

    mask_dimensions_.push_back ( mask_size_x_ );
    mask_dimensions_.push_back ( mask_size_y );

    /* Allocate memory for image data */
    mask_ = new int[ mask_size_x_ * mask_size_y_ ];
    /* Load the data from the first channel of the  image */
    for(unsigned int x = 0; x < mask_size_x_; ++ x){
      for(unsigned int y = 0; y < mask_size_y_; ++ y){
        mask_[ x * mask_size_y_ + y ] = image( x, y, 0, 1);
      }
    }

  }
  

  // Go through each of the bitmap files and submit the persistence jobs.
  for ( int j = filestart; j <= fileend ; ++ j ) {

    char fileData[500];
    char filePersistence[500];
    char filePersistenceInv[500];
    char fileTmp[500];  

    // Make file name
    std::strcpy(fileData, jobDir);
    sprintf (fileTmp, jobPattern, j);
    std::cout << fileTmp;
    std::strcat(fileData, fileTmp);

    // Load data
    CDataPersistence p;
    p.LoadData( fileData );

    // Check data size against mask size if mask is not a null pointer
    if ( mask_ != NULL ) {
      if ( p.getDimensions != mask_dimensions_ ) {
        std::cout << "Mask size does not match image size. Image=" << fileData << "\n";
        throw std::runtime_error("Mask size does not match image size. Image=" + fileData);
      }
    }

    // Submit sublevel sets
    if ( sublevel ) {
        std::strcpy(filePersistence, jobDir);
        sprintf (fileTmp, "/PD/DownUp/Diagrams/Out_%d", j);
        std::strcat(filePersistence, fileTmp);
        p.SavePersistenceDiagrams( filePersistence, filter, mask_ );
    }

    // Submit superlevel sets
    if ( superlevel ) {
        std::strcpy(filePersistenceInv, jobDir);
        sprintf (fileTmp, "/PD/UpDown/Diagrams/Out_%d", j);
        std::strcat(filePersistenceInv, fileTmp);
        p.SavePersistenceDiagramsInvers( filePersistenceInv, filter, mask_ );
    }

  }


}
