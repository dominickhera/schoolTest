'use strict'

// C library API
const ffi = require('ffi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');
const mysql = require('mysql');

app.use(fileUpload());

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }
  // else
  // {
  //   console.log(req.files.uploadFile.name);
  // }

 
  let uploadFile = req.files.uploadFile;
 
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }

    res.redirect('/');
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    console.log(err);
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 


let sharedLib = ffi.Library('./parser/bin/parserLib', {
//   'addIndividual': [ 'void', ['Object', 'string' ] ],   //return type first, argument list second
//                   //for void input type, leave argumrnt list empty
//   'JSONtoGEDCOM': [ 'Object', [ 'string' ] ], //int return, int argument
//   'getDesc' : [ 'string', [] ],
    'initFilesToJSON': [ 'string', ['string']],
    'grabIndList': ['string', ['string']],
    'addIndividualWrapper': ['void', ['string' , 'string']],
    'createGEDCOMWrapper' : ['void', ['string', 'string']]
//   'putDesc' : [ 'void', [ 'string' ] ],
});

app.get('/create/:name', function(req, res){
  let filePath = "./uploads/";
  let indParse = JSON.parse(req.params.name);
  // console.log("file params are " + indParse);
   let fileCreate = filePath + indParse.name;
   // let newJson = 
   var myJSON = {givenName: indParse.givenName , surname: indParse.surname};
   var newJson = JSON.stringify(myJSON);
   let createInd = sharedLib.addIndividualWrapper(fileCreate, newJson);
});


app.get('/add/:name', function(req, res){
  // console.log("add");
  let filePath = "./uploads/";
  let indParse = JSON.parse(req.params.name);
   let fileCreate = filePath + indParse.name;
   var myJSON = {source: indParse.source , gedcVersion: indParse.gedcVersion, encoding: indParse.encoding, subName: indParse.subName, subAddress: indParse.subAddress};
   var newJson = JSON.stringify(myJSON);
   let createInd = sharedLib.createGEDCOMWrapper(newJson, fileCreate);
});


app.get('/signIn/:name', function(req, res) {
  // console.log("mo fuckers");
  let indParse = JSON.parse(req.params.name);
  console.log("indparse is " + indParse);

    const connection = mysql.createConnection({
    host     : 'dursley.socs.uoguelph.ca',
    user     : indParse.username,
    password : indParse.password,
    database : indParse.database
});


connection.connect();
});


const testFolder = "./uploads/"
var fileArray = [];
var fileInfo = [];
var indList = [];
fs.readdir('./uploads/', (err, files) => {
  files.forEach((file) => {
    fileArray.push(file);
    // var array = fs.readFileSync(testFolder + file).toString().split("\n");
     // console.log("\n\n\n",array); 
     let testFile = "./uploads/" + file;
     let fileInfoJSON = sharedLib.initFilesToJSON(testFile);
     fileInfo.push(fileInfoJSON);
     let indListJSON = sharedLib.grabIndList(testFile);
     indList.push(indListJSON);

      // console.log(fileInfoJSON);
    // console.log(file);
  });
  // console.log("\n\n\n",array);
  app.get('/uploads/', function(req , res){
  res.send({
    foo: "bar",
    fileArrayList: fileArray,
    fileInfoList: fileInfo,
    fileIndList: indList
  });
});
});


app.listen(portNum);
console.log('Running app at localhost: ' + portNum);