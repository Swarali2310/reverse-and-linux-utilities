#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct Node
{
	char* data;
	struct Node* next;
};

struct Node* insertAtHead(struct Node* head, char* val, ssize_t len)
{
	struct Node* node=(struct Node*)malloc(sizeof(struct Node));
	if(node==NULL)
	{
		fprintf(stderr,"malloc failed");
		exit(1);
	}
    node->data=(char*)malloc(sizeof(char)*len);
	if(node->data==NULL)
	{
		fprintf(stderr,"malloc failed");
        exit(1);
	}
	strcpy(node->data,val);
	node->next=head;
	head=node;
	return node;
}

void printList(struct Node* head,FILE* out)
{
	struct Node* node = head;
	if(out==NULL)
		out=stdout;
	while(node)
	{
		fprintf(out,"%s",node->data);
		node=node->next;
	}
	if(out)
		fclose(out);
}

struct Node* readFileintoList(FILE* fp,struct Node* head)
{
    char* line=NULL;
    size_t len=0;
    ssize_t read;

	if(fp==NULL)
		fp=stdin;

    while((read = getline(&line,&len,fp)) != -1)	//read from the input file line by line till end and insert each new line at the head of the list
	{
		if(fp==stdin && feof(stdin))			//when no input file is specified, read till EOF is encountered
			return head;
		head = insertAtHead(head,line,read);	// read gives the characters read in a line, pass on that to the list so that it knows how much data to expect 
	}
	if(fp!=stdin)
		fclose(fp);
	return head;
}

void verifySameFiles(char* file1, char* file2, char* filename)
{
	int infile=open(file1,O_RDONLY);
	int outfile=open(file2,O_WRONLY|O_CREAT,0644);
	if(infile < 0)
	{
		fprintf(stderr,"%s: cannot open file '%s'\n",filename,file1);
		exit(1);
	}
	if(outfile < 0)
	{
		fprintf(stderr,"%s: cannot open file '%s'\n",filename,file2);
		exit(1);
	}
	struct stat ip_file_stat, op_file_stat;
	int ip_ret=fstat(infile,&ip_file_stat);
	int op_ret=fstat(outfile,&op_file_stat);
	if(ip_ret < 0 || op_ret < 0)
	{
		fprintf(stderr,"%s: Cannot get stat for the files",filename);
		exit(1);
	}
	if(ip_file_stat.st_ino == op_file_stat.st_ino)
	{
		fprintf(stderr,"%s: input and output file must differ\n",filename);
		exit(1);
	}
	close(infile);
	close(outfile);
}

int main(int argc, char *argv[])
{
	struct Node* head=NULL;
	FILE *infile=NULL,*outfile=NULL;
	char* filename=argv[0]+2;
	if(argc > 3)
	{
		fprintf(stderr,"usage: %s <input> <output>\n",filename);
		exit(1);
	}

	if(argc >= 2)	//condition of having input OR input+output files
	{
		if(argc==3)
		{
			verifySameFiles(argv[1],argv[2],filename);		//checks whether the input and output files are the same, and exits with error if same
		}
		infile=fopen(argv[1],"r");	
		if(!infile)
		{
			fprintf(stderr,"%s: cannot open file '%s'\n",filename,argv[1]);
			exit(1);
		}
		head=readFileintoList(infile,head);	//read from the input file into the list
	}

	if(argc == 3)
	{
		outfile=fopen(argv[2],"w+");		//open the output file for writing
		if(!outfile)
		{
			fprintf(stderr,"%s: cannot open file '%s'\n",filename,argv[2]);
			exit(1);
		}
	}

	if(argc==1)
	{
		head=readFileintoList(infile,head);	//infile is NULL in this case, and it reads from the stdin
		
	}
    printList(head,outfile);	//print out the list	
	return 0;
}
