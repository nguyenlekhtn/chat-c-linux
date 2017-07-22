#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

const int port = 8888;
const int bufSize = 1025;

void error(char *msg);
int compareStrings(char a[], char b[]);

int main()
{
	// khai bao bien
	int clientSocket, addrSize;
	char message[bufSize];
	struct sockaddr_in serverAddr;
	
	// tao socket client
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
		error("ERROR opening socket");
	
	// khai bao server
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	
	addrSize = sizeof(serverAddr);
	
	// ket noi toi server
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, addrSize) < 0)
		error("ERROR connecting");
	
	printf("---- Connected ----\n");
	printf("---- Go check de load chat hien tai ----\n");
	
	while(1)
	{
		//printf("Bat dau\n");
		// doc noi dung tu socket
		memset(&message[0], 0, sizeof(message));
		int readValue = recv(clientSocket, message, sizeof message - 1, MSG_DONTWAIT);
		//printf("Readvalue = %d\n", readValue);
		
		// loi
/*		if(readValue < 0)
			error("ERROR reading");
		else
		{
			
			// neu noi dung trong thi nhap tin nhan
			if(readValue == 0)
			{
				printf("You: ");
				fgets(message, bufSize, stdin);
				message[strcspn(message, "\n")] = '\0';
				send(clientSocket, message, bufSize, 0);
				memset(&message[0], 0, sizeof(message));
			}
			else
			{
				// nguoc lai thi in tin nhan
				printf("%s\n", message);
				memset(&message[0], 0, sizeof(message));
			}
		}*/
	
		if(readValue > 0)
		{
			printf("%s\n", message);
			memset(&message[0], 0, sizeof(message));
		}
		else
		{
			printf("You: ");
			scanf(" %[^\n]s", message);
			if(compareStrings(message, "check") != 0)
			{
				int size;
				if((size = send(clientSocket, message, bufSize - 1, 0))	< 0)
					error("ERROR sending");
				send(clientSocket, "\n", sizeof("\n"), 0);
				// printf("Sent!\n");
			}
			else
			{
				continue;
			}
			
			
		}
		
			
//		printf("Ket thuc\n");
	}
			


	
	return 0;
}
		
						  
	
void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// ham so sanh chuoi ki tu, tra ve 0 neu giong
// nguoc lai thi -1

int compareStrings(char a[], char b[])
{
    int c = 0;
    while (a[c] == b[c]) 
    {
        if (a[c] == '\0' || b[c] == '\0')
        break;
        c++;
    }
    if (a[c] == '\0' && b[c] == '\0')
    return 0;
    else
    return -1;
}
