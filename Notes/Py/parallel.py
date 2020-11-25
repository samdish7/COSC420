from mpi4py import MPI

# the MPI object is our main interface
# with the MPI spec

comm = MPI.COMM_WORLD

# call a getter on the "comm" object
# to get my rank
rank = comm.Get_rank()

print(f"hello from proc {rank}")

