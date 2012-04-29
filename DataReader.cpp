#include "DataReader.h"
using namespace std;

namespace DataFileReader
{

	DataReader::DataReader(string dataFileName, string colorFileName)
	{
		dataConstructor(dataFileName.c_str());
		colorConstructor(colorFileName.c_str());
	}

	DataReader::DataReader(char *dataFileName, char *colorFileName)
	{
		dataConstructor(dataFileName);
		colorConstructor(colorFileName);
	}

	DataReader::~DataReader()
	{
		free(this->geometry);
	}

	void DataReader::dataConstructor(const char *dataFileName)
	{
		fstream in;
		char temp[256];
		string header[4];
		this->dSize = this->dx = this->dy = this->dz = 0;
		this->scale = 255;
		in.open( dataFileName, ios::in | ios::binary );
		if (in.is_open())
		{
//		  cout << "File " << dataFileName << " successfully opened." << endl;
		  for(int a = 0; a < 4; a ++)
		  {
				in.getline(temp, 256);
				header[a].append(temp);
//				cout << header[a] << header[a].length() << endl;
		  }
		  if(this->getDimensions(header))
		  {
				this->geometry = (float *)malloc(this->geoSize);
				in.read((char *)this->geometry, this->geoSize);
				buildInterpolate();
		  }
			in.close();
		}
		else
		{
		  cout << "Error opening file " << dataFileName << endl;
		}
	}

	bool DataReader::getDimensions(string *header)
	{
		unsigned int loc, prevLoc, i;
		string temp[6];
		// Check that the file is the correct type...
		if(header[0].compare("DL Data Format") != 0) return false;
		if(header[1].compare(0, 10, "Dimensions") != 0) return false;
		if(header[2].compare(0, 11, "Type Binary") != 0) return false;
		if(header[3].compare(0, 12, "Grid Uniform") != 0) return false;

		i = prevLoc = 0;
		loc = header[1].find_first_of(" ");
		while((loc != string::npos) && (i < 6))
		{
			temp[i] = header[1].substr(prevLoc, loc - prevLoc);
			prevLoc = loc + 1;
			loc = header[1].find_first_of(" ", prevLoc);
			i++;
		}
		this->dx = atoi(temp[1].c_str());
		this->dy = atoi(temp[2].c_str());
		this->dz = atoi(temp[3].c_str());
		this->dSize = atoi(header[2].substr(header[2].size() - 1).c_str());
		if(this->dSize == sizeof(float))
		{
			this->geoSize = this->dx * this->dy * this->dz * this->dSize;
		}
		else return false;
		return true;
	}

	void DataReader::buildInterpolate(void)
	{
		this->maxG = FLT_MIN;
		this->minG = FLT_MAX;
		for(int i = 0; i < this->geoSize >> 2; i++)
		{
			this->geometry[i] < this->minG ? this->minG = this->geometry[i] : 0;
			this->geometry[i] > this->maxG ? this->maxG = this->geometry[i] : 0;
//			cout << "geometry[" << i << "]" << this->geometry[i] << endl;
		}
//		cout << "Min: " << this->minG << endl;
//		cout << "Max: " << this->maxG << endl;
		//(inVal – inMin) / (inMax – inMin) = (outVal – outMin) / (outMax – outMin)
		return;
	}

	void DataReader::colorConstructor(const char *colorFileName)
	{
		fstream in;
		char temp[256];
		string s;
		string t[4];
		unsigned int i, st, en;
		DataFileReader::Color c;
		in.open( colorFileName, ios::in | ios::binary );
		if(in.is_open())
		{
			in.getline(temp, 256);
			while(!in.eof())
			{
				s.assign(temp);
//				cout << "IN:  " << temp << " size: " << s.size() << endl;
				if(s.size() >= 4)	// pointless to parse tiny strings
				{
					for(i = 0; i < 3; i++)
					{
						st = s.find_first_not_of(" ");
						en = s.find_first_of(" ", st);
						t[i].assign(s.substr(st, en));
						s.assign(s.substr(en, s.size() - en));
					}
					t[3].assign(s.c_str());

//					cout << "OUT: ";
//					cout << t[0] << ":";
//					cout << t[1] << ":";
//					cout << t[2] << ":";
//					cout << t[3];
//					cout << endl;
					c.r = atof(t[0].c_str());
					c.g = atof(t[1].c_str());
					c.b = atof(t[2].c_str());
					c.a = atof(t[3].c_str());
					this->colors.push_back(c);
				}
				in.getline(temp, 256);
			}
			in.close();
		}
//		cout.precision(6);
//		for(unsigned int d = 0; d < this->colors.size(); d++)
//		{
//			cout << this->colors[d].r << " ";
//			cout << this->colors[d].g << " ";
//			cout << this->colors[d].b << " ";
//			cout << this->colors[d].a << " " << endl;
//		}
		return;
	}

	unsigned int DataReader::getX(void) { return this->dx; }
	unsigned int DataReader::getY(void) { return this->dy; }
	unsigned int DataReader::getZ(void) { return this->dz; }
	unsigned int DataReader::getDataSize(void)  { return this->dSize; }
	long int DataReader::getGeoSize(void) { return this->geoSize; }
	Color DataReader::at(unsigned int i)
	{
		int c = (int)((this->geometry[i] - this->minG) * this->scale / \
					(this->maxG - this->minG));
		c = c < 0 ? 0 : c;
		c = c > 255 ? 255 : c;
//		cout << "dr.at(" << i << ") = " << c << endl;
		return this->colors[c];
//		return this->colors[128];
	}
} /* namespace DataFileReader */
