#include "Polinom.h"

bool TPolinom::IsSign(char op)
{
	if (op == '+' || op == '-')
		return true;
	else return false;
}

bool TPolinom::IsVariable(char op)
{
	if (op == 'x' || op == 'y' | op == 'z')
		return true;
	else return false;
}

int TPolinom::GetDegree(char p)
{
	if (int(p) > 49 && int(p) < 58) 
		return int(p - 48);
	else return 1;
}

TPolinom::TPolinom(const TPolinom& pl)
{
	this->prefix = pl.prefix;
	this->polinom = pl.polinom;
}

void TPolinom::Convert()
{
	int begin = 0;
	bool sign = true;
	Monom monom;
	string num;
	TList<Monom>::iterator it;
	for (int i = 0; i < prefix.size(); i++)
	{
		monom = {};
		if (prefix[i] == '+')
		{
			sign = true;
			i++;
		}
		else if (prefix[i] == '-')
		{
			sign = false;
			i++;
		}
		if (!IsSign(prefix[i]) && !IsVariable(prefix[i]))
		{
			while (!IsVariable(prefix[i]) && i != prefix.size() && !IsSign(prefix[i]))
			{
				num += prefix[i];
				i++;
			}
			monom.koef = atof(num.c_str());
			num = "";
		}
		begin = i;
		if (IsVariable(prefix[i]))
		{
			int x = 0, y = 0, z = 0, sum;
			while (!IsSign(prefix[i]) && i != prefix.size())
			{
				switch (prefix[i])
				{
				case 'x':
				{
					x = GetDegree(prefix[i + 1]);
					i++;
					break;
				}
				case 'y':
				{
					y = GetDegree(prefix[i + 1]);
					i++;
					break;
				}
				case 'z':
				{
					z = GetDegree(prefix[i + 1]);
					i++;
					break;
				}
				default:
					i++;
				}
			}
			i--;
			sum = x * 100 + y * 10 + z;
			monom.name = prefix.substr(begin, i - begin + 1);
			monom.deg = sum;
			if (!sign)
				monom.koef = monom.koef * (-1);
		}
		if (polinom.IsEmpty())
		{
			polinom.PushBack(monom);
			continue;
		}
		for (it = polinom.Begin(); it != polinom.End(); ++it)
		{
			if (monom.deg == it->data.deg)
			{
				it->data.koef = it->data.koef + monom.koef;
				if (it->data.koef == 0)
					polinom.Erase(it);
				break;
			}
			if (monom.deg > it->data.deg)
			{
				polinom.Insert(it, monom);
				break;
			}
		}
		if (it == polinom.End())
			polinom.PushBack(monom);
	}
}

int TPolinom::CalculateInPoint(int _x, int _y, int _z)
{
	int result = 0;
	for (auto it = polinom.Begin(); it != polinom.End(); ++it)
	{
		int x = it->data.deg / 100, y = (it->data.deg / 10) % 10, z = it->data.deg % 10;
		result += (pow(_x, x) * pow(_y, y) * pow(_z, z)) * it->data.koef;
	}
	return result;
}

TPolinom TPolinom::Sort()
{
	if (this->polinom.IsEmpty())
		throw "Polinom is empty";
	TPolinom res;
	TList<Monom>::iterator right, left, max;
	for (right = this->polinom.Begin(); right != this->polinom.End();++right)
	{
		max->data = right->data;
		for (left = right; left != this->polinom.End(); ++left)
		{
			if (right->data.deg < left->data.deg)
			{
				max->data = left->data;
				left->data = right->data;
				right->data = max->data;
			}
		}
	}
	return *this;
}

TPolinom TPolinom::operator+(TPolinom& pl)
{
	if (this->polinom.IsEmpty() || pl.polinom.IsEmpty())
		throw "Polinom is empty";
	TPolinom result;
	TList<Monom>::iterator right, left;
	bool check = false;
	for (right = pl.polinom.Begin(); right != pl.polinom.End(); ++right)
	{
		check = false;
		for (left = this->polinom.Begin(); left != this->polinom.End(); ++left)
			if (right->data.deg == left->data.deg)
			{
				if ((left->data.koef + right->data.koef) != 0)
					result.polinom.PushBack(*(left)+*(right));
				check = true;
			}
		if (check == false)
			result.polinom.PushBack(*right);
	}
	check = false;
	for (left = this->polinom.Begin(); left != this->polinom.End(); ++left)
	{
		check = false;
		right = pl.polinom.Begin();
		for (right = pl.polinom.Begin(); right != pl.polinom.End(); ++right)
			if (left->data.deg == right->data.deg)
				check = true;
		if (check == false)
			result.polinom.PushBack(*left);
	}
	if (result.polinom.IsEmpty())
	{
		right = pl.polinom.Begin();
		right->data.koef = 0;
		right->data.name = "";
		right->data.deg = 0;
		result.polinom.PushBack(*right);
	}
	return result.Sort();
}

TPolinom TPolinom::operator-(TPolinom& pl)
{
	if (this->polinom.IsEmpty() || pl.polinom.IsEmpty())
		throw "Polinom is empty";
	TPolinom result;
	TList<Monom>::iterator right, left;
	bool check = false;
	for (right = pl.polinom.Begin(); right != pl.polinom.End(); ++right)
	{
		check = false;
		for (left = this->polinom.Begin(); left != this->polinom.End(); ++left)
			if (right->data.deg == left->data.deg)
			{
				if ((left->data.koef - right->data.koef) != 0)
				{
					result.polinom.PushBack(*(left)-*(right));
				}
				check = true;
			}
		if (check == false)
		{
			int koef = right->data.koef;
			right->data.koef = (-1)*right->data.koef;
			result.polinom.PushBack(*right);
			right->data.koef = koef;
		}
	}
	check = false;
	for (left = this->polinom.Begin(); left != this->polinom.End(); ++left)
	{
		check = false;
		right = pl.polinom.Begin();
		for (right = pl.polinom.Begin(); right != pl.polinom.End(); ++right)
			if (left->data.deg == right->data.deg)
				check = true;
		if (check == false)
			result.polinom.PushBack(*left);
	}
	return result.Sort();
}

TPolinom TPolinom::operator*(TPolinom& pl)
{
	if (this->polinom.IsEmpty() || pl.polinom.IsEmpty())
		throw "Polinom is empty";
	TPolinom result;
	TList<Monom>::iterator right, left;
	for (right = this->polinom.Begin(); right != this->polinom.End();)
	{
		for (left = pl.polinom.Begin(); left != this->polinom.End();)
		{
			if ((right->data.koef * left->data.koef) != 0)
				result.polinom.PushBack((*(right)) * (*(left)));
			++left;
		}
		++right;
	}
	while (left != pl.polinom.End())
	{
		result.polinom.PushBack(*left);
		++left;
	}
	return result.Sort();
}

TPolinom& TPolinom::operator=(const TPolinom& pl)
{
	this->polinom = pl.polinom;
	this->prefix = pl.prefix;
	return *this;
}

bool TPolinom::operator==(const TPolinom& pl)const
{
	if (this->prefix == pl.prefix)
		return true;
	else return false;
}

ostream& operator<<(ostream& os, TPolinom& pl)
{
	if (pl.polinom.IsEmpty())
		os << pl.prefix;
	else
	{
		for (auto it = pl.polinom.Begin(); it != pl.polinom.End(); ++it)
		{
			if (it->data.deg != 0)
			{
				if (it != pl.polinom.Begin() && it->data.koef > 0)
					os << '+';
				if ((it->data.koef != 1) && (it->data.koef != -1))
				{
					os << it->data.koef;
					os << it->data.name;
				}
				if (it->data.koef == 1)
					os << it->data.name;
				if (it->data.koef == -1)
				{
					os << '-';
					os << it->data.name;
				}
			}
			else
			{
				if (it != pl.polinom.Begin() && it->data.koef > 0)
					os << '+';
				os << it->data.koef;
			}
		}
	}
	return os;
}

istream& operator>>(istream& is, TPolinom& pl)
{
	for (auto it = pl.polinom.Begin(); it != pl.polinom.End(); ++it)
	{
		if ((it->data.koef != 1) && (it->data.name != "\0"))
		{
			is >> it->data.koef;
			is >> it->data.name;
		}
		if (it->data.name == "\0")
			is >> it->data.koef;
		if (it->data.koef == 1)
			is >> it->data.name;
	}
	return is;
}

void TPolinom::SaveInFile(TPolinom& polinom1, TPolinom& polinom2, TPolinom& multiplication, TPolinom& subtraction, TPolinom& addition)
{ 
	ofstream out;
	out.open("Polinom.txt");
	if (out.is_open())
	{
		out << "Исходные полиномы:" << endl;
		out << "F = " << polinom1 << endl;
		out << "G = " << polinom2 << endl;
		out << "Результаты исчислений:" << endl;
		out << "F*G = " << multiplication << endl;
		out << "F-G = " << subtraction << endl;
		out << "F+G = " << addition << endl;
	}
	out.close();
}

void TPolinom::SaveInFile(TPolinom& polinom1, TPolinom& polinom2, TPolinom& multiplication, 
	int calMultiplication, TPolinom& subtraction, int calSubtraction, TPolinom& addition, int calAddition, int _x, int _y, int _z)
{
	ofstream out;
	out.open("Polinom.txt");
	if (out.is_open())
	{
		out << "Исходные полиномы:" << endl;
		out << "F = " << polinom1 << endl;
		out << "G = " << polinom2 << endl;
		out << "Результаты исчислений:" << endl;
		out << "F*G = " << multiplication << endl;
		out << "F*G(" << _x << "," << _y << "," << _z << ") = " << calMultiplication << endl;
		out << "F-G = " << subtraction << endl;
		out << "F-G(" << _x << "," << _y << "," << _z << ") = " << calSubtraction << endl;
		out << "F+G = " << addition << endl;
		out << "F+G(" << _x << "," << _y << "," << _z << ") = " << calAddition << endl;
	}
	out.close();
}

void TPolinom::ReadFile()
{
	string line;
	ifstream in("Polinom.txt"); 
	if (in.is_open())
		while (getline(in, line))
			cout << line << endl;
	in.close();                
}

string TPolinom::GetPrefix()
{
	return this->prefix;
}