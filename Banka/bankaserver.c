// u SERVERU SAM!!!!!!!!


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

int komunicirajSaKlijentom (int sock);
int primiPoruku( int sock, int *vrstaPoruke);
int porukaOdKlijenta(int vrstaPoruke);

int main( int argc, char **argv )
{
	if( argc != 2 )
		printf( "Upotreba: %s port\n", argv[0] );

	int port;
	sscanf( argv[1], "%d", &port ); //port servera na osluskuje

    int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 ); //uspjesno otvoren socket na serveru
    if( listenerSocket == -1 )
        perror( "socket" );
	
	struct sockaddr_in mojaAdresa; //def u nekoj liberiju

	mojaAdresa.sin_family = AF_INET;
	mojaAdresa.sin_port = htons( port );
	mojaAdresa.sin_addr.s_addr = INADDR_ANY;
	memset( mojaAdresa.sin_zero, '\0', 8 ); //polje od 8 znakova postavlja na 0, jer je tako definirano u struct sockaddr_in mojaAdresa

    if( bind( listenerSocket, (struct sockaddr *) &mojaAdresa, sizeof( mojaAdresa ) ) == -1 )
		perror( "bind" );

    if( listen( listenerSocket, 10 ) == -1 )
		perror( "listen" );

	int klijenti[10][1000];

	printf("Slusam na: %s\n", inet_ntoa(mojaAdresa.sin_addr));
	int brojacSocketa = 0;
	int red = 0;
	int commSocket[10000];
	int broj;
    
    while( 1 )
	{
        	struct sockaddr_in klijentAdresa;
			int lenAddr = sizeof( klijentAdresa ); //velicinu strukture
			brojacSocketa++;
			commSocket[brojacSocketa] = accept( listenerSocket, (struct sockaddr *) &klijentAdresa, &lenAddr ); //sockaddr umjesto sockaddr_in
                                                                                  //zato sto accept bas prima taj tip podatka
			if( commSocket[brojacSocketa] == -1 )
				perror( "accept" );

			char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr ); //zbog ljepšeg zapisa
			printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );

			broj = komunicirajSaKlijentom( commSocket[brojacSocketa] ); //kaze je li to klijent ili sluzbenik i koju vrstu zeli???
			if(broj < 10)
				{klijenti[broj][red++]=brojacSocketa;
				printf("%d, %d\n", broj, red);} //klijent - broj oznacava vrstu, a neki novi brojac koji je na redu
			else
				{int brisi=klijenti[broj%10][0];
				printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
				printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
				close(commSocket[brisi]);
				close(commSocket[brojacSocketa]);
				for (int i = 0; i < red-1; ++i)
					{
						klijenti[broj%10][i]=klijenti[broj%10][i+1];
					}	
		}
	}

    return 0;
}

int primiPoruku( int sock, int *vrstaPoruke)
{
	int primljeno, primljenoZadnje;
	int duljinaPoruke_n, duljinaPoruke;
	int vrstaPoruke_n;
	
	primljenoZadnje = recv( sock, &vrstaPoruke_n, sizeof( vrstaPoruke_n ), 0 );
	if(primljenoZadnje != sizeof(primljenoZadnje)) 
	{
		return NIJEOK;
	}
	*vrstaPoruke = ntohl( vrstaPoruke_n );

    if (porukaOdKlijenta(*vrstaPoruke))
    {
    	//Vrati mu broj broj klijentu
    	printf ("Primio sam poruku od klijena %d\n", *vrstaPoruke);

    } else {
    	//Vrati broj koji da sluzbenik prikaze
    	printf ("Primio sam poruku od sluzbenika %d\n", *vrstaPoruke);
    }


	return OK;
}

int porukaOdKlijenta(int vrstaPoruke)
{
	if (vrstaPoruke < 10)
	{
		return 1;
	}
	return 0;
}

int komunicirajSaKlijentom (int sock)
{
	int vrstaPoruke, gotovo = 0;
	primiPoruku(sock, &vrstaPoruke);
	return vrstaPoruke;
}

