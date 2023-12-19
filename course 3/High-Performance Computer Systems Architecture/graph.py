import networkx as nx
import matplotlib.pyplot as plt

# Заданный граф в виде списка смежности
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': ['C'],
    'E': ['F'],
    'F': ['G', 'H'],
    'G': ['E'],
    'H': []
}

# Создание направленного графа из списка смежности
G = nx.DiGraph(graph)

# Создание BFS-дерева
bfs_tree = nx.bfs_tree(G, 'A')

# Рассчитываем позиции узлов для упорядоченного представления по уровням
pos = nx.shell_layout(bfs_tree)

# Рисование графа
nx.draw_networkx(bfs_tree, pos, with_labels=True, node_size=700, node_color='skyblue', font_size=10, font_color='black', font_weight='bold', edge_color='gray', linewidths=1, alpha=0.7)

# Отображение рисунка
plt.show()
