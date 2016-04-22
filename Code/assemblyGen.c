/*
* @Author:    Pratyush Kar (2013A7PS029P),
*             Ayush Kataria (2013A7PS028P)
* @Email:     f2013029@pilani.bits-pilani.ac.in,
*             f2013028@pilani.bits-pilani.ac.in
* @Gp Number: 52
* @File Name: typeChecker.h
* @Date:      2016-03-29 10:44:42
*/

#include "assemblyGen.h"

int temp_index=0;
node* dup_list=NULL;

int searchEntry(char* temp)
{
	node* new_node = dup_list;
	while(new_node!=NULL)
	{
		if( strcmp(new_node->str,temp)==0 )
			return 0;
		new_node = new_node->next;
		//printf("//////%s\n",new_node->str);
	}
	//printf("okay\n");
	return 1;
}
void insert(char* temp)
{
	node* new_node =(node*) malloc(sizeof(node));
	strcpy(new_node->str,temp);
	new_node->next = NULL;
	if(dup_list==NULL)
		dup_list=new_node;
	else
	{
		node* temp2;
		temp2 = dup_list->next;
		dup_list->next = new_node;
		new_node->next = temp2;
	}
}

void readDirective(int option, triple t,FILE* fp)
{
	fprintf(fp, ";read begin\n");
	fprintf(fp, "push rbp\n");
	if(option==0)
		fprintf(fp, "mov rsi,%s\n",t.op);	
	else
		fprintf(fp, "mov rsi,%d\n",t.val1);
	fprintf(fp, "mov rdi,format_inp\n");
	fprintf(fp, "mov rax,0\n");
	fprintf(fp, "call scanf\n");
	fprintf(fp, "pop rbp\n");
	fprintf(fp,";read over\n\n");

}
void writeDirective(int option, triple t,FILE* fp)
{
	fprintf(fp,";write begin\n");
	fprintf(fp, "push rbp\n");
	if(option==0)
		fprintf(fp, "mov rsi,[%s]\n",t.op);	
	else
		fprintf(fp, "mov rsi,%d\n",t.val1);
	fprintf(fp, "mov rdi,format\n");
	fprintf(fp, "mov rax,0\n");
	fprintf(fp, "call printf\n");
	fprintf(fp, "pop rbp\n");
	fprintf(fp,";write ends\n\n");
}

void assignDirectiveZero(char* a,char* b ,FILE* fp)
{
	fprintf(fp,"; assign op\n");
	fprintf(fp,"MOV rax,[%s]\n",b);
	fprintf(fp,"MOV [%s],rax\n",a);
	fprintf(fp,"; assign op ends\n");
}	
void assignDirectiveOne(char* a,int b ,FILE* fp)
{
	fprintf(fp,"; assign op\n");
	fprintf(fp,"MOV rax,%d\n",b);
	fprintf(fp,"MOV [%s],rax\n",a);
	fprintf(fp,"; assign op ends\n");
}
void arithDirective(char* op , int option , char* ans , char* val1,char* val2 , FILE* fp)
{
	fprintf(fp,";case %d\n",option);
	switch(option)
	{
		case 0:
			fprintf(fp,"MOV rax,[%s]\n",val1);
			fprintf(fp,"MOV rbx,[%s]\n",val2);
			fprintf(fp,"MOV [%s],rax\n",ans);
			fprintf(fp,"%s [%s],rbx\n",op,ans);
			fprintf(fp,";end of operation\n\n");
			break;		
		case 1:
			fprintf(fp,"MOV rax,[%s]\n",val1);
			fprintf(fp,"MOV rbx,%s\n",val2);
			fprintf(fp,"MOV [%s],rax\n",ans);
			fprintf(fp,"%s [%s],rbx\n",op,ans);
			fprintf(fp,";end of operation\n\n");
			break;
		case 2:
			fprintf(fp,"MOV rax,%s\n",val1);
			fprintf(fp,"MOV rbx,[%s]\n",val2);
			fprintf(fp,"MOV [%s],rax\n",ans);
			fprintf(fp,"%s [%s],rbx\n",op,ans);
			fprintf(fp,";end of operation\n\n");
			break;
		case 3:
			fprintf(fp,"MOV rax,%s\n",val1);
			fprintf(fp,"MOV rbx,%s\n",val2);
			fprintf(fp,"MOV [%s],rax\n",ans);
			fprintf(fp,"%s [%s],rbx\n",op,ans);
			fprintf(fp,";end of operation\n\n");
			break;
		
	} 
}

void compareDirective(int option,char* op,int jump_label,char* val1,char* val2,FILE* fp)
{
	switch(option)
	{
		case 0:
			fprintf(fp,"mov rax,%s\n",val1);
			fprintf(fp,"mov rbx,%s\n",val2);
			fprintf(fp,"cmp rax,rbx\n");
			break;
		case 1:
			fprintf(fp,"mov rax,%s\n",val1);
			fprintf(fp,"mov rbx,[%s]\n",val2);
			fprintf(fp,"cmp rax,rbx\n");
			break;
		case 2:
			fprintf(fp,"mov rax,[%s]\n",val1);
			fprintf(fp,"mov rbx,%s\n",val2);
			fprintf(fp,"cmp rax,rbx\n");
			break;
		case 3:
			fprintf(fp,"mov rax,[%s]\n",val1);
			fprintf(fp,"mov rbx,[%s]\n",val2);
			fprintf(fp,"cmp rax,rbx\n");
			break;
	}

	
	fprintf(fp,"%s label%d\n",op,jump_label);

}

void labelDirective(int label_index,FILE* fp)
{
	fprintf(fp,"label%d:\n",label_index);
}

void jumpDirective(int label_index,FILE* fp)
{
	fprintf(fp,"JMP label%d\n",label_index);	
}

void combineCode(const char* asmFile)
{
	FILE *temp = fopen("dataseg.txt","r");
	FILE *temp2 = fopen("codeseg.txt","r");
	FILE *finalcode = fopen(asmFile,"w+");

	fprintf(finalcode, "extern printf,exit,scanf\n");
	fprintf(finalcode,"section .data\n");
	fprintf(finalcode,"\tformat_inp db %c%cd%c, 0\n",'"','%','"');
	fprintf(finalcode,"\tformat db %c%cd%c, 10, 0\n",'"','%','"');
	char ch;
	while( (ch=fgetc(temp))!=EOF)
	{
		fputc(ch, finalcode);
		if(ch=='\n')
			fputc('\t', finalcode);
	}
	fprintf(finalcode,"section .text\n");
	fprintf(finalcode,"\tglobal main\n");
	fprintf(finalcode,"\tmain:\n");	
	while( (ch=fgetc(temp2))!=EOF)
	{
		fputc(ch, finalcode);
		if(ch=='\n')
			fputc('\t', finalcode);
	}	
	fprintf(finalcode,"call exit\n");
	fclose(temp);
	fclose(temp2);
	fclose(finalcode);
}




void generateAssemblyCode(triple* currTriple,int len,const char* asmFile)
{
	FILE *codeseg = fopen("codeseg.txt","w");
	FILE *dataseg = fopen("dataseg.txt","w");
	int temp_arr[len];
	char temp_arr2[len][100];
	memset(temp_arr,0, sizeof(temp_arr));
	memset(temp_arr2,'\0', sizeof(temp_arr2));
	int i;
	for(i=0;i<len;i++)
	{
		//printf("!!!!!!!!!!!!!!!!! %d\n",i);
		if(strcmp(currTriple[i].op,"read") == 0) 
		{
			int a = currTriple[i].val1;
			//printf("Read %d\n",i);
			if(strcmp( currTriple[a].op,"NUM")==0 )
				readDirective(1,currTriple[a], codeseg);
			else
				readDirective(0,currTriple[a], codeseg);
		}
		else if(strcmp(currTriple[i].op,"write")==0) 
		{
			int a = currTriple[i].val1;
			//printf("Write %d\n",i);
			if(strcmp( currTriple[a].op,"NUM")==0 )
				writeDirective(1,currTriple[a],codeseg);
			else
				writeDirective(0,currTriple[a], codeseg);
		}
		else if(strcmp(currTriple[i].op,"=")==0)
		{
			//int a = currTriple[i].val1;
			int b = currTriple[i].val2;
			int a = currTriple[i].val1;
			//printf("%d %d\n",b,temp_arr[b]);
			if(strcmp(currTriple[b].op,"NUM") ==0)
				assignDirectiveOne(currTriple[a].op,currTriple[b].val1,codeseg);
			else if(temp_arr[b]==1)
				assignDirectiveZero(currTriple[a].op , temp_arr2[b],codeseg);
			else
				assignDirectiveZero(currTriple[a].op , currTriple[b].op,codeseg);
		}
		else if(strcmp(currTriple[i].op,"+")==0 || strcmp(currTriple[i].op,"-")==0 ||
			strcmp(currTriple[i].op,"*")==0  || strcmp(currTriple[i].op,"/")==0   )
		{
			char new_op[100];
			if(strcmp(currTriple[i].op,"+")==0 )
				strcpy(new_op,"ADD");
			else if(strcmp(currTriple[i].op,"-")==0 )
				strcpy(new_op,"SUB");
			else if(strcmp(currTriple[i].op,"*")==0 )
				strcpy(new_op,"MUL");
			else if(strcmp(currTriple[i].op,"/")==0 )
				strcpy(new_op,"DIV");
			
			temp_arr[i]=1;
			strcpy(temp_arr2[i],"temp");
			char temp[100];
			//itoa(temp_index,temp,10);
			sprintf(temp,"%d",temp_index); 
			strcat(temp_arr2[i],temp);
			temp_index++;
			fprintf(dataseg,"%s dq 0\n",temp_arr2[i]);

			int a =currTriple[i].val1;
			int b=currTriple[i].val2;

			
			if(temp_arr[a]==1 && temp_arr[b]==1)
				arithDirective(new_op , 0,temp_arr2[i] , temp_arr2[a] , temp_arr2[b] , codeseg);
			
			else if(temp_arr[a]==0 && temp_arr[b]==1 && strcmp(currTriple[a].op,"NUM")!=0  )
				arithDirective( new_op ,0,temp_arr2[i] , currTriple[a].op , temp_arr2[b] , codeseg);
			
			else if(temp_arr[a]==0 && temp_arr[b]==1 && strcmp(currTriple[a].op,"NUM")==0  )
			{
				char temp2[100];
				//itoa(currTriple[a].val1,temp2,10);
				sprintf(temp2,"%d",currTriple[a].val1); 
				arithDirective(new_op ,2,temp_arr2[i] , temp2 , temp_arr2[b] , codeseg);
			}
			else if(temp_arr[a]==1 && temp_arr[b]==0  && strcmp(currTriple[b].op,"NUM")!=0  )
			{
				arithDirective(new_op , 0,temp_arr2[i] , temp_arr2[a] , currTriple[b].op , codeseg);
			}
			else if(temp_arr[a]==1 && temp_arr[b]==0  && strcmp(currTriple[b].op,"NUM")==0  )
			{
				char temp2[100];
				//itoa(currTriple[b].val1,temp2,10);
				sprintf(temp2,"%d",currTriple[b].val1);
				arithDirective(new_op ,1,temp_arr2[i] , temp_arr2[a] , temp2 , codeseg);
			}
			else if(temp_arr[a]==0 && strcmp(currTriple[a].op , "NUM")==0)
			{
				if(temp_arr[b]==0 && strcmp(currTriple[b].op,"NUM")==0)
				{
					char temp2[100];
					char temp3[100];
					//itoa(currTriple[a].val1,temp2,10);
					//itoa(currTriple[b].val1,temp3,10);
					sprintf(temp2,"%d",currTriple[a].val1);
					sprintf(temp3,"%d",currTriple[b].val1);

					arithDirective(new_op ,3,temp_arr2[i] , temp2 , temp3 , codeseg);
				}
				else
				{
					char temp2[100];
					//char temp3[100];
					//itoa(currTriple[a].val1,temp2,10);
					sprintf(temp2,"%d",currTriple[a].val1);

					//itoa(currTriple[b].val1,temp3,10);
					arithDirective(new_op ,2,temp_arr2[i] , temp2 , currTriple[b].op , codeseg);

				}
			}
			else if(temp_arr[a]==0 && strcmp(currTriple[a].op ,"NUM" )!=0)
			{
				if(temp_arr[b]==0 && strcmp(currTriple[b].op,"NUM")==0)
				{
					char temp2[100];
					//char temp3[100];
					//itoa(currTriple[b].val1,temp2,10);
					sprintf(temp2,"%d",currTriple[b].val1);
					//itoa(currTriple[b].val1,temp3,10);
					arithDirective(new_op ,1,temp_arr2[i] , currTriple[a].op ,temp2 , codeseg);		
				}
				else
				{
					arithDirective(new_op ,0,temp_arr2[i] , currTriple[a].op , currTriple[b].op , codeseg);

					
				}

			}


		}

		else if(strcmp(currTriple[i].op,"Label")==0)
		{
			labelDirective(currTriple[i].mylabel,codeseg);	
			//printf("..............%d\n",i);
		}
		else if(strcmp(currTriple[i].op,"Jump")==0)
		{
			jumpDirective(currTriple[i].jumplabel,codeseg);
		}
		else if(strcmp(currTriple[i].op,"<=")==0 ||
				strcmp(currTriple[i].op,"<")==0  ||
				strcmp(currTriple[i].op,">=")==0 ||
				strcmp(currTriple[i].op,">")==0  ||
				strcmp(currTriple[i].op,"!=")==0 ||
				strcmp(currTriple[i].op,"==")==0 
				)
		{
			char op[100];
			if( strcmp(currTriple[i].op , "<=")==0)
			{
				strcpy(op,"JLE");
			}
			else if(strcmp(currTriple[i].op ,"<" )==0)
			{
				strcpy(op,"JL");
			}
			else if( strcmp(currTriple[i].op , "==")==0)
			{
				strcpy(op,"JZ");
			}
			else if(strcmp(currTriple[i].op ,"!=" )==0)
			{
				strcpy(op,"JNZ");
			}
			else if( strcmp(currTriple[i].op , ">")==0)
			{
				strcpy(op,"JG");
			}
			else if(strcmp(currTriple[i].op ,">=" )==0)
			{
				strcpy(op,"JGE");
			}
		
		
			int a,b;
			a = currTriple[i].val1;
			b = currTriple[i].val2;
			int jump_label = currTriple[i].jumplabel;

			if( strcmp(currTriple[a].op,"NUM")==0)
			{
				if( strcmp(currTriple[b].op,"NUM")==0)
				{
					char temp[100];
					char temp1[100];
					sprintf(temp,"%d",currTriple[a].val1);
					sprintf(temp1,"%d",currTriple[b].val1);
					compareDirective(0,op,jump_label,temp,temp1,codeseg);
				}
				else
				{
						char temp[100];
					//char temp1[100];
					sprintf(temp,"%d",currTriple[a].val1);
					//sprintf(temp1,"%d",currTriple[b].val1);
					compareDirective(1,op,jump_label,temp,currTriple[b].op,codeseg);	

				}
			}
			else
			{
				if( strcmp(currTriple[b].op,"NUM")==0)
				{
			
					//char temp[100];
					char temp1[100];
						//sprintf(temp,"%d",currTriple[a].val1);
					sprintf(temp1,"%d",currTriple[b].val1);
					compareDirective(2,op,jump_label,currTriple[a].op,temp1,codeseg);	
				}
				else
				{
					//char temp[100];
					//char temp1[100];
					//sprintf(temp,"%d",currTriple[a].val1);
					//sprintf(temp1,"%d",currTriple[b].val1);
					compareDirective(3,op,jump_label,currTriple[a].op,currTriple[b].op,codeseg);
				}

			}

		}
		else if( currTriple[i].val1 == INF &&
					currTriple[i].val2 ==INF &&  
					currTriple[i].mylabel==0 &&
					currTriple[i].jumplabel==0)
		{
			//remove duplicates
			if(searchEntry(currTriple[i].op))
			{
				fprintf(dataseg,"%s dq 0\n",currTriple[i].op);
				insert(currTriple[i].op);
			}
				//fprintf(dataseg,"%s dq 0\n",currTriple[i].op);
				

		}
	}

	
	fclose(codeseg);
	fclose(dataseg);

	/*FILE *temp = fopen("dataseg.txt","r");
	char ch;
	while((ch=fgetc(temp))!=EOF)
			printf("%c",ch);
	fclose(temp);*/ 
	combineCode(asmFile);
	//fclose(finalcode);
}
