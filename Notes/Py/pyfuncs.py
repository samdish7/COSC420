# Python functions are defined with the
# "def" keyword, then the name, list of
# parameters, then a colon.
# note that functions do not have
# return types, and parameters do not
# have types (but you can provide them
# anyway)

# scopes in python are delineated not by
# curly braces (as in c/c++) but by tabs
# you can use spaces to indent or tabs,
# but don't mix-and-match


def func():
  # all following indented lines are 
  # bound to the "func" block
  print("hello from func")

# non type-hinted version
def funcParams(a,b,c):
  # using python's "f-strings"
  print(f"a: {a}")
  print(f"b: {b+10}")
  print(f"c: {c}")
  return 10 # return looks the same

# hinted version
def funcParams2(
    a : str,
    b : int,
    c : float) -> int :
  # using python's "f-strings"
  print(f"a: {a}")
  print(f"b: {b+10}")
  print(f"c: {c}")
  return "10" # return looks the same

def main():
  print("Start of program")
  print("about to call the function:")
  func() # call the funcion
  #val = funcParams(15, 10, 3.4)
  val = funcParams2(15, 10, 3.4)
  print(val)

# back in the top-level scope
main()

