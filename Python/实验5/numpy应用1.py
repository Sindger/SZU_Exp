import numpy as np

matrix=np.array([[1,2,5,7],[4,1,8,0],[2,0,5,1],[0,2,1,1]])
len=matrix.shape[0]
len//=2
ans1=matrix[:len,:len].sum()/(len**2)
ans2=matrix[:len,len:].sum()/(len**2)
ans3=matrix[len:,:len].sum()/(len**2)
ans4=matrix[len:,len:].sum()/(len**2)
print(np.array([[ans1,ans2],[ans3,ans4]]))