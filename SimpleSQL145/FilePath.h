#pragma once
#include "String.h"

class FilePath
{
	String directory;
	String name;
	String extension;

public:
	FilePath(const char* fileName);
	FilePath(const String& fileName);
	const String& getDirectory() const;
	const String& getName() const;
	const String& getExtension() const;
};

