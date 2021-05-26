#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
	int i;
	char* filename = argv[0] + 2;
	FILE *fp;
	int count;
	char buffer;

	if(argc==1)
	{
		printf("%s: file1 [file2 ...]\n",filename);
		exit(1);
	}

	for(i=1;i<argc;i++)
	{
		fp=fopen(argv[i],"r");

		fseek(fp, 0L, SEEK_END);	//go to the end of the file
		long int res = ftell(fp);	//count the bytes present in the file
		fseek(fp, 0, SEEK_SET); 	//reset the file pointer at the beginning of the file again
		int iterations = res / 5;	//count how many chunks are to be read

		int idx;
		for(idx=0;idx<iterations;idx++)
		{
			fread(&count,4,1,fp);	//iterate over each chunk and get the count and character
			fread(&buffer,1,1,fp);

			int j;
			for(j=0;j<count;j++)	
				printf("%c",buffer);	//print the character obtained "count" number of times
		}
	}
	return 0;
}
