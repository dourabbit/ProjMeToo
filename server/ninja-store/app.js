
/**
 * Module dependencies.
 */

var express = require('express')
  , store = require('./routes/store')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path');

var app = express();

app.configure(function(){
  app.set('port', process.env.PORT || 3000);
  app.set('views', __dirname + '/views');
  app.set('view engine', 'jade');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(express.cookieParser('your secret here'));
  app.use(express.session());
  app.use(app.router);
  app.use(require('stylus').middleware(__dirname + '/public'));
  app.use(express.static(path.join(__dirname, 'public')));
});

app.configure('development', function(){
  app.use(express.errorHandler());
});

app.get('/', store.home);
app.get('/users', user.list);

http.createServer(app).listen(app.get('port'), function(){
  console.log("Express server listening on port " + app.get('port'));
});

function FileRepository(){

    
}
FileRepository.prototype.getFile = function(callback,nm) {
    console.log(nm);
    var mongo = require('mongodb'),
    fs = require('fs'),
    Server = mongo.Server,
    GridStore = mongo.GridStore,
    Db = mongo.Db;
    var db = Db('test', new Server("127.0.0.1", 27017,
                {auto_reconnect: false}));
    db.open(function(err, client) {
            
            var gs = new GridStore(client,nm, 'r');
            gs.open(function(err,gs){
                    gs.read(callback);
                    });
            });
};

app.get('/data/:imgtag', function(req, res) {
        var fileRepository = new FileRepository();
        //console.log(req.params);
        fileRepository.getFile( function(error,data) {
                         res.writeHead('200', {'Content-Type': 'image/png'});
                         res.end(data,'binary');},//end of callback
                         req.params.imgtag);

});