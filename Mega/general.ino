/*
 * General function for control of cycle or measuring of loop cycle time
 *
 */

signed long resultCTime;  // result of loop cycle time
signed long startCTime;   // variable where time of measuring start is stored




// function for measuring of loop cycle time, for usage just call it
void RuntimeMeasuring() {
	resultCTime = (signed long)millis() - startCTime;
	Serial.print(F("|CT:")); Serial.print(resultCTime); Serial.print(F("|"));
	startCTime = (signed long)millis();
}


// Function Timer with delay on, auto reset when condition are met
// usage: if (TimerDelayOn(T10, 10000)) Print_Time_TFT(); -> this will call function Print_Time_TFT() each 10s
bool TimerDelayOn(struct timerVar_t &T, int T_PRE)//, int T_PRE)
{
	bool ret = false;

	if (!T.flagRun) {
		T.PRE = T_PRE;
		T.REF = (signed long)millis();
		T.flagRun = true;
	}

	T.ACC =(signed long)millis() - T.REF;
	if (T.ACC > T.PRE)
	{
		T.flagRun = false;
		ret = true;
	}

	return ret;
}


// Function Retentive timer with delay on, reset should be done by function TimerReset()
bool TimerDelayOnRet(struct timerVar_t &T)//, int T_PRE)
{
	bool ret = false;

	if (!T.flagRun) {
		//T.PRE = T_PRE;
		T.REF = (signed long)millis();
		T.flagRun = true;
	}

	T.ACC =(signed long)millis() - T.REF;
	if (T.ACC > T.PRE)
	{
		ret = true;
	}

	return ret;
}



void TimerReset(struct timerVar_t &T)
{
	T.REF = (signed long)millis();
	T.flagRun = false;
}


void MEGA_WDT()
{
#if defined(WDT) and defined(BOARD_MEGA)
  if (Mower_Running == 1 && !wdt_enable_flagRun) {
	  //wdt_enable(WDTO_2S); // reset Mega when freeze longer then 2 seconds
	  //wdt_enable(WDTO_4S); // reset Mega when freeze longer then 4 seconds
	  wdt_enable(WDTO_8S); // reset Mega when freeze longer then 8 seconds
	  wdt_enable_flagRun = true;
  }
  else if (Mower_Running == 0) {
	  wdt_disable();
	  if (wdt_enable_flagRun) Serial.println(F("\n !!! WDT disabled !!!"));
	  wdt_enable_flagRun = false;
  }
  else {
	  wdt_reset(); // reset HW WatchDog timer
  }


  // remote software restart of Arduino Mega
  if (Mega_SW_restart_En) {
	  wdt_disable();
	  wdt_enable(WDTO_15MS);
	  while (1) {}
  }
#endif // -(WDT)-
}


