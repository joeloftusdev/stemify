$workingDirectory = '..\build\SpleeterUI'
$workingDirectoryAbsPath = Convert-Path $workingDirectory

# Change to the project directory
Set-Location $workingDirectoryAbsPath

# Run dotnet restore
Start-Process "dotnet" -ArgumentList "restore", "SpleeterUI.csproj" -Wait

$absolutePath = $workingDirectoryAbsPath + '\SpleeterUI.csproj'

$xml = [xml](Get-Content -Path $absolutePath)

$node = $xml.Project.PropertyGroup | 
where {$_.Label -eq 'Globals'}
echo $node

# Create two new XML elements
$UseWPF = $xml.CreateElement('UseWPF')
$UseWPF.InnerText = 'true'

$UseWindowsForms = $xml.CreateElement('UseWindowsForms')
$UseWindowsForms.InnerText = 'true'

# Append the new elements to the selected node
$node.AppendChild($UseWPF)
$node.AppendChild($UseWindowsForms)

# Save the modified XML back to the file
$xml.Save($absolutePath)



