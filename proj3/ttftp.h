/*
** name: ttftp.h
**
** author: bjr
** created: 31 jan 2015 by bjr
** last modified:
**   14 feb 2016, for 162 semester of csc424 -bjr 
**
*/

extern int g_verbose ;

#define MAXMSGLEN 2048
#define MAXFILENAMELEN 256

#define TFTP_RRQ 1
#define TFTP_WRQ 2
#define TFTP_DATA 3
#define TFTP_ACK 4
#define TFTP_ERR 5

//tftp error codes
#define FILENOTFOUND 1
#define PERMISSION 2
#define ILLEGALOP 4

#define OCTET_STRING "octet"
#define LEN_OCTET_STR 6
#define TFTP_DATALEN 512

#define ACK_TIMEOUT 4
#define ACK_RETRY 6

#define VAR_SIZE 0 

typedef struct TftpReq {
	char opcode[2] ;
	char filename_and_mode[MAXFILENAMELEN+LEN_OCTET_STR] ; /* size varies */
}TftpReq;

typedef struct TftpData {
	char opcode[2] ;
	char block_num[2] ;
	char data[TFTP_DATALEN] ; /* zero to 512 bytes */
}TftpData;

typedef struct TftpAck {
	char opcode[2] ;
	char block_num[2] ;
}TftpAck;

typedef struct TftpError {
	char opcode[2] ;
	char error_code[2] ;
	char error_msg[MAXMSGLEN-4];
}TftpError;

int  ttftp_client( char * host, char* port, char * file ) ;
int  ttftp_server( char *listen_port, int is_noloop ) ;
void validate(char* filename);
void validatePort(char* port);
int sendErrorPacket(int error_code,char* error_msg,struct sockaddr_in*client_addr,int sock);
void check(int val,char *error_msg);
int fillDataPacket(FILE* file,char *data);
int sendDataPacket(int sock,struct sockaddr_in *client_addr,TftpData *data_packet,int size);
int sendAckPacket(int block_num,int sock,struct sockaddr_in *client_addr);
int sendRRQ(TftpReq* rrq_packet,int sock, struct sockaddr* client_addr);
TftpReq* createRRQ(char* filename);
FILE * openFile(char *filename);
