#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>

class Terrain
{
private:
	

public:
	Terrain(std::string s);
	std::string types;
	~Terrain();

	static std::string getRealString(char c);	
};

#endif
