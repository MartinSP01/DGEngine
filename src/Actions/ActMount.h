#pragma once

#include "Action.h"
#include "FileUtils.h"

class ActMount : public Action
{
private:
	std::string file;
	std::string mountPoint;
	bool appendToSearchPath;
	bool useSaveDir;

public:
	ActMount(const std::string& file_, const std::string& mountPoint_,
		bool appendToSearchPath_, bool useSaveDir_) : file(file_),
		mountPoint(mountPoint_), appendToSearchPath(appendToSearchPath_),
		useSaveDir(useSaveDir_) {}

	virtual bool execute(Game& game)
	{
		std::string file2;
		if (useSaveDir == false)
		{
			file2 = game.getPath() + file;
		}
		else
		{
			file2 = FileUtils::getSaveDir() + file;
		}
		FileUtils::mount(file2, mountPoint, appendToSearchPath);
		return true;
	}
};

class ActUnmount : public Action
{
private:
	std::string file;
	bool useSaveDir;

public:
	ActUnmount(const std::string& file_, bool useSaveDir_)
		: file(file_), useSaveDir(useSaveDir_) {}

	virtual bool execute(Game& game)
	{
		std::string file2;
		if (useSaveDir == false)
		{
			file2 = game.getPath() + file;
		}
		else
		{
			file2 = FileUtils::getSaveDir() + file;
		}
		FileUtils::unmount(file2);
		return true;
	}
};

class ActUnmountAll : public Action
{
public:
	virtual bool execute(Game& game)
	{
		FileUtils::unmountAll();
		return true;
	}
};
