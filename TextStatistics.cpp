
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
//Задачи: добавить ассинхронность, вывод статы в файл

bool flag_count_chars;

struct File {
	vector<string> lines;
	path path_to_file;
	int char_count = 0;
	int word_count = 0;
	unordered_map<char, int> count_each_char;
	unordered_map<string, int> count_each_word;
	vector<pair<char, int>> sorted_counts;
	vector<pair<string, int>> sorted_word_counts;

	void inf(int ier = 0) {
		string iers = "";
		for (int i = 0; i < ier; ++i) iers += "    ";
		cout << iers << "File name: " << path_to_file.filename() << endl;
		cout << iers << "Lines: " << lines.size() << endl;
		cout << iers << "Chars: " << char_count << endl;
		cout << iers << "Words: " << word_count << endl;

		if (flag_count_chars) {
			for (auto it = sorted_counts.begin(); it != sorted_counts.end(); ++it) {
				cout << iers << "'" << it->first << "': " << it->second << endl;
			}
		}
	}

	File logic(path path) {
		path_to_file = path;
		string line;
		ifstream file(path_to_file);
		while (getline(file, line)) {
			lines.push_back(line);
			char_count += line.length();
		}
		file.close();
		for (int i = 0; i < lines.size(); i++) {
			for (int j = 0; j < lines[i].length() - 1; j++) {
				count_each_char[lines[i][j]]++;
				if (isalpha(lines[i][j]) && !isalpha(lines[i][j + 1])) {
					word_count++;
				}
			}
		}

		for (auto it = count_each_char.begin(); it != count_each_char.end(); ++it) {
			sorted_counts.push_back(make_pair(it->first, it->second));
		}

		sort(sorted_counts.begin(), sorted_counts.end(), [](pair<char, int>& a, pair<char, int>& b) { return a.second > b.second; });

		//Считаем слова
		for (int i = 0; i < lines.size(); ++i) {
			int l = 0, r = 0;
			while (l < lines[i].length() && !isalpha(lines[i][l])) ++l;
			r = l + 1;
			while (r < lines[i].length() && isalpha(lines[i][r])) ++r;
			if (r <= lines[i].length()) {
				++count_each_word[lines[i].substr(l, r - l)];
			}
		}

		for (auto it = count_each_word.begin(); it != count_each_word.end(); ++it) {
			sorted_word_counts.push_back(make_pair(it->first, it->second));
		}

		sort(sorted_word_counts.begin(), sorted_word_counts.end(), [](pair<string, int>& a, pair<string, int>& b) { return a.second > b.second; });

		return *this;
	}
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

	void inf(int ier = 0) {
		string iers = "";
		for (int i = 0; i < ier; ++i) iers += "    ";
		cout << iers << "Folder name: " << path_to_folder.filename() << endl;
		cout << iers << "Lines: " << lines_count << endl;
		cout << iers << "Chars: " << char_count << endl;
		cout << iers << "Words: " << word_count << endl;

		if (flag_count_chars) {
			for (auto it = sorted_counts.begin(); it != sorted_counts.end(); ++it) {
				cout << iers << "'" << it->first << "': " << it->second << endl;
			}
		}

		for (auto& fold : all_folders) {
			fold.inf(ier+1);
		}
		for (auto& file : all_files) {
			file.inf(ier+1);
		}
	}

	Folder logic(path path) {
		path_to_folder = path;
		for (auto& entry : directory_iterator(path_to_folder)) {
			if (is_regular_file(entry.path()) && entry.path().extension() == ".txt") {
				all_files.push_back(File().logic(entry.path()));
				this->char_count += all_files.back().char_count;
				this->word_count += all_files.back().word_count;
				this->lines_count += all_files.back().lines.size();
				for (auto it = all_files.back().count_each_char.begin(); it != all_files.back().count_each_char.end(); ++it) {
					count_each_char[it->first] += it->second;
				}
				sorted_counts = vector<pair<char, int>>();
				for (auto it = count_each_char.begin(); it != count_each_char.end(); ++it) {
					sorted_counts.push_back(make_pair(it->first, it->second));
				}
				sort(sorted_counts.begin(), sorted_counts.end(), [](pair<char, int>& a, pair<char, int>& b) {return a.second > b.second; });
			}
			else if (is_directory(entry.path())){
				all_folders.push_back(Folder().logic(entry.path()));
				this->char_count += all_folders.back().char_count;
				this->word_count += all_folders.back().word_count;
				this->lines_count += all_folders.back().lines_count;
				for (auto it = all_folders.back().count_each_char.begin(); it != all_folders.back().count_each_char.end(); ++it) {
					count_each_char[it->first] += it->second;
				}
				sorted_counts = vector<pair<char, int>>();
				for (auto it = count_each_char.begin(); it != count_each_char.end(); ++it) {
					sorted_counts.push_back(make_pair(it->first, it->second));
				}
				sort(sorted_counts.begin(), sorted_counts.end(), [](pair<char, int>& a, pair<char, int>& b) {return a.second > b.second; });
				//тут ост
			}
		}
		return *this;
	}
};

int main()
{
	setlocale(LC_ALL, "Ru");
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);
	string path = "";
	while (!exists(path) || !is_directory(path)) {
		cout << "Введите путь(относительный) к папке с файлами .txt для которой нужно вывести статистику: ";
		getline(cin, path);
		if (!exists(path)) cout << "Такой папки не существует!" << endl;
		else if (!is_directory(path)) cout << "Это не папка!" << endl;
	}
	string flag = "";
	cout << "Флаги:\n1 - подсчёт отдельных символов\n2 - только основная статистика\nФлаг: ";
	getline(cin, flag);
	if (flag == "1") flag_count_chars = true;
	else flag_count_chars = false;
	Folder fol;
	fol.logic(path);
	fol.inf();

	cin.ignore(); //очистка буфера
	cin.get(); //ждёт нажатия Enter

	return 0;
}