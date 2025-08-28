#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cmath> // Para std::abs

#include "matrix.hpp"
#include "cluster.hpp"
#include "simsearch.hpp"
#include "utils.hpp"

void print_vector(const std::vector<size_t>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

int main() {
    //Cambiar rutas: 
    Matrix mat_data("/home/anto/universidad/estructuraDeDatosYAlgoritmos/tarea1/EDA-TAREA-1/data_eda.npy");
    Matrix mat_queries("/home/anto/universidad/estructuraDeDatosYAlgoritmos/tarea1/EDA-TAREA-1/queries_eda.npy");
    //cambiamos m para cada tabla
    size_t m = 8;
    size_t num_queries = mat_queries.getN();

    std::cout << "Fuerza Bruta:" << std::endl;
    {
        Cluster dummy_cluster(mat_data, 1);
        SimSearch buscador(mat_data, dummy_cluster);
        double total_duration_ms = 0;
        //search_without para cada consulta
        for (size_t i = 0; i < num_queries; ++i) {
            const float* query = mat_queries.getRow(i);
            auto start = std::chrono::high_resolution_clock::now();
            //ejecuta search_without
            buscador.search_without(query, m);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            total_duration_ms += duration.count();
        }
        //entrega la info para hacer la tablita
        std::cout << "k-clusters: 0 (no clusters)" << std::endl;
        std::cout << "Tiempo promedio: " << total_duration_ms / num_queries << " ms" << std::endl;
        std::cout << "Error promedio: 0.0" << std::endl << std::endl;
    }
    //para cada clusters
    std::vector<size_t> k_values = {8, 16, 32, 64, 128};
    //para cada clusters
    for (size_t k : k_values) {
        std::cout << "k = " << k  << std::endl;
        Cluster cluster_obj(mat_data, k);
        cluster_obj.applyClustering();
        SimSearch buscador(mat_data, cluster_obj);
        double total_duration_ms = 0;
        double total_error = 0;
        //search_with_clusters para cada consulta
        for (size_t i = 0; i < num_queries; ++i) {
            const float* query = mat_queries.getRow(i);
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<size_t> results_cluster = buscador.search_with_clusters(query, m);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            total_duration_ms += duration.count();
            std::vector<size_t> results_truth = buscador.search_without(query, m);
            double query_error = 0;
            for(size_t j = 0; j < m; ++j){
                float dist_truth = vec_compute_distance(query, mat_data.getRow(results_truth[j]), mat_data.getDim());
                float dist_cluster = vec_compute_distance(query, mat_data.getRow(results_cluster[j]), mat_data.getDim());
                query_error += std::abs(dist_truth - dist_cluster);
            }
            total_error += (query_error / m);
        }
        //entrega la info para hacer la tablita
        std::cout << "k-clusters: " << k << std::endl;
        std::cout << "Tiempo promedio: " << total_duration_ms / num_queries << " ms" << std::endl;
        std::cout << "Error promedio: " << total_error / num_queries << std::endl << std::endl;
    }
    return 0;
}