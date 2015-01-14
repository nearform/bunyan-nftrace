var bunyan = require('bunyan');
var lttng = require('..');

exports.it_should_log_something = function(done) {
  var log = bunyan.createLogger({
    name: 'foo',
    streams: [{
      level: 'debug',
      type: 'raw',
      stream: lttng.createBunyanStream()
    }]
  });

  log.info('hello world');
  //done();
}
