#include <stdbool.h>
#include "header.h"

void init_layer(t_layer *layer) {
	int i;
	int j;

	// Инициализация связей между входом НС и скрытым слоем случайными значениями
	i = 0;
	while (i < layer->i_n) {
		j = 0;
		while (j < layer->j_n) {
			layer->w_ij[i][j] = ((double)rand()) / RAND_MAX;
			j++;
		}
		i++;
	}
}

void calculate_layer(double *input, t_layer *layer) {
	int i;
	int j;
	int nearest;
	double dist;

	nearest = 0;
	i = 0;
	while (i < layer->i_n) {
		dist = 0.0;
		j = 0;
		while (j < layer->j_n) {
			dist += ((layer->w_ij)[i][j] -  input[j]) * ((layer->w_ij)[i][j] -  input[j]);
			j++;
		}
		(layer->f)[i] = sqrt(dist);
		if ((layer->f)[i] < (layer->f)[nearest])
			nearest = i;
		i++;
	}
	layer->i_winner = nearest;
}

double neighbourhood(int winner, int current, int iter) {
	int x_c;
	int y_c;
	int x;
	int y;
	double r;
	double h;
	double b;

	x_c = winner % MAP_W;
	y_c = winner / MAP_W;
	x = current % MAP_W;
	y = current / MAP_W;
	r = sqrt((x_c - x) * (x_c - x) + (y_c - y) * (y_c - y));
	//b = (LAST_ERA - iter) / 1000.0;
	//b = (LAST_ERA - iter) * (LAST_ERA - iter) / 1000.0 /1000.0;
	b = (LAST_ERA - iter) / 500.0;
	h = exp(-(r * r) / b);
	return (h);
	if (r > MAP_RAD)
		return (1.0);
	return (0.0);
}

void change_weight(double *input, t_layer *layer, int ep) {
	int i;
	int j;
	double alpha;
	double h;

	i = 0;
	alpha = (ALPHA / (1 + ep));
	while (i < layer->i_n) {
		h = neighbourhood(layer->i_winner, i, ep);
		if (h > 0.0001) {
			j = 0;
			while (j < layer->j_n) {
				layer->w_ij[i][j] += alpha * (input[j] - layer->w_ij[i][j]);
				j++;
			}
		}
		i++;
	}
}

void print_f_as_map(t_layer layer) {
	int n;

	n = 0;
	while (n < layer.i_n) {
		if (layer.i_winner == n)
			printf("\033[7;37m%.4lf\033[00m ", layer.f[n]);
		else
			printf("%.4lf ", layer.f[n]);

		if ((n + 1) % MAP_W == 0) {
			printf("\n");
		}
		n++;
	}
}

void init_map(t_map *map) {
	int i;

	i = 0;
	while (i < N_HIDDEN) {
		map->dist[i] = MAX_DIST_ON_MAP;
		strcpy(map->letter[i], "_");
		map->is_winner[i] = FALSE;
		i++;
	}
}

void print_map(t_map *map) {
	int n;
	char *format;

	n = 0;
	while (n < N_HIDDEN) {
		format = "%s ";
		if (map->is_winner[n])
			format = "\033[7;37m%s\033[00m ";
		printf(format, map->letter[n]);
		if ((n + 1) % MAP_W == 0) {
			printf("\n");
		}
		n++;
	}
}

void change_map(t_map *map, t_layer layer, char *letter) {
	int n;
	double center;
	double *dist;

	dist = layer.f;
	center = layer.f[layer.i_winner];
	map->is_winner[layer.i_winner] = TRUE;
	strcpy(map->letter[layer.i_winner], letter);
	n = 0;
	while (n < N_HIDDEN) {
		if (!map->is_winner[n] && dist[n] - center < map->dist[n]) {
			map->dist[n] = dist[n] - center;
			strcpy(map->letter[n], letter);
		}
		n++;
	}
}

int main() {

	read_letters_from_file("../letters.txt");
	letter_to_x0();

	t_layer layer;
	layer.i_n = N_HIDDEN;
	layer.j_n = N_INPUT;

	srand(time(NULL));
	init_layer(&layer);

	int ep;
	int letter;

	ep = 0;
	while (ep < LAST_ERA) {
		letter = 0;
		while (letter < ANSWER_COUNT) {

			calculate_layer(input[letter], &layer);
			change_weight(input[letter], &layer, ep);
			letter++;
		}
		ep++;
	}

	t_map map;
	init_map(&map);

	int i = 0;
	while (i < ANSWER_COUNT) {
		calculate_layer(input[i], &layer);
		change_map(&map, layer, letter_by_num(i));
		i++;
	}
	print_map(&map);
	return 0;
}
