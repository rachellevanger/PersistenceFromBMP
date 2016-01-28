
#include <iostream>
#include "CDataPersistence.h"


#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>




/* main */
int main ( int argc, char * argv [] ) {

  int filestart = atoi(argv[1]); // Starting integer for bitmaps
  int fileend = atoi(argv[2]); // Ending integer for bitmaps
  char jobDir[500];
  std::strcpy(jobDir, argv[3]); // Directory containing the persistence diagrams/etc
  char jobPattern[100];
  std::strcpy(jobPattern, argv[4]); // Pattern to find the height functions relative to jobDir
  int sublevel = atoi(argv[5]); // Do sublevel sets?
  int superlevel = atoi(argv[6]); // Do superlevel sets?
  int isRadial = atoi(argv[7]); // Do radial persistence?

  int center_x = 0;
  int center_y = 0;
  int radius = 0;
  if( isRadial ) {
      int center_x = atoi(argv[8]);
      int center_y = atoi(argv[9]);
      int radius = atoi(argv[10]);
  }

  int filter = atoi(argv[11]); // Filter pixel values less than this amount.

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

    // Submit sublevel sets
    if ( sublevel ) {
        std::strcpy(filePersistence, jobDir);
        sprintf (fileTmp, "/PD/DownUp/Diagrams/Out_%d", j);
        std::strcat(filePersistence, fileTmp);
        p.SavePersistenceDiagrams( filePersistence, isRadial, center_x, center_y, radius, filter );
    }

    // Submit superlevel sets
    if ( superlevel ) {
        std::strcpy(filePersistenceInv, jobDir);
        sprintf (fileTmp, "/PD/UpDown/Diagrams/Out_%d", j);
        std::strcat(filePersistenceInv, fileTmp);
        p.SavePersistenceDiagramsInvers( filePersistenceInv, isRadial, center_x, center_y, radius, filter );
    }

  }


}
