#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib,"wsock32.lib")

int card();
int Check(int b);
int CheckAce(int b);
int Ace = 0;
int newCard;
int main() {
	//連線端
	/*WSADATA wsaData = {0};
	WORD wVer = MAKEWORD(2, 2);
	WSAStartup(wVer, &wsaData);

	SOCKET hSock;
	hSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in saListen;
	saListen.sin_family = AF_INET;
	saListen.sin_port = htons(10000);
	saListen.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(hSock, (sockaddr*)&saListen, sizeof(sockaddr));

	listen(hSock, 5);
	printf("waiting for connection ... \n");

	sockaddr_in saClient;
	int nSALen = sizeof(sockaddr);
	SOCKET hClient = accept(hSock, (sockaddr*)&saClient, &nSALen);

	int m, n;
	char buffer[100];
	printf("waiting for data ... \n");
	m = recv(hClient, buffer, sizeof(buffer), 0);
	printf("\t %d bytes received\n\t dumping received data:\n", m);
	for (n = 0; n < m; n++)
		printf("\t\t #%2d \t %2x \t %c\n", n, buffer[n], buffer[n]);
	printf("send back to client\n\t %d bytes sent\n", send(hClient, buffer, sizeof(buffer), 0));
	*/

	//21點
	srand((unsigned)time(NULL));
	int playerCard = 0;
	do {
		printf("enter 1 start game");
		int player;
		scanf("%d", &player);
		if (player == 1) {
			printf("Starting game...\n");
			newCard = card();
			playerCard+= newCard;
			newCard = card();
			playerCard+= newCard;
			if(playerCard>21)
				playerCard =CheckAce(playerCard);
		}else
			printf("Invalid input");
	} while (playerCard <= 0);
	if (playerCard<21) {
		int player;
		int Counter = 0;
		do {
			printf("%d\n", playerCard);
			printf("Double: 1/Hit: 2/Stand: 3\n");
			scanf("%d", &player);
			if (player == 1&& Counter==0) {
				printf("Double\n");
				playerCard += card();
				playerCard = CheckAce(playerCard);
				Counter++;
				break;
			}
			else if(player==1&&Counter!=0) {
				printf("\nYou have already doubled your bet.");
			}
			if (player == 2) {
				printf("Hit\n");
				playerCard += card();
				playerCard = CheckAce(playerCard);
				Counter++;
			}
			if (player == 3) {
				printf("Stand\n");
				break;
			}
		} while (Check(playerCard) == 1);
	}
	else if (playerCard == 21) {
		printf("\n21! BlackJack!");
		return 0;
	}else{
		printf("\nBust! You lose!");
		return 0;
	}
	printf("%d\n", playerCard);
	if (playerCard <= 21){
		printf("Dealer round\n");
		Ace = 0;
		int DealerCard = 0;
		while (DealerCard < 17 && DealerCard <= playerCard) {
			newCard = card();
			DealerCard += newCard;
			DealerCard = CheckAce(DealerCard);
		}
		printf("%d\n", DealerCard);
		if (DealerCard > 21)
			printf("Dealer busts!\n");
		if (DealerCard <= 21 && DealerCard > playerCard)
			printf("Dealer wins!\n");
		if (DealerCard == playerCard) 
			printf("Push! It's a tie!\n");
		if(DealerCard<playerCard) 
			printf("You win!\n");
		
	}else
		printf("You lose!\n");
	return 0;

	//close
	/*
	closesocket(hSock);
	WSACleanup();
	system("PAUSE");
	return EXIT_SUCCESS;
	*/
}

int card(){
	int a = rand() % 13 + 1;
	if(a>=10)
		a = 10;
	if (a == 1) {
		a = 11;
		Ace++;
	}
	printf("%d\n", a);
	return a;
}

int Check(int b) {
	if (b < 21) {
		return 1;
	}
	else if (b == 21) {
		return 0;
	}
	else {
		return 3;
	}
}
int CheckAce(int b) {
	if (b > 21 && Ace > 0) {
		b -= 10;
		Ace--;
		return b;
	}
	else
		return b;
}