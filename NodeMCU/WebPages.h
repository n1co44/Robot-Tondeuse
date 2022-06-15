/*
 * WebPages.ino
 *
 *
 */


#ifndef WEBPAGES_INO_
#define WEBPAGES_INO_

#if defined(WEBSERVER)


const char Index_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 15px 32px;
		  text-align: left;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 14px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<center>
		<div>
		<h1>ReP_AL Robot Webserver</h1>
		</div>

		<div>
			MowerTime:  <span id="MowerTime"></span><br>
			MowerMode:  <span id="MowerMode"></span><br>		  
			Battery[V]:  <span id="BatteryVoltage"> V</span><br>
		  	Charging[A]: <span id="ChargeAmps"> A</span><br><br>
		</div>

		<div>
		  <button class="button" onclick="send(0)">Setup</button><br><br>
		  <button class="button" onclick="send(1)">Tests</button><br><br>
		  <button class="button" onclick="send(2)">RemoteControl</button><br><br>
		  <button class="button" onclick="send(3)">RunningData</button><br><br>
		  <button class="button" onclick="send(4)">ArduDiagCtrl</button><br><br>
		</div>
		</center>
		 <br>

		<script>
		function send(pageNo) 
		{
			if      (pageNo == 0) location.replace("/setup")
			else if (pageNo == 1) location.replace("/test")
			else if (pageNo == 2) location.replace("/remotectrl")
			else if (pageNo == 3) location.replace("/rundata")
			else if (pageNo == 4) location.replace("/ardudiagctrl")
		}

		setInterval(function() 
		{
		  getData();
		}, 500);
 
		function getData() {
		  var xhttp = new XMLHttpRequest();
		  xhttp.onreadystatechange = function() {
		    if (this.readyState == 4 && this.status == 200) {
				var res = JSON.parse(xhttp.responseText);
				
				document.getElementById("MowerMode").innerHTML = res.MowerMode;				
				document.getElementById("BatteryVoltage").innerHTML = res.BatteryVoltage;
				document.getElementById("ChargeAmps").innerHTML = res.ChargeAmps;
				document.getElementById("MowerTime").innerHTML = res.MowerTime;
		    }
		  };
		  xhttp.open("GET", "/index_getData", true);
		  xhttp.send();
		}
		</script>

		</body>
		</html>
		)====="
;


const char Setup_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 10px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 9px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<h2><a href="/">Home</a> &nbsp;&nbsp; <a href="/test">Test</a> &nbsp;&nbsp; <a href="/remotectrl">RemoteControl</a> &nbsp;&nbsp; <a href="/rundata">RunData</a> &nbsp;&nbsp;</h2>
		<div>
		<h1>ReP_AL Robot - Setup</h1>

			<p><button class="button" onclick="send(30)">ON</button>
			   <button class="button" onclick="send(31)">OFF</button>
			   Compass: <span id="Compass_Activate"></span></p>

			<p><button class="button" onclick="send(32)">ON</button>
			   <button class="button" onclick="send(33)">OFF</button>
			   HeadingHold: <span id="Compass_Heading_Hold_Enabled"></span></p>

			<p><button class="button" onclick="send(34)">ON</button>
			   <button class="button" onclick="send(35)">OFF</button>
			   Gyro: <span id="GYRO_Enabled"></span></p>

			<p><button class="button" onclick="send(37)">ON</button>
			   <button class="button" onclick="send(38)">OFF</button>
			   Sonar1: <span id="Sonar_1_Activate"></span></p>

			<p><button class="button" onclick="send(39)">ON</button>
			   <button class="button" onclick="send(40)">OFF</button>
			   Sonar2: <span id="Sonar_2_Activate"></span></p>

			<p><button class="button" onclick="send(41)">ON</button>
			   <button class="button" onclick="send(42)">OFF</button>
			   Sonar3: <span id="Sonar_3_Activate"></span></p>

			<p><button class="button" onclick="send(43)">ON</button>
			   <button class="button" onclick="send(44)">OFF</button>
			   Bumper: <span id="Bumper_Activate_Frnt"></span></p>

			<p><button class="button" onclick="send(47)">ON</button>
			   <button class="button" onclick="send(48)">OFF</button>
			   Alarm1: <span id="Alarm_1_ON"></span></p>

			<p><button class="button" onclick="send(49)">ON</button>
			   <button class="button" onclick="send(50)">OFF</button>
			   Alarm2: <span id="Alarm_2_ON"></span></p>

			<p><button class="button" onclick="send(51)">ON</button>
			   <button class="button" onclick="send(52)">OFF</button>
			   Alarm3: <span id="Alarm_3_ON"></span></p>

			<p><button class="button" onclick="send(55)">ON</button>
			   <button class="button" onclick="send(56)">OFF</button>
			   GPS: <span id="GPS_Enabled"></span></p>

			<p><button class="button" onclick="send(57)">ON</button>
			   <button class="button" onclick="send(58)">OFF</button>
			   AngleSensor: <span id="Angle_Sensor_Enabled"></span></p>

			<p><button class="button" onclick="send(59)">ON</button>
			   <button class="button" onclick="send(60)">OFF</button>
			   TipSensor: <span id="Tip_Over_Sensor_Enabled"></span></p>

			<p><button class="button" onclick="send(61)">ON</button>
			   <button class="button" onclick="send(62)">OFF</button>
			   WheelAmpSensor: <span id="Wheel_Amp_Sensor_ON"></span></p>

			<p><button class="button" onclick="send(91)">ON</button>
			   <button class="button" onclick="send(92)">OFF</button>
			   Wheels_Activate: <span id="Wheels_Activate"></span></p>

			<p><button class="button" onclick="send(93)">ON</button>
			   <button class="button" onclick="send(94)">OFF</button>
			   Ramp_Motor: <span id="Ramp_Motor_ON"></span></p>

			<p><button class="button" onclick="send(95)">ON</button>
			   <button class="button" onclick="send(96)">OFF</button>
			   MAG_Speed_Adjustment: <span id="MAG_Speed_Adjustment"></span></p>

			<p><button class="button" onclick="send(97)">ON</button>
			   <button class="button" onclick="send(98)">OFF</button>
			   Perimeter_Wire: <span id="Perimeter_Wire_Enabled"></span></p>

			<p><button class="button" onclick="send(99)">ON</button>
			   <button class="button" onclick="send(100)">OFF</button>
			   Use_Charging_Station: <span id="Use_Charging_Station"></span></p>

			<br>
		</div>

		<script>
		setInterval(function() 
		{
		  getData();
		}, 500);
 
		function getData() {
		  var xhttp = new XMLHttpRequest();
		  xhttp.onreadystatechange = function() {
		    if (this.readyState == 4 && this.status == 200) {
				var res = JSON.parse(xhttp.responseText);
				
				document.getElementById("Compass_Activate").innerHTML = res.Compass_Activate;
				document.getElementById("Compass_Heading_Hold_Enabled").innerHTML = res.Compass_Heading_Hold_Enabled;
				document.getElementById("GYRO_Enabled").innerHTML = res.GYRO_Enabled;
				document.getElementById("Sonar_1_Activate").innerHTML = res.Sonar_1_Activate;
				document.getElementById("Sonar_2_Activate").innerHTML = res.Sonar_2_Activate;
				document.getElementById("Sonar_3_Activate").innerHTML = res.Sonar_3_Activate;
				document.getElementById("Bumper_Activate_Frnt").innerHTML = res.Bumper_Activate_Frnt;
				document.getElementById("Alarm_1_ON").innerHTML = res.Alarm_1_ON;
				document.getElementById("Alarm_2_ON").innerHTML = res.Alarm_2_ON;
				document.getElementById("Alarm_3_ON").innerHTML = res.Alarm_3_ON;
				document.getElementById("GPS_Enabled").innerHTML = res.GPS_Enabled;
				document.getElementById("Angle_Sensor_Enabled").innerHTML = res.Angle_Sensor_Enabled;
				document.getElementById("Tip_Over_Sensor_Enabled").innerHTML = res.Tip_Over_Sensor_Enabled;
				document.getElementById("Wheel_Amp_Sensor_ON").innerHTML = res.Wheel_Amp_Sensor_ON;
				document.getElementById("Wheels_Activate").innerHTML = res.Wheels_Activate;
				document.getElementById("Ramp_Motor_ON").innerHTML = res.Ramp_Motor_ON;
				document.getElementById("MAG_Speed_Adjustment").innerHTML = res.MAG_Speed_Adjustment;
				document.getElementById("Perimeter_Wire_Enabled").innerHTML = res.Perimeter_Wire_Enabled;
				document.getElementById("Use_Charging_Station").innerHTML = res.Use_Charging_Station;
		    }
		  };
		  xhttp.open("GET", "/setup_getData", true);
		  xhttp.send();
		}

		function send(btnNo) 
		{
		  var xhttp = new XMLHttpRequest();
		  xhttp.open("GET", "cmdSetup?btn="+btnNo, true);
		  xhttp.send();
		}
		</script>

		</body>
		</html>
		)====="
;


const char Test_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 10px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 9px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<h2><a href="/">Home</a> &nbsp;&nbsp; <a href="/setup">Setup</a> &nbsp;&nbsp; <a href="/remotectrl">RemoteControl</a> &nbsp;&nbsp; <a href="/rundata">RunData</a> &nbsp;&nbsp;</h2>
		<center>
		<div>
		<h1>ReP_AL Robot - Test</h1>
		</div>
		 <br>

		<div>
			Battery[V]:  <span id="BatteryVoltage"> V</span><br>
			Charging[A]: <span id="ChargeAmps"> A</span><br>
			WheelAmps[A]: <span id="WheelAmps"> A</span><br>
			Sonar dist1: <span id="distance1"> A</span><br>
			Sonar dist2: <span id="distance2"> A</span><br>
			Sonar dist3: <span id="distance3"> A</span><br>
			Sonar_Status: <span id="Sonar_Status"> A</span><br>
			Outside_Wire: <span id="Outside_Wire"> A</span><br>
			Bumper: <span id="Bumper"> A</span><br>
			Tilt_Angle_Sensed: <span id="Tilt_Angle_Sensed"> A</span><br>
			GPS_Inside_Fence: <span id="GPS_Inside_Fence"> A</span><br>
			Rain_Detected: <span id="Rain_Detected"> A</span><br>
			Wheel_Blocked_Status: <span id="Wheel_Blocked_Status"> A</span><br>
			<br>
			<h3>Simulation</h3>

			<p><button class="button" onclick="send(110)">ON</button>
			   <button class="button" onclick="send(111)">OFF</button>
			   Fake_All_Settings: <span id="Fake_All_Settings"></span></p>

			<p><button class="button" onclick="send(112)">ON</button>
			   <button class="button" onclick="send(113)">OFF</button>
			   Fake_Loops: <span id="Fake_Loops"></span></p>

			<p><button class="button" onclick="send(114)">ON</button>
			   <button class="button" onclick="send(115)">OFF</button>
			   Fake_Wire: <span id="Fake_Wire"></span></p>

			<p><button class="button" onclick="send(116)">ON</button>
			   <button class="button" onclick="send(117)">OFF</button>
			   Fake_WheelAmp: <span id="Fake_WheelAmp"></span></p>

		</div>

		<script>
		setInterval(function() 
		{
		  getData();
		}, 500);
 
		function getData() {
		  var xhttp = new XMLHttpRequest();
		  xhttp.onreadystatechange = function() {
		    if (this.readyState == 4 && this.status == 200) {
				var res = JSON.parse(xhttp.responseText);
				
				document.getElementById("BatteryVoltage").innerHTML = res.BatteryVoltage;
				document.getElementById("ChargeAmps").innerHTML = res.ChargeAmps;
				document.getElementById("WheelAmps").innerHTML = res.WheelAmps;
				document.getElementById("distance1").innerHTML = res.distance1;
				document.getElementById("distance2").innerHTML = res.distance2;
				document.getElementById("distance3").innerHTML = res.distance3;
				document.getElementById("Sonar_Status").innerHTML = res.Sonar_Status;
				document.getElementById("Outside_Wire").innerHTML = res.Outside_Wire;
				document.getElementById("Bumper").innerHTML = res.Bumper;
				document.getElementById("Tilt_Angle_Sensed").innerHTML = res.Tilt_Angle_Sensed;
				document.getElementById("GPS_Inside_Fence").innerHTML = res.GPS_Inside_Fence;
				document.getElementById("Rain_Detected").innerHTML = res.Rain_Detected;
				document.getElementById("Wheel_Blocked_Status").innerHTML = res.Wheel_Blocked_Status;
				
				document.getElementById("Fake_All_Settings").innerHTML = res.Fake_All_Settings;
				document.getElementById("Fake_Loops").innerHTML = res.Fake_Loops;
				document.getElementById("Fake_Wire").innerHTML = res.Fake_Wire;
				document.getElementById("Fake_WheelAmp").innerHTML = res.Fake_WheelAmp;
				//document.getElementById("").innerHTML = res.;
		    }
		  };
		  xhttp.open("GET", "/test_getData", true);
		  xhttp.send();
		}

		function send(btnNo) 
		{
		  var xhttp = new XMLHttpRequest();
		  xhttp.open("GET", "cmdTest?btn="+btnNo, true);
		  xhttp.send();
		}
		</script>

		</center>
		</body>
		</html>
		)====="
;



const char RemoteCtrl_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 15px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 14px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<h2><a href="/">Home</a> &nbsp;&nbsp; <a href="/setup">Setup</a> &nbsp;&nbsp; <a href="/test">Test</a> &nbsp;&nbsp; <a href="/rundata">RunData</a> &nbsp;&nbsp;</h2>
		<center>
		<div>
		<h1>ReP_AL Robot - Remote Control</h1>
			<br>
			  <button class="button" onclick="send(5)">Manual</button>
			  <button class="button" onclick="send(6)">Auto</button><br><br>
			  <button class="button" onclick="send(21)">AutoSpiral</button>
			  <button class="button" onclick="send(22)">AutoParallel</button><br><br>
			  <br><br>
			  <button class="button" onclick="send(4)">ExitDock</button>
			  <button class="button" onclick="send(3)">QuickStart</button><br><br>
			  <button class="button" onclick="send(2)">GoToDock</button>
			  <button class="button" onclick="send(1)">PauseStop</button><br><br>
			  <br><br>
			  <button class="button" onclick="send(9)">WheelLeft</button>
			  <button class="button" onclick="send(7)">WheelForward</button>
			  <button class="button" onclick="send(10)">WheelRight</button><br><br>
			  <button class="button" onclick="send(8)">WheelReverse</button><br><br>
		</div>
		 <br>

		<script>
		setInterval(function() 
		{
		  getData();
		}, 500);
 
		function getData() {
		  var xhttp = new XMLHttpRequest();
		  xhttp.onreadystatechange = function() {
		    if (this.readyState == 4 && this.status == 200) {
				var res = JSON.parse(xhttp.responseText);
				
				document.getElementById("MowerMode").innerHTML = res.MowerMode;
		    }
		  };
		  xhttp.open("GET", "/remotectrl_getData", true);
		  xhttp.send();
		}

		function send(btnNo) 
		{
		  var xhttp = new XMLHttpRequest();
		  xhttp.open("GET", "cmdRemoteCtrl?btn="+btnNo, true);
		  xhttp.send();
		}
		</script>

		</center>
		</body>
		</html>
		)====="
;


const char RunData_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 15px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 14px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<h2><a href="/">Home</a> &nbsp;&nbsp; <a href="/setup">Setup</a> &nbsp;&nbsp; <a href="/test">Test</a> &nbsp;&nbsp; <a href="/remotectrl">RemoteControl</a> &nbsp;&nbsp; </h2>
		<br>
		<h1>ReP_AL Robot - Running data</h1>
		<br>
		<div>
			Battery[V]:  <span id="BatteryVoltage"> V</span><br>
			Charging[A]: <span id="ChargeAmps"> A</span><br>
			<br>
			Loop_Cycle_Mowing: <span id="Loop_Cycle_Mowing"> A</span><br>
			Robot_Status_Value: <span id="Robot_Status_Value"> A</span><br>
			Mower_Error_Value: <span id="Mower_Error_Value"> A</span><br>
			Compass_Steering_Status: <span id="Compass_Steering_Status"> A</span><br>
			Compass_Heading_Degrees: <span id="Compass_Heading_Degrees"> A</span><br>
			MAG_Now: <span id="MAG_Now"> A</span><br>
			Compass_Error: <span id="Compass_Error"> A</span><br>
			PWM_Right: <span id="PWM_Right"> A</span><br>
			PWM_Left: <span id="PWM_Left"> A</span><br>
			Mower_RunBack: <span id="Mower_RunBack"> A</span><br>
			Manouver_Turn_Around_Phase: <span id="Manouver_Turn_Around_Phase"> A</span><br>
			Manouver_Turn_Around_Sonar_Phase: <span id="Manouver_Turn_Around_Sonar_Phase"> A</span><br>
			<br>
			WheelAmps[A]: <span id="WheelAmps"> A</span><br>
			Wheel_Blocked_Status: <span id="Wheel_Blocked_Status"> A</span><br>
			Sonar dist1: <span id="distance1"> A</span><br>
			Sonar dist2: <span id="distance2"> A</span><br>
			Sonar dist3: <span id="distance3"> A</span><br>
			Sonar_Status: <span id="Sonar_Status"> A</span><br>
			Outside_Wire: <span id="Outside_Wire"> A</span><br>
			Bumper: <span id="Bumper"> A</span><br>
			Tilt_Angle_Sensed: <span id="Tilt_Angle_Sensed"> A</span><br>
			GPS_Inside_Fence: <span id="GPS_Inside_Fence"> A</span><br>
			Rain_Detected: <span id="Rain_Detected"> A</span><br>
		</div>

		<script>
		setInterval(function() 
		{
		  getData();
		}, 500);
 
		function getData() {
		  var xhttp = new XMLHttpRequest();
		  xhttp.onreadystatechange = function() {
		    if (this.readyState == 4 && this.status == 200) {
				var res = JSON.parse(xhttp.responseText);
				
				document.getElementById("BatteryVoltage").innerHTML = res.BatteryVoltage;
				document.getElementById("ChargeAmps").innerHTML = res.ChargeAmps;
				
				document.getElementById("Loop_Cycle_Mowing").innerHTML = res.Loop_Cycle_Mowing;
				document.getElementById("Robot_Status_Value").innerHTML = res.Robot_Status_Value;
				document.getElementById("Mower_Error_Value").innerHTML = res.Mower_Error_Value;
				document.getElementById("Compass_Steering_Status").innerHTML = res.Compass_Steering_Status;
				document.getElementById("Compass_Heading_Degrees").innerHTML = res.Compass_Heading_Degrees;
				document.getElementById("MAG_Now").innerHTML = res.MAG_Now;
				document.getElementById("Compass_Error").innerHTML = res.Compass_Error;
				document.getElementById("PWM_Right").innerHTML = res.PWM_Right;
				document.getElementById("PWM_Left").innerHTML = res.PWM_Left;
				document.getElementById("Mower_RunBack").innerHTML = res.Mower_RunBack;
				document.getElementById("Manouver_Turn_Around_Phase").innerHTML = res.Manouver_Turn_Around_Phase;
				document.getElementById("Manouver_Turn_Around_Sonar_Phase").innerHTML = res.Manouver_Turn_Around_Sonar_Phase;

				document.getElementById("WheelAmps").innerHTML = res.WheelAmps;
				document.getElementById("distance1").innerHTML = res.distance1;
				document.getElementById("distance2").innerHTML = res.distance2;
				document.getElementById("distance3").innerHTML = res.distance3;
				document.getElementById("Sonar_Status").innerHTML = res.Sonar_Status;
				document.getElementById("Outside_Wire").innerHTML = res.Outside_Wire;
				document.getElementById("Bumper").innerHTML = res.Bumper;
				document.getElementById("Tilt_Angle_Sensed").innerHTML = res.Tilt_Angle_Sensed;
				document.getElementById("GPS_Inside_Fence").innerHTML = res.GPS_Inside_Fence;
				document.getElementById("Rain_Detected").innerHTML = res.Rain_Detected;
				document.getElementById("Wheel_Blocked_Status").innerHTML = res.Wheel_Blocked_Status;
				//document.getElementById("").innerHTML = res.;

		    }
		  };
		  xhttp.open("GET", "/rundata_getData", true);
		  xhttp.send();
		}
		</script>

		</body>
		</html>
		)====="
;



const char ArduDiagCtrl_Html[] PROGMEM = R"=====(
		<!DOCTYPE html>
		<html>
		<style type="text/css">
		.button {
		  background-color: #4CAF50; /* Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 15px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		.button:focus {
		  background-color: #099999; /* Dark Green */
		  border: outset;
		  border-radius: 12px;
		  color: white;
		  padding: 14px 32px;
		  text-align: center;
		  text-decoration: none;
		  display: inline-block;
		  font-size: 16px;
		}
		</style>
		<body style="background-color: #f9e79f ">
		<h2><a href="/">Home</a> &nbsp;&nbsp; <a href="/setup">Setup</a> &nbsp;&nbsp; <a href="/test">Test</a> &nbsp;&nbsp; <a href="/remotectrl">RemoteControl</a> &nbsp;&nbsp; <a href="/rundata">RunData</a> &nbsp;&nbsp; </h2>
		<br>
		<h1>ReP_AL Robot - Arduino Diag / Control</h1>
		<br>
		<div>
		  <button class="button" onclick="send(0)">Mega HW reset</button><br><br>
		  <button class="button" onclick="send(1)">Mega SW reset</button><br><br>
		  <button class="button" onclick="send(2)">TFT SW reset</button><br><br>
		  <button class="button" onclick="send(3)">NodeMCU SW reset</button><br><br>
		</div>

		<script>
		function send(btnNo) 
		{
		  var xhttp = new XMLHttpRequest();
		  xhttp.open("GET", "cmdArduDiagCtrl?btn="+btnNo, true);
		  xhttp.send();
		}
		</script>

		</body>
		</html>
		)====="
;



const char * javascriptCode = " <!DOCTYPE html> "
"<html>"
"<body>"
"<p>Click the button to get a message from the ESP8266:</p>"
"<button onclick=\"buttonFunction()\">Message</button>"
"<script>"
"function buttonFunction() { "
" alert(\"Hello from the ESP8266!\"); "
"} "
"</script>"
"</body>"
"</html>";

/*
String SendHTML(
		String str,
		String mode
		){
	String ptr = "<!DOCTYPE html> <html>\n";
	ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
	ptr +="<meta http-equiv='refresh' content='1'>"; // auto refresh web page - number is delay in seconds
	ptr +="<title>ESP8266 Global Server</title>\n";

	ptr +="</head>\n";
	ptr +="<body>\n";
	ptr +="<div id=\"webpage\">\n";
	ptr +="<h1>ReP_AL Robot WebServer</h1>\n";

	ptr +="Mode: ";
	ptr +=mode;
	ptr +="<br>Robot_Status_Value: ";
	ptr +=Robot_Status_Value;
	ptr +="<br>Mower_Error_Value: ";
	ptr +=Mower_Error_Value;
	ptr +="<br>Loop_Cycle_Mowing: ";
	ptr +=Loop_Cycle_Mowing;

	ptr +="<br>Mower_RunBack: ";
	ptr +=Mower_RunBack;
	ptr +="<br>Manouver_Turn_Around_Phase: ";
	ptr +=Manouver_Turn_Around_Phase;
	ptr +="<br>Manouver_Turn_Around_Sonar_Phase: ";
	ptr +=Manouver_Turn_Around_Sonar_Phase;

	ptr +="<br>Compass_Heading_Lock: ";
	ptr +=Compass_Heading_Lock;
	ptr +="<br>Compass_Steering_Status: ";
	ptr +=Compass_Steering_Status;
	ptr +="<br>Compass_Heading_Degrees: ";
	ptr +=Compass_Heading_Degrees;
	ptr +="<br>Compass_Error: ";
	ptr +=Compass_Error;
	ptr +="°<br>MAG_Now: ";
	ptr +=MAG_Now;

	ptr +="<br>WheelAmps: ";
	ptr +=WheelAmps;
	ptr +="<br>PWM_Right: ";
	ptr +=PWM_Right;
	ptr +="<br>PWM_Left: ";
	ptr +=PWM_Left;

	ptr +="<br>BatteryVoltage: ";
	ptr +=BatteryVoltage;
	ptr +="<br>Amps: ";
	ptr +=Amps;

	ptr +="<br>Sonar_Status: ";
	ptr +=Sonar_Status;
	ptr +="<br>Outside_Wire: ";
	ptr +=Outside_Wire;
	ptr +="<br>Bumper: ";
	ptr +=Bumper;
	ptr +="<br>Tilt_Angle_Sensed: ";
	ptr +=Tilt_Angle_Sensed;
	ptr +="<br>Wheel_Blocked_Status: ";
	ptr +=Wheel_Blocked_Status;
	//ptr +="<br>GPS_Inside_Fence: ";
	//ptr +=GPS_Inside_Fence;
	ptr +="<br>Rain_Detected: ";
	ptr +=Rain_Detected;
	//ptr +="<br>: ";
	//ptr +=;

	ptr +="<br>";

	ptr +="</div>\n";
	ptr +="</body>\n";
	ptr +="</html>\n";
	return ptr;
}
*/

#endif //-(WEBSERVER)-

#endif /* WEBPAGES_INO_ */
