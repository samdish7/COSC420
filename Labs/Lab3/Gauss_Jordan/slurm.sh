#!/bin/sh

#SBATCH --job-name=lab3_Dish
#SBATCH --nodes=6
#SBATCH --tasks-per-node=24
#SBATCH --mem=2gb
#SBTACH --output=out/%j.log

mpirun ~/Documents/COSC420/Labs/Lab3/Gauss_Jordan/gauss
