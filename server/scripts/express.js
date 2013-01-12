var express = require('express');
var app = express();

app.get('/',function(req,res){
	res.send("helooooo world");
});

app.listen(3000);