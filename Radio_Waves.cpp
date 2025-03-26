#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>

class Solution {
public:
    int calculateMax(int network_nodes, 
                     const std::vector<int>& network_from, 
                     const std::vector<int>& network_to, 
                     const std::vector<int>& frequencies) {
        // Create adjacency list
        std::vector<std::vector<int>> graph(network_nodes);
        for (size_t i = 0; i < network_from.size(); ++i) {
            graph[network_from[i] - 1].push_back(network_to[i] - 1);
            graph[network_to[i] - 1].push_back(network_from[i] - 1);
        }
        
        // Find longest path from each node
        int max_distance = 0;
        for (int start = 0; start < network_nodes; ++start) {
            max_distance = std::max(max_distance, findLongestPath(start, graph, frequencies));
        }
        
        return max_distance;
    }
    
private:
    // Check if two nodes can transmit based on frequency
    bool canTransmit(int node1, int node2, const std::vector<int>& frequencies) {
        return std::abs(frequencies[node1] - frequencies[node2]) <= 1;
    }
    
    // Find longest path from a given start node
    int findLongestPath(int start_node, 
                        const std::vector<std::vector<int>>& graph, 
                        const std::vector<int>& frequencies) {
        std::vector<bool> visited(graph.size(), false);
        std::vector<int> distances(graph.size(), 0);
        std::queue<std::pair<int, int>> q;
        
        q.push({start_node, 0});
        visited[start_node] = true;
        int max_distance = 0;
        
        while (!q.empty()) {
            auto [current_node, current_distance] = q.front();
            q.pop();
            
            for (int neighbor : graph[current_node]) {
                if (!visited[neighbor] && canTransmit(current_node, neighbor, frequencies)) {
                    q.push({neighbor, current_distance + 1});
                    visited[neighbor] = true;
                    distances[neighbor] = current_distance + 1;
                    max_distance = std::max(max_distance, current_distance + 1);
                }
            }
        }
        
        return max_distance;
    }
};

// Test function
void testCalculateMax() {
    Solution solution;
    
    // Test Case 1 (from the example)
    {
        std::vector<int> network_from = {1, 2, 3};
        std::vector<int> network_to = {2, 3, 4};
        std::vector<int> frequencies = {1, 2, 3, 1};
        int result = solution.calculateMax(4, network_from, network_to, frequencies);
        std::cout << "Test Case 1: Expected 2, Got " << result << std::endl;
        assert(result == 2);
    }
    
    // Test Case 2: No transmission possible
    {
        std::vector<int> network_from = {1, 2};
        std::vector<int> network_to = {2, 3};
        std::vector<int> frequencies = {1, 3, 5, 7};
        int result = solution.calculateMax(4, network_from, network_to, frequencies);
        std::cout << "Test Case 2: Expected 0, Got " << result << std::endl;
        assert(result == 0);
    }
    
    // Test Case 3: Longer network with multiple paths
    {
        std::vector<int> network_from = {1, 2, 3, 4};
        std::vector<int> network_to = {2, 3, 4, 5};
        std::vector<int> frequencies = {1, 2, 3, 4, 5};
        int result = solution.calculateMax(5, network_from, network_to, frequencies);
        std::cout << "Test Case 3: Expected 4, Got " << result << std::endl;
        assert(result == 4);
    }
    
    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testCalculateMax();
    return 0;
}