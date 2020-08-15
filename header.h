//
// Created by ssoraka on 15.08.2020.
//

#ifndef NEURO_KOKOHEN_HEADER_H
#define NEURO_KOKOHEN_HEADER_H


#include <string.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef int t_bool;

#define LETTER_IN_STRING 15
#define STRING_COUNT 2
#define ANSWER_COUNT 30
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 5
#define STRING_LEN (LETTER_IN_STRING * LETTER_WIDTH)


// Параметры НС
// Число входов,
#define N_INPUT (LETTER_WIDTH * LETTER_HEIGHT)
// высота карты
#define MAP_H 30
// ширина карты
#define MAP_W (MAP_H)
// радиус обучения
#define MAP_RAD (MAP_W / 3)
// Число нейронов в скрытом слое
#define N_HIDDEN (MAP_W * MAP_H)
// Скорость обучения
#define ALPHA 0.5
// Скорость обучения
#define MAX_DIST_ON_MAP 5.0
// Количество эпох обучения
#define LAST_ERA 7000

char g_letters[ANSWER_COUNT * LETTER_HEIGHT * LETTER_WIDTH];
double input[LETTER_IN_STRING * STRING_COUNT][N_INPUT];
char g_ru_letter[ANSWER_COUNT][5];

//структура слоя
typedef struct		s_layer
{
	//массив выходов нейронов
	double			f[N_HIDDEN];
	//количество нейронов в этом слое
	int				i_n;
	// количество нейронов в предыдущем слое
	int				j_n;
	// номер нейрона победителя
	int				i_winner;
	// массив связей размером i_count * j_count
	double			w_ij[N_HIDDEN][N_INPUT];
}					t_layer;

typedef struct		s_map
{
	//массив минимальных дистанций
	double			dist[N_HIDDEN];
	//массив соответствующих букв на карте
	char			letter[N_HIDDEN][4];
	t_bool			is_winner[N_HIDDEN];
}					t_map;

void    read_letters_from_file(char *name);
void	letter_to_x0();
void	print_arr_double(double *d, int size);
void	print_letter(int n);
char	*letter_by_num(int i);

#endif //NEURO_KOKOHEN_HEADER_H
