#include"header.h"

int main(int argc,char *argv[])
{
	int sd,i,ret,len,count=0,x;

	struct sockaddr_in serveraddr;

	char final[MAX],buff[MAX];
	char *rchar;
	memset(final,0,MAX);
	memset(buff,0,MAX);
	if(argv[1]==NULL)
	{
		printf("Please enter IP ADDRESS\n");
		exit(0);
	}
	if(argv[2]==NULL)
	{
		printf("Please enter PORT NO.\n");
		exit(0);
	}
	for(i=3;i<argc;i++)
	{
		if(argv[i]==NULL)
		{
			printf("Please enter string\n");
			exit(0);
		}
	}
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		perror("Socket creating errorn\n");
		exit(0);
	}
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(MYPORT);
	serveraddr.sin_addr.s_addr= inet_addr(argv[1]);

	if((connect(sd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))<0)
	{
		printf("Cannot connect to server\n");
		exit(0);
	}
	for(i=3;i<argc;i++)
	{
		strcat(final,argv[i]);
		strcat(final," ");
	}
	printf("final str :%s\n",final);
	write(sd,final,strlen(final));
	//harshal
	ret = read(sd,buff,sizeof(buff));
	buff[ret]='\0';
	printf("length of buff %d %d",strlen(buff),ret);
	printf("string recvd from server %s \n",buff);
	len=strlen(buff);
	//buff[len-1]='\0';
	rchar=strtok(buff," ");
	while(NULL!=rchar)
	{
		count++;
		if((count%2)==1)
		{
			printf("%s\t",rchar);
		}
		else
		{
			printf("%s\n",rchar);
		}
		rchar = strtok(NULL," ");
	}
	shutdown(sd,SHUT_WR);
	return 0;
}
