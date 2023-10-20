# -*- coding: utf-8 -*-
import grammer_identify
from prettytable import PrettyTable

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
        self.analysis_stack=[]
        self.parse_stack=[]
        self.parse_str=parse_str
        self.parse_list=[]
        self.table={}
        self.analysis_stack.append("#")
        self.SET_forecast_table()

    def get_production(self):
        self.analysis_stack.append("E")
        print("分析过程如下:")
        while self.parse_stack[0]!="#":
            print("分析栈:", self.analysis_stack, end=" ")
            production = self.table[self.analysis_stack.pop()][self.parse_stack[0]]
            print("剩余分析串:",self.parse_stack,end=" ")
            print("产生式:",production)
            self.parse_list.append(production)
            left, right = production.split("->")
            stack = []
            for i in right:
                if i == "'":
                    stack[-1] = stack[-1] + i
                else:
                    stack.append(i)
            while stack != []:
                self.analysis_stack.append(stack.pop())
            if self.analysis_stack[-1] == self.parse_stack[0]:
                print("分析栈:", self.analysis_stack, end=" ")
                print("剩余输入串:", self.parse_stack, end=" ")
                print("匹配成功"+self.parse_stack[0])
                self.analysis_stack.pop()
                self.parse_stack.pop(0)
            if self.analysis_stack[-1] == "ε":
                self.parse_list.pop()
                self.analysis_stack.pop()
            print("分析成功")
        return self.parse_list

    def SET_forecast_table(self):
        self.table={
            "E": {
                "(": "E->TE'",
                ")": "",
                "i": "E->TE'",
                "*": "",
                "+": "",
                "-": "",
                "/": "",
                "#": ""
            },
            "E'": {
                "(": "",
                ")": "E'->ε",
                "i": "",
                "*": "",
                "+": "E'->+TE'",
                "-": "E'->-TE'",
                "/": "",
                "#": "E'->ε"
            },
            "T":{
                "(": "T->FT'",
                ")": "",
                "i": "T->FT'",
                "*": "",
                "+": "",
                "-": "",
                "/": "",
                "#": ""
            },
            "T'":{
                "(": "",
                ")": "T'->ε",
                "i": "",
                "*": "T'->*FT'",
                "+": "T'->ε",
                "-": "T'->ε",
                "/": "T'->/FT'",
                "#": "T'->ε"
            },
            "F":{
                "(": "F->(E)",
                ")": "",
                "i": "F->i",
                "*": "",
                "+": "",
                "-": "",
                "/": "",
                "#": ""
            }
        }
        for i in self.parse_str:
            self.parse_stack.append(i)
        self.parse_stack.append("#")

    def print_table(self):
        print("预测分析表如下:")
        header = [""] + list(self.table["E"].keys())
        pt = PrettyTable(header)

        for k, v in self.table.items():
            row = [k]
            for kk, vv in v.items():
                row.append(vv)
            pt.add_row(row)
        print(pt)

if __name__=="__main__":
    parse_str=input("请输入需要解析的字符串:")
    parse=parse(parse_str)
    parse.print_table()
    parse_list=parse.get_production()
    print(parse_list)
    tree=tree_node()
    P2T=production_to_tree(parse_list)
    P2T.create_tree(0,tree)
    P2T.print_tree(tree)
    print("语法树为:",P2T.get_grammar_tree())