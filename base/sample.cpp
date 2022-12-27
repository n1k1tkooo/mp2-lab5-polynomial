#include "Polinom.h"
#include "string.h"
void main()
{
	setlocale(LC_ALL, "ru");
	string pol1, pol2;
	cout << "Введите первый полином: ";
	cin >> pol1;
	cout << "Введите второй полином: ";
	cin >> pol2;
	string chance;
	int x = 0, y = 0, z = 0;
	int calAddition, calSubtraction, calMultiplication;
	TPolinom polinom1(pol1), polinom2(pol2);
	TPolinom addition, subtraction, multiplication;
	polinom1.Convert();
	polinom2.Convert();
	addition = polinom1 + polinom2;
	multiplication = polinom1 * polinom2;
	subtraction = polinom1 - polinom2;
	cout << "Хотите ли Вы вывести произведенные вычисления? Введите 'yes' или 'no'." << endl;
	cin >> chance;
	if (chance == "yes")
	{
		cout << "Первый полином: F = " << polinom1 << endl;
		cout << "Второй полином: G = " << polinom2 << endl;
		cout << "Умножение F*G = " << multiplication << endl;
		cout << "Вычитание F-G = " << subtraction << endl;
		cout << "Сложение F+G = " << addition << endl;
	}
	cout << "Хотите ли Вы найти значение в точке? Введите 'yes' или 'no'." << endl;
	cin >> chance; 
	if (chance == "yes")
	{
		cout << "Введите значение переменной x: " << endl;
		cin >> x;
		cout << "Введите значение переменной y: " << endl;
		cin >> y;
		cout << "Введите значение переменной z: " << endl;
		cin >> z;
		cout << "Первый полином: F = " << polinom1 << endl;
		cout << "Второй полином: G = " << polinom2 << endl;
		calAddition = addition.CalculateInPoint(x, y, z);
		cout << "F+G(" << x << "," << y << "," << z << ") = " << calAddition << endl;
		calMultiplication = multiplication.CalculateInPoint(x, y, z);
		cout << "F*G(" << x << "," << y << "," << z << ") = " << calMultiplication << endl;
		calSubtraction = subtraction.CalculateInPoint(x, y, z);
		cout << "F-G(" << x << "," << y << "," << z << ") = " << calSubtraction << endl;
	}
	cout << "Хотите ли Вы сохранить результаты в файл? Введите 'yes' или 'no'." << endl;
	cin >> chance;
	if (chance == "yes")
	{
		if (x==0 && y==0 && z==0)
			polinom1.SaveInFile(polinom1, polinom2, multiplication, subtraction, addition);
		else
			polinom1.SaveInFile(polinom1, polinom2, multiplication, calMultiplication, subtraction, calSubtraction, addition, calAddition, x, y, z);
	}
	cout << "Хотите ли Вы считать из файла произведенные вычисления? Введите 'yes' или 'no'." << endl;
	cin >> chance;
	if (chance == "yes")
		polinom1.ReadFile();
}