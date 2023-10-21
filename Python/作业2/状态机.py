class SM:
    def __init__(self):
        self.start_state=None

    def translation_fn(self,s,x):
        return NotImplementedError

    def output_fn(self,s):
        raise NotImplementedError

    def transduce(self,input_seq):
        for i in range(len(input_seq)):
            self.start_state=self.translation_fn(self,self.start_state,input_seq[i])
        print(self.output_fn(self,self.start_state))

class Accumulator(SM):
    start_state=0
    ans=[]
    def translation_fn(self,s,x):
        return s+x

    def output_fn(self,s):
        return s

class Binary_Addition(SM):
    start_state=(0,[])
    def translation_fn(self,s,x):
        num=s[1]
        if x[0]+x[1]+s[0]==0:
            num.append(0)
            s=(0,num)
        elif x[0]+x[1]+s[0]==1:
            num.append(1)
            s=(0,num)
        elif x[0]+x[1]+s[0]==2:
            num.append(0)
            s=(1,num)
        elif x[0]+x[1]+s[0]==3:
            num.append(1)
            s=(1,num)
        return s

    def output_fn(self,s):
        if s[0]==1:
            s[1].append(1)
        return s[1]

class Reverse(SM):
    start_state=(0,0,0,[])
    def translation_fn(self,s,x):
        num=s[3]
        num.append(x)
        if s[0]==1:
            return 1,s[1],s[2]+1,num
        if x=='end':
            return 1,s[1],s[2]+1,num
        else:
            return 0,s[1]+1,s[2]+1,num

    def output_fn(self,s):
        ans=[]
        for i in range(s[2]):
            if i<s[1]:
                ans.append(None)
            elif i>=s[1] and i<=s[1]*2-1:
                ans.append(s[3][2*s[1]-1-i])
            else:
                ans.append(None)
        return ans

if __name__=="__main__":
    acc=Accumulator
    acc.transduce(acc,[-1,2,3,-2,5,6])
    Bin=Binary_Addition
    Bin.transduce(Bin,[(1,1),(1,0),(0,0)])
    reverse = Reverse
    reverse.transduce(reverse, ['foo', ' ', 'bar'] + ['end'] + ['end']*3 +list(range(2)))
    #reverse=Reverse
    #reverse.transduce(reverse,list('the')+['end']+list(range(3)))
