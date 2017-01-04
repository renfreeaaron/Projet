#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include "header_paq.h"

int main(int argc, char *argv[])
{
  	Elf32_Ehdr *data;
	char err_args [] = "USAGE: executable <binary_file>";
	char err_open [] = "Ouverture du fichier impossible";
	char err_rec [] = "Recuperation des informations du fichier impossible";
	char err_mem [] = "Chargement du fichier en memoire impossible";
	char err_elf [] = "Pas format propre";
	char err_arch [] = "Mauvais architecture";
	//struct stat { 
        //       dev_t     st_dev;     /* ID of device containing file */ 
        //       ino_t     st_ino;     /* inode number */ 
        //       mode_t    st_mode;    /* protection */ 
        //       nlink_t   st_nlink;   /* number of hard links */ 
        //       uid_t     st_uid;     /* user ID of owner */ 
        //       gid_t     st_gid;     /* group ID of owner */ 
        //       dev_t     st_rdev;    /* device ID (if special file) */ 
        //       off_t     st_size;    /* total size, in bytes */ 
        //       blksize_t st_blksize; /* blocksize for file system I/O */ 
        //       blkcnt_t  st_blocks;  /* number of 512B blocks allocated */ 
        //       time_t    st_atime;   /* time of last access */ 
        //       time_t    st_mtime;   /* time of last modification */ 
        //       time_t    st_ctime;   /* time of last status change */ 
        //   };	
	struct stat file_info;
	int file_descriptor;


	if (argc != 2)
	{
		puts(err_args);
	}
	else
	{
		//int open(const char *path, int oflags);
		//Returns the file descriptor for the new file. 
		//The file descriptor returned is the smallest integer > 0 that is still available. 
		//If a negative value is returned, then there was an error opening the file.
		if ((file_descriptor = open(argv[1], O_RDONLY)) <= 0)
		{
			puts(err_open);
		}
		else
		{
			//int fstat(int fd, struct stat *buf);
			//printf("%d\n",fstat(file_descriptor, &file_info)); //-> 0
			if (fstat(file_descriptor, &file_info) == -1)
			{
				puts(err_rec);
			}
			//void *mmap(void *addr, size_t len, int protection, int flags, int fildes, off_t off);
			else if ((data = mmap(0, file_info.st_size, PROT_READ, MAP_PRIVATE, file_descriptor, 0)) == MAP_FAILED)
			{
				puts(err_mem);
			}
			else
			{							
				if (check_elf(data))
				{
					puts(err_elf);
				}
				else if (check_arch(data))
				{
					puts(err_arch);
				}
				else
				{
					print_info(data);
				}
				munmap(data, file_info.st_size);
			}
			close(file_descriptor);
		}
	}
	return (0);
}


