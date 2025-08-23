#ifndef _SIM_SEARCH_HPP
#define _SIM_SEARCH_HPP
//lo que debemos implementar
class SimSearch{
private:
    //referencia de matriz con los datos
    const Matrix &mat_data; // data to be processed
    //referencia a matriz con los centroides de los clusters
    const Matrix &mat_clusters; // centroids to be used

public:
    SimSearch(Matrix, clusters);
    //busqueda por fuerza bruta
    //comparar el query con todos los datos, calcular las distancias, ordenar y obtener los m mejores
    std::vector<size_t> search_with_clusters(const float *query,  top_k);
    //busqueda ooptimizada usando clustering 
    //comrpar el query con los k centroides para encontrar el cluster más cercano, buscar datos más cernanos 
    std::vector<size_t> search_without(const float *query, top_k);
}

#endif 