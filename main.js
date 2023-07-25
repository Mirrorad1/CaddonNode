const calculate = require('./build/Release/calculate');

// Function that returns a promise for calc()
function promisifiedCalc() {
    return new Promise((resolve, reject) => {
      let i, x = 100.32462344, y = 200.333456533452;
      for (i = 0; i < 100; i++) {
        x += y;
      }
  
      const total = x;
      resolve(total);
    });
  }
  
  // Function that returns a promise for calc2()
  function promisifiedCalc2() {
    return new Promise((resolve, reject) => {
      let i, x = 100.32462344, y = 200.333456533452;
      for (i = 0; i < 100; i++) {
        x += y;
      }
  
      const total = x;
      resolve(total);
    });
  }
  
  // Function that returns a promise for calc3()
  function promisifiedCalc3() {
    return new Promise((resolve, reject) => {
      let i, x = 100.32462344, y = 200.333456533452;
      for (i = 0; i < 100; i++) {
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


 console.time('c++');
 const a = calculate.calc();
 console.log(a);
 console.timeEnd('c++');