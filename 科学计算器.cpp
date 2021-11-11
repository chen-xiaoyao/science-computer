//��������ʽ����
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

//ͨ����0���ô���������������ȫ������������ȷ���жϣ�ͬʱ��һ��ȫ�����꣬��������
bool Input(char str[])
{
	char ch;
	int p = 0;
	int left = 0, right = 0;

	ch = getchar();//�ȸ�һ����ֹp-1Խ��
	if (ch == '+' || ch == '-')
	{
		str[p++] = '0';//��0���1
	}
	if (ch == '(')//ƥ�����ŵ����1
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
		//��0���2/3,������ż������ţ��Լ������ź������,�򻯣�����ch
		if (ispunct(str[p-1])
			&& (ch == '+' || ch == '-'))
		{
			str[p++] = '0';//��0
		}
		//������������������
		if ((isalnum(str[p - 1]) && ch == '(')
			|| (str[p - 1] == ')' && isalnum(ch))
			|| (str[p - 1] == ')' && ch == '('))
		{
			while (getchar() != '\n')
				continue;
			return false;//����
		}
		//��op
		if (str[p - 1] == '(' 
			&& (ch == '*' || ch == '/' || ch == '%' || ch == '^'))
		{
			while (getchar() != '\n')
				continue;
			return false;//����
		}
		//ƥ�����ŵ����
		if (ch == '(')
			left++;
		if (ch == ')')
			right++;
		
		str[p++] = ch;
	}
	str[p] = '\0';//�����ַ�����β

	if (right != left)//����ƥ��
	{
		//���ﲻ������
		return false;
	}
		
	return true;//�ɹ�ת��
}
//�жϲ��������ȼ�
int getPriority(char op)
{
	switch (op)//��Ϊȫ��return�����Բ���break��
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
//ת������õ�str���沨��ʽ��queue�����лὫ������&�ֽ�
void antiBolan(std::queue<char>& exp, char str[])
{
	//��ʼ��
	std::stack<char>op;
	char ch, temp;
	bool innum = false;

	//����opջ��exp���й���  
	for (int i = 0; i < strlen(str); i++)
	{
		ch = str[i];

		if (isalnum(ch))//num  
		{
			if (!innum)//��ǽ�������
				innum = true;
			exp.push(ch);
			//��������һ�����֣���ô����Ĳ��趼û�ˣ���Ȼ���޷�������&
			if (i == strlen(str) - 1)
				exp.push('&');
		}
			
		else if (ch == '(' || ch == ')')//����  
		{
			if (innum)//�ճ����֣���ǳ����֣���&��β
			{
				innum = false;
				exp.push('&');
			}

			if (ch == '(')
				op.push(ch);
			else //�����ţ���ô��������žͲ������ˣ��м���Ĳ�����һ��ѹ��  
			{
				while (1)
				{
					temp = op.top();
					op.pop();//������Σ��ȵ���������Ǻã���ѹ����Ȼ��break��˳�㻹�ӵ�������  
					if (temp == '(')
						break;
					else
						exp.push(temp);
				}
			}
		}
		else //op  
		{
			if (innum)//�ճ����֣���ǳ����֣���&��β
			{
				innum = false;
				exp.push('&');
			}

			while (1)//���Ϻ�op��topԪ�رȽϣ�ֱ������ǡ����  
			{
				if (op.empty() || op.top() == '(')//����ǿյģ����߶���Ϊ����ֱ����  
				{
					op.push(ch);
					break;
				}
				if (getPriority(ch) > getPriority(op.top())
					||(ch=='^'&&op.top()=='^'))//����ע�����^������
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

		if (isalnum(temp))//������
		{
			toInt[p++] = temp;//���浽��ʱ�ַ���׼��ת��
			if (!innum)//��������״̬
				innum = true;
		}
		else if (temp == '&')//��&
		{
			toInt[p] = '\0';//���
			p = 0;//ָ�����
			innum = false;//�˳�����״̬
			//puts(toInt);//�����֤
			ans.push(atoi(toInt));//ת��������
		}
		else//����temp����op��
		{
			//��������
			b = ans.top();
			ans.pop();
			a = ans.top();
			ans.pop();
			//�жϼ��㣬���Ӵ����ж�
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
				if (b == 0)//����Ϊ0
				{
					puts("Divide 0.");
					return INT_MAX;//��int���ֵ��ǣ�����кð취����
				}
				ans.push(a / b);
				break;
			}
			case '%':
			{
				if (b == 0)//��ʱ���ܶ�0��ģ
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
				puts("δ֪�����");
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
	//��׺ת�沨��ʽ������Ԥ�����������Ż�����ѹ��ʱ�������ַָ�ж���ʽ��ȷ
	//��ȡ�����Ż������ţ������жϹ�ʽ��ȷ��
	char str[LEN];
	if (Input(str) == false)//�������
	{
		puts("error.");
		return 0;
	}
	//��strת�����沨��ʽ���������ַָ�
	std::queue<char>exp;
	antiBolan(exp, str);
	//outAntiBolan(exp); //�����֤
	if ((ans = computeBolan(exp)) != INT_MAX)
	{
		printf("%d\n", ans);
	}
}

