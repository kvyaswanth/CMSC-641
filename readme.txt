I have included two other scripts that I used to work on this coding assignment

    Chunking Data:
    On line 43 of the python script, I split the data into 75 separate CSV files, each containing one modulus. I did this so I can run instances in parallel.

    Parallel Processing:
    I used a tcsh script to process each of the 75 CSV files in parallel. The tcsh script runs multiple instances of the factorizer program, with a timeout of 5 hours per instance, and saves the results of each file into 75 separate output files.

    Combining Results:
    On line 44 of the Python script, I concatenated the outputs from all 75 files into a single consolidated file, which is the results.csv files that I included.