#
# Module for basic mathematic functions
#
import numpy as np
E = 2.7182818284590451
MAX_STEPS = 100

def sqrt(x, kmax = MAX_STEPS):
    s = x
    if(s < 0):
        print("Invalid input for sqrt function")
        return 0   
    for k in range(kmax):
        s = .5*(s + x/s)
    return s

def factorial(x):
    s = 1
    for k in range(x):
        s *= k + 1
    return s

def exp(x, kmax = MAX_STEPS):
    x0 = int(x)
    z = x - x0
    exp0 = E**x0
    s = 0
    for k in range(kmax):
        s += (z**k)/factorial(k)
    return exp0*s

def logBase2Approx(x):
    s = int(x + .5)
    count = 0
    while(s > 0):
        s >>= 1
        count += 1
    
    return count

#The approximation for s is based off of the idea presented by in the following link
#https://www.researchgate.net/post/Is_there_an_approximation_of_lnx_for_a_large_value_of_x#:~:text=ln(x)%20is%20an%20analytic,any%20point%20of%20its%20domain.&text=ln%20x%20%3D%20ln%20a%20%2B%20n,quite%20good%20as%20an%20approximation.
#The only thing required is a pre-calculation of ln(2) = 0.69314718056.
#This function should work for all x's
def ln(x, kmax = MAX_STEPS):
    if(x <= 0):
        print("Invalid input for ln function")
        return 0
    s = 0.69314718056*logBase2Approx(x)
    for i in range(kmax):
        s += x * exp(-s) - 1
    return s