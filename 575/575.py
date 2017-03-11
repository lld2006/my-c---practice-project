#! /usr/bin/python
from decimal import *
import numpy
def getIndex(row, col, nrow):
    return row*nrow+col;
def solvemat(c2, s2,  c3, s3 ,c4, s4):
    nrow = 6
    nrow2 = nrow*nrow
    mat = [[0 for i in range(0, nrow2)] for j in range(0,nrow2)];
    rhs=[0]*nrow2
    for row in range(0, nrow):
        for col in range(0, nrow):
            ind = getIndex(row, col, nrow)
            xside = (row == 0) or (row == nrow-1)
            yside = (col == 0) or (col == nrow-1) 
            if(xside and yside):
                mat[ind][ind] = -c2;
                if(row == 0):
                    ind2 = getIndex(row+1, col, nrow);
                    mat[ind2][ind] = s2
                else:
                    ind2 = getIndex(row-1, col, nrow)
                    mat[ind2][ind]= s2
                if(col == 0):
                    ind2 = getIndex(row, col+1, nrow)
                    mat[ind2][ind]= s2
                else:
                    ind2 = getIndex(row, col-1, nrow)
                    mat[ind2][ind]= s2
            elif(xside or yside):
                mat[ind][ind]= -c3;
                if(row == 0):
                    mat[getIndex(row,col-1,nrow)][ind]= s3
                    mat[getIndex(row, col+1, nrow)][ind]=s3
                    mat[getIndex(row+1, col, nrow)][ind]=s3
                elif(row ==nrow-1):
                    mat[getIndex(row,col-1,nrow)][ind]=s3
                    mat[getIndex(row,col+1,nrow)][ind]=s3
                    mat[getIndex(row-1,col,nrow)][ind]=s3
                elif(col == 0):
                    mat[getIndex(row+1,col,nrow)][ind]=s3
                    mat[getIndex(row-1,col,nrow)][ind]=s3
                    mat[getIndex(row,col+1,nrow)][ind]=s3
                else:
                    mat[getIndex(row+1,col,nrow)][ind]=s3
                    mat[getIndex(row-1,col,nrow)][ind]=s3
                    mat[getIndex(row,col-1,nrow)][ind]=s3
            else:
                assert(xside == 0 and yside == 0)
                mat[ind][ind]=-c4;
                mat[getIndex(row-1,col,nrow)][ind]=s4
                mat[getIndex(row+1,col,nrow)][ind]=s4
                mat[getIndex(row,col-1,nrow)][ind]=s4
                mat[getIndex(row,col+1,nrow)][ind]=s4
    #for col in range (0, nrow2):
    #    for row in range(0, nrow2):
    #        if(abs(mat[row][col]) > 0):
    #            print("(%d, %d) %f") %(row, col, mat[row][col]);
    for col in range(0, nrow2):
        mat[nrow2-1][col]=1.0
    rhs[nrow2-1]=1.0
    #print("rhs is",rhs)
    #print("????", c2, s2, c3, s3, c4, s4)
    pmat = numpy.array(mat, dtype='f8')
    prhs = numpy.array(rhs, dtype='f8')
    x = numpy.linalg.solve(pmat, prhs)
    return x
c2= 1./2 
s2 = c2/2
c3 = 1./2
s3 = c3/3
c4 = 1./2
s4 = c4/4
x = solvemat(c2, s2, c3, s3, c4, s4)
print(x)

total = x[0]+x[3]+x[8]+x[24]+x[15]
c2= 2./3 
s2 = c2/2
c3 = 3./4
s3 = c3/3
c4 = 4./5
s4 = c4/4
x = solvemat(c2, s2, c3, s3, c4, s4)
print(x)
total += x[0]+x[3]+x[8]+x[24]+x[15]
print(total/2);
