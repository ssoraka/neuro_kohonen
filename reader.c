//
// Created by ssoraka on 06.08.2020.
//

#include "header.h"
char g_ru_letter[ANSWER_COUNT][5] = {
"А","Б","В","Г",
"Д","Е","Ж","З",
"И","К","Л","М",
"Н","О","П","Р",
"С","Т","У","Ф",
"Х","Ц","Ч","Ш",
"Ъ","Ы","Ь","Э","Ю","Я"
};

char *letter_by_num(int i) {
	return (g_ru_letter[i]);
}

void	print_letter_name(){
	char *str;
	int i;

	str = "АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЪЫЬЭЮЯ";
	i = 0;
	while (i < ANSWER_COUNT) {
		printf("  %.2s  ", str + i * 2);
		i++;
	}
	printf("\n");
}

void	print_arr_double(double *d, int size) {
	int i;

	i = 0;
	while (i < size) {
		printf("%.4lf ", d[i]);
		i++;
	}
	printf("\n");
}

void	letter_to_x0() {
	int x;
	int y;
	int i;
	int j;
	int n;
	double *ptr;

	ptr = input;
	n = 0;
	while (n < ANSWER_COUNT) {
		x = (n % LETTER_IN_STRING) * LETTER_WIDTH;
		y = (n / LETTER_IN_STRING) * STRING_LEN * LETTER_HEIGHT;
		i = 0;
		while (i < LETTER_HEIGHT) {
			j = 0;
			while (j < LETTER_WIDTH) {
				if (g_letters[x + y + i * STRING_LEN + j] == '0')
					*ptr = 0.0;
				else
					*ptr = 1.0;
				ptr++;
				j++;
			}
			i++;
		}
		n++;
	}
}

void	print_letter(int n) {
	int i;
	int x0;
	int y0;

	if (n >= ANSWER_COUNT || n < 0)
		return ;
	x0 = n % LETTER_IN_STRING;
	y0 = n / LETTER_IN_STRING;
	i = 0;
	while (i < LETTER_HEIGHT) {
		write(0, g_letters + y0 * STRING_LEN * LETTER_HEIGHT + x0 * LETTER_WIDTH + i * STRING_LEN, LETTER_WIDTH);
		write(0, "\n", 1);
		i++;
	}
}

void    read_letters_from_file(char *name)
{
	int fd;

	fd = open(name, O_RDWR);
	if (fd == -1) {
		printf("can't open file %s\n", name);
		exit(0);
	}
	int red;
	char *str = g_letters;

	while ((red = read(fd,  (void *)str, 1))) {
		if (*str != '\n')
			str++;
	}
	close(fd);
}
