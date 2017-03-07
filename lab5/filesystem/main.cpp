#include "myfile.h"
#define CMD_NUM 5

// input
char cmds[CMD_NUM][10] = {"ls", "touch", "mkdir", "cd", "exit"};
char arg[32];
char cmd[32];
int op = 1;
int _exit = 0;

int main() {
    usage();
    init();
    while (1) {
        op = 100;
        printf("\033[1;34m%s\033[0m$ ", pwd);
        scanf("%s", cmd);
        strcpy(arg, "unname");
        if (strcmp(cmd, "touch") == 0 || strcmp(cmd, "mkdir") == 0 || \
            strcmp(cmd, "cd") == 0) {
            scanf("%s", arg);
        }
        for (int i = 0; i < CMD_NUM; i++) {
            if (strcmp(cmds[i], cmd) == 0) {
                op = i;
                break;
            }
        }
        switch (op) {
        case 0:
            //printf("ls\n");
            show();
            break;
        case 1:
           // printf("touch %s\n", arg);
            mkfile(cur_inum, arg, _FILE);
            break;
        case 2:
            //printf("mkdir\n");
            mkfile(cur_inum, arg, _DIR);
            break;
        case 3:
            //printf("cd\n");
            close_dir(cur_inum);
            if (open_dir(arg) == 0) {

            }
            break;
        case 4:
            //printf("exit\n");

            close_dir(cur_inum);
            _exit = 1;
            break;
        default:
            printf("file_num = %d", cur_fnum);
            printf("No command \'%s\' found\n", cmd);
            break;
        }
        if (_exit == 1) break;
    }
    end();
}

int init() {
    //  init filesystem
    fs = fopen("fs", "r+");
    //  fseek(fs, BlockSeg, SEEK_SET);
    strcpy(pwd, "/");
    cur_inum = 0;

    if (open_dir(cur_inum) == -1) {
        init_root();
    }
    return 0;
}

int init_root() {
    // init superBlock
    memset(sb.inode_map, 0, sizeof(sb.inode_map));
    memset(sb.block_map, 0, sizeof(sb.block_map));
    sb.inode_map[0] = 1;
    sb.inode_used = 1;
    sb.block_map[0] = 1;
    sb.block_used = 1;
    Inode inode;
    inode.size = sizeof(Dir);
    inode.block_num = 1;
    inode.blocks[0] = 0;
    inode.type = _DIR;
    strcpy(pwd, "/");
    // write . ..
    Dir dir;
    dir.inum = 0;
    strcpy(dir.name, ".");
    fseek(fs, BlockSeg, SEEK_SET);
    fwrite(&dir, sizeof(Dir), 1, fs);
    // write new_inode
    fseek(fs, InodeSeg, SEEK_SET);
    fwrite(&inode, sizeof(Inode), 1, fs);
    cur_inode = inode;
    cur_inum = 0;
    cur_files[cur_fnum++] = dir;
    return 0;
}

int end() {
    fclose(fs);
}

// inum : parent's inum
int mkfile(int pa_inum, char *name, int type) {
    int new_inum = get_inum();
    if (type == _DIR) {
        init_dir(pa_inum, new_inum);
    } else {
        init_file(new_inum);
    }
    Dir dir;
    strcpy(dir.name, name);
    dir.inum = new_inum;
    cur_files[cur_fnum++] = dir;
}

int init_dir(int pa_inum, int new_inum) {
    // init inode
    Inode inode;
    int bnum;
    memset(inode.blocks, 0, sizeof(inode.blocks));
    inode.type = _DIR;
    inode.block_num = 1;
    bnum = get_bnum();
    inode.blocks[0] = bnum;
    inode.size = 2 * sizeof(Dir);
    // write . ..
    Dir dir[2];
    strcpy(dir[0].name, ".");
    dir[0].inum = new_inum;
    strcpy(dir[1].name, "..");
    dir[1].inum = pa_inum;
    fseek(fs, BlockSeg + (BlockSize * bnum), SEEK_SET);
    fwrite(dir, sizeof(Dir), 2, fs);
    // write new_inode
    fseek(fs, InodeSeg + (sizeof(Inode) * new_inum), SEEK_SET);
    fwrite(&inode, sizeof(Inode), 1, fs);
    return 0;
}

int init_file(int inum) {
    Inode inode;
    memset(inode.blocks, 0, sizeof(inode.blocks));
    inode.block_num = 0;
    inode.size = 0;
    inode.type = _FILE;
    fseek(fs, InodeSeg + (sizeof(Inode) * inum), SEEK_SET);
    fwrite(&inode, sizeof(Inode), 1, fs);
    return 0;
}

int show() {
    int j = 0;
    for (int i = 0; i < cur_fnum; i++) {
        if (j++ == 4) {
            j = 0;
            printf("\n");
        }
        if (get_itype(cur_files[i].inum) == _DIR) {
            // printf("%s\n", cur_files[i].name);
            printf("\033[1;34m%-20s\033[0m", cur_files[i].name);
        } else {
            printf("%-20s", cur_files[i].name);
        }
    }
    printf("\n");
    return 0;
}

int get_itype(int inum) {
    Inode inode;
    fseek(fs, InodeSeg + (sizeof(Inode) * inum), SEEK_SET);
    fread(&inode, sizeof(Inode), 1, fs);
    return inode.type;
}

int get_inum() {
    // check if used up
    if (sb.inode_used >= InodeNum) {
        printf("inode is used up\n");
        return -1;
    }
    // get an inode num
    for (int i = 0; i < InodeNum; i++) {
        if (sb.inode_map[i] == 0) {
            sb.inode_map[i] |= 1;
            sb.inode_used++;
            return i;
        }
    }
}

int get_bnum() {
    // check if used up
    if (sb.block_used >= BlockNum) {
        printf("block is used up\n");
        return -1;
    }
    // get an block num
    for (int i = 0; i < BlockNum; i++) {
        if (sb.block_map[i] == 0) {
            sb.block_map[i] |= 1;
            sb.block_used++;
            return i;
        }
    }
}

int open_dir(int inum) {
    // read
    fseek(fs, InodeSeg + (inum  * sizeof(Inode)), SEEK_SET);
    fread(&cur_inode, sizeof(Inode), 1, fs);
    // null
    if (cur_inode.block_num == 0) {
        return -1;
    }
    // is a file
    if (cur_inode.type == _FILE) {
        printf("This is a file, not a dir\n");
        return -2;
    }
    //
    fseek(fs, InodeSeg + (sizeof(Inode) * inum), SEEK_SET);
    fread(&cur_inode, sizeof(Inode), 1, fs);
    cur_inum = inum;
    cur_fnum = cur_inode.size / sizeof(Dir);
    int bnum = cur_inode.blocks[0];
    fseek(fs, BlockSeg + (BlockSize * bnum), SEEK_SET);
    fread(cur_files, sizeof(Dir), cur_fnum, fs);
    return 0;
}

int change_dir(char *name) {
    // current
    if (strcmp(name, ".") == 0) {
        return 0;
    }
    // father
    if (strcmp(name, "..") == 0) {
        // change pwd[128]
        int i = 0;
        int pos = 0;
        char c;
        while (c = pwd[i++]) {
            if (c == '/') {
                pos = i - 1;
            }
        }
        pwd[pos] = '\0';
    } else {
        // add
        strcat(pwd, "/");
        strcat(pwd, name);
    }
    return 0;
}

int close_dir(int inum) {
    // save cur_files
    fseek(fs, BlockSeg + (BlockSize * cur_inode.blocks[0]), SEEK_SET);
    fwrite(cur_files, sizeof(Dir), cur_fnum, fs);
    // save inode
    fseek(fs, InodeSeg + (sizeof(Inode) * inum), SEEK_SET);
    cur_inode.size = cur_fnum * sizeof(Dir);
    fwrite(&cur_inode, sizeof(Inode), 1, fs);
    return 0;
}

char* get_namei(int inum) {
    /*Inode inode;
    FILE *fp = fopen("fs", "r");
    fseek(fs, InodeSeg + (inum * sizeof(Inode)), 0);
    fread(&inode, sizeof(Inode), 1, fp);
    fclose(fp);
    return inode.name;
    */
}

void usage() {
    // red
    printf("\n\033[32;31mjust use it as linux shell\033[0m\n\n");
    // blue
    //printf("\n\033[0;34mjust use it as linux shell\033[0m\n");
    // printf("\033[显示方式;前景色;背景色m输出字符串\033[0m/n");
}
