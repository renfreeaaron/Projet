#include <stdio.h>
//#include "header_paq.h"
//Autres fichers .h

int main(int argc, char *argv[])
{
	
	char option;
	char menu[] = "Option 1 : AAAAAAAAAAAAAAAAAAAAAAAAAAAAA \n Option 2 : BBBBBBBBBBBBBBBBBBBBBBBBBB";
	char err_option[] = "Le caractere entre n'est pas valide";
	while (1)
	{
		
		puts(menu);		
		scanf("%c",&option);
		switch (option)
		{
			case 'a' :
				break;
			case 'b' :
				break;
			case 'c' :
				break;
			default :
				puts(err_option); continue;
		}
		break;
	}


	return (0);
}


