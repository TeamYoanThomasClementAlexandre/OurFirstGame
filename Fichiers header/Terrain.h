#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <string>

class Terrain
{
private:
	std::string types;

public:
	Terrain(std::string s);
	~Terrain();

	static std::string getRealString(char c);	
};

#endif
