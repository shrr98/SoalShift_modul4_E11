#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

#define KEY 17
char domain[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0\0";
char codomain[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0\0";
const char *dirpath = "/home/trash/shift4";

void generateCodomain(int key){
    char potongan[key+1];
    strncpy(potongan, domain, key);
    potongan[key] = 0;
    sprintf(codomain, "%s%s", domain+key, potongan);
}

void enkrip(char *nama){
    int index = 0;
    int idxDiDomain;
    while(nama[index]!='\0'){
        if (nama[index]!='/'){
            idxDiDomain = strchr(domain, nama[index]) - domain;
            nama[index] = codomain[idxDiDomain];
        }
        index++;
    }
}

void dekrip(char *nama){
    int index = 0;
    int idxDiCodomain;
    while(nama[index]!='\0'){
        if(nama[index]!='/'){
            idxDiCodomain = strchr(codomain, nama[index]) - codomain;
            nama[index] = domain[idxDiCodomain];
        }
        index++;
    }
}

static int asf_getAttribute(const char *path, struct stat *stbuf){
    if(strcmp(path, "..")==0 || strcmp(path, ".")==0) return 0;
    int res;
    char fpath[1024];
    char encPath[512];
    sprintf(encPath, "%s", path);
    enkrip(encPath);
    sprintf(fpath, "%s%s", dirpath, encPath);
    res = lstat(fpath, stbuf);
    if (res==-1)
        return -errno;

    return 0;
}

static int asf_readDir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi){
if(strcmp(path, "..")==0 || strcmp(path, ".")==0) return 0;
char fpath[1000];
char encPath[512];

sprintf(encPath, "%s", path);

enkrip(encPath);
if(strcmp(path,"/") == 0)
{
    path=dirpath;
    sprintf(fpath,"%s",path);
}
else sprintf(fpath, "%s%s",dirpath,encPath);
int res = 0;
DIR *dp;
struct dirent *de;

(void) offset;
(void) fi;
dp = opendir(fpath);
if(dp == NULL)
    return -errno;

while ((de = readdir(dp)) != NULL){
    struct stat st;
    memset(&st, 0, sizeof(st));
    st.st_ino = de->d_ino;
    st.st_mode = de->d_type << 12;
    if(strcmp(de->d_name, "..")==0 || strcmp(de->d_name, ".")==0)
        continue;
    dekrip(de->d_name);

    if(filler(buf, de->d_name, &st, 0))
        break;
}
closedir(dp);
return 0;              
}

static void asf_mkdir(const char* path, mode_t mode){
{
    char encPath[512];
    char fpath[1024];
    mode = 0750;
    sprintf(encPath, "%s", path);
    enkrip(encPath);
    sprintf(fpath, "%s%s", dirpath, encPath);
	int res;

	res = mkdir(fpath, mode);
	if (res == -1)
		return -errno;
// 1111101000 =
// 9876543210 = 
	return 0;
}
}

static int asf_read(const char *path, char *buff, size_t size, off_t offset,
                struct fuse_file_info *fi)
{
    if(strcmp(path, "..")==0 || strcmp(path, ".")==0) return 0;
    char fpath[1000];
    char encPath[512];

    sprintf(encPath, "%s", path);

    enkrip(encPath);
    if(strcmp(path, "/")==0){
        path = dirpath;
        sprintf(fpath, "%s", path);
    }    
    else sprintf(fpath, "%s%s", dirpath, encPath);
    int result = 0;
    int fd = 0;
    (void) fi;
    fd = open(fpath, O_RDONLY);
    result = pread(fd, buff, size, offset);
    if (result == -1)
        result = -errno;
    close(fd);
    return result;
}



static struct fuse_operations asf_oper = {
	.getattr	= asf_getAttribute,
	.readdir	= asf_readDir,
	.read		= asf_read,
    .mkdir      = asf_mkdir,
    // .opendir    = openDir,
    
};


int main(int argc, char** argv){
    generateCodomain(17);
    // char ss[] = "n,nsbZ]wio";
    // char s[] = "INI_FOLDER";
    // enkrip(s);
    // dekrip(ss);
    // printf("%s\n%s\n%s\n%s\n", domain, codomain, s, ss);
    umask(0);
	return fuse_main(argc, argv, &asf_oper, NULL);
}