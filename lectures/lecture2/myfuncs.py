#
# Module for basic mathematic functions
#
E = 2.7182818284590451
MAX_STEPS = 100

def sqrt(x, kmax = MAX_STEPS):
    s = x
    if(s < 0):
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

def ln(x, kmax = MAX_STEPS):
    s = x
    for i in range(kmax):
        s += x * exp(-s) - 1
    return s