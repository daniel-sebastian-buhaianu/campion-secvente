#include <stdio.h>
#include <stdlib.h>

#define MIN_N 1
#define MAX_N 100000

int main()
{
	FILE *fin = fopen("secvente.in", "r");

	if (!fin) {
		printf("Eroare fisier secvente.in\n");
		return 1;
	}

	int n, m;

	fscanf(fin, "%d %d", &n, &m);

	if (n < MIN_N || n > MAX_N) {
		printf("Eroare valoare N\n");
		return 2;
	}

	if (m < 0 || m > n) {
		printf("Eroare valoare M\n");
		return 3;
	}
	
	char c;
	int i;
	unsigned *b, nr;

	for (nr = 0, i = 1; i <= n; i++) {
		fscanf(fin, " %c", &c);

		if (c < '0' || c > '1') {
			printf("Eroare valoare B[%d] = '%c'\n", i, c);
			return 4;
		}

		if (c == '1') {
			if (nr == 0) {
				b = (unsigned*)malloc((nr+1)*sizeof(unsigned));

				if (!b) {
					printf("Eroare alocare memorie *b\n");
					return 5;
				}

				b[nr++] = i;
			} else {
				b = (unsigned*)realloc(b, (nr+1)*sizeof(unsigned));

				if (!b) {
					printf("Eroare realocare memorie *b\n");
					return 6;
				}

				b[nr++] = i;
			}
		}
	}

	unsigned char exista, *uz;
	int x, y, st, dr, mij;
	unsigned *a;

	a = (unsigned*)calloc(n+1, sizeof(unsigned));

	uz = (unsigned char*)calloc(n+1, sizeof(unsigned char));

	for (exista = i = 1; i <= m && exista; i++) {
		fscanf(fin, "%d %d", &x, &y);

		if (x < 0 || x > n) {
			printf("Eroare valoare x\n");
			return 7;
		}

		if (y < 0 || y > n) {
			printf("Eroare valoare y\n");
			return 8;
		}

		if (y > x) {
			st = -1, dr = nr;

			while (dr-st > 1) {
				mij = st + (dr-st)/2;

				if (b[mij] >= y) {
					dr = mij;
				} else {
					if (b[mij] >= x) {
						st = dr = mij;
					} else {
						st = mij;
					}
				}
			}

			if (st == dr) {
				exista = 0;
			}
		}

		a[x] = y, uz[y] = 1;
	}

	fclose(fin);

	FILE *fout = fopen("secvente.out", "w");

	if (!exista) {
		fprintf(fout, "IMPOSIBIL");
	} else {
		unsigned urmpoz = 1;

		for (i = 0; i < nr; i++) {
			for (x = 1; x <= b[i]; x++) {
				if (!uz[x]) {
					while (a[urmpoz] && urmpoz <= n) {
						urmpoz++;
					}	
					
					if (urmpoz <= n) {
						a[urmpoz] = x;
						uz[x] = 1;
					}	
				}
			}
		}

		for (i = 1; i <= n; i++) {
			fprintf(fout, "%u ", a[i]);
		}
	}	

	fclose(fout);

	free(b);	
	free(a);
	free(uz);

	return 0;
}
// scor 10
