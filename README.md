# Bunyan-LTTNG

Bunyan stream for LTTNG.

# Installation

`npm install bunyan-stream`

```javascript
var bunyan = require('bunyan');
var lttng = require('bunyan-lttng');

var log = bunyan.createLogger({
    name: 'foo',
    streams: [ {
        level: 'debug',
        type: 'raw',
        stream: lttng.createBunyanStream()
    }]
});

log.debug({foo: 'bar'}, 'hello %s', 'world');
```

# License

MIT.
