/*
 * General function for control of cycle or measuring of loop cycle time
 *
 */

signed long resultCTime;
signed long startCTime;




// function for measuring of loop cycle time, for usage just call it
void RuntimeMeasuring() {
	resultCTime = (signed long)millis() - startCTime;
	Serial.print(F("|CT:")); Serial.print(resultCTime); Serial.print(F("|"));
	startCTime = (signed long)millis();
}


bool TimerDelayOn(struct timerVar_t &T, int T_PRE)//, int T_PRE)
// Function Timer with delay on, auto reset when condition are met
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


bool TimerDelayOnRet(struct timerVar_t &T)//, int T_PRE)
// Function Retentive timer with delay on, reset should be done by function TimerReset()
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

