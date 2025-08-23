#ifndef _CLUSTER_HPP
#define _CLUSTER_HPP
#include "matrix.hpp"
#include <vector>
//clase Cluster 
class Cluster{
    private:
        //refencia a matriz con todos los datos
        const Matrix &mat_data; //it's a set of vectors n x dim
        //matriz con los centroides de cada uno de los k clusters
        Matrix mat_centroids; // it'ss a set of centroids, clusters k x dim
        //cantidad k de clusters que se van a crear
        size_t k_clusters; //it's a number of clusters
        //puntero a array de vectores donde cada vector guarda los indices de los puntos que pertenen a un cluster
        //ej: inds[0] contiene lista con todos los puntos dentro de cluster 0
        std::vector<size_t> *inds; // it is an array of vectors

    public: 
        Cluster(const Matrix &mat, size_t k = 8);  
        //asigna cada punto a un cluster     
        void compute_clusters();
        //recalcula la posición de cada centroide basandose en el promedio de los puntos dentro del cluster
        void update_centroids();
        //ejecuta k_means completo
        void applyClustering();
        //obtener el lugar del centroide
        const float *getCentroid(size_t i);
        //obtener lista de puntos de un cluster
        std::vector<size_t> getInds(size_t i);
        void print_clusters() const;
        virtual ~Cluster();
};
#endif