var Stream = require('stream').Stream;
var util = require('util');
var debug = require('debug')('lttng-stream');
var lttng = require('../build/Release/lttng');
console.log("BINDING", lttng);

function LttngStream(opts) {

  Stream.call(this);

  this.name = opts && opts.name || process.title || process.argv[0];
  this.writable = true;

  //if (this.constructor.name === 'SyslogStream') {
  //  binding.openlog(this.name, binding.LOG_CONS, 0);
  //  process.nextTick(this.emit.bind(this, 'connect'));
  //}

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
  if (arguments.length > 0)
    this.write.apply(this, Array.prototype.slice.call(arguments));

  this.writable = false;
  this.close();
};

LttngStream.prototype.write = function write(rec) {
  if (!this.writable)
    throw new Error('LttngStream has been ended already');

  var h;
  var l;
  var m;
  var t;

  if (Buffer.isBuffer(rec)) {
    m = rec.toString('utf8');
  } else if (typeof (rec) === 'object') {
    debug('rec', rec);
    h = rec.hostname;
    l = level(rec.level);
    m = JSON.stringify(rec, bunyan.safeCycles());
    t = time(rec.time);
  } else if (typeof (rec) === 'string') {
    m = rec;
  } else {
    throw new TypeError('record (Object) required');
  }

  l = l ? level(l) : level(bunyan.INFO);
  debug('level:', l,  'msg:', m);
  lttng.log(l,m);
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

// LTTNG Levels - TODO
function level(lev) {
  return lev;
}

function time(t) {
  return (new Date(t).toJSON());
}

var LOG_EMERG = 0;
var LOG_ALERT = 1;
var LOG_CRIT = 2;
var LOG_ERR = 3;
var LOG_WARNING = 4;
var LOG_NOTICE = 5;
var LOG_INFO = 6;
var LOG_DEBUG = 7;