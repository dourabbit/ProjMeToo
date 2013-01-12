var os  = require('os');  
//过虑掉字符串首尾格式，替换字符串中的多个空格为一个空格  
function trim(s){  
    return s;//s.replace(/(^/s*)|(/s*$)/g, '').replace(//s+/g,' ');  
}  
exports.get = function (req, res, next) {  
  //df --total |grep total  
  var sysinfo = {'hostname'   : os.hostname(),  
                 'systemtype' : os.type(),  
                 'release'    : os.release(),  
                 'uptime'     : os.uptime(),  
                 'loadavg'    : os.loadavg(),  
                 'totalmem'   : os.totalmem(),  
                 'freemem'    : os.freemem(),  
                 'cpus'       : os.cpus(),  
                 'disk'       : ''  
                };  
  var exec = require('child_process').exec;  
  exec('df --total |grep total',  
      function (error, stdout, stderr) {  
        if (error !== null) {  
           console.log('exec error: ' + error);  
        }else{  
           var tmp = trim(stdout).split(' ');  
           sysinfo.disk = {total:tmp[1],used:tmp[2],free:tmp[3]};  
        }  
        res.send(JSON.stringify(sysinfo));  
    });  
};  