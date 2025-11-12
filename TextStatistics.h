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
//#include <windows.h>
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

	void inf(Flags flags, int ier = 0);
	Folder logic(path path);
};

class Manager {
	bool stop = false;
	Flags flags;

	void flags_asking() {
		if (flags.inf_chars) cout << "Символы - Включено [1]\n";
		else cout << "Символы - Выключено [1]\n";
		if (flags.inf_words) cout << "Слова - Включено [2]\n";
		else cout << "Слова - Выключено [2]\n";
		string chose;
		getline(cin, chose);
		if (chose == "1") flags.inf_chars = !flags.inf_chars;
		else if (chose == "2") flags.inf_words = !flags.inf_words;
		cout << endl;
	}

public:
	void asking() {
		while (!stop) {
			//Добавить обработку кавычек
			string path;
			cout << "Введите путь к файлу/папке (Закрыть программу - \"-\"): ";
			getline(cin, path);
			if (path == "-") {
				stop = true;
				return;
			}
			if (exists(path)) {
				cout << "Вывести статистику [1]\nИзменить флаги [2]\nВведите число: ";
				string move;
				getline(cin, move);
				if (move == "1") {
					if (is_directory(path)) {
						Folder fol;
						fol.logic(path);
						fol.inf(flags);
					}
					else {
						File fil;
						fil.logic(path);
						fil.inf(flags);
					}
				}
				else if (move == "2") {
					flags_asking();
				}
				else {
					cout << "Такой команды нет!\n\n";
				}
			}
			else {
				cout << "Неправильный путь!\n\n";
			}
		}
	}


};

#endif //TEXTSTATISTICS_H