#include<termios.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
static struct termios termios_old;
int main(int argc,char**argv){
	system("clear");
	tcgetattr(0,&termios_old);
	struct termios t=termios_old;
	t.c_lflag&=~ICANON;
	t.c_lflag&=~ECHO;
	tcsetattr(0,TCSANOW,&t);

	char bs[]{"  \b"};
	char buf[8];
	const int bufn{sizeof buf};
	char*bufp{buf};
	char*bufe{buf+bufn};
	while(true){
//		if(bufp==bufe)break;
		char c=getchar();
		printf(" %d ",c);
		if(c=='\b'){
			if(bufp==buf)continue;
			bs[0]=c;
			write(1,bs,sizeof bs);
			bufp--;
			continue;
		}else{
			if(bufp<bufe){
				write(1,&c,1);
				*bufp++=c;
			}
		}
		if(c=='\n')break;
	}
	write(1,buf,bufp-buf);
	tcsetattr(0,TCSANOW,&termios_old);
	return 0;
}


// forked from http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
