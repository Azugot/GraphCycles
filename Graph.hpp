// Purpose: Header file for the Graph class.
// Authors: Augusto Scardua and Pedro Heinrich
// All methods implemented in private section are effectively the ones used to solve the problem, and the public methods are used to interact with the Graph class.
// Include necessary libraries
#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
namespace std
{

    /**
     * @class Graph
     * @brief Represents a graph data structure.
     *
     * The Graph class provides functionality to represent a graph using an adjacency list representation.
     * It supports operations such as depth-first search, generating permutations, and counting paths.
     */
    class Graph
    {
    private:
        int NNodes;                           // Number of nodes in the graph
        map<int, vector<int>> adjList;        // Adjacency list representation of the graph
        vector<vector<int>> permutationsList; // List to store permutations
        vector<vector<int>> dfsPaths;         // List to store DFS paths
        int DFScount = 0;
        int PERMcount = 0;
        bool storePaths = false;

        /**
         * Checks if an element exists in a vector.
         *
         * @param vec The vector to search in.
         * @param element The element to find.
         * @return True if the element is found, false otherwise.
         */
        bool findElement(vector<int> vec, int element)
        {
            for (auto i : vec)
            {
                if (i == element)
                {
                    return true;
                }
            }
            return false;
        }

        bool isValidPath(vector<int> path)
        {
            path.push_back(path[0]); // Adiciona o primeiro vértice ao final do caminho

            //for (int i : path){
            //    cout << i << " ";
            //}
            //cout << endl;

            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                // Verifica se cada vértice está conectado ao próximo
                if (find(adjList[path[i]].begin(), adjList[path[i]].end(), path[i + 1]) == adjList[path[i]].end())
                {
                    //cout << "Invalid Path" << endl;
                    return false; // O próximo vértice não está na lista de adjacências do vértice atual
                }
            }
            //cout << "Valid Path" << endl;
            return true; // Todos os vértices estão conectados
        }

        /**
         * Performs a depth-first search starting from a given node in the graph.
         *
         * @param node The current node being visited.
         * @param origin The starting node of the search.
         * @param path The path taken during the search.
         * @param parent The parent node of the current node.
         */
        void depthFirstSearch(int node, int origin, vector<int> path, int parent)
        {
            path.push_back(node);              // Add the current node to the path
            for (int neighbor : adjList[node]) // Iterate through the neighbors of the current node
            {
                if (neighbor == origin && node != parent && path.size() > 2) // If a cycle is found
                {
                    if (storePaths == true)
                    {
                        dfsPaths.push_back(path); // Add the cycle path to the list
                    }
                    else
                    {
                        DFScount++;
                    }
                }
                else if (neighbor != parent && neighbor != origin && !findElement(path, neighbor)) // If the neighbor is not the parent, origin, and not already in the path
                {
                    depthFirstSearch(neighbor, origin, path, node); // Recursively call depth-first search on the neighbor
                }
            }
        }

        /**
         * Generates optimized permutations for subsets of nodes.
         *
         * This function generates permutations for subsets of nodes ranging from size 3 to NNodes.
         * It uses an optimized approach to generate the permutations by generating subsets of nodes
         * and then permuting each subset. The permutations are stored in the permutationsList vector.
         *
         * @param None
         * @return None
         */
        void generatePermutationsOptimized()
        {
            vector<int> nodes(NNodes);
            iota(nodes.begin(), nodes.end(), 0); // Preenche nodes de 0 a NNodes-1

            // Limpa a lista de permutações anterior
            permutationsList.clear();

            // Gera subconjuntos de tamanho 3 até N
            for (int r = 3; r <= NNodes; ++r)
            {
                vector<bool> v(NNodes);
                fill(v.begin(), v.begin() + r, true);

                do
                {
                    vector<int> subset;
                    for (int i = 0; i < NNodes; ++i)
                    {
                        if (v[i])
                        {
                            subset.push_back(i);
                        }
                    }
                    // Gera permutações para o subconjunto
                    sort(subset.begin(), subset.end());
                    do
                    {

                        if (isValidPath(subset))
                        {
                            if (storePaths == true)
                            {
                                permutationsList.push_back(subset);
                            }
                            else
                            {
                                PERMcount++;
                            }
                        }
                    } while (next_permutation(subset.begin(), subset.end()));
                } while (prev_permutation(v.begin(), v.end()));
            }
        }

        /**
         * Finds all paths in the graph that form cycles.
         *
         * @return A vector of vectors, where each inner vector represents a cycle in the graph.
         */
        vector<vector<int>> PERMFindPaths()
        {
            vector<vector<int>> Cycles;
            map<int, vector<int>> adjListCopy = getAdjList();
            vector<vector<int>> permList = getPermutationsList();
            for (auto instance : permList)
            {
                bool found = true;
                for (int i = 0; i < instance.size() && found; i++)
                {
                    int u = instance[i];
                    int v = instance[(i + 1) % instance.size()];
                    found = findElement(adjListCopy[u], v);
                }
                if (found)
                {
                    Cycles.push_back(instance);
                }
            }
            return Cycles;
        }

        /**
         * Removes duplicate vectors from the given vector of vectors.
         *
         * @param permutations The vector of vectors containing permutations.
         * @return A new vector of vectors with duplicate permutations removed.
         */
        vector<vector<int>> removeDuplicates(vector<vector<int>> &permutations)
        {
            vector<vector<int>> uniquePermutations;
            for (auto i : permutations)
            {
                if (find(uniquePermutations.begin(), uniquePermutations.end(), i) == uniquePermutations.end())
                {
                    uniquePermutations.push_back(i);
                }
            }
            return uniquePermutations;
        }

    public:
        // Setter methods
        /**
         * @brief Sets the number of nodes in the graph.
         *
         * This function sets the number of nodes in the graph to the specified value.
         *
         * @param n The number of nodes to set.
         */
        void setNNodes(int n) { NNodes = n; }

        /**
         * @brief Sets the adjacency list of the graph.
         *
         * This function sets the adjacency list of the graph to the provided map of integers and vectors.
         * The map represents the vertices of the graph, and each vector represents the adjacent vertices of a particular vertex.
         *
         * @param adj The map representing the adjacency list of the graph.
         */
        void setAdjList(map<int, vector<int>> adj) { adjList = adj; }

        /**
         * @brief Sets the permutations list for the graph.
         *
         * This function sets the permutations list for the graph. The permutations list is a vector of vectors of integers,
         * where each inner vector represents a permutation of the vertices in the graph. This function updates the permutationsList
         * member variable of the graph object.
         *
         * @param perms The permutations list to be set.
         */
        void setPermutationsList(vector<vector<int>> perms) { this->permutationsList = perms; }

        /**
         * Sets whether or not to store paths in the graph.
         *
         * @param storePaths A boolean value indicating whether to store paths.
         */
        bool setStorePaths(bool storePaths)
        {
            this->storePaths = storePaths;
        }

        /**
         * @brief Sets the DFS paths of the graph.
         *
         * This function sets the DFS paths of the graph to the specified paths.
         *
         * @param paths A vector of vectors representing the DFS paths.
         */
        void setDfsPaths(vector<vector<int>> paths) { this->dfsPaths = paths; }

        // Getter methods
        /**
         * Returns the number of nodes in the graph.
         *
         * @return The number of nodes in the graph.
         */
        int getNNodes() { return NNodes; }

        /**
         * Returns the adjacency list of the graph.
         * The adjacency list is a mapping of each vertex to its list of adjacent vertices.
         *
         * @return The adjacency list of the graph.
         */
        map<int, vector<int>> getAdjList() { return adjList; }

        /**
         * Returns the permutations list.
         *
         * @return The permutations list as a vector of vectors of integers.
         */
        vector<vector<int>> getPermutationsList() { return permutationsList; }

        /**
         * Returns the Depth-First Search (DFS) paths of the graph.
         *
         * @return A vector of vectors representing the DFS paths of the graph.
         */
        vector<vector<int>> getDfsPaths() { return dfsPaths; }

        // DFS Methods

        /**
         * Counts the number of paths from a given source vertex to all other vertices in the graph using Depth-First Search (DFS).
         *
         * This function performs a Depth-First Search starting from the source vertex and counts the number of paths to each vertex in the graph.
         * The result is stored in a data structure that can be accessed later.
         *
         * @param None
         * @return None
         */
        void DFSCountPathsFromTotal()
        {
            map<int, bool> visited;
            map<int, vector<int>> adjListCopy = getAdjList();
            vector<vector<int>> dfsPaths;

            for (auto i : adjListCopy)
            {
                int origin = i.first;
                depthFirstSearch(origin, origin, {}, -1);
            }
        }

        /**
         * Performs a depth-first search to remove duplicate paths in the graph.
         * This function removes any duplicate paths that exist between two vertices in the graph.
         * It starts the search from a specified vertex and explores all possible paths until it reaches a dead end.
         * The function modifies the graph by removing any duplicate paths found.
         */
        void DFSRemoveSamePaths()
        {
            vector<vector<int>> paths = getDfsPaths();
            {
                for (int i = 0; i < paths.size(); i++)
                {
                    vector<int> path = paths[i];
                    sort(path.begin(), path.end()); // Sort the path to remove duplicates
                    // Uncomment the following lines to print the sorted path
                    // cout << "sorted: ";
                    // for (auto i : path)
                    //{
                    //     cout << i << " ";
                    // }
                    // cout << endl;
                    paths[i] = path;
                }
            }
            paths = removeDuplicates(paths); // Remove duplicate paths
            setDfsPaths(paths);              // Update the permutations list
            // printPermutations(); // Print the updated permutations
        }

        /**
         * Prints all the paths obtained from a Depth-First Search traversal of the graph.
         */
        void DFSPrintPaths()
        {
            if (storePaths == true)
            {
                for (auto i : getDfsPaths())
                {
                    for (auto j : i)
                    {
                        cout << j << " ";
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "Function Disabled as it requires the Paths to be Stored (May not work for graphs with more than 9 vertices)" << endl;
            }
        }

        /**
         * Prints the count of cycle paths using Depth-First Search (DFS).
         * This function calculates the count of cycle paths in the graph using DFS and
         * prints the result to the console.
         */
        void DFSPrintCyclePathCount()
        {
            if (getDfsPaths().size() == 0)
            {
                DFSCountPathsFromTotal();
            }
            if (storePaths == true)
            {
                cout << "CyclesPaths DFS: " << getDfsPaths().size() << endl;
            }
            else
            {
                cout << "CyclesPaths DFS: " << this->DFScount << endl;
            }
        }

        /**
         * Prints the count of unique cycles using Depth-First Search (DFS).
         *
         * This function first counts the total number of paths using DFSCountPathsFromTotal(),
         * then removes duplicate paths using DFSRemoveSamePaths(), and finally prints the count
         * of unique cycles.
         */
        void DFSPrintUniqueCyclesCount()
        {
            if (storePaths == true)
            {
                if (getDfsPaths().size() == 0)
                {
                    DFSCountPathsFromTotal();
                }
                DFSRemoveSamePaths();
                cout << "Unique Cycles DFS: " << getDfsPaths().size() << endl;
            }
            else
            {
                cout << "Function Disabled as it requires the Paths to be Stored (May not work for graphs with more than 9 vertices)" << endl;
            }
        }

        /**
         * Prints the count of cycle paths generated by permutations.
         * This function generates permutations and finds cycle paths using the PERMFindPaths function.
         * It then prints the number of cycle paths found.
         */
        void PERMPrintCyclePathCount()
        {
            if (getPermutationsList().size() == 0)
            {
                generatePermutationsOptimized();
            }
            if (storePaths == true)
            {
                vector<vector<int>> Cycles = PERMFindPaths();
                cout << "CyclesPaths Permutations: " << Cycles.size() << endl;
            }
            else
            {
                cout << "CyclesPaths Permutations: " << this->PERMcount << endl;
            }
        }

        /**
         * Prints the count of unique cycles permutations.
         *
         * This function generates permutations, removes same paths, and then prints the count of unique cycles permutations.
         *
         * @return void
         */
        void PERMPrintUniqueCyclesCount()
        {
            if (storePaths == true)
            {
                if (getPermutationsList().size() == 0)
                {
                    generatePermutationsOptimized();
                }
                PERMRemoveSamePaths();
                cout << "Unique Cycles Permutations: " << getPermutationsList().size() << endl;
            }
            else
            {
                cout << "Function Disabled as it requires the Paths to be Stored (May not work for graphs with more than 9 vertices)" << endl;
            }
        }

        /**
         * Prints all the paths in the permutations list.
         */
        void PERMPrintPaths()
        {
            if (storePaths == true)
            {
                for (auto i : getPermutationsList())
                {
                    for (auto j : i)
                    {
                        cout << j << " ";
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "Function Disabled as it requires the Paths to be Stored (May not work for graphs with more than 9 vertices)" << endl;
            }
        }

        /**
         * Removes duplicate paths from the graph.
         * This function removes any duplicate paths found in the graph, keeping only one instance of each unique path.
         * The function modifies the graph in-place.
         */
        void PERMRemoveSamePaths()
        {
            vector<vector<int>> paths = getPermutationsList();
            {
                for (int i = 0; i < paths.size(); i++)
                {
                    vector<int> path = paths[i];
                    sort(path.begin(), path.end()); // Sort the path to remove duplicates
                    // Uncomment the following lines to print the sorted path
                    // cout << "sorted: ";
                    // for (auto i : path)
                    //{
                    //     cout << i << " ";
                    // }
                    // cout << endl;
                    paths[i] = path;
                }
            }
            paths = removeDuplicates(paths); // Remove duplicate paths

            // removeInvalidPaths(); // Remove invalid paths

            setPermutationsList(paths); // Update the permutations list
            // printPermutations(); // Print the updated permutations
        }
        /**
         * @brief Constructs a new Graph object.
         *
         * This constructor initializes a new Graph object with zero nodes.
         */
        Graph()
        {
            NNodes = 0;
        }

        /**
         * @brief Constructs a Graph object with the specified number of nodes.
         *
         * @param n The number of nodes in the graph.
         */
        Graph(int n)
        {
            NNodes = n;
            for (int i = 0; i < n; i++)
            {
                adjList[i] = {};
            }
        }

        /**
         * Adds an edge between two vertices in the graph.
         *
         * @param u The first vertex.
         * @param v The second vertex.
         */
        void addEdge(int u, int v)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        /**
         * @brief Removes an edge between two vertices in the graph.
         *
         * This function removes the edge between vertex 'u' and vertex 'v' in the graph.
         * It removes 'v' from the adjacency list of 'u' and 'u' from the adjacency list of 'v'.
         *
         * @param u The first vertex of the edge.
         * @param v The second vertex of the edge.
         */
        void removeEdge(int u, int v)
        {
            adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
            adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
        }

        /**
         * Prints the adjacency list representation of the graph.
         */
        void printGraph()
        {
            for (auto i : adjList)
            {
                cout << i.first << " -> ";
                for (auto j : i.second)
                {
                    cout << j << " ";
                }
                cout << endl;
            }
        }

        /**
         * Prints all the permutations in the permutationsList.
         */
        void printPermutations()
        {
            for (auto permutation : permutationsList)
            {
                for (auto walk : permutation)
                {
                    cout << walk << " ";
                }
                cout << endl;
            }
        }

        /**
         * Generates a complete graph by adding edges between all pairs of nodes.
         * The graph must already have the desired number of nodes.
         */
        void genCompleteGraph()
        {
            for (int i = 0; i < NNodes; i++)
            {
                for (int j = i + 1; j < NNodes; j++)
                {
                    addEdge(i, j);
                }
            }
        }
    };
}

#endif