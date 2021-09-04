const fs = require('fs');
const freetype = require('..');

const face = freetype.generateMSDF(fs.readFileSync(__dirname + '/OpenSans-Bold.ttf'), "abcde", {imageWidth: 100});

console.log(face);
