from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
	# make a python dictionary
	# is a key-value store, like
	# 
