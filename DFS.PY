1  # DFS on graph
def dfs(graph, start_node, visited=None):
    if visited is None:
        visited = set()
    
    visited.add(start_node)
    print(start_node, end=" ")
    
    for neighbor in graph[start_node]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)

def get_user_input():
    graph = {}
    num_nodes = int(input("Enter the number of nodes: "))
    
    for i in range(num_nodes):
        node = input(f"Enter the name of node {i + 1}: ").strip()
        neighbors = input(f"Enter the neighbors of {node}: ").strip().split()
        graph[node] = neighbors

    return graph

if __name__ == "__main__":
    print("Graph Input")
    graph = get_user_input()
    start_node = input("Enter the starting node for DFS: ").strip()
    print("\nDFS Traversal")
    dfs(graph, start_node)