#!/usr/bin/env node

if ("linux"!==process.platform) return;

var movedFile = false;

var fs = require('fs');
var path = require('path');

var src = path.join(__dirname, '..', 'binding.gyp');

movedFile = true;

//npm_execpath: '/usr/local/lib/node_modules/npm/bin/npm-cli.js',
var nodegyp = path.join(process.env.npm_execpath,
                        '..',
                        'node-gyp-bin',
                        'node-gyp');

if (!fs.existsSync(nodegyp))
  nodegyp = path.join(process.execPath,
                        '..',
                        '..',
                        'lib',
                        'node_modules',
                        'npm',
                        'bin',
                        'node-gyp-bin',
                        'node-gyp');

if (!fs.existsSync(nodegyp)) {
  console.error('cannot locate npm install');
  return;
}

var spawn = require('child_process').spawn;

var stdio = 'ignore';

if (process.env.V)
  stdio = 'inherit';

var options = {
  cwd: path.join(__dirname, '..'),
  stdio: stdio
};

var child = spawn(nodegyp, ['rebuild'], options);

child.on('close', function(code, signal) {
  if ((code || signal) && process.env.V === undefined) {
    console.error('---------------');
    console.error('Building bunyan-nftrace failed with exit code %d and signal %d',
                  code, signal);
    console.error('re-run install with environment variable V set to see the build output');
    console.error('---------------');
  }
  process.exit(0);
});