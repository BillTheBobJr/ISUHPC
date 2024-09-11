import numpy as np

#This counts the number of times a particular value appears
#in a 1d list, particularly used for finding number of 0's
#for Gaussian elemination
#list = array to check
#element = value to search for
def countElements(list, element):
    counter = 0
    done = element not in list
    while(not done):
        counter += 1
        index = list.index(element)
        list = list[index + 1:]
        done = element not in list
    return counter

#Finds the solution the this particular form of linear systems
#U = n by n upper matrix
#b = n length solution vector
def solvU(U, b):
    x = np.zeros(b.shape[0])
    for i in range(b.shape[0]).__reversed__():
        val = b[i]
        for ele in range(i + 1, b.shape[0]):
            val -= U[i, ele]*x[ele]
        x[i] = val/U[i, i]

    return x

#Preforms Gaussian Elimination, has been tested for a hand full of
#3 by 3 linear systems and a 4 by 4 linear system
#A = n by n matrix
#b = an n size vector
def gaussian_elimination(A, b):
    x, y = A.shape
    U = []
    altB = np.array([])
    transformationVector = np.array([])
    matrixDictionary = {}
    for i in range(y):
        matrixDictionary[f'{i}'] = np.array([])
    for i in range(y):
        row = A[i,:]
        numberOfZeros = countElements(row.tolist(), 0)
        matrixDictionary[f'{numberOfZeros}'] = np.append(matrixDictionary[f'{numberOfZeros}'],i)
    for key in matrixDictionary.keys():
        for index in matrixDictionary[key]:
            U.append((A[int(index),:]).copy())
            altB = np.append(altB, b[int(index)])
            transformationVector = np.append(transformationVector, index)
    U = np.array(U)
    
    for head in range(y):
        a = U[head, head]
        for current in range(head + 1, y):
            m = U[current, head]/a
            U[current, :] -= m * U[head, :]
            altB[current] -= m * altB[head]
    return solvU(U, altB)
            


A = np.array([[-2.,0.,1.],[-1.,7.,1.],[5.,-1.,1.]])
b = np.array([-4.,-50.,-26.])
print("Gaussian Elimination Preformed by my program:", gaussian_elimination(A, b))
print("Guassian Elimination Preformed by numpy:     ", np.linalg.solve(A, b))
