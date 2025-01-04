import os
import csv
import pandas as pd

def create_data_chunks(input_file, output_dir, chunks=75):
    """
    splits the input all-moduli file to pieces with one moduli per file and saves them as csv files
    """
    
    # load and preprocess data
    df = pd.read_csv(input_file)
    df['len'] = df['Modulus'].str.len()
    df.sort_values('len', ascending=True, inplace=True)
    df = df[['ModulusName', 'Modulus']]

    os.makedirs(output_dir, exist_ok=True)

    # saving chunks to csv
    for i in range(chunks):
        chunk_file = os.path.join(output_dir, f'all-moduli-{i}.csv')
        df.iloc[i:i+1].to_csv(chunk_file, index=False)

def concatenate_results(output_file, input_dir, chunks=75):
    """
    concatenates all the generated csv files into one
    """
    # writes concatenated oput to 'output_file'
    with open(output_file, 'w', newline='') as outfile:
        writer = csv.writer(outfile)
        writer.writerow(['ModulusName', 'Method', 'Factor'])  # Adjust columns as needed

        for i in range(chunks):
            file_path = os.path.join(input_dir, f'results-{i}.csv')

            if os.path.exists(file_path) and os.path.getsize(file_path) > 0:
                try:
                    with open(file_path, 'r') as infile:
                        reader = csv.reader(infile)
                        writer.writerows(reader)  # Append rows to the output file
                except Exception as e:
                    print(f"Error processing {file_path}: {e}")

# create_data_chunks('/afs/umbc.edu/users/v/v/v117/home/all-moduli.csv', '/afs/umbc.edu/users/v/v/v117/home/da641/datachunks')
concatenate_results('/afs/umbc.edu/users/v/v/v117/home/results.csv', '/afs/umbc.edu/users/v/v/v117/home/da641/datachunks')

