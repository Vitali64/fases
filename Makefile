#
#	Copyright (C) 2022 Ferass EL HAFIDI
#	Copyright (C) 2022 Leah Rowe
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

include ./config.mk

# Commands
# ========

all: clean box

prepbox:
	mkdir -p box_tmp
	for f in ${SRC}; do sed "s/^int main(/int $$(echo "$$f")_main(/" < "core/"$$f".c" | sed "s/printUsage()/$$(echo "$$f")_printUsage()/g" > "box_tmp/"$$f"_box.c"; done

box: box.o
	$(CC) $(CFLAGS) box_tmp/*.c box.o -o box 

clean:
	rm -f box *.o
	rm -Rf box_tmp

install: box
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f box $(DESTDIR)$(PREFIX)/bin

# Utilities
# =========

box.o: prepbox
	$(CC) $(CFLAGS) $(NOLINKER) box.c -o box.o
