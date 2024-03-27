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
        int NNodes; // Number of nodes in the graph
        map<int, vector<int>> adjList; // Adjacency list representation of the graph
        vector<vector<int>> permutationsList; // List to store permutations
        vector<vector<int>> dfsPaths; // List to store DFS paths

        // Helper function for depth-first search
        void depthFirstSearch(int node, int origin, vector<int> path, int parent)
        {
            path.push_back(node); // Add the current node to the path
            for (int neighbor : adjList[node]) // Iterate through the neighbors of the current node
            {
                if (neighbor == origin && node != parent) // If a cycle is found
                {
                    path.push_back(neighbor); // Add the origin node to complete the cycle

                    // Uncomment the following lines to print the cycle path
                    // cout << "Cycle found:" << cycleCount << endl;
                    // for (auto i : path)
                    //{
                    //     cout << i << " ";
                    // }
                    // cout << endl;

                    path.pop_back(); // Remove the origin node from the path
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
        void setNNodes(int n) { NNodes = n; }
        void setAdjList(map<int, vector<int>> adj) { adjList = adj; }
        void setPermutationsList(vector<vector<int>> perms) { this->permutationsList = perms; }
        void setDfsPaths(vector<vector<int>> paths) { this->dfsPaths = paths; }

        // Getter methods
        int getNNodes() { return NNodes; }
        map<int, vector<int>> getAdjList() { return adjList; }
        vector<vector<int>> getPermutationsList() { return permutationsList; }
        vector<vector<int>> getDfsPaths() { return dfsPaths; }

        // Perform depth-first search to count cycles starting from a given origin node
        void DFSCountPathsFromOrigin(int origin)
        {
            map<int, bool> visited;
            depthFirstSearch(origin, origin, {}, -1); // Start DFS with the origin
        }

        // Perform depth-first search to count cycles starting from all nodes
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

        // Remove duplicate paths found by DFS
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
            setDfsPaths(paths); // Update the permutations list
            //printPermutations(); // Print the updated permutations
        }

        // Print the paths found by DFS
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

        // Print the count of cycle paths found by DFS
        void DFSPrintCyclePathCount()
        {
            DFSCountPathsFromTotal();
            cout << "CyclesPaths DFS: " << getDfsPaths().size() << endl;
        }

        void DFSPrintUniqueCyclesCount()
        {
            DFSCountPathsFromTotal();
            DFSRemoveSamePaths();
            cout << "Unique Cycles DFS: " << getDfsPaths().size() << endl;
        }

        // Print the count of cycle paths found by permutations
        void PERMPrintCyclePathCount()
        {
            generatePermutations();
            vector<vector<int>> Cycles = PERMFindPaths();
            cout << "CyclesPaths Permutations: " << Cycles.size() << endl;
        }

        void PERMPrintUniqueCyclesCount()
        {
            generatePermutations();
            PERMRemoveSamePaths();
            cout << "Unique Cycles Permutations: " << getPermutationsList().size() << endl;
        }

        // Print the paths found by permutations
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

        // Remove duplicate paths found by permutations
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

            //removeInvalidPaths(); // Remove invalid paths

            setPermutationsList(paths); // Update the permutations list
            //printPermutations(); // Print the updated permutations
        }

        // Find cycle paths using permutations
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

        // Default constructor
        Graph()
        {
            NNodes = 0;
        }

        // Parameterized constructor
        Graph(int n)
        {
            NNodes = n;
            for (int i = 0; i < n; i++)
            {
                adjList[i] = {};
            }
        }

        void addEdge(int u, int v)
        {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        void removeEdge(int u, int v)
        {
            adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
            adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
        }

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