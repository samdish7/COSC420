#!/bin/sh

#SBATCH --job-name=Pri
#SBATCH --nodes=6
#SBATCH --tasks-per-node=24
# #SBATCH --ntasks=20
#SBATCH --mem=2gb
# #SBATCH --time=23:59:59
#SBATCH --output=out/%j.log


mpirun ~/Documents/COSC420/Projects/Project1/Primality/prim
