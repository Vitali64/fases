/*	head - print file until a certain line
 *	Copyright (C) 2022 Ferass EL HAFIDI
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUsage() {
	printf("Ferass' Base System.\n\n"
		"Usage: head [FILE] [-n NUMBER]\n\n"
		"Print FILE's contents until line NUMBER.\n\n"
		"\t-n NUMBER\tPrint first NUMBER line(s).\n"
	);
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		char args;
		int usedargs = 0;
		int arg_lines;    /* Number of lines to print */
		for (int i = 1; argv[i]; i++) {
			if (argv[i][usedargs + 1] == 'n' && argv[i + 1]) {
				args = 'n'; 
				arg_lines = strtol(argv[i + 1], NULL, 0);
				usedargs++;
			}
			if (argv[i][usedargs + 1] == 'h') {
				printUsage();
				exit(0);
			}
		}
		FILE *file;
		char s[512];
		int i = 0;
		file=fopen(argv[1], "r");
		if (file == NULL) {
			printf("head: %s: No such file or directory\n",
				argv[1]);
			exit(1);
		}
		while (i != arg_lines && (fgets(s, 512, file)) != NULL) {
			s[strcspn(s, "\n")] = 0; /* Remove trailing newline */
			puts(s); 
			i++;
		}
		fclose(file);
	}
	else if (argc == 1) {
		/* Output to stdout based on user input */
		while (1) {
			char input[80];
			fgets(input, 80, stdin);
			printf("%s", input);
		}
	}
	return 0;
}
