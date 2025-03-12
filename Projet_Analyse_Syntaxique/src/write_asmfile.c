#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#

int main(int argc, char const *argv[])
{
	FILE* file = fopen("_anonymous.asm","w");
	if(!file){
		fprintf(stderr, "Erreur à l'ouverture du ficher");
	}
	fclose(file);
	return 0;
}
