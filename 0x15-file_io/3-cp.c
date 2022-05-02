#include "main.h"

/**
 * exit98_check - checks if file_from exists and can be read
 * @x: int to check
 * @file: file that does not exist or cannot be read
 *
 * Return: 0 if successful, exits early with code 98 otherwise
 */

int exit98_check(int x, char *file)
{
	if (x == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
		exit(98);
	}

	return (0);
}

/**
 * close_all - closes all file descriptors
 * @fd1: file directory 1
 * @fd2: file directory 2
 *
 * Return: 0 if successful
 */

int close_all(int fd1, int fd2)
{
	int close_check1 = close(fd1);
	int close_check2 = close(fd2);

	if (close_check1 == -1 || close_check2 == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %i\n",
			close_check1 == -1 ? fd1 : fd2);
		exit(100);
	}

	return (0);
}

/**
 * copy_file - copies the contents of a file to another file
 * @file_from: file to copy from
 * @file_to: file to copy to
 *
 * Return: 1 on success, -1 on failure
 */

int copy_file(char *file_from, char *file_to)
{
	int fd_from, fd_to;
	ssize_t read_actual, write_actual;
	char *buffer[1024];

	fd_from = open(file_from, O_RDONLY);
	fd_to = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);

	exit98_check(fd_from, file_from);

	if (fd_to == -1)
		return (-1);

	while ((read_actual = read(fd_from, buffer, 1024)) > 0)
	{
		if (read_actual == -1)
			exit98_check(read_actual, file_from);

		write_actual = write(fd_to, buffer, read_actual);
		if (write_actual == -1)
		{
			close_all(fd_from, fd_to);
			return (-1);
		}
	}

	exit98_check(read_actual, file_from);

	close_all(fd_from, fd_to);
	return (1);
}

/**
 * main - entry point function in C
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 if success
 */

int main(int argc, char *argv[])
{
	int copy_status;
	char *file_from, *file_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	file_from = argv[1];
	file_to = argv[2];

	if (file_from == NULL)
		exit98_check(-1, file_from);

	copy_status = copy_file(file_from, file_to);

	if (copy_status == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		exit(99);
	}

	return (0);
}
