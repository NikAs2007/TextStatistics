#include "TextStatistics.h"



void Manager::flags_asking() {
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

void Manager::asking() {
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