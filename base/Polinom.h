#include "List.h"
const int DEG_MAX = 10;

struct Monom
{
	int koef;
	int deg;
	string name;
	Monom(int _k = 1, int _d = 0)
	{
		koef = _k;
		deg = _d;
	}
	Monom operator +(const Monom& mn)
	{
		if (this->deg != mn.deg)
			throw "incorrect addition";
		Monom tmp;
		tmp.koef = this->koef + mn.koef;
		tmp.deg = this->deg;
		tmp.name = this->name;
		return tmp;
	}
	Monom operator -(const Monom& mn)
	{
		if (this->deg != mn.deg)
			throw "incorrect subtraction";
		Monom tmp;
		tmp.koef = this->koef - mn.koef;
		tmp.deg = this->deg;
		tmp.name = this->name;
		return tmp;
	}
	Monom operator *(const Monom& mn)
	{
		Monom tmp;
		tmp.koef = this->koef * mn.koef;
		tmp.deg = this->deg + mn.deg;
		int a = tmp.deg / 100, b = (tmp.deg / 10) % 10, c = tmp.deg % 10;
		string _a, _b, _c;
		_a = to_string(a);
		_b = to_string(b);
		_c = to_string(c);
		string _name = "";
		if ((a != 0) && (a != 1))
			_name = _name + "x" + _a;
		if ((b != 0) && (b != 1))
			_name = _name + "y" + _b;
		if ((c != 0) && (c != 1))
			_name = _name + "z" + _c;
		if (a == 1)
			_name = _name + "x";
		if (b == 1)
			_name = _name + "y";
		if (c == 1)
			_name = _name + "z";
		tmp.name = _name;
		return tmp;
	}
};

class TPolinom
{
private:
	string prefix;
	TList<Monom> polinom;

	bool IsSign(char op);
	bool IsVariable(char op);
	int GetDegree(char p);

public:
	TPolinom(string _str = "") :prefix(_str) {}
	TPolinom(const TPolinom& pl);
	void Convert();
	int CalculateInPoint(int _x, int _y, int _z);
	TPolinom operator+(TPolinom& pl);
	TPolinom operator-(TPolinom& pl);
	TPolinom operator*(TPolinom& pl);
	TPolinom& operator=(const TPolinom& pl);
	friend ostream& operator<<(ostream& os, TPolinom& pl);
	friend istream& operator>>(istream& is, TPolinom& pl);
	bool operator == (const TPolinom& pl)const;
	void SaveInFile(TPolinom& polinom1, TPolinom& polinom2, TPolinom& multiplication, TPolinom& subtraction, TPolinom& addition);
	void SaveInFile(TPolinom& polinom1, TPolinom& polinom2, TPolinom& multiplication, int calMultiplication, 
		TPolinom& subtraction, int calSubtraction, TPolinom& addition, int calAdditio, int _x, int _y, int _z);
	void ReadFile();
	TPolinom Sort();
	string GetPrefix();
};