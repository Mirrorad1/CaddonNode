const { parentPort, workerData } = require('worker_threads');

parentPort.postMessage(eval(`(${workerData.func})()`));
