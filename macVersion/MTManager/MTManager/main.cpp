/*
 * tcpclient.c - A simple TCP client
 * usage: tcpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}
void readConsole(char* buf){
    /* get message line from the user */
    printf("Please enter msg: ");
    bzero(buf, BUFSIZE);
    fgets(buf, BUFSIZE, stdin);
}
int main(int argc, char **argv) {
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    
//    /* check command line arguments */
//    if (argc != 3) {
//        fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
//        exit(0);
//    }
    hostname = "localhost";//argv[1];
    portno = 1984;//atoi(argv[2]);
    
    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    
    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }
    
    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);
    
    /* connect: create a connection with the server */
    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
        error("ERROR connecting");
    
    
    int listenPID=fork();
    if(listenPID==0){//child proc for listen
        listenPID = getpid();
        while(1){
            bzero(buf, BUFSIZE);
            n = read(sockfd, buf, BUFSIZE);
            if (n < 0)
                error("ERROR reading from socket");
            printf("Echo from server: %s", buf);
        }
    }
    
    while(buf[0]!=':'){

    bzero(buf, BUFSIZE);
    readConsole(buf);
    if(fork()==0){
        n = write(sockfd, buf, strlen(buf));
        if (n < 0)
            error("ERROR writing to socket");
        exit(0);
    }
            
    }
    
    
    kill(listenPID,SIGKILL);
    close(sockfd);
    return 0;
    
    
//    while(buf[0]!=':'){
//        
////        /* send the message line to the server */
////        n = write(sockfd, buf, strlen(buf));
////        if (n < 0)
////            error("ERROR writing to socket");
////        
////        
////        
//        int pid;
//        if (fork() == 0) {
//            pid = fork();
//            if (pid == 0) {//child's child proc for sending
//                /* send the message line to the server */
//                n = write(sockfd, buf, strlen(buf));
//                if (n < 0)
//                    error("ERROR writing to socket");
//            }
//            else{//child proc for recieving
//                /* print the server's reply */
//                bzero(buf, BUFSIZE);
//                n = read(sockfd, buf, BUFSIZE);
//                if (n < 0)
//                    error("ERROR reading from socket");
//                printf("Echo from server: %s", buf);
//            }
//            exit(0);  // child terminates here
//        }
//        
        

        
        //        int pid;
        //        if (fork() == 0) {
        //            pid = fork();
        //            if (pid == 0) {//child's child proc for sending
        //                /* send the message line to the server */
        //                n = write(sockfd, buf, strlen(buf));
        //                if (n < 0)
        //                    error("ERROR writing to socket");
        //            }
        //            else{//child proc for recieving
        //                /* print the server's reply */
        //                bzero(buf, BUFSIZE);
        //                n = read(sockfd, buf, BUFSIZE);
        //                if (n < 0)
        //                    error("ERROR reading from socket");
        //                printf("Echo from server: %s", buf);
        //            }
        //            exit(0);  // child terminates here
        //        }
        
    
}
