var LttngStream = require('./lib/lttng-stream.js');

module.exports = {
  createBunyanStream: function createBunyanStream(opts) {
  	if("linux"!==process.platform) return process.stdout;
    return new LttngStream(opts);
  }
};
