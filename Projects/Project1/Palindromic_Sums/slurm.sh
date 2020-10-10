#!/bin/sh

#SBATCH --job-name=palin
#SBATCH --nodes=4
#SBATCH --tasks-per-node=12
#SBATCH --mem=2gb
#SBATCH --output=out/%j.log

mpirun ~/Documents/COSC420/Projects/Project1/Palindromic_Sums/pSum

