#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static const char TMPFILE[]="tmpfile";

void convertToZip()
{
	FILE* outfile;
    char ch, c;
    int count=1;

    outfile=fopen(TMPFILE,"r");
	if(outfile==NULL)
	{
		printf("Unable to open the tmpfile");
		exit(1);
	}
    ch=fgetc(outfile);
    while((c = fgetc(outfile)) != EOF)	//loop that keeps a running count of characters in file
    {
        if(ch == c)
            count++;
        else
        {
            fwrite(&count,4,1,stdout);
            fwrite(&ch,1,1,stdout);
            ch = c;
            count = 1;
        }
    }
    fwrite(&count,4,1,stdout);
    fwrite(&ch,1,1,stdout);
    fclose(outfile);	
}

int main(int argc,char* argv[])
{
	char* filename=argv[0]+2;
	int i;
	FILE* fp, *outfile;

	if(argc==1)
	{
		printf("%s: file1 [file2 ...]\n",filename);
		exit(1);
	}

	outfile=fopen(TMPFILE,"w");		//create a file that clubs all the content of all the input files
	if(outfile==NULL)
	{
		printf("%s: Could not open file for writing",filename);
		exit(1);
	}
	
	for(i=1;i<argc;i++)
	{
		char c;
		fp=fopen(argv[i],"r");
		if(fp==NULL)
		{
			printf("%s: could not open the file",filename);
			exit(1);
		}

		while((c = fgetc(fp)) != EOF)
		{
			fputc(c,outfile); //read file character by character and store it in tmpfile
		}
		fclose(fp);
	}

	fclose(outfile);
	convertToZip();	//function that reads from tmpfile and compresses file contents
	return 0;
}
