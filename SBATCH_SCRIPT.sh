#Sample script to run a program on Mt Moran.
#Submit the job to the scheduler using the command : sbatch name_of_your_sbatch_script.sh

#!/bin/bash

#Assign Job Name
#SBATCH --job-name=myjob

#Assign Account Name
#SBATCH --account=arccinterns

#Set Max Wall Time
#days-hours:minutes:seconds
#SBATCH --time=00:02:00

#Specify Resources Needed
#SBATCH --nodes=#insert number of nodes here#
#SBATCH --ntasks-per-node=#insert number of tasks per node here#

#Load Required Modules
#example: module load python
#example module load R

module load #required modules#

srun #insert application here#

#srun examples:
#srun Rscript your_R_script.R
#srun python your_python_script.py
#srun your_executable_C_file
