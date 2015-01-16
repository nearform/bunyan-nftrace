var Stream = require('stream').Stream;
var util = require('util');
var debug = require('debug')('lttng-stream');
//var lttng = require('bindings')('lttng');
var lttng = require('../build/Release/lttng');

function LttngStream(opts) {

  Stream.call(this);

  this.name = opts && opts.name || process.title || process.argv[0];
  this.writable = true;

  debug('in constructor');
}

util.inherits(LttngStream, Stream);
module.exports = LttngStream;

LttngStream.prototype.close = function close() {
  //binding.closelog();
};


LttngStream.prototype.destroy = function destroy() {
  this.writable = false;
  this.close();
};


LttngStream.prototype.end = function end() {
  if (arguments.length > 0){
    this.write.apply(this, Array.prototype.slice.call(arguments));
  } 

  this.writable = false;
  this.close();
};

LttngStream.prototype.write = function write(rec) {
  if (!this.writable){
    throw new Error('LttngStream has been ended already');
  }

  var m;

  if (Buffer.isBuffer(rec)) {
    m = rec.toString('utf8');
  } else if (typeof (rec) === 'object') {
    debug('rec', rec);
    m = JSON.stringify(rec, bunyan.safeCycles());
  } else if (typeof (rec) === 'string') {
    m = rec;
  } else {
    throw new TypeError('record (Object) required');
  }

  rec.level = rec.level ? rec.level : bunyan.INFO;
  debug('level:', rec.level,  'msg:', m);
  lttng.log(rec.level, m);
}

// Harcoded from https://github.com/trentm/node-bunyan
var bunyan = {
  FATAL: 60,
  ERROR: 50,
  WARN:  40,
  INFO:  30,
  DEBUG: 20,
  TRACE: 10,
  safeCycles: function safeCycles() {
    var seen = [];
    function bunyanCycles(k, v) {
      if (!v || typeof (v) !== 'object') {
        return (v);
      }
      if (seen.indexOf(v) !== -1) {
        return ('[Circular]');
      }
      seen.push(v);
      return (v);
    }

    return (bunyanCycles);
  }
};

function time(t) {
  return (new Date(t).toJSON());
}