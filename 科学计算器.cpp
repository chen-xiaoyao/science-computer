//整数波兰式计算
#include<cstdio>
#include<cstdlib>
#include<cstdbool>
#include<cctype>
#include<climits>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#define LEN 100

//通过补0来让带有正负号情况变成全正情况，兼顾正确性判断，同时把一行全部读完，包括换行
bool Input(char str[])
{
	char ch;
	int p = 0;
	int left = 0, right = 0;

	ch = getchar();//先赋一个防止p-1越界
	if (ch == '+' || ch == '-')
	{
		str[p++] = '0';//补0情况1
	}
	if (ch == '(')//匹配括号的情况1
	{
		left++;
	}
	if (ch == ')')
	{
		right++;
	}
	str[p++] = ch;

	while ((ch = getchar()) != '\n')
	{
		//补0情况2/3,：左符号加正负号，以及左括号后加政府,简化，更改ch
		if (ispunct(str[p-1])
			&& (ch == '+' || ch == '-'))
		{
			str[p++] = '0';//补0
		}
		//数（，）数，）（，
		if ((isalnum(str[p - 1]) && ch == '(')
			|| (str[p - 1] == ')' && isalnum(ch))
			|| (str[p - 1] == ')' && ch == '('))
		{
			while (getchar() != '\n')
				continue;
			return false;//报错
		}
		//（op
		if (str[p - 1] == '(' 
			&& (ch == '*' || ch == '/' || ch == '%' || ch == '^'))
		{
			while (getchar() != '\n')
				continue;
			return false;//报错
		}
		//匹配括号的情况
		if (ch == '(')
			left++;
		if (ch == ')')
			right++;
		
		str[p++] = ch;
	}
	str[p] = '\0';//补上字符串结尾

	if (right != left)//括号匹配
	{
		//这里不用清理
		return false;
	}
		
	return true;//成功转化
}
//判断操作符优先级
int getPriority(char op)
{
	switch (op)//因为全部return，所以不加break了
	{
	case '+':
	case '-':
	{
		return 1;
	}
	case '*':
	case '/':
	case '%':
	{
		return 2;
	}
	case '^':
	{
		return 3;
	}
	default:
	{
		return -1;
	}
	}
}
//转化处理好的str到逆波兰式的queue，其中会将整数用&分节
void antiBolan(std::queue<char>& exp, char str[])
{
	//初始化
	std::stack<char>op;
	char ch, temp;
	bool innum = false;

	//利用op栈和exp队列构造  
	for (int i = 0; i < strlen(str); i++)
	{
		ch = str[i];

		if (isalnum(ch))//num  
		{
			if (!innum)//标记进入数字
				innum = true;
			exp.push(ch);
			//如果是最后一个数字，那么后面的步骤都没了，自然就无法给他加&
			if (i == strlen(str) - 1)
				exp.push('&');
		}
			
		else if (ch == '(' || ch == ')')//括号  
		{
			if (innum)//刚出数字，标记出数字，加&结尾
			{
				innum = false;
				exp.push('&');
			}

			if (ch == '(')
				op.push(ch);
			else //右括号，那么这个右括号就不操作了，中间包的操作符一起压入  
			{
				while (1)
				{
					temp = op.top();
					op.pop();//不管如何，先弹出，如果是好，就压，不然就break，顺便还扔掉左括号  
					if (temp == '(')
						break;
					else
						exp.push(temp);
				}
			}
		}
		else //op  
		{
			if (innum)//刚出数字，标记出数字，加&结尾
			{
				innum = false;
				exp.push('&');
			}

			while (1)//不断和op的top元素比较，直到碰到恰当的  
			{
				if (op.empty() || op.top() == '(')//如果是空的，或者顶部为），直接入  
				{
					op.push(ch);
					break;
				}
				if (getPriority(ch) > getPriority(op.top())
					||(ch=='^'&&op.top()=='^'))//这里注意二连^可以套
				{
					op.push(ch);
					break;
				}
				else
				{
					temp = op.top();
					op.pop();
					exp.push(temp);
				}
			}
		}
	}
	while (!op.empty())
	{
		temp = op.top();
		op.pop();
		exp.push(temp);
	}
}
void outAntiBolan(std::queue<char>exp)
{
	while (!exp.empty())
	{
		char top = exp.front();
		exp.pop();
		putchar(top);
	}
	putchar('\n');
}

int computeBolan(std::queue<char>exp)
{
	std::stack<int>ans;
	int a, b, c;
 	bool innum = false;
	char toInt[LEN];
	int p = 0;

	while (!exp.empty())
	{
		char temp = exp.front();
		exp.pop();

		if (isalnum(temp))//是数字
		{
			toInt[p++] = temp;//储存到临时字符串准备转化
			if (!innum)//进入数字状态
				innum = true;
		}
		else if (temp == '&')//是&
		{
			toInt[p] = '\0';//封口
			p = 0;//指针归零
			innum = false;//退出数字状态
			//puts(toInt);//输出验证
			ans.push(atoi(toInt));//转化并打入
		}
		else//这种temp就是op了
		{
			//弹出两个
			b = ans.top();
			ans.pop();
			a = ans.top();
			ans.pop();
			//判断计算，叠加错误判断
			switch (temp)
			{
			case '+':
			{
				ans.push(a + b);
				break;
			}
			case '-':
			{
				ans.push(a - b);
				break;
			}
			case '*':
			{
				ans.push(a * b);
				break;
			}
			case '/':
			{
				if (b == 0)//除数为0
				{
					puts("Divide 0.");
					return INT_MAX;//用int最大值标记，如果有好办法更好
				}
				ans.push(a / b);
				break;
			}
			case '%':
			{
				if (b == 0)//暂时不能对0求模
				{
					puts("error.");
					return INT_MAX;
				}
				ans.push(a % b);
				break;
			}
			case '^':
			{
				if (b < 0)
				{
					puts("error.");
					return INT_MAX;
				}
				ans.push((int)pow(a, b));
				break;
			}
			default :
			{
				puts("未知运算符");
			}
			}
		}
	}

	return ans.top();
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	int ans;
	//中缀转逆波兰式，包含预处理正负号优化，，压入时增加数字分割，判定公式正确
	//读取，并优化正负号，初步判断公式正确性
	char str[LEN];
	if (Input(str) == false)//报错情况
	{
		puts("error.");
		return 0;
	}
	//将str转换成逆波兰式，增加数字分割
	std::queue<char>exp;
	antiBolan(exp, str);
	//outAntiBolan(exp); //输出验证
	if ((ans = computeBolan(exp)) != INT_MAX)
	{
		printf("%d\n", ans);
	}
}

