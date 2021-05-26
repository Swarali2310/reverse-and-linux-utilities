#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void readFileAndGrep(FILE* fp,const char* pattern)
{
	char* buffer;
    size_t bufsize=0;
    size_t characters;

	if(fp==NULL)
		fp=stdin;

	while((characters=getline(&buffer,&bufsize,fp)) != -1)
	{
		if(fp==stdin && feof(stdin))
			break;

		if(strstr(buffer,pattern))	//check if the string has the pattern, if yes, print the line; else move onto the next line
			printf("%s",buffer);		
	}
}

int main(int argc,char* argv[])
{
    char* filename=argv[0]+2;	//remove the first 2 chars "./" from the executable
	if(argc==1)
	{
		printf("%s: searchterm [file ...]\n",filename);
		exit(1);
	}

	const char* grep_string=argv[1];	
    FILE* ipfile=NULL;
	int i;
    for(i=2;i<argc;i++)
    {
		ipfile=fopen(argv[i],"r");	
        if(ipfile==NULL)
        {
            printf("%s: cannot open file\n",filename);
            exit(1);
        }
		else
		{
			readFileAndGrep(ipfile,grep_string);
			fclose(ipfile);	
		}
	}
	if(argc==2)	//when only search pattern is specified without filename
		readFileAndGrep(ipfile,grep_string);
	return 0;
}
