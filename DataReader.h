#ifndef DATAREADER_H_
#define DATAREADER_H_
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <vector>

namespace DataFileReader
{

	struct Color
	{
			float r;
			float g;
			float b;
			float a;
	};

	class DataReader
	{
		public:
			DataReader(std::string dataFileName, std::string colorFileName);
			DataReader(char *dataFileName, char *colorFileName);
			virtual ~DataReader();
			Color at(unsigned int i);	// Return data value at i
			long int getGeoSize(void);	// Return size of geometry list
			unsigned int getX(void);
			unsigned int getY(void);
			unsigned int getZ(void);
			unsigned int getDataSize(void);

		private:
			unsigned int dx, dy, dz;		// Dimensions of data file
			unsigned int dSize;				// Size of data element
			long int geoSize;			// Size of geometry array
			float minG, maxG;			// Geometry extremes
			float *geometry;	// Array of geometry from file
			float scale;			// scale the value of geometry. Calculate from colors.
			std::vector<Color> colors;
			void dataConstructor(const char *dataFileName);
			void colorConstructor(const char *colorFileName);
			bool getDimensions(std::string *header);	// Return false if not proper format
			void buildInterpolate(void);				// Build the interpolation table
//			Color getColor(unsigned int i);		// Get color structure from data
	};

} /* namespace DataFileReader */
#endif /* DATAREADER_H_ */
