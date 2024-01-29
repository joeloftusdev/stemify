## How to Build
```
# Clone the Spleeterpp submodule
git submodule add https://github.com/joeloftusdev/spleeterpp.git SpleeterLib/deps/spleeterpp

# Navigate to the Spleeterpp directory
cd SpleeterLib/deps/spleeterpp

# Create a build directory and build using CMake
mkdir build
cd build
cmake ..

# Build the Spleeterpp library
cmake --build .

# Navigate to the Stemify directory
cd ./Stemify

# Create a build directory and then build using CMake
mkdir build
cd build
cmake ..

# Build Stemify
cmake --build . -- -r

# Navigate to the scripts directory
cd ../scripts

# Copy the models and the spleeterlib dll using either a Python script or PowerShell script
# Choose either the Python script (copyfiles.py) or PowerShell script (copyresources.ps1)
python copyfiles.py
# powershell.exe -File copyresources.ps1


```
