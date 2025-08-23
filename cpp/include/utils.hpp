#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <cmath>
//calcula la distancia entre 2 vectores
//distancia euclidiana
float vec_compute_distance(const float *u, const float* v, size_t dim);
//suma un vector a otro
void vec_add(float *s, const float* u,  size_t dim);
//divide cada elemento del vector en un escalar
void vec_divide(float *u, float scalar, size_t dim);
//inicializar los valores del vector a 0 u otro numero
void set_array(float *array, size_t dim, float val = 0);
//calcular la diferencia promedio entre 2 vectores
float vec_compute_avg_dif(const float *u, const float* v,  size_t dim);
//imprime el vector en la consola
void print_array(const float *array, size_t d);

//debemos hacer esta función:
//size_t *argsort(...)


#endif