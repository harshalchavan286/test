#include"header.h"

int main()
{
	int sd,retbind,index=0,len,connfd,ret,length;
	//hello world

	char str_name[MAX];
	char final[MAX];
	char str1[MAX];
	char *rchar,*name[10];
	struct sockaddr_in serveraddr,clientaddr;
	memset(str_name,0,MAX);
	memset(final,0,MAX);
	memset(str1,0,MAX);
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		perror("Error in creating socket\n");
		exit(1);
	}
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(MYPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	retbind=bind(sd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(-1==retbind)
	{
		printf("binding error\n");
		exit(1);
	}
	listen(sd,5);

	for(;;)
	{
		printf("server running\n");
		len=sizeof(clientaddr);
		connfd=accept(sd,(struct sockaddr*)&clientaddr,&len);
		printf("\nConnection from= %s",inet_ntop(AF_INET,&clientaddr.sin_addr,str_name,sizeof(str_name)));
		ret = read(connfd,str_name,sizeof(str_name));
		str_name[ret]='\0';
		printf("String is: %s\n",str_name);
		length=strlen(str_name);
		//str_name[length-1]='\0';
		rchar=strtok(str_name," ");
		while(NULL != rchar)
		{
		//	name[index]=rchar;
			strcat(final,rchar);
			strcat(final," ");
			int l=strlen(rchar);
			sprintf(str1,"%d",l);
			strcat(final,str1);
			strcat(final," ");
			rchar = strtok(NULL," ");
		}
		write(connfd,final,sizeof(final));
		printf("string sent from server %s\n",final);
		close(connfd);
	}
	close(sd);
	return 0;
}
