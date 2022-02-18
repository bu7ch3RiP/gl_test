#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <stack>
#include <mutex>
#include <queue>
namespace fs = std::filesystem;
const std::string ROOT_PATH = "C:\\";

class Searcher
{
	fs::path path= "C:\\";
	bool found = false;
	std::queue<std::string> list_of_root_dir;
	std::mutex mtx;

public:

	Searcher() {};
	Searcher(const fs::path path);

	//work methods
	bool finder(const fs::path& path, std::string& file_name);
	void work(std::string& file_name);

	//getters
	fs::path get_current_dir();
	bool get_found();
	std::queue<std::string> get_list_of_root_dir();
	int get_size_of_dir_list();

	//setters
	void set_path(const fs::path& path);
	void set_found(const bool &found);
	void set_list_of_root_dir();
};

