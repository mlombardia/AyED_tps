import fibonacci_heap_mod
from tqdm import tqdm


class Algorithms:

  def dfs(graph, vertex, visited_nodes):

    stack = []

    stack.append(vertex)

    while len(stack) != 0:
      vertex = stack.pop()

      if vertex not in visited_nodes:
        visited_nodes[vertex] = {'data': graph.get_vertex_data(vertex), 'neighbors': graph.get_neighbors(vertex)}
      
      for vert in graph.get_neighbors(vertex):
        if vert not in visited_nodes.keys():
          stack.append(vert)

  def dfs_b(graph, vertex, visited_nodes):

    stack = []

    stack.append(vertex)

    while len(stack) != 0:
      vertex = stack.pop()

      if vertex not in visited_nodes:
        visited_nodes[vertex] = {'neighbors': graph.get_neighbors(vertex)}
      
      for vert in graph.get_neighbors(vertex):
        if vert not in visited_nodes.keys():
          stack.append(vert)

  def bfs(graph, vertex):

    queue = []

    queue.append(vertex)
    visited_nodes = set()

    visited_nodes.add(vertex)

    all_distances = { vertex: 0 }

    while len(queue) != 0:
      vertex = queue.pop(0)
      distance = all_distances[vertex] + 1

      for vert in graph.get_neighbors_component(vertex):
        if vert not in visited_nodes:
          visited_nodes.add(vert)
          all_distances[vert] = distance
          queue.append(vert)

    return all_distances
  
  def bfs_b(graph, vertex, visited_nodes):

    queue = []

    queue.append(vertex)

    visited_nodes[vertex] = {'neighbors': graph.get_neighbors(vertex)}

    while len(queue) != 0:
      vertex = queue.pop(0)

      for vert in graph.get_neighbors_component(vertex):
        if vert not in visited_nodes.keys():
          visited_nodes[vert] = {'neighbors': graph.get_neighbors(vert)}
          queue.append(vert)

  def dijkstra(graph,starting_vertex):
    distances = {vertex: len(graph)*len(graph) for vertex in graph} # len*len = 491964765604 para hacer un numero suficientemente largo (fibo heap no me admite float('inf'))
    distances[starting_vertex] = 0

    heap = fibonacci_heap_mod.Fibonacci_heap()

    heap_entries = {}

    for vertex in graph:
      heap_entries[vertex] = heap.enqueue(vertex,distances[vertex])

    while heap.m_size > 0:
      curr = heap.dequeue_min()

      for neighbor, weight in graph[curr.get_value()].items():
        candidate_distance = distances[curr.get_value()] + weight
        if candidate_distance < distances[neighbor]:
          distances[neighbor] = candidate_distance
          heap.decrease_key(heap_entries[neighbor],candidate_distance)
    
    return distances
  
  def johnson(graph):
    extra_vertex = 'extra_vertex'
    graph[extra_vertex] = {vertex: 0 for vertex in graph}

    distances_from_extra = Algorithms.dijkstra(graph, extra_vertex)
  
    for vertex in tqdm(graph):
      for neighbor in graph[vertex]:
        graph[vertex][neighbor] += distances_from_extra[vertex] - distances_from_extra[neighbor]

    final_distances = {vertex: {} for vertex in graph}

    for vertex in tqdm(graph):
      distances_from_vertex = Algorithms.dijkstra(graph, vertex)
      
      for neighbor,weight in tqdm(distances_from_vertex.items()):
        final_distances[vertex][neighbor] = weight - (distances_from_extra[vertex] - distances_from_extra[neighbor])
        
    return final_distances
