class vertex:
    def __init__(self,name=""):
        self.name=name
        self.edges={}

    def get_name(self):
        return self.name

    def get_neighbors(self):
        return self.edges.keys()

    def add_neighbor(self,neighbor,cost):
        self.edges[neighbor]=cost

    def remove_neighbor(self,neighbor):
        if neighbor in self.edges.keys():
            del self.edges[neighbor]

    def get_cost(self,neighbor):
        if neighbor in self.edges.keys():
            return self.edges[neighbor]
        return -1

    def __str__(self):
        res = str(self.name) + \
              '\tadjacency: ' + str([(k, v) for (k, v) in self.edges.items()])
        return res

class edge:
    def __init__(self,start,end,cost):
        self.start=start
        self.end=end
        self.cost=cost

class simplegraph(vertex,edge):
    def __init__(self):
        self.edge_num=0
        self.vertex_num=0
        self.vertexlist={}
        self.edgelist= {}

    def add_vertex(self,v):
        self.vertex_num+=1
        self.vertexlist[v]=vertex(v)

    def add_edge(self,v1,v2,cost):
        if v1 not in self.vertexlist:
            self.add_vertex(v1)
        if v2 not in self.vertexlist:
            self.add_vertex(v2)
        if edge(v1,v2,cost) not in self.edgelist:
            self.edgelist[self.edge_num]=edge(v1,v2,cost)
            self.vertexlist[v1].add_neighbor(v2,cost)
            self.edge_num+=1

    def contains_vertex(self,v):
        for i in self.vertexlist:
            if i==v:
                return True
        return False

    def contains_edge(self,v1,v2,cost):
        for i in self.edgelist:
            if edge(v1,v2,cost)==i:
                return True
        return False

    def is_empty(self):
        if self.vertex_num==0:
            return  True
        return False

    def remove_vertex(self,v):
        if v in self.vertexlist:
            del self.vertexlist[v]
            self.vertex_num-=1

    def remove_edge(self,v1,v2):
        if v1 in self.vertexlist and v1 in self.vertexlist:
            self.vertexlist[v1].remove_neighbor(v1)
            self.edge_num-=1

    def is_neighbors(self,v1,v2):
        if v2 in self.vertexlist[v1].get_neighbors():
            return True
        return False

    def is_reachable(self,v1,v2):
        if self.vertexlist[v1].get_cost(v2)==-1:
            return False
        return True

    def clear_all(self):
        del self.vertexlist
        del self.edgelist
        self.vertex_num=0
        self.edge_num=0

    def __str__(self):
        res = 'numEdge = ' + str(self.edge_num) + '\n' + \
              'numVertex = ' + str(self.vertex_num) + '\n'
        for v in self.vertexlist.values():
            res += str(v) + '\n'
        return res

if __name__=="__main__":
    g=simplegraph()
    for i in ['V0', 'V1', 'V2', 'V3', 'V4', 'V5']:
        g.add_vertex(i)
    print(g)
    g.add_edge('V0', 'V1', 5)
    g.add_edge('V0', 'V5', 2)
    g.add_edge('V1', 'V2', 4)
    g.add_edge('V2', 'V3', 9)
    g.add_edge('V3', 'V4', 7)
    g.add_edge('V3', 'V5', 3)
    g.add_edge('V4', 'V0', 1)
    g.add_edge('V5', 'V4', 1)
    g.add_edge('V5', 'V5', 8)
    print(g,end="")
    print(g.is_neighbors('V1','V2'))
    print(g.contains_vertex('V2'))
    print(g.contains_edge('V1','V3',5))
    g.remove_vertex('V1')
    g.remove_edge('V4','V0')
    print(g,end="")
    print(g.is_reachable('V0','V5'))
    print(g.is_empty())
    g.clear_all()
    print(g.is_empty())