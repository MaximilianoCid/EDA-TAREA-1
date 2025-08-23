#include "simsearch.hpp"
#include "cluster.hpp" //por si acaso
#include "matrix.hpp" //por si acaso
#include "utils.hpp"
#include <vector>
#include <algorithm>
#include <utility>

//contructor refencia a la matriz con los datos y matriz con los centroides
SimSearch::SimSearch(const Matrix &mat_data, const Matrix &mat_clusters)
    : mat_data(mat), mat_clusters(clusters){
}

//busqueda por fuerza bruta
//comparar el query con todos los datos, calcular las distancias, ordenar y obtener los m mejores
std::vector<size_t> SimSearch::search_with_clusters(const float *query,  top_k){

}


    //busqueda ooptimizada usando clustering 
    //comrpar el query con los k centroides para encontrar el cluster más cercano, buscar datos más cernanos 
std::vector<size_t> SimSearch::search_without(const float *query, top_k){

}
