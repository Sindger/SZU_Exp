#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<semaphore.h>
#include"fsys.h"

ctrl_info* cinfo;

int traverse(int pdir, char *path, int bias){
	int i, step=0, depth=0, tmp;
	char *each_fname[32];
	each_fname[depth++] = strtok(path, "/");
	
	if(path[0] == '/'){
		pdir = 0;
		path++;
	}
	else if(path[0]=='.' && path[1]=='/')
		path+=2;

	while(each_fname[depth++] = strtok(NULL, "/"));
	depth--;

	while (step < depth){
		for(i=0; i<cinfo->fcbs[pdir].items; i++){
			tmp = cinfo->fcbs[pdir].addr[i];
			if(!strcmp(each_fname[step], cinfo->fcbs[tmp].fname)){
				if(	(step+bias<depth && cinfo->fcbs[tmp].ftype) ||(step+1>=depth && !bias)){
					pdir = tmp;
					break;
				}
				else
					return -1;
			}
			else if(step + bias >= depth)	
				return pdir;
			else if(i+1 >= cinfo->fcbs[pdir].items)
				return -1;
		}
		step++;
	}
	return pdir;
}

char* process_path(char *path){
	if(!path)	
		return NULL;
	int i = strlen(path)-1;
	if(path[i] == '/')	
		path[i] = '\0';
	return path;
}

char* getname(char* path){	
	char *tmp;
	if(!process_path(path))
		return NULL;

	tmp = strrchr(path, '/');	
	if(tmp == NULL)
		tmp = path;
	else
		tmp++;
	return tmp;
}

int nextfcb(){
	int tmp;
	for(cinfo->row=0; cinfo->row < cinfo->fatfcb_rows; cinfo->row++){
		tmp = (int)cinfo->fatfcb[cinfo->row];	
		if(tmp == -1)	
			continue;
		for(cinfo->col=0; cinfo->col < fcbfatrow; cinfo->col++)
			if((cinfo->fatfcb[cinfo->row] & (1 << cinfo->col)) == 0)
				return 1;
	}
	return -1;
}

int nextfile(){
	int tmp;
	for(cinfo->row=0; cinfo->row < cinfo->fatfile_rows; cinfo->row++){
		tmp = (int)cinfo->fatfile[cinfo->row];
		if(tmp == -1)	
			continue;
		for(cinfo->col=0; cinfo->col < fcbfatrow; cinfo->col++)
			if((cinfo->fatfile[cinfo->row] & (1 << cinfo->col)) == 0)
				return 1;
	}
	return -1;
}

void ls(int pdir){
	int i, tmp, items = cinfo->fcbs[pdir].items;
	for(i=0; i<items; i++){
		tmp = cinfo->fcbs[pdir].addr[i];
		printf("%s\t", cinfo->fcbs[tmp].fname);
		if(i % 4 == 3)
			printf("\n");
	}
	printf("\n");
}

void tostr(int idx, char* path){
	int i=2;
	path[0] = 'f';path[1] = 's';
	while(idx){
		path[i++] = 0x30 + idx%10;
		idx /= 10;
	}
	path[i] = '\0';
}

void bsread(int idx){
	int bnum = cinfo->fcbs[idx].fitems;
	int i,j, bidx;
	for(i=0; i<bnum; i++){	
		bidx = cinfo->fcbs[idx].faddr[i];
		printf("%s", cinfo->files[bidx].data);
	}
	printf("\n");
}

int newblock(int idx){
	int flg = nextfile();
	int fidx = cinfo->fcbs[idx].fitems;
	if(flg == -1){
		printf("No more free block\n");
		return -1;
	}
	cinfo->fcbs[idx].fitems++;
	cinfo->fatfile[cinfo->row] += (1<<cinfo->col);
	cinfo->fcbs[idx].faddr[fidx] = cinfo->row * fcbfatrow + cinfo->col;
	cinfo->block_num++;
	return 0;
}

void append(int idx, char* content){
	int next_fblock = cinfo->fcbs[idx].fitems;
	int len, fidx, flg, wptr, i;
	int rptr=0;
	if(next_fblock<1 || next_fblock>fcb_faddr_size){
		printf("block index error\n");
		return;
	}
	
	fidx = cinfo->fcbs[next_fblock].faddr[next_fblock-1];
	wptr = cinfo->files[fidx].items;

	if(next_fblock < fcb_faddr_size || wptr < fstr_size){
		len = strlen(content);
		
		while (1){
			for(i=wptr; i<fstr_size && content[rptr]; i++)
				cinfo->files[fidx].data[i] = content[rptr++];
			cinfo->files[fidx].items += i - wptr;
			wptr = 0;
			next_fblock++;
			if(!content[rptr])
				break;
			else if(next_fblock < fcb_faddr_size){
				flg = newblock(idx);
				if(flg == -1)
					break;
				else
					fidx = cinfo->fcbs[idx].faddr[next_fblock];
			}
			else{
				printf("Warning: the last block of this file is full\n");
				break;
			}
		}
	}
	else
		printf("insufficient space\n");
}

void release_block(int idx){
	int len = cinfo->fcbs[idx].fitems;
	int i,fidx;
	
	for(i=0;i<len;i++){
		fidx = cinfo->fcbs[idx].faddr[i];
		cinfo->files[fidx].items = 0;
		cinfo->row = fidx/fcbfatrow;
		cinfo->col = fidx%fcbfatrow;
		cinfo->fatfile[cinfo->row] ^= (1<<cinfo->col);
	}
	cinfo->block_num -= len;
	cinfo->fcbs[idx].fitems = 0;
}

void release_fcb(int idx){
	cinfo->row = idx/fcbfatrow;
	cinfo->col = idx%fcbfatrow;
	cinfo->fatfcb[cinfo->row] ^= (1<<cinfo->col);
	cinfo->fcb_num--;
}

char* change_dir(int idx, char* pwd){
	int len;
	if(idx > 0){
		pwd = change_dir(cinfo->fcbs[idx].pdir, pwd);
		if(pwd){
			len = strlen(pwd);
			pwd[len] = '/';
			strcat(pwd, cinfo->fcbs[idx].fname);
		}
	}
	else if(!idx){
		pwd[0] = '\0';
	}
	else{
		printf("fcb index error\n");
		pwd = NULL;
	}
	return pwd;
}

void main(){
	int i, idx, shmid;
	int pfcb=0, free_fcb, tmpfcb;
	char *command, input[buffer_size], pwd[buffer_size], content[buffer_size];
	char *cache[8];
	sem_t *cinfo_s, *tmpsemt, *fsems[MAXfsg];

    shmid = shmget((key_t)627, space_size*MB, 0);
	if(shmid<0){
		shmid = shmget((key_t)627, space_size*MB, 0666|IPC_CREAT);	
		cinfo = (ctrl_info*)shmat(shmid, 0, 0);
		init_ctrl_info(cinfo);	

		cinfo_s = sem_open(cinfoname, O_CREAT | O_RDWR, 0666, 1);
		sem_init(cinfo_s, 2, 1);
	}
	else{
		cinfo = (ctrl_info*)shmat(shmid, 0, 0);
		if((void*)cinfo < (void*)0){
			printf("memory error\n");
			exit(-1);
		}

		cinfo_s = sem_open(cinfoname, 0);
	}
	strcpy(pwd, "/");

	while (1){
		printf("%s@%s:%s$", user, pcname, pwd);
		if (fgets(input, buffer_size, stdin) == NULL)
			exit(0);
		else if(input[0] == '\n')
			continue;
		
		cache[0] = strchr(input, '\n');
		if(cache[0]) *cache[0] = '\0';
		
		command = strtok(input, " ");

		if(!strcmp(command, "exit"))
			break;
		else if(!strcmp(command, "ls")){
			cache[0] = strtok(NULL, " ");
			if(!cache[0])	
				tmpfcb = pfcb;
			else{
				sem_wait(cinfo_s);
				tmpfcb = traverse(pfcb, cache[0], 0);
				sem_post(cinfo_s);
			}
			
			if(tmpfcb >= 0){
				sem_wait(cinfo_s);
				ls(tmpfcb);
				sem_post(cinfo_s);
			}
			else
				printf("Path Error!\n");
		}
		else if(!strcmp(command, "mkdir") || !strcmp(command, "open")){
			cache[0] = strtok(NULL, " ");
			cache[1] = getname(cache[0]);
			if(!cache[1]){	
				printf("failed to %s\n", command);
				continue;
			}

			sem_wait(cinfo_s);
			tmpfcb = traverse(pfcb, cache[0], 1);
			if(tmpfcb == -1)
				printf("failed to %s\n", command);
			else if(cinfo->fcbs[tmpfcb].items >= MAX_sub)
				printf("sub dir/block numbers exceeds\n");
			else if(nextfcb() == -1)	
				printf("No more space for fcb\n");
			else{
				free_fcb = cinfo->row * fcbfatrow + cinfo->col;

				cinfo->fatfcb[cinfo->row] += (1<<cinfo->col);
				init_fcb(cinfo, cache[1], command[0]=='m'?1:0, tmpfcb,free_fcb);
				add_child(cinfo, tmpfcb, free_fcb);
				cinfo->fcb_num++;
				if(command[0] == 'o')
					newblock(free_fcb);
			}
			sem_post(cinfo_s);
		}
		else if(!strcmp(command, "rmdir") || !strcmp(command, "rm")){
			i = command[2]=='d'?1:0;
			cache[0] = strtok(NULL, " ");
			cache[1] = getname(cache[0]);
			if(!cache[1]){
				printf("failed to %s\n", command);
				continue;
			}
			sem_wait(cinfo_s);
			tmpfcb = traverse(pfcb, cache[0], 0);
			if(tmpfcb == -1)
				printf("Path Error!\n");
			else if(cinfo->fcbs[tmpfcb].items && i)
				printf("Not Empty Dir\n");
			else if((i && cinfo->fcbs[tmpfcb].ftype) || (!i && !cinfo->fcbs[tmpfcb].ftype)){
				i = cinfo->fcbs[tmpfcb].pdir;
				for(idx=0; idx<cinfo->fcbs[i].items; idx++)
					if(tmpfcb == cinfo->fcbs[i].addr[idx]){
						if(cinfo->fcbs[i].items--)
							cinfo->fcbs[i].addr[idx] = cinfo->fcbs[i].addr[cinfo->fcbs[i].items];	
						break;
					}
				release_fcb(tmpfcb);
				if(command[2] == '\0')
					release_block(tmpfcb);
			}
			sem_post(cinfo_s);
		}
		else if(!strcmp(command, "rename")){
			cache[0] = strtok(NULL, " ");
			process_path(cache[0]);
			cache[1] = strrchr(cache[0], '/');
			
			cache[2] = strtok(NULL, " ");	
			process_path(cache[2]);
			cache[3] = strrchr(cache[2], '/');	

			if(!cache[1] && !cache[3]){
				cache[3] = cache[2];
				cache[1] = cache[0];
			}
			else if((cache[1]||cache[3]) && (cache[1]-cache[0]!=cache[3]-cache[2])){
				printf("Path Error!\n");
				continue;
			}
			else if(cache[1] && cache[3]){
				cache[3]++;
				cache[1]++;
				cache[4] = cache[0];
				cache[5] = cache[2];
				while (cache[4] != cache[1]){	
					if(*cache[4] != *cache[5]){	
						printf("Path Error!\n");
						break;
					}
					cache[4]++;
					cache[5]++;
				}
				if(*cache[4] != *cache[5]){	
					printf("Path Error!\n");
					continue;
				}
			}

			sem_wait(cinfo_s);
			tmpfcb = traverse(pfcb, cache[0], 0);
			if(tmpfcb == -1)
				printf("Path Error!\n");
			else
				strcpy(cinfo->fcbs[tmpfcb].fname, cache[3]);
			
			sem_post(cinfo_s);
		}
		else if(!strcmp(command, "read") || !strcmp(command, "edit")){
			cache[0] = strtok(NULL, " ");
			cache[1] = getname(cache[0]);
			if(!cache[1]){
				printf("failed to %s\n", command);
				continue;
			}
			
			tmpfcb = traverse(pfcb, cache[0], 0);

			if(tmpfcb == -1)
				printf("Path Error!\n");
			else if(cinfo->fcbs[tmpfcb].ftype)
				printf("it's a dir\n");
			else if(command[0] == 'r'){
				tostr(tmpfcb, cache[2]);
				tmpsemt = sem_open(cache[2], 0, 0);
				if(!tmpsemt){
					bsread(tmpfcb);
					getchar();
				}
			}
			else if(command[0] == 'e'){	
				sem_wait(cinfo_s);
				tostr(tmpfcb, cache[2]);

				tmpsemt = sem_open(cache[2], 0, 0);	
				if(!tmpsemt){	
					tmpsemt = sem_open(cache[2], O_CREAT | O_RDWR, 0666, 1);
					sem_init(tmpsemt, 2, 1);
				}
				
				sem_wait(tmpsemt);
				fgets(content, buffer_size, stdin);	
				cache[3] = strchr(content, '\n');
				if(cache[3]) *cache[3] = '\0';
				append(tmpfcb, content);
				sem_post(tmpsemt);

				sem_getvalue(tmpsemt, &i);
				if(i > 0){	
					sem_close(tmpsemt);
					sem_unlink(cache[2]);
				}
				sem_post(cinfo_s);
			}
		}
		else if(!strcmp(command, "cinfo")){
			sem_wait(cinfo_s);
			showcinfo(cinfo);
			sem_post(cinfo_s);
		}
		else if(!strcmp(command, "cd")){
			cache[0] = strtok(NULL, " ");
			if(!cache[0]){
				printf("Empty path\n");
				continue;
			}
			i = strlen(cache[0]);
			
			sem_wait(cinfo_s);
			if(i==1 && cache[0][0] == '/')
				tmpfcb = 0;
			else
				tmpfcb = traverse(pfcb, cache[0], 0);
			sem_post(cinfo_s);

			if(tmpfcb >= 0){
				pfcb = tmpfcb;
				sem_wait(cinfo_s);
				if(!tmpfcb)
					strcpy(pwd, "/");
				else
					change_dir(tmpfcb, pwd);
				sem_post(cinfo_s);
			}
			else
				printf("Path Error!\n");
		}
		else if(!strcmp(command, "fcb")){
			cache[0] = strtok(NULL, " ");
			if(!cache[0]){
				printf("Empty path\n");
				continue;
			}
			tmpfcb = atoi(cache[0]);
			
			sem_wait(cinfo_s);
			if(cache[0][0] != '0' && !tmpfcb)
				tmpfcb = traverse(pfcb, cache[0], 0);
			cinfo->row = tmpfcb/fcbfatrow;
			cinfo->col = tmpfcb%fcbfatrow;

			if(
				i>=0 && i<cinfo->maxfcb && tmpfcb>=0 &&
				(cinfo->fatfcb[cinfo->row] & (1<<cinfo->col))
			)
				showpfcb(cinfo, tmpfcb);
			else
				printf("Index error\n");
			sem_post(cinfo_s);
		}
		else
			printf("Command error\n");
	}
	printf("Bye!\n");
	
	sem_getvalue(cinfo_s, &i);
	if(i>0){
		sem_close(cinfo_s);
		sem_unlink(cinfoname);
	}
	shmctl(shmid, IPC_RMID, NULL);

	return;
}