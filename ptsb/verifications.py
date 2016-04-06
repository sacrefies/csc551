#!/usr/bin/env python

import math


def fact(n):
    '''non-recursive version of n factorial. n! is returned.
    '''
    if n < 0:
        print 'Unable to do factorial of a negative number'
        return -1

    if n == 0:
        return 1

    if n <= 2:
        return n

    r = 1
    for i in range(2, n + 1):
        r = r * i

    return r


def multiply(start, end):
    if start == end:
        return start

    mid = (start + end) >> 1
    return multiply(start, mid) * multiply(mid + 1, end)


def factRecursive(n):
    '''recursive version of n factorial.  n! is returned.
    '''
    if n < 0:
        print 'Unable to do factorial of a negative number'
        return -1

    if n == 0:
        return 1

    if n <= 2:
        return n

    return multiply(2, n)


if __name__ == '__main__':
    print '*************** do testing against factorial methods'
    print 'test 0:'
    print 'fact: %d, fact_recursive: %d' % (fact(0), factRecursive(0))
    print 'test < 0:'
    print 'fact: %d, fact_recursive: %d' % (fact(-2), factRecursive(-2))
    print 'test 1:'
    print 'fact: %d, fact_recursive: %d' % (fact(1), factRecursive(1))
    print 'test 2:'
    print 'fact: %d, fact_recursive: %d' % (fact(2), factRecursive(2))
    print 'test 3:'
    print 'fact: %d, fact_recursive: %d' % (fact(3), factRecursive(3))
    print 'test 4:'
    print 'fact: %d, fact_recursive: %d' % (fact(4), factRecursive(4))
    print 'test 10:'
    print 'fact: %d, fact_recursive: %d' % (fact(10), factRecursive(10))
    print 'test 20:'
    print 'fact: %d, fact_recursive: %d' % (fact(20), factRecursive(20))
    print 'test 17:'
    print 'fact: %d, fact_recursive: %d' % (fact(17), factRecursive(17))
