#define NIJEOK 0
#define OK 1

#define KUNSKO_PLACANJE 1
#define DEVIZNO_POSLOVANJE 2
#define CEKOVI 3
#define KREDITI 4

#define KUNSKO_PLACANJE_S 11
#define DEVIZNO_POSLOVANJES 12
#define CEKOVI_S 13
#define KREDITI_S 14


/*fja1(int commSocket, int broj)
{if(broj < 10)
				{if(broj==1)
					{klijenti[broj][red1++]=brojacSocketa;
					novi1++;
					printf("%d, %d\n", broj, red1);
					if (posaljiPoruku(commSocket[brojacSocketa] , red1) == 0)
						printf("Poslao sam\n");
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
					novi3;
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
				{if(broj==11)
					{
					int brisi=klijenti[broj%10][red1-novi1];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red1-novi1+1) == 0) // 
						printf("Poslao sam\n");
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brisi]);
					close(commSocket[brojacSocketa]);
					novi1--;
					}	
				if(broj==12)
					{
					int brisi=klijenti[broj%10][red2-novi2];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red2-novi2+1) == 0) // 
						printf("Poslao sam\n");
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brisi]);
					close(commSocket[brojacSocketa]);
					novi2--;
					}	
				if(broj==13)
					{
					int brisi=klijenti[broj%10][red3-novi3];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red3-novi3+1) == 0) // 
						printf("Poslao sam\n");
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brisi]);
					close(commSocket[brojacSocketa]);
					novi3--;
					}	
				if(broj==14)
					{
					int brisi=klijenti[broj%10][red4-novi4];  //brise onaj socket u kojem se nalazi klijent koji dolazi na red
					if (posaljiPoruku(commSocket[brojacSocketa] , red4-novi4+1) == 0) // 
						printf("Poslao sam\n");
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brisi] );
					printf( "Zavrsio komunikaciju sa %s [socket=%d]\n", dekadskiIP, commSocket[brojacSocketa] );
					close(commSocket[brisi]);
					close(commSocket[brojacSocketa]);
					novi4--;
					}	
				}
}*/