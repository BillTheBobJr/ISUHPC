import numpy as np
import matplotlib.pyplot as plt

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
def GaussElimination(A, b):
    x, y = A.shape
    U = []
    altB = np.array([])
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
    U = np.array(U)
    
    for head in range(y):
        a = U[head, head]
        for current in range(head + 1, y):
            m = U[current, head]/a
            U[current, :] -= m * U[head, :]
            altB[current] -= m * altB[head]
    return solvU(U, altB)


if __name__ == "__main__":
    A = np.array([[(-.1)**3,(-.1)**2,(-.1)**1,1],[(-.2)**3,(-.2)**2,(-.2)**1,1],[(.2)**3,(.2)**2,(.2)**1,1],[(.1)**3,(.1)**2,(.1)**1,1]])
    b = np.array([np.cos(-.1),np.cos(-.2),np.cos(.2),np.cos(.1)])
    coeffiecents = GaussElimination(A, b)
    t = np.arange(-1, 1, .01)
    func = lambda x : coeffiecents[0]*x**3 + coeffiecents[1]*x**2 + coeffiecents[2]*x + coeffiecents[3]
    plt.clf()
    plt.plot(t, func(t), label = 'p(x)')
    plt.plot(t, np.cos(t), label = 'f(x)')
    plt.legend()
    plt.savefig('Output_From_matplotlib.png')
    plt.show()