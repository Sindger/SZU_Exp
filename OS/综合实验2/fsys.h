#define File_Control_Block 336	
#define FileSize 4096
#define fstr_size 4092
#define FCB_faddr_size 13	
#define fname_size 8

#define space_size 100
#define fat_space 1
#define FCB_space 4	
#define block_space 95	
#define MB (1024 * 1024)

#define MAXfsg 8
#define buffer_size 256
#define MAX_sub 64	
#define FCBfatrow 32

const char* cinfoname = "cinfo";	
const char* user = "root";

typedef struct FCB{
	char fname[fname_size];	
	int idx;	
	int ftype;
	int pdir;	
	
	int fitems;
	int faddr[FCB_faddr_size];

	int items;
	int addr[MAX_sub];
}FCB;


typedef struct File{	
	int items;
	char data[fstr_size];	
}file;


typedef struct CTRL_info{
	int maxFCB, maxblock;
	int FCB_num, block_num;	
	unsigned int fatFCB_rows, fatfile_rows;
	int row, col;

	unsigned int fatFCB[FCB_space * MB / (File_Control_Block * FCBfatrow) + 1];
	unsigned int fatfile[block_space * MB / (FileSize * FCBfatrow) + 1];
	FCB FCBs[FCB_space * MB / File_Control_Block];
	file files[block_space * MB / FileSize];
}ctrl_info;

void init_FCB(ctrl_info* cinfo, char *fname, int ftype, int pdir, int idx){
	strcpy(cinfo->FCBs[idx].fname, fname);
	cinfo->FCBs[idx].ftype = ftype;
	cinfo->FCBs[idx].pdir = pdir;
	cinfo->FCBs[idx].idx = idx;	
	cinfo->FCBs[idx].items = 0;
	cinfo->FCBs[idx].fitems = 0;	
}

void init_ctrl_info(ctrl_info* cinfo){
	int i;
	cinfo->maxFCB = FCB_space * MB / sizeof(FCB);
	cinfo->maxblock = block_space * MB / sizeof(file);	
	cinfo->fatFCB_rows = cinfo->maxFCB / FCBfatrow + 1;	
	cinfo->fatfile_rows = cinfo->maxblock / FCBfatrow +1;

	cinfo->FCB_num = 1;	
	cinfo->fatFCB[0] = 1;	
	for(i=1; i<cinfo->fatFCB_rows; i++)
		cinfo->fatFCB[i] = 0;	

	cinfo->block_num = 0;	
	for(i=0;i<cinfo->fatfile_rows; i++)
		cinfo->fatfile[i] = 0;
	
	init_FCB(cinfo, "/", 1, 0, 0);	
}

void showcinfo(ctrl_info* cinfo){
	printf(">>>maxFCB: %d, maxblock: %d\n", cinfo->maxFCB, cinfo->maxblock);
	printf(">>>FCB num: %d, block_num: %d\n", cinfo->FCB_num, cinfo->block_num);
	printf("\n");
}

void showpFCB(ctrl_info* cinfo, int idx){
	int i,tmp,len;
	tmp = cinfo->FCBs[idx].ftype;	
	printf(">>>FCB index: %d\n", idx);
	printf(">>>type: %s\n", tmp?"dir":"file");
	if(tmp){
		len = cinfo->FCBs[idx].items;
		printf(">>>num of sub dir: %d\n", len);
		for(i=0; i<cinfo->FCBs[idx].items;i++)
			printf("sub dir index: %d\n", cinfo->FCBs[idx].addr[i]);
	}
	else{
		len = cinfo->FCBs[idx].fitems;
		printf(">>>num of block: %d\n", len);
		for(i=0; i<cinfo->FCBs[idx].fitems;i++){
			tmp = cinfo->FCBs[idx].faddr[i];
			printf("block index:%d, str size: %d\n", tmp, cinfo->files[tmp].items);
		}
	}
	printf("\n");
}

void add_child(ctrl_info* cinfo, int pdir, int child_idx){
	int items = cinfo->FCBs[pdir].items++;	
	cinfo->FCBs[pdir].addr[items] = child_idx;	
}