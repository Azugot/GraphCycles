#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

namespace std
{

    class Graph
    {
    private:
        int NNodes;
        map<int, vector<int>> adjList;
        vector<vector<int>> permutationsList;
        vector<vector<int>> dfsPaths;

        void depthFirstSearch(int node, int origin, vector<int> path, int parent)
        {
            path.push_back(node);
            for (int neighbor : adjList[node])
            {
                if (neighbor == origin && node != parent)
                {
                    path.push_back(neighbor);

                    // cout << "Cycle found:" << cycleCount << endl;
                    // for (auto i : path)
                    //{
                    //     cout << i << " ";
                    // }
                    // cout << endl;
                    path.pop_back();
                    if (path.size() > 2)
                    {
                        dfsPaths.push_back(path);
                    }
                }
                else if (neighbor != parent && neighbor != origin && !findElement(path, neighbor))
                {

                    depthFirstSearch(neighbor, origin, path, node);
                }
            }
        }

    public:
        void setNNodes(int n) { NNodes = n; }
        void setAdjList(map<int, vector<int>> adj) { adjList = adj; }
        void setPermutationsList(vector<vector<int>> perms) { this->permutationsList = perms; }

        int getNNodes() { return NNodes; }
        map<int, vector<int>> getAdjList() { return adjList; }
        vector<vector<int>> getPermutationsList() { return permutationsList; }

        void countCyclesFromOrigin(int origin)
        {
            map<int, bool> visited;
            depthFirstSearch(origin, origin, {}, -1); // Start DFS with the origin
        }

        void countCyclesFromTotal()
        {
            map<int, bool> visited;
            map<int, vector<int>> adjListCopy = getAdjList();

            for (auto i : adjListCopy)
            {
                int origin = i.first;
                depthFirstSearch(origin, origin, {}, -1);
            }
        }

        void printDfsPaths()
        {
            for (auto i : dfsPaths)
            {
                for (auto j : i)
                {
                    cout << j << " ";
                }
                cout << endl;
            }
        }

        void printCycleCount() const
        {
            cout << dfsPaths.size() << endl;
        }

        void removeSamePaths()
        {
            vector<vector<int>> paths = getPermutationsList();
            {
                for (int i = 0; i < paths.size(); i++)
                {
                    vector<int> path = paths[i];
                    sort(path.begin(), path.end());
                    // cout << "sorted: ";
                    // for (auto i : path)
                    //{
                    //     cout << i << " ";
                    // }
                    // cout << endl;
                    paths[i] = path;
                }
            }
            paths = removeDuplicates(paths);
            setPermutationsList(paths);
            printPermutations();
        }

        Graph()
        {
            NNodes = 0;
        }

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

        vector<vector<int>> findCyclesPermutation()
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