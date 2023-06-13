from tqdm import tqdm

class Algorithms:

  def dfs(graph, vertex, visited_nodes):

    stack = []

    stack.append(vertex)

    while len(stack) != 0:
      vertex = stack.pop()

      if vertex not in visited_nodes:
        visited_nodes.add(vertex)
      
      for vert in graph.get_neighbors(vertex):
        if vert not in visited_nodes:
          stack.append(vert)

  def bfs(graph, vertex, visited_nodes):

    queue = []

    queue.append(vertex)
    visited_nodes.add(vertex)

    while len(queue) != 0:
      vertex = stack.pop(0)

      for vert in graph.get_neighbors(vertex):
        if vert not in visited_nodes:
          visited_nodes.add(vert)
          queue.append(vert)
      
