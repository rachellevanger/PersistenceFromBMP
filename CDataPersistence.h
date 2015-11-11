/*
 * CDataPersistence.h
 *
 *  Created on: Sep 6, 2012
 *      Author: miro
 */

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
	void SavePersistenceDiagrams( const char* save_as, const int isRadial, const int center_x, const int center_y, const int radius, const int filter );
	void SavePersistenceDiagramsInvers( const char* save_as, const int isRadial, const int center_x, const int center_y, const int radius, const int filter  );
};

#endif /* CDATAPERSISTENCE_H_ */
