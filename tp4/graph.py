import os
import pickle
import time
from typing import Any, List, Optional

from tqdm import tqdm

from algorithms import Algorithms


class Graph:
    """
    Graph class
    """
    def __init__(self):
        self._graph = {}
        self._min_component = {}
        self._max_component = {}
        self._second_max_component = {}
        self._components = []
        self._distances = {}

    def add_vertex(self, vertex: str, data: Optional[Any]=None, weighted=True) -> None:
        """
        Adds a vertex to the graph
        :param vertex: the vertex name
        :param data: data associated with the vertex
        """
        if vertex not in self._graph:
            self._graph[vertex] = {'data': data, 'neighbors': {}}
            if weighted:
              self._distances[vertex] = {}

    def add_edge(self, vertex1: str, vertex2: str, data: Optional[Any]=None, weighted=True) -> None:
        """
        Adds an edge to the graph
        :param vertex1: vertex1 key
        :param vertex2: vertex2 key
        :param data: the data associated with the vertex
        """
        if not vertex1 in self._graph or not vertex2 in self._graph:
            raise ValueError("The vertexes do not exist")
        self._graph[vertex1]['neighbors'][vertex2] = data
        self._graph[vertex2]['neighbors'][vertex1] = data
        if weighted:
          self._distances[vertex1][vertex2] = len(data)
          self._distances[vertex2][vertex1] = len(data)



    def get_neighbors(self, vertex) -> List[str]:
        """
        Get the list of vertex neighbors
        :param vertex: the vertex to query
        :return: the list of neighbor vertexes
        """
        if vertex in self._graph:
            return list(self._graph[vertex]['neighbors'].keys())
        else:
            return []

    def get_neighbors_component(self, vertex) -> List[str]:
        """
        Get the list of vertex neighbors in the max component
        :param vertex: the vertex to query
        :return: the list of neighbor vertexes
        """
        if vertex in self._max_component:
            return list(self._max_component[vertex]['neighbors'])
        else:
            return []

    def get_vertex_data(self, vertex: str) -> Optional[Any]:
        """
        Gets  vertex associated data
        :param vertex: the vertex name
        :return: the vertex data
        """
        if self.vertex_exists(vertex):
            return self._graph[vertex]['data']
        else:
            return None

    def get_edge_data(self, vertex1: str, vertex2: str) -> Optional[Any]:
        """
        Gets the vertexes edge data
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: vertexes edge data
        """
        if self.edge_exists(vertex1, vertex2):
            return self._graph[vertex1]['neighbors'][vertex2]
        raise ValueError("The edge does not exist")

    def print_graph(self) -> None:
        """
        Prints the graph
        """
        for vertex, data in self._graph.items():
            print("Vertex:", vertex)
            print("Data:", data['data'])
            print("Neighbors:", data['neighbors'])
            print("")

    def vertex_exists(self, vertex: str) -> bool:
        """
        If contains a vertex
        :param vertex: the vertex name
        :return: boolean
        """
        return vertex in self._graph

    def edge_exists(self, vertex1: str, vertex2: str) -> bool:
        """
        If contains an edge
        :param vertex1: the vertex1 name
        :param vertex2: the vertex2 name
        :return: boolean
        """
        return vertex1 in self._graph and vertex2 in self._graph[vertex1]['neighbors']

    def get_connected_components(self):
        """
        Gets connected components
        """
        
        print("Connected comps qty: ", len(self._components))
        print("Max Component, length: ",len(self._max_component))
        print("Second Max Component, length: ",len(self._second_max_component))
        print("Content: ", self._second_max_component)
        print("Min Component, length: ",len(self._min_component))
        print("Content: ", self._min_component)

    def get_diameter(self):
      """
      Gets the diameter of the max component
      """
      diameter = 0
      start = time.time()
      for vertex in tqdm(self._max_component):
        lens = Algorithms.bfs(self, vertex)
        diameter = max(diameter,max(lens.values()))
        if time.time() - start >= 900: #15 minutos * 60 segundos
          print("Diameter: ",diameter)
          return
      print("Diameter: ",diameter)

    def get_min_paths_to_others(self, starting_vertex):
      distances = Algorithms.dijkstra(self._distances, starting_vertex)
      for vertex in distances.keys():
        if distances[vertex] == 491964765604:
          distances[vertex] = float('inf')
      print(distances)
      print("Total: ",len(distances))

    def get_min_paths_all_to_all(self):
      distances = Algorithms.johnson(self._distances)
      print(distances)
      print("Total: ",len(distances))

    def load_components_data(self):
      """
      Loads relevant connected components data of the graph
      """
      if os.path.exists('max_component_a.pickle'):
        print("Reading max component from pre-saved file")
        try:
          with open('max_component_a.pickle', 'rb') as file:
              self._max_component = pickle.load(file)
        except Exception:
          pass
      if os.path.exists('second_max_component_a.pickle'):
        print("Reading second max component from pre-saved file")
        try:
          with open('second_max_component_a.pickle', 'rb') as file:
              self._second_max_component = pickle.load(file)
        except Exception:
          pass
      if os.path.exists('min_component_a.pickle'):
        print("Reading min component from pre-saved file")
        try:
          with open('min_component_a.pickle', 'rb') as file:
              self._min_component = pickle.load(file)
        except Exception:
          pass
      if os.path.exists('components_a.pickle'):
        print("Reading components from pre-saved file")
        try:
          with open('components_a.pickle', 'rb') as file:
              self._components = pickle.load(file)
        except Exception:
          pass

      if not os.path.exists('max_component_a.pickle') or not os.path.exists('second_max_component_a.pickle') or not os.path.exists('min_component_a.pickle') or not os.path.exists('components_a.pickle'):
        visited_nodes = set()
          
        min_len = float('inf')

        for vertex in tqdm(self._graph):
          if vertex not in visited_nodes:
            visited_from_component = {}

            Algorithms.dfs(self, vertex, visited_from_component)

            if len(visited_from_component) > len(self._max_component):
              self._max_component = visited_from_component

            if len(visited_from_component) < len(self._max_component) and len(visited_from_component) > len(self._second_max_component):
              self._second_max_component = visited_from_component

            if len(visited_from_component) < min_len:
              min_len = len(visited_from_component)
              self._min_component = visited_from_component

            visited_nodes = visited_nodes.union(visited_from_component)
            
            self._components.append(visited_from_component)

        with open('max_component_a.pickle', 'wb') as file:
          pickle.dump(self._max_component, file)
        with open('second_max_component_a.pickle', 'wb') as file:
          pickle.dump(self._second_max_component, file)
        with open('min_component_a.pickle', 'wb') as file:
          pickle.dump(self._min_component, file)
        with open('components_a.pickle', 'wb') as file:
          pickle.dump(self._components, file)

    def load_components_data_b(self):
      """
      Loads relevant connected components data of the graph B
      """
      if os.path.exists('max_component_b.pickle'):
        print("Reading max component from pre-saved file")
        try:
          with open('max_component_b.pickle', 'rb') as file:
              self._max_component = pickle.load(file)
        except Exception:
          pass
      if os.path.exists('components_b.pickle'):
        print("Reading components from pre-saved file")
        try:
          with open('components_b.pickle', 'rb') as file:
              self._components = pickle.load(file)
        except Exception:
          pass

      if not os.path.exists('max_component_b.pickle') or not os.path.exists('components_b.pickle'):
        visited_nodes = set()

        for vertex in tqdm(self._graph):
          if vertex not in visited_nodes:
            visited_from_component = {}

            Algorithms.bfs_b(self, vertex, visited_from_component)

            if len(visited_from_component) > len(self._max_component):
              self._max_component = visited_from_component

            visited_nodes = visited_nodes.union(visited_from_component)
            
            self._components.append(visited_from_component)

        with open('max_component_b.pickle', 'wb') as file:
          pickle.dump(self._max_component, file)
        with open('components_b.pickle', 'wb') as file:
          pickle.dump(self._components, file)
