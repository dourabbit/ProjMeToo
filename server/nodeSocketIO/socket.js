

////Below codes failed in different computers
//var net = require('net');
//var tcp_server = net.createServer(function(socket){
//
//	socket.write('Server Connected\r\n');
//	socket.pipe(socket);
//});
//tcp_server.listen(1984,'127.0.0.1');


//var io = require('socket.io').listen(1984);
//
//io.sockets.on('connection', function (socket) {
//              socket.write('Server Connected\r\n');
//              socket.pipe(socket);
//              
//              //连接成功则执行下面的监听
//              socket.on('message',function(event){
//                        console.log('Received message from client!',event);
//              });
//              //断开连接callback
//              socket.on('disconnect',function(){
//                        console.log('Server has disconnected');
//              });
//});

var io = require('socket.io').listen(3000);

io.sockets.on('connection', function (socket) {
              socket.emit('news', { hello: 'world' });
              socket.on('my other event', function (data) {
                        console.log(data);
                        });
              });