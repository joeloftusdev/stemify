# Set models directory in spleeterpp 
$modelsSourceDirectory = '..\SpleeterLib\deps\spleeterpp\build\models\offline'
$modelsSourceDirectoryAbsPath = Convert-Path $modelsSourceDirectory

#set models target dir
$modelsTargetDir = '..\build\SpleeterUI\Debug\'
$modelsTargetAbsPath = Convert-Path $modelsTargetDir

# Copy the directory
Copy-Item -Path $modelsSourceDirectoryAbsPath -Destination $modelsTargetAbsPath -Recurse -Force

$currentName = $modelsTargetAbsPath + 'offline'
$newName = $modelsTargetAbsPath + 'models'

# Rename the directory
Rename-Item -Path $currentName -NewName $newName

# Copy a specific file (adjust the file name accordingly)
$sourceFile = '..\build\SpleeterUI\SpleeterLib\src\Debug\SpleeterLib.dll'
$destinationFile = Join-Path $modelsTargetDir 'SpleeterLib.dll'
Copy-Item -Path $sourceFile -Destination $destinationFile -Force