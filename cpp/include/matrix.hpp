#ifndef _MATRIX_HPP
#define _MATRIX_HPP
#include <iostream>

//clase matrix
class Matrix{
    private:
        //puntero a memoria
        float *data; // buffer for storing the float data
        //numero de filas
        size_t n; // number of rows
        //numero de columnas
        size_t dim; // dimension of the vectors
    public:
        Matrix(size_t _n = 0, size_t _dim  = 0);
        Matrix(const std::string &str_file);
        //rellena la matriz con datos aleatorios
        void setAllRandom();
        //devuelve puntero al inicio de una fila específica
        const float *getRow(size_t row) const;
        //modifica una fila completa de la matriz
        void setRow(size_t row, float* vector);
        //imprime la matriz
        void show() const;
        //obtener numero de filas
        size_t getN() const;
        //obtener numero columnas
        size_t getDim() const;
        //obtner puntero a memoria
        const float *getData();
        virtual ~Matrix();
};

#endif