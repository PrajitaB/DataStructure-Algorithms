1  # BFS on graph
def bfs(graph, start_node):
    visited = []
    queue = [start_node]
    while queue:
        current_node = queue.pop(0)

        if current_node not in visited:
            visited.append(current_node)
            print(current_node, end=" ")

            for neighbor in graph[current_node]:
                if neighbor not in visited:
                    queue.append(neighbor)

def graph_input():
    graph = {}
    nodes = int(input("Enter the number of nodes: "))
    
    for i in range(nodes):
        node = input(f"Enter the name of node {i + 1}: ").strip()
        neighbors = input(f"Enter the neighbors of {node}: ").strip().split()
        graph[node] = neighbors

    return graph

if __name__ == "__main__":
    print("Graph Input")
    graph = graph_input()
    start_node = input("Enter the starting node: ").strip()
    print("\nBFS Traversal")
    bfs(graph, start_node)