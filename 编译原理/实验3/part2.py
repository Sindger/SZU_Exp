# -*- coding: utf-8 -*-
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
        self.current_node=None

    def production_split(self):
        for i in range(len(self.production)):
            self.production_tuples.append(self.production[i].split("->"))
        return self.production_tuples

    def create_tree(self, index, tree):
        if index == len(self.production_tuples):
            return
        elif index == 0:
            tree.insert_date(self.production_tuples[index][0])
            child = self.production_tuples[index][1]
            for i in child:
                if i=="'":
                    child=tree.get_child()
                    child[-1].data=child[-1].data+"'"
                else:
                    child_node = tree_node(i)
                    tree.add_child(child_node)
        else:
            self.current_parent = self.production_tuples[index][0]
            self.current_child = self.production_tuples[index][1]
            self.dfs(tree)
            if self.current_node!=None:
                for i in self.current_child:
                    if i == "'":
                        child = self.current_node.get_child()
                        child[-1].data = child[-1].data + "'"
                    else:
                        child_node = tree_node(i)
                        self.current_node.add_child(child_node)
                self.current_node=None
        self.create_tree(index+1,tree)

    def dfs(self, tree):
        if tree.get_data()==None:
            return
        child=tree.get_child()
        length=len(child)
        for i in range(0,length):
            if child[i].get_data()==self.current_parent:
                if child[i].get_child()==[]:
                    self.current_node=child[i]
                else:
                    self.dfs(child[i])
            else:
                self.dfs(child[i])

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

    def get_grammar_tree(self):
        return self.grammar_tree

class parse:
    def __init__(self,parse_str):
        self.parse_str=parse_str #输入的字符串
        self.parse_list=[] #输出的产生式序列
        self.E() #开始解析

    def get_production(self):
        for i in range(len(self.parse_str)):
            if self.parse_str[i]=="i" and i!=len(self.parse_str)-1:
                self.T()
            elif self.parse_str[i]=="+":
                self.E_()
            elif self.parse_str[i]=="*":
                self.T_()
            elif self.parse_str[i]=="i" and i==len(self.parse_str)-1:
                self.F()

    def E(self):
        self.parse_list.append("E->TE'")
        self.get_production()

    def E_(self):
        self.parse_list.append("E'->+TE'")

    def T(self):
        self.parse_list.append("T->FT'")
        self.parse_list.append("F->i")

    def T_(self):
        self.parse_list.append("T'->*FT'")

    def F(self):
        self.parse_list.append("F->i")

    def print_parse(self):
        print("G[E]:")
        for i in self.parse_list:
            print(i)

if __name__=="__main__":
    parse_str=input("请输入需要解析的字符串:")
    P=parse(parse_str)
    P.print_parse()
    parse_list=P.parse_list
    print(parse_list)
    tree=tree_node()
    P2T=production_to_tree(parse_list)
    P2T.create_tree(0,tree)
    P2T.print_tree(tree)
    grammar_tree=P2T.get_grammar_tree()
    print("语法树为:",grammar_tree)