/* program hello */
/* Adapted from mpihello.f by drs */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#include "px_log.h"
#include "px_debug.h"

int print_files(char *dir_path);

int main(int argc, char **argv)
{
	int rank;
	char index_file[100],data_file[100];
	char *ret_ptr;
	int ret;

	if(argc < 3){
		printf("usage format <path> <size-in_MB>\n");
		exit(1);
	}

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//read the command line arguments
	char *dir_loc = argv[1];
	ulong size = strtol(argv[2],&ret_ptr,10);
	ulong node_id = rank;

	sprintf(index_file,"%s/%s%lu",dir_loc,"mmap.file.meta",node_id);
	sprintf(data_file,"%s/%s%lu",dir_loc,"mmap.file.data",node_id);
	if(!rank){
		log_info("shm file-names : %s , %s\n",index_file, data_file);
		log_info("shm format size : %lu MB\n", size);
	}
	size = size * 1024 * 1024; // converting to bytes
	ret = create_shm(index_file, data_file, size);
	check(ret == 0,"error creating shm region");
	if(!rank){
		log_info("content in the formatted directory");
		ret=print_files(dir_loc);	
		check(ret == 0,"error creating shm region");
	}
	MPI_Finalize();
	return 0;

error:
	exit(1);

}

int print_files(char *dir_path){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (dir_path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			printf ("%s\n", ent->d_name);
		}
		closedir (dir);
		return 0;
	} else {
		/* could not open directory */
		log_err("error opening directory");
		return -1;
	}
	return 0; // make compiler happy
}
