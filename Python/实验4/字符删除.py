import string
def delchar(str1,str2):
    length=len(str2)
    i=0
    j=0
    while j<length:
        if str1[i]==str2[j]:
            i+=1
        j+=1
        if i==len(str1):
            break;
    if i==len(str1):
        return True
    return False

if __name__=="__main__":
    str1=input("Please input string s and string t:");
    str2=input()
    if delchar(str1,str2):
        print("String s gets string t after removing some characters")
    else:
        print("String s does not get string t after removing some characters")