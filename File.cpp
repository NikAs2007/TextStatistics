#include "TextStatistics.h"


void File::inf(Flags flags, int ier) {
	string iers = "";
	for (int i = 0; i < ier; ++i) iers += "    ";
	cout << iers << "File name: " << path_to_file.filename() << endl;
	cout << iers << "Lines: " << lines.size() << endl;
	cout << iers << "Chars: " << char_count << endl;
	cout << iers << "Words: " << word_count << endl;

	if (flags.inf_chars) {
		for (auto it = sorted_counts.begin(); it != sorted_counts.end(); ++it) {
			cout << iers << "'" << it->first << "': " << it->second << endl;
		}
	}

	if (flags.inf_words) {
		for (auto it = sorted_word_counts.begin(); it != sorted_word_counts.end(); ++it) {
			cout << iers << "'" << it->first << "': " << it->second << endl;
		}
	}
}

File File::logic(path path) {
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

	//—читаем слова
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
