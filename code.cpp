#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define MAX_ROW 8
#define MAX_COL 8

void clrscr() // Ekrani temizlemek icin kullanilan fonksiyon
{
    system("@cls||clear");
}

void fileCreator(char checker[MAX_ROW][MAX_COL]) // bu fonksiyon oyunun ilk acilisinda, dosyayi ilk baslangic halinde olusturmaktadir.
{
	FILE *fp, *fclptr;
	// ================================== bu kisim oyun adimlarini kayit eden dosyaya yeni oyun baslangicinda tarih atmak icin olusturuldu
	char text[100];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);	
	strftime(text, sizeof(text)-1, "%d %m %Y %H:%M", t);
	fclptr = fopen("cCLog.txt", "a+");
	fputs("\nNew Game\n",fclptr);
	fputs(text,fclptr);
	fputs("\n",fclptr);
	fclose(fclptr);
	// ==================================\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/
  	
	fp = fopen("checkersLog.txt", "wb");
	if( !fp )	// fopen() return NULL if last operation was unsuccessful
	{
		// File not created hence exit
		printf("Unable to creat file.\n");
		exit(EXIT_FAILURE);
	}
	// checker[][] dizisi donulerek karakter karakter dosyaya yazilacak
	for (int i = 0; i < MAX_ROW; i++){
		for (int j = 0 ; j < MAX_COL ; j++) // The for loop here is to print where should be the player 1 and player 2 chess should be located
			{
				//fwrite(checker[i][j], 8, 1, fp );
				fputc(checker[i][j],fp);
			}	
			fputs("\n",fp);
	}
	fputc('w',fp);
	fclose(fp);
}

void fileUpdater(char checker[MAX_ROW][MAX_COL], int i1, int i2, int j1, int j2, int rmv, int ri, int rj) // bu fonksiyon her hamleden sonra tahta gorunumunu dosyadan guncellemek icin olusturuldu
{
	
//	int p;
//	FILE * fuptr;
//	fuptr = fopen("checkersLog.txt", "w+");
	
//	fseek(fuptr, p, SEEK_SET);
	

	
// rewind(fuptr) used for to set file pointer to starting point in the file
// fseek(fuptr, 0, 0) this will take us to the beginning of the file
// fseek(fuptr, N, 0) this will take us to (N+1)th bytes in the file
// fseek(fuptr, -1, 2) this will take us to the last char of the file

//	i,j						x							
//	0,0 0,1 0,2 0,3 0,4 0,5 0,6 0,7
//	1,0	1,1 1,2 1,3 1,4 1,5 1,6 1,7 
//	2,0	2,1 2,2 2,3 2,4 2,5 2,6 2,7 
//	3,0	3,1 3,2 3,3 3,4 3,5 3,6 3,7 
//	4,0	4,1 4,2 4,3 4,4 4,5 4,6 4,7 
//	5,0	5,1 5,2 5,3 5,4 5,5 5,6 5,7	 
//	6,0	6,1 6,2 6,3 6,4 6,5 6,6 6,7 
//	7,0	7,1 7,2 7,3 7,4 7,5 7,6 7,7 
//		 				
	
//	fclose(fuptr);
}

void fileUploader(char checker[MAX_ROW][MAX_COL]) // bu fonksiyon oyun yeni acildiginda kalan oyundan devam edilmek istenirse dosyadaki kayittan tahta durumunu getirmek icin olusturuldu
{
	char c;
	char *line;
	FILE *fsptr;
	fsptr = fopen("checkersLog.txt", "r");
 
	int i=0,j=0;
	while( !feof(fsptr) ) {
		c = fgetc(fsptr); 
		if( c != '\n')	
			{
				checker[i][j] = c;
  				j++;
				if(j == 8)
				{
					j=0;
					i++;
				}
				if(i==8)
					break;
			}
	} // end while
 
	fclose(fsptr);
} // end function

char roleChecker() // bu fonksiyon oyuna devam etmek icin dosyadan en son oyunun kimde kaldigina bakiyor
{
	char p;
	FILE *frptr;
	frptr = fopen("checkersLog.txt", "r");
	fseek(frptr, -1, 2);
	p = fgetc(frptr);
	fclose(frptr);
	return p;
}  // end function

void roleSetter(char p) // bu fonksiyon dosyadan sadece siranin hangi oyuncuda oldugunu gosteren kismi guncelliyor(en son kisim)
{
	FILE *frsptr;
	frsptr = fopen("checkersLog.txt", "r+");
	fseek(frsptr, -1, 2);
	fputc(p, frsptr);
	fclose(frsptr);
} // end function

void commandLogFunc(int playe, char command[4] ) // bu fonksiyon oyuncularin hamlalerini sequential olarak kayida aliyor ============================== ODEV 2. KISIM ==============================
{
	// write each turn's player command into an additonal sequential access file. 
	// The file's content is going to be like this 
	// w:a3a4
	// b:f5e5
	// sequential file organization designed using fprintf() function
	char *c, *data;
	if( playe == 1 )
		c = "w:" ;
	else if( playe == 0 )
		c = "b:";
  
	char* str1;
    char* str2;
    str1 = c;
    str2 = command;
    char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
 	strcpy(str3, str1);
    strcat(str3, str2);
     
	FILE * fclptr;
	fclptr = fopen("cCLog.txt", "a+");
 	fprintf(fclptr, str3);
 	fprintf(fclptr, "\n");
 	fclose(fclptr);
} // end function

void displayboard(char checker[MAX_ROW][MAX_COL]){
	int i, j;
	clrscr();
	printf("     A   B   C   D   E   F   G   H   \n");
	
		for (i = 0; i < MAX_ROW; i++){
			printf (" %d", 8 - i );
			printf(" | ");
			for (j = 0 ; j < MAX_COL ; j++) // The for loop here is to print where should be the player 1 and player 2 chess should be located
				if(checker[i][j] == 'W' || checker[i][j] == 'B') // Tasin dama olup olmadigina kontrol ediyoruz
					printf("%c%c| ", tolower(checker[i][j]), tolower(checker[i][j]));
				else
					printf("%c | ", checker[i][j]); 
			printf("\n");
		}
	printf("\n\n");

} // end function



void populatechecker(char checker[MAX_ROW][MAX_COL]){	// bu fonksiyon taslarin ilk dizilisini ayarlamak icin
	int i, j;											// ayni zamanda checker[][] dizisini de olusturuyor
														// daha sonra hamleler oldukca bu dizi guncellenecek
	for(i = 0; i < MAX_ROW; i++)
		for( j = 0; j < MAX_COL; j++)
			checker[i][j] = ' ';
	
	for(i = 0; i < MAX_ROW; i++)
		for ( j = 0; j < MAX_COL; j++)
			if ( i >= 1 && i <= 2 )
				checker[i][j] = 'w';
			
	for(i = 0; i < MAX_ROW; i++)
		for(j = 0; j < MAX_COL; j++)
			if( i >= 5 && i <= 6  )
				checker[i][j] = 'b';

//  hafizada kayitli olan					ekranda olan
//	i,j										y,x							
//	0,0 0,1 0,2 0,3 0,4 0,5 0,6 0,7
//	1,0	1,1 1,2 1,3 1,4 1,5 1,6 1,7 			a,8 b,8 c,8 d,8 e,8 f,8 g,8 h,8  8=8-i
//	2,0	2,1 2,2 2,3 2,4 2,5 2,6 2,7 			a,7 b,7 c,7 d,7 e,7 f,7 g,7 h,7	 7=8-i
//	3,0	3,1 3,2 3,3 3,4 3,5 3,6 3,7   	 		a,6 b,6 c,6 d,6 e,6 f,6 g,6 h,6	 6=8-i
//	4,0	4,1 4,2 4,3 4,4 4,5 4,6 4,7 			a,5 b,5 c,5 d,5 e,5 f,5 g,5 h,5  5=8-i
//	5,0	5,1 5,2 5,3 5,4 5,5 5,6 5,7		 		a,4 b,4 c,4 d,4 e,4 f,4 g,4 h,4  4=8-i
//	6,0	6,1 6,2 6,3 6,4 6,5 6,6 6,7 			a,3 b,3 c,3 d,3 e,3 f,3 g,3 h,3  3=8-i
//	7,0	7,1 7,2 7,3 7,4 7,5 7,6 7,7 			a,2 b,2 c,2 d,2 e,2 f,2 g,2 h,2  2=8-i
//		 										a,1 b,1 c,1 d,1 e,1 f,1 g,1 h,1  1==8-i
										//		a=0 b=1 c=2 d=3 e=4 f=5 g=6 h=7
			
} // end function

void gameScore(int white, int black)
{
	printf("************** Game Over **************\n\n");
			
	if (white == 1)
		printf("***White Wins!***");
	else if (black == 1)
		printf("***Black Wins!***");

	char checker[MAX_ROW][MAX_COL];
	populatechecker(checker);
} // end function

void progressSelector(char checker[MAX_ROW][MAX_COL], int cnt) // bu fonksiyon oyunun sifirdan mi basladigini yoksa kaldigi yerden devam mi ettigini kontrol edip ekrani duzenliyor.
{
	if(cnt == 0 )
	{
		populatechecker(checker);
	}	
		
	displayboard(checker);
} // end function

int commandChecker(char checker[MAX_ROW][MAX_COL], char command[4], int player, int wpiece, int bpiece ) // oyunun komutlari burada kontrol edilip gerceklestiriliyor
{
	int i1,j1,i2,j2;
	int x1, x2 ;
	char y1, y2 ;
 	
	y1 = command[0];
	x1 = command[1];
	y2 = command[2];
	x2 = command[3];
	
	if(x1 == '8' )
		i1=0;
	else if(x1 == '7')
		i1=1;
	else if(x1 == '6')
		i1=2;
	else if(x1 == '5')
		i1=3;
	else if(x1 == '4')
		i1=4;
	else if(x1 == '3')
		i1=5;
	else if(x1 == '2')
		i1=6;
	else if(x1 == '1')
		i1=7;
	else
	{
		return 0; 
	}
	
	
	if(y1 == 'a')
		j1=0;
	else if(y1 == 'b')
		j1=1;
	else if(y1 == 'c')
		j1=2;
	else if(y1 == 'd')
		j1=3;
	else if(y1 == 'e')
		j1=4;
	else if(y1 == 'f')
		j1=5;
	else if(y1 == 'g')
		j1=6;
	else if(y1 == 'h')
		j1=7;
	else
	{
		return 0; 
	}
	
	fflush(stdin);
	// target command check step
	if(x2 == '8' )
		i2=0;
	else if(x2 == '7')
		i2=1;
	else if(x2 == '6')
		i2=2;
	else if(x2 == '5')
		i2=3;
	else if(x2 == '4')
		i2=4;
	else if(x2 == '3')
		i2=5;
	else if(x2 == '2')
		i2=6;
	else if(x2 == '1')
		i2=7;
	else
	{
		return 0; 
	}
	
	if(y2 == 'a')
		j2=0;
	else if(y2 == 'b')
		j2=1;
	else if(y2 == 'c')
		j2=2;
	else if(y2 == 'd')
		j2=3;
	else if(y2 == 'e')
		j2=4;
	else if(y2 == 'f')
		j2=5;
	else if(y2 == 'g')
		j2=6;
	else if(y2 == 'h')
		j2=7;
	else
	{
		return 0; 
	}
	
	
	// dama olma durumlari tek kare giderek white
	if(   checker[i1][j1] == 'w' && checker[i2][j2] == ' ' && i2 == 7 && i1 == 6 && ( j2 - j1 == 0 )    )
	{
		
		checker[i2][j2] = 'W';
		checker[i1][j1] = ' ';
		return 1;
	}
	// dama olma durumlari tek kare giderek black
	else if(   checker[i1][j1] == 'b' && checker[i2][j2] == ' ' && i2 == 0 && i1 == 1 && ( j2 - j1 == 0 )   )
	{
		
		checker[i2][j2] = 'B';
		checker[i1][j1] = ' ';
		return 1;
	}
	// dama olma durumlari tas yiyerek white
	else if( (checker[i1][j1] == 'w' && checker[i2][j2] == ' ' && i2 == 7 && i1 == 5  && ( j2 - j1 == 0 ) && ( checker[6][j1] == 'b' || checker[6][j1] == 'B' )  )  )
	{
		checker[6][j1] = ' ';
		bpiece--;
		checker[i2][j2] = 'W';
		checker[i1][j1] = ' ';
		return 2;
	}
	// dama olma durumlari tas yiyerek black
		else if( (checker[i1][j1] == 'b' && checker[i2][j2] == ' ' && i2 == 0 && i1 == 2  && ( j2 - j1 == 0 ) && ( checker[1][j1] == 'w' || checker[6][j1] == 'W' )  )  )
	{
		checker[1][j1] = ' ';
		bpiece--;
		checker[i2][j2] = 'B';
		checker[i1][j1] = ' ';
		return 2;
	}
	// tek kare gitme durumlari
	else if((checker[i1][j1] == 'w' || checker[i1][j1] == 'W') && ( (i2-i1 == 0 && (j2-j1 == 1 || j2-j1 == -1 ) ) ||  ( i2-i1 == 1 && j2-j1 == 0 ) ) && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'w')
				checker[i2][j2] = 'w';
			else if(checker[i1][j1] == 'W')
				checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			return 1;
					
		}
	else if(( checker[i1][j1] == 'b' || checker[i1][j1] == 'B' ) && ( ( i2-i1 == 0 && (j2-j1 == 1 || j2-j1 == -1) ) || ( i2-i1 == -1 && j2-j1 == 0 ) ) && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'b')
				checker[i2][j2] = 'b';
			else if(checker[i1][j1] == 'B')
				checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			return 1;
			
		}
	// tas yeme durumlari beyaz siyahi yer sag 
	else if( ( ( checker[i1][j1] == 'w' || checker[i1][j1] == 'W' ) && ( i2-i1 == 0 &&  j2-j1 == 2 ) ) && ( checker[i1][j2-1] == 'b' || checker[i1][j2-1] == 'B') && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'w')
				checker[i2][j2] = 'w';
			else if(checker[i1][j1] == 'W')
				checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			checker[i1][j2-1] = ' ';
			bpiece--;
			return 2;
		}
	// tas yeme durumlari beyaz siyahi yer sol	
	else if( ( ( checker[i1][j1] == 'w' || checker[i1][j1] == 'W' ) && ( i2-i1 == 0 &&  j2-j1 == -2 ) ) && ( checker[i1][j2+1] == 'b' || checker[i1][j2+1] == 'B' ) && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'w')
				checker[i2][j2] = 'w';
			else if(checker[i1][j1] == 'W')
				checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			checker[i1][j2+1] = ' ';
			bpiece--;
			return 2;
		}
	// tas yeme durumlari beyaz siyahi yer asagi		
	else if( ( ( checker[i1][j1] == 'w' || checker[i1][j1] == 'W' ) && (  i2-i1 == 2 && j2-j1 == 0 ) ) && (checker[i1+1][j1] == 'b' || checker[i1+1][j1] == 'B') && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'w')
				checker[i2][j2] = 'w';
			else if(checker[i1][j1] == 'W')
				checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			checker[i1+1][j1] = ' ';
			bpiece--;
			return 2;
		}
	
	// tas yeme durumlari siyah beyazi yer sag 
	else if( ( ( checker[i1][j1] == 'b' || checker[i1][j1] == 'B' )  && ( i2-i1 == 0 &&  j2-j1 == 2 ) ) && ( checker[i1][j2-1] == 'w' || checker[i1][j2-1] == 'W') && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'b')
				checker[i2][j2] = 'b';
			else if(checker[i1][j1] == 'B')
				checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			checker[i1][j2-1] = ' ';
			wpiece--;
			return 2;
		}
	// tas yeme durumlari siyah beyazi yer sol	
	else if( ( ( checker[i1][j1] == 'b' || checker[i1][j1] == 'B' ) && ( i2-i1 == 0 &&  j2-j1 == -2 ) ) && ( checker[i1][j2+1] == 'w' || checker[i1][j2+1] == 'W' ) && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'b')
				checker[i2][j2] = 'b';
			else if(checker[i1][j1] == 'B')
				checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			checker[i1][j2+1] = ' ';
			wpiece--;
			return 2;
		}
	// tas yeme durumlari siyah beyazi yer yukari		
	else if( (( checker[i1][j1] == 'b' || checker[i1][j1] == 'B' ) && (  i2-i1 == -2 && j2-j1 == 0 ) ) && (checker[i1-1][j1] == 'w' || checker[i1-1][j1] == 'W') && checker[i2][j2] == ' ' )
		{
			if(checker[i1][j1] == 'b')
				checker[i2][j2] = 'b';
			else if(checker[i1][j1] == 'B')
				checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			checker[i1-1][j1] = ' ';
			wpiece--;
			return 2;
		}

		
	// dama hareketi durumlari white vertical
	else if( (checker[i1][j1] == 'W' && checker[i2][j2] == ' ' ) && ( abs(i2-i1) >= 2 && j2-j1 == 0 ) )
	{
		 
		int c = 0 , x, y, i, g, s;
		
		if(i2 > i1){
			g=i2;
			s=i1;
		}
		else if(i1 > i2){
			g=i1;
			s=i2;
		}
			
		for(i = s+1 ; i<g ; i++ )
		{
			 
			if(checker[i][j1] == 'b' || checker[i][j1] == 'B')
			{
				x = i;
				y = j1;
				c++;
			} 
		}
		if(c == 0)
		{
		 
			checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			return 1;
		}	
			
		else if(c >= 2){
			return 0;
		}
		else if(c == 1)
		{
		 
			checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			checker[x][y] = ' ';
			bpiece--;
			return 2;
			
		}
 		
	}
	// dama hareketi durumlari white horizantal
	else if( (checker[i1][j1] == 'W' && checker[i2][j2] == ' ' ) && ( abs(j2-j1) >= 2 && i2-i1 == 0 ) )
	{
		int c = 0 , x, y, i, g, s;
		
		if(j2 > j1){
			g=j2;
			s=j1;
		}
		else if(j1 > j2){
			g=j1;
			s=j2;
		}
			
		for(i = s+1 ; i<g ; i++ )
		{
			if(checker[i1][i] == 'b' || checker[i1][i] == 'B')
			{
				x = i1;
				y = i;
				c++;
			} 
		}
		if(c == 0)
		{
			checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			return 1;
		}	
			
		else if(c >= 2)	
			return 0;
		else if(c == 1)
		{
			
			checker[i2][j2] = 'W';
			checker[i1][j1] = ' ';
			checker[x][y] = ' ';
			bpiece--;
			return 2;
			
		}
 		
	}
	// dama hareketi durumlari black vertical
	else if( (checker[i1][j1] == 'B' && checker[i2][j2] == ' ' ) && ( abs(i2-i1) >= 2 && j2-j1 == 0 ) )
	{
		int c = 0 , x, y, i, g, s;
		
		if(i2 > i1){
			g=i2;
			s=i1;
		}
		else if(i1 > i2){
			g=i1;
			s=i2;
		}
			
		for(i = s+1 ; i<g ; i++ )
		{
		
			if(checker[i][j1] == 'w' || checker[i][j1] == 'W')
			{
				x = i;
				y = j1;
				c++;
			} 
		}
		if(c == 0)
		{
			checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			return 1;
		}	
		else if(c >= 2)	
			return 0;
		else if(c == 1)
		{
			checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			checker[x][y] = ' ';
			bpiece--;
			return 2;
		}
	}
	// dama hareketi durumlari black horizantal
	else if( (checker[i1][j1] == 'B' && checker[i2][j2] == ' ' ) && ( abs(j2-j1) >= 2 && i2-i1 == 0 ) )
	{
		int c = 0 , x, y, i, g, s;
		
		if(j2 > j1){
			g=j2;
			s=j1;
		}
		else if(j1 > j2){
			g=j1;
			s=j2;
		}
			
		for(i = s+1 ; i<g ; i++ )
		{
			if(checker[i1][i] == 'w' || checker[i1][i] == 'W')
			{
				x = i1;
				y = i;
				c++;
			} 
		}
		if(c == 0)
		{
			checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			return 1;
		}	
		else if(c >= 2)	
			return 0;
		else if(c == 1)
		{
			checker[i2][j2] = 'B';
			checker[i1][j1] = ' ';
			checker[x][y] = ' ';
			bpiece--;
			return 2;
		}
	}
	
	else{
		return false;
	}
			 
} // end function

int * peaceCounter(char checker[MAX_ROW][MAX_COL], int * checkerData) // bu fonksiyon eski oyuna devam etmek icin gerekli bilgileri toparliyor
{
	int  Data[3], w=0, b=0, p=1;
	for (int i = 0; i < MAX_ROW; i++){
			for (int j = 0 ; j < MAX_COL ; j++)  
			{ 
				if(checker[i][j] == 'w' || checker[i][j] == 'W')
					w++;
				else if(checker[i][j] == 'b' || checker[i][j] == 'B')
					b++;
			}
		}
		p = roleChecker();
		if( p == 'w')
			p = 1;
		else if( p == 'b')
			p = 0;
		else
			printf("File read error, role can not detect.");

		Data[0] = w;
		Data[1] = b;
		Data[2] = p;
		
		for(int i = 0; i < 3; i++){
			*(checkerData + i) = Data[i];
		}	 
 		return checkerData;
} // end function			

int gameFunction(char checker[MAX_ROW][MAX_COL], int wpiece, int bpiece, int playe)
{
	char command[5]  ;
	bool test;
	int i, a;
	int  white = 1 , black = 0 ;
 	if(playe == 0){
		black = 1;
		white = 0;
	}
	else  {
		white = 1;
		black = 0;
	}
 
	do {
		if( white == 1 )
		{
			playe=1;
			do{
				printf("\nIt is White's Turn please choose peace to move (a2a3) (type 0 to exit) : ");
				fflush(stdin);// bu fonksiyon input buffer i resetlemek icin kullaniliyor
				gets( command );
				if( command[0] == '0' )
				{
					roleSetter('w');
					return 0;	
				}
				 
				else if(  ( a = commandChecker(checker, command, playe, wpiece, bpiece) ) == 1  )
					{
						displayboard(checker);
						black=1;
						white=0;
						commandLogFunc(playe, command);
						
					}
				else if( a == 2)
					{
						displayboard(checker);
						black=0;
						white=1;
						commandLogFunc(playe, command);
					}
					
				else if(a == 0)
					printf("The move chosen is invalid\n");
			} while ( bpiece != 0 && white == 1 );
		}
		else if ( black == 1 )
		{
			playe = 0;
			do{
				printf("\nIt is Black's Turn please choose peace to move (b2b3) (type 0 to exit) : ");
				fflush(stdin);// bu fonksiyon input buffer i resetlemek icin kullaniliyor
				gets( command );
				if( command[0] == '0' )
				{
					roleSetter('b');
					return 0;
				}
					
								
				else if( ( a = commandChecker(checker, command, playe, wpiece, bpiece) ) == 1)
					{
						displayboard(checker);
						white=1;
						black=0;
						commandLogFunc(playe, command);
					}
				else if( a == 2)
					{
						displayboard(checker);
						black=1;
						white=0;
						commandLogFunc(playe, command);
					}
					
				else if( a == 0)
					printf("The move chosen is invalid\n");
			
			}while (wpiece != 0 && black == 1  );
		}
	 
	} while( wpiece != 0 && bpiece !=0 );	
	if(wpiece == 0 )
	 	gameScore(0,1);
	else if ( bpiece == 0)
		gameScore(1,0);
	
} // end function

int main()
{
 	int choice;
 	char checker[MAX_ROW][MAX_COL];
	char temp;
	int x1, x2 ;
	char y1, y2 ;
	int cnt, checkerData[3], playe ;
	int wpiece = 16, bpiece = 16;
 	
	while(choice != 3){

		printf("\nWelcome to Checkers Game - Have Fun\n\n"
				"MENU\n"
				"1. New Game\n"
				"2. Continue Game\n"
				"3. Enough For Today!\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				clrscr();
				cnt = 0;
				progressSelector(checker, cnt); // burada oyun tahtasi duzeni hazirlaniyor, yeni oyun veya eskiden devam icin
				fileCreator(checker);
				gameFunction(checker, wpiece, bpiece, 1);
				clrscr();
			break;
				
			case 2:
				clrscr();
				cnt = 1;
				fileUploader(checker); // dosyadan okuyup checker[][] ogesini olusturacak
				progressSelector(checker, cnt); // burada oyun kaldigi yerden devam edecegi sekilde ayarlaniyor
				// ----------------------------------------- bu kisimda oyunda kalan tas sayisi siradaki oyuncu vs gibi veriler getiriliyor
				int checkerData[3] ;
				peaceCounter(checker, checkerData );
				for(int i=0;i<3;i++){
					checkerData[i] = *(checkerData + i);
				}
				wpiece = checkerData[0];
				bpiece = checkerData[1];
				playe = checkerData[2];
				// -----------------------------------------
				gameFunction(checker, wpiece, bpiece, playe);
				// dosyadaki kayitlar getirilecek ve oyunun oradan devam etmesi saglanacak
				clrscr();
			break;
			
 			case 3:
				clrscr();
				//cikis icin gerekli islemler yapilacak
 				printf("\n\n\n\n**************Good By.!**************\n\n\n\n");
				printf("Program is closing, push any keyboard button to exit..\n");
				break;
			
			default:
				clrscr();
				printf("\n******Wrong choice, try again**********\n");
		}
 	}
 	return 0;
} // end main function
