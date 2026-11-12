package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.User;

import java.util.*;
import java.util.stream.Collectors;

public class GraphService {
    /**
     * Default constructor
     */
    public GraphService() {

    }

    /**
     * Builds an adjacency list representation of the social network graph
     * @param users the list of users
     * @param friendships the list of friendships
     * @return a map where each user ID maps to the list of IDs of their friends
     */
    public static Map<Long, List<Long>> buildAdjacencyList(List<User> users, List<Friendship> friendships) {
        Map<Long, List<Long>> adjacencyList = users.stream().collect(Collectors.toMap(User::getId, user -> new ArrayList<>()));

        for (Friendship friendship: friendships) {
            Long user1Id = friendship.getIdUser1();
            Long user2Id = friendship.getIdUser2();

            if (adjacencyList.containsKey(user1Id) && adjacencyList.containsKey(user2Id)) {
                adjacencyList.get(user1Id).add(user2Id);
                adjacencyList.get(user2Id).add(user1Id);
            }
        }

        return adjacencyList;
    }

    /**
     * Calculates the total number of connected components (communities) in the network graph
     * @param users the list of users
     * @param friendships the list of friendships
     * @return the total number of communities
     */
    public static int getNumberOfComunities(List<User> users, List<Friendship> friendships) {
        Map<Long, List<Long>> adjacencyList = buildAdjacencyList(users, friendships);
        Set<Long> visited = new HashSet<>();
        return (int) adjacencyList.keySet().stream().filter(visited::add).peek(userId -> dfs(userId, adjacencyList, visited, null)).count();
    }

    /**
     * Performs a Depth-First Search (DFS) traversal to discover all nodes in a connected component
     * @param startNode the starting user ID for traversal
     * @param adjacencyList graph representation of user connections
     * @param visited set tracking visited user IDs
     * @param component optional list populated with discovered user IDs in the current component (can be {@code null})
     */
    public static void dfs(Long startNode, Map<Long, List<Long>> adjacencyList, Set<Long> visited, List<Long> component) {
        visited.add(startNode);
        if (component != null) {
            component.add(startNode);
        }

        for (Long nodeId: adjacencyList.get(startNode)) {
            if (!visited.contains(nodeId)) {
                dfs(nodeId, adjacencyList, visited, component);
            }
        }
    }

    /**
     * Computes the maximum shortest path distance (graph diameter) within a given component using Breadth-First Search (BFS)
     * @param component list of user IDs in the component
     * @param adjacencyList graph representation of user connections
     * @return the longest path length found in the component
     */
    public static int getLongestPathInComponent(List<Long> component, Map<Long, List<Long>> adjacencyList) {
        int maxDist = 0;

        for (Long startNode: component) {
            Map<Long, Integer> distances = new HashMap<>();
            Queue<Long> queue = new LinkedList<>();

            queue.add(startNode);
            distances.put(startNode, 0);

            while (!queue.isEmpty()) {
                Long currentNode = queue.poll();
                int dist = distances.get(currentNode);
                maxDist = Math.max(maxDist, dist);

                for (Long neighbour: adjacencyList.get(currentNode)) {
                    if (!distances.containsKey(neighbour)) {
                        distances.put(neighbour, dist + 1);
                        queue.add(neighbour);
                    }
                }
            }
        }
        return maxDist;
    }

    /**
     * Identifies the most sociable comunity in the network, defined as the connected component
     * with the longest simple path (maximum diameter)
     * @param users the list of users
     * @param friendships the list of friendships
     * @return a list of {@link Long} Ids belonging to the most sociable community
     */
    public static List<Long> getMostSociableComunity(List<User> users, List<Friendship> friendships) {
        Map<Long, List<Long>> adjacencyList = buildAdjacencyList(users, friendships);
        Set<Long> visited = new HashSet<>();

        return adjacencyList.keySet().stream()
                .filter(visited::add)
                .map(userId -> {
                    List<Long> component = new ArrayList<>();
                    dfs(userId, adjacencyList, visited, component);
                    return component;
                }).max(Comparator.comparingInt(component -> getLongestPathInComponent(component, adjacencyList)))
                .orElse(Collections.emptyList());
    }
}