//
//var http = require('http'), io = require('socket.io');
////创建server
//var server = http.createServer(function(req, res){ 
//  // Send HTML headers and message
//  res.writeHead(200,{ 'Content-Type': 'text/html' }); 
//  res.end('<h1>Hello Socket Lover!</h1>');
//});
////端口8000
//server.listen(1985);
////创建socket
//var socket = io.listen(server);
////添加连接监听
//socket.on('connection', function(client){   
//	//连接成功则执行下面的监听
//	client.on('message',function(event){ 
//		console.log('Received message from client!',event);
//	});
//	//断开连接callback
//	client.on('disconnect',function(){
//		console.log('Server has disconnected');
//	});
//});

var net = require('net');
var tcp_server = net.createServer(function(socket){

	socket.write('Echo hello from server \r\n');
	socket.pipe(socket);
});
tcp_server.listen(1984,'127.0.0.1');