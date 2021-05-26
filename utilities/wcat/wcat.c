#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
	if(argc==1)	//when no parameters specified, return normally
		return 0;

	int i;
	char* filename=argv[0]+2;
	FILE* ipfile=NULL;
	for(i=1;i<argc;i++)
	{
		char str[500];
		ipfile=fopen(argv[i],"r");
		if(ipfile==NULL)
		{
			printf("%s: cannot open file\n",filename);
			exit(1);
		}
		while(fgets(str,sizeof str,ipfile))	//read the contents of the file into the buffer, and print out the buffer
		{
			printf("%s",str);
		}
		fclose(ipfile);
	}	
	return 0;
}
