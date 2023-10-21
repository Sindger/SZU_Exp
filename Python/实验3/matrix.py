import numpy as np
import sys
def matrix_dim(M):
    m=np.mat(M)
    return m.shape

def muti_M_v(M,v):
    dim=matrix_dim(M)
    n=dim[0]
    m=dim[1]
    m1=[0 for a in range(n)]
    for i in range(n):
        for j in range(m):
            m1[i]=M[i][j]*v[j]
    return m1

def transpose(M):
    m=np.mat(M)
    return m.T

def largest_col_sum(M):
    dim=matrix_dim(M)
    n=dim[0]
    m=dim[1]
    sum=-sys.maxsize;
    for i in range(m):
        num=0
        for j in range(n):
            num+=M[j][i]
        if num>sum:
            sum=num
    return sum

def switch_column(M,i,j):
    dim = matrix_dim(M)
    n = dim[0]
    for k in range(n):
        M[k][i],M[k][j]=M[k][j],M[k][i]
    return np.mat(M)
