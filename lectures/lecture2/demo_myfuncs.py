import numpy as np
import myfuncs as fn

def testsqrt(test_value):
    actual = np.sqrt(2)
    estimated = fn.sqrt(2)

    abs_error = actual - estimated
    print("For x =", test_value,"the absolute error between numpy and my created func is", abs_error)


 #sqrt Tests
testsqrt(2)
testsqrt(37)