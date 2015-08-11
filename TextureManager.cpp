//TextureManager Implementation file

#include "TextureManager.h"

TextureManager::TextureManager() : textures(), directories() {}

TextureManager::~TextureManager()
{
	textures.clear();
	directories.clear();
}

const sf::Texture& TextureManager::getTexture(const std::string &filename)
{
	// If the texture already exists
	for (std::map<std::string, sf::Texture>::const_iterator it = textures.begin(); it != textures.end(); it++)
	{
		if (filename == it->first)
			return it->second;
	}

	sf::Texture texture;
	// Else.. Create and save it.

	// if no sub directories are indicated... 
	if (directories.empty())			
	{
		if (texture.loadFromFile(filename))
		{
			textures[filename] = texture;
			return textures[filename];
		}
	}
	// if sub directory(s) is indicated... 						
	else							
	{
		for (std::vector< std::string >::iterator it = directories.begin(); it != directories.end(); it++)
		{
			if (texture.loadFromFile((*it) + filename))
			{
				textures[filename] = texture;
				return textures[filename];
			}
		}
	}
	// If not found, fill texture map with empty image
	std::cout << "ERROR: " << filename << " was not found.It will be filled with an empty texture.\n";
	textures[filename] = texture;
	return textures[filename];
}

void TextureManager::unloadTexture(const sf::Texture &texture)
{
	for (std::map<std::string, sf::Texture>::const_iterator it = textures.begin(); it != textures.end(); it++)
	{
		if (&texture == &it->second)
		{
			textures.erase(it);		
			return;
		}
	}
}

void TextureManager::unloadTexture(const std::string &filename)
{
	std::map<std::string, sf::Texture>::const_iterator it = textures.find(filename);
	if (it != textures.end())
		textures.erase(it);			
}

void TextureManager::addDirectory(const std::string &directory)
{
	// Check whether the path already exists
	for (std::vector<std::string>::const_iterator it = directories.begin(); it != directories.end(); it++)
	{
		// If the path exists... do nothing
		if (directory == (*it))
			return;
	}  // else... add to vector
	directories.push_back(directory);
}

void TextureManager::deleteDirectory(const std::string &directory)
{
	for (std::vector<std::string>::const_iterator it = directories.begin(); it != directories.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			it = directories.erase(it);
		else
			it++;
	}
}