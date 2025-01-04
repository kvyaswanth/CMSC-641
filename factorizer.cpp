#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <gmp.h>
#include <gmpxx.h>
#include <cstdlib>
#include <ctime>

// calculate the GCD using GMP library
mpz_class gcd(const mpz_class &a, const mpz_class &b) {
    mpz_class result; 
    mpz_gcd(result.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t()); // calculate GCD using GMP library
    return result;
}

// pollards rho algorithm
void pollard_rho(mpz_class &factor, const mpz_class &n) {
    mpz_class x = 2, y = 2, d = 1; // initialize x and y to be same
    
    // we loop until a factor is found
    while (d == 1) {

        x = (x * x + 1) % n; // update x using f(x) = (x^2 + 1) mod n
        y = (y * y + 1) % n; // update y using the same function
        y = (y * y + 1) % n; // update y again for double speed (Floyd's cycle detection)
        d = gcd(abs(x - y), n); // calculate GCD of |x - y| and n to find a factor
    }

    if (d == n) { // factorization failed, if GCD equals n
        factor = 0; // if not factor found
    } else { // otherwise case, we factor found
        factor = d; 
    }
}

// pollards p-1 algorithm
void pollard_p_minus_1(mpz_class &factor, const mpz_class &n) {
    mpz_class a = 2, d; // initialize variables -- a for modular exponentiation and d for factor

    for (unsigned long int i = 2; i < 1000000; i++) { // iterate until reasonable runtime
        mpz_powm_ui(a.get_mpz_t(), a.get_mpz_t(), i, n.get_mpz_t()); // compute a^i mod n
        d = gcd(a - 1, n); // calculate GCD of a-1 and n

        if (d > 1 && d < n) { // if factor found
            factor = d;
            return;
        }
    }

    factor = 0; // if no factor found
}

// function to process the csv and run factorization
void process_csv(const std::string &input_filename, const std::string &output_filename) {
    std::ifstream input_file(input_filename); // open the input file
    std::ofstream output_file(output_filename); // open the output file
    
    // checks if either file failed to open, throws an error in case
    if (!input_file || !output_file) { 
        std::cerr << "Error: Unable to open file(s).\n"; 
        exit(EXIT_FAILURE);
    }

    std::string line;

    // skip the header of csv
    if (std::getline(input_file, line)) { 
        // std::cout << "Skipping header: " << line << std::endl; // Debug log (optional)
    }

    // reads the input file
    // throws an error if line is faulty, like line has no commas
    while (std::getline(input_file, line)) { 
        size_t comma = line.find(',');
        if (comma == std::string::npos) {
            std::cerr << "Malformed line: " << line << std::endl;
            continue;
        }

        // extract lines
        std::string modulus_name = line.substr(0, comma); 
        std::string modulus_str = line.substr(comma + 1);

        // parse modulus as an mpz_class object
        mpz_class modulus(modulus_str), factor; 

        // apply pollards p-1 algorithm
        // checks if a factor found
        // writes to output file
        pollard_p_minus_1(factor, modulus);
        if (factor != 0) { 
            std::cout << modulus_name << ",ppm1," << factor << "\n"; 
            output_file << modulus_name << ",ppm1," << factor << "\n"; 
        }

        // pollards rho algorithm
        // checks if a factor found
        // writes to output file
        pollard_rho(factor, modulus);
        if (factor != 0) { // Check if a factor was found
            std::cout << modulus_name << ",prho," << factor << "\n";
            output_file << modulus_name << ",prho," << factor << "\n";
        }
    }
}

// main function
// takes in arguments, input file -- all-moduli.csv, output file -- results.csv  
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_csv> <output_csv>\n";
        return EXIT_FAILURE;
    }

    process_csv(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
