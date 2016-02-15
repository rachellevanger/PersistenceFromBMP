/*
 * CDataPersistence.h
 *
 *  Created on: Sep 6, 2012
 *      Author: miro
 */


#include <iostream>
#include <vector>

#ifndef CDATAPERSISTENCE_H_
#define CDATAPERSISTENCE_H_






class CDataPersistence {
private:
	int* data_;
	unsigned int data_size_x_;
	unsigned int data_size_y_;


public:
	CDataPersistence();
	virtual ~CDataPersistence();

	void LoadData( const char* file_name );
	void SavePersistenceDiagrams( const char* save_as, const int filter, const int* mask );
	void SavePersistenceDiagramsInvers( const char* save_as, const int filter, const int* mask  );

  std::vector<int> const&
  getDimensions ( void ) const;

};

#endif /* CDATAPERSISTENCE_H_ */
