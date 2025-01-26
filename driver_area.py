#! /usr/bin/python3

import glob
import sys

def process_files(driver_filter, field_index):
    for file in glob.glob("*.sdb"):  # Match all .sdb files
        with open(file, 'r') as f:
            matches_file = False
            for line in f:
                fields = line.strip().split(';')
                if len(fields) >= 2 and driver_filter in fields[1]:  # Check the 2nd field
                    matches_file = True
                    break  # File matches; no need to check further lines

            if matches_file:
                # Reprocess the file to extract the desired field
                f.seek(0)  # Go back to the start of the file
                for line in f:
                    fields = line.strip().split(';')
                    if len(fields) >= field_index:  # Ensure the field exists
                        # Print the filename along with the specified field
                        # print(f"{file}: {fields[field_index - 1].strip()}")
                        print(f"{file} {fields[field_index - 1].strip()}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python Surface_Area.py <driver_filter> <field_index>")
        sys.exit(1)

    driver_filter = sys.argv[1]  # Filter based on the 2nd field
    field_index = int(sys.argv[2])  # Field index to extract
    process_files(driver_filter, field_index)

