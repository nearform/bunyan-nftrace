var bunyan = require('bunyan');
var nftrace = require('..');

exports.it_should_log_something = function(done) {
  var log = bunyan.createLogger({
    name: 'foo',
    streams: [{
      level: 'debug',
      type: 'raw',
      stream: nftrace.createBunyanStream()
    }]
  });

  log.info('hello world');
  //done();
}
