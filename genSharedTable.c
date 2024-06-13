#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void main( int argc , char ** argv ) { // GENERATE SHARED TABLE
	char * fileName=argv[1];
	FILE * fp;
	fp = fopen(fileName,"w");
	srand(time(NULL));
	for (int i=0;i<1000;i++){
		int r = rand();
		char c = (r % 255) +1 ;
		fputc(c,fp);
	}
	fclose(fp);
}
// gcc genSharedTable.c -o genSharedTable
// ./genSharedTable shared-table-01