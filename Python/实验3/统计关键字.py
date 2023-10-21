import string
def removePunctuation(word):
    for i in word:
        if i in string.punctuation or i=='\n':
            word=word.replace(i," ")
    flag=word.split(' ')
    length=len(flag)-1
    for i in range(length,-1,-1):
        if len(flag[i])==0:
            del flag[i]
            continue
        if flag[i]=='\n':
            del flag[i]
    return flag

if __name__=="__main__":
    Dictionary={"and": 0, "as": 0, "assert": 0, "break": 0, "class": 0, "continue": 0, "def": 0, "del": 0, "elif": 0, "else": 0, "except": 0, "False": 0, "finally": 0, "for": 0, "from": 0, "global": 0,
            "if": 0, "import": 0, "in": 0, "is": 0, "lambda": 0, "None": 0, "nonlocal": 0, "not": 0, "or": 0, "pass": 0, "raise": 0, "return": 0, "True": 0, "try": 0, "while": 0, "with": 0, "yield": 0}
    file=open("nARQ.py","r")
    while 1:
        fileword=file.readline()
        if not fileword:
            break;
        if fileword=='\n':
            continue
        words=removePunctuation(fileword)
        for flag in words:
            if flag in Dictionary.keys():
                Dictionary[flag]+=1
    print(Dictionary)
    file.close()