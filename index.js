module.exports = {
  createBunyanStream: function createBunyanStream(opts) {
  	if("linux"!==process.platform) return process.stdout;
  	
  	var LttngStream = require('./lib/lttng-stream.js');
    return new LttngStream(opts);
  }
};
