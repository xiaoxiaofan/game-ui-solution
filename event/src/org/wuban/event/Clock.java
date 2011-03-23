package org.wuban.event;

import java.util.ArrayList;
import java.util.List;

public class Clock {

	private  List<EventListener> listeners = new ArrayList<EventListener>();
	
	public  void addWakeUpListener(WakeUpListener wakeUpListener){
		listeners.add(wakeUpListener);
	}
	
	public void addDateListener(DateListener dateListener){
		listeners.add(dateListener);
	}
	
	public void checkListeners(){
		for (EventListener listener : listeners) {
			listener.performed();
		}
	}
	
	public static void main(String[] args) {
		Clock clock = new Clock();
		clock.addWakeUpListener(new WakeUpListener(new WakeUpEvent1()));
		clock.addWakeUpListener(new WakeUpListener(new WakeUpEvent2()));
		clock.addWakeUpListener(new WakeUpListener(new WakeUpEvent3()));
		clock.addDateListener(new DateListener(new DateEvent1()));
		clock.addDateListener(new DateListener(new DateEvent2()));
		clock.checkListeners();
	}
}
