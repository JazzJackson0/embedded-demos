/*Hook function implementations to be used if needed*/

void vApplicationIdleHook(void) {
	
	//Put Microcontroller into sleep mode
}


void vApplicationTickHook(void) {
	
	
}

void vApplicationMallocFailedHook(void) {
	
	
}


void FRTOS1vApplicationStackOverflowHook(xTaskHandle pxTask, signed portCHAR *pcTaskName) {
  /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECKFORSTACKOVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. /
  (void)pxTask;
  (void)pcTaskName;
  taskDISABLE_INTERRUPTS();
  / Write your code here … */
  for(;;) {}
 }

