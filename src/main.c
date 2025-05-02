#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void printA(int sig){
	printf("A\n");
	fflush(stdout);
}

void printB(int sig){
	printf("B\n");
	fflush(stdout);
}

void printC(int sig){
	printf("C\n");
	fflush(stdout);
}

void print_handler(const char *label, void (*handler)(int)){
	printf("%s: %p", label, (void *)handler);
	if(handler == SIG_DFL){
		printf(" (SIG_DFL)\n");
	}
	else if(handler == SIG_IGN){
		printf(" (SIG_IGN)\n");
	}
	else{
		printf(" (custom handler)\n");
	}
	fflush(stdout);
}

int main(){

	struct sigaction sa, sb, sc, sold;
	
	memset(&sa, 0, sizeof(struct sigaction));
	memset(&sb, 0, sizeof(struct sigaction));
	memset(&sc, 0, sizeof(struct sigaction));
	memset(&sold, 0, sizeof(struct sigaction));

	sa.sa_handler = printA;
	sb.sa_handler = printB;
	sc.sa_handler = printC;

	sigemptyset(&sa.sa_mask);
	sigemptyset(&sb.sa_mask);
	sigemptyset(&sc.sa_mask);

	sa.sa_flags = 0;
	sb.sa_flags = 0;
	sc.sa_flags = 0;

	sigaction(SIGALRM, NULL, &sold);
	printf("Initial SIGALRM action:\n");
	print_handler("sold.sa_handler", sold.sa_handler);

	sigaction(SIGALRM, &sa, &sold);
	print_handler("After setting act=printA, old handler", sold.sa_handler);
	raise(SIGALRM);
	
	sigaction(SIGALRM, &sb, &sold);
	print_handler("After setting act=printB, old handler", sold.sa_handler);
	raise(SIGALRM);

	sigaction(SIGALRM, &sc, &sold);
	print_handler("After setting act=printC, old handler", sold.sa_handler);
	raise(SIGALRM);

	return 0;
}
