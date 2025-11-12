
#include "TextStatistics.h"
//Задачи: добавить ассинхронность, вывод статы в файл

int main()
{
	setlocale(LC_ALL, "Ru");
	Manager man;
	man.asking();

	cin.ignore(); //очистка буфера
	cin.get(); //ждёт нажатия Enter

	return 0;
}