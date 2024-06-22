#pragma once
#include "String.h"

class FilePath
{
	String name;
	String extension;

public:
	FilePath(const char* fileName);
	FilePath(const String& fileName);
	const String& getName() const;
	const String& getExtension() const;
};

