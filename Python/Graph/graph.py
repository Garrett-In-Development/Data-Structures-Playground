from node import Node

class Graph:

    def __init__(self, directed=False):
        '''
        Constructor for the Graph class

        verticies: dictionary that stores vertices
                   and their edges

        size: the number of verticies within the graph
        '''
        self.__graph = dict()
        self.__directed = directed
        self.__size = 0

    def size(self):
        """
        Returns __size
        """
        return self.__size

    def get_node(self, node_name):
        for node in self.__graph.keys():
            try:
                if node_name == node.get_value():
                    return node
            except TypeError:
                continue

        return None

    def add_node(self, node):
        if isinstance(node, Node):
            new_node = node
        else:
            new_node = self.get_node(node)
            if new_node is None:
                new_node = Node(node)
            else:
                return False

        self.__graph.update({new_node : []})
        self.__size += 1

        return True

    def add_edge(self, node, node_prime, weight):
        if isinstance(node, Node):
            node1 = node
        else:
            node1 = self.get_node(node)
            if node1 is None:
                node1 = Node(node)

        if isinstance(node_prime, Node):
            node2 = node_prime
        else:
            node2 = self.get_node(node_prime)
            if node2 is None:
                node2 = Node(node_prime)

        if node1 not in self.__graph.keys():
            self.add_node(node1)

        if node2 not in self.__graph.keys():
            self.add_node(node2)

        edges1 = self.__graph.get(node1)
        if not (node2, weight) in edges1:
            edges1.append((node2, weight))
            self.__graph.update({node1 : edges1})

        if not self.__directed:
            edges2 = self.__graph.get(node2)
            if not (node1, weight) in edges2:
                edges2.append((node1, weight))
                self.__graph.update({node2 : edges2})

    def remove_node(self, node):
        if isinstance(node, Node):
            rem_node = node
        else:
            rem_node = self.get_node(node)

        if rem_node is None:
            return rem_node

        for node in self.__graph.keys():
            neighbors = self.__graph.get(node)
            for neighbor in neighbors:
                if neighbor[0] is rem_node:
                    neighbors.remove(neighbor)

        del self.__graph[rem_node]

        return rem_node

    def remove_edge(self, node1, node2):
        rem_node1 = None
        rem_node2 = None
        if isinstance(node1, Node):
            rem_node1 = self.get_node(node1.get_value())
        else:
            rem_node1 = self.get_node(node1)

        if isinstance(node2, Node):
            rem_node2 = self.get_node(node2.get_value())
        else:
            rem_node2 = self.get_node(node2)

        if rem_node1 is None or rem_node2 is None:
            return False

        for neighbor in self.__graph.get(rem_node1):
            if neighbor[0] == rem_node2:
                self.__graph.get(rem_node1).remove(neighbor)

        if not self.__directed:
            for neighbor in self.__graph.get(rem_node2):
                if neighbor[0] == rem_node1:
                    self.__graph.get(rem_node2).remove(neighbor)

        return True


    def read_graph(self, fileName):
        pass

    def list_nodes(self):
        for key in self.__graph.keys():
            print(key.get_value(), end=" ")
        print()

    def list_edges(self):
        for key in self.__graph.keys():
            connections = self.__graph.get(key)
            for connection in connections:
                print(key.get_value(), f"{connection[1]}-->", connection[0].get_value())

    def print_graph(self):
        print("{")
        for key in self.__graph.keys():
            connections = self.__graph.get(key)
            print("{", key.get_value(), "-> [", end=" ")
            for connection in connections:
                print(connection[0].get_value(), end=" ")
            print("]", end=" ")
            print("},")
        print("}")

    def bfs(self, node):
        visited_nodes = []
        edges = []
        queue = []

        queue.append(node)
        visited_nodes.append(node)

        while len(queue) != 0:
            vertex = queue.pop(0)
            print("Visiting", vertex.get_value())
            for neighbor in self.__graph.get(vertex):
                if neighbor[0] not in visited_nodes:
                    edges.append((vertex, neighbor[0]))
                    queue.append(neighbor[0])
                    visited_nodes.append(neighbor[0])


        for edge in edges:
            print(edge[0].get_value(), " -- ", edge[1].get_value())

    def dfs_search(self, node):
        visited_nodes = []
        node1 = self.get_node(node)
        if node1 is None:
            return None
        return self.__dfs_helper(node1, visited_nodes)

    def __dfs_helper(self, node, visited_nodes):
        visited_nodes.append(node)
        print("Visited", node.get_value())
        for neighbor in self.__graph.get(node):
            if neighbor[0] not in visited_nodes:
                self.dfs_helper(neighbor[0], visited_nodes)

        return visited_nodes


    def topilogical_ordering(self):

        ret_val = []
        queue = []

        if not self.__directed:
            print("This is an undirected graph")
            return []

        else:

            # First thing we need to do is create the in-degree array
            n_deg = {}
            for node in self.__graph.keys():
                if node not in n_deg.keys():
                    n_deg.update({node : 0})
                else:
                    for connection in self.__graph.get(node):
                        if connection[0] not in n_deg.keys():
                            n_deg.update({connection[0] : 1})
                        else:
                            incoming = n_deg.get(connection[0])
                            n_deg.update({connection[0] : incoming + 1})

            for node in self.__graph.keys():
                if n_deg.get(node) == 0:
                    queue.append(node)

            # Now that we have the In-Degree Array, we do the topological ordering
            while(len(queue) != 0):
                node = queue.pop(0)
                ret_val.append(node)
                for neighbor in self.__graph.get(node):
                    in_deg = n_deg.get(neighbor[0])
                    n_deg.update({neighbor[0] : in_deg - 1})
                    if in_deg - 1 == 0:
                        queue.append(neighbor[0])

        return ret_val

    def shortest_path(self, source, end, method="dijkstra"):
        distances = dict()
        for node in self.graph.keys():
            distances.update({node : 999})
