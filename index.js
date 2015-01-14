var LttngStream = require('./lib/lttng-stream.js');

module.exports = {
  createBunyanStream: function createBunyanStream(opts) {
    return new LttngStream(opts);
  }
};