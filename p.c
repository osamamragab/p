#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PGDEF 22

static int pglen = PGDEF;

void printfile(FILE *f);

int main(int argc, char *argv[]) {
	FILE *f = 0;
	while (argc > 1) {
		argc--; argv++;
		if (*argv[0] == '-') {
			pglen = atoi(&argv[0][1]);
			if (pglen <= 0)
				pglen = PGDEF;
			continue;
		}
		f = fopen(argv[0], "r");
		if (f == 0){
			fprintf(stderr, "p: can't open %s\n", argv[0]);
			continue;
		}
		printfile(f);
		fclose(f);
	}
	if (f == 0)
		printfile(stdin);

	return 0;
}

void printfile(FILE *f) {
	size_t len = 0;
	size_t cap = 128;
	char *buf = malloc(cap);
	if (buf == 0) {
		fputs("p: can't allocate memory\n", stderr);
		exit(1);
	}

	int i;
	char c;
	char *p = buf;
	for (;;) {
		for (i = 1; i <= pglen; i++) {
			if (fgets(p, cap-len, f) == 0) {
				free(buf);
				return;
			}
			len += strlen(p);
			if (len >= cap || buf[len-1] != '\n') {
				cap *= 2;
				buf = realloc(buf, cap);
				p = buf;
			}
			if (i == pglen && buf[len-1] == '\n')
				buf[len-1] = '\0';
			fputs(p, stdout);
			p = buf + len;
		}
		fflush(stdout);
		c = getchar();
		if (c == EOF || c == 'q')
			exit(0);
		p = buf;
		len = 0;
	}
}
