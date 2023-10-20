#-*- coding:utf-8 -*-
import grammer_identify
import gram_tree
from prettytable import PrettyTable

class Dot:
    def __init__(self,production):
        self.production=production #产生式
        self.dot_index=0 #点的位置
        self.left=None #产生式左部
        self.right=None #产生式右部
        self.dot_init() #初始化点的位置

    def dot_init(self):
        self.left,self.right=self.production.split("->")
        for i in range(len(self.right)):
            if self.right[i]==".":
                self.dot_index=i
                break

    def get_dot(self):
        return self.dot_index

    def move_dot(self):
        left,right=self.production.split("->")
        right=list(right)
        right.pop(self.dot_index)
        self.dot_index+=1
        right.insert(self.dot_index,".")
        right="".join(right)
        self.production=left+"->"+right

    def get_production(self):
        return self.production

class state:
    def __init__(self,state_name):
        self.state_name=state_name #状态名
        self.begin_state=[] #开始状态
        self.end_state=[] #结束状态
        self.production_list=[] #产生式列表
        self.transform=[] #状态转换
        self.transform_factor=[] #状态转换因子

    def add_production(self,production):
        self.production_list.append(production)

    def add_state_transform(self,end_state,symbol):
        self.begin_state.append(self.state_name)
        self.end_state.append(end_state.get_state_name())
        state_transform="From "+self.state_name+" transform to "+end_state.get_state_name()+" by "+symbol
        self.transform.append(state_transform)

    def get_production_list(self):
        return self.production_list

    def get_state_name(self):
        return self.state_name

    def get_state_transform(self):
        return self.transform

    def print_state(self):
        date=[]
        date.append([self.state_name,"\n".join(self.production_list),"\n".join(self.transform)])
        table=PrettyTable(["State","Production","Transform"])
        for i in date:
            table.add_row(i)
        print(table)

class LR0:
    def __init__(self,production):
        self.production=production #产生式
        self.production_set=[] #产生式集合
        self.symbol=['S'] #符号集合
        self.state_group=[] #状态组
        self.transaction=[] #状态转换
        self.current_state=0 #当前状态
        self.terminals=[] #终结符
        self.non_terminals=[] #非终结符
        self.get_symbol()

    def get_symbol(self):
        for i in self.production:
            left,right=i.split("->")
            if left not in self.terminals:
                self.terminals.append(left)
            right=list(right)
            for j in right:
                if j not in self.symbol:
                    self.symbol.append(j)
        for i in self.symbol:
            if i not in self.terminals:
                self.non_terminals.append(i)
        self.production.insert(0, "S'->S")

    def state_init(self):
        I0=state("I0")
        for i in self.production:
            left,right=i.split("->")
            right=list(right)
            right.insert(0,".")
            right="".join(right)
            I0.add_production(left+"->"+right)
            self.production_set.append(left+"->"+right)
        self.state_group.append(I0)
        self.current_state+=1

    def get_dfa(self):
        k=0
        while k!=len(self.state_group):
            current_state=self.state_group[k]
            production = current_state.get_production_list()
            for i in production:
                i = Dot(i)
                dot_index = i.get_dot()
                for j in self.symbol:
                    if dot_index == len(i.right) - 1:
                        continue
                    else:
                        if i.right[dot_index + 1] == j:
                            i.move_dot()
                            new_production = i.get_production()
                            if new_production not in self.production_set:
                                self.production_set.append(new_production)
                                new_state = state("I" + str(self.current_state))
                                new_state.add_production(new_production)
                                current_state.add_state_transform(new_state,j)
                                current_state.transform_factor.append(j)
                                self.get_core(new_state)
                                self.state_group.append(new_state)
                                self.current_state += 1
            k+=1
        self.get_transform()

    def get_core(self,state):
        production=state.get_production_list()
        for i in production:
            i=Dot(i)
            right=i.right
            dot_index=i.get_dot()
            if dot_index==len(i.right)-1:
                continue
            else:
                suffix=right[dot_index+1]
                for j in self.production:
                    left,right=j.split("->")
                    if left==suffix:
                        right=list(right)
                        right.insert(0,".")
                        right="".join(right)
                        state.add_production(left+"->"+right)
                        self.production_set.append(left+"->"+right)
        state_name=state.get_state_name()

    def get_transform(self):
        for i in range(1,len(self.state_group)):
            for j in range(1,len(self.state_group)):
                self.state_transform(i,j)
        for i in self.state_group:
            length=len(i.transform_factor)
            for j in range(length):
                str="f("+i.begin_state[j]+","+i.transform_factor[j]+")="+i.end_state[j]
                self.transaction.append(str)

    def state_transform(self,index1,index2):
        production1=self.state_group[index1].get_production_list()
        production2=self.state_group[index2].get_production_list()
        if len(production1)==1:
            return
        for i in range(1,len(production1)):
            production=Dot(production1[i])
            dot_index=production.get_dot()
            if dot_index==len(production.right)-1:
                continue
            else:
                suffix=production.right
                for j in self.symbol:
                    if suffix[dot_index + 1] == j:
                        production.move_dot()
                        if production.get_production() in production2:
                            self.state_group[index1].add_state_transform(self.state_group[index2],
                                                                         suffix[dot_index + 1])
                            self.state_group[index1].transform_factor.append(suffix[dot_index + 1])

    def get_action_table(self):
        action_table=PrettyTable()
        trans=["#"]
        action_table.field_names=["ACTION","#"]
        end_state="S."
        for i in self.non_terminals:
            action_table.add_column(i,[])
            trans.append(i)
        for i in self.state_group:
            row=[]
            row.append(i.get_state_name())
            for j in trans:
                if len(i.production_list)==1:
                    production = i.production_list[0]
                    if production=="S'->S." and j=='#':
                        row.append("Acc")
                    else:
                        production = list(production)
                        production.pop()
                        production = "".join(production)
                        row.append("r" + str(self.production.index(production)))
                elif j in i.transform_factor:
                    index=i.transform_factor.index(j)
                    row.append("('S','"+i.end_state[index]+"')")
                else:
                    row.append("")
            action_table.add_row(row)
        print(action_table)

    def get_goto_table(self):
        go_to_table=PrettyTable()
        go_to_table.field_names=["GOTO"]
        for i in self.terminals:
            go_to_table.add_column(i,[])
        for i in self.state_group:
            row=[]
            row.append(i.get_state_name())
            for j in self.terminals:
                if j in i.transform_factor:
                    index=i.transform_factor.index(j)
                    row.append(i.end_state[index])
                else:
                    row.append("")
            go_to_table.add_row(row)
        print(go_to_table)

    def print_dfa(self):
        for i in self.state_group:
            i.print_state()
        for i in self.transaction:
            print(i)
        self.get_action_table()
        self.get_goto_table()
        self.production.pop(0)

if __name__=="__main__":
    file_name="input.txt"
    production=grammer_identify.identify(file_name)
    lr0=LR0(production)
    lr0.state_init()
    lr0.get_dfa()
    lr0.print_dfa()
    gram_tree.get_tree(production)