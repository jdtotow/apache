rm build/Debug/mod_datanoesis.dll 
cd build 
MSBuild .\mod_datanoesis.sln  
httpd.exe -k stop -n "Apache"  
Copy-Item "Debug/mod_datanoesis.dll" -Destination "C:\Program Files (x86)\Apache Software Foundation\Apache\modules"
httpd.exe -k start -n "Apache" 
Write-Verbose "Module ready for being used"
C:\Windows\curl.exe http://localhost/datanoesis
cd ..