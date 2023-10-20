import re
from typing import List
from collections import deque


class state_node:
    def __init__(self):
        pass

    # ״̬ת��
    def state_transition(self, state):
        ch = chr(ord('A') + state)
        return ch


# ������ʽ
class Regex:
    def __init__(self, regex):
        self.regex = regex

    # ��������ʽת��Ϊ��׺���ʽ
    def regex_to_postfix(self):
        regex = self.regex
        stack = deque()
        postfix = []
        postfix_str = ''
        for i in regex:
            if i == '(':
                stack.append(i)
            elif i == ')':
                while stack[-1] != '(':
                    postfix.append(stack.pop())
                stack.pop()
            elif i == '|':
                stack.append(i)
            elif i == '*':
                postfix.append(i)
            elif i == '.':
                postfix.append(i)
            else:
                postfix.append(i)
        while stack:
            postfix.append(stack.pop())
        for i in postfix:
            postfix_str += i
        return postfix_str


class NFA:
    def __init__(self):
        self.start_state = None  # ��ʼ״̬
        self.end_state = None  # ����״̬
        self.current_state = None  # ��ǰ״̬
        self.accept_state = None  # ����״̬
        self.states = set()  # ״̬����
        self.alphabet = set()  # ��ĸ��
        self.transition = []  # ״̬ת����
        self.accept_location = {}  # ����״̬��
        self.op_stack = deque()  # ������ջ
        self.alphabet_stack = deque()  # ������ջ
        self.dot_location = None  # �����������λ��
        self.star_location = None  # �հ��������λ��
        self.or_location = None  # ���������λ��
        self.state = 0  # ״̬��
        self.state_init()  # ��ʼ����ʼ״̬

    def state_init(self):
        self.start_state = state_node().state_transition(self.state)
        self.state += 1
        self.dot_location = self.start_state
        self.current_state = self.start_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)

    # ��ʼ��������ջ�Ͳ�����ջ
    def stack_init(self, postfix):
        for i in postfix:
            if i == '|':
                self.op_stack.append(i)
            elif i == '*':
                self.op_stack.append(i)
            elif i == '��':
                self.op_stack.append(i)
            else:
                self.alphabet_stack.append(i)

    # ����׺���ʽת��ΪNFA
    def postfix_to_nfa(self, postfix):
        self.stack_init(postfix)
        for i in self.alphabet_stack:
            if i not in self.alphabet:
                self.alphabet.add(i)
        for i in range(len(postfix)):
            if self.op_stack and self.op_stack[0]=='|':
                self.or_op()
                self.op_stack.popleft()
            elif postfix[i] in self.alphabet and self.alphabet_stack:
                self.alphabet_op(postfix[i])
            elif postfix[i]=='*':
                self.op_stack.popleft()
                if postfix[i-1]=='|':
                    self.or_star_op()
                else:
                    self.star_op()
            elif postfix[i] == '��':
                self.dot_op()
        self.end_state=self.accept_state
        #��'A'��accept��״̬д��״̬��
        state_code=ord(self.end_state)-ord('A')
        for i in range(state_code+1):
            self.states.add(state_node().state_transition(i))

    # ��ĸ����
    def alphabet_op(self, alphabet):
        self.current_state = self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + alphabet + ")=" + self.accept_state
        self.transition.append(transition_function)
        self.accept_location.setdefault(alphabet, self.current_state)
        self.current_state = self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)

    # ������
    def or_op(self):
        alphabet1 = self.alphabet_stack.popleft()
        self.current_state=self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)
        self.dot_location=self.current_state
        self.current_state=self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + alphabet1 + ")=" + self.accept_state
        self.transition.append(transition_function)
        if self.accept_location.get(alphabet1):
            self.accept_location.pop(alphabet1)
            self.accept_location.setdefault(alphabet1, self.dot_location)
        else:
            self.accept_location.setdefault(alphabet1, self.dot_location)
        alphabet2 = self.alphabet_stack.popleft()
        self.current_state = self.dot_location
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)
        self.current_state = self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + alphabet2 + ")=" + self.accept_state
        self.transition.append(transition_function)
        self.current_state = self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)
        self.current_state=self.accept_location[alphabet1]
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)
        self.current_state=self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1

    # �հ�����
    def star_op(self):
        alphabet = self.alphabet_stack[0]
        self.dot_location = self.accept_location[alphabet]
        print(self.dot_location)
        transition_function = "f(" + self.current_state + "," + "��)=" + self.dot_location
        self.transition.append(transition_function)

    # ��������
    def dot_op(self):
        if self.op_stack[0] == '*':
            self.current_state = self.accept_state
            transition = "f(" + self.dot_location + "," + "��)=" + self.current_state
            self.transition.append(transition)
            self.dot_location = self.current_state
        else:
            pass
        while self.op_stack:
            if self.op_stack[0] =='��':
                self.op_stack.popleft()
                break
            else:
                self.op_stack.popleft()
        self.current_state = self.accept_state
        self.accept_state = state_node().state_transition(self.state)
        self.state += 1
        transition_function = "f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)
        self.alphabet_stack.popleft()
        self.dot_location = self.accept_state

    # ��հ�����
    def or_star_op(self):
        # self.current_state = self.dot_location
        transition_function = "f(" + self.current_state + "," + "��)=" + self.dot_location
        self.current_state=self.dot_location
        self.transition.append(transition_function)
        self.current_state = self.dot_location
        transition_function="f(" + self.current_state + "," + "��)=" + self.accept_state
        self.transition.append(transition_function)

    # ��ӡNFA
    def print_nfa(self):
        print("NFA:")
        print("K={", end="")
        for i in range(self.state-1):
            print(state_node().state_transition(i), end=",")
        print(state_node().state_transition(self.state-1), end="}")
        print("")
        print("��={", end="")
        alphabet = list(set(self.alphabet))
        for i in alphabet:
            if i!=alphabet[-1]:
                print(i, end=",")
            else:
                print(i,end="}")
        print("")
        for i in self.transition:
            if i!=self.transition[-1]:
                print(i, end=",")
            else:
                print(i,end="")
        print("")
        print(self.start_state)
        print("Z={"+self.end_state+"}")


if __name__ == "__main__":
    regex = Regex(input())
    postfix = regex.regex_to_postfix()
    print(postfix)
    nfa = NFA()
    nfa.postfix_to_nfa(postfix)
    nfa.print_nfa()