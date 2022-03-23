#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

class Calculator
{
public:
	//加减乘除，输入string，拆分，操作，返回string
	//不化简，化简使用simplify手动操作
	string plus(string left, string right)
	{
		int lu, ru, ld, rd;
		one_down(left, right, lu, ld, ru, rd);
		
		return frac(lu + ru, ld);
	}
	string minus(string left, string right)
	{
		int lu, ru, ld, rd;
		one_down(left, right, lu, ld, ru, rd);

		return frac(lu - ru, ld);

	}
	string multiply(string left, string right)
	{
		int lu, ru, ld, rd;
		split(left, lu, ld);
		split(right, ru, rd);

		return frac(lu * ru, ld * rd);
	}
	string divide(string left, string right)
	{
		int lu, ru, ld, rd;
		split(left, lu, ld);
		split(right, ru, rd);
		if (ru == 0)
			return "error! 0 devisor!";

		return frac(lu * rd, ld * ru);
	}
	//简化分数，输入分数，返回分数
	string simplify(string x)
	{
		int up, down;
		split(x, up, down);
		//约数
		int gcd_num = gcd(up, down);
		up /= gcd_num;
		down /= gcd_num;
		//返回结果
		string res(to_string(up));
		if (down != 1)
		{
			res += ("/" + to_string(down));
		}

		return res;
	}
	//通分两个分数，目前暴力通，后面进行巧妙通
	void one_down(string left, string right,
		int& lu, int& ld, int& ru, int& rd)
	{
		split(left, lu, ld);
		split(right, ru, rd);

		lu *= rd;
		ru *= ld;
		ld *= rd;
		rd = ld;
	}
	void test()
	{
		
	}
private:
	//统一所有分数的形式，整数为分母1.特殊地，0变成0/1
	string unify(string x)
	{
		int pos = x.find('/');
		if (pos == x.npos)
			return x += "/1";
		else
			return x;
	}
	//拆分分母分子，使用引用返回，基于unify
	void split(string x, int& up, int& down)
	{
		x = unify(x); //统一形式

		int pos = x.find('/');
		//取子串后转化
		up = stoi(x.substr(0, pos));
		down = stoi(x.substr(pos + 1));
	}
	//组合分母分子，返回统一形式
	string frac(int up, int down=1)
	{
		return string(to_string(up) + "/" + to_string(down));
	}
	//求最大公因数
	int gcd(int a, int b)
	{
		if (a % b == 0)
		{
			return b;
		}
		else
		{
			return gcd(b, a % b);
		}
	}
};

int main(void)
{
	Calculator calc;
	//读取
	string left, right;
	char op;

	cin >> left >> op >> right;
	switch (op)
	{
	case '+': cout << left << " " << op << " " << right << " = " 
		<< calc.simplify(calc.plus(left, right)) << endl;
		break;
	case'-': cout << left << " " << op << " " << right << " = "
		<< calc.simplify(calc.minus(left, right)) << endl;
		break;
	case '*': cout << left << " " << op << " " << right << " = "
		<< calc.simplify(calc.multiply(left, right)) << endl;
		break;
	case '/': cout << left << " " << op << " " << right << " = "
		<< calc.simplify(calc.divide(left, right)) << endl;
		break;
	}

	return 0;
}
