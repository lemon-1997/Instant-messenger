#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define PORT 9999 
#define MAX 20 
/*
 *此服务器代码不做返回值判断！！！！！使用请自行添加
 */
int main(int argc,char * argv[])
{
	int lfd,cfd,efd,ret,i,j,n;
	char buf[1024];
	struct sockaddr_in saddr,caddr;
	socklen_t caddr_len = sizeof(caddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	lfd = socket(AF_INET,SOCK_STREAM,0);
	bind(lfd,(struct sockaddr *)&saddr,sizeof(saddr));
	listen(lfd,128);

	struct epoll_event temp, ep[MAX]; 
	efd = epoll_create(MAX);
	temp.events = EPOLLIN;
	temp.data.fd = lfd;
	epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &temp); 
	
	while(1)
	{
		ret = epoll_wait(efd,ep,MAX,-1);
		for(i=0;i<ret;++i)
		{
			if(!ep[i].events & EPOLLIN){
				continue;
			}
			if(ep[i].data.fd == lfd){
				cfd = accept(lfd, (struct sockaddr *)&caddr, &caddr_len);
				temp.events = EPOLLIN;
				temp.data.fd = cfd;     
				epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &temp);
				sprintf(buf,"%d",cfd);
				write(cfd,buf,strlen(buf));
			}
			else
			{
				n = read(ep[i].data.fd,buf,1024);
				if(n==0){
					epoll_ctl(efd,EPOLL_CTL_DEL,ep[i].data.fd,NULL);
					close(ep[i].data.fd);
				}
				else{
					char confd[2];
					int send_fd;
					confd[0] = buf[n-4];
					confd[1] = buf[n-3];
					send_fd = atoi(confd);
					for (j = 0; j < n-4; j++){
						buf[j] = toupper(buf[j]);
					}
					write(send_fd, buf, n); 
					write(STDOUT_FILENO,buf,n);
				}
			}
		}
	}
	return 0;
}
