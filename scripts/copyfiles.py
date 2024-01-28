import os
import shutil

models_source_directory = 'C:\\dev\\projects\\Stemify\\SpleeterLib\\deps\\spleeterpp\\build\\models\\offline'
models_target_directory = 'C:\\dev\\projects\\Stemify\\build\\SpleeterUI\\Debug'

models_source_abs_path = os.path.abspath(models_source_directory)
models_target_abs_path = os.path.abspath(models_target_directory)

if not os.path.exists(models_source_abs_path):
    print(f"Error: Source directory '{models_source_abs_path}' does not exist.")
    exit(1)

if not os.path.exists(models_target_abs_path):
    os.makedirs(models_target_abs_path)

shutil.copytree(models_source_abs_path, os.path.join(models_target_abs_path, 'models'))

source_dll_file = 'C:\\dev\\projects\\Stemify\\build\\SpleeterUI\\SpleeterLib\\src\\Debug\\SpleeterLib.dll'
target_dll_file = os.path.join(models_target_abs_path, 'SpleeterLib.dll')
shutil.copyfile(source_dll_file, target_dll_file)

print('Script executed successfully.')

