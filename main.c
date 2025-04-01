#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
		int fd;
		fd = open("./read_write.txt", O_RDONLY);
        char *str;
		str = get_next_line(fd);
		printf("%s",str);
		// str = get_next_line(fd);
		// printf("%s",str);
		// str = get_next_line(fd);
		// printf("%s",str);
		// str = get_next_line(fd);
		// printf("%s",str);
		// str = get_next_line(fd);
		// printf("%s",str);
		// str = get_next_line(fd);
		// printf("%s",str);
		close(fd);
		free(str);
}