require("oosocks")
 
local connection = OOSock(IPPROTO_UDP);
 
connection:SetCallback(function(socket, callType, callId, err, data, peer, peerPort)
    if(callType == SCKCALL_BIND && err == SCKERR_OK) then
        print("Bound.");
        connection:Send("rofl", "127.0.0.1", 37777);
        connection:ReceiveDatagram();
    end
     
    if(callType == SCKCALL_SEND && err == SCKERR_OK) then
        print("Sent.");
    end
     
    if(callType == SCKCALL_REC_DATAGRAM && err == SCKERR_OK) then
        print("Got '" .. data .. "'  from  " .. peer .. ":" .. tostring(peerPort));
        socket:Close()
    end
     
    if(err != SCKERR_OK) then
        socket:Close()
    end
end);
 
-- an IP of "" binds to all interfaces.
connection:Bind("", 37777);