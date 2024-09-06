"""
MAX_STEPS : global default max number of iterations for functions in this file
TOL       : global default tolerance to terminate iterations for functions in this file
E         : the precalculated value of e
LN2       : the precalculated value of ln(2)
"""
MAX_STEPS = 100
TOL = 1e-14
E = 2.7182818284590451
LN2 = 0.69314718056


"""
    Computing and approximation for log(x)/log(2)
    x : a real number
"""
def logBase2Approx(x):
    return int(x).bit_length() - 1


"""
    Computing the factorial of x
    x            : a real number
"""
def factorial(x):
    s = 1
    for k in range(x):
        s *= k + 1
    return s


"""
    Computing s = sqrt(x) using Newtons Method
    x            : a real number
    inital_guess : initial guess for newtons iteration, default = an approximation of 2^(.5*logBase2(x))
    kmax         : max number of iterations, default = MAX_STEPS
    tol          : tolerance to terminate newton's mehtod, default is 1e-14
    print_how    : if 1 prints change in guess between iterations, default = 0
"""
def sqrt(x, inital_guess = None, kmax = MAX_STEPS, tol = TOL, print_how = 0):
    # if no initial guess is input, we calculate it based off of x
    s = inital_guess or 1 << int(logBase2Approx(x)/2 + .5)

    if x < 0:
        print('Input is negative')
        return -1
    
    if x == 0:
        return 0

    #loop for newtons method
    for k in range(kmax):
        sDelta = -.5*(s - x/s)
        s += sDelta
        
        # print information to screen
        if print_how == 1:
            print(k, ":", abs(sDelta))

        # check step change for early termination
        if abs(sDelta) < tol:
            break
    return s


"""
    Computing e^x using the Taylor's Series
    x            : a real number
    kmax         : max number of iterations, default = MAX_STEPS
    tol          : tolerance to terminate newton's mehtod, default = TOL
    print_how    : if 1 prints change in guess between iterations, default = 0

"""
def exp(x, kmax = MAX_STEPS, tol = TOL, print_how = 0):
    x0 = int(x)
    z = x - x0
    exp0 = E**x0
    s = 0

    # loop for taylor series summation
    for k in range(kmax):
        sDelta = (z**k)/factorial(k)
        s += sDelta

        # print information to screen
        if print_how == 1:
            print(k, ":", abs(sDelta))

        # check step change for early termination
        if abs(sDelta) < tol:
            break
    return exp0*s


"""
    Computing ln(x) using Newtons Method
    x            : a real number
    inital_guess : initial guess for newtons iteration, default = an approximation for ln(2)*logBase2(x)
    kmax         : max number of iterations, default = MAX_STEPS
    tol          : tolerance to terminate newton's mehtod, default = TOL
    print_how    : if 1 prints change in guess between iterations, default = 0

"""
def ln(x, initial_guess = None, kmax = MAX_STEPS, tol = TOL, print_how = 0):
    if(x <= 0):
        print("Invalid input for ln function")
        return 0
    
    # if no initial_guess, then we calculate an approximation of ln(x)
    s = initial_guess or LN2*logBase2Approx(x)


    #loop for newtons method
    for k in range(kmax):
        sDelta = x * exp(-s) - 1
        s += sDelta

        # print information to screen
        if print_how == 1:
            print(k, ":", sDelta)

        # check step change for early termination
        if abs(sDelta) < tol:
            break
    return s