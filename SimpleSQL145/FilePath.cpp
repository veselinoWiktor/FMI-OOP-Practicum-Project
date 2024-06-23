#include "FilePath.h"
#include <sstream>

FilePath::FilePath(const char* fileName) : FilePath((String)fileName)
{
}

FilePath::FilePath(const String& fileName)
{
	const char* beg = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getLength();
	const char* dirIter = end;

	while (dirIter != beg && *dirIter != '/') {
		dirIter--;
	}
	dirIter++;

	this->directory = fileName.substr(0, dirIter - beg);

	const char* nameIter = end;

	while (nameIter != beg && *nameIter != '.') {
		nameIter--;
	}

	this->name = fileName.substr(dirIter - beg, nameIter - dirIter);
	this->extension = fileName.substr(nameIter - beg, end - nameIter);
}

const String& FilePath::getDirectory() const
{
	return directory;
}

const String& FilePath::getName() const
{
	return name;
}

const String& FilePath::getExtension() const
{
	return extension;
}