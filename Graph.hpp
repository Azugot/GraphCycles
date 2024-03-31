// Include necessary libraries
#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

namespace std
{

    // Define a Graph class
    class Graph
    {
    private:
        int NNodes;                           // Number of nodes in the graph
        map<int, vector<int>> adjList;        // Adjacency list representation of the graph
        vector<vector<int>> permutationsList; // List to store permutations
        vector<vector<int>> dfsPaths;         // List to store DFS paths

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
                if (neighbor == origin && node != parent) // If a cycle is found
                {
                    path.push_back(neighbor); // Add the origin node to complete the cycle

                    // Uncomment the following lines to print the cycle path
                    // cout << "Cycle found:" << cycleCount << endl;
                    // for (auto i : path) {
                    //     cout << i << " ";
                    // }
                    // cout << endl;

                    path.pop_back();     // Remove the origin node from the path
                    if (path.size() > 2) // If the cycle has more than 2 nodes
                    {
                        dfsPaths.push_back(path); // Add the cycle path to the list
                    }
                }
                else if (neighbor != parent && neighbor != origin && !findElement(path, neighbor)) // If the neighbor is not the parent, origin, and not already in the path
                {
                    depthFirstSearch(neighbor, origin, path, node); // Recursively call depth-first search on the neighbor
                }
            }
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

        // Perform depth-first search to count cycles starting from a given origin node
        void DFSCountPathsFromOrigin(int origin)
        {
            map<int, bool> visited;
            depthFirstSearch(origin, origin, {}, -1); // Start DFS with the origin
        }

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
            for (auto i : getDfsPaths())
            {
                for (auto j : i)
                {
                    cout << j << " ";
                }
                cout << endl;
            }
        }


        /**
         * Prints the count of cycle paths using Depth-First Search (DFS).
         * This function calculates the count of cycle paths in the graph using DFS and
         * prints the result to the console.
         */
        void DFSPrintCyclePathCount()
        {
            DFSCountPathsFromTotal();
            cout << "CyclesPaths DFS: " << getDfsPaths().size() << endl;
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
            DFSCountPathsFromTotal();
            DFSRemoveSamePaths();
            cout << "Unique Cycles DFS: " << getDfsPaths().size() << endl;
        }

        /**
         * Prints the count of cycle paths generated by permutations.
         * This function generates permutations and finds cycle paths using the PERMFindPaths function.
         * It then prints the number of cycle paths found.
         */
        void PERMPrintCyclePathCount()
        {
            generatePermutations();
            vector<vector<int>> Cycles = PERMFindPaths();
            cout << "CyclesPaths Permutations: " << Cycles.size() << endl;
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
            generatePermutations();
            PERMRemoveSamePaths();
            cout << "Unique Cycles Permutations: " << getPermutationsList().size() << endl;
        }

        /**
         * Prints all the paths in the permutations list.
         */
        void PERMPrintPaths()
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
         * Generates all possible permutations of numbers from 0 to (n-1), where n is the number of nodes in the graph.
         * The permutations are stored in a vector of vectors.
         */
        void generatePermutations()
        {
            vector<vector<int>> permutations; // Create a vector to store all the permutations
            int permNumber = getNNodes();     // Permutation Max size
            // cout << "Permutation Max size: " << permNumber << endl;

            vector<int> allNumbers(permNumber); // Initialize with numbers from 0 to permNumber - 1
            for (int i = 0; i < permNumber; i++)
            {
                allNumbers[i] = i;
            }

            for (int j = permNumber; j > 2; j--) // Generate permutations for sizes n to 3
            {
                do
                {
                    // Push only the first j elements to get a permutation of size j
                    vector<int> currentPermutation(allNumbers.begin(), allNumbers.begin() + j);
                    permutations.push_back(currentPermutation);
                } while (next_permutation(allNumbers.begin(), allNumbers.end())); // Generate the next permutation

                // After generating all permutations of size j, reset the permutation order to ensure all combinations are covered
                sort(allNumbers.begin(), allNumbers.end());
            }
            permutations = removeDuplicates(permutations);
            setPermutationsList(permutations); // Store the permutations
            // cout << "Total permutations: " << permutations.size() << endl;

            vector<vector<int>> Npermutations = getPermutationsList();
            // cout << "Total permutations2: " << permutations.size() << endl;
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