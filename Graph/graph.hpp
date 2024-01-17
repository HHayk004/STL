#ifndef GRAPH_HPP
	#define GRAPH_HPP
	
	Graph::Graph(size_t size) : vec(size, std::vector<std::pair<int, int>>()) {}

	void Graph::addVertex()
	{
		vec.push_back(std::vector<std::pair<int, int>>());
	}	

	void Graph::addEdge(int vertex1, int vertex2, int weight)
	{
		if (vertex1 >= 0 && vertex1 < vec.size() && vertex1 != vertex2 &&
            vertex2 >= 0 && vertex2 < vec.size() && weight > 0 && !find(vertex1, vertex2))
		{
			vec[vertex1].push_back({vertex2, weight});
		}
	}

    void Graph::removeVertex(int vertex)
    {
        if (vertex >= 0 && vertex < vec.size())
        {
            vec.erase(vec.begin() + vertex);

            for (int i = 0; i < vec.size(); ++i)
            {
                for (int j = 0; j < vec[i].size(); ++j)
                {
                    if (vec[i][j].first == vertex)
                    {
                        vec[i].erase(vec[i].begin() + j);
                        --j;
                    }

                    else if (vec[i][j].first > vertex)
                    {
                        --vec[i][j].first;
                    }
                }
            }
        }
    }

    void Graph::removeEdge(int vertex1, int vertex2)
    {
        for (int i = 0; i < vec[vertex1].size(); ++i)
        {
            if (vec[vertex1][i].first == vertex2)
            {
                vec[vertex1].erase(vec[vertex1].begin() + i);
                break;
            }
        }
    }

    int Graph::vertexCount() const
    {
        return vec.size();
    }

    int Graph::edgeCount() const
    {
        int edges_count = 0;
        for (int i = 0; i < vec.size(); ++i)
        {
            edges_count += vec[i].size();
        }

        return edges_count;
    }

    std::vector<std::pair<int, int>> Graph::vertexEdges(int vertex) const
    {
        return vec[vertex];
    }

    std::vector<int> Graph::shortPath(int vertex1, int vertex2) const
    {
        std::unordered_set<int> visited;
        
        std::vector<int> path;
        std::vector<int> short_path;
        
        int weight = 0;
        int min_weight = 0;
        
        dfs(vertex1, vertex2, visited, path, short_path, weight, min_weight);

        return short_path;
    }

    void Graph::dfs(int vertex1, int vertex2, std::unordered_set<int>& visited, 
                    std::vector<int>& path, std::vector<int>& short_path, int& weight, int& min_weight) const
    { 
        visited.insert(vertex1);
        path.push_back(vertex1);

        if (vertex1 == vertex2)
        {
            if (min_weight == 0 || weight < min_weight)
            {
                short_path = path;
                min_weight = weight;
            }
        }
        
        else
        {   
            for (int i = 0; i < vec[vertex1].size(); ++i)
            {
                if (visited.find(vec[vertex1][i].first) == visited.end())
                {
                    weight += vec[vertex1][i].second;
                    dfs(vec[vertex1][i].first, vertex2, visited, path, short_path, weight, min_weight);
                    weight -= vec[vertex1][i].second;
                }
            }
        }
    
        visited.erase(vertex1);
        path.pop_back();
    }

    void Graph::levelOrder(int vertex) const
    {
        std::queue<int> vertexes;
        vertexes.push(vertex);
        
        std::unordered_set<int> visited;
        visited.insert(vertex);        

        while (!vertexes.empty())
        {
            int vertex = vertexes.front();
            for (auto& elem : vec[vertex])
            {
                if (visited.find(elem.first) == visited.end())
                {
                    vertexes.push(elem.first);
                    visited.insert(elem.first);
                }
            }

            std::cout << vertex << ' ';
            vertexes.pop();
        }
        std::cout << std::endl;
    }

    std::vector<int> Graph::dijkstra(int vertex) const
    {
        std::vector<int> fast(vec.size(), INT_MAX);
        fast[vertex] = 0;

        dijkstraImpl(vertex, fast);

        return fast;
    }

    void Graph::dijkstraImpl(int vertex, std::vector<int>& fast) const
    {
        for (const std::pair<int, int>& neighbor : vec[vertex])
        {
            int x = neighbor.first;
            int w = neighbor.second + fast[vertex];

            if (w < fast[x])
            {
                fast[x] = w;
                dijkstraImpl(x, fast);
            }
        }
    }

    std::vector<std::vector<int>> Graph::connectedComponents() const
    {
        std::vector<std::vector<int>> result(vec.size(), std::vector<int>()); 
        
        for (int i = 0; i < vec.size(); ++i)
        {
            if (result[i].empty())
            {
                std::vector<int> path;
                std::unordered_set<int> visited;
                
                connectedComponentsImpl(i, visited, path, result);
            }

            std::sort(result[i].begin(), result[i].end());
        }

        return result;
    }

    void Graph::connectedComponentsImpl(int vertex, std::unordered_set<int>& visited,
                                        std::vector<int>& path ,std::vector<std::vector<int>>& result) const
    {
        path.push_back(vertex);
        visited.insert(vertex);

        for (const std::pair<int, int>& neighbor : vec[vertex])
        {
            if (visited.find(neighbor.first) == visited.end())
            {
                for (const int& elem : path)
                {
                    bool check = true;
                    for (int i = 0; i < result[elem].size(); ++i)
                    {
                        if (result[elem][i] == neighbor.first)
                        {
                            check = false;
                            break;
                        }
                    }

                    if (check)
                    {
                        result[elem].push_back(neighbor.first);
                    }
                }

                connectedComponentsImpl(neighbor.first, visited, path, result);
            }
        }

        path.pop_back();
        visited.erase(vertex);
    }
    
    bool Graph::find(int vertex1, int vertex2) const
    {
        for (int i = 0; i < vec[vertex1].size(); ++i)
        {
            if (vec[vertex1][i].first == vertex2)
            {
                return true;
            }
        }

        return false;
    }

	void Graph::printGraph() const
	{
		for (int i = 0; i < vec.size(); ++i)
		{
			std::cout << i << " -> ";
			for (int j = 0; j < vec[i].size(); ++j)
			{
				std::cout << '{' << vec[i][j].first << ", " << vec[i][j].second << "} ";
			}
			std::cout << std::endl;
		}
        std::cout << std::endl;
	}

#endif
