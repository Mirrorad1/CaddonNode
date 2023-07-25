const calculate = require('./build/Release/calculate');
const { Worker } = require('worker_threads');
const path = require('path');

// Function that returns a promise for calc()
function promisifiedCalc() {
    return new Promise((resolve, reject) => {
      let i, x = 100.32462344, y = 200.333456533452;
      for (i = 0; i < 10000000; i++) {
        for (let j = 0; j < 50; j++) {
          x += y;
        }
        x += y;
      }
  
      const total = x;
      resolve(total);
    });
  }
  
  // Function that returns a promise for calc2()
  function promisifiedCalc2() {

    return new Promise((resolve, reject) => {
      let total = 0;
      for (let i = 0; i < 10000000; i++) {
        for (let j = 0; j < 50; j++) {
          total += j;
        }
        total += i;
      }
      resolve(total);
    });
  }
  
  // Function that returns a promise for calc3()
  function promisifiedCalc3() {
    return new Promise((resolve, reject) => {
      let i, x = 100.32462344, y = 200.333456533452;
      for (i = 0; i < 10000000; i++) {
        x += y;
      }
  
      const total = x;
      resolve(total);
    });
  }
  



console.time('javascript');
Promise.all([promisifiedCalc(), promisifiedCalc2(), promisifiedCalc3()])
.then((results) => {
    console.timeEnd('javascript');
  })
  .catch((error) => {
    console.error('Error:', error);
  });


   // C++ // 
  // Function that performs the first calculation
  function calc1() {
      let x = 100.32462344, y = 200.333456533452;
      for (let i = 0; i < 10000000; i++) {
        for (let j = 0; j < 50; j++) {
          x += y;
        }
          x += y;
      }
      return x;
  }
  
  // Function that performs the second calculation
  function calc2() {
      let result = 0;
      for (let i = 0; i < 10000000; i++) {
        for (let j = 0; j < 50; j++) {
          result += j;
        }
        result += i;
      }
      return result;
  }
  
  // Function that performs the third calculation
  function calc3() {
      return [{name: "Hello, world!"}, {name: "test"}];
  }
  
  function runWorker(func) {
      return new Promise((resolve, reject) => {
          const worker = new Worker(path.join(__dirname, 'worker.js'), { workerData: { func: func.toString() } });
          worker.on('message', resolve);
          worker.on('error', reject);
          worker.on('exit', (code) => {
              if (code !== 0) {
                  reject(new Error(`Worker stopped with exit code ${code}`));
              }
          });
      });
  }
  
  async function runCalculations() {
      const functions = [calc1, calc2, calc3];
      console.time('c++');
      const results = await Promise.all(functions.map((func) => runWorker(func)));
      console.log(results);
      console.timeEnd('c++');
  }
  
  runCalculations();