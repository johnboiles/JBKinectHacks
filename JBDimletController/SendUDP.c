#include "SendUDP.h"

//#define SERVERPORT 4950    // the port users will be connecting to

struct hostent *he;
struct sockaddr_in their_addr; // connector's address information
int sockfd;		       // file descriptor for socket connection

//Initialize network connection
int SUDP_Init(const char* ipaddress){
   
    if ((he=gethostbyname(ipaddress)) == NULL) {  // get the host info
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(SERVERPORT); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
	return 0;
}

//Send a UDP packet
int SUDP_SendMsg(const char * data, int length)
{
    int numbytes;
    if ((numbytes = sendto(sockfd, data, length, 0,
             (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) 
    {
        perror("sendto");
        return -1;
    }

    return numbytes;
}

//Close the socket
int SUDP_Close(){
    close(sockfd);
    return 0;
}



