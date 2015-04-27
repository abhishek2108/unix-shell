/*
*****************MYSHELL**********************

Project By:
NAME 	: ABHISHEK KUMAR SINGH
USN  	: 1PE11CS005
BRANCH	: CSE
SEM	: VI
COLLEGE : PESIT-BSC

**********************************************
*/


#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ustat.h>
#include <time.h>
#include <utime.h>
#include <grp.h>
#include <sys/utsname.h>
#include <limits.h>
extern char **environ;
int getarguments(char inp[10],char *argv[50])
{
	char *ptr;
	int i=0;

	ptr=strtok(inp," ");

	while(ptr!=NULL)
	{
		argv[i++]=ptr;
		ptr=strtok(NULL," ");
	}
	return i;
}
void mylink(char *argv[],int argc)
{	if(strcmp(argv[1],"-s")==0)
         		{  	if(!symlink(argv[2],argv[3]))
                 			printf("soft link created\n");
             			else
                			printf("error creatng symlink\n");

          		}
          		else if(argc==3)
			{	 if(!link(argv[1],argv[2]))
                    			printf("hard link created\n");
                    		else
                   			printf("error creating hard link\n");
			}
          		else
				printf("syntax error\n");

}




int mycopy(char *argv[],int argc)
{

	if(argc!=3)
		{
			printf("invalid argv \n");
		}

	else
		{
			int fd,fd1,r;
			char buf[50],c;

     			fd=open(argv[1],0,0777); // opening the source file

			if(fd==-1)
				{
					printf("** Source file not found ** \n\n"); // source file missing
					return 1;
				}

				fd1=creat(argv[2],00777);    //  creating the file to copy

				while((r=read(fd,buf,1))>0)
					write(fd1,buf,1); // writing the contents to the file
				printf("file copied successfully\n");

		   }

	return 0;

}


void mydate(char *argv[], int argc)
{
	time_t t = time(NULL);
        struct tm tm = *localtime(&t);
	printf("The date is: %d-%d-%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

}



void mytime(char *argv[], int argc)
{
	time_t t = time(NULL);
        struct tm tm = *localtime(&t);
	printf("The time is: %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

}




int mycat(char *argv[],int argc)
{
	int i,fdesc,fdesc1,r;
	char buf[50];

	if(argc<2)
	{
		printf("mycat:Too few argv!**!");
		return 0;
	}

	else if(argc>2)
	{
		if(!strcmp(argv[1],">"))
		{
			fdesc=creat(argv[2],00777);
			while((r=read(0,buf,50))>0)
			write(fdesc,buf,r);
			return 0;
		}

		else if(!strcmp(argv[2],">"))
		{
			fdesc=open(argv[1],0,00777);
				if(fdesc==-1)
				{
					printf("mycat:%s:No such file or directory!**!\n",argv[1]);
					return 0;
				}

			fdesc1=creat(argv[3],00777);
			while((r=read(fdesc,buf,50))>0)
			write(fdesc1,buf,r);

		return 0;
	       	}

		else if(!strcmp(argv[2],">>"))
		{
			fdesc=open(argv[1],O_RDWR);
			fdesc1=open(argv[3],O_RDWR|O_APPEND);

			if(fdesc==-1)
			{
				printf("error");
				return 1;
			}

			if(fdesc1==-1)
			fdesc=creat(argv[3],00777);

			while((r=read(fdesc,buf,50))>0)
				write(fdesc1,buf,r);
				return 0;
		}

		else
		{
			for(i=1;i<argc;i++)
			{
				fdesc=open(argv[i],O_RDWR);
					if(fdesc==-1)
						printf("mycat:%s:No such file or directory!**!\n",argv[i]);
					else

					while((r=read(fdesc,buf,50))>0)
						write(1,buf,r);
			}
		}
	}

	else
	{
		fdesc=open(argv[1],0,O_RDWR);
			if(fdesc==-1)
				printf("mycat:%s:No such file or directory!**!\n",argv[1]);
			else

			while((r=read(fdesc,buf,50))>0)
				write(1,buf,r);
	}

	return 0;
}

void mymkdir(char *argv[],int argc)
{
	if(argc!=2)
	{
		printf("Invalid number of argv \n");
		return;
	}

	if(mkdir(argv[1],0777)==0)
		printf("Directory %s created! \n",argv[1]);
	else
		printf("Invalid path Or directory already exists \n");
}

void myrmdir(char *argv[],int argc)
{
	if(argc!=2)
	{
		printf("Invalid number of argv \n");
		return;
	}

	if(rmdir(argv[1])==0)
		printf("Directory %s successfully removed!\n",argv[1]);
	else
		printf("Invalid path / Directory is not empty \n");
}

int mychdir(char *argv[],int argc)
{
	

	if(argc!=2)
	{
		printf("invalid!!\n");
		exit(0);
	}

	if(access(argv[1],F_OK)==0)
	{
		if(!chdir(argv[1]));
		printf("directory changed\n");

		
	}

	else
	{
		perror("access");
}
	return 0;
}

void mymove(char *argv[],int argc)
{
	int fd,fd1,r;
	char buf1[50],buf2[50];
	switch(argc)
	{
		case 1:
		printf("Error:No argv!");
		break;
		case 2:
		printf("Error:Too few argv for move command!");
		break;
		case 3:
		mylink(argv,argc);
		unlink(argv[1]);
		printf("Contents of file %s moved to file %s\n",argv[1],argv[2]);
		break;
		default:
		printf("Error:Excess argv supplied!**!");
		break;
	}

}

void myrm(char *argv[],int argc)
{
	if(argc!=2)
	{	printf("Not enough argv\n");
		return ;
	}

			unlink(argv[1]);
			printf("File successfully deleted\n");


}

int mytouch(char *argv[],int argc)
{
	struct utimbuf times;
	if(argc!=2)
	{
		printf("usage error\n");
		exit(0);
	}
	if(access(argv[1],F_OK)==0)
	{
		times.actime=times.modtime=time(0);
	}
	else
	{
	creat(argv[1],S_IRWXU);
	times.actime=times.modtime=time(0);
	}
	if(utime(argv[1],&times))
	{
		printf("error\n");
	}
	return 0;
}


int mypwd(char *argv[],int argc)
{
	char buf[100];
	if(argc!=1)
	{
		printf("invalid number of arguments\n");
		exit(0);
	}
	else
	{
		getcwd(buf,sizeof(buf));
		printf("%s",buf);
	}
	return 0;
}

int myperm(char *argv[],int argc)
{
	int fd;
	if(argc!=2)
	{
		printf("Too few arguments");
		return;
	}
	else
	{
		if(access(argv[1],R_OK)==0)
		{
			printf("read permission exists\n");
		}
		if(access(argv[1],W_OK)==0)
		{
			printf("write permission exists\n");
		}
		if(access(argv[1],X_OK)==0)
		{
			printf("execute permission executes\n");
		}
		
	}
	return 0;
}


void mynls(char *argv[],int argc)
{
	DIR *dir1;
	struct dirent *dir;
	struct stat buf;
	char name[100],user[100],*usr;
	struct group *grp;
	if(argc == 1 || argc== 2)
	{
		if(strcmp(argv[1],".")==0 || argc == 1)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					printf("%s\t",dir->d_name);
				}
				printf("\n");
			}
		}
		else if(access(argv[1],F_OK)==0)
		{
			printf("%s\n",argv[1]);
		}
		else if(strcmp(argv[1],"-l")==0)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					
					if(stat(dir->d_name,&buf)==0)
					{

							printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    							printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    							printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    							printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    							printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    							printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    							printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    							printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    							printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    							printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
							printf(" %2d %s %2s %5d %10s %2s",(int)buf.st_nlink,getlogin(),getlogin(),(int)buf.st_size,dir->d_name,ctime(&buf.st_ctime));
					}
					else
					{
						perror("ls -l");
						return;
					}
				}
			}
		}
		
	}
	else if(argc == 3)
	{
		if(access(argv[2],F_OK)==0)
		{
			if((dir1=opendir("."))== NULL)
			{
				perror("ls");
			}
			else
			{
				while((dir=readdir(dir1)) != NULL)
				{
					
					if(stat(dir->d_name,&buf)==0)
					{
						//if(strcmp(argv[2],dir->d_name)==0)
						{
							grp=getgrnam(usr);
							printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    							printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    							printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    							printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    							printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    							printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    							printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    							printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    							printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    							printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
							printf(" %2d %s %2s %5d %10s %2s",(int)buf.st_nlink,getlogin(),grp->gr_name,(int)buf.st_size,dir->d_name,ctime(&buf.st_ctime));
							//printf("\n");
						}
					}
					else
					{
						perror("ls -l");
						return;
					}
				}
			}
		}
	}
	else
	{
		perror("Invalid no of arguments!!\n");
		return;
	}
}

int myuname()
{
	struct utsname buf;

	if(!uname(&buf))//Get name and information about current kernel.

		printf("%s\n",buf.sysname);//Display the system name.
	else
		perror("uname");//Display the error occurred while retrieving information about current kernel.

	return ;
}

int myecho(char *argv[],int argc)
{
	int i;
    	for(i=1;i<argc;i++)
	{
		printf("%s",argv[i]);
		printf(" ");
	}
	printf("\n");	
	return 0;
}

int mywc(char *argv[],int argc )
{
 int character_count = 0;
           int space_count = 0;
           int word_count = 0;
           int line_count = 0;
           char ch;

           FILE *fp;
           fp = fopen(argv[1],"r");

           if(argc == 0)
           {
   printf("Please specify the filename as argument\n");
                      exit(0);
           }

           


           while((ch=fgetc(fp))!=EOF)
           {
                       character_count++;
                       if(ch == ' ')
                       {
                             space_count++;
                             word_count++;
                       }
                       if(ch == '\n')
                       {
				line_count++;
                       }
           }
           printf("character_count = %d\n",character_count);
           printf("space_count = %d\n",space_count);
           printf("word_count = %d\n",word_count+1);
           printf("line_count = %d\n",line_count);
}

int mychmod(char *argv[],int argc)
{
	if(argc!=3)
	{
		printf("errorrr..\n");
		exit(0);
	}
	chmod(argv[1],(int)argv[2]);
	return 0;
}

int myenv()
{
	int i=0;

	while(environ[i]!=NULL)
	{
		puts(environ[i]);
		i++;
		printf("\n");
	}

	return 0;
}



int myexit()
{
	printf("Exiting MiniShell.....\n\n");
	exit(0);
}	


int main()
{
	int argc,i;
	printf("\n************************** MY SHELL ********************************\nProject By:\nABHISHEK KUMAR SINGH - 1PE11CS005\n********************************************************************\n");
	printf("--------------------------------------------------------------------\n");
	printf("Existing Commands are : \n");
	printf("1.) ln\t\t2.) cp\t\t3.) cat\t\t4.) mkdir\n\n");
	printf("5.) rmdir\t6.) env\t\t7.) uname\t8.) date\n\n");
	printf("9.) time\t10.) cd\t\t11.) mv\t\t12.) rm\n\n");
	printf("13.) touch\t14.) pwd\t15.) ls\t\t16.) echo\n\n");
	printf("17.) perm\t18.) wc\t\t19.) chmod\t20.) env\n\n");
	printf("Type \"exit\" to exit this shell.\n");
	printf("_____________________________________________________________________\n");
	printf("Enter the desired commands below :\n\n");

	char input[10],*argv[50];
	do
	{
		printf("\nabhishek's minishell:~$ ");
		gets(input);

		argc=getarguments(input,argv);
		if(strcmp(argv[0],"ln")==0)
			mylink(argv,argc);
		else if(strcmp(argv[0],"cp")==0)
			mycopy(argv,argc);
		else if(strcmp(argv[0],"date")==0)
			mydate(argv,argc);
		else if(strcmp(argv[0],"time")==0)
			mytime(argv,argc);
		else if(strcmp(argv[0],"cat")==0)
			mycat(argv,argc);
		else if(strcmp(argv[0],"mkdir")==0)
			mymkdir(argv,argc);
		else if(strcmp(argv[0],"rmdir")==0)
			myrmdir(argv,argc);
		else if(strcmp(argv[0],"cd")==0)
			mychdir(argv,argc);
		else if(strcmp(argv[0],"mv")==0)
			mymove(argv,argc);
		else if(strcmp(argv[0],"rm")==0)
			myrm(argv,argc);
		else if(strcmp(argv[0],"touch")==0)
			mytouch(argv,argc);
		else if(strcmp(argv[0],"pwd")==0)
			mypwd(argv,argc);
		else if(strcmp(argv[0],"perm")==0)
			myperm(argv,argc);
		else if(strcmp(argv[0],"ls")==0)
			mynls(argv,argc);
		else if(strcmp(argv[0],"uname")==0)
			myuname();
		else if(strcmp(argv[0],"echo")==0)
			myecho(argv,argc);
		else if(strcmp(argv[0],"wc")==0)
			mywc(argv,argc);
		else if(strcmp(argv[0],"chmod")==0)
			mychmod(argv,argc);
		else if(strcmp(argv[0],"env")==0)
			myenv();
		else if(strcmp(argv[0],"exit")==0)
			myexit();
		else printf("invalid Command....\n");

	}while(1);

	return 0;
}