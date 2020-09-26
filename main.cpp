#include <stdio.h> 
// #define WINDOWS  /* uncomment  for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

char *GetCurrentWorkingDir(void)
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	char *current_working_dir(buff);
	return current_working_dir;
}

void list()
{
	DIR *dir;
	struct dirent *ent;
	char *current_dir = GetCurrentWorkingDir();
	if ((dir = opendir(current_dir)) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			printf("%s\n", ent->d_name);
		}
		closedir(dir);
	}
	else
	{
		/* could not open directory */
		perror("");
	}
}

void delete_file(string name)
{
	//convert string to *char
	char *cstr = new char[name.length() + 1];
	strcpy(cstr, name.c_str());
	std::remove(cstr);
	cout << "File was deleted successfuly" <<endl;
}

// split command into array
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos)
	{
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

int main()
{
	string full_command;
	while (true)
	{
		cout << "Enter the command" << endl;
		cin >> full_command;
		std::vector<std::string> v;
		split(full_command, v, ' ');
		if (v[0] == "list")
		{
			list();
		}
		if (v[0] == "delete")
		{
			delete_file(v[1]);
		}
		if (v[0] == "stop")
		{
			cout << "closing..." <<endl;
			exit(EXIT_FAILURE);
		}
	}
	return 1;
