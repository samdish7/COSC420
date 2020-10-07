#!/bin/sh

#SBATCH --job-name=sam/jorProject
# #SBATCH --nodes=4
# #SBATCH --tasks-per-node=12
#SBATCH --ntasks=20
#SBATCH --mem=2gb
#SBATCH --time=23:59:59
#SBATCH --output=out/%j.log


mpirun ~/Documents/COSC420/Projects/Project1/Strong_Achilles_Numbers/ach
