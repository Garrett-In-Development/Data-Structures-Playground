from graph import Graph

DIRECTED = True
EXIT = 10

def main():

    graph1 = Graph(DIRECTED)

    response = -1

    while(response < EXIT):
        print("Graph Interface:\n \
              1\tAdd a node.\n \
              2\tAdd an edge.\n \
              3\tRemove a node.\n \
              4\tRemove an edge.\n \
              5\tList Nodes.\n \
              6\tList edges.\n \
              7\tAttempt Topological Ordering.\n \
              8\tRun BFS\n \
              9\tRun DFS\n \
              10\tExit.\n")
        try:
            response = int(input("Pick an Option: "))
        except ValueError:
            print("That is not an option")
            continue

        match response:

            case 1:
                node_name = input("Name this node: ")
                if graph1.add_node(node_name):
                    print("Node added to the graph")
                else:
                    print("Error adding node to graph or node already exists!")

            case 2:
                node1 = input("Name of first node: ")
                node2 = input("Name of second node: ")
                weight = input("Weight for connection (for unwieghted enter 1): ")

                graph1.add_edge(node1, node2, weight)

            case 3:
                node = input("Enter the name of the node you want to remove: ")
                removed_node = graph1.remove_node(node)
                if removed_node is None:
                    print(node, "was not in the graph.")
                else:
                    print(removed_node.get_value(), "has been removed.")

            case 4:
                node1 = input("Enter the first node in the edge: ")
                node2 = input("Enter the second node in the edge: ")

                i = graph1.get_node(node1)
                j = graph1.get_node(node2)

                if i is None or j is None:
                    print("Edge is not in the graph")
                else:
                    if not graph1.remove_edge(i, j):
                        print("Edge was not in the graph")

            case 5:
                graph1.list_nodes()

            case 6:
                graph1.list_edges()

            case 7:
                top_order = graph1.topilogical_ordering()
                for node in top_order:
                    print(node.get_value())

            case 10:
                exit

            case _:
                print("Not implemented...")


if __name__ == "__main__":
    main()
