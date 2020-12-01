# logical operators in python include
# "in" "is" "not"

if( 1 is not 5 ):
  print("test 1 success")

if( 1 != 5 ):
  print("test 2 success")

# the difference between == and "is" is
# that "is" looks for equivalence in
# the variable references, i.e. do the
# two things point to the same object?

if( 1 < 5 ):
  print("test 3 success")

# Python does not have arrays.
# Python has "lists" and "tuples"

# list, uses square brackets
a = [3, 5, 9, 1]

# similar interface to c-style arrays
# indexes from 0
print(a[0])

# the "in" keyword, used in an if-statement
# checks for membership
if( 5 in a ):
  print("test 4 success")

# "in" is also used to enumerate with loops
# x will take each value inside a
for x in a:
  x += 1
  print(x)

# does not get modified by the above
print(a)

# Python has built-in ranges
# range(a,b) is all the ints
# a, a+1, a+2, ..., b-1
# and the "len" function computes
# the length of a list
for i in range(0,len(a)):
  a[i] += 1

# We can print whole lists
# is modified by the above loop
print(a)

# the goofy one
for key,value in enumerate(a):
  print(f"{key} -> {value}")


