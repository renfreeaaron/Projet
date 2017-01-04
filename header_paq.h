#ifndef __HEADER_PAQ_H__
#define __HEADER_PAQ_H__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>




int check_elf(Elf32_Ehdr * data);

int check_arch(Elf32_Ehdr * data);

void print_info(Elf32_Ehdr * data);


#endif
