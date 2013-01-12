/**
 * User: jacky
 * Date: 11-3-30
 * Time: ����11:11
 * To change this template use File | Settings | File Templates.
 */
var express = require('express');
var app = express.createServer();
var path = require('path');
var fs = require('fs');
var url = require('url');
//configration
//ÿ����������ִ�е�����
app.configure(function(){
    //console.log('in configure');
    app.use(express.methodOverride());
    app.use(express.bodyParser());
    app.use(app.router);
    app.use(express.logger({ format: ':method :url' }));
});
//Ĭ�Ϸ�ʽ $ node ./server.js Ϊ����ģʽ
app.configure('development', function(){
    //console.log('in configure with development');
    app.use(express.static(__dirname + '/static'));
    //console.log(__dirname + '/static');
    app.use(express.errorHandler({ dumpExceptions: true, showStack: true }));
});
//�� $NODE_ENV=production node ./server.js ��ʽ���У���Ϊ����ģʽ
app.configure('production', function(){
  //console.log('in configure with production');
  var oneYear = 31557600000;
  app.use(express.static(__dirname + '/static', { maxAge: oneYear }));
  app.use(express.errorHandler());
});
// routing settings
//�ض���̬�ļ� html,css,js,jpg,png => /static/+req.url
app.all('/*.(html|css|js|jpg|png){1}', function(req, res, next){
    //var static_file_formats = ['.html','.css','.js','.jpg','.png'];
    //console.log(path.extname(req.url));
    var realpath = __dirname + '/static' + url.parse(req.url).pathname;
    //console.log(realpath);
    if(path.existsSync(realpath)){
        res.end(fs.readFileSync(realpath));
    }else{
        res.end('Cannot find request url: '+req.url);
    }
});
//���������ļ�routing.js������routings. [/scripts/routing.js]
var routings = require(__dirname + '/scripts/routing.js').routings;
for(var r in routings){
    var pf = require(__dirname + routings[r].file)[routings[r].processFunction];
    if(routings[r].method == 'get')
        app.get(r, pf,function(req, res){});
    else if(routings[r].method == 'post')
        app.post(r,pf);
    else
        app.all(r, pf,function(req, res){});
}
app.listen(8080);
console.log('Server running at http://127.0.0.1:8080/');