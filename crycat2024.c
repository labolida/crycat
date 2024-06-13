#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help() {
		printf("\n Crycat 2024 - cryptography - Linux 64-bits " ) ;
		printf("\n This program is released under GNU GPL v3 license - https://www.gnu.org/licenses" ) ;
		printf("\n Opensource distributed by the author leonardo.labolida.com ");
		printf("\n Missing parameters. Expected: " ) ;
		printf("\n		 param[1]: Filename of a shared table. This is going to be part of the encription key." ) ;
		printf("\n		 param[2]: A secret character secuence. this is going to be the key to access the shared table." ) ;
		printf("\n		 param[3]: Filename to be readed and processed - source input." ) ;
		printf("\n		 param[4]: Filename to be wrote and processed - target output." ) ;
		printf("\n  Example:   " ) ;
		printf("\n 	  crycat ourSharedTable mySecretKeyPass theMessage.txt  encrypted " ) ;
		printf("\n 	  crycat ourSharedTable mySecretKeyPass encrypted  theMessage.txt " ) ;
		printf("\n\n" ) ;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

char * loadFile( char * filename ) {
		FILE * fp ;
		fp = fopen( filename  , "r");
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char * buff= malloc(size + 1);
		fread( buff, size , 1 , fp );
		fclose(fp);
		return buff ;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void crycat( int argc , char ** argv ) {
	char * fileNameTable	= argv[1];			// shared-table filename
	char * key		= argv[2];			// password (keys:table)
	char * filenameIn	= argv[3];			// input  filename
	char * filenameOut	= argv[4];			// output filename
	FILE * fp1;						// FilePoint in
	FILE * fp2;						// FilePoint out
	int s=0;
	int c;

	char * table = loadFile( fileNameTable );	//printf("%s" , table );

	fp1 = fopen( filenameIn  , "r");
	fp2 = fopen( filenameOut , "w");
	while( (c = fgetc(fp1))!=EOF ) {
		char k = key[s % strlen(key)];
		long index = k + s ;                             //printf(" :%ld " , index  ); // printf(" :%ld %i" , index , s );
		char p = table[ index % strlen(table) ];
		p =  p ^ k ;                                     //printf(" ^%i" , p );
		fputc( c ^ p  , fp2 );
		s++;
	}
	fclose(fp1);
	fclose(fp2);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main( int argc , char ** argv ) {
	if (argc<5) {
		help();
	}else{
		crycat(argc,argv);
	}
	return 0;
}
