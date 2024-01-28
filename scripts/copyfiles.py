import os
import shutil

models_source_directory = '../SpleeterLib/deps/spleeterpp/build/models/offline'
models_target_directory = '../build/SpleeterUI/Debug'

script_directory = os.path.dirname(os.path.abspath(__file__))
models_source_abs_path = os.path.abspath(os.path.join(script_directory, models_source_directory))
models_target_abs_path = os.path.abspath(os.path.join(script_directory, models_target_directory))

if not os.path.exists(models_source_abs_path):
    print(f"Error: Source directory '{models_source_abs_path}' does not exist.")
    exit(1)

if not os.path.exists(models_target_abs_path):
    os.makedirs(models_target_abs_path)

shutil.copytree(models_source_abs_path, os.path.join(models_target_abs_path, 'models'))

source_dll_file = '../build/SpleeterUI/SpleeterLib/src/Debug/SpleeterLib.dll'
target_dll_file = os.path.join(models_target_abs_path, 'SpleeterLib.dll')
shutil.copyfile(source_dll_file, target_dll_file)

print('Files copied.')
