#ifndef GRAPH_H
	#define GRAPH_H
	
    #include <iostream>
	#include <vector>
    #include <queue>
    #include <utility>
    #include <limits>
    #include <unordered_set>

	class Graph {
		private:
			std::vector<std::vector<std::pair<int, int>>> vec;
	
            void dfs(int vertex1, int vertex2, std::unordered_set<int>& visited, 
                     std::vector<int>& path, std::vector<int>& short_path,
                     int& weight, int& min_weight) const;

            void dijkstraImpl(int vertex, std::vector<int>& fast) const;

            void connectedComponentsImpl(int vertex, std::unordered_set<int>& visited,
                 std::vector<int>& path, std::vector<std::vector<int>>& result) const;
                
		public:
			Graph(size_t size = 0);
			~Graph() = default;

			void addVertex();
			void addEdge(int vertex1, int vertex2, int weight);

            void removeVertex(int vertex);
            void removeEdge(int vertex1, int vertex2);

            int vertexCount() const;
            int edgeCount() const;

            std::vector<std::pair<int, int>> vertexEdges(int vertex) const;

            bool find(int vertex1, int vertex2) const;

            std::vector<int> shortPath(int vertex1, int vertex2) const;
            void levelOrder(int vertex) const;

            std::vector<int> dijkstra(int vertex) const;
            
            std::vector<std::vector<int>> connectedComponents() const;

			void printGraph() const;
	};

	#include "graph.hpp"
	
#endif
