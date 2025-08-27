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
//comparar el query con todos los datos, calcular las distancias, ordenar y obtener los k mejores
std::vector<size_t> SimSearch::search_without(const float *query, size_t top_k){
    //vector donde guardar la distancia del dato al query con el indice
    std::vector<float> distancias;

    //para cada dato, obtener la distancia al query y guardar el vector
    //recorro la matriz con todos los datos
    for(int i = 0; i<mat_data.getN() ;i++){
        const float* dato = mat_data.getRow(i);
        float distancia_al_query = vec_compute_distance(query, dato, mat_data.getDim());
        //guardo el vector: la dictancia y el indice
        distancias.push_back(distancia_al_query);
    }

    //creo un vector para guardar los indices ordenador con la función argsort
    std::vector<size_t> indices_ordenados = argsort(distancias.data(), distancias.size());

    //se entregan los k mejores
    if (indices_ordenados.size() > top_k) {
        indices_ordenados.resize(top_k);
    }

    //retorno vector con indices ordenados
    return indices_ordenados;

}

//busqueda optimizada usando clustering 
//compara el query con los k centroides para encontrar el o los clusters más cercanos, y después buscar datos más cernanos 
std::vector<size_t> SimSearch::search_with_clusters(const float *query, size_t top_k, const Cluster& class_cluster){
    //primero, ordenar los cluster más cerca al query:
    //calculo las distancias del centro del cluster al query, para cada cluster y lo guardo
    std::vector<float> distancia_cluster;
    size_t k_clusters = class_cluster.getK();
    for(int i = 0; i< k_clusters; i++){
        const float* centroide_cluster = class_cluster.getCentroid(i);
        float distancia_cluster_query = vec_compute_distance(query, centroide_cluster, mat_data.getDim());
        distancia_cluster.push_back(distancia_cluster_query);
    }
    //ordeno de menor distancia a mayor:
    std::vector<size_t> indices_cluster_ordenados = argsort(distancia_cluster.data(), distancia_cluster.size());

    //busco la cantidad de clusters necesaria para tener todos los datos y que no nos falten después
    std::vector<size_t> indices_necesarios_de_cluster;
    for(int i = 0; i<indices_cluster_ordenados.size(); i++){
        size_t cluster_idx = indices_cluster_ordenados[i];
        std::vector<size_t> puntos_del_cluster = class_cluster.getInds(cluster_idx);
        indices_necesarios_de_cluster.insert(indices_necesarios_de_cluster.end(), puntos_del_cluster.begin(), puntos_del_cluster.end());
        if(indices_necesarios_de_cluster.size()>=top_k){
            break;
        }
    }

    //ahora con la cantidad de datos necesaria, hacemos la busqueda por fuerza bruta
    //copie lo de arriba (función de search without) pero recorriendo los datos de los clusters
    std::vector<float> distancias;
    for(size_t i = 0; i<indices_necesarios_de_cluster.size() ;i++){
        int idx = indices_necesarios_de_cluster[i];
        const float* dato = mat_data.getRow(idx);
        float distancia_al_query = vec_compute_distance(query, dato, mat_data.getDim());
        distancias.push_back(distancia_al_query);
    }
    //ordenamos los datos de menor a mayor distancia
    std::vector<size_t> indices_ordenados = argsort(distancias.data(), distancias.size());
    //vector donde guardaremos indices
    std::vector<size_t> resultado_final;
    //tenemos que volver a tener los indices de antes de hacer argsort
    for(int i = 0; i < top_k; i++){
        size_t posicion_argsort = indices_ordenados[i];
        size_t indice_original = indices_necesarios_de_cluster[posicion_argsort];
        resultado_final.push_back(indice_original);
    }

    return resultado_final;
}










    //std::vector<size_t> assign(mat_data.getN(),0);
    //for(size_t i = 0;i < mat_data.getN() ; i++ ){
    //    const float *x = mat_data.getRow(i);
    //    float mejor_dist = std::numeric_limits<float>::infinity();
    //    size_t mejor_centroide = 0;
    //
    //    for(size_t c = 0 ;c < mat_clusters.getK(); c++){
    //        const float* cent = mat_clusters.getCentroid(c);
    //        float dist = vec_compute_distance(x, cent , mat_data.getDim());
    //        if ((dist < mejor_dist))
    //    {
    //        mejor_dist = dist;
    //        mejor_centroide = cent;
    //    }
    //    }  
    //}

