from collections import deque
import random
import networkx as nx
import matplotlib.pyplot as plt

def visualize_graph_with_matching(graph, matching_edges):
    G = nx.Graph(graph)
    G = nx.relabel_nodes(G, lambda x: str(x))

    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, font_weight='bold', node_size=700)

    matching_edges = [(str(u), str(v)) for u, v in matching_edges]
    nx.draw_networkx_edges(G, pos, edgelist=matching_edges, edge_color='r', width=2)
    plt.savefig("image.png")
    plt.show()
def generate_random_graph(num_vertices, num_edges):
    graph = {i: [] for i in range(num_vertices)}
    edges = set()

    while len(edges) < num_edges:
        u, v = random.sample(range(num_vertices), 2)
        if u > v:
            u, v = v, u
        edges.add((u, v))

    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)

    return graph

def edmonds():
    for i in range(n):
        if match[i] == -1:
            last_v = find_augment_path(i)
            if last_v != -1:
                alternate_path(i, last_v)

def find_augment_path(root):
    visited = [False] * n
    queue = deque()
    queue.append(root)

    while queue:
        v = queue.popleft()
        for to in g[v]:
            if not visited[to]:
                if base[v] == base[to] or match[v] == to:
                    continue
                if to == root or (match[to] != -1 and p[match[to]] != -1):
                    cur_base = lca(v, to)
                    blossom = [False] * n
                    mark_path(v, cur_base, to)
                    mark_path(to, cur_base, v)
                    for i in range(n):
                        if blossom[base[i]]:
                            base[i] = cur_base
                            if not visited[i]:
                                visited[i] = True
                                queue.append(i)
                elif p[to] == -1:
                    p[to] = v
                    if match[to] == -1:
                        return to
                    to = match[to]
                    visited[to] = True
                    queue.append(to)
    return -1

def lca(a, b):
    used = [False] * n
    while True:
        a = base[a]
        used[a] = True
        if match[a] == -1:
            break
        a = p[match[a]]

    while True:
        b = base[b]
        if used[b]:
            return b
        b = p[match[b]]

def mark_path(v, b, children):
    while base[v] != b:
        blossom[base[v]] = True
        blossom[base[match[v]]] = True
        p[v] = children
        children = match[v]
        v = p[match[v]]

def alternate_path(v):
    while v != -1:
        pv = p[v]
        ppv = match[pv]
        match[v] = pv
        match[pv] = v
        v = ppv

def find_path(root):
    global used, p, base, blossom
    used = [False] * n
    p = [-1] * n
    base = list(range(n))

    used[root] = True
    queue = deque([root])

    while queue:
        v = queue.popleft()
        for to in g[v]:
            if base[v] == base[to] or match[v] == to:
                continue
            if to == root or (match[to] != -1 and p[match[to]] != -1):
                cur_base = lca(v, to)
                blossom = [False] * n
                mark_path(v, cur_base, to)
                mark_path(to, cur_base, v)
                for i in range(n):
                    if blossom[base[i]]:
                        base[i] = cur_base
                        if not used[i]:
                            used[i] = True
                            queue.append(i)
            elif p[to] == -1:
                p[to] = v
                if match[to] == -1:
                    return to
                to = match[to]
                used[to] = True
                queue.append(to)
    return -1


# Генерация случайного графа
n = 6
num_edges = 7
g = generate_random_graph(n, num_edges)
print("Структура графа:")
for vertex in g:
    print(f"{vertex}: {g[vertex]}")

MAXN = 1000
match = [-1] * MAXN
p = [-1] * MAXN
base = list(range(MAXN))
used = [False] * MAXN
blossom = [False] * MAXN

for i in range(n):
    if match[i] == -1:
        v = find_path(i)
        while v != -1:
            pv = p[v]
            ppv = match[pv]
            match[v] = pv
            match[pv] = v
            v = ppv

print("Максимальное паросочетание:")
for i in range(n):
    if match[i] != -1:
        print(f"({i}, {match[i]})")


visualize_graph_with_matching(g, [(i, match[i]) for i in range(n) if match[i] != -1])
