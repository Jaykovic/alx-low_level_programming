#include "main.h"
/**
 * read_textfile - function to read  and print a file
 * @filename: file
 * @letters: number of letters of the file
 * Return: numbers of letters or zero it fails
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd = 0;
	char *buffer;
	int  byt_read;
	int byt_writ;

	if (filename == NULL)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buffer = malloc(sizeof(char) * letters);
	if (buffer == NULL)
		return (0);
	byt_read = read(fd, buffer, letters);
	if (byt_read == -1)
	{
		free(buffer);
		return (0);
	}
	byt_writ = write(STDOUT_FILENO, buffer, (ssize_t)byt_read);
	if (byt_writ == -1)
	{
		free(buffer);
		return (0);
	}
	close(fd);
	return (byt_read);
}
