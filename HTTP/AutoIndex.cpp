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
//	for (size_t i = 0; i < dir_content.size(); ++i)
//	{
//		ss << dir_content[i].name;
//		for (int j = 0; j < 20 - dir_content[i].name.size(); ++j) {
//			ss << " ";
//		}
//		ss << "\t" << dir_content[i].size
//		<< "\t" << dir_content[i].ref;
//		for (int j = 0; j < 20 - dir_content[i].ref.size(); ++j) {
//			ss << " ";
//		}
//		ss << "\t" << dir_content[i].last_mode;
//	}
	return ss.str();
}

void	get_title(std::stringstream &response, std::string &path){
//title--------------------------------
	response << 	"<!DOCTYPE html>"
				"<html lang=\"en\">"
				"<head>"
				"<meta charset=\"UTF-8\">"
				"<title>"
				<< path <<
				"</title>"
				"<style>"
//				"#q {"
//				"background:#477ab9;"
//				"width:100%;"
//				"-webkit-transition: all 0.4s ease-in-out;"
//				"-moz-transition: all 0.4s ease-in-out;"
//				"-ms-transition: all 0.4s ease-in-out;"
//				"-o-transition: all 0.4s ease-in-out;"
//				"transition: all 0.4s ease-in-out;"
//				"}"
//				"#q:hover { "
//				"background:#3D689C;"
//				"}"
				"canvas {"
				"position:absolute;"
				"top: 0px;"
				"right: 0px;"
				"z-index:-1;"
				"}"
				"</style>"
				"</head>";
}

void	get_body(std::stringstream &response, std::vector<t_content> &dir_content) {
	response << "<body>";
	response << "<canvas id=q></canvas>"
	"<script>"
	"const s = window.screen;"
	"const w = (q.width = s.width);"
	"const h = (q.height = s.height);"
	"const ctx = q.getContext(\"2d\");"
								 "const p = Array(Math.floor(w / 10) + 1).fill(0);"
	"const random = (items) => items[Math.floor(Math.random() * items.length)];"
	"const hex = \"0123456789ABCDEF\".split(\"\");"
	"setInterval(() => {"
	"	ctx.fillStyle = \"rgba(0,0,0,.05)\";"
	"	ctx.fillRect(0, 0, w, h);"
	"	ctx.fillStyle = \"#0f0\";"
	"	p.map((v, i) => {"
	"		ctx.fillText(random(hex), i * 10, v);"
	"		p[i] = v >= h || v > 50 + 10000 * Math.random() ? 0 : v + 10;"
	"	});"
	"	}, 1000 / 30);"
	"</script>";
	response << "<center>";
	response << "<div id=\"aaa\">";
	response <<	"<listing>";
	response << "<font color=\"white\" >";
	for (size_t i = 0; i < dir_content.size(); ++i)
	{
		if (dir_content[i].name[0] == '.' && dir_content[i].name != "..")
			continue;
//		<a href="URL">текст ссылки</a>
		if (dir_content[i].size == 0) // folder
			response << "<img src=\"https://icons-for-free.com/iconfiles/png/512/folder-131964753094019398.png\" width=\"20\" height=\"20\">";
		else //file
			response << "<img src=\"https://rubin-spb.ru/wp-content/uploads/2021/02/file.png\" width=\"20\" height=\"20\">";
		response << 	"<a href=\"";
		response << dir_content[i].name;
		response << "\" style=\"color: white\">";
		response << dir_content[i].name << "</a>";
		for (unsigned long j = 0; j < 20 - dir_content[i].name.size(); ++j) {
			response << " ";
		}
		response << "\t" << dir_content[i].size;
//		   << "\t" << dir_content[i].ref;
//		for (int j = 0; j < 20 - dir_content[i].ref.size(); ++j) {
//			response << " ";
//		}
		response << "\t" << dir_content[i].last_mode;
	}
}

void	get_close(std::stringstream &response){
	response << "</font>"
				"</listing>"
				"</div>"
				"</center>"
				"</body>"
		   		"</html>";
}

std::string get_autoindex(std::string &path, std::string &root){
	std::string str;
	std::vector<t_content> dir_content;
	std::stringstream response;

//	std::cout << path << " " << root << std::endl;

	str = get_dir_content(path, dir_content, root);
	get_title(response, path);
	get_body(response, dir_content);
	get_close(response);
	return response.str();
}