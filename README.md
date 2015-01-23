# Bunyan-nftrace

Bunyan stream support for tracing (using lttng right now).

# Installation

`npm install bunyan-stream`

```javascript
var bunyan = require('bunyan');
var nftrace = require('bunyan-nftrace');

var log = bunyan.createLogger({
    name: 'foo',
    streams: [ {
        level: 'debug',
        type: 'raw',
        stream: nftrace.createBunyanStream()
    }]
});

log.debug({foo: 'bar'}, 'hello %s', 'world');
```

# License

MIT.
