#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PGDEF 22

static int pglen = PGDEF;

void printfile(FILE *f);

int main(int argc, char *argv[]) {
	int n = 0;
	FILE *f = NULL;
	while (argc > 1) {
		argc--; argv++;
		if (*argv[0] == '-') {
			pglen = atoi(&argv[0][1]);
			if (pglen <= 0)
				pglen = PGDEF;
			continue;
		}
		n++;
		f = fopen(argv[0], "r");
		if (f == NULL) {
			fprintf(stderr, "p: can't open %s\n", argv[0]);
			continue;
		}
		printfile(f);
		fclose(f);
	}
	if (n == 0)
		printfile(stdin);

	return 0;
}

void printfile(FILE *f) {
	size_t len = 0;
	size_t cap = 32 * pglen;
	char *buf = malloc(cap+1);
	if (buf == NULL) {
		fputs("p: can't allocate memory\n", stderr);
		exit(1);
	}

	int i;
	char c;
	char *p = buf;
	size_t plen = 0;
	for (;;) {
		for (i = 1; i <= pglen; i++) {
			if (fgets(p, (cap-len)+1, f) == NULL) {
				free(buf);
				return;
			}
			plen = strlen(p);
			len += plen;
			if (len >= cap) {
				cap = (cap+len) * 2;
				buf = realloc(buf, cap+1);
				p = buf + (len-plen);
				if (p[plen-1] != '\n')
					i--;
			}
			if (i == pglen && p[plen-1] == '\n')
				p[plen-1] = '\0';
			fputs(p, stdout);
			p += plen;
		}
		fflush(stdout);
		c = getchar();
		if (c == EOF || c == 'q')
			exit(0);
		p = buf;
		len = 0;
	}
}
