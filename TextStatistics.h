#ifndef TEXTSTATISTICS_H
#define TEXTSTATISTICS_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <thread>
using namespace std;
using namespace std::filesystem;

struct Flags {
	bool inf_chars = false;
	bool inf_words = false;
};

struct File {
	vector<string> lines;
	path path_to_file;
	int char_count = 0;
	int word_count = 0;
	unordered_map<char, int> count_each_char;
	unordered_map<string, int> count_each_word;
	vector<pair<char, int>> sorted_counts;
	vector<pair<string, int>> sorted_word_counts;

	void inf(Flags flags, int ier = 0);
	File logic(path path);
};

struct Folder {
	path path_to_folder;
	vector<File> all_files;
	vector<Folder> all_folders;

	int char_count = 0;
	int word_count = 0;
	int lines_count = 0;
	unordered_map<char, int> count_each_char;
	vector<pair<char, int>> sorted_counts;
	unordered_map<string, int> count_each_word;
	vector<pair<string, int>> sorted_words_counts;

	void inf(Flags flags, int ier = 0);
	Folder logic(path path);
};

class Manager {
	bool stop = false;
	Flags flags;

	void flags_asking();

public:
	void asking();
};

#endif //TEXTSTATISTICS_H