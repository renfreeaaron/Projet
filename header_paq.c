#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include "elf32_header.h"




int check_elf(Elf32_Ehdr * data)
{
  
  if (data->e_ident[EI_MAG0] != ELFMAG0 ||
      data->e_ident[EI_MAG1] != ELFMAG1 ||
      data->e_ident[EI_MAG2] != ELFMAG2 ||
      data->e_ident[EI_MAG3] != ELFMAG3)
    return (-1);

  return (0);
}

int check_arch(Elf32_Ehdr * data)
{
  if (data->e_ident[EI_CLASS] != 1)
    return (-1);

  return (0);
}

void print_info(Elf32_Ehdr * data)
{
	puts("En-tête ELF:");
	printf("  Magique:   ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", data->e_ident[i]);
	puts(" ");
	if (data->e_ident[4] == 1)
		puts("  Classe:                            ELF32");
	else if (data->e_ident[4] == 2)
		puts("  Classe:                            ELF64");
	else if (data->e_ident[4] == 0)
		puts("  Classe:                          Aucun");
	if (data->e_ident[5] == 1)
		puts("  Données:                          complément à 2, système à octets de poids faible d'abord (little endian)");
	else if (data->e_ident[5] == 2)
		puts("  Données:                          système à octets de poids fort d'abord (big endian)");
	else if (data->e_ident[5] == 0)
		puts("  Données:                          Aucun");	
	if (data->e_ident[6] == 1)
		puts("  Version:                           1 (current)");
	else if (data->e_ident[6] == 0)
		puts("  Version:                           0 (aucun)");
	printf("  OS/ABI:                            ");
	switch(data->e_ident[7]) {
   		case 0  :
      			puts("UNIX - System V"); break;
   		case 1  :
      			puts("HP-UX"); break;
   		case 2  :
      			puts("NetBSD"); break;
   		case 3  :
      			puts("Linux"); break;
   		case 6  :
      			puts("Sun Solaris"); break;
   		case 7  :
      			puts("IBM AIX"); break;
   		case 8  :
      			puts("SGI IRIX"); break;
   		case 9  :
      			puts("FreeBSD"); break;
   		case 10  :
      			puts("Compaq TRU64"); break;
   		case 11  :
      			puts("Novell Modesto"); break;
   		case 12  :
      			puts("OpenBSD"); break;
   		case 13  :
      			puts("OpenVMS"); break;
   		case 14  :
      			puts("NonStop Kernel"); break;
   		case 15  :
      			puts("AROS"); break;
   		case 16  :
      			puts("Fenix OS"); break;
   		case 17  :
      			puts("CloudABI"); break;
   		case 64  :
      			puts("ARM EABI"); break;
   		case 83  :
      			puts("Sortix"); break;
   		case 97  :
      			puts("ARM"); break;
   		case 255  :
      			puts("Standalone"); break;
   		default  :
      			printf("Autre avec le code %x\n", data->e_ident[6]); break;
	}
	printf("  Version ABI:                       %d\n", data->e_ident[8]);
	printf("  Type:                              ");
	switch(data->e_type) {
   		case 1  :
      			puts("Repositionable"); break;
   		case 2  :
      			puts("Executable"); break;
  		case 3  :
      			puts("Objet partagé"); break;
  		case 4  :
      			puts("Fichier Core"); break;
		case 0  :
      			puts("Aucun"); break;
   		default  :
      			printf("Erreur"); break;
	}
	printf("  Machine:                           ");
	switch(data->e_machine) {
   		case 0  :
      			puts("Aucune"); break;
   		case 2  :
      			puts("SPARC"); break;
   		case 3  :
      			puts("Intel 80386"); break;
   		case 4  :
      			puts("Motorola 68000"); break;
   		case 7  :
      			puts("Intel i860"); break;
   		case 8  :
      			puts("MIPS I"); break;
   		case 19  :
      			puts("Intel i960"); break;
   		case 20  :
      			puts("PowerPC"); break;
   		case 40  :
      			puts("ARM"); break;
   		case 62  :
      			puts("x64"); break;
   		default  :
      			printf("Autre avec le code %d\n", data->e_machine); break;
	}
	printf("  Version:                           0x%x\n", data->e_version);
	printf("  Adresse du point d'entrée:         0x%0x\n", data->e_entry);
	if (data->e_phoff == 0)
		printf("  Début des en-têtes de programme:   0 (octets dans le fichier)\n");
	else
		printf("  Début des en-têtes de programme:         %d (octets dans le fichier)\n", data->e_phoff);
	if (data->e_shoff == 0)
		printf("  Début des en-têtes de section:    0 (octets dans le fichier)\n");
	else
		printf("  Début des en-têtes de section:         %d (octets dans le fichier)\n", data->e_shoff);
  	printf("  Fanions:                           0x%0x\n", data->e_flags);
  	printf("  Taille de cet en-tête:             %d (bytes)\n", data->e_ehsize);
  	printf("  Taille de l'en-tête du programme:  %d (bytes)\n", data->e_phentsize);
  	printf("  Nombre d'en-tête du programme:     %d\n", data->e_phnum);
  	printf("  Taille des en-têtes de section:    %d (bytes)\n", data->e_shentsize);
  	printf("  Nombre d'en-têtes de section:      %d\n", data->e_shnum);
  	printf("  Table d'indexes des chaînes d'en-tête de section: %d\n", data->e_shstrndx);

}

