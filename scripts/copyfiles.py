import os
import shutil

# Set relative paths for source and target directories
models_source_directory = '../SpleeterLib/deps/spleeterpp/build/models/offline'
models_target_directory = '../build/SpleeterUI/Debug'

# Convert paths to absolute paths based on the script location
script_directory = os.path.dirname(os.path.abspath(__file__))
models_source_abs_path = os.path.abspath(os.path.join(script_directory, models_source_directory))
models_target_abs_path = os.path.abspath(os.path.join(script_directory, models_target_directory))

# Check if the source directory exists
if not os.path.exists(models_source_abs_path):
    print(f"Error: Source directory '{models_source_abs_path}' does not exist.")
    exit(1)

# Create the target directory if it doesn't exist
if not os.path.exists(models_target_abs_path):
    os.makedirs(models_target_abs_path)

# Copy the entire source directory to the target directory
shutil.copytree(models_source_abs_path, os.path.join(models_target_abs_path, 'models'))

# Copy the specific file 'SpleeterLib.dll' to the 'Debug' directory
source_dll_file = '../build/SpleeterUI/SpleeterLib/src/Debug/SpleeterLib.dll'
target_dll_file = os.path.join(models_target_abs_path, 'SpleeterLib.dll')
shutil.copyfile(source_dll_file, target_dll_file)

print('Script executed successfully.')
