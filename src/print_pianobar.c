#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "i3status.h"

static char *path;
static bool first = false;

void print_pianobar(yajl_gen json_gen, char *buffer) {

	char *env, *outwalk;
	FILE* nowplaying;

	if (buffer == NULL)
		return;

	if (path == NULL) {
		env = getenv("HOME");
		if (env == NULL) {
			fputs("$HOME not defined, please set $HOME", stderr);
			path = "";
			return;
		}
		asprintf(&path, PIANOBAR_NOWPLAYING, env);
	}

	if (!first && path && strlen(path)) {
		FILE* tmp = fopen(path, "w");
		if (tmp) {
			fputs("-", tmp);
			fclose(tmp);
			first = true;
		}
	}

	if ((nowplaying = fopen(path, "r"))) {
		fgets(buffer, 4096, nowplaying);
		fclose(nowplaying);

		outwalk = buffer + strlen(buffer) -1;
		OUTPUT_FULL_TEXT(buffer);
	}
}
