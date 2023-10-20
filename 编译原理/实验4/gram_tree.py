import grammer_identify

class tree_node:
    def __init__(self,data=None):
        self.child=[]
        self.data=data

    def insert_date(self,data):
        self.data=data

    def add_child(self,child):
        self.child.append(child)

    def get_data(self):
        return self.data

    def get_child(self):
        return self.child

class production_to_tree:
    def __init__(self,production):
        self.production=production
        self.production_tuples=[]
        self.production_split()
        self.current_parent=None
        self.current_child=None
        self.grammar_tree=""
        self.leaf=""

    def production_split(self):
        for i in range(len(self.production)):
            self.production_tuples.append(self.production[i].split("->"))
        return self.production_tuples

    def create_tree(self,index,tree):
        if index==len(self.production_tuples):
            return
        elif index==0:
            tree.insert_date(self.production_tuples[index][0])
            child=self.production_tuples[index][1]
            for i in child:
                child_node=tree_node(i)
                tree.add_child(child_node)
        else:
            self.current_parent=self.production_tuples[index][0]
            self.current_child=self.production_tuples[index][1]
            self.dfs(tree)
        self.create_tree(index+1,tree)

    def dfs(self,tree):
        if tree.get_data()==None:
            return
        child=tree.get_child()
        for i in child:
            date=i.get_data()
            if date==self.current_parent:
                if i.get_child()==[]:
                    for j in self.current_child:
                        child_node=tree_node(j)
                        i.add_child(child_node)
                else:
                    self.dfs(i)
            else:
                self.dfs(i)

    def print_tree(self,tree):
        if tree.get_data()==None:
            return
        self.grammar_tree+=tree.get_data()
        child=tree.get_child()
        if child!=[]:
            self.grammar_tree+="("
            for i in child:
                self.print_tree(i)
            self.grammar_tree+=")"
        else:
            self.leaf+=tree.get_data()

    def get_grammar_tree(self):
        return self.grammar_tree

    def get_leaf(self,tree):
        return self.leaf

def get_tree(production):
    tree = tree_node()
    grammar_tree = production_to_tree(production)
    grammar_tree.create_tree(0, tree)
    grammar_tree.print_tree(tree)
    print(grammar_tree.get_grammar_tree())
    print(grammar_tree.get_leaf(tree))

if __name__=="__main__":
    input=input("")
    input=input+".txt"
    production=grammer_identify.identify(input)
    print(production)
    tree=tree_node()
    grammar_tree=production_to_tree(production)
    grammar_tree.create_tree(0,tree)
    grammar_tree.print_tree(tree)
    print(grammar_tree.get_grammar_tree())
    print(grammar_tree.get_leaf(tree))