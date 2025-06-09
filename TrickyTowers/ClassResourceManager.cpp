#include"ClassResourceManager.h"

ResourceManager::ResourceManager() {
	this->font = new std::map<std::string, OSL_FONT*>;
	this->image = new std::map<std::string, OSL_IMAGE*>;
	this->sound = new std::map<std::string, OSL_SOUND*>;
}

int ResourceManager::loadFont(std::string val, std::string path) {
	std::map<std::string, OSL_FONT*>::iterator it;
	it = this->font->find(val);
	if (it != this->font->end())
		return -1; // c'è già una risorsa con quel nome
	OSL_FONT* font = oslLoadIntraFontFile(path.c_str(), INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	if (!font)
		return -2;  // impossibile caricare il file
	this->font->insert(std::pair<std::string, OSL_FONT*>(val, font));
	return 0; //tutto OK
}

int ResourceManager::loadImage(std::string val, std::string path, int options,int pixel_format) {
	std::map<std::string, OSL_IMAGE*>::iterator it;
	it = this->image->find(val);
	if (it != this->image->end())
		return -1; // c'è già una risorsa con quel nome
	OSL_IMAGE* texture = oslLoadImageFilePNG(const_cast<char*>(path.c_str()), OSL_IN_RAM, pixel_format);
	if (!texture)
		return -2;  // impossibile caricare il file
	this->image->insert(std::pair<std::string, OSL_IMAGE*>(val, texture));
	return 0; //tutto OK
}

int ResourceManager::loadSound(std::string val, std::string path, int stream) {
	std::map<std::string, OSL_SOUND*>::iterator it;
	it = this->sound->find(val);
	if (it != this->sound->end())
		return -1; // c'è già una risorsa con quel nome
	OSL_SOUND* s = oslLoadSoundFileMP3(const_cast<char*>(path.c_str()), stream);
	if (!s)
		return -2;  // impossibile caricare il file
	this->sound->insert(std::pair<std::string, OSL_SOUND*>(val, s));
	return 0; //tutto OK
}

OSL_SOUND* ResourceManager::getSound(std::string val) {
	std::map<std::string, OSL_SOUND*>::iterator it;
	it = this->sound->find(val);
	if (it == this->sound->end())
		return nullptr;
	return it->second;
}

OSL_IMAGE* ResourceManager::getImage(std::string val) {
	std::map<std::string, OSL_IMAGE*>::iterator it;
	it = this->image->find(val);
	if (it == this->image->end())
		return nullptr;
	return it->second;
}

OSL_FONT* ResourceManager::getFont(std::string val) {
	std::map<std::string, OSL_FONT*>::iterator it;
	it = this->font->find(val);
	if (it == this->font->end())
		return nullptr;
	return it->second;
}

bool ResourceManager::deleteImage(std::string val) {
	std::map<std::string, OSL_IMAGE*>::iterator it;
	it = this->image->find(val);
	if (it == this->image->end())
		return false; // non c'è risorsa con quel nome
	oslDeleteImage(it->second);
	this->image->erase(val);
	return true;
}

bool ResourceManager::deleteFont(std::string val) {
	std::map<std::string, OSL_FONT*>::iterator it;
	it = this->font->find(val);
	if (it == this->font->end())
		return false; // non c'è risorsa con quel nome
	oslDeleteFont(it->second);
	this->font->erase(val);
	return true;
}

bool ResourceManager::deleteSound(std::string val) {
	std::map<std::string, OSL_SOUND*>::iterator it;
	it = this->sound->find(val);
	if (it == this->sound->end())
		return false; // non c'è risorsa con quel nome
	oslDeleteSound(it->second);
	this->sound->erase(val);
	return true;
}