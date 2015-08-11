//  TextureManager.h header file for handling textures

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class TextureManager
{
private:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> directories;

public:
	TextureManager();
	~TextureManager();
	const sf::Texture& getTexture(const std::string &fileName);
	void unloadTexture(const sf::Texture &texture);
	void unloadTexture(const std::string &filename);
	void addDirectory(const std::string &directory);
	void deleteDirectory(const std::string &directory);

private:
	TextureManager(const TextureManager &temp) = delete;
	TextureManager& operator =(const TextureManager &temp) = delete;
};

#endif // TEXTUREMANAGER_H