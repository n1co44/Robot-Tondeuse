/*
 * WebServer.ino
 *
 *
 */




// *** Web pages handlers ***
void handleRoot() {
#if defined(WEBSERVER)
	String s = Index_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}

void handleSetup() {
#if defined(WEBSERVER)
	String s = Setup_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}

void handleTest() {
#if defined(WEBSERVER)
	String s = Test_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}

void handleRemoteCtrl() {
#if defined(WEBSERVER)
	String s = RemoteCtrl_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}

void handleRunData() {
#if defined(WEBSERVER)
	String s = RunData_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}

void handleArduDiagCtrl() {
#if defined(WEBSERVER)
	String s = ArduDiagCtrl_Html;
	server.send(200, "text/html", s);
#endif //-(WEBSERVER)-
}
/*
void handleAllData() {
#if defined(WEBSERVER)
	String str;
	String mode = MowerMode();
	server.send(200, "text/html", SendHTML(str, mode));
	#endif //-(WEBSERVER)-
}*/


// *** Get data handlers ***
void handleIndexGetData() {
#if defined(WEBSERVER)
	server.send(200, "text/html", getJson_index());
#endif //-(WEBSERVER)-
}

void handleSetupGetData() {
#if defined(WEBSERVER)
	server.send(200, "text/html", getJson_setup());
#endif //-(WEBSERVER)-
}

void handleTestGetData() {
#if defined(WEBSERVER)
	server.send(200, "text/html", getJson_test());
#endif //-(WEBSERVER)-
}

void handleRemoteCtrlGetData() {
#if defined(WEBSERVER)
	server.send(200, "text/html", getJson_remoteCtrl());
#endif //-(WEBSERVER)-
}

void handleRunDataGetData() {
#if defined(WEBSERVER)
	server.send(200, "text/html", getJson_runData());
#endif //-(WEBSERVER)-
}


// *** Set data handlers ***
void handleSetupSetData() {
#if defined(WEBSERVER)
	int i_web = 0;
	if (server.args()>0){
		if (server.arg("btn")!="") {
			String msg = server.arg("btn");
			i_web = msg.toInt();
		}

		server.sendHeader("Location","/setup");        // Add a header to respond with a new location for the browser to go to the home page again
		server.send(303);

		Transmit_Web_Data_to_Mega(i_web);
	}
#endif //-(WEBSERVER)-
}


void handleTestSetData() {
#if defined(WEBSERVER)
	int i_web = 0;
	if (server.args()>0){
		if (server.arg("btn")!="") {
			String msg = server.arg("btn");
			i_web = msg.toInt();
		}

		server.sendHeader("Location","/test");        // Add a header to respond with a new location for the browser to go to the home page again
		server.send(303);

		Transmit_Web_Data_to_Mega(i_web);
	}
#endif //-(WEBSERVER)-
}


void handleRemoteCtrlSetData() {
#if defined(WEBSERVER)
	int i_web = 0;
	if (server.args()>0){
		if (server.arg("btn")!="") {
			String msg = server.arg("btn");
			i_web = msg.toInt();
		}

		server.sendHeader("Location","/remotectrl");        // Add a header to respond with a new location for the browser to go to the home page again
		server.send(303);

		Transmit_Web_Data_to_Mega(i_web);
	}
#endif //-(WEBSERVER)-
}


void handleArduDiagCtrlSetData() {
#if defined(WEBSERVER)
	//int i_web = 0;
	if (server.args()>0){
		if (server.arg("btn")!="") {
			String msg = server.arg("btn");
			if      (msg.toInt()==0) Mega_HW_restart();
			else if (msg.toInt()==1) Mega_SW_restart();
			else if (msg.toInt()==2) TFT_SW_restart();
			else if (msg.toInt()==3) NodeMCU_SW_restart();
		}

		server.sendHeader("Location","/ardudiagctrl");        // Add a header to respond with a new location for the browser to go to the home page again
		server.send(303);

		//Transmit_Web_Data_to_Mega(i_web);
	}
#endif //-(WEBSERVER)-
}


// *** Other functions ***
String MowerMode() {
	String ptr="";
#if defined(WEBSERVER)

	if 		(Mower_Parked == 1) 	ptr +="Parked";
	else if (Mower_Docked == 1) 	ptr +="Docked";
	else if (Mower_Running == 1) 	ptr +="Running";
	else if (Charge_Detected == 1) 	ptr +="Charging";
	else if (Tracking_Wire == 1) 	ptr +="Tracking_Wire";
	else if (Manuel_Mode) 			ptr +="Manual";

#endif //-(WEBSERVER)-
	return ptr;
}



void Mega_HW_restart() {
#if defined(WEBSERVER)
	SerialDebug.println("MEGA HW restart over web");
	digitalWrite(D5, HIGH);
	digitalWrite(D5, LOW);
	delay(50);
	digitalWrite(D5, HIGH);
#endif //-(WEBSERVER)-
}

void Mega_SW_restart() {
#if defined(WEBSERVER)
	SerialDebug.println("MEGA SW restart over web");
	Transmit_Web_Data_to_Mega(200);
#endif //-(WEBSERVER)-
}

void TFT_SW_restart() {
#if defined(WEBSERVER)
	SerialDebug.println("TFT SW restart over web");
	Transmit_Web_Data_to_Mega(201);
#endif //-(WEBSERVER)-
}

void NodeMCU_SW_restart() {
#if defined(WEBSERVER)
	ESP.restart();
#endif //-(WEBSERVER)-
}


void startServer() {
#if defined(WEBSERVER)
	server.begin();

	// *** Web pages ***
	server.on("/", handleRoot);
	server.on("/setup", handleSetup);
	server.on("/test", handleTest);
	server.on("/remotectrl", handleRemoteCtrl);
	server.on("/rundata", handleRunData);
	server.on("/ardudiagctrl", handleArduDiagCtrl);
	//server.on("/alldata", handleAllData);

	// *** Get data ***
	server.on("/index_getData", handleIndexGetData);
	server.on("/setup_getData", handleSetupGetData);
	server.on("/test_getData", handleTestGetData);
	server.on("/remotectrl_getData", handleRemoteCtrlGetData);
	server.on("/rundata_getData", handleRunDataGetData);

	// *** Set data ***
	server.on("/cmdSetup", handleSetupSetData);
	server.on("/cmdTest", handleTestSetData);
	server.on("/cmdRemoteCtrl", handleRemoteCtrlSetData);
	server.on("/cmdArduDiagCtrl", handleArduDiagCtrlSetData);

	server.on("/javascript", []() { //temporary for test
		server.send(200, "text/html", javascriptCode);
	});
#endif //-(WEBSERVER)-
}


