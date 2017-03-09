#ifndef __MYFILE_H_
#define __MYFILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// size
#define InodeNum 1024
#define BlockNum 1024 * 80
#define BlockSize 1024
#define MaxPerInode 1024
#define MaxPerDir (BlockSize / sizeof(Dir))
// begin address, segment
#define SuperSeg 0
#define InodeSeg sizeof(SuperBlock)
#define BlockSeg (InodeSeg + InodeNum * sizeof(Inode))
// 1: mkdir
// 0: touch
#define _DIR 5
#define _FILE 6

// struct
typedef struct _SuperBlock SuperBlock;
typedef struct _Inode Inode;
typedef struct _Dir Dir;

struct _SuperBlock {
    bool inode_map[InodeNum];
    bool block_map[BlockNum];
    int inode_used;
    int block_used;
};

struct _Inode {
    int block_num;
    int blocks[MaxPerInode];
    int size;
    int type;
};

struct _Dir {
    char name[24];
    int inum;
};

// fs, sb
FILE *fs;
SuperBlock sb;
char BUF[BlockSize];
// cur info
Inode cur_inode;
int cur_inum;
char pwd[128];
int cur_fnum;
Dir cur_files[MaxPerDir];


// init, end
int init();
int init_root();
int end();
// create dir , file
int mkfile(int pa_inum, char *name, int type);
int same_name(char *name, int type);
int get_itype(int inum);
int get_inum();
int get_bnum();
int init_dir(int pa_inum, int new_inum);
int init_file(int inum);
// open, close dir
int open_dir(int inum);
int iget_name(char *name);
int change_dir(char *name);
int close_dir(int inum);
// open, write, read file
int read_file(int inum);
int write_file(int inum);
// rm file, dir
int rm_file(int inum);
int rm_dir(int inum);
int rm_cur(int inum);
int free_inum(int inum);
int free_bnum(int bnum);
// show
int show();
int show_map();
void usage();

#endif
