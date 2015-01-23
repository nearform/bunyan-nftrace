var http = require('http');
var util = require('util');
var cuid = require('cuid');
var bunyan = require('bunyan');
var nftrace = require('..');

// generic log serializer for requests
function reqSerializer(req) {

  return {
    reqId: cuid,
    method: req.method,
    url: req.url
    // headers: req.headers
  }
};

var opts = {
  name: 'simple logger',
  serializers: {
    req: reqSerializer
  },
  streams: [{
    level: 'debug',
    type: 'raw',
    stream: nftrace.createBunyanStream()
  }]
};

var logger = bunyan.createLogger(opts);

logger.info('starting up');

var server = http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  logger.info({req: req});
  res.end('hello world');
}).listen(9000, '0.0.0.0');
console.log('Server running at http://127.0.0.1:9000/. Process PID: ', process.pid);
