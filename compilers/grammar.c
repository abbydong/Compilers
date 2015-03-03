#include <stdio.h>
#include <string.h>
#include "symbol.h"

int FOLLOW[60][10];
int FIRST[60][10];
int TABLE[20][32];

#include "buildtable.h"

void build_first()
{

	FILE * fp1 ;				//读入文件 的描述符 
	FILE * fp2 ;				//写入文件 的描述符
	
	char readline[100] = "";
	char r1[10] , r2[10] , r3[10];
//	char FIRST[60][10] ;
	//char check[10] = "";
	//char check2[10] = "";

	for(int i = 0 ; i < 60 ; i++)
	{
		for(int j = 0; j < 10 ; j ++ )
		{
			FIRST[i][j] = -1;
		}
	}
	if( (fp1 = fopen("grammar.txt" , "r+")) == NULL)
	{
		printf("file name is error!\n");
	}
	while( !feof(fp1) )
	{
		fgets(readline , 100 , fp1);
		int i = 0;
		int k1 , k11;
		int k3 ;
		int k2 ;
		//printf("readline:%s\n" , readline);
		while(readline[i+1] != '\0')
		{
				int j = 0 ;
				char check[10] = "";
				char check2[10] = "";
				while(readline[i+j] != 32)						//读入每行第一个字符串
				{
					check[j] = readline[i+j];
					j++;
				}				
				//printf("c1:%s" , check);
				i = i + j + 1;

				while(readline[i] != 32)						//跳过第二个字符串->
				{
					i++;
				}
				i = i + 1;
				j = 0;
				k1 = 0;
				//printf("c2:%s\n" , check);

				while( k1 < 40)											//对比第一个字符串在non_terminal中的位置
				{
					if(strcmp(check , non_terminal[k1]) == 0)
						break;
					else if(strcmp(check , terminal[k1]) == 0)				//对比第一个字符串在terminal中的位置。+20
					{
						k1 = k1 + 20;
						break;
					}
					else
						k1++;

				}
				
				//printf("c:%s\n",check);
				while((readline[i+j] != 32)	&& (readline[i+j] != 10 ))					//将第三个字符串读入
				{
					//printf("a1\n");	
					check2[j] = readline[i+j];		
						j++;
				}
				i = i + j;
				j = 0;
				 k3 = 0 , k11 = 0 , k2 = 0;
				//printf("check2%s," , check2);
			
				while( k3 < 40)											//对比第三个字符串在non_terminal和terminal中的位置。如果是terminal则+20.
				{
					if(strcmp(check2 , non_terminal[k3]) == 0)
					{
					//	printf("UN:%s , %s , %d \n" , check2 , non_terminal[k3] , k3);
						break;
					}
					else if(strcmp(check2 , terminal[k3]) == 0)
					{
					//	k2 = k3 + 20;
						k3 = k3 + 20;
					//	printf("TE:%s , %s , %d \n" , check2 , terminal[k3-20] ,k3-20);
						break;
					}
					else	
					k3++;
					//printf("ELS:%s , %s , %d \n" , check2 , terminal[k3] , k3);
				}
				while(j < 10 )
				{
					if((FIRST[k1][j] == k2) || (FIRST[k1][j] == k3))
					{
						break;
					}
					else if(FIRST[k1][j] == -1)
					{
						//if(k2 != 0)
						//	FIRST[k1][j] = k2;									//无论是终结符还是非终结符都填入FIRST集
						//else
							FIRST[k1][j] = k3;
						break;
					}
					else
						j++;
				}
			break;
		}
	
	}
	
	
	int i, j = 0 , k0 = 0 , k1 = 0 , k2 = 0;																	
/*	for(i = 0 ; i < 19 ; i++)
	{
		while(FIRST[i][j] != -1)
		{
			if(FIRST[i][j] >= 20)				//判断是否为非终结符
			{
				while(FIRST[FIRST[i][j]-20][k0] != -1)
				{
					if(FIRST[FIRST[i][j]-20][k0] == FIRST[i][k1])
					{
						k0++;
						k1 = 0;
					}
					else
					{
						if(FIRST[i][k1] == -1)
						{
							FIRST[i][k1] = FIRST[FIRST[i][j]-20][k0];
							k0++;
						}
						k1++;
					}
				}
			}
			j++;
		}
	}
*/
	FIRST[0][0] = 21 ;
	FIRST[0][1] = 22 ;
	FIRST[1][0] = 24 ;
	FIRST[1][2] = 25 ;
	FIRST[3][0] = 26 ;
	FIRST[3][2] = 27 ; 
	FIRST[3][3] = 28 ;
	FIRST[2][0] = 21 ;
	FIRST[2][1] = 22 ;
	FIRST[9][1] = 20 ;
	FIRST[13][0] = 21;
	FIRST[13][1] = 22;
	FIRST[15][0] = 47;
	FIRST[15][1] = 48;
	FIRST[15][2] = 49;
	FIRST[17][1] = -1;
	FIRST[17][2] = -1;

	for(i = 0 ; i < 52 ; i++)														//打印FIRST集
	{
		if(i < 20)
			printf("%d\t%s:\t" ,i , non_terminal[i]);
		else
			printf("%d\t%s:\t" , i , terminal[i-20]);
		for(j = 0 ; j < 10 ; j++ )
		{
			if(FIRST[i][j] != -1)
			{
				if(FIRST[i][j]<20)
					printf("%d %s\t",FIRST[i][j], non_terminal[FIRST[i][j]]);
				else
					printf("%d %s\t" , FIRST[i][j] , terminal[FIRST[i][j]-20]);
			}
		}
		printf("\n");
	}
	fclose(fp1);
}

void build_follow()
{
	//int FOLLOW[60][10];
	
	int i , j , k;

	for(i = 0 ; i < 60 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			FOLLOW[i][j] = -1;
		}
		FOLLOW[i][0] = 55;									//栈底符号
	}

	for(i = 0 ; i < 4 ; i++)
		FOLLOW[i][1] = 23;									// )

	for(i = 6 ; i < 9 ; i++)
		FOLLOW[i][1] = 23;
	
	FOLLOW[7][2] = 31;
	FOLLOW[8][2] = 31;

	FOLLOW[7][3] = 30;
	FOLLOW[8][3] = 30;

	FOLLOW[10][1] = 38;
	FOLLOW[12][1] = 38;
	FOLLOW[13][1] = 23;



}

void Use_Predicting_Analysis_Table()
{
	int i = 0, j = 0 ;
	
	for(i = 0 ; i < 20 ; i++)
	{
		for(j = 0 ; j < 32 ; j++)
		{
			TABLE[i][j] = -1;
		}
	}


		
}
int main()
{
	build_first();
	build_follow();
	Use_Predicting_Analysis_Table();
	return 0;
}
