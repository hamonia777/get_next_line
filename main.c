#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
void Myputs(char *szBuffer)
{
		while(*szBuffer)
		{
			write(1, szBuffer, 1);
			++szBuffer;
		}
}

int main(void)
{
		int fd;
		fd = open("./read_write.txt", O_CREAT, 00700);
        char *str;
		str = get_next_line(fd);
		printf("%s",str);
		str = get_next_line(fd);
        printf("%s",str);

}