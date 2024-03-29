import csv
from itertools import combinations

from graph import Graph

MOVIE_TITLE_TYPE = "movie"
MOVIE_COLUMNS = ["tconst", "titleType", "primaryTitle"]
PRINCIPALS_COLUMNS = ["nconst", "category"]
MOVIES_DATA_PATH = "./datasets/title-basics-f.tsv"
ACTORS_DATA_PATH = "./datasets/title-principals-f.tsv"
ACTORS_NAMES_PATH = "./datasets/name-basics-f.tsv"

def read_data(movies_file, actors_file, actors_name_file):
    print("Reading data")
    movies_by_id = {}
    with open(movies_file, "r", newline="", encoding="utf-8") as file1:
        reader = csv.DictReader(file1, delimiter="\t")
        for row in reader:
            if row["titleType"] == MOVIE_TITLE_TYPE:
                movies_by_id[row['tconst']] = row

    actors_ids = set()
    actors_by_movie = {m: set() for m in movies_by_id.keys()}
    with open(actors_file, "r", newline="", encoding="utf-8") as file2:
        reader = csv.DictReader(file2, delimiter="\t")
        for row in reader:
            if row["tconst"] in actors_by_movie:
                actors_by_movie[row["tconst"]].update([row["nconst"]])
                actors_ids.update([row["nconst"]])

    actor_names_by_id = {}
    with open(actors_name_file, "r", newline="", encoding="utf-8") as file2:
        reader = csv.DictReader(file2, delimiter="\t")
        for row in reader:
            if row["nconst"] in actors_ids:
                actor_names_by_id[row["nconst"]] = row["primaryName"]

    return movies_by_id, actors_by_movie, actor_names_by_id

def load_graph(movies_by_id, actors_by_movie, actor_names_by_id) -> Graph:
    """
    Loads the graph
    :param movies_by_id: the movies data by id as dict
    :param actors_by_movie: the actors data by movie
    :param actor_names_by_id: the actors names by their ids
    :return: a Graph
    """
    graph = Graph()
    print("Loading graph")

    for movie_id in movies_by_id.keys():
        graph.add_vertex(movie_id,movies_by_id[movie_id]['primaryTitle'])
    
    for actor_id in actor_names_by_id.keys():
        #print(actor_id)
        #print(actor_names_by_id[actor_id])
        graph.add_vertex(actor_id, actor_names_by_id[actor_id], weighted = False)

    for movie_id in actors_by_movie.keys():
        for actor_id in actors_by_movie[movie_id]:
          #print(movies_by_id[movie_id]['primaryTitle'])
          if actor_names_by_id.get(actor_id, "ERROR")!= "ERROR":
            #print(actor_names_by_id[actor_id]['primaryName'])
            graph.add_edge(movie_id,actor_id, weighted = False)

    return graph
# Define the paths to the datasets

movies_by_id, actors_by_movie, actor_names_by_id = read_data(MOVIES_DATA_PATH, ACTORS_DATA_PATH, ACTORS_NAMES_PATH)
graph = load_graph(movies_by_id, actors_by_movie, actor_names_by_id)
#graph.print_graph()
graph.load_components_data_b()

#graph.get_separation_grade(vertex1,vertex2) => Ejercicio 2 => BFS desde vertex1 hasta 
                                                # encontrar vertex2, y ese numero dividirlo
                                                #  por 2 (por cada pelicula hay 2 saltos)
#graph.kevin_bacon_number() => Ejercicio 3 => Sería replicar el Ejercicio 2 pero para todos
                                              #  los actores, y quedarse con el máximo
