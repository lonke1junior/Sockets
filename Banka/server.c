/*Pomoću biblioteke Sockets API napišite tri programa (dva klijenta, jedan poslužitelj) koji simuliraju čekanje na
red u poslovnici banke.

Prvi klijent nastupa u ime stranke koja je došla obaviti neki posao u poslovnici banke. Klijent šalje
oznaku vrste posla (kunsko poslovanje, devizno poslovanje, čekovi, … ), a poslužitelj vraća broj za listić s
kojim će stranka čekati na red.

Drugi klijent nastupa u ime službenika banke specijaliziranog za određenu vrstu posla. Klijent javlja da je
službenik za dotičnu vrstu posla slobodan. Poslužitelj vraća broj stranke koja je na redu za tu vrstu
posla i koju službenik treba pozvati da priđe šalteru.*/


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

#include <pthread.h>

#include "poruke.h"

int posaljiPoruku(int sock, int vrstaPoruke);
int komunicirajSaKlijentom (int sock);
int primiPoruku( int sock, int *vrstaPoruke);
int porukaOdKlijenta(int vrstaPoruke);

/*typedef struct par
{int commSocket[10000];
int broj;
};*/

int klijenti[10][1000];
int brojacSocketa = 0;
int red1 = 0, red2 = 0, red3 = 0, red4 = 0;
int novi1 = 0, novi2 = 0, novi3 = 0, novi4 =0;
pthread_mutex_t lokot_ekran = PTHREAD_MUTEX_INITIALIZER;

int main( int argc, char **argv )
{
	pthread_t dretva[2];
	int isError;

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

	int broj;
	int commSocket[10000];

	printf("Slusam na: %s\n", inet_ntoa(mojaAdresa.sin_addr));

	while( 1 )
	{
        	struct sockaddr_in klijentAdresa;
			int lenAddr = sizeof( klijentAdresa ); //velicinu strukture

            //pthread_mutex_lock(&lokot_ekran);
			brojacSocketa++;
			commSocket[brojacSocketa] = accept( listenerSocket, (struct sockaddr *) &klijentAdresa, &lenAddr ); //sockaddr umjesto sockaddr_in
                                                                         //zato sto accept bas prima taj tip podatka
			if( commSocket[brojacSocketa] == -1 )
				perror( "accept" );

			char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr ); //zbog ljep�eg zapisa
			printf( "Prihvatio konekciju od %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
            //pthread_mutex_unlock(&lokot_ekran);
			broj = komunicirajSaKlijentom( commSocket[brojacSocketa] ); //kaze je li to klijent ili sluzbenik i koju vrstu zeli???

			if(broj< 10)
				{if(broj==1)
					{klijenti[broj][red1++]=brojacSocketa;
					novi1++;
					printf("%d, %d\n", broj, red1);
					if (posaljiPoruku(commSocket[brojacSocketa] , red1) == 0)
						printf("Poslao sam\n");
					printf("red %d\n", red1);
					}
				if(broj==2)
					{klijenti[broj][red2++]=brojacSocketa;
					novi2++;
					printf("%d, %d\n", broj, red2);
					if (posaljiPoruku(commSocket[brojacSocketa], red2) == 0)
						printf("Poslao sam\n");
					}
				if(broj==3)
					{klijenti[broj][red3++]=brojacSocketa;
					novi3++;
					printf("%d, %d\n", broj, red3);
					if (posaljiPoruku(commSocket[brojacSocketa] , red3) == 0)
						printf("Poslao sam\n");
					}
				if(broj==4)
					{klijenti[broj][red4++]=brojacSocketa;
					novi4++;
					printf("%d, %d\n", broj, red4);
					if (posaljiPoruku(commSocket[brojacSocketa] , red4) == 0)
						printf("Poslao sam\n");
					}
				}
			else
				{
				if(broj==11)
					{if(novi1==0)
						{if (posaljiPoruku(commSocket[brojacSocketa] , 0) == 0) //
							printf("Poslao sam\n");}
					else
					{
					int brisi=klijenti[broj%10][red1-novi1];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red1-novi1+1) == 0) //
						printf("Poslao sam\n");
						novi1--;
					printf("%d, %d\n", red1, novi1);
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					close(commSocket[brisi]);}
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brojacSocketa]);
					}
				if(broj==12)
					{
					if(novi2==0)
						{if (posaljiPoruku(commSocket[brojacSocketa] , 0) == 0) //
							printf("Poslao sam\n");}
					else
					{
					int brisi=klijenti[broj%10][red2-novi2];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red2-novi2+1) == 0) //
						printf("Poslao sam\n");
						novi2--;
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					close(commSocket[brisi]);}
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brojacSocketa]);
					}
				if(broj==13)
					{
					if(novi3==0)
						{if (posaljiPoruku(commSocket[brojacSocketa] , 0) == 0) //
							printf("Poslao sam\n");}
					else
					{
					int brisi=klijenti[broj%10][red3-novi3];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red3-novi3+1) == 0) //
						printf("Poslao sam\n");
					novi3--;
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					close(commSocket[brisi]);}
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brojacSocketa]);
					}
				if(broj==14)
					{
					if(novi4==0)
						{if (posaljiPoruku(commSocket[brojacSocketa] , 0) == 0) //
							printf("Poslao sam\n");}
					else
					{
					int brisi=klijenti[broj%10][red4-novi4];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red4-novi4+1) == 0) //
						printf("Poslao sam\n");
						novi4--;
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					close(commSocket[brisi]);}
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brojacSocketa]);
					}
				}
			}
    return 0;
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
