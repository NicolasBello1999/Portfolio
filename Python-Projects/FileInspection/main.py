import pefile, os

# dll_files = [
#     "api-ms-win-core-string-l1-1-0.dll",
#     "api-ms-win-core-interlocked-l1-1-0.dll",
#     "api-ms-win-core-processthreads-l1-1-0.dll",
#     "api-ms-win-core-timezone-l1-1-0.dll"
# ]

# Output file to save results
output_file = "dll_exports.txt"

# Get all .dll files in the current directory
dll_files = [f for f in os.listdir('.') if f.endswith('.dll')]

# Function to analyze a single DLL
def analyze_dll(file_path):
    try:
        pe = pefile.PE(file_path)
        exports = []
        if hasattr(pe, "DIRECTORY_ENTRY_EXPORT"):
            for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
                export_name = exp.name.decode('utf-8') if exp.name else "Unnamed export"
                exports.append(export_name)
        return exports
    except Exception as e:
        return [f"Error analyzing {file_path}: {str(e)}"]

# Process each DLL and write results to the output file
with open(output_file, "w") as f:
    for dll in dll_files:
        f.write(f"Exports for {dll}:\n")
        exports = analyze_dll(dll)
        if exports:
            for export in exports:
                f.write(f"  {export}\n")
        else:
            f.write("  No exports found\n")
        f.write("\n")

print(f"Analysis complete. Results saved to {output_file}")
