require("oosocks");

local connection = OOSock(IPPROTO_TCP);

function CallBack(socket, callType, callId, err, data, peer, peerPort)
	Msg("Got a callback")
	if(callType == SCKCALL_CONNECT and err == SCKERR_OK) then
		print("Connected to google.com.au, YAY!");
		socket:SendLine("GET /index.html HTTP/1.1");
		socket:SendLine("Host: localhost");
		socket:SendLine("");
		socket:ReceiveLine();
	end
 
	if(callType == SCKCALL_REC_LINE and err == SCKERR_OK and data != "") then
		print(data);
		 
		local lengthSig = "Content-Length: ";
		if(string.Left(data, string.len(lengthSig)) == lengthSig) then
			HTTPLen = tonumber(string.Right(data, string.len(data) - string.len(lengthSig)));
		end
 
		-- Get all the headers
		socket:ReceiveLine();
	elseif(callType == SCKCALL_REC_LINE and err == SCKERR_OK and data == "") then
		socket:Receive(HTTPLen);
	end
 
	if(callType == SCKCALL_REC_SIZE) then
		print(data);
	end
end

function TestConnect()
	Msg("Connecting to localhost !!!!\n")
	Msg(connection:Connect("127.0.0.1", 80));
	connection:SetCallback(CallBack)
	connection:SendLine("GET /index.html HTTP/1.1");
	connection:SendLine("Host: localhost");
	connection:SendLine("");
	Msg("\n")
	Msg(connection:ReceiveLine());
end
concommand.Add("test_sock",function(p,c,a) TestConnect() end)