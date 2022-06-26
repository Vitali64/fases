/*	cat - concatenate a file to stdout 
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *	Copyright (C) 2022 Leah Rowe
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int getopt(int argc, char *const argv[], const char *optstring);

void printUsage() {
	printf("Ferass' Base System.\n\n"
	"Usage: cat [FILE]\n\n"
	"Concatenate FILE to stdout\n\n"
	"\t-u\tPrint unbuffered\n");
}

int main(int argc, char *const argv[]) {
	int file, argument, i = 1;
	char s[4096], input[4096];

	while ((argument = getopt(argc, argv, "uh")) != -1) {
		if (argument == 'h') {
			printUsage();
			return 0;
		}
		else if (argument == 'u')
			setvbuf(stdout, NULL, _IONBF, 0);
		else
			setvbuf(stdout, NULL, _IOFBF, 0);
	}
	
	if (argc < 2) {
		while (1) {
			read(STDIN_FILENO, input, 4096);
			printf("%s", input);
		}
	}

	for (i = 1; i != argc; i++) {
		if (argv[i][0] != '-') {
			file = open(argv[i], O_RDONLY);
			if (file == -1) return errno; /* Something went wrong */
			while (read(file, s, 4096) > 0)
				printf("%s", s);
			close(file);
		}
	}
	return 0;
}
