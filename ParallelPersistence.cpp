
#include <iostream>
#include "delegator/delegator.h"

#include "CDataPersistence.h"


#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>





class Process : public Coordinator_Worker_Process {
public:
  void initialize ( void );
  void work ( Message & result_message, const Message & job_message ) const;
  void finalize ( void );
private:
  int num_jobs_sent;
  int num_jobs;
};

inline void Process::initialize ( void ) {
    int filestart = atoi(argv[1]); // Starting integer for bitmaps
	int fileend = atoi(argv[2]); // Ending integer for bitmaps
	char jobDir[500];
	strcpy(jobDir, argv[3]); // Directory containing the persistence diagrams/etc
    char jobPattern[100];
    strcpy(jobPattern, argv[4]); // Pattern to find the height functions relative to jobDir
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

    // Prepare job messages and push them onto "JOBS_TO_SEND" stack.
  
	for ( int j = filestart; j <= fileend ; ++ j ) {
      Message job_message;
      job_message << j;
      job_message << jobDir;
      job_message << jobPattern;
      job_message << sublevel;
      job_message << superlevel;
      job_message << isRadial;
      job_message << center_x;
      job_message << center_y;
      job_message << radius;
      JOBS_TO_SEND . push ( job_message );
    }
  
}

inline void Process::work ( Message & result_message, const Message & job_message ) const {
	// Extract job information from "job" message
	int job;
	char jobDir[500];
    char jobPattern[100];
    int sublevel;
    int superlevel;
    int isRadial;
    int center_x;
    int center_y;
    int radius;

	job_message >> job;
	job_message >> jobDir;
    job_message >> jobPattern;
    job_message >> sublevel;
    job_message >> superlevel;
    job_message >> isRadial;	  
    job_message >> center_x;
    job_message >> center_y;
    job_message >> radius;

	char fileData[500];
	char filePersistence[500];
	char filePersistenceInv[500];
	char fileTmp[500];  

    char sOut[50];

	strcpy(fileData, jobDir);
	sprintf (fileTmp, jobPattern, job);
	std::cout << fileTmp;
	strcat(fileData, fileTmp);
    std::cout << fileData;

    CDataPersistence p;
    p.LoadData( fileData );

    if ( sublevel ) {
        strcpy(filePersistence, jobDir);
        sprintf (fileTmp, "/PD/DownUp/Diagrams/Out_%d", job);
        strcat(filePersistence, fileTmp);
        std::cout << filePersistence;
        p.SavePersistenceDiagrams( filePersistence, isRadial, center_x, center_y, radius );
    }

    if ( superlevel ) {
        strcpy(filePersistenceInv, jobDir);
        sprintf (fileTmp, "/PD/UpDown/Diagrams/Out_%d", job);
        strcat(filePersistenceInv, fileTmp);
        std::cout << filePersistenceInv;
        p.SavePersistenceDiagramsInvers( filePersistenceInv, isRadial, center_x, center_y, radius );
    }

}

inline void Process::finalize ( void ) { }

/* main */
int main ( int argc, char * argv [] ) {

	delegator::Start ();
	delegator::Run < Process > ( argc, argv );
	delegator::Stop ();
	return 0;
}
