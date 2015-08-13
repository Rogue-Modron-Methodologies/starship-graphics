//  Copyright 2015 Jamie Johnson.
//  This work is for educational purposes only.
//  No commercial use, duplication, or distribution is allowed.
//  All artwork belongs to Mayfair Games Inc.
//  www.mayfairgames.com
//  Used without permission for educational purposes only.
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

template <class T>
class ResourceManager
{
private:
	std::map<std::string, T> resources;
	std::vector<std::string> directories;

public:
	ResourceManager();
	~ResourceManager();
	const T& getResource(const std::string &fileName);
	void unloadResource(const T &resource);
	void unloadResource(const std::string &filename);
	void addDirectory(const std::string &directory);
	void deleteDirectory(const std::string &directory);

private:
	ResourceManager(const ResourceManager &temp) = delete;
	ResourceManager& operator =(const ResourceManager &temp) = delete;
};

template <class T>
ResourceManager<T>::ResourceManager() : resources(), directories() {}

template <class T>
ResourceManager<T>::~ResourceManager()
{
	resources.clear();
	directories.clear();
}

template <class T>
const T& ResourceManager<T>::getResource(const std::string &filename)
{
	// If the resource already exists
	for (std::map<std::string, T>::const_iterator it = resources.begin(); it != resources.end(); it++)
	{
		if (filename == it->first)
			return it->second;
	}

	T resource;
	// Else.. Create and save it.

	// if no sub directories are indicated... 
	if (directories.empty())
	{
		if (resource.loadFromFile(filename))
		{
			resources[filename] = resource;
			return resources[filename];
		}
	}
	// if sub directory(s) is indicated... 						
	else
	{
		for (std::vector< std::string >::iterator it = directories.begin(); it != directories.end(); it++)
		{
			if (resource.loadFromFile((*it) + filename))
			{
				resources[filename] = resource;
				return resources[filename];
			}
		}
	}
	// If not found, fill texture map with empty image
	std::cout << "ERROR: " << filename << " was not found.It will be filled with an empty texture.\n";
	resources[filename] = resource;
	return resources[filename];
}

template <class T>
void ResourceManager<T>::unloadResource(const T &resource)
{
	for (std::map<std::string, T>::const_iterator it = resources.begin(); it != resources.end(); it++)
	{
		if (&resource == &it->second)
		{
			resources.erase(it);
			return;
		}
	}
}

template <class T>
void ResourceManager<T>::unloadResource(const std::string &filename)
{
	std::map<std::string, T>::const_iterator it = resources.find(filename);
	if (it != resources.end())
		textures.erase(it);
}

template <class T>
void ResourceManager<T>::addDirectory(const std::string &directory)
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

template <class T>
void ResourceManager<T>::deleteDirectory(const std::string &directory)
{
	for (std::vector<std::string>::const_iterator it = directories.begin(); it != directories.end();)
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			it = directories.erase(it);
		else
			it++;
	}
}


#endif // RESOURCEMANAGER_H