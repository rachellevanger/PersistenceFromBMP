/*
 * CDataPersistence.cpp
 *
 *  Created on: Sep 6, 2012
 *      Author: miro
 */

#include "CDataPersistence.h"

#include <iostream>
#include <vector>

#include <sstream>
#include <string>
#include <algorithm>


#include "Cells/All.h"
#include "Complexes/All.h"
#include "Algos/All.h"




#include "CImg.h"

using namespace cimg_library;


CDataPersistence::CDataPersistence() {
	data_ = NULL;
	data_size_x_ = 0;
	data_size_y_ = 0;

}

CDataPersistence::~CDataPersistence() {
	if( data_ != NULL ) delete[] data_;
}

void CDataPersistence::LoadData( const char* file_name ){
	/* Delete the previous data if it exists */
	if( data_ != NULL ) delete[] data_;

	/* Load the image from file and save its dimensions */
	CImg<int> image( file_name );
	data_size_x_ = image . width( ) ;
	data_size_y_ = image . height( ) ;

	/* Allocate memory for image data */
	data_ = new int[ data_size_x_ * data_size_y_ ];
	/* Load the data from the first channel of the  image */
	for(unsigned int x = 0; x < data_size_x_; ++ x){
		for(unsigned int y = 0; y < data_size_y_; ++ y){
			data_[ x * data_size_y_ + y ] = image( x, y, 0, 1);
		}
	}
}

void CDataPersistence::SavePersistenceDiagrams( const char* save_as ){
	/*declare cubical data with integer chains and int births*/
	DenseCToplex<int,int> cubical_complex;

	/* define dimension of the image */
	std::vector<num> dimensions;
	dimensions.push_back( data_size_x_  );
	dimensions.push_back( data_size_y_ );

	/* initialize cubical complex with the given dimensions */
	cubical_complex.Init( dimensions );

	/* Load cubes (in the disk given by the experimental domain ) from the data_ */

	vector<num> coords;
	coords.resize( 2 );
	for(unsigned int x = 0; x < data_size_x_; ++ x){
		for(unsigned int y = 0; y < data_size_y_; ++ y){
		/*Inster the cube if it is in the disk */
		coords[ 0 ] =  x;
		coords[ 1 ] =  y;
		cubical_complex.addTopCube( coords,  data_[ x * data_size_y_ + y ]   );
		}
	}
	cubical_complex.ComputePersistence( save_as);
}
void CDataPersistence::SavePersistenceDiagramsInvers( const char* save_as ){
	/*declare cubical datas et with integer chains and int births*/
		DenseCToplex<int,int> cubical_complex;

		/* define dimension of the image */
		std::vector<num> dimensions;
		dimensions.push_back( data_size_x_  );
		dimensions.push_back( data_size_y_ );

		/* initialize cubical complex with the given dimensions */
		cubical_complex.Init(dimensions);

		/* Load inverse cubes from the data_ */
		vector<num> coords;
		coords.resize( 2 );
		for(unsigned int x = 0; x < data_size_x_; ++ x){
			for(unsigned int y = 0; y < data_size_y_; ++ y){
			/*Inster the cube if it is in the disk */
			     coords[ 0 ] =  x;
			     coords[ 1 ] =  y;
			     cubical_complex.addTopCube( coords, 255 - data_[ x * data_size_y_ + y ]   );
                
            }
        }
		cubical_complex.ComputePersistence( save_as);
}
