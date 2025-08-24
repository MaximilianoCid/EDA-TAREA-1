#include "simsearch.hpp"
#include "cluster.hpp" //por si acaso
#include "matrix.hpp" //por si acaso
#include "utils.hpp"
#include <vector>
#include <algorithm>
#include <utility>

//contructor refencia a la matriz con los datos y matriz con los centroides
SimSearch::SimSearch(const Matrix &mat_data, const Cluster &mat_clusters)
    : mat_data(mat_data), mat_clusters(mat_clusters){
}

//busqueda por fuerza bruta
//comparar el query con todos los datos, calcular las distancias, ordenar y obtener los m mejores
std::vector<size_t> SimSearch::search_without(const float *query, size_t top_k){
    //vector donde guardar la distancia del dato al query con el indice
    std::vector<std::pair<float, size_t>> distancias;

    //para cada dato, obtener la distancia al query y guardar el vector
    //recorro la matriz con todos los datos
    for(int i = 0; i<mat_data.getN() ;i++){
        const float* dato = mat_data.getRow(i);
        float distancia_al_query = vec_compute_distance(query, dato, mat_data.getDim());
        //guardo el vector: la dictancia y el indice
        distancias.push_back({distancia_al_query, i});
    }
    //ordenar las distancias de menor a mayor
    std::sort(distancias.begin(), distancias.end());

    //creo un vector para guardar los indices
    std::vector<size_t> indices_ordenados;

    //copio hasta obtener k indices
    for(int i = 0; i < top_k; i++){
        indices_ordenados.push_back(distancias[i].second);
    }

    //retorno vector con indices ordenados
    return indices_ordenados;

}


//busqueda ooptimizada usando clustering 
//comrpar el query con los k centroides para encontrar el cluster más cercano, buscar datos más cernanos 
std::vector<size_t> SimSearch::search_with_clusters(const float *query, size_t top_k){

    std::vector<size_t> assign(mat_data.getN(),0);

    for(size_t i = 0;i < mat_data.getN() ; i++ ){
        const float *x = mat_data.getRow(i);
        float mejor_dist = std::numeric_limits<float>::infinity();
        size_t mejor_centroide = 0;

        for(size_t c = 0 ;c < mat_clusters.getK(); c++){
            const float* cent = mat_clusters.getCentroid(c);
            float dist = vec_compute_distance(x, cent , mat_data.getDim());
            if ((dist < mejor_dist))
        {
            mejor_dist = dist;
            mejor_centroide = cent;
        }
        }  
    }
}

