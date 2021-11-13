//
// Created by Maya Queen on 11/13/21.
//

#include "HttpResponse.hpp"
#include <dirent.h>

typedef struct	s_content {
	std::string root;
	std::string name;
	off_t 		size;
	std::string last_mode;
	std::string ref;
}				t_content;

void back_ref(std::string &ref, std::string &root){
	ref.erase(ref.rfind("/.."));
	if (ref + "/" != root)
		ref.erase(ref.rfind('/'));
}

t_content genarate_struct(std::string &path, const std::string& name, std::string &root){
	t_content cont;

	cont.root = path;
	if (cont.root[cont.root.size() - 1] != '/')
		cont.root += '/';
	cont.name = name;
	cont.ref = path + name;

	struct stat structstat;
	if (stat(cont.ref.c_str(), &structstat) < 0)
	{
		std::cerr << "ERROR: Autoindex.cpp: generate_struct" << std::endl;
		return cont;
	}
	time_t time = structstat.st_mtimespec.tv_sec;
	cont.last_mode = ctime(&time);

	if (S_ISDIR(structstat.st_mode)) {
		cont.size = 0;
		if (cont.name == "..")
			back_ref(cont.ref, root);
		else if (cont.name == ".")
			cont.ref.erase(cont.ref.rfind('/'));
		else
			cont.name += '/';
	}
	if (S_ISREG(structstat.st_mode))
		cont.size = (structstat.st_size);
	return cont;
}

std::string get_dir_content(std::string &path, std::vector<t_content> &dir_content, std::string &root){
	DIR *dir;
	struct dirent *dent;

	std::stringstream ss;

	if (path[path.size() - 1] != '/')
		path += '/';

	dir = opendir(path.c_str());
	if(dir!=NULL)
	{
		while((dent=readdir(dir))!=NULL){
			dir_content.push_back(genarate_struct(path, dent->d_name, root));
		}
		closedir(dir);
	}
	for (size_t i = 0; i < dir_content.size(); ++i)
	{
		ss << dir_content[i].name;
		for (int j = 0; j < 20 - dir_content[i].name.size(); ++j) {
			ss << " ";
		}
		ss << "\t" << dir_content[i].size
		<< "\t" << dir_content[i].ref;
		for (int j = 0; j < 20 - dir_content[i].ref.size(); ++j) {
			ss << " ";
		}
		ss << "\t" << dir_content[i].last_mode;
	}
	return ss.str();
}

std::string get_autoindex(std::string &path, std::string &root){
	std::string str;
	std::vector<t_content> dir_content;

	str = get_dir_content(path, dir_content, root);
	return str;
}