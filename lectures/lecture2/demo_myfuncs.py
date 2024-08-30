import numpy as np
import myfuncs as fn

def testsqrt(test_value):
    actual = np.sqrt(test_value)
    estimated = fn.sqrt(test_value)

    abs_error = actual - estimated
    print("For x =", test_value,"the absolute error between numpy and my created func for sqrt is", abs_error)

def testexp(test_value):
    actual = np.exp(test_value)
    estimated = fn.exp(test_value)

    abs_error = actual - estimated
    print("For x =", test_value,"the absolute error between numpy and my created func for exp is", abs_error)

def testln(test_value):
    actual = np.log(test_value)
    estimated = fn.ln(test_value)

    abs_error = actual - estimated
    print("For x =", test_value,"the absolute error between numpy and my created func for ln is", abs_error)

#sqrt tests
testsqrt(2)
testsqrt(37)

#exp tests
testexp(.9234)
testexp(8.132)

#ln tests
testln(3.1)
testln(123.4)