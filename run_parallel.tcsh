#!/bin/tcsh

# number of parallel jobs
set JOBS = 8

# timeout duration, 5 hours/instance 
set TIMEOUT = 18000

# runs the factorizer on all the file chunks created
foreach i (`seq 0 74`)
    
    # run instances with some TIMEOUT
    (timeout $TIMEOUT ./factorizer all-moduli-${i}.csv results-${i}.csv |& tee output-${i}.txt) &
    
    # limitting the number of jobs
    while (`jobs | wc -l` >= $JOBS)
        wait
    end
end

wait