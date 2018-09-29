c:
net use \\Serv2\Columbus-CNC server2
net use \\Anc46\C\winanc\CNC path 

copy C:\NCFILES\%1.CNC \\Anc46\C\winanc\CNC\Programs\%2.cnc
copy C:\NCFILES\%1.CNC \\Serv2\Columbus-CNC\%1.cnc
copy C:\NCFILES\%1.CNC \\Serv2\Columbus-CNC\%2.cnc
ECHO Message "File Transfer Complete!"
PAUSE

C:
