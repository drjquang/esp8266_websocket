/*
 This file stores variable settings
*/

#ifndef settings_h
#define settings_h

char* my_ssid = "espard";
char* my_pass = "abc132de";

char webSiteCont[] PROGMEM = 
R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
    #btn{
      display: inline-block;
      text-decoration: none;
      background: #8cd460;
      color: rgba(255, 255, 255, 0.80);
      font-weight: bold;
      font: 100px arial, sans-serif;
      width: 320px;
      height: 320px;
      line-height: 320px;
      border-radius: 50%;
      margin: 30%;
      margin-top: 60px;
      text-align: center;
      vertical-align: middle;
      overflow: hidden;
      box-shadow: 0px 0px 0px 8px #8cd460;
      border: solid 2px rgba(255, 255, 255, 0.47);
      transition: 0.4s;
    }
    </style>
    <title>ESP8266</title>
</head>
<body>
  <a href="#" id="btn" onclick="myFunction()"></a>
  <script>
      InitWebSocket();
      function InitWebSocket(){
          websock = new WebSocket('ws://' + window.location.hostname + ':88/');
          websock.onmessage = function(event){
              JSONobj = JSON.parse(event.data);
              document.getElementById('btn').innerHTML = JSONobj.LEDonoff;
              if(JSONobj.LEDonoff == 'ON'){
                  document.getElementById('btn').style.background = '#8cd460';
                  document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #8cd460";
              } else {
                  document.getElementById('btn').style.background = '#111111';
                  document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #111111";
              }
          }; // end of onmessage
      }; // end of websocket
      function myFunction(){
          btn = 'LEDonoff=ON';
          if(document.getElementById('btn').innerHTML === 'ON'){
             btn = 'LEDonoff=OFF';
          }
          websock.send(btn);
      };
  </script>
</body>
</html>
)=====";

#endif
