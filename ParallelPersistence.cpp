
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
	int files = atoi(argv[1]);
	char jobDir[500];
	strcpy(jobDir, argv[2]);
  // Prepare job messages and push them onto "JOBS_TO_SEND" stack.
  
	for ( int j = 0; j < files ; ++ j ) {
      Message job_message;
      job_message << j;
      job_message << jobDir;
      JOBS_TO_SEND . push ( job_message );
    }
  
}

inline void Process::work ( Message & result_message, const Message & job_message ) const {
	// Extract job information from "job" message
	int job;
	char jobDir[500];
	job_message >> job;
	job_message >> jobDir;	  

	char fileData[500];
	char filePersistence[500];
	char filePersistenceInv[500];
	char fileTmp[50];  

	strcpy(fileData, jobDir);
	sprintf (fileTmp, "height_functions/%d.bmp", job);
	strcat(fileData, fileTmp);

	strcpy(filePersistence, jobDir);
	sprintf (fileTmp, "PD/DownUp/Diagrams/Out_%d", job);
	strcat(filePersistence, fileTmp);

	strcpy(filePersistenceInv, jobDir);
	sprintf (fileTmp, "PD/UpDown/Diagrams/Out_%d", job);
	strcat(filePersistenceInv, fileTmp);

    char sOut[50];
    sprintf(sOut, "Submitting persistence job %d...", job );
    std::cout << sOut ;

	CDataPersistence p;
	p.LoadData( fileData );
	p.SavePersistenceDiagrams( filePersistence );
	p.SavePersistenceDiagramsInvers( filePersistenceInv );

    sprintf(sOut, "...persistence job %d submit!", job );
    std::cout << sOut ;

}

inline void Process::finalize ( void ) { }

/* main */
int main ( int argc, char * argv [] ) {

	delegator::Start ();
	delegator::Run < Process > ( argc, argv );
	delegator::Stop ();
	return 0;
}
