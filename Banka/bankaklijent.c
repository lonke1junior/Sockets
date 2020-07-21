#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "poruke.h"

int posaljiPoruku(int sock, int vrstaPoruke);

int main( int argc, char **argv )
{
	if( argc != 3 )
		printf( "Upotreba: %s IP-adresa port\n", argv[0] );

	char dekadskiIP[20]; 
	strcpy( dekadskiIP, argv[1] );
	int port;          
	sscanf( argv[2], "%d", &port );

	int mojSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if( mojSocket == -1 )
		perror( "socket" );
		
	struct sockaddr_in adresaServera;
	
	adresaServera.sin_family = AF_INET;
	adresaServera.sin_port = htons( port );
	if( inet_aton( dekadskiIP, &adresaServera.sin_addr ) == 0 )
		printf( "%s nije dobra adresa!\n", dekadskiIP );

	memset( adresaServera.sin_zero, '\0', 8 );
	
	if( connect( mojSocket,(struct sockaddr *) &adresaServera,sizeof( adresaServera ) ) == -1 )
		perror( "connect" );

	if (posaljiPoruku(mojSocket, KUNSKO_PLACANJE) == 0)
	{
		printf("Poslao sam KUNSKO_PLACANJE\n");
	}
}

int posaljiPoruku(int sock, int vrstaPoruke)
{
	int poslano, poslanoZadnje;

	int vrstaPoruke_n = htonl( vrstaPoruke );
	poslanoZadnje = send( sock, &vrstaPoruke_n, sizeof( vrstaPoruke_n ), 0 );
	if( poslanoZadnje != sizeof( vrstaPoruke_n ) ) 
	{
			return NIJEOK;
	}

	return OK;
}
