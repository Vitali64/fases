/*	cat - concatenate a file to stdout 
 *	Copyright (C) 2022 Ferass EL HAFIDI
 *	Copyright (C) 2022 Leah Rowe
 *
 *	Redistribution and use in source and binary forms, with or without 
 *	modification, are permitted provided that the following conditions are met:
 *	
 *	    1. Redistributions of source code must retain the above copyright notice, 
 *	       this list of conditions and the following disclaimer.
 *	    2. Redistributions in binary form must reproduce the above copyright 
 *	       notice, this list of conditions and the following disclaimer in the 
 *	       documentation and/or other materials provided with the distribution.
 *	    3. Neither the name of the copyright holder nor the names of its 
 *	       contributors may be used to endorse or promote products derived from 
 *	       this software without specific prior written permission.
 *	
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 *	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *	POSSIBILITY OF SUCH DAMAGE.
 */

#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "version.h"

#ifndef COMPILETIME
#define COMPILETIME
#endif

int  cat(int flides, int unbuffered);
void printUsage();

int main(int argc, char *const argv[]) {
	int file, argument, i = 1, unbuffered;

	while ((argument = getopt(argc, argv, "u")) != -1) {
		if (argument == '?') {
			printUsage();
			return 1;
		}
		else if (argument == 'u')
			unbuffered = 1;
	}

	
	if (argc < 2) {
		cat(STDIN_FILENO, unbuffered);
	}

	for (i = 1; i != argc; i++) {
		if (strcmp(argv[i], "-u")) {
			if (strcmp(argv[i], "-")) file = open(argv[i], O_RDONLY);
			else file = STDIN_FILENO;
			if (file == -1) return errno; /* Something went wrong */
			cat(file, unbuffered);
			close(file);
		}
	}
	return 0;
}

int cat(int fildes, int unbuffered) {
	char s[4096];
	FILE *filstr;
	size_t length;
	if (unbuffered) while ((length = read(fildes, s, 4096)) > 0)
		write(STDOUT_FILENO, s, length);
	else {
		filstr = fdopen(fildes, "r");
		while ((length = fread(s, 4096, 1, filstr)) > 0)
			fwrite(s, length, 1, stdout);
	}
	if (errno) return errno;
	return 0;
}

void printUsage() {
	printf("Ferass' Base System. (%s)\n\n"
	"Usage: cat [file]\n\n"
	"Concatenate <file> to standard output.\n"
	"When no file is specified or file is '-', read standard input\n\n"
	"\t-u\tPrint unbuffered\n", COMPILETIME);
}
