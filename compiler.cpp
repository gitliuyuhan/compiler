#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>
#include<stack>

#define K_DIGIT       3      //整数
#define K_CHAR        4      //字符
#define K_STRING      5      //字符串
#define K_TYPE        6      //数据类型
#define K_KEYWORDS    7      //关键字
#define K_OPERATOR    8      //运算符
#define K_IDENTIFIER  9      //标识符
#define K_BRACKET     10     //括号

using namespace std;

//存储分词类型
typedef struct IDwords
{
	int       id;     //标志
	string    word;   //单词
}IDwords;

typedef struct Variable
{
	string   var;    //变量
	string   value;  //初始化值
}Variable;

//目标代码元素
typedef struct Target
{
	string    dsf;    //结果
	string    op;     //操作
	string    dst;    //目的操作数
	string    dsc;    //源操作数
	string    mark;   //标志
	string    step;   //跳转位置
}Target;

//保存声明变量
vector<Variable>      var_table;
//保存目标代码
vector<Target>        target_code;


char                  lab='A'; //记录跳转标志
char                  vab='A'; //记录中间变量

//生成的汇编文件名称
string  asmfile(string source)
{
	if(source.size()==0)
	{
		cout<<"源文件名不能为空"<<endl;
		exit(-1);
	}
	string temp="";
	int i,j;
	j = source.size();
    for(i = j-1;i>=0;i--)
	{
//		if(source[i] == '\\' || source[i]== '/')
//			break;
		if(source[i] == '.')
		{
			j = i;
			break;
		}
	}
	temp = source.substr(0,j) + ".asm";
	return temp;
}

//运算符优先级
int level(string s)
{
	if(s=="#")
		return 1;
	else if(s=="=")
		return 2;
	else if(s=="+" || s=="-")
		return 3;
	else if(s=="*" || s=="/")
		return 4;
	else
		return -1;
}


//保存到目标代码
void add_target_code(string dsf,string op,string dst,string dsc,string mark,string step)
{
	Target  tmp;
	tmp.dsf = dsf;
	tmp.op = op;
	tmp.dst = dst;
	tmp.dsc = dsc;
	tmp.mark = mark;
	tmp.step = step;
	target_code.push_back(tmp);
}

//字符转字符串
string char_to_str(char c)
{
	char s[2] = " ";
	s[0] = c;
	return string(s);
}

//是否为运算操作符
int is_operator(char c)
{
	if(c == '+' || c=='-'||c=='*'||c=='/'||c==','||c=='=' ||c=='>' || c=='<')
		return 1;
	else
		return 0;
}

//是否为大括号、小括号、分号
int is_bracket(char c)
{
	if(c=='{' || c=='}' || c=='(' || c==')' ||c==';')
		return 1;
	else
		return 0;
}

//是否为空白
int is_blank(char c)
{
	if(c=='\n' || c=='\t' || c==' ' || c=='\r')
		return 1;
	else
		return 0;
}

//判断单词类型
int word_token(string s)
{
	int    size = s.size();
	//字符数据
	if(s[0]=='\'')
	{
		if(s[size-1] == '\'')
			return K_CHAR;
		else
		{
			cout<<"错误的字符串数据："<<s<<endl;
			exit(-1);
		}
	}
	//字符串数据
	else if(s[0]=='\"')
	{
		if(s[size-1]=='\"')
			return K_STRING;
		else
		{
            cout<<"错误的字符串数据："<<s<<endl;
			exit(-1);
		}
	}
	//整数
	else if(isdigit(s[0]))
	{
		for(int i=1;i<size;i++)
		{
			if(!isdigit(s[i]))
			{
				cout<<"不合法的标识符："<<s<<endl;
				exit(-1);
			}
		}
		return K_DIGIT;
	}
	else
	{
		for(int i=0;i<size;i++)
		{
			if(!isalnum(s[i]) && s[i]!='_')
			{
                cout<<"不合法的标识符："<<s<<endl;
				exit(-1);
			}
		}
		//数据类型
		if(s=="int" || s=="char")
			return K_TYPE;
		//关键字
		else if(s=="if" || s=="else" || s=="printf" || s=="main")
			return K_KEYWORDS;
		//自定义标识符
		else
			return K_IDENTIFIER;
	}
}

//添加分词结果
void add_keywords(vector<IDwords> &v,int id,string word)
{
	IDwords    temp;
	temp.id = id;
	temp.word = word;
	v.push_back(temp);
}

//词法分析
void lexical_analysis(string source,vector<IDwords> &AnalysisResults)
{
	char       ch;
	ifstream   rfile(source.c_str());
	if(!rfile.is_open())
	{
		cout<<"无法打开源文件"<<endl;
		exit(-1);
	}

	rfile>>noskipws;   //不过滤空格
	while(rfile>>ch)
	{
		int         state=0;        //判断状态
		string      temp("");       //字符串缓存
        char        try_ch;         //探测前面的字符
		
		switch(state)
		{
		case 0:
			if(ch=='/') //可能是注释
			{
				rfile>>try_ch;
				if(try_ch=='/')
				{
					while(rfile>>try_ch)
					{
						if(try_ch=='\n')
							break;   //这是一行注释
					}
					break;
				}
				else if(try_ch=='*')
				{
					while(rfile>>try_ch)
					{
						if(try_ch=='*')
						{
							rfile>>try_ch;
							if(try_ch=='/')
								break; //这是多行注释
						}
					}
					break;
				}
				else
				{
					add_keywords(AnalysisResults,K_OPERATOR,char_to_str(ch));
					ch = try_ch;  //继续状态1
				}
			}
		case 1:
		    if(is_operator(ch)) //判断操作符
			{
				add_keywords(AnalysisResults,K_OPERATOR,char_to_str(ch));
				break;
			}
		case 2:
		    if(is_bracket(ch)) //大括号、小括号
			{
				add_keywords(AnalysisResults,K_BRACKET,char_to_str(ch));
				break;
			}
		case 3:
			if(is_blank(ch)) //空白符
				break;
		case 4:
			if(ch=='#') //跳过预处理
			{
				while(rfile>>ch)
				{
					if(is_blank(ch))
					{
						break;
					}
				}
				break;
			}
		default://判断单词类型
			temp = temp + char_to_str(ch);
			while(rfile>>try_ch)
			{
				if(try_ch == '\"')
				{
					temp = temp + char_to_str(try_ch);
					if(ch == '\"')
					{
						add_keywords(AnalysisResults,word_token(temp),temp);
						break;
					}
					else
					{
						cout<<"不合法的标识符："+temp<<endl;
						exit(-1);
					}
				}
				else if(is_blank(try_ch) )
				{
					if(ch != '\'' && ch != '\"')
					{
						add_keywords(AnalysisResults,word_token(temp),temp);
						break;
					}
					else
						temp = temp + char_to_str(try_ch);
				}
				else if(is_operator(try_ch) )
				{
					if(ch !='\'' && ch != '\"' )
					{
						add_keywords(AnalysisResults,word_token(temp),temp);
					    add_keywords(AnalysisResults,K_OPERATOR,char_to_str(try_ch));
						break;
					}
					else
						temp = temp + char_to_str(try_ch);
				}
				else if(is_bracket(try_ch))
				{
					add_keywords(AnalysisResults,word_token(temp),temp);
					add_keywords(AnalysisResults,K_BRACKET,char_to_str(try_ch));
					break;
				}
				else
					temp = temp + char_to_str(try_ch);
			}
		}
	}
	rfile.close();
}

//输出词法分析结果
void print_lexical(vector<IDwords> &v)
{
	vector<IDwords>::iterator  it;
	for(it = v.begin();it != v.end();it++)
		cout<<it->id<<" "<<it->word<<endl;
}

//获取变量声明
void add_var_table(vector<IDwords>::iterator &it)
{
	while(it->id == K_TYPE)
	{
		it++;
		while(it->word != ";")
		{
	
			if(it->id == K_IDENTIFIER)
			{
				Variable     tmp;
				tmp.var = it->word;
				string   tmp_var = it->word;
				if((it+1)->word=="=")   //判断变量有没有初始化
				{
					it = it+2;
					tmp.value = it->word;
					add_target_code(tmp_var,"=",tmp.value," "," "," ");
				}
				var_table.push_back(tmp);
			}
			it++;
		}
		it++;
	}
}

//表达式分析
void expression(vector<IDwords>::iterator &it)
{
	string dsf,op,dst,dsc;         
	//保存非操作符栈
    stack<string>         word_stack;
    //操作符栈
    stack<string>         oper_stack;
	oper_stack.push("#");
	while(it->word != ";")       //遇到';'一条语句结束
	{
	
		if(it->word == "(")
			oper_stack.push(it->word);
		else if(it->word == ")")
		{

			while(oper_stack.top() != "(")
			{
				op = oper_stack.top();
			
			    oper_stack.pop();
		//	    oper_stack.push(it->word);
			    dsc = word_stack.top();
                word_stack.pop();
			    dst = word_stack.top();
			    word_stack.pop();
			    vab = vab+1;
				if(vab == 91)
					vab = '0';
			    dsf = "tmp" + char_to_str(vab);

				Variable     tmp;
				tmp.var = dsf;
				var_table.push_back(tmp);

			    word_stack.push(dsf);
                add_target_code(dsf,op,dst,dsc," "," ");
			}
			oper_stack.pop();
	
		}
		else if(it->id != K_OPERATOR)
			word_stack.push(it->word);
		else if(oper_stack.top() == "(")
		{
			oper_stack.push(it->word);
		}
		else if(level(it->word) < level(oper_stack.top()))  //优先级低
		{
			op = oper_stack.top();
			oper_stack.pop();
			oper_stack.push(it->word);
			dsc = word_stack.top();
            word_stack.pop();
			dst = word_stack.top();
			word_stack.pop();
			vab = vab+1;
			if(vab == 91)
				vab = '0';
			dsf = "tmp" + char_to_str(vab);

            Variable     tmp;
			tmp.var = dsf;
			var_table.push_back(tmp);

			word_stack.push(dsf);
            add_target_code(dsf,op,dst,dsc," "," ");
		}
		else   //优先级高
			oper_stack.push(it->word);
		it++;
	}
	//弹出剩下的
	while(oper_stack.top() != "#")
	{
		op = oper_stack.top();
        oper_stack.pop();
		dsc = word_stack.top();
        word_stack.pop();
		dst = word_stack.top();
		word_stack.pop();
	
		if(op=="=")//赋值运算
		{
			add_target_code(dst,op,dsc," "," "," ");
		}
		else
		{
            vab = vab+1;
			if(vab == 91)
				vab = '0';
			dsf = "tmp" + char_to_str(vab);

            Variable     tmp;
			tmp.var = dsf;
			var_table.push_back(tmp);

			word_stack.push(dsf);
            add_target_code(dsf,op,dst,dsc," "," ");
		}
	}
}

//分析printf输出
void printf_analysis(vector<IDwords>::iterator &it)
{
	int j,i=1;
	it = it+2;
	string str = it->word; //获取输出内容
	string strvar;         //获取输出变量

	Variable       tmp;
	//分析输出内容及格式
	for(j=1;j<str.size()-1;)
	{
		if(str[j]=='%')
        {
			if(i != j)
			{
				vab = vab + 1;
				if(vab == 91)
					vab = '0';
			    add_target_code("\'"+str.substr(i,j-i)+"$\'","p"," "," ","tmp"+char_to_str(vab)," ");
			    tmp.var = "tmp"+char_to_str(vab);
			    tmp.value = "\'"+str.substr(i,j-i)+"$\'";
			    var_table.push_back(tmp);
            }

			i = j+2;
			it = it+2;  //获取对应变量
			strvar = it->word;
            add_target_code(strvar,"p"," "," ",str.substr(j,2)," ");
			j = i;
			continue;
		}
		j++;
	}
	if(i!=j)
	{
		vab = vab+1;
		if(vab == 91)
			vab = '0';
		add_target_code("\'"+str.substr(i,j-i)+"$\'","p"," "," ","tmp"+char_to_str(vab)," ");
		tmp.var = "tmp"+char_to_str(vab);
		tmp.value = "\'"+str.substr(i,j-i)+"$\'";
		var_table.push_back(tmp);
	}
	it = it+2; //略过“)}”
}

//分析if语句
void if_analysis(vector<IDwords>::iterator &it)
{
	string  op,mark,dst,dsc;
	it++;
	if(it->word != "(")
	{
		cout<<"错误的if语句：缺少'('"<<endl;
		exit(-1);
	}
	it++;
	dst = it->word;
	it++;
	mark = it->word;
	it++;
	dsc = it->word;
	op = "if";

	add_target_code(" ",op,dst,dsc,mark,"step"+char_to_str(lab+1));
	it++;
	if(it->word != ")")
	{
		cout<<"错误的if条件语句：缺少')'"<<endl;
		exit(-1);
	}
	it++; //略过‘{’
	it++;
    
	//分析else
	vector<IDwords>::iterator   it2 = it;
    while(it2->word != "}")
	{
		it2++;
	}
	it2++;
	//判断有没有else
	if(it2->word == "else")
	{
		it2++; //略过‘{’
        while(it2->word != "}")
		{
			expression(it2);
			it2++;
		}
	}//else分析完成
	else
		it2--;
	lab = lab + 2;
    add_target_code(" ","jmp"," "," "," ","step"+char_to_str(lab));

	add_target_code(" ","pstep"," "," "," ","step"+char_to_str(lab-1));
	
	while(it->word != "}")
	{
		expression(it); //表达式分析
		it++;
	}
    add_target_code(" ","jmp"," "," "," ","step"+char_to_str(lab));
    add_target_code(" ","pstep"," "," "," ","step"+char_to_str(lab));

	it = it2;
}

//语法分析
void syntax_analysis(vector<IDwords> &AnalysisResults)
{
	vector<IDwords>::iterator  it=AnalysisResults.begin();
    if(it->word != "main")
	{
		cout<<"缺少main"<<endl;
		exit(-1);
	}
	it = it+3; //跳过“（）”
	if(it->word != "{")
	{
		cout<<"main函数缺少'{'"<<endl;
		exit(-1);
	}
	it++;
	//获取变量声明
    add_var_table(it);
    //获取代码段的操作
	while(it != AnalysisResults.end())
	{
		//遇到printf
		if(it->word == "printf")
		{
			printf_analysis(it);
		}
		// if 语句
		else if(it->word == "if")
		{
			if_analysis(it);
		}
		else if(it->word == "}")
			break;
		//表达式分析
		else
		{
			expression(it); //表达式分析
		}
		it++;
	}
}

//输出语法分析结果
void print_syntax()
{
	vector<Variable>::iterator  it;
	cout<<"变量声明及初始化"<<endl;
	for(it = var_table.begin();it != var_table.end();it++)
	{
		cout<<it->var<<"   "<<it->value<<endl;
	}

	vector<Target>::iterator it2;
	cout<<"中间代码"<<endl;
	for(it2 = target_code.begin();it2 != target_code.end();it2++)
	{
		cout<<it2->dsf<<"  "<<it2->op<<"  "<<it2->dst<<"  "<<it2->dsc<<"  "<<it2->mark<<"  "<<it2->step<<endl;
	}
}

//加减法转换
void addsub_asm(ofstream &out,string dsf,string op,string dst,string dsc)
{
	out<<"    mov BL,"<<dst<<endl;
	if(op == "+")
		out<<"    add BL,"<<dsc<<endl;
	else
		out<<"    sub BL,"<<dsc<<endl;
	out<<"    mov "<<dsf<<",BL"<<endl;
}

//乘法
void mul_asm(ofstream &out,string dsf,string dst,string dsc)
{
	out<<"    mov AL,"<<dst<<endl;
	out<<"    mov BH,"<<dsc<<endl;
	out<<"    mul BH"<<endl;
	out<<"    mov BL,1"<<endl;
	out<<"    div BL"<<endl;
	out<<"    mov "<<dsf<<",AL"<<endl;
}

//除法
void div_asm(ofstream &out,string dsf,string dst,string dsc)
{
	out<<"    mov AL,"<<dst<<endl;
	out<<"    CBW"<<endl;
	out<<"    mov BL,"<<dsc<<endl;
	out<<"    div BL"<<endl;
	out<<"    mov "<<dsf<<",AL"<<endl;
}

//赋值运算
void sign_asm(ofstream &out,string dsf,string dst)
{
	out<<"    mov BL,"<<dst<<endl;
	out<<"    mov "<<dsf<<",BL"<<endl;
}

//输出转换
void print_asm(ofstream &out,string dsf,string mark)
{
	//以字符格式输出
	if(mark=="%c")
	{
		out<<"    mov DL,"<<dsf<<endl;
		out<<"    mov AH,02H"<<endl;
		out<<"    int 21H"<<endl;
	}
	//以整数格式输出
	else if(mark=="%d")
	{
		out<<"    mov AL,"<<dsf<<endl;
		out<<"    CBW"<<endl;
		out<<"    mov BL,10"<<endl;
		out<<"    DIV BL"<<endl;
		out<<"    mov BH,AH"<<endl;
		out<<"    add BH,30H"<<endl;
		out<<"    add AL,30H"<<endl;
		out<<"    CMP AL,48"<<endl;
		//确定十位是否是0
		lab = lab + 2;
		string step2 = "step" + char_to_str(lab);
		out<<"    JE "<<step2<<endl;
        string step1 = "step" + char_to_str(lab-1);
		out<<"  "<<step1<<":"<<endl;
		out<<"    mov DL,AL"<<endl;
		out<<"    mov AH,2"<<endl;
		out<<"    int 21H"<<endl;

		//输出个位
		out<<"  "<<step2<<":"<<endl;
		out<<"    mov DL,BH"<<endl;
		out<<"    mov AH,2"<<endl;
		out<<"    int 21H"<<endl;
	}
	//字符串输出
	else
	{
		out<<"    LEA DX,"<<mark<<endl;
		out<<"    mov AH,09"<<endl;
		out<<"    int 21H"<<endl;
	}
}

//if语句转换
void if_asm(ofstream &out,string dst,string dsc,string mark,string step)
{
	out<<"    mov AL,"<<dst<<endl;
	out<<"    CMP AL,"<<dsc<<endl;
	if(mark == ">")
		out<<"    JG "<<step<<endl;
	else if(mark == "<")
		out<<"    JL "<<step<<endl;
	else
	{
		cout<<"暂不支持其他条件判断"<<endl;
		exit(-1);
	}
}


//生成汇编文件
void create_asm(string file)
{
	//变量声明
	ofstream   wfile(file.c_str());
	if(!wfile.is_open())
		cout<<"无法创建汇编文件"<<endl;

	vector<Variable>::iterator  it_var;
	
	wfile<<"ASSUME CS:codesg,DS:datasg"<<endl;
	//数据段
	wfile<<"datasg segment"<<endl;
	for(it_var=var_table.begin();it_var!=var_table.end();it_var++)
	{
		wfile<<"    "<<it_var->var<<" DB ";
		if(it_var->value != "")
			wfile<<it_var->value<<endl;
		else
			wfile<<"\'?\'"<<endl;
	}
	wfile<<"datasg ends"<<endl;
	//代码段
	wfile<<"codesg segment"<<endl;
	wfile<<"  start:"<<endl;
	wfile<<"    mov AX,datasg"<<endl;
	wfile<<"    mov DS,AX"<<endl;

	vector<Target>::iterator     it;
	Target        tmp;
    for(it = target_code.begin();it != target_code.end();it++)
	{
		//加减法转化
		if(it->op == "+" || it->op=="-")
			addsub_asm(wfile,it->dsf,it->op,it->dst,it->dsc);
		//乘法转换
		else if(it->op == "*")
			mul_asm(wfile,it->dsf,it->dst,it->dsc);
		//除法转换
		else if(it->op == "/")
			div_asm(wfile,it->dsf,it->dst,it->dsc);
		//赋值运算
		else if(it->op == "=")
			sign_asm(wfile,it->dsf,it->dst);
		//输出操作
		else if(it->op == "p")
			print_asm(wfile,it->dsf,it->mark);
		//if语法分析
		else if(it->op == "if")
		{
			if_asm(wfile,it->dst,it->dsc,it->mark,it->step);
		}
		else if(it->op == "else")
		{
			cout<<"else 没有找到匹配的 if"<<endl;
			exit(-1);
		}
		//跳转语句
		else if(it->op == "jmp")
		{
			wfile<<"    JMP "<<it->step<<endl;
		}
		//跳转语句段标识
		else if(it->op == "pstep")
		{
			wfile<<"  "<<it->step<<":"<<endl;
		}
		//其他
		else
		{
			cout<<"编译器暂不支持该语法操作"<<endl;
			exit(-1);
		}
	}

	//代码段结束
	wfile<<"    mov ax,4C00H"<<endl;
	wfile<<"    int 21H"<<endl;
	wfile<<"codesg ends"<<endl;
	wfile<<"  end start"<<endl;

	wfile.close();
}


int main(int argc,char* argv[])
{
	vector<IDwords>  AnalysisResults;

	string source;

	//缺省时给以提示
	if(argc == 1)
	{
		cout<<"*****************************************************"<<endl;
		cout<<"\n在源文件目录下生成 .asm 汇编文件\n"<<endl;
		cout<<"*****************************************************"<<endl;
		cout<<"\n请输入源文件：";
		cin>>source;
        //词法分析
	    lexical_analysis(source,AnalysisResults);
		//语法分析
	    syntax_analysis(AnalysisResults);
		//生成汇编文件
	    create_asm(asmfile(source));
		cout<<"\n使用结束"<<endl;
	}
	else if(argc == 2)
	{
		//默认生成汇编文件：源文件名.asm
        //词法分析
	    lexical_analysis(argv[1],AnalysisResults);
		//语法分析
	    syntax_analysis(AnalysisResults);
		//生成汇编文件
	    create_asm(asmfile(argv[1]));
	}
	else if(argc == 3)
	{
		//词法分析
	    lexical_analysis(argv[1],AnalysisResults);
		//语法分析
	    syntax_analysis(AnalysisResults);
		//生成汇编文件
	    create_asm(asmfile(argv[2]));
	}
	else
	{
		cout<<"正确使用格式：compile.exe [源文件] [汇编文件]"<<endl;
	}

	//输出分析
 //   print_lexical(AnalysisResults);
	//输出语法分析结果
//	print_syntax();
	return 0;
}




