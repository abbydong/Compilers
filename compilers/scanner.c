#include <stdio.h>
#include "keywords.h"
#include <string.h>
#include <math.h>

int main()
{
	char filename[100] = "";
	char filename2[100] = "";
	char checktoken[10] = "";
	FILE * fp;
	FILE * fp2;

	int i = 0 ;
	
//	printf("please enter the file name\n");

//	gets(filename);

	if( (fp = fopen( "test.txt" , "r" )) == NULL)
	{
		printf("file name is error!\n");
		return 0;
	}
	
	if( (fp2 = fopen("b.txt" , "w+" )) == NULL)
	{
		printf("file name is error!\n");
		return 0;
	}

	int num;
	while( !feof(fp) )
	{
		fgets(filename , 100 , fp);
		i = 0;
		while(filename[i+1] != '\0')
		{
		//	printf("i=%d,filename[%d]=%c\n",i,i,filename[i]);
			if( ((filename[i] <= 'Z') && (filename[i] >= 'A')) ||((filename[i] <= 'z') && (filename[i] >= 'a')) )			//第一个字符是字母的情况
			{
				int j = 0;
//				printf("aa\n");	
				while( ((filename[i+j] <= 'z') && (filename[i+j] >= 'a')) || ((filename[i+j] <= 'Z') && (filename[i+j] >= 'A')) )			//扫描直到字符不是字母为止。
				{
					checktoken[j] = filename[i+j];			//将字符复制到checktoken里面
					j++;
				}
					
				if( strcmp(checktoken , "call") == 0)		//判断是否是关键字call
				{
					num = fprintf(fp2 , "关键字：%s\t%d\n", checktoken , CALL);	
//					printf("%d\n" , num);
				}	
				else if(strcmp(checktoken , "while") == 0)	//判断是否是关键字while
				{
					fprintf(fp2 , "关键字：%s\t%d\n", checktoken , WHILE);	
				}
				else if(strcmp(checktoken , "if") == 0)		//判断是否是关键字if
				{
					fprintf(fp2 , "关键字：%s\t%d\n" , checktoken , IF);
				}
				else if(strcmp(checktoken , "else") == 0)	//判断是否是关键字else
				{
					fprintf(fp2 ,"关键字：%s\t%d\n" , checktoken , ELSE);
				}
				else if(strcmp(checktoken , "num") == 0)	//判断是否是关键字num
				{
					fprintf(fp2 , "关键字：%s\t%d\n" , checktoken ,NUM);
				}
				else if(strcmp(checktoken , "string") == 0)	//判断是否是关键字string
				{
					fprintf(fp2 , "关键字：%s\t%d\n" , checktoken , STRING);
				}
				else if(strcmp(checktoken , "void") == 0)	//判断是否是关键字void
				{
					fprintf(fp2 , "关键字：%s\t%d\n" , checktoken , VOID);
				}
				else if(strcmp(checktoken , "return") == 0)	//判断是否是关键字return
				{
					fprintf(fp2 , "关键字：%s\t%d\n" , checktoken , RETURN);
				}
				else
				{
					fprintf(fp2 , "标识符：%s\t%d\n" , checktoken , IDEN);
				}
				int k = 0;
				while(k<10)
				{
					checktoken[k] = ' ';
					k++;
				}
				
				i = i + j;
			}
			else if( (filename[i] <= '9') && (filename[i] >= '0'))			//第一个字符是数字的情况
			{
				int j = 0;
				int j2= 0;
				int k = 0;
				int k2 = 0;
				int m = -1;
				float number = 0;
				float numl=0 , numr = 0;
				while(( (filename[i+j] <= '9') && (filename[i+j] >= '0') ) || (filename[i+j] == '.' ))			//扫描直到字符不是数字为止。
				{
					checktoken[j] = filename[i+j];			//将字符复制到checktoken里面
					j++;
					j2++;
					if(filename[i+j] == '.')
					{
						k++;
						if(k > 1)							//只有一个小数点
							break;
						m = i+j;							//记住小数点的位置
					}
				}
				printf("%s\n",checktoken);
				if( m == -1)								//没有小数点
				{
					while(j!=0)
					{
						j--;
						number = number + (checktoken[k2]-48)*pow(10,j);
						k2++;
					}
				printf("%f\n",number);
				}
				else
				{
					k2 = 0;
					while(i+k2 != m)
					{
						numl = numl + (checktoken[k2]-48)*pow(10,m-i-k2-1);
						k2++;
					}
					int k3;
					k3 = k2;
					while(j+i-m != 0)
					{
						j--;
						numr = numr + (checktoken[k2]-48)*pow(10,-(k2-k3));
						k2++;
					}
					number = numl + numr;
					printf("%f\t%f\n",numl,numr);
					printf("%f\n",number);
				}
				fprintf(fp2 , "数字：%f\t%d\n" , number , NUMBER);
				i = i + j2;				
			}
			else if((filename[i] == 32)||(filename[i] == '\0') || (filename[i] == 13) || (filename[i] == 9))
			{
				i++;
			}
			else if(filename[i] == '+')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , PLUS);
				i++;
			}
			else if(filename[i] == '-')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , MINUS);
				i++;
			}
			else if(filename[i] == '*' )
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , MULTI);
				i++;
			}
			else if(filename[i] == '/' )
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , DIV);
				i++;
			}
			else if(filename[i] == '&')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , AND);
				i++;
			}
			else if(filename[i] == '|')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , OR);
				i++;
			}
			else if(filename[i] == '%')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , MOD);
				i++;
			}
			else if(filename[i] == '(')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] ,SLP);
				i++;
			}
			else if(filename[i] == ')')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , SRP);
				i++;
			}
			else if(filename[i] == '[')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , MLP);
				i++;
			}
			else if(filename[i] == ']')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , MRP);
				i++;
			}
			else if(filename[i] == '{')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , BLP);
				i++;
			}
			else if(filename[i] == '}')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , BRP);
				i++;
			}
			else if(filename[i] == ',')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] ,COMMA);
				i++;
			}
			else if(filename[i] == '#')
			{
				fprintf(fp2 , "注释符：%c\t%d\n" , filename[i] , SHAP);
				i++;
				break;
			}
			else if(filename[i] == '<')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , LESS);
				i++;
			}
			else if(filename[i] == '>')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] ,MORE);
				i++;
			}
			else if(filename[i] == '=')
			{
				fprintf(fp2 , "操作符：%c\t%d\n" , filename[i] , EQUAL);
				i++;
			}
			else 
			{
				fprintf(fp2 , "非法字符：%c\n" , filename[i] );
				i++;
			}

		}
	}
	fclose(fp);
	fclose(fp2);
	return 0;
}
