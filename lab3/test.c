#include <stdio.h>
#include <string.h>
#define SIZE 4096

int main()
{
    char src[SIZE];
    char dest[SIZE];
	
	strcpy(src, "The string to char_dev");
	printf("\nthe write is \"%s\"\n", src);
	FILE *fp0 = fopen("/dev/qihao0", "r+");
	if (fp0 == NULL) {
		printf("open file error\n");
		return 0;
	}
	fwrite(src, sizeof(src), 1, fp0);
	// fp0 到文件头
	fseek(fp0, 0, SEEK_SET);
	fread(dest, sizeof(dest), 1, fp0);
	printf("\nthe read is \"%s\"\n", dest);
    fclose(fp0);
    return 0;    

}
