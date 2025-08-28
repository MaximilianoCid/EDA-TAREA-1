#include <iostream>
#include <vector>
#include <chrono> // Para medir el tiempo
#include <numeric> // Para std::accumulate

#include "matrix.hpp"
#include "cluster.hpp"
#include "simsearch.hpp"
#include "utils.hpp"

// Función para imprimir un vector de resultados
void print_vector(const std::vector<size_t>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i == v.size() - 1 ? "" : ", ");
    }       
    std::cout << std::endl;
}

int main() {
    // --- 1. CARGAR DATOS ---
    std::cout << "Cargando datos..." << std::endl;
    Matrix mat_data("/home/maximiliano-cid/Documentos/EDA/EDA-TAREA-1/data_eda.npy");
    Matrix mat_queries("/home/maximiliano-cid/Documentos/EDA/EDA-TAREA-1/queries_eda.npy");
    std::cout << "Datos cargados." << std::endl << std::endl;

    size_t m = 64; // Los 'm' vecinos más cercanos a buscar
    size_t num_queries = mat_queries.getN();

    // --- 2. PRUEBA DE FUERZA BRUTA (SIN CLUSTERS) ---
    std::cout << "--- Ejecutando Búsqueda de Fuerza Bruta (Baseline) ---" << std::endl;
    {
        // Creamos un objeto Cluster y SimSearch "vacío" solo para poder llamar al método
        Cluster dummy_cluster(mat_data, 1);
        SimSearch buscador(mat_data, dummy_cluster);
        
        double total_duration_ms = 0;

        for (size_t i = 0; i < num_queries; ++i) {
            const float* query = mat_queries.getRow(i);
            
            auto start = std::chrono::high_resolution_clock::now();
            buscador.search_without(query, m);
            auto end = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double, std::milli> duration = end - start;
            total_duration_ms += duration.count();
        }
        std::cout << "k-clusters: 0 (no clusters)" << std::endl;
        std::cout << "Tiempo promedio: " << total_duration_ms / num_queries << " ms" << std::endl;
        std::cout << "Error promedio: 0.0" << std::endl << std::endl;
    }


    // --- 3. PRUEBA CON CLUSTERS ---
    std::vector<size_t> k_values = {8, 16, 32, 64, 128};

    for (size_t k : k_values) {
        std::cout << "--- Probando con k = " << k << " ---" << std::endl;

        // Construir los clusters para este valor de 'k'
        Cluster cluster_obj(mat_data, k);
        cluster_obj.applyClustering();
        
        SimSearch buscador(mat_data, cluster_obj);

        double total_duration_ms = 0;
        double total_error = 0;

        for (size_t i = 0; i < num_queries; ++i) {
            const float* query = mat_queries.getRow(i);

            bool log = (i==0);

            // Ejecutar y medir tiempo de la búsqueda con clusters
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<size_t> results_cluster = buscador.search_with_clusters(query, m, cluster_obj);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            total_duration_ms += duration.count();
            
            // Calcular el error comparando con la búsqueda de fuerza bruta
            std::vector<size_t> results_truth = buscador.search_without(query, m);
            double query_error = 0;
            for(size_t j = 0; j < m; ++j){
                float dist_truth = vec_compute_distance(query, mat_data.getRow(results_truth[j]), mat_data.getDim());
                float dist_cluster = vec_compute_distance(query, mat_data.getRow(results_cluster[j]), mat_data.getDim());
                query_error += std::abs(dist_truth - dist_cluster);
            }
            total_error += (query_error / m);
        }

        std::cout << "k-clusters: " << k << std::endl;
        std::cout << "Tiempo promedio: " << total_duration_ms / num_queries << " ms" << std::endl;
        std::cout << "Error promedio: " << total_error / num_queries << std::endl << std::endl;
    }

    return 0;
}