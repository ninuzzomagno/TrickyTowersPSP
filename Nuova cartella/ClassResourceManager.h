#pragma once
#include<map>
#include<oslib/oslib.h>
#include<string>

class ResourceManager {
public:
	ResourceManager();
	//LOAD
	int loadFont(std::string, std::string);
	int loadImage(std::string, std::string, int, int);
	int loadSound(std::string, std::string, int);
	//DELETE
	bool deleteFont(std::string);
	bool deleteImage(std::string);
	bool deleteSound(std::string);
	//GET
	OSL_IMAGE* getImage(std::string);
	OSL_FONT* getFont(std::string);
	OSL_SOUND* getSound(std::string);
private:
	std::map<std::string, OSL_FONT*>* font;
	std::map<std::string, OSL_IMAGE*>* image;
	std::map<std::string, OSL_SOUND*>* sound;
};