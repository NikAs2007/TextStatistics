#include "TextStatistics.h"

Folder::Folder() : thread_pool(thread::hardware_concurrency()){}

Folder::Folder(const Folder& fol) : thread_pool(thread::hardware_concurrency()) {
	path_to_folder = fol.path_to_folder;
	all_files = fol.all_files;
	all_folders = fol.all_folders;

	char_count = fol.char_count;
	word_count = fol.word_count;
	lines_count = fol.lines_count;
	count_each_char = fol.count_each_char;
	sorted_counts = fol.sorted_counts;
	count_each_word = fol.count_each_word;
	sorted_words_counts = fol.sorted_words_counts;
}

void Folder::operator=(const Folder& fol) {
	path_to_folder = fol.path_to_folder;
	all_files = fol.all_files;
	all_folders = fol.all_folders;

	char_count = fol.char_count;
	word_count = fol.word_count;
	lines_count = fol.lines_count;
	count_each_char = fol.count_each_char;
	sorted_counts = fol.sorted_counts;
	count_each_word = fol.count_each_word;
	sorted_words_counts = fol.sorted_words_counts;
}

void Folder::inf(Flags flags, int ier) {
	string iers = "";
	for (int i = 0; i < ier; ++i) iers += "    ";
	cout << iers << "Папка: " << path_to_folder.filename() << endl;
	cout << iers << "Количество строк: " << lines_count << endl;
	cout << iers << "Количество символов: " << char_count << endl;
	cout << iers << "Количество слов: " << word_count << endl;
	cout << endl;

	if (flags.inf_chars) {
		cout << iers << "Список символов:\n";
		for (auto it = sorted_counts.begin(); it != sorted_counts.end(); ++it) {
			cout << iers << "'" << it->first << "': " << it->second << endl;
		}
		cout << "\n";
	}

	if (flags.inf_words) {
		cout << iers << "Список слов:\n";
		for (auto it = sorted_words_counts.begin(); it != sorted_words_counts.end(); ++it) {
			cout << iers << "'" << it->first << "': " << it->second << endl;
		}
		cout << "\n";
	}

	if (flags.inf_chars || flags.inf_words) cout << endl;

	for (auto& fold : all_folders) {
		fold.inf(flags, ier + 1);
	}
	for (auto& file : all_files) {
		file.inf(flags, ier + 1);
	}
}

Folder Folder::logic(path path) {
	path_to_folder = path;
	for (auto& entry : directory_iterator(path_to_folder)) {
		if (is_regular_file(entry.path()) && entry.path().extension() == ".txt") {
			all_files.push_back(File().logic(entry.path()));

			//thread_pool.emplace([this, entry]() { all_files.push_back(File().logic(entry.path()));
			//this->char_count += all_files.back().char_count;
			//this->word_count += all_files.back().word_count;
			//this->lines_count += all_files.back().lines.size();
			//for (auto it = all_files.back().count_each_char.begin(); it != all_files.back().count_each_char.end(); ++it) {
			//	count_each_char[it->first] += it->second;
			//}
			//sorted_counts = vector<pair<char, int>>();
			//for (auto it = count_each_char.begin(); it != count_each_char.end(); ++it) {
			//	sorted_counts.push_back(make_pair(it->first, it->second));
			//}
			//sort(sorted_counts.begin(), sorted_counts.end(), [](pair<char, int>& a, pair<char, int>& b) {return a.second > b.second; });

			//for (auto it = all_files.back().count_each_word.begin(); it != all_files.back().count_each_word.end(); ++it) {
			//	count_each_word[it->first] += it->second;
			//}
			//sorted_words_counts = vector<pair<string, int>>();
			//for (auto it = count_each_word.begin(); it != count_each_word.end(); ++it) {
			//	sorted_words_counts.push_back(make_pair(it->first, it->second));
			//}
			//sort(sorted_words_counts.begin(), sorted_words_counts.end(), [](pair<string, int>& a, pair<string, int>& b) {return a.second > b.second; });
			//	
			//	
			//	
			//});

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

			for (auto it = all_files.back().count_each_word.begin(); it != all_files.back().count_each_word.end(); ++it) {
				count_each_word[it->first] += it->second;
			}
			sorted_words_counts = vector<pair<string, int>>();
			for (auto it = count_each_word.begin(); it != count_each_word.end(); ++it) {
				sorted_words_counts.push_back(make_pair(it->first, it->second));
			}
			sort(sorted_words_counts.begin(), sorted_words_counts.end(), [](pair<string, int>& a, pair<string, int>& b) {return a.second > b.second; });
		}
		else if (is_directory(entry.path())) {
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
			
			for (auto it = all_folders.back().count_each_word.begin(); it != all_folders.back().count_each_word.end(); ++it) {
				count_each_word[it->first] += it->second;
			}
			sorted_words_counts = vector<pair<string, int>>();
			for (auto it = count_each_word.begin(); it != count_each_word.end(); ++it) {
				sorted_words_counts.push_back(make_pair(it->first, it->second));
			}
			sort(sorted_words_counts.begin(), sorted_words_counts.end(), [](pair<string, int>& a, pair<string, int>& b) {return a.second > b.second; });
		}
	}
	return *this;
}
